#ifndef	__NVRAM_PART_CONFIG_HEADER__
#define	__NVRAM_PART_CONFIG_HEADER__

#ifdef	__cplusplus
extern "C" {
#endif

D_Result d_nvpartcfg_check_part_update(const D_NVPart *pi) D_FUNCPOSTFIT;
const D_NVPartCfg * d_nvpartcfg_get_config(D_Int *cfg_items) D_FUNCPOSTFIT;
D_Size d_loader_size(void) D_FUNCPOSTFIT;


#ifdef	__cpluplus
}
#endif



#endif	//__NVRAM_PART_CONFIG_HEADER__
