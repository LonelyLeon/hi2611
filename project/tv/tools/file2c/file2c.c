/** @file
* @brief 文件转化为C语言
* @author 龚克
* @date 2005-7-20 龚克: 建立文件
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

static FILE	*inp, *outp;
static int gen_mode = 0; /*文件生成模式:0 生成C源文件, 1 生成头文件*/
static char	*name = "file_data"; /*数据结构名*/

static void
gen_c ()
{
	int chr;
	long int cnt = 0;
	
	fprintf (outp, "#include \"dTypes.h\"\n\n");
	fprintf (outp, "unsigned char const D_FAR %s[] = {\n", name);
	
	while ((chr = fgetc (inp)) != EOF) {
		cnt ++;
		fprintf (outp, " 0x%02x,", (unsigned char) chr);
		if (!(cnt % 8))
			fprintf (outp, "\n");
	}
	
	fprintf (outp, "};\n");
}

static void
gen_h ()
{
	unsigned long pos;
	
	fseek (inp, 0, SEEK_END);
	pos = ftell (inp);
	
	fprintf (outp, "#ifndef _D_%s_H_\n", name);
	fprintf (outp, "#define _D_%s_H_\n\n", name);
	fprintf (outp, "#include \"dTypes.h\"\n\n");
	fprintf (outp, "#ifdef  __cplusplus\nextern \"C\"\n{\n#endif\n\n");
	fprintf (outp, "#define %s_size %ldl\n", name, pos);
	fprintf (outp, "extern unsigned char const D_FAR %s[];\n", name);
	fprintf (outp, "\n#ifdef __cplusplus\n}\n#endif\n\n#endif\n");
}

int
main (int argc, char **argv)
{
	int i = 0;
	int set_inp = 0;
	
	inp = stdin;
	outp = stdout;
	
	/*参数检查*/
	for (i = 1; i < argc; i ++) {
		if (argv[i]) {
			if (strcmp (argv[i], "-h") == 0) {
				gen_mode = 1;
			} else if (strcmp (argv[i], "-c") == 0) {
				gen_mode = 0;
			} else if (! set_inp) {
				set_inp = 1;
				inp = fopen (argv[i], "rb");
				if (! inp) {
					fprintf (stderr, "Cannot open input file \"%s\"\n", argv[i]);
					return 1;
				}
			} else {
				name = argv[i];
			}
		}
	}
	
	if (gen_mode == 0)
		gen_c ();
	else if (gen_mode == 1)
		gen_h ();
	
	return 0;
}
