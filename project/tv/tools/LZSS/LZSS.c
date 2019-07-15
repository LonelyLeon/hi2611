//LZSS压缩解压算法
//压缩后的文件信息包含
//55AA5AA5 + 压缩前长度(4bytes) + 压缩后长度(4bytes)+ 压缩数据+ [双字节补齐FF]
//2011-5-9 haier 覃宜
/*========================LZSS.C===================
	LZSS.C -- A Data Compression Program
	(tab = 4 spaces)
***************************************************************
	4/6/1989 Haruhiko Okumura
	Use, distribute, and modify this program freely.
	Please send me your improved versions.
		PC-VAN		SCIENCE
		NIFTY-Serve	PAF01022
		CompuServe	74050,1022
**************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <getopt.h>
#include <malloc.h>

#define FILE_NAME_MAX_LEN 256



static char filename_in[FILE_NAME_MAX_LEN] = {'\0'};
static char filename_out[FILE_NAME_MAX_LEN] = {'\0'};

static int operate_mode = -1;




#define N		 4096	/* size of ring buffer */
#define F		   16	/* upper limit for match_length */
#define THRESHOLD	2   /* encode string into position and length
						   if match_length is greater than this */
#define NIL			N	/* index for root of binary search trees */


static unsigned long int	textsize = 0;	/* text size counter */
static unsigned long int	codesize = 0;	/* code size counter */
static unsigned char		text_buf[N + F - 1];	/* ring buffer of size N,	with extra F-1 bytes to facilitate string comparison */
static int	match_position, match_length,  /* of longest match.  These are set by the InsertNode() procedure. */
		lson[N + 1], rson[N + 257], dad[N + 1];  /* left & right children &	parents -- These constitute binary search trees. */
//FILE	*infile, *outfile;  /* input & output files */




static void InitTree(void)  /* initialize trees */
{
	int  i;

	/* For i = 0 to N - 1, rson[i] and lson[i] will be the right and
	   left children of node i.  These nodes need not be initialized.
	   Also, dad[i] is the parent of node i.  These are initialized to
	   NIL (= N), which stands for 'not used.'
	   For i = 0 to 255, rson[N + i + 1] is the root of the tree
	   for strings that begin with character i.  These are initialized
	   to NIL.  Note there are 256 trees. */

	for (i = N + 1; i <= N + 256; i++) rson[i] = NIL;
	for (i = 0; i < N; i++) dad[i] = NIL;
}

static void InsertNode(int r)
	/* Inserts string of length F, text_buf[r..r+F-1], into one of the
	   trees (text_buf[r]'th tree) and returns the longest-match position
	   and length via the global variables match_position and match_length.
	   If match_length = F, then removes the old node in favor of the new
	   one, because the old one will be deleted sooner.
	   Note r plays double role, as tree node and position in buffer. */
{
	int  i, p, cmp;
	unsigned char  *key;

	cmp = 1;  key = &text_buf[r];  p = N + 1 + key[0];
	rson[r] = lson[r] = NIL;  match_length = 0;
	for ( ; ; ) 
	{
		if (cmp >= 0) 
		{
			if (rson[p] != NIL) 
				
					p = rson[p];

			else 
			{  
					rson[p] = r;
					
					dad[r] = p; 
					
					return;  
			}
		} else 
		{
			if (lson[p] != NIL) 
				p = lson[p];
			else 
			{  
					lson[p] = r;  
			
					dad[r] = p;  
					
					return;  
			}
		}
		for (i = 1; i < F; i++)

			if ((cmp = key[i] - text_buf[p + i]) != 0) 
				
				break;

		if (i > match_length)
		{
			match_position = p;
			if ((match_length = i) >= F)  
				break;
		}
	}
	dad[r] = dad[p]; 
	
	lson[r] = lson[p]; 

	rson[r] = rson[p];

	dad[lson[p]] = r; 

	dad[rson[p]] = r;

	if (rson[dad[p]] == p) 

		rson[dad[p]] = r;
	else                   
		lson[dad[p]] = r;

	dad[p] = NIL;  /* remove p */
}

static void DeleteNode(int p)  /* deletes node p from tree */
{
	int  q;
	
	if (dad[p] == NIL) return;  /* not in tree */
	if (rson[p] == NIL) q = lson[p];
	else if (lson[p] == NIL) q = rson[p];
	else {
		q = lson[p];
		if (rson[q] != NIL) {
			do {  q = rson[q];  } while (rson[q] != NIL);
			rson[dad[q]] = lson[q];  dad[lson[q]] = dad[q];
			lson[q] = lson[p];  dad[lson[p]] = q;
		}
		rson[q] = rson[p];  dad[rson[p]] = q;
	}
	dad[q] = dad[p];
	if (rson[dad[p]] == p) rson[dad[p]] = q;  else lson[dad[p]] = q;
	dad[p] = NIL;
}

static int Encode( FILE * infile, FILE * outfile )
{
	int  i, c, len, r, s, last_match_length, code_buf_ptr, match_offset;
	unsigned char  code_buf[17], mask;
	
	codesize = 0;	/* initialize code size */
	InitTree();		/* initialize trees */
	code_buf[0] = 0;  /* code_buf[1..16] saves eight units of code, and
		code_buf[0] works as eight flags, "1" representing that the unit
		is an unencoded letter (1 byte), "0" a position-and-length pair
		(2 bytes).  Thus, eight units require at most 16 bytes of code. */
	code_buf_ptr = mask = 1;
	s = 0;  r = N - F;
	for (i = s; i < r; i++) text_buf[i] = 0;  /* Clear the buffer with
		any character that will appear often. */
	for (len = 0; len < F && (c = getc(infile)) != EOF; len++)
		text_buf[r + len] = c;  /* Read F bytes into the last F bytes of
			the buffer */
	if ((textsize = len) == 0) return 0;  /* text of size zero */
	for (i = 1; i <= F; i++) InsertNode(r - i);  /* Insert the F strings,
		each of which begins with one or more 'space' characters.  Note
		the order in which these strings are inserted.  This way,
		degenerate trees will be less likely to occur. */
	InsertNode(r);  /* Finally, insert the whole string just read.  The
		global variables match_length and match_position are set. */
	do {
		if (match_length > len) match_length = len;  /* match_length
			may be spuriously long near the end of text. */
		if (match_length <= THRESHOLD) {
			match_length = 1;  /* Not long enough match.  Send one byte. */
			code_buf[0] |= mask;  /* 'send one byte' flag */
			code_buf[code_buf_ptr++] = text_buf[r];  /* Send uncoded. */
		} else {
			// 使用线性缓冲，取消环形缓冲，以加快解码速度
			match_offset = ( ( r | 0x1000 ) - match_position ) & 0x0FFF;
			code_buf[code_buf_ptr++] = (unsigned char)( (match_offset >> 8)
			  | ((match_length - (THRESHOLD + 1)) << 4 ) );  /* Send position and
					length pair. Note match_length > THRESHOLD. */
			code_buf[code_buf_ptr++] = (unsigned char)( match_offset );
		}
		if ((mask <<= 1) == 0) {  /* Shift mask left one bit. */
			for (i = 0; i < code_buf_ptr; i++)  /* Send at most 8 units of */
				putc(code_buf[i], outfile);     /* code together */
			codesize += code_buf_ptr;
			code_buf[0] = 0;  code_buf_ptr = mask = 1;
		}
		last_match_length = match_length;
		for (i = 0; i < last_match_length &&
				(c = getc(infile)) != EOF; i++) {
			DeleteNode(s);		/* Delete old strings and */
			text_buf[s] = c;	/* read new bytes */
			if (s < F - 1) text_buf[s + N] = c;  /* If the position is
				near the end of buffer, extend the buffer to make
				string comparison easier. */
			s = (s + 1) & (N - 1);  r = (r + 1) & (N - 1);
				/* Since this is a ring buffer, increment the position
				   modulo N. */
			InsertNode(r);	/* Register the string in text_buf[r..r+F-1] */
		}
		textsize += i;
		while (i++ < last_match_length) {	/* After the end of text, */
			DeleteNode(s);					/* no need to read, but */
			s = (s + 1) & (N - 1);  r = (r + 1) & (N - 1);
			if (--len) InsertNode(r);		/* buffer may not be empty. */
		}
	} while (len > 0);	/* until length of string to be processed is zero */
	if (code_buf_ptr > 1) {		/* Send remaining code. */
		for (i = 0; i < code_buf_ptr; i++) putc(code_buf[i], outfile);
		codesize += code_buf_ptr;
	}
	
	return 1;
}

static unsigned long int Decode( unsigned char *pSrc,unsigned char *pDes ,int flag)
{
	unsigned int i, j, k, nFlag;
	unsigned char *pTail, *pBuf,*pos;
    unsigned long int   nSrcLen;//,nDesLen


	nSrcLen = ((*(pSrc+8))<<24) + ((*(pSrc+9))<<16) + ((*(pSrc+10))<<8) + *(pSrc+11);
	//nDesLen = ((*(pSrc+4))<<24) + ((*(pSrc+5))<<16) + ((*(pSrc+6))<<8) + *(pSrc+7);

    pos = pDes;	
	pSrc = pSrc + 12;

	nFlag = 0;
	pTail = pSrc + nSrcLen;
	while( pSrc < pTail )
	{
		nFlag >>= 1;
		if ( ( nFlag & 0x100 ) == 0 ) /*nFlag 0 未压缩 1  压缩 */
		{
			nFlag = 0xFF00 | ( *pSrc++ );
		}
		if ( nFlag & 0x01 )
		{
			*pDes++ = *pSrc++;
		}
		else
		{
			i = *pSrc++;
			j = *pSrc++;
			k = ( ( ( i & 0x0f ) << 8 ) + j );  ////坐标
			j = ( i >> 4 ) + THRESHOLD + 1;      //长度
			i = k;
			
			pBuf = pDes - i;
			for ( k=0; k<j; k++ ) 
			{
			    if((pBuf+k)<pos)
			        pDes[k] = 0;
			    else
			        pDes[k] = pBuf[k];
			}
			pDes += j;
		}
	}
//	if((pDes - pos) != nDesLen)/*比较解压后的长度*/
//	{
//        printf("Encode data package error\n");
//        return false;
//	}
//	return true;
	return (pDes - pos);
}
/*===========================================================================*/
/*================================LZSS.C=====================================*/


/********************************************************  
*函数名称: FileEncode()  
*功能描述: 压缩文件
*入口参数: 文件名  、flag=true时，在压缩文件头里添加4个字节byte(12-15)，
           保存一些信息，这里提取源文件的头四个字节。
*函数返回: 成功返回true，反之false   
*********************************************************/
static int  FileEncode(FILE *infile, FILE*outfile, int flag) 
{
	unsigned char buf[16];
//	unsigned char checksum = 0;
	unsigned char data = 0xff;
	unsigned char headlen = 12;

	if(!infile || !outfile)
		return 0;

	printf(">> Compress file...\n");
	printf("   Src file path --> %s\n", filename_in);
	
	rewind(infile);
	rewind(outfile);

	//预留12或16个字节的文件头信息
	memset(buf,0,16);
	if(flag)
		headlen = 16;
	if(fwrite(buf,1,headlen,outfile) != headlen)
	{
		return 0;
	}
	
	//进行压缩编码
	Encode(infile, outfile);

    
	//双字节对齐
	fseek(outfile,0,SEEK_END);
	if((ftell(outfile)%2)!=0)
	{
		fwrite(&data,1,1,outfile);
	}
	rewind(outfile);

	//添加文件头信息
	buf[0]	= 0x55;
	buf[1]	= 0xAA;
	buf[2]	= 0x5A;
	buf[3]	= 0xA5;
	buf[4]	= ( unsigned char )( textsize >> 24 );
	buf[5]	= ( unsigned char )( textsize >> 16 );
	buf[6]	= ( unsigned char )( textsize >> 8 );
	buf[7]	= ( unsigned char )( textsize );
	buf[8]	= ( unsigned char )( codesize >> 24 );
	buf[9]	= ( unsigned char )( codesize >> 16 );
	buf[10] = ( unsigned char )( codesize >> 8 );
	buf[11] = ( unsigned char )( codesize );

#if 0
	//add 2011-03-06,压缩gprs.bin，加4个字节的软件版本信息
	rewind(infile);
	buf[12]	= ( unsigned char )getc(infile);
	buf[13]	= ( unsigned char )getc(infile);
	buf[14] = ( unsigned char )getc(infile);
	buf[15] = ( unsigned char )getc(infile);	
/*
    for(int i=0;i<12;i++)
    {
		checksum = checksum^buf[i];
	}
	buf[12] = checksum;
*/
#endif
	if(fwrite(buf,1,headlen,outfile) != headlen)
	{
		return 0;
	}
	codesize += headlen;
	
	printf("   Dst file path --> %s\n", filename_out);
 	printf("=> Compress file OK, rate is %.2f%% (%.2fM -> %.2fM).\n\n", (100.0*codesize/textsize), textsize/(1024*1024.0), codesize/(1024*1024.0));
	return 1;
}


/********************************************************  
*函数名称: CheckEncode()  
*功能描述: 检查文件是否已经压缩
*入口参数: 文件名  
*函数返回: 已压缩返回1，反之0，出错返回-1,-2    
*********************************************************/
static int CheckEncode( FILE *fp)
{
	unsigned char buf[12];
//	unsigned char checksum = 0;
//	unsigned char i = 0;
	unsigned long int  nSrcLen,nDesLen,nLen;

    return 1;

	rewind(fp);
	
	if(fread(buf,1,12,fp) != 12)
	{
		return 0;
	}

	rewind(fp);
	fseek(fp,0,SEEK_END);
    	nLen = ftell(fp); //压缩文件总长度
	rewind(fp);

	//查看文件头
	if(!((buf[0]==0x55)&&(buf[1]==0xAA)&&(buf[2]==0x5A)&&(buf[3]==0xA5)))
	{
		return 0;
	}

	//比较文件头信息里的源文件与目标文件的长度
	nSrcLen = ((*(buf+8))<<24) + ((*(buf+9))<<16) + ((*(buf+10))<<8) + *(buf+11);
	nDesLen = ((*(buf+4))<<24) + ((*(buf+5))<<16) + ((*(buf+6))<<8) + *(buf+7);
	if(nDesLen <= nSrcLen)
		return 0;


	//printf("size: nlen = %X, esize = %X\n",nLen,nSrcLen+12);

	if((nLen != nSrcLen+12) /*&& (nLen != nSrcLen+13) */&& (nLen != nSrcLen+16)/* && (nLen != nSrcLen+17)*/)
	{
		printf("Maybe the data of encode file error!\n");
		return 0;
	}

/* 文件头信息里不再用校验值
    //检查校验
    for(i=0;i<12;i++)
	{
		checksum = checksum^buf[i];
	}
	if(buf[12] != checksum)
	{
		return 0;
	}
*/	

	return 1;
}



/********************************************************  
*函数名称: FileDecode()  
*功能描述: 解压文件
*入口参数: 文件名  
*函数返回: 成功返回true，反之false     
*********************************************************/
//解压后的文件最大值为16M
#define FILE_MAX_LEN 0xffffff
static int FileDecode(FILE *infile, FILE*outfile, int flag) 
{
	unsigned char *pSrc,*pDes;
	unsigned char buf[12];
    unsigned long int  nLen, nDesLen;
    //unsigned long int  nSrcLen;
//	unsigned char c;
	
	if(!infile || !outfile)
		return 0;
	
	rewind(infile);
	rewind(outfile);	
	
	printf(">> Decompress file...\n");
	printf("   Src file path --> %s\n", filename_in);	
	
	if(CheckEncode(infile))
	{	
		rewind(infile);
		rewind(outfile);
		
		//取得压缩文件 文件头信息
		memset(buf,0,12);
		fread(buf,1,12,infile);

	//	nSrcLen = ((*(buf+8))<<24) + ((*(buf+9))<<16) + ((*(buf+10))<<8) + *(buf+11);
		nDesLen = ((*(buf+4))<<24) + ((*(buf+5))<<16) + ((*(buf+6))<<8) + *(buf+7);

		rewind(infile);
		fseek(infile,0,SEEK_END);
	    	nLen = ftell(infile); //压缩文件总长度
		rewind(infile);

		//分配内存，存放压缩数据
		pSrc = (unsigned char *)malloc(nLen);
		if(pSrc == NULL)
		{
			return 0;
		}
		//分配内存，存放解压数据
		pDes = (unsigned char *)malloc(nDesLen + 4096);
		if(pDes == NULL)
		{
			free(pSrc);
			return 0;
		}
		//读取压缩文件数据
		if(nLen != fread(pSrc,1,nLen,infile))
		{
			free(pSrc);
			free(pDes);
			return 0;
		}
		//进行解压
	    	nLen = Decode(pSrc,pDes,flag);

		if(nLen == nDesLen)
		{
			if(nDesLen != fwrite(pDes,1,nDesLen,outfile))
				nLen --; //为后面的比较用
		}

	   	 if(nLen != nDesLen)
		{
			printf("Data of encode file error!\n");
			return 0;
		}
		printf("   Dst file path --> %s\n", filename_out);
 		printf("=> Decompress file OK.\n\n");
	}
	else
	{
		/*文件已经不是压缩文件*/
		printf("   Src file is not a valid compress file!\n");		
	}

    	return 1;
}



/** @brief 显示命令行*/
static void usage()
{
	fprintf (stderr, "Usage: LZSS -e(-d) -i infile -o outfile\n");
	fprintf (stderr, "    -e --encode,		compress the file\n");
	fprintf (stderr, "    -d --decode,		decompress the file\n");		
	fprintf (stderr, "    -i --inputfile,		input file name\n");
	fprintf (stderr, "    -o --outputfile,		output file name\n");	
	fprintf (stderr, "    -h --help,			print this help.\n");
	exit(0);
}

static struct option long_options[] =
{
	{"help", 0, 0, 'h'},
	{"encode", 0, 0, 'e'},
	{"decode", 0, 0, 'd'},
	{"inputfile", 1, 0, 'i'},
	{"outputfile", 1, 0, 'o'},
	{0, 0, 0, 0}
};


/** @brief 主函数*/
int main (int argc, char **argv)
{
	int c;
	FILE* fpin = NULL;
	FILE *fpout = NULL;
	
	while(1)
	{
		int option_index = 0;
		
		c = getopt_long (argc, argv, "hedi:o:", long_options, &option_index);	
		if(c == -1) break;
		
		switch(c)
		{
			case 'h':
				usage();
				break;
			case 'e':
				if(operate_mode != -1)
				{
					fprintf(stderr,"WARNING: option -e -d appeared together.");
				}
				operate_mode = 1; 
					
				break;
			case 'd':
				if(operate_mode != -1)
				{
					fprintf(stderr,"WARNING: option -e -d appeared together.");
				}
				operate_mode = 0;
				break;				
			case 'i':
				strcpy(filename_in, optarg);
				if((fpin = fopen(optarg,"rb")) == NULL)
				{
					fprintf(stderr, "ERROR: Cannot open file `%s`\n",optarg);
					exit(-1);
				}
				break;
			case 'o':
				strcpy(filename_out, optarg);
				if((fpout = fopen(optarg,"wb")) == NULL)
				{
					fprintf(stderr, "ERROR: Cannot open file `%s`\n",optarg);
					exit(-1);
				}
				break;				
			default:
				exit(-1);
				break;
		}		
	}	

	if(fpin && fpout && operate_mode == 1)
	{
		if(!FileEncode(fpin, fpout, 0))
			printf("=> Compress file err !!!!!!!!!\n\n");
	}
	else if(fpin && fpout && operate_mode == 0)
	{
		if(!FileDecode(fpin, fpout, 0))
			printf("=> Decompress file err !!!!!!!!!\n\n");
	}

	if(fpin)fclose(fpin);
	if(fpout)fclose(fpout);
	
	return 0;
}


