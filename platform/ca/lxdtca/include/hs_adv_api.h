
#ifndef __HS_ADV_API_H__
#define __HS_ADV_API_H__

#ifdef  __cplusplus
extern "C" {
#endif

typedef char    INT8;  /**< 8 bits, bit 7 is the signed bit */
typedef short    INT16; /**< 16 bits, bit 15 is the signed bit */
typedef int     INT32;  /**< 32 bits, bit 31 is the signed bit */
typedef unsigned char     BOL;  /**< 32 bits, bit 31 is the signed bit */
typedef  unsigned char   UINT8;  /**< 8 bits */
typedef  unsigned short   UINT16;/**< 16 bits */
typedef unsigned long    UINT32;  /**< 32 bits */
typedef unsigned long long    UINT64; /**< 64 bits */
#define THREAD_SIZE_HSAD (1024*5)

#define ADTRUE        1

#define ADFALSE        0

#define Section_Size  (4096)

#ifndef	NULL
#define	NULL								0
#endif

#define Show_Logo_Buff (100000)

typedef enum
{
	AD_LOGO = 0xA0,
	AD_VOL,
	AD_MENU,
	AD_BANNEL,
	AD_HANG,
	AD_ROLL_PIC,
	AD_ROLL_CHARACTER,
}AD_type;
/*
	广告系统初始化
	@priority: 广告任务的优先级
	@return: 0->success;1->failure
*/
extern UINT8 HSADSTB_Ad_Init(UINT8 priority);
/*
获取机顶盒的广告数据(section)
*/
extern UINT8 HSADSTB_Get_Stb_Data(UINT8 *data);

extern UINT8* HSADSTB_Get_Roll_Pic_Data(UINT16 service_id,UINT16 *display_start_x,UINT16 *display_start_y,UINT16 *display_end_x,UINT16 *display_end_y,UINT16 *speed,UINT8 *dis_time,UINT16 frequence);
/*获取滚动字幕的数据和相关属性*/
extern UINT8 * HSADSTB_Get_Roll_Character_Data(UINT16 service_id,UINT16 *speed,UINT32 *font_color,UINT32 *bg_color,UINT8 *dis_style,UINT8 *dis_time,UINT16 frequence);
/*获取音量广告，菜单广告 数据*/
extern UINT8 *HSADSTB_Get_Single_Data(UINT8 ad_type,UINT32 *data_len);
/*获取挂角图片数据*/
extern UINT8 * HSADSTB_Get_Hang_Data(UINT8 ad_type,UINT16 service_id,UINT8 *hang_style,UINT8 *dis_time,UINT16 frequence);
/*获取换台广告数据*/
extern UINT8 * HSADSTB_Get_Bannel_Data(UINT16 service_id,UINT16 frequence);

/*判断广告数据是否接收完毕*/
extern INT32 HSADSTB_Get_Status(void);
/*显示开机LOGO*/
extern BOL HSADSTB_Show_Logo(void);

/*------------------------以上接口是ADV提供给STB----------------------------------------*/

/*------------------------以下接口是STB提供给ADV----------------------------------------*/

/*该函数用于分配内存*/
extern void* HSSTBAD_Malloc(UINT32 u32BufSize);

/*该函数用于释放内存*/
extern void  HSSTBAD_Free(void* pBuf);

/*该函数用于对数组或者指针赋值*/
extern void  HSSTBAD_Memset(void* pDestBuf,UINT8 c,UINT32 u32Size);

/*该函数用于内存拷贝*/
extern void  HSSTBAD_Memcpy(void* pDestBuf,void* pSrcBuf,UINT32 u32Size);

/*该函数用于计算字符串长度函数*/
extern UINT16  HSSTBAD_Strlen(char* pString);

/*该函数用于输出打印信息*/
extern void HSSTBAD_Printf(const char * fmt,...);

/*该函数用于创建任务*/
extern BOL HSSTBAD_RegisterTask( const char * pu8Name, UINT8 u8Priority, void* pTaskFun,void* pParam, UINT16 nStackSize);

/*该函数 用于延迟*/
extern void HSSTBAD_Delay(INT32 time);

/*该函数用来初始化过滤器*/
extern INT32 HSSTBAD_Demux_GotPrivateData(UINT32 pid,UINT32 table_id);

/*该函数用来开启过滤器*/
extern void HSSTBAD_Demux_Start(void);

/*该函数用来停止过滤器*/
extern void HSSTBAD_Demux_Stop(void);

/*该函数用来改变机顶盒的系统时间*/
extern void HSSTBAD_Change_Stb_Time(INT32 year,INT32 month,INT32 day,INT32 hour,INT32 minute,INT32 second);

/*该函数用来获取机顶盒的系统时间*/
extern void HSSTBAD_Get_Stb_Time(INT32 *year,INT32 *month,INT32 *day,INT32 *hour,INT32 *minute,INT32 *second);

/*该函数用来将开机图片数据写入flash中*/

extern UINT32 HSSTBAD_Write_Logo2flash(UINT8 *data,UINT32 logo_len,UINT8 logo_ver,UINT8 logo_discmd);

/*该函数用来将开机图片数据从flash中读出*/

extern UINT32 HSSTBAD_Read_Logo2flash(UINT8 *data,UINT8 *logo_ver,UINT8 *logo_discmd);
/*该函数用于机顶盒提供开机图片的显示接口*/

extern UINT32 HSSTBAD_Show_Logo(UINT8 *data,UINT32 logo_len);

#endif /* __HS_AV_H__ */
