#ifndef __JPEG_HW_H__
#define __JPEG_HW_H__

#include "_helper.h"
enum {
	DATA_TYPE_FILE = 0,
	DATA_TYPE_MEM,
};

int hdk_jpeg_hw_init(void);
void hdk_jpeg_hw_show(void);
void hdk_jpeg_hw_close(void);
int hdk_jpeg_get_hw(void * data, int data_type, int * width, int * height);
int hdk_jpeg_hw_decode(void * data, int data_type, int data_size, int pic_in_w, int pic_in_h, int pic_x, int pic_y, int show_type);
#endif //__JPEG_HW_H__
