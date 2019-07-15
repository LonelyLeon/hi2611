//合并多个文件数据
//2011-5-9 haier 覃宜


#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <getopt.h>
#include <stdlib.h>

#define FILE_NAME_MAX_LEN 256

static char dfilename[FILE_NAME_MAX_LEN] = {'\0'};
static char sfilename[FILE_NAME_MAX_LEN] = {'\0'};

static FILE* dfpin = NULL;
static FILE* sfpin = NULL;

static int address = 0;
static int	setData = 0;

static int mode = -1;

static struct option long_options[] =
{
	{"help", 0, 0, 'h'},
	{"dfile", 1, 0, 'i'},
	{"address", 1, 0, 'a'},
	{"data", 1, 0, 'd'},
	{"sfile", 1, 0, 'f'},
	{0, 0, 0, 0}
};



/** @brief 显示命令行*/
static void usage()
{
	fprintf (stderr, "Usage: SetFileData [-i file.bin] [-a 0x00000000] [-d 0x12345678] -o outfile\n");
	fprintf (stderr, "    -i --dfile,		destination file\n");
	fprintf (stderr, "    -a --address,		address\n");	
	fprintf (stderr, "    -d --data,			data.\n");
	fprintf (stderr, "    -f --sfile,			source file\n");
	fprintf (stderr, "    -h --help,			print this help.\n");
	exit(0);
}

static void release_all()
{
	if(dfpin)fclose(dfpin);
	if(sfpin)fclose(sfpin);
}


static int setfiledata()
{
	unsigned char *buf = NULL;
	int SrcSize = 0, DesSize = 0;

	if(!dfpin || mode == (-1))
		return 0;

	if(mode == 0)
		printf("\n>> Set file data :  %s  address 0x%08x   data 0x%08x\n", dfilename, address, setData);
	else
		printf("\n>> Set file data :  %s  address 0x%08x   data %s\n", dfilename, address, sfilename);

	fseek(dfpin, 0L, SEEK_END);	
	DesSize = ftell(dfpin);

	if(DesSize < address)
	{
		printf("err  filesize(0x%08x) <  address(0x%08x)\n", DesSize, address);
		return 0;
	}
			
	fseek(dfpin, address, SEEK_SET);

	if(mode == 0)
	{
		buf = (unsigned char*)malloc(4);
		buf[0] = (unsigned char)((setData >> 24) & 0xff);
		buf[1] = (unsigned char)((setData >> 16) & 0xff);
		buf[2] = (unsigned char)((setData >> 8) & 0xff);
		buf[3] = (unsigned char)(setData & 0xff);
		fwrite(buf, 1, 4, dfpin);
		free(buf);
		buf = NULL;
	}
	else
	{
		fseek(sfpin, 0L, SEEK_END);	
		SrcSize = ftell(sfpin);		
		buf = (unsigned char*)malloc(SrcSize);
		if(buf == NULL)
		{
			printf("Unable to malloc memory\n");
			return 0;		
		}

		memset(buf, 0, SrcSize);
		fseek(sfpin, 0L, SEEK_SET);
		
		if(SrcSize == fread(buf, 1, SrcSize, sfpin))
		{
			if(SrcSize != fwrite(buf, 1, SrcSize, dfpin))
			{
				printf("write the  destination file err!\n");
				free(buf);			
				return 0;
			}				
		}
		else
		{
			printf("read the source file  err!\n");
			free(buf);		
			return 0;
		}

		free(buf);
		buf = NULL;
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
		
		c = getopt_long (argc, argv, "hi:a:d:f:", long_options, &option_index);	
		if(c == -1) break;
		
		switch(c)
		{
			case 'h':
				usage();
				break;
			case 'i':
				strcpy(dfilename, optarg);
				if((dfpin = fopen(dfilename,"rb+")) == NULL)
				{
					fprintf(stderr, "ERROR: Cannot open file `%s`\n",dfilename);
					exit(-1);
				}				
				break;
			case 'a':
				address = strtoul(optarg, NULL, 0);
				break;
			case 'd':
				mode = 0;
				setData = strtoul(optarg, NULL, 0);
				break;
			case 'f':
				mode = 1;
				strcpy(sfilename, optarg);
				if((sfpin = fopen(sfilename,"rb")) == NULL)
				{
					fprintf(stderr, "ERROR: Cannot open file `%s`\n",sfilename);
					exit(-1);
				}
				break;
			default:
				exit(-1);
				break;
		}		
	}	

	setfiledata();

	release_all();
	
	return 0;
}


