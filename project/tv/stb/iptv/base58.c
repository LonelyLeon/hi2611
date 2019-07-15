#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "_helper.h"

typedef signed char             int8_t; 
typedef short int               int16_t;
typedef int                     int32_t;

typedef unsigned char           uint8_t;
typedef unsigned short int      uint16_t;
typedef unsigned int            uint32_t;
typedef unsigned long int       uint64_t;

//编码表 
static const char b58digits_ordered[] = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz"; 

int b58enc(char *b58, size_t *b58sz, const void *data, size_t binsz) 
{	
	const uint8_t *bin = data; 
	int carry; 
	ssize_t i, j, high, zcount = 0; 
	uint8_t buf[12 * 1024] = {0}; 
	size_t size; 
	
	//计算待编码数据前面 0 的个数 
	while (zcount < (ssize_t)binsz && !bin[zcount]) 
		++zcount; 
	
	//计算存放转换数据所需要的数组的大小    138/100 --> log(256)/log(58) 
	size = (binsz - zcount) * 138 / 100 + 1; 
	
	memset(buf, 0, size); 
	
	//遍历待转换数据 
	for (i = zcount, high = size - 1; i < (ssize_t)binsz; ++i, high = j) 
	{ 
		//将数据从后往前依次存放 
		for (carry = bin[i], j = size - 1; (j > high) || carry; --j) 
		{ 
			carry += 256 * buf[j]; 
			buf[j] = carry % 58; 
			carry /= 58; 
		} 
	} 
	
	for (j = 0; j < (ssize_t)size && !buf[j]; ++j); 

	if (*b58sz <= zcount + size - j) 
	{ 
		*b58sz = zcount + size - j + 1; 
		return 0; 
	} 
	
	if (zcount) memset(b58, '1', zcount); 
	
	for (i = zcount; j < (ssize_t)size; ++i, ++j) 
	{
		b58[i] = b58digits_ordered[buf[j]];
	}
	
	b58[i] = '\0'; 
	*b58sz = i + 1; 
	
	return 1; 
}

static const int8_t b58digits_map[] = { 
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 
	-1, 0, 1, 2, 3, 4, 5, 6, 7, 8,-1,-1,-1,-1,-1,-1, 
	-1, 9,10,11,12,13,14,15,16,-1,17,18,19,20,21,-1, 
	22,23,24,25,26,27,28,29,30,31,32,-1,-1,-1,-1,-1, 
	-1,33,34,35,36,37,38,39,40,41,42,43,-1,44,45,46, 
	47,48,49,50,51,52,53,54,55,56,57,-1,-1,-1,-1,-1, 
}; 

int b58dec(void *bin, size_t *binszp, const char *b58) 
{ 
	size_t binsz = *binszp; 
	const unsigned char *b58u = (const unsigned char*)b58; 
	unsigned char *binu = bin; 
	
	uint32_t outi[12 * 1024] = {0}; 
	size_t outisz = (binsz + 3) / 4; 
	
	uint64_t t; 
	uint32_t c; 
	size_t i, j; 
	uint8_t bytesleft = binsz % 4; 
	uint32_t zeromask = bytesleft ? (0xffffffff << (bytesleft * 8)) : 0; 
	unsigned zerocount = 0; 
	size_t b58sz; 
	
	b58sz = strlen(b58); 
	
	memset(outi, 0, outisz * sizeof(*outi)); 
	
	// Leading zeros, just count 
	for (i = 0; i < b58sz && b58u[i] == '1'; ++i) 
		++zerocount; 
	
	for (; i < b58sz; ++i) 
	{ 
		if (b58u[i] & 0x80) 
			// High-bit set on invalid digit 
			return 0; 
		
		if (b58digits_map[b58u[i]] == -1) 
			// Invalid base58 digit 
			return 0; 
		
		c = (unsigned)b58digits_map[b58u[i]]; 
		
		for (j = outisz; j--; ) 
		{ 
			t = ((uint64_t)outi[j]) * 58 + c; 
			c = (t & 0x3f00000000) >> 32; 
			outi[j] = t & 0xffffffff; 
		} 
		
		if (c) 
			// Output number too big (carry to the next int32) 
			return 0; 
		
		if (outi[0] & zeromask) 
			// Output number too big (last int32 filled too far) 
			return 0; 
	} 
	
	j = 0; 
	
	switch (bytesleft) 
	{ 
		case 3: 
			*(binu++) = (outi[0] & 0xff0000) >> 16; 

		case 2: 
			*(binu++) = (outi[0] & 0xff00) >> 8; 

		case 1: 
			*(binu++) = (outi[0] & 0xff); 
			++j; 

		default: 
			break; 
	} 
	
	for (; j < outisz; ++j) 
	{ 
		*(binu++) = (outi[j] >> 0x18) & 0xff; 
		*(binu++) = (outi[j] >> 0x10) & 0xff; 
		*(binu++) = (outi[j] >> 8) & 0xff; 
		*(binu++) = (outi[j] >> 0) & 0xff; 
	} 
	
	// Count canonical base58 byte count binu = bin; 
	
	for (i = 0; i < binsz; ++i) 
	{ 
		if (binu[i]) 
		{ 
			if (zerocount > i) 
			{ 
				/* result too large */ 
				return 0; 
			} 
			break;
	   	} 
		--*binszp; 
	} 
	
	*binszp += zerocount; 
	return 1;
}

#if 0
void main()
{
	char test1[32];
	char tran[64];
	int len;

	len = strlen(tran);
	strcpy(test1, "006F0A6B3B7D");//uk586oacRVLuFrqq
	b58enc(tran, (size_t *)&len, (const void *) test1, strlen(test1));

	printf("%s: %s\n", test1, tran);

	memset(test1, 0, sizeof(test1));
	strcpy(test1, "053964718886");
	b58enc(tran, (size_t *)&len, (const void *) test1, strlen(test1));
	
	printf("%s: %s\n", test1, tran);
}
#endif
