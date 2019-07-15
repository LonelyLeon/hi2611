/** @file
* @brief 配置文件管理
* @author 李臣
* @date 2013-09-16 李臣: 建立文件
*/
#ifndef __D_CONFIG_FILE_H
#define __D_CONFIG_FILE_H
#ifdef  __cplusplus
extern "C"
{
#endif

#include "dTypes.h"

/** @brief 配置文件管理初始化结构 */
typedef struct
{
    D_U8 *hw_data; /**< 硬件配置数据 */
    D_U16 hw_data_size; /**< 硬件配置数据大小 */
    D_U8 *sw_data; /**< 软件配置数据 */
    D_U16 sw_data_size; /**< 软件配置数据大小 */
}D_ConfigFileOpenParam;

/** @brief 配置文件管理初始化函数
* @param[in] OpenParam 初始化结构
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_conf_file_open(D_ConfigFileOpenParam *OpenParam) D_FUNCPOSTFIT;

/** @brief 配置文件管理释放
* @return 成功返回D_OK,失败返回D_ERR
*/
D_Result d_conf_file_close(void) D_FUNCPOSTFIT;

/** @brief 配置文件管理搜索tag
* @param[in] tag 描述符8位
* @param[out] length 返回tag载荷数据长度
* @return 成功返回载荷数据指针,失败返回NULL
*/
void* d_conf_file_search_tag(D_U8 tag, D_U16 *length) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif
#endif

