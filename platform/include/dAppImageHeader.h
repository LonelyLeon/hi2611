/** @file
* @brief app����ͷ����Ϣ
*
* ����loaderУ�������app
* @author �
* @date 2013-09-26 �: �����ļ�
*/
#ifndef __APP_IMAGE_HEADER_H__
#define __APP_IMAGE_HEADER_H__

#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"	

/*
 * Operating System Codes
 */
#define IH_OS_INVALID		0	/* Invalid OS	*/
#define IH_OS_OPENBSD		1	/* OpenBSD	*/
#define IH_OS_NETBSD		2	/* NetBSD	*/
#define IH_OS_FREEBSD		3	/* FreeBSD	*/
#define IH_OS_4_4BSD		4	/* 4.4BSD	*/
#define IH_OS_LINUX		5	/* Linux	*/
#define IH_OS_SVR4		6	/* SVR4		*/
#define IH_OS_ESIX		7	/* Esix		*/
#define IH_OS_SOLARIS		8	/* Solaris	*/
#define IH_OS_IRIX		9	/* Irix		*/
#define IH_OS_SCO		10	/* SCO		*/
#define IH_OS_DELL		11	/* Dell		*/
#define IH_OS_NCR		12	/* NCR		*/
#define IH_OS_LYNXOS		13	/* LynxOS	*/
#define IH_OS_VXWORKS		14	/* VxWorks	*/
#define IH_OS_PSOS		15	/* pSOS		*/
#define IH_OS_QNX		16	/* QNX		*/
#define IH_OS_U_BOOT		17	/* Firmware	*/
#define IH_OS_RTEMS		18	/* RTEMS	*/
#define IH_OS_ARTOS		19	/* ARTOS	*/
#define IH_OS_UNITY		20	/* Unity OS	*/
#define IH_OS_HROS      21  /* ����IC OS */

/*
 * CPU Architecture Codes (supported by Linux)
 */
#define IH_CPU_INVALID		0	/* Invalid CPU	*/
#define IH_CPU_ALPHA		1	/* Alpha	*/
#define IH_CPU_ARM		2	/* ARM		*/
#define IH_CPU_I386		3	/* Intel x86	*/
#define IH_CPU_IA64		4	/* IA64		*/
#define IH_CPU_MIPS		5	/* MIPS		*/
#define IH_CPU_MIPS64		6	/* MIPS	 64 Bit */
#define IH_CPU_PPC		7	/* PowerPC	*/
#define IH_CPU_S390		8	/* IBM S390	*/
#define IH_CPU_SH		9	/* SuperH	*/
#define IH_CPU_SPARC		10	/* Sparc	*/
#define IH_CPU_SPARC64		11	/* Sparc 64 Bit */
#define IH_CPU_M68K		12	/* M68K		*/
#define IH_CPU_NIOS		13	/* Nios-32	*/
#define IH_CPU_MICROBLAZE	14	/* MicroBlaze   */
#define IH_CPU_NIOS2		15	/* Nios-II	*/
#define IH_CPU_SH4	        16	/* SuperH SH-4  */
#define IH_CPU_SH64	        17	/* SuperH SH-5  */
#define IH_CPU_ST200	        18	/* STMicroelectronics ST200  */

/*
 * Image Types
 *
 * "Standalone Programs" are directly runnable in the environment
 *	provided by U-Boot; it is expected that (if they behave
 *	well) you can continue to work in U-Boot after return from
 *	the Standalone Program.
 * "OS Kernel Images" are usually images of some Embedded OS which
 *	will take over control completely. Usually these programs
 *	will install their own set of exception handlers, device
 *	drivers, set up the MMU, etc. - this means, that you cannot
 *	expect to re-enter U-Boot except by resetting the CPU.
 * "RAMDisk Images" are more or less just data blocks, and their
 *	parameters (address, size) are passed to an OS kernel that is
 *	being started.
 * "Multi-File Images" contain several images, typically an OS
 *	(Linux) kernel image and one or more data images like
 *	RAMDisks. This construct is useful for instance when you want
 *	to boot over the network using BOOTP etc., where the boot
 *	server provides just a single image file, but you want to get
 *	for instance an OS kernel and a RAMDisk image.
 *
 *	"Multi-File Images" start with a list of image sizes, each
 *	image size (in bytes) specified by an "uint32_t" in network
 *	byte order. This list is terminated by an "(uint32_t)0".
 *	Immediately after the terminating 0 follow the images, one by
 *	one, all aligned on "uint32_t" boundaries (size rounded up to
 *	a multiple of 4 bytes - except for the last file).
 *
 * "Firmware Images" are binary images containing firmware (like
 *	U-Boot or FPGA images) which usually will be programmed to
 *	flash memory.
 *
 * "Script files" are command sequences that will be executed by
 *	U-Boot's command interpreter; this feature is especially
 *	useful when you configure U-Boot to use a real shell (hush)
 *	as command interpreter (=> Shell Scripts).
 */

#define IH_TYPE_INVALID		0	/* Invalid Image		*/
#define IH_TYPE_STANDALONE	1	/* Standalone Program		*/
#define IH_TYPE_KERNEL		2	/* OS Kernel Image		*/
#define IH_TYPE_RAMDISK		3	/* RAMDisk Image		*/
#define IH_TYPE_MULTI		4	/* Multi-File Image		*/
#define IH_TYPE_FIRMWARE	5	/* Firmware Image		*/
#define IH_TYPE_SCRIPT		6	/* Script file			*/
#define IH_TYPE_FILESYSTEM	7	/* Filesystem Image (any type)	*/

/*
 * Compression Types
 */
#define IH_COMP_NONE		0	/*  No	 Compression Used	*/
#define IH_COMP_GZIP		1	/* gzip	 Compression Used	*/
#define IH_COMP_BZIP2		2	/* bzip2 Compression Used	*/
#define IH_COMP_LZSS        3   /* LZSS */

#define IH_MAGIC	0x27051956	/* Image Magic Number		*/
#define IH_NMLEN		32	/* Image Name Length		*/
#define IH_RESERVED_LEN 688 /* ����688�ֽ� */
#define IH_SIGLEN   272     /* ǩ����С, 256+16 */

/*
 * all data in network byte order (aka natural aka bigendian)
 * sizeof(typedef struct image_header) = 1024
 */

typedef struct image_header {
	D_U32 ih_magic;	/* Image Header Magic Number	*/
	D_U32 ih_hcrc;	/* Image Header CRC Checksum	*/
	D_U32 ih_time;	/* Image Creation Timestamp	*/
	D_U32 ih_size;	/* Image Data Size		*/
	D_U32 ih_load;	/* Data	 Load  Address		*/
	D_U32 ih_ep;		/* Entry Point Address		*/
	D_U32 ih_dcrc;	/* Image Data CRC Checksum	*/
	D_U8 ih_os;		/* Operating System		*/
	D_U8 ih_arch;	/* CPU architecture		*/
	D_U8 ih_type;	/* Image Type			*/
	D_U8 ih_comp;	/* Compression Type		*/
    D_U8 ih_name[IH_NMLEN];	/* Image Name		*/
    D_U8 ih_reserved[IH_RESERVED_LEN]; /* ���� */
    D_U8 ih_signature[IH_SIGLEN];	/* ǩ��		*/
} image_header_t;

typedef struct image_header D_AppImageHeader;
typedef struct image_header D_LoaderImageHeader;

typedef struct _loader_info{
    D_U32 loader_curr_no;
    D_U32 loader_1_addr;
    D_U32 loader_2_addr;
    D_U32 loader_size;
    D_U32 loader_replace;
}_loader_info_t;

typedef struct _loader_info D_LoaderInfo;

#ifdef  __cplusplus
}
#endif
#endif
