/** @file
* @brief Tuner���ݽṹ
* @author ��ѫ
* @date 2005-9-28 ��ѫ: �����ļ�
*/

#ifndef _D_FENDINTERNAL_H_
#define _D_FENDINTERNAL_H_

#include "dTypes.h"
#include "dFend.h"
#include "dMutex.h"

#ifdef  __cplusplus
extern "C"
{
#endif


#define TUNER_FE_HAIER_IC///////////////////
#ifndef TUNER_FE_TYPE
#define TUNER_FE_TYPE  TUNER_FE_HAIER_IC
#endif

struct datatype
{
    D_S8 address;
    D_S8 dataa;
};

typedef enum
{
    IDLE,
    ACQUISITION,
    MONITORING
} TunerState_t;

typedef struct SignalPower_e  
{   
    D_U8 PowerFul;  
    D_U8 dBmFul;  
} SignalPower_t;

typedef struct DVBCTRANS_T
{
  D_S32 Frequency;
  D_U32 SymbolRate;
  D_U8 QAM;
  D_S16 SweepRate;
  D_S16 CarrierOffset;
  D_U8 SpectrumInversion;
} DVBCTRANS_t;

/*add params*/
typedef struct _D_TunerOp	D_TunerOp;
typedef struct _D_TunerSet      D_TunerSet;

typedef struct {
	const		 D_TunerOp	*op;
	D_ID		 iic_id;
	D_HIIC		 hiic;
	D_FEndType	 type;
    
       DemodType_t demod;   
	D_HMutex     tunerhmutex;
	D_U8         used;
	union
	{
		struct {
                        D_U8         mode;                          //�ڲ���Ϊ0����ҵ�Ϊ1
                        D_U8         iic_addr;                     // �������߱�ʶ
                        D_U32       dvbc_base;               //�ڲ���ʱ��Ļ���ַ
                        D_U8         printf_en;                 //��ӡʹ��
                        D_U8        adc_clk_pll;           //0  // ADCʱ��ֱ�����Ծ���1:// ADCʱ������PLL��Ƶ
                        D_U16      xtalFreqKHz	;   
                        }demod3205;
		struct {
			D_U8         mode;                          //�ڲ���Ϊ0����ҵ�Ϊ1
                     D_U8         iic_addr;                     // �������߱�ʶ
                     D_U32       dvbc_base;               //�ڲ���ʱ��Ļ���ַ
                     D_U8         printf_en;	
             }demod3103;        
	}demodPara;	
       union
	{
		struct {
			DVBCTRANS_t  PParams;
			D_U8         byte[6];
			D_U8         TunerLock;
			D_U8         Lms2Factor;
			D_S32				 specinv;
		}tuner0297;
		struct {
			D_U8				 reg[0xE0];
		}sharp;
		struct {
		    DVBCTRANS_t  PParams;
			D_U8         byte[6];
			D_U8         TunerLock;
		}tda10023;
		void* hfend;
	}tunerPara;

}D_Tuner;


struct _D_TunerOp {

	D_Result (*init)(/*void*/D_Tuner *tuner)D_FUNCPOSTFIT;
	D_Result (*deinit)(D_Tuner *tuner)D_FUNCPOSTFIT;
	D_Result (*set_param) (D_Tuner *tuner, D_FEndParam *param, D_FEndFreq lnbfreq) D_FUNCPOSTFIT;
	D_Bool	 (*locked) (D_Tuner *tuner) D_FUNCPOSTFIT;
	D_Result (*get_status) (D_Tuner *tuner, D_FEndStatus *status) D_FUNCPOSTFIT;
	D_FEndBlindResult (*blind_scan)(D_Tuner *tuner, D_FEndBlindCmd blindcmd, D_FEndParam *param, D_FBlindParam *blindparam);			
	void (*set_diseqc)(D_Tuner *tuner, D_FEndDiSEqC cmd, D_F22KSTATE f22kstate, D_FEndPol pol);
	void(*set_22k)(D_Tuner *tuner, D_F22KSTATE f22kstate);
	void (*set_pol)(D_Tuner *tuner, D_FEndPol pol);
};
#ifdef  __cplusplus
}
#endif

#endif
