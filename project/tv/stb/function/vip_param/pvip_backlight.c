/**@defgroup tv �����Զ���������ʵ��
*@{*/
/** @file
* @brief �����Զ���������ʵ��
* @author hegx
* @date 2015-10-17 hegx: �����ļ�
*/

#include <stdio.h>
#include <string.h>
#include "dSys.h"
#include "ptvConfig.h"

static D_HTask hTask_backlight = D_INVALID_HANDLE;
static D_U8 windos9_flag = 0;
static D_U8 check_times = 0;
static D_U8 backlight_gd = 0;
static D_U8 needcheck = 0;//��Ҫ�仯
static D_U8 needbacklight = 0;//Ŀ�걳��ֵ
static D_U8 curbacklight = 0;//��ǰ����ֵ
static D_U8 lastbacklight_gd = 0;
static D_VidInput lastinput = D_VID_IUTPUT_MAX;

#define backlight_ex_num    17//��Ч����ʱ����Ҫ�����ı���ֵ
#define Detector_backlight_num 31//��̬��ʱ�򱳹���Ҫ��������ֵ
/** @brief �����Զ���������
* @return �������
*/
void backlight_monitor_reset(D_VidInput input) D_FUNCPOSTFIT
{
    //�������̬�����¿���
    windos9_flag = 0;
    check_times = 0;
    backlight_gd = 0;
    needbacklight = 0;
    curbacklight = 0;

    return;
}

/** @brief �����Զ���������
* @return �������
*/
void backlight_monitor(D_VidInput input) D_FUNCPOSTFIT
{
    if(d_vip_get_play_status(0) == D_OK)
    {
        D_U8 backlight;

        if(windos9_flag == 0)//��δ�жϵ���9����
        {
            if(d_vip_get_play_status(2) == D_OK)
            {
                windos9_flag = 1;
            }
        }
        else
        {
            D_U8 video_mode;
            D_BLDIM_SET blparam;

            //�ж�ͼ��ģʽΪ�û������ȺͶԱȶȲ���50��ʱ�����������Ч����
            p_tvconf_get_cur_imagemode(&video_mode, p_vip_get_dbinput(input));

            if(video_mode == 2)
            {
                D_Tv_Config_EEI eel_param;

                p_tvconf_get_eei_param(&eel_param);

                p_tvconf_get_bldim_backlight(&(backlight), p_vip_get_dbinput(input));
                p_tvconf_get_bldim_set_param(&(blparam), p_vip_get_dbinput(input));
                if(d_vip_get_play_status(1) == D_OK) //��̬ͼ��
                {
                    backlight_gd = 0;
                    if(backlight > (eel_param.motionless + eel_param.motion))
                        needbacklight = backlight - (eel_param.motionless + eel_param.motion);
                }
                else//��̬ͼ��
                {
                    backlight_gd = 0;
                    if(backlight > (eel_param.motionless + eel_param.motion))
                        needbacklight = backlight - eel_param.motionless;
                }
                if(curbacklight != needbacklight)
                {
                    if(curbacklight == 0)
                    {
                        curbacklight = backlight;
#ifndef D_TV_IAMGE_SOURCE
                        lastbacklight_gd = blparam.gd_on;
#endif
                    }
                    if(curbacklight > needbacklight)
                    {
                        if((curbacklight - needbacklight) > 5)
                            curbacklight = curbacklight - 5;
                        else
                            curbacklight = needbacklight;
#ifndef D_TV_IAMGE_SOURCE
                        if(curbacklight == needbacklight)
                        {
                            blparam.gd_on = backlight_gd;
                        }
                        else
                        {
                            blparam.gd_on = lastbacklight_gd;
                        }
                        lastbacklight_gd = blparam.gd_on;
#endif
                        d_vip_setBldim(&(blparam), curbacklight);
                    }
                    else if(curbacklight < needbacklight)
                    {
                        if((needbacklight  - curbacklight) > 5)
                            curbacklight = curbacklight + 5;
                        else
                            curbacklight = needbacklight;
#ifndef D_TV_IAMGE_SOURCE
                        if(curbacklight == needbacklight)
                        {
                            blparam.gd_on = backlight_gd;
                        }
                        else
                        {
                            blparam.gd_on = lastbacklight_gd;
                        }
                        lastbacklight_gd = blparam.gd_on;
#endif
                        d_vip_setBldim(&(blparam), curbacklight);
                    }
                }

            }
        }
    }
}


/** @brief �����Զ���������
* @return �������
*/
static void backlight_proc(D_Ptr p) D_FUNCPOSTFIT
{
    D_VidInput      input;
    D_U8 video_mode;
    //p_vip_set_gamma(D_VID_IUTPUT_DTV, 0);
    while(1)
    {
        input = p_conf_get_vid_input();
        if((input != D_VID_IUTPUT_TV) && (input != D_VID_IUTPUT_DTV))//�ж�����Դ// added DTV source by wangyg on 2015-11-27
        {
            //�������̬�����¿���
            d_task_wait(300);
            continue;
        }
        //�ж�ͼ��ģʽΪ�û�������������Ч����
        p_tvconf_get_cur_imagemode(&video_mode, p_vip_get_dbinput(input));
        if(video_mode != 2)
        {
            //�������̬�����¿���
            d_task_wait(300);
            continue;
        }
        if(d_vip_get_play_status(0) == D_OK)
        {
            D_U8 backlight;

            if(windos9_flag == 0)//��δ�жϵ���9����
            {
                if(d_vip_get_play_status(2) == D_OK)
                {
                    windos9_flag = 1;
                }
            }
            else
            {
                D_BLDIM_SET blparam;

                D_Tv_Config_EEI eel_param;

                p_tvconf_get_eei_param(&eel_param);

                p_tvconf_get_bldim_backlight(&(backlight), p_vip_get_dbinput(input));
                p_tvconf_get_bldim_set_param(&(blparam), p_vip_get_dbinput(input));
                if(d_vip_get_play_status(1) == D_OK) //��̬ͼ��
                {
                    backlight_gd = 0;
                    if(backlight > (eel_param.motionless + eel_param.motion))
                        needbacklight = backlight - (eel_param.motionless + eel_param.motion);
                }
                else//��̬ͼ��
                {
                    backlight_gd = 0;
                    if(backlight > (eel_param.motionless + eel_param.motion))
                        needbacklight = backlight - eel_param.motionless;
                }
                if(curbacklight != needbacklight)
                {
                    if(curbacklight == 0)
                    {
                        curbacklight = backlight;
#ifndef D_TV_IAMGE_SOURCE						
                        lastbacklight_gd = blparam.gd_on;
#endif
                    }
                    if(curbacklight > needbacklight)
                    {
                        if((curbacklight - needbacklight) > 5)
                            curbacklight = curbacklight - 5;
                        else
                            curbacklight = needbacklight;
#ifndef D_TV_IAMGE_SOURCE
                        if(curbacklight == needbacklight)
                        {
                            blparam.gd_on = backlight_gd;
                        }
                        else
                        {
                            blparam.gd_on = lastbacklight_gd;
                        }
                        lastbacklight_gd = blparam.gd_on;
#endif
                        d_vip_setBldim(&(blparam), curbacklight);
                    }
                    else if(curbacklight < needbacklight)
                    {
                        if((needbacklight  - curbacklight) > 5)
                            curbacklight = curbacklight + 5;
                        else
                            curbacklight = needbacklight;
#ifndef D_TV_IAMGE_SOURCE
                        if(curbacklight == needbacklight)
                        {
                            blparam.gd_on = backlight_gd;
                        }
                        else
                        {
                            blparam.gd_on = lastbacklight_gd;
                        }
                        lastbacklight_gd = blparam.gd_on;
#endif
                        d_vip_setBldim(&(blparam), curbacklight);
                    }
                    d_task_wait(100);
                    continue;
                }
            }
        }
        //�������̬�����¿���
        d_task_wait(300);
    }
}

/** @brief ����
* @return �������
*/
D_Result
p_vip_backlight_open(void)D_FUNCPOSTFIT
{
    D_TaskAttr TaskAttr;

    D_TASK_ATTR_INIT(&TaskAttr);
    TaskAttr.name = "backlight";
    TaskAttr.priority = 3;
    TaskAttr.stack_size = 4096;
    windos9_flag = 0;

    hTask_backlight = d_task_create(&TaskAttr, backlight_proc, NULL);
    if(hTask_backlight == D_INVALID_HANDLE)
    {
        D_ERROR("backlight task create failed!\n");
        return D_ERR;
    }

    return D_OK;
}

/** @brief ����
* @return �������
*/
D_Result
p_vip_backlight_close(void)D_FUNCPOSTFIT
{
    if(hTask_backlight != D_INVALID_HANDLE)
    {
        d_task_join(hTask_backlight);
    }

    hTask_backlight = D_INVALID_HANDLE;

    return D_OK;
}



/**@}*/
