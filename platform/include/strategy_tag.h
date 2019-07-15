

/** @file
* @brief ����Ƶ�豸����
* @author ����
* @date 2005-5-18 ����: �����ļ�
*   @date 2005-8-24 ����: �豸��������ǰ���豸ID��Ա
* @date 2006-8-2 shanzs:
        ����D_VidPicParam�ṹ
        ����D_VidPicRatio�ṹ
        ����D_VidRatioType����
        ����d_av_set_pic_param����
        ����d_av_set_pic_ratio����
*/

#ifndef _D_STRATEGY_H_
#define _D_STRATEGY_H_
/*tag*/
#define TAG_RESERVED 0x00
#define TAG_SNYC_DELAY 0x01
#define TAG_SYNC_SRC_SEL 0x02
#define TAG_UNCHANGE_PCR_DELAY 0x03
#define TAG_UNCHANGE_SYNC_SRC 0x04
#define TAG_MAX_DELAY 0x05
#define TAG_VP_ADJUST_TH0_OFFSET 0x06
#define TAG_PCR_SYNC_VP_ADJUST_TH1 0x07
#define TAG_APTS_SYNC_VP_ADJUST_TH1 0x08
#define TAG_VP_ADJUST_TH2 0x09
#define TAG_AUDIO_ADJUST_LOWER_LIMIT 0x0a
#define TAG_AUDIO_ADJUST_SUPERIOR_LIMIT 0x0b
#define TAG_PCM_UNDERFLOW_TH 0x0c
#define TAG_ACD_UNDERFLOW_TH 0x0d
#define TAG_WAIT_TYNC_TIMEOUT 0x0e
#define TAG_WAIT_VDELTA_LOWER_TIMEOUT 0x0f
#define TAG_WAIT_VDELTA_UPPER_TIMEOUT 0x10
#define TAG_PCM_UNDERFLOW_AAC_TH 0x11
#define TAG_ACD_UNDERFLOW_AAC_TH 0x12
#define TAG_PCM_UNDERFLOW_AC3_TH 0x13
#define TAG_ACD_UNDERFLOW_AC3_TH 0x14
#define TAG_PCM_UNDERFLOW_DRA_TH 0x15
#define TAG_ACD_UNDERFLOW_DRA_TH 0x16
#define TAG_AUDIO_DECRYPT_CTRL 0x17
#define TAG_AUDIO_DELAY_ADJUST 0x18


/*size*/
#define TAG_RESERVED_SIZE 4
#define TAG_SNYC_DELAY_SIZE 4
#define TAG_SYNC_SRC_SEL_SIZE 4
#define TAG_UNCHANGE_PCR_DELAY_SIZE 1
#define TAG_UNCHANGE_SYNC_SRC_SIZE 1
#define TAG_MAX_DELAY_SIZE 4
#define TAG_VP_ADJUST_TH0_OFFSET_SIZE 1
#define TAG_PCR_SYNC_VP_ADJUST_TH1_SIZE 1
#define TAG_APTS_SYNC_VP_ADJUST_TH1_SIZE 1
#define TAG_VP_ADJUST_TH2_SIZE 4
#define TAG_AUDIO_ADJUST_LOWER_LIMIT_SIZE 2
#define TAG_AUDIO_ADJUST_SUPERIOR_LIMIT_SIZE 2
#define TAG_PCM_UNDERFLOW_TH_SIZE 2
#define TAG_ACD_UNDERFLOW_TH_SIZE 2
#define TAG_WAIT_TYNC_TIMEOUT_SIZE 2
#define TAG_WAIT_VDELTA_LOWER_TIMEOUT_SIZE 2
#define TAG_WAIT_VDELTA_UPPER_TIMEOUT_SIZE 2
#define TAG_PCM_UNDERFLOW_AAC_TH_SIZE 2
#define TAG_ACD_UNDERFLOW_AAC_TH_SIZE 2
#define TAG_PCM_UNDERFLOW_AC3_TH_SIZE 2
#define TAG_ACD_UNDERFLOW_AC3_TH_SIZE 2
#define TAG_PCM_UNDERFLOW_DRA_TH_SIZE 2
#define TAG_ACD_UNDERFLOW_DRA_TH_SIZE 2
#define TAG_AUDIO_DECRYPT_CTRL_SIZE 1
#define TAG_AUDIO_DELAY_ADJUST_SIZE 4

/*payload�ο�ֵ*/
#define HR_TAG_RESERVEDE             0//Ԥ��
#define HR_INIT_SNYC_DELAY						INIT_SNYC_DELAY	//ͬ��delay�ĳ�ʼֵ
#define HR_INIT_SNYC_SRC_SEL					INIT_SNYC_SRC_SEL		//	0:PCR ��Ϊͬ��Դ;  1:��Ƶ��Ϊͬ��Դ;  2:��Ƶ��Ϊͬ��Դ(2830E��֧�ָ�ģʽ)�� 3��ȡ��ͬ������������Ƶ���ο�ͬ����׼�����в���
#define HR_UNCHANGE_PCR_DELAY                  UNCHANGE_PCR_DELAY  //0--delay ���ض�̬��Ӧ��1--delay�̶�Ϊ��ʼ��ֵ֮���ٸı䡣�ò�����sync_src_selΪPCRʱ��Ч
#define HR_UNCHANGE_SYNC_SRC                   UNCHANGE_SYNC_SRC //0--ͬ����ؿ����л�ͬ��Դѡ��1--ͬ����ز��л�ͬ��Դ
#define HR_VDELAY_MAX							VDELAY_MAX	// ����Ƶ�ӳٲ���������(0.711MS��λ)
#define HR_VP_ADJUST_TH0_OFFST				VP_ADJUST_TH0_OFFST		//��Ƶ����ͬ����������Ҫ���ص����ķ�Χ��ƫ��ֵ,һ��̶�Ϊ0��Ŀǰ���޵�������					
#define HR_APTS_SYNC_VP_ADJUST_TH1			APTS_SYNC_VP_ADJUST_TH1	// ��Ƶ��Ϊͬ��Դʱ����Ƶ����ͬ����������ֵ(0.711MS��λ)
#define HR_PCR_SYNC_VP_ADJUST_TH1			PCR_SYNC_VP_ADJUST_TH1	// PCR��Ϊͬ��Դʱ����Ƶ����ͬ����������ֵ(0.711MS��λ)
#define HR_VP_ADJUST_TH2					VP_ADJUST_TH2	//��ƵPTS��STC��ƫ�������ֵ�Ͳ�����(0.711MS��λ)
#define HR_DEFAULT_ADJUST_LOWER_LIMIT 		DEFAULT_ADJUST_LOWER_LIMIT		//��Ƶƫ�������ֵʱ��ʼ����
#define HR_DEFAULT_ADJUST_SUPERIOR_LIMIT 	DEFAULT_ADJUST_SUPERIOR_LIMIT	//��Ƶƫ�������ֵʱ���ٽ���ͬ������
#define HR_PCM_UNDERFLOW_TH				    PCM_UNDERFLOW_TH	//һ����Ƶ��PCM buffer�����ж���ֵ
#define HR_ASIZE_UNDERFLOW_TH				ASIZE_UNDERFLOW_TH	// һ����Ƶ��ACD buffer �����ж���ֵ
#define HR_SW_WAIT_VDELTA_LOWER_LIMIT		SW_WAIT_VDELTA_LOWER_LIMIT		//��̨��ͬ����vdeltaֵС�ڸ���ֵʱ�Ϳ��������ȴ�ѭ��
#define HR_SW_WAIT_VDELTA_UPPER_LIMIT		SW_WAIT_VDELTA_UPPER_LIMIT	//��̨��ͬ����vdeltaֵ���ڸ���ֵʱ�Ϳ��������ȴ�ѭ��
#define HR_PCM_UNDERFLOW_TH_AAC			    PCM_UNDERFLOW_TH_AAC	// AAC��Ƶ��PCM buffer�����ж���ֵ
#define HR_ASIZE_UNDERFLOW_TH_AAC			ASIZE_UNDERFLOW_TH_AAC	// AAC��Ƶ��ACD buffer �����ж���ֵ
#define HR_PCM_UNDERFLOW_TH_AC3			    PCM_UNDERFLOW_TH_AC3	//AC3��Ƶ��PCM buffer�����ж���ֵ
#define HR_ASIZE_UNDERFLOW_TH_AC3			ASIZE_UNDERFLOW_TH_AC3	// AC3��Ƶ��ACD buffer �����ж���ֵ
#define HR_PCM_UNDERFLOW_TH_DRA			    PCM_UNDERFLOW_TH_DRA	// DRA��Ƶ��PCM buffer�����ж���ֵ
#define HR_ASIZE_UNDERFLOW_TH_DRA			ASIZE_UNDERFLOW_TH_DRA	// DRA��Ƶ��ACD buffer �����ж���ֵ
#define HR_SW_WAIT_SYNC_TIMEOUT			    SW_WAIT_SYNC_TIMEOUT//��̨���̵�ͬ����ʱ����ʱ��
#define HR_AUDIO_DECRYPT_CTRL		     0 	// ES���ŵ������������ ,0--���ý��ţ�1--��һ�ַ�ʽ���ţ�2--�ڶ��ַ�ʽ��
#define HR_AUDIO_DELAY_ADJUST				 0 	//���ӡ����Ŀ����Ƶ�ӳٻ���ǰ���������У׼, 0--��ʾ����ҪУ׼����ֵ--��ʾ��Ƶ���ӳ٣���ֵ--��ʾ��Ƶ����ǰ����ֵ�ĵ�λΪMS
#endif


