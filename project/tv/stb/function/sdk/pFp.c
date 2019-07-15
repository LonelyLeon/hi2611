/** @file
* @brief Fp
*
* @author 李臣
* @date 2013-07-10 李臣: 建立文件
*/
#include "pFp.h"
#include "dRemote.h"
#include "dCBMan.h"
#include "dDebug.h"
#include "dSys.h"
#include "pCustomConfig.h"
#include "pMem.h"
#include "dMutex.h"
#include "dPowerOff.h"

#define P_FP_FILTER_KEYS_CNT (16)


#if defined(D_DEBUG) && defined(D_USE_TESTTOOL)
#include "dtesttool.h"
#include "dTime.h"
#include <stdlib.h>

static D_S32 auto_generate_key = 0;
#endif

#define REPEAT_FILTER_KEY(_k, _p)       ((((_k) != D_KEY_LEFT) \
                                        && ((_k) != D_KEY_RIGHT) \
                                        && ((_k) != D_KEY_UP) \
                                        && ((_k) != D_KEY_DOWN) \
                                        && ((_k) != D_KEY_PGUP) \
                                        && ((_k) != D_KEY_PGDOWN) \
                                        && ((_k) != D_KEY_VOLUME_PLUS) \
                                        && ((_k) != D_KEY_VOLUME_MINUS) \
                                        && ((_k) != D_KEY_PROGRAM_PLUS) \
                                        && ((_k) != D_KEY_PROGRAM_MINUS)) \
                                        && (_p)->key->repeat)


/** @brief 全局变量锁*/
static D_HMutex fp_lock_handle = D_INVALID_HANDLE;

/** @brief gui是否响应面板与遥控器*/
static D_Bool fp_enable = D_TRUE;

/** @brief gui响应面板与遥控器过滤个数与键值*/
static D_U16 fp_filter_keys_cnt = 0xFFFF;
static D_KeyCode fp_filter_keys[P_FP_FILTER_KEYS_CNT] = {0};

static D_U32        last_power_time, fp_poweroff_flag = 0;

static D_KeyCode curr_key = D_KEY_NUL;

/** @brief 取得当前的按键
* @param[in] param 参数
* @retval D_OK
*/
D_KeyCode
p_fp_get_curr_key(D_U32 param) D_FUNCPOSTFIT
{
    D_KeyCode key;
    d_mutex_lock(fp_lock_handle);    
    key = curr_key;
    curr_key = D_KEY_NUL;
    d_mutex_unlock(fp_lock_handle);
    return key;
}


/** @brief 设定面板遥控器使能与否
* @param[in] enable 使能与否
* @retval D_OK
*/
D_Result
p_fp_set_enable(D_Bool enable) D_FUNCPOSTFIT
{
    d_mutex_lock(fp_lock_handle);  
    fp_enable = enable;
    curr_key = D_KEY_NUL;
    d_mutex_unlock(fp_lock_handle);
    return D_OK;
}

/** @brief 设定面板遥控器过滤的按键值列表(列表之外的键值无效)
* @param[in] filter_keys 过滤键值表，暂定最多可过滤16个按键
* @param[in] keys_cnt 过滤键值表数目
(暂定最多为16，当为(D_U16)-1 或0xfffff时说明取消过滤操作)
* @retval D_OK
*/
D_Result
p_fp_set_filter_keys(D_KeyCode *filter_keys, D_U16 keys_cnt) D_FUNCPOSTFIT
{
    d_mutex_lock(fp_lock_handle);
    fp_filter_keys_cnt = (keys_cnt > P_FP_FILTER_KEYS_CNT) ? 0xFFFF : keys_cnt;
    if(filter_keys && fp_filter_keys_cnt <= P_FP_FILTER_KEYS_CNT)
    {
        memcpy(fp_filter_keys, filter_keys, sizeof(D_KeyCode) * fp_filter_keys_cnt);
    }
    d_mutex_unlock(fp_lock_handle);
    return D_OK;
}

/*检查按键是否有效*/
static D_Bool Key_is_valid(D_KeyCode key) D_FUNCPOSTFIT
{
    D_Bool ret = D_TRUE;
    D_U32 idx;

    d_mutex_lock(fp_lock_handle);
    if(fp_filter_keys_cnt <= P_FP_FILTER_KEYS_CNT)
    {
        ret = D_FALSE;
        for(idx = 0; idx < fp_filter_keys_cnt; idx++)
        {
            if(key == fp_filter_keys[idx])
            {
                ret = D_TRUE;
                break;
            }
        }
    }
    d_mutex_unlock(fp_lock_handle);
    return ret;
}

static D_Result Key_Remap(D_RemoteMapHookParam *KeyParam) D_FUNCPOSTFIT
{
    D_Int i;
    D_KeyCode key = D_KEY_NUL;
    P_CustomIrConfig *ir = CUSTOM_CONFIG.ir;
    P_CustomIrKey *source_key;

    D_DUMP("KeyHook::[%02X][%04X][%04X][%d]\n",
    KeyParam->key->guid_code,
    KeyParam->key->machine_code,
    KeyParam->key->source_code,
    KeyParam->key->repeat);

    for(i = 0; i < 4; i ++)
    {
        if((KeyParam->key->guid_code == ir[i].guid_code) \
        && (KeyParam->key->machine_code == ir[i].machine_code))
        {
            for(source_key = ir[i].keys; source_key && (source_key->source_code != 0xFFFF); source_key ++)
            {
                if(source_key->source_code == KeyParam->key->source_code)
                {
                    key = source_key->mapped_key;
                    break;
                }
            }

            if(key != D_KEY_NUL)
                break;
        }
    }

    if((key == D_KEY_NUL) || REPEAT_FILTER_KEY(key, KeyParam))
        return D_ERR;

    if(D_FALSE == Key_is_valid(key))
        return D_ERR;

    if(fp_enable)
    {
        KeyParam->mapped_key = key;
    }

    d_mutex_lock(fp_lock_handle);
    curr_key = key;
    d_mutex_unlock(fp_lock_handle);

    return D_OK;
}

static void ir_remap_cb(D_U32 cb_id, D_Handle obj, D_Ptr obj_data, D_Ptr cb_data) D_FUNCPOSTFIT
{
    D_RemoteMapHookParam *HookParam = (D_RemoteMapHookParam*)obj_data;
    Key_Remap(HookParam);
}

static void fp_remap_cb(D_U32 cb_id, D_Handle obj, D_Ptr obj_data, D_Ptr cb_data) D_FUNCPOSTFIT
{
    D_FPMapHookParam *FPMapHookParam = (D_FPMapHookParam*)obj_data;
    P_CustomIrKey *source_key;
    D_FPKey key = FPMapHookParam->source_code;
    D_KeyCode mapped_key = D_KEY_NUL;
    static D_FPKey last_key = 0;
    static D_U32 last_key_time = 0;


    if((last_key != key) || (d_sys_get_time() - last_key_time > 200))
    {
        for(source_key = CUSTOM_CONFIG.fp.keys; source_key && (source_key->source_code != 0xFFFF); source_key ++)
        {
            if(source_key->source_code == key)
            {
                mapped_key = source_key->mapped_key;
                break;
            }
        }

        if(mapped_key != D_KEY_NUL)
        {
            if(fp_enable)
            {
                FPMapHookParam->mapped_key = mapped_key;
            }
            last_key = key;
            last_key_time = d_sys_get_time();

            D_DUMP("FPHook::[%d] -> [0x%02X]\n", key, mapped_key);

            d_mutex_lock(fp_lock_handle);
            curr_key = mapped_key;
            d_mutex_unlock(fp_lock_handle);
        }
    }
}

static void user_generate_key_cb(D_U32 cb_id, D_Handle obj, D_Ptr obj_data, D_Ptr cb_data) D_FUNCPOSTFIT
{
#if defined(D_DEBUG) && defined(D_USE_TESTTOOL)
    if(obj_data && auto_generate_key)
    {
        D_KeyCode *k = (D_KeyCode*)obj_data;

        *k = (D_KeyCode)(rand() % D_KEY_DEADLINE);
    }
#endif
}
/*通过待机芯片查询，前面板待机键是否被按下*/
static void poweroff_key_check(D_U32 cb_id, D_Handle obj, D_Ptr obj_data, D_Ptr cb_data)
{
    D_KeyCode *k = (D_KeyCode*)obj_data;
    D_U8 state_mcu_rcv;

    if(fp_poweroff_flag > 50) //连续50次检测待机MCU没有回应，认为没有焊接待机芯片
    {
        return ;
    }

    if(d_sys_get_time() - last_power_time > 1000)
    {
//      state_mcu_rcv = d_fp_power_off();
        if(state_mcu_rcv == 4)
        {
            *k = D_KEY_PNL_POWER; // @/@*$ 0x0E前面板POWER键$*@/@
            fp_poweroff_flag = 0;
        }
        else if(state_mcu_rcv == 5)
        {
            fp_poweroff_flag++;
        }
        else
        {
            state_mcu_rcv = 0;
        }
        last_power_time = d_sys_get_time();
    }
}
#if defined(D_DEBUG) && defined(D_USE_TESTTOOL)
static D_Bool GenerateKeyRandom(parse_t *parse_p, char *result_p) D_FUNCPOSTFIT
{
    HRTST_GetInteger(parse_p, 0, (D_S32*)&auto_generate_key);

    return D_FALSE;
}
#endif

D_U8 p_get_remote_key(D_KeyCode key, P_POWERKEY* key_buf, D_U8 remote_size)D_FUNCPOSTFIT
{
    D_Int i, j = 0;
    P_CustomIrConfig *ir = CUSTOM_CONFIG.ir;
    P_CustomIrKey *source_key;



    for(i = 0; i < 4; i ++)
    {
        for(source_key = ir[i].keys; source_key && (source_key->source_code != 0xFFFF); source_key ++)
        {
            if(source_key->mapped_key == key )
            {
                key_buf->guid_code = ir[i].guid_code;
                key_buf->machine_code = ir[i].machine_code;
                key_buf->key = source_key->source_code;
                key_buf++;
                j++;
                break;
            }
        }

        if(j >= remote_size)
            break;

    }

    return j;
}

D_U8 p_get_multiple_remote_key(D_KeyCode key1, D_KeyCode key2,  P_POWERKEY* key_buf, D_U8 remote_size)D_FUNCPOSTFIT
{
    D_Int i, j = 0;
    P_CustomIrConfig *ir = CUSTOM_CONFIG.ir;
    P_CustomIrKey *source_key;



    for(i = 0; i < 4; i ++)
    {
        for(source_key = ir[i].keys; source_key && (source_key->source_code != 0xFFFF); source_key ++)
        {
            if(source_key->mapped_key == key1 )
            {
                key_buf->guid_code = ir[i].guid_code;
                key_buf->machine_code = ir[i].machine_code;
                key_buf->key = source_key->source_code;
                key_buf++;
		j++;
                break;
            }
        }

        for(source_key = ir[i].keys; source_key && (source_key->source_code != 0xFFFF); source_key ++)
        {
            if(source_key->mapped_key == key2 )
            {
                key_buf->guid_code = ir[i].guid_code;
                key_buf->machine_code = ir[i].machine_code;
                key_buf->key = source_key->source_code;
                key_buf++;
		j++;
                break;
            }
        }

        if(j >= remote_size)
            break;

    }

    return j;
}


D_Bool p_ir_had_value(D_Int idx, D_U8 guid_code, D_U16 machine_code, P_CustomIrKey *keys)
{
    D_Int i;
    D_Bool ret = D_FALSE;
    for(i = 0; i < idx; i++)
    {
        if(g_custom_config.ir[i].guid_code == guid_code && g_custom_config.ir[i].machine_code == machine_code)
        {
            PROJECT_FREE(g_custom_config.ir[i].keys);//释放原来的空间
            g_custom_config.ir[i].keys = keys;
            ret = D_TRUE;
            break;
        }
    }
    return ret;
}
D_Result p_fp_init(void) D_FUNCPOSTFIT
{
    D_U8 * payload, i;
    D_U16 len;
    P_CustomIrKey *keys;
	
#ifdef D_TV_PEOJECT_TOUYY
	d_fp_set_rckey_mode(1);
#endif	
    d_fp_open_ex();

    payload = d_conf_file_search_tag(CUSTOM_CONFIG_TAG_FP, &len);
    if(payload && (len >= 23))
    {
        payload += 23;
        len -= 23;

        keys = (P_CustomIrKey*)PROJECT_ALLOC((len / 2 + 1) * sizeof(P_CustomIrKey));
        if(keys == NULL)
        {
            D_ERROR("Can not alloc mem for custom config!\n");
            return D_ERR;
        }

        i = 0;
        while(len >= 2)
        {
            keys[i].source_code = payload[0];
            keys[i].mapped_key = (D_KeyCode)payload[1];

            len -= 2;
            payload += 2;
            i ++;
        }

        keys[i].source_code = 0xFFFF;
        keys[i].mapped_key = D_KEY_DEADLINE;

        CUSTOM_CONFIG.fp.keys = keys;
    }
	else if(payload && (len >= 3))
	{
        payload += 3;
        len -= 3;

        keys = (P_CustomIrKey*)PROJECT_ALLOC((len / 2 + 1) * sizeof(P_CustomIrKey));
        if(keys == NULL)
        {
            D_ERROR("Can not alloc mem for custom config!\n");
            return D_ERR;
        }

        i = 0;
        while(len >= 2)
        {
            keys[i].source_code = payload[0];
            keys[i].mapped_key = (D_KeyCode)payload[1];

            len -= 2;
            payload += 2;
            i ++;
        }

        keys[i].source_code = 0xFFFF;
        keys[i].mapped_key = D_KEY_DEADLINE;

        CUSTOM_CONFIG.fp.keys = keys;
    }

    d_remote_open_ex();

    /* IR1 */
    payload = d_conf_file_search_tag(CUSTOM_CONFIG_TAG_IR, &len);
    if(payload && (len >= 6))
    {
        D_U8 guid_code;
        D_U16 machine_code;

        guid_code = payload[0];
        machine_code = d_make_u16(payload[1], payload[2]);

        len -= 3;
        payload += 3;

        keys = (P_CustomIrKey*)PROJECT_ALLOC((len / 3 + 1) * sizeof(P_CustomIrKey));
        if(keys == NULL)
        {
            D_ERROR("Can not alloc mem for custom config!\n");
            return;
        }

        i = 0;
        while(len >= 3)
        {
            keys[i].source_code = d_make_u16(payload[0], payload[1]);
            keys[i].mapped_key = (D_KeyCode)payload[2];

            len -= 3;
            payload += 3;
            i ++;
        }

        keys[i].source_code = 0xFFFF;
        keys[i].mapped_key = D_KEY_DEADLINE;

        g_custom_config.ir[0].guid_code = guid_code;
        g_custom_config.ir[0].machine_code = machine_code;
        g_custom_config.ir[0].keys = keys;
    }

    /* IR2 */
    payload = d_conf_file_search_tag(CUSTOM_CONFIG_TAG_IR2, &len);
    if(payload && (len >= 6))
    {
        D_U8 guid_code;
        D_U16 machine_code;
        P_CustomIrKey *keys;

        guid_code = payload[0];
        machine_code = d_make_u16(payload[1], payload[2]);

        len -= 3;
        payload += 3;

        keys = (P_CustomIrKey*)PROJECT_ALLOC((len / 3 + 1) * sizeof(P_CustomIrKey));
        if(keys == NULL)
        {
            D_ERROR("Can not alloc mem for custom config!\n");
            return D_ERR;
        }

        i = 0;
        while(len >= 3)
        {
            keys[i].source_code = d_make_u16(payload[0], payload[1]);
            keys[i].mapped_key = (D_KeyCode)payload[2];

            len -= 3;
            payload += 3;
            i ++;
        }

        keys[i].source_code = 0xFFFF;
        keys[i].mapped_key = D_KEY_DEADLINE;

        g_custom_config.ir[1].guid_code = guid_code;
        g_custom_config.ir[1].machine_code = machine_code;
        g_custom_config.ir[1].keys = keys;
        if(p_ir_had_value(1, guid_code, machine_code, keys)) //如果该遥控器已经在之前的配置中存在，则此遥控器覆盖之前填过的值，将此项赋值为空。
            g_custom_config.ir[1].keys = NULL;
    }

    /* IR2 */
    payload = d_conf_file_search_tag(CUSTOM_CONFIG_TAG_IR3, &len);
    if(payload && (len >= 6))
    {
        D_U8 guid_code;
        D_U16 machine_code;
        P_CustomIrKey *keys;

        guid_code = payload[0];
        machine_code = d_make_u16(payload[1], payload[2]);

        len -= 3;
        payload += 3;

        keys = (P_CustomIrKey*)PROJECT_ALLOC((len / 3 + 1) * sizeof(P_CustomIrKey));
        if(keys == NULL)
        {
            D_ERROR("Can not alloc mem for custom config!\n");
            return D_ERR;
        }

        i = 0;
        while(len >= 3)
        {
            keys[i].source_code = d_make_u16(payload[0], payload[1]);
            keys[i].mapped_key = (D_KeyCode)payload[2];

            len -= 3;
            payload += 3;
            i ++;
        }

        keys[i].source_code = 0xFFFF;
        keys[i].mapped_key = D_KEY_DEADLINE;

        g_custom_config.ir[2].guid_code = guid_code;
        g_custom_config.ir[2].machine_code = machine_code;
        g_custom_config.ir[2].keys = keys;
        if(p_ir_had_value(2, guid_code, machine_code, keys)) //如果该遥控器已经在之前的配置中存在，则此遥控器覆盖之前填过的值，将此项赋值为空。
            g_custom_config.ir[2].keys = NULL;
    }

    d_cbman_subscribe(PL_GUI_IR_REMAP, D_INVALID_HANDLE, ir_remap_cb, NULL);
    d_cbman_subscribe(PL_GUI_FP_REMAP, D_INVALID_HANDLE, fp_remap_cb, NULL);
    d_cbman_subscribe(PL_GUI_GENERATE_USER_KEY, D_INVALID_HANDLE, user_generate_key_cb, NULL);
    /***检测前面板待机键**/
    d_cbman_subscribe(PL_GUI_GENERATE_USER_KEY, D_INVALID_HANDLE, poweroff_key_check, NULL);
#if defined(D_DEBUG) && defined(D_USE_TESTTOOL)
    HRTST_RegisterCommand("KEY", GenerateKeyRandom, "Generate random key");
    srand(d_time_get_time());
#endif
    fp_lock_handle = d_mutex_create (NULL);
    if(fp_lock_handle == D_INVALID_HANDLE)
    {
        return D_ERR;
    }
    D_DUMP("p_fp_init Ok.\n");

    return D_OK;
}

