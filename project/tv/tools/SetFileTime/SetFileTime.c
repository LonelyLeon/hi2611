/*修改文件的时间*/
/*qiny @2013-10-9*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdarg.h>
#include <getopt.h>
#include<sys/types.h>
#include<utime.h>



#define FILE_NAME_MAX_LEN 256

static char filename[FILE_NAME_MAX_LEN] = {'\0'};
static int mode = 0;


static struct option long_options[] =
{
	{"help", 0, 0, 'h'},
	{"file", 1, 0, 'f'},
	{"mode", 1, 0, 'm'},
	{0, 0, 0, 0}
};

/** @brief 显示命令行*/
static void usage()
{
	fprintf (stderr, "Usage: SetFileTime [-f file] [-m 0]\n");
	fprintf (stderr, "    -f --file,		file\n");
	fprintf (stderr, "    -m --mode,	time mode : 0, current time\n");	
	exit(0);
}

/*修改文件的时间*/
static int setfiletime()
{
	int ret;

       if(mode == 0)
      {
	    ret = utime(filename, NULL);
	    printf("setfiletime ret = %d\n", ret);        
      }
      else
      {

      }
      
	return 0;
}


/** @brief 主函数*/
int main (int argc, char **argv)
{
	int c;
	
	while(1)
	{
		int option_index = 0;
		
		c = getopt_long (argc, argv, "hf:m:", long_options, &option_index);	
		if(c == -1) break;
		
		switch(c)
		{
			case 'h':
				usage();
				break;
			case 'f':
				strcpy(filename, optarg);				
				break;
			case 'm':
				mode = strtoul(optarg, NULL, 0);
				break;
			default:
				exit(-1);
				break;
		}		
	}

    setfiletime();
    return 0;
}

