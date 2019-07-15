/*************************************************************************************************

File Name      :  cdca_fun.h

Description    :  

Copyright(C)   :  Haier_IC 2012.1

Project Group  :  CA

Author(s)      :  hourn

Notes          :  

History        :

	Version    Date        	Author(s)      Description         Referrence

	1.0        2012-02-01     hourn          created              ---

**************************************************************************************************/

/************************************************************************************************/
/***************************************Includes*************************************************/
/************************************************************************************************/

#ifndef _HRCA_BURNOTP_H_
#define _HRCA_BURNOTP_H_

#include <stdint.h>


/************************************End of Includes*********************************************/

/*****************************CA public function*****************************************/
extern void ca_byte_exchange_to_otp(uint8_t *inbit, uint8_t *outbit, uint8_t len);
extern int32_t HRCA_BurnOtpInfoByUsb(void);
extern int32_t HRCA_BurnOtpInfoBySerialPort(uint8_t *potp, uint16_t len);
extern int32_t HRABVCA_BurnOtp_OtpInfo(uint8_t* otpinfo, uint16_t len);
extern int32_t HRUNITENDCA_BurnOtp_OtpInfo(uint8_t* otpinfo, uint16_t len);
extern int32_t HRTHTFCA_BurnOtp_OtpInfo(uint8_t* otpinfo, uint16_t len);
#endif


