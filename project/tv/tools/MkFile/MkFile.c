/** @file
* @brief 创建一个新文件
*
* @author 李臣
* @date 2013-09-03 李臣: 建立文件
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <getopt.h>

static void usage()
{
	fprintf (stderr, "Usage: MkFile -b(-r) -s size -o outfile\n");
	fprintf (stderr, "    -b --byte,\t\t填充指定字节\n");
	fprintf (stderr, "    -r --random,\t\t填充随机字节\n");		
	fprintf (stderr, "    -s --size,\t\t生成文件大小\n");
	fprintf (stderr, "    -o --output,\t\t生成文件名\n");	
	fprintf (stderr, "    -h --help,\t\tprint this help.\n");
	exit(0);
}

static struct option long_options[] =
{
	{"help", 0, 0, 'h'},
	{"byte", 1, 0, 'b'},
	{"random", 0, 0, 'r'},
	{"size", 1, 0, 's'},
	{"output", 1, 0, 'o'},
	{0, 0, 0, 0}
};

static unsigned char fillbyte = 0xFF; /* 默认填充0xFF */
static int fillrandom = 0;
static unsigned long filesize = 0;
static FILE *fout = NULL;

int main(int argc, char *argv[])
{
    int c;
    int b;
    unsigned int cnt;

    while(1)
	{
		int option_index = 0;
		
		c = getopt_long(argc, argv, "hb:rs:o:", long_options, &option_index);
		if(c == -1) break;
		
		switch(c)
		{
			case 'b':
                fillbyte = (unsigned char)strtoul(optarg, NULL, 0);
				break;
			case 'r':
				fillrandom = 1;
				break;
			case 's':
                filesize = strtoul(optarg, NULL, 0);
				break;
			case 'o':
				if((fout = fopen(optarg, "wb")) == NULL)
				{
					fprintf(stderr, "ERROR: Cannot create file `%s`!\n", optarg);
					exit(-1);
				}
				break;
            case 'h':
			default:
                usage();
				exit(-1);
				break;
		}		
	}

    if(fout == NULL)
    {
        fprintf(stderr, "ERROR: Must specify output file!\n\n");
        usage();
        return -1;
    }

    printf("Making...");

    b = fillbyte;
    srand((unsigned int)time(NULL));
    cnt = 0;

    while(filesize)
    {
        if(fillrandom)
            b = rand() & 0xFF;

        fputc(b, fout);

        filesize --;
        cnt ++;
    }

    fclose(fout);

    printf("OK!\n");
    printf("Total %u Bytes.\n", cnt);

    return 0;
}

