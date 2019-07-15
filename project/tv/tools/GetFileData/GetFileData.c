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
static int  getLen = 0;



static struct option long_options[] =
{
    {"help", 0, 0, 'h'},
    {"sfile", 1, 0, 'i'},
    {"address", 1, 0, 'a'},
    {"len", 1, 0, 'l'},
    {"dfile", 1, 0, 'o'},
    {0, 0, 0, 0}
};



/** @brief 显示命令行*/
static void usage()
{
    fprintf (stderr, "Usage: SetFileData [-i file.bin] [-a 0x00000000] [-l 0x100] -o outfile\n");
    fprintf (stderr, "    -i --sfile,		source file\n");
    fprintf (stderr, "    -a --address,		address\n");
    fprintf (stderr, "    -l --len,			len\n");
    fprintf (stderr, "    -o --dfile,			destination file\n");
    fprintf (stderr, "    -h --help,			print this help.\n");
    exit(0);
}

static void release_all()
{
    if(dfpin)fclose(dfpin);
    if(sfpin)fclose(sfpin);
}


static int getfiledata()
{
    unsigned char *buf = NULL;
    int SrcSize = 0;

    if((!dfpin) || (!sfpin))
        return 0;

    printf("\n>> Get file data from: %s addr 0x%08x len 0x%08x -> %s\n", sfilename, address, getLen, dfilename);

    fseek(sfpin, 0L, SEEK_END);
    SrcSize = ftell(sfpin);

    if(getLen == 0 || SrcSize <= address || (address + getLen) > SrcSize)
    {
        printf("err  adress or len\n");
        return 0;
    }

    fseek(sfpin, address, SEEK_SET);

    buf = (unsigned char*)malloc(getLen);
    if(buf == NULL)
    {
        printf("Unable to malloc memory\n");
        return 0;
    }

    memset(buf, 0, getLen);

    if(getLen == fread(buf, 1, getLen, sfpin))
    {
        if(getLen != fwrite(buf, 1, getLen, dfpin))
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

    return 0;
}




/** @brief 主函数*/
int main (int argc, char **argv)
{
    int c;

    while(1)
    {
        int option_index = 0;

        c = getopt_long (argc, argv, "hi:a:l:o:", long_options, &option_index);
        if(c == -1) break;

        switch(c)
        {
            case 'h':
                usage();
                break;
            case 'i':
                strcpy(sfilename, optarg);
                if((sfpin = fopen(sfilename, "rb")) == NULL)
                {
                    fprintf(stderr, "ERROR: Cannot open file `%s`\n", sfilename);
                    exit(-1);
                }
                break;
            case 'a':
                address = strtoul(optarg, NULL, 0);
                break;
            case 'l':
                getLen = strtoul(optarg, NULL, 0);
                break;
            case 'o':
                strcpy(dfilename, optarg);
                if((dfpin = fopen(dfilename, "wb+")) == NULL)
                {
                    fprintf(stderr, "ERROR: Cannot open file `%s`\n", dfilename);
                    exit(-1);
                }
                break;
            default:
                exit(-1);
                break;
        }
    }

    getfiledata();

    release_all();

    return 0;
}


