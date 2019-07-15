//#include <stdio.h>
#include "dDebug.h"

#pragma alignvar (8)
unsigned short pmaddhwdata[] = {
0x0, 0x0, 0x0, 0x0,/* 该64位用来保存运算结果  */
0x1, 0x3, 0x5, 0x7,/* src1 = 0x0007 0005 0003 0001 */
0x2, 0x4, 0x6, 0x8/* src2 = 0x0008 0006 0004 0002 */
};

/*inline*/ void pmaddhw(unsigned short * const row)
{
#if 0
    asm volatile
        (
            ".set noreorder\n\t"
            "ldc1 $f0, %1\n\t" /* 从内存加载 64 位数据到 f0 */
            "ldc1 $f2, %2\n\t" /* f2 <-- SRC2 */
            "pmaddhw $f2, $f2, $f0\n\t" /* pmaddhw dest, src2, src1 */
            "sdc1 $f2, %0\n\t" /* 存储计算结果 */
            ".set reorder\n\t"
            ".set mips0\n\t"
            : "=m"(*row)
            : "m"(*(row+4)), "m"(*(row+8))
            : "$f0", "$f2", "memory"
        );
#else
	__asm(".word 0x27bdfff8");
	__asm(".word 0xafbe0004");
	__asm(".word 0x03a0f021");
	__asm(".word 0xafc40008");
	__asm(".word 0x8fc20008");
	__asm(".word 0x24440008");
	__asm(".word 0x8fc20008");
	__asm(".word 0x24430010");
	__asm(".word 0x8fc20008");
	__asm(".word 0xd4800000");
	__asm(".word 0xd4620000");
	__asm(".word 0x4b60108e");
	__asm(".word 0xf4420000");
	__asm(".word 0x03c0e821");
	__asm(".word 0x8fbe0004");
	__asm(".word 0x03e00008");
	__asm(".word 0x27bd0008");
	__asm(".word 0x00000000");
#endif
}

void pmaddhw_test()                                                                                                           
{
	unsigned int res[2];                                                                                                                    
	D_DUMP("src1: 0x%04x %04x %04x %04x\n\n", pmaddhwdata[7], pmaddhwdata[6], pmaddhwdata[5], pmaddhwdata[4]);                                       
	D_DUMP("src2: 0x%04x %04x %04x %04x\n", pmaddhwdata[11], pmaddhwdata[10], pmaddhwdata[9], pmaddhwdata[8]);
	res[0] = pmaddhwdata[6]*pmaddhwdata[10]+pmaddhwdata[7]*pmaddhwdata[11];
  res[1] = pmaddhwdata[4]*pmaddhwdata[8]+pmaddhwdata[5]*pmaddhwdata[9];                                       
	pmaddhw(pmaddhwdata);                                                                                                       
	D_DUMP("pmaddhw dest, src2, src1 result is: 0x%04x %04x %04x %04x\n\n", pmaddhwdata[3], pmaddhwdata[2], pmaddhwdata[1], pmaddhwdata[0]);
	if((res[0] == (pmaddhwdata[1]<<16)|pmaddhwdata[0]) && res[1] == (pmaddhwdata[3]<<16)|pmaddhwdata[2])
     D_DUMP("ok\n");
  else
     D_DUMP("wrong\n");
}

#if 0
int main()
{
	pmaddhw_test();
	while(1);	
}
#endif
