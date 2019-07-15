

/** @file
* @brief 音视频设备操作
* @author 龚克
* @date 2005-5-18 龚克: 建立文件
*   @date 2005-8-24 龚克: 设备属性增加前端设备ID成员
* @date 2006-8-2 shanzs:
        增加D_VidPicParam结构
        增加D_VidPicRatio结构
        增加D_VidRatioType类型
        增加d_av_set_pic_param函数
        增加d_av_set_pic_ratio函数
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

/*payload参考值*/
#define HR_TAG_RESERVEDE             0//预留
#define HR_INIT_SNYC_DELAY						INIT_SNYC_DELAY	//同步delay的初始值
#define HR_INIT_SNYC_SRC_SEL					INIT_SNYC_SRC_SEL		//	0:PCR 作为同步源;  1:音频作为同步源;  2:视频作为同步源(2830E不支持该模式)； 3：取消同步调整，音视频不参考同步基准，自行播放
#define HR_UNCHANGE_PCR_DELAY                  UNCHANGE_PCR_DELAY  //0--delay 随监控动态适应，1--delay固定为初始化值之后不再改变。该参数在sync_src_sel为PCR时有效
#define HR_UNCHANGE_SYNC_SRC                   UNCHANGE_SYNC_SRC //0--同步监控可以切换同步源选择，1--同步监控不切换同步源
#define HR_VDELAY_MAX							VDELAY_MAX	// 音视频延迟参数的上限(0.711MS单位)
#define HR_VP_ADJUST_TH0_OFFST				VP_ADJUST_TH0_OFFST		//视频触发同步调整后需要调回的中心范围的偏差值,一般固定为0，目前暂无调整需求					
#define HR_APTS_SYNC_VP_ADJUST_TH1			APTS_SYNC_VP_ADJUST_TH1	// 音频作为同步源时，视频触发同步调整的阈值(0.711MS单位)
#define HR_PCR_SYNC_VP_ADJUST_TH1			PCR_SYNC_VP_ADJUST_TH1	// PCR作为同步源时，视频触发同步调整的阈值(0.711MS单位)
#define HR_VP_ADJUST_TH2					VP_ADJUST_TH2	//视频PTS与STC的偏差超过此阈值就不调整(0.711MS单位)
#define HR_DEFAULT_ADJUST_LOWER_LIMIT 		DEFAULT_ADJUST_LOWER_LIMIT		//音频偏差超过该阈值时开始调整
#define HR_DEFAULT_ADJUST_SUPERIOR_LIMIT 	DEFAULT_ADJUST_SUPERIOR_LIMIT	//音频偏差超过该阈值时不再进行同步调整
#define HR_PCM_UNDERFLOW_TH				    PCM_UNDERFLOW_TH	//一般音频的PCM buffer下溢判定阈值
#define HR_ASIZE_UNDERFLOW_TH				ASIZE_UNDERFLOW_TH	// 一般音频的ACD buffer 下溢判定阈值
#define HR_SW_WAIT_VDELTA_LOWER_LIMIT		SW_WAIT_VDELTA_LOWER_LIMIT		//换台等同步的vdelta值小于该阈值时就可以跳出等待循环
#define HR_SW_WAIT_VDELTA_UPPER_LIMIT		SW_WAIT_VDELTA_UPPER_LIMIT	//换台等同步的vdelta值大于该阈值时就可以跳出等待循环
#define HR_PCM_UNDERFLOW_TH_AAC			    PCM_UNDERFLOW_TH_AAC	// AAC音频的PCM buffer下溢判定阈值
#define HR_ASIZE_UNDERFLOW_TH_AAC			ASIZE_UNDERFLOW_TH_AAC	// AAC音频的ACD buffer 下溢判定阈值
#define HR_PCM_UNDERFLOW_TH_AC3			    PCM_UNDERFLOW_TH_AC3	//AC3音频的PCM buffer下溢判定阈值
#define HR_ASIZE_UNDERFLOW_TH_AC3			ASIZE_UNDERFLOW_TH_AC3	// AC3音频的ACD buffer 下溢判定阈值
#define HR_PCM_UNDERFLOW_TH_DRA			    PCM_UNDERFLOW_TH_DRA	// DRA音频的PCM buffer下溢判定阈值
#define HR_ASIZE_UNDERFLOW_TH_DRA			ASIZE_UNDERFLOW_TH_DRA	// DRA音频的ACD buffer 下溢判定阈值
#define HR_SW_WAIT_SYNC_TIMEOUT			    SW_WAIT_SYNC_TIMEOUT//换台流程等同步超时跳出时间
#define HR_AUDIO_DECRYPT_CTRL		     0 	// ES解扰的情况进行配置 ,0--不用解扰，1--第一种方式解扰，2--第二种方式解
#define HR_AUDIO_DELAY_ADJUST				 0 	//针对印尼项目将音频延迟或提前的情况进行校准, 0--表示不需要校准，正值--表示音频被延迟，负值--表示音频被提前，数值的单位为MS
#endif


