
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
	���ϵͳ��ʼ��
	@priority: �����������ȼ�
	@return: 0->success;1->failure
*/
extern UINT8 HSADSTB_Ad_Init(UINT8 priority);
/*
��ȡ�����еĹ������(section)
*/
extern UINT8 HSADSTB_Get_Stb_Data(UINT8 *data);

extern UINT8* HSADSTB_Get_Roll_Pic_Data(UINT16 service_id,UINT16 *display_start_x,UINT16 *display_start_y,UINT16 *display_end_x,UINT16 *display_end_y,UINT16 *speed,UINT8 *dis_time,UINT16 frequence);
/*��ȡ������Ļ�����ݺ��������*/
extern UINT8 * HSADSTB_Get_Roll_Character_Data(UINT16 service_id,UINT16 *speed,UINT32 *font_color,UINT32 *bg_color,UINT8 *dis_style,UINT8 *dis_time,UINT16 frequence);
/*��ȡ������棬�˵���� ����*/
extern UINT8 *HSADSTB_Get_Single_Data(UINT8 ad_type,UINT32 *data_len);
/*��ȡ�ҽ�ͼƬ����*/
extern UINT8 * HSADSTB_Get_Hang_Data(UINT8 ad_type,UINT16 service_id,UINT8 *hang_style,UINT8 *dis_time,UINT16 frequence);
/*��ȡ��̨�������*/
extern UINT8 * HSADSTB_Get_Bannel_Data(UINT16 service_id,UINT16 frequence);

/*�жϹ�������Ƿ�������*/
extern INT32 HSADSTB_Get_Status(void);
/*��ʾ����LOGO*/
extern BOL HSADSTB_Show_Logo(void);

/*------------------------���Ͻӿ���ADV�ṩ��STB----------------------------------------*/

/*------------------------���½ӿ���STB�ṩ��ADV----------------------------------------*/

/*�ú������ڷ����ڴ�*/
extern void* HSSTBAD_Malloc(UINT32 u32BufSize);

/*�ú��������ͷ��ڴ�*/
extern void  HSSTBAD_Free(void* pBuf);

/*�ú������ڶ��������ָ�븳ֵ*/
extern void  HSSTBAD_Memset(void* pDestBuf,UINT8 c,UINT32 u32Size);

/*�ú��������ڴ濽��*/
extern void  HSSTBAD_Memcpy(void* pDestBuf,void* pSrcBuf,UINT32 u32Size);

/*�ú������ڼ����ַ������Ⱥ���*/
extern UINT16  HSSTBAD_Strlen(char* pString);

/*�ú������������ӡ��Ϣ*/
extern void HSSTBAD_Printf(const char * fmt,...);

/*�ú������ڴ�������*/
extern BOL HSSTBAD_RegisterTask( const char * pu8Name, UINT8 u8Priority, void* pTaskFun,void* pParam, UINT16 nStackSize);

/*�ú��� �����ӳ�*/
extern void HSSTBAD_Delay(INT32 time);

/*�ú���������ʼ��������*/
extern INT32 HSSTBAD_Demux_GotPrivateData(UINT32 pid,UINT32 table_id);

/*�ú�����������������*/
extern void HSSTBAD_Demux_Start(void);

/*�ú�������ֹͣ������*/
extern void HSSTBAD_Demux_Stop(void);

/*�ú��������ı�����е�ϵͳʱ��*/
extern void HSSTBAD_Change_Stb_Time(INT32 year,INT32 month,INT32 day,INT32 hour,INT32 minute,INT32 second);

/*�ú���������ȡ�����е�ϵͳʱ��*/
extern void HSSTBAD_Get_Stb_Time(INT32 *year,INT32 *month,INT32 *day,INT32 *hour,INT32 *minute,INT32 *second);

/*�ú�������������ͼƬ����д��flash��*/

extern UINT32 HSSTBAD_Write_Logo2flash(UINT8 *data,UINT32 logo_len,UINT8 logo_ver,UINT8 logo_discmd);

/*�ú�������������ͼƬ���ݴ�flash�ж���*/

extern UINT32 HSSTBAD_Read_Logo2flash(UINT8 *data,UINT8 *logo_ver,UINT8 *logo_discmd);
/*�ú������ڻ������ṩ����ͼƬ����ʾ�ӿ�*/

extern UINT32 HSSTBAD_Show_Logo(UINT8 *data,UINT32 logo_len);

#endif /* __HS_AV_H__ */
