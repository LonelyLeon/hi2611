/** @file
* @brief  main函数
* @author 李臣
* @date 2013-03-11  李臣: 建立文件
*/
#include "dTypes.h"

extern int project_main(int argc, char *argv[]) D_FUNCPOSTFIT;

/** @brief 标准C程序入口函数
* @param[in] argc 参数个数
* @param[in] argv 参数指针
* @return 错误代码
*/
int main(int argc, char *argv[]) D_FUNCPOSTFIT
{
	return project_main(argc, argv);
}
/*EOF*/
