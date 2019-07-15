/** @file
* @brief �������ģ��
*
*	һ�������ɶ���ؼ����,����ͨ��һ�����ݽṹ����,�����ڵ�
*	�ؼ�����ͨ��Ԥ���趨��ID��������
* @author ����
* @date 2013-05-08 ����: �����ļ�
*/
#ifndef _D_FRAME_H_
#define _D_FRAME_H_

#include "dAV.h"
#include "dVisual.h"

#ifdef  __cplusplus
extern "C"
{
#endif

typedef D_U16  	D_ColourID;
typedef D_U16  	D_ImageID;
typedef D_U16  	D_TextID;
typedef	D_U16   	D_Align;

/** @brief �������Ͷ���*/
#define D_FONT_DOT_MATRIX 0	/**< ����*/
#define D_FONT_TRUE_TYPE 1		/**< */

/** @brief ���ж��ж���*/
#define D_LINE_SINGLE 0
#define D_LINE_MULTI 1

/** @brief �ؼ�״̬���Ͷ���*/
#define D_CTR_STATUS_NORMAL		0	/**< ƽ��״̬*/
#define D_CTR_STATUS_FOCUSED		1	/**< ����״̬*/
#define D_CTR_STATUS_DISABLE		2	/**< ʧЧ״̬*/
#define D_CTR_STATUS_MAX			3	/**< ����*/	


/** @brief ���뷽ʽ*/
#define D_ALIGN_LEFT		1	/**< ˮƽ�����*/
#define D_ALIGN_RIGHT		2	/**< ˮƽ�Ҷ���*/
#define D_ALIGN_CENTER		4	/**< ˮƽ���ж���*/
#define D_ALIGN_TOP			8	/**< ��ֱ�϶���*/
#define D_ALIGN_BOTTOM		16	/**< ��ֱ�¶���*/
#define D_ALIGN_MIDDLE		32	/**< ��ֱ���ж���*/
#define D_ALIGN_WHOLE_CENTER 64	/**< ����ˮƽ���У�����ʱ��֮�������*/

/** @brief ��ֱˮƽ������*/
#define D_DIR_HORIZONTAL	0	/**< ˮƽ����*/
#define D_DIR_VERTICAL		1	/**< ��ֱ����*/


/** @brief ����ƴͼ���ͣ�ͼƬid����*/
#define D_COMB_IMG_HOR_LEFT		0
#define D_COMB_IMG_HOR_CENTER	1
#define D_COMB_IMG_HOR_RIGHT		2

#define D_COMB_IMG_VER_TOP		0
#define D_COMB_IMG_VER_MIDDLE		1
#define D_COMB_IMG_VER_BOTTOM	2

#define D_COMB_IMG_MATRIX_TOP_LEFT			0
#define D_COMB_IMG_MATRIX_TOP_CENTER		1
#define D_COMB_IMG_MATRIX_TOP_RIGHT			2
#define D_COMB_IMG_MATRIX_MIDDLE_LEFT		3
#define D_COMB_IMG_MATRIX_MIDDLE_CENTER		4
#define D_COMB_IMG_MATRIX_MIDDLE_RIGHT		5
#define D_COMB_IMG_MATRIX_BOTTOM_LEFT		6
#define D_COMB_IMG_MATRIX_BOTTOM_CENTER		7
#define D_COMB_IMG_MATRIX_BOTTOM_RIGHT		8


#define D_IMAGE_ID_RES_TYPE_INVALID			0
#define D_IMAGE_ID_RES_TYPE_SINGLE_IMAGE		1
#define D_IMAGE_ID_RES_TYPE_COMB_IMAGES		2
#define D_IMAGE_ID_RES_TYPE_FREE_SHAPE		3


/** @brief ��ɫ�Ƿ���Ч */
#define D_IS_VALID_COLOR(_a_)	(_a_ != ((D_ColourID)(-1)))

/** @brief ͼƬ�Ƿ���Ч */
#define D_IS_VALID_IMAGE(_a_)	(_a_ != ((D_ImageID)(-1)))

/** @brief �Ƿ������ͼ*/
#define D_IS_COMB_IMAGES(_t_)	(_t_ == D_IMAGE_ID_RES_TYPE_COMB_IMAGES)

/** @brief �Ƿ��ǻص�����*/
#define D_IS_DRAW_CALLBACK(_t_)	(_t_ == D_IMAGE_ID_RES_TYPE_FREE_SHAPE)




/** @brief �ؼ����Ͷ���*/
typedef enum {
	D_CTRL_DESKTOP = 0,		/**< ��������*/
	D_CTRL_WINDOW,		/**< ����*/
	D_CTRL_LABEL,			/**< �ı�*/
	D_CTRL_BUTTON,		/**< ��ť*/
	D_CTRL_SELECT,/**< ѡ���*/
	D_CTRL_CHECK,	/**< ��ѡ��*/
	D_CTRL_RADIO,	/**< ��ѡ��*/
	D_CTRL_INPUT,	/**< �ı������*/
	D_CTRL_LIST,			/**< �б�*/
	D_CTRL_LIST_ROW,	/**< �б���*/
	D_CTRL_LIST_CELL,	/**< �б���*/
	D_CTRL_PROGRESS,	/**< ������*/
	D_CTRL_SCROLL,		/**< ������*/
	D_CTRL_GROUP,			/**< ������*/
	D_CTRL_DRAW_AREA,	/**< ��ͼ��*/
	D_CTRL_IMAGE,			/**< ͼ��ؼ�*/
} D_ControlType;


/** @brief label������*/	
typedef enum {
 	D_LABEL_TYPE_NORMAL		 	= 0,		/*ƽ����ǩ*/
 	D_LABEL_TYPE_VIDEO_WIN_MSG	= 1,		/*С��Ƶ��Ϣ��ʾ��ǩ*/
 	D_LABEL_TYPE_PAGE_SWITCH	= 2,		/*��ҳ��ʾ��ǩ*/
 	D_LABEL_TYPE_OTHER					/**< ����*/
}D_LabelType;


/** @brief�ı�������ʽ*/
typedef enum {
	D_SCROLL_TYPE_NO					= 0,		/**< ��������*/
	D_SCROLL_TYPE_R2L_PIXSEL			= 1,		/**< ���������ع���*/
	D_SCROLL_TYPE_L2R_PIXSEL			= 2,		/**< ���������ع���*/
	D_SCROLL_TYPE_R2L_CHAR			= 3,		/**< �������ַ�����*/
	D_SCROLL_TYPE_L2R_CHAR			= 4,		/**< �������ַ�����*/
	D_SCROLL_TYPE_DOWN2UP_PIXSEL	= 5,		/**< ���������ع���*/
	D_SCROLL_TYPE_UP2DOWN_PIXSEL	= 6,		/**< ���������ع���*/
	D_SCROLL_TYPE_LINE				= 7,		/**< �й���(����)*/
	D_SCROLL_TYPE_PAGE				= 8,		/**< ҳ����(����)*/
	D_SCROLL_TYPE_OTHER						/**< ����*/	
}D_TextScrollType;


/** @brief ���������*/	
typedef enum {
	D_INPUTBOX_TYPE_NUMBER			= 0,		/**< ���������*/
	D_INPUTBOX_TYPE_CHAR				= 1,		/**< Ӣ����ĸ(���������ַ�)�����*/
	D_INPUTBOX_TYPE_TEXT				= 2,		/**< �����ַ������*/
	D_INPUTBOX_TYPE_PASSWD_NUMBER	= 3,		/**< �������������*/
	D_INPUTBOX_TYPE_PASSWD_CHAR	= 4,		/**< Ӣ����ĸ(���������ַ�)�����*/
	D_INPUTBOX_TYPE_FORMAT			= 5,		/**< ��ʽ������(��ʱ�䡢���ڡ�IP��)*/
	D_INPUTBOX_TYPE_OTHER					/**< ����*/	
}D_InputBoxType;


/** @brief �б�۽�����*/	
typedef enum {
	D_LIST_FOCUS_TYPE_NO			= 0,		/**<���۽�*/
	D_LIST_FOCUS_TYPE_ROW		= 1,		/**< �о۽�*/
	D_LIST_FOCUS_TYPE_CELL		= 2,		/**< ��Ԫ��۽�*/
	D_LIST_FOCUS_TYPE_ALL			= 3,		/**< �����б�۽�*/
	D_LIST_FOCUS_TYPE_OTHER				/**< ����*/
}D_ListFocusType;


/** @brief image������*/	
typedef enum {
 	D_IMAGEBOX_TYPE_NORMAL		 	= 0,		/*ƽ��ͼƬ�ؼ�*/
 	D_IMAGEBOX_TYPE_IMAGE_USE_ALIGN	= 0x20,	/*��ͼƬʱʹ�ö��뷽ʽ*/
 	D_LABELBOX_TYPE_OTHER					/**< ����*/
}D_ImageBoxType;


/** @brief �������*/	
typedef enum {
	D_CURSOR_TYPE_NO			= 0,		/**< �޹��*/
	D_CURSOR_TYPE_UNDERLINE	= 1,		/**< �º��߹��*/
	D_CURSOR_TYPE_VERTICAL	= 2,		/**< ���߹��*/
	D_CURSOR_TYPE_OTHER				/**< ����*/
}D_CursorType;

/** @brief ���ͼ����*/	
typedef enum {
	D_IMG_COMB_TYPE_HOR		= 0,		/**< ˮƽ���*/
	D_IMG_COMB_TYPE_VER		= 1,		/**< ��ֱ���*/
	D_IMG_COMB_TYPE_MATRIX	= 2,		/**< �Ź���������*/
	D_IMG_COMB_TYPE_OTHER			/**< ����*/ 
}D_ImgCombType;


/** @brief ���ͼ�ṹ*/
typedef struct
{
	D_U16	combtype;
	D_U16	imgids[9];	/*���9�ţ���ˮƽ��ֱ��ֻ�õ�3��*/
}D_ImageCombInfo;	
	

/** @brief ��ʽ����*/
typedef struct
{
	D_ColourID	frontColourId;		/**< ǰ����ɫID*/
	D_U8		fontType;			/**< ����*/
	D_U8		fontSize;			/**< �����С*/
	D_U8		multiLine;			/**< ���ж���*/
	D_Coord		hOffset;				/**< ˮƽƫ��*/
	D_Coord		vOffset;				/**< ��ֱƫ��*/	
	D_Align		align;				/**< ���뷽ʽ*/	
	D_TextScrollType	scrollType;		/**< ��������*/
	D_U16		scrollVelocity;		/**< �����ٶȣ�ʱ��(��λms)*/
	D_U16		scrollGranularity;	/**< ��������(����/ �ַ���/ ����)*/
	D_U32		reserved;
	D_U32		reserved1;
}D_Format;


/** @brief ��������*/
typedef struct{
	D_ColourID	bgColourId;		/**< ������ɫID*/
	D_ImageID	bgImageId;		/**< ����ͼƬID*/
	D_TextID		textId;			/**< �ı�ID*/
	D_Format	*pFormat;		/**< ��ʾ��ʽ*/
}D_CtrlAttribute;



/** @brief һ��ؼ�����*/
typedef struct {
	D_CtrlAttribute *ctrlAttributeList[D_CTR_STATUS_MAX];/**< �ؼ���ʾ���Ա�*/
	D_U32		transparence;						/*�ؼ�͸����־*/
} D_FrameCtrlDescr;	



/** @brief ѡ�������*/
typedef struct {
	D_CtrlAttribute *ctrlAttributeList[D_CTR_STATUS_MAX];/**< �ؼ���ʾ���Ա�*/
	D_U32		transparence;			/*�ؼ�͸����־*/
	D_U16			 	cnt;				/**< ѡ������*/
	D_TextID const D_FAR	*text_id_list;	/**<�� ѡ����ʾ�ı���Ϣ*/
} D_FrameSelectDescr;	


/** @brief ���������*/
typedef struct {
	D_CtrlAttribute 	*ctrlAttributeList[D_CTR_STATUS_MAX];/**< �ؼ���ʾ���Ա�*/
	D_U32		transparence;						/*�ؼ�͸����־*/
	D_InputBoxType	type;	/**< ���������*/	
	D_U16			cnt;			/**< �������ַ�����*/
	D_Char	  		*text;		/**< ������ı�������*/
	D_CursorType		cursorType;	/**< �������*/
	D_Char	  		chr1;		/**< ������ʾ�ַ�*/
	D_Char	  		chr2;		/**< ��������ַ�*/
} D_FrameInputBoxDescr;	


/** @brief ����������*/
typedef struct {
	D_CtrlAttribute 	*ctrlAttributeList[D_CTR_STATUS_MAX];/**< �ؼ���ʾ���Ա�*/
	D_U32			transparence;						/*�ؼ�͸����־*/
	D_U16			max;		/**< �ܲ���*/
	D_U16			step;		/**< ����*/
	D_U8			HV_flag;		/**< ˮƽ��ֱ�����ʶ*/
	D_ColourID		frontColourId;	/**< ǰ����ɫID*/
	D_ImageID		frontImageId;	/**< ǰ��ͼƬID*/
} D_FrameProgressBarDescr;


/** @brief �б�������*/
typedef struct {
	D_CtrlAttribute *pRowAttr;          /**< ������*/	
	D_CtrlAttribute **pCellAttrList;     /**< ���ﵥԪ�����Ա�*/
}D_RowCtrlAttribute;

/** @brief �б�����*/
typedef struct {
	D_CtrlAttribute 	*ctrlAttributeList[D_CTR_STATUS_MAX];/**< �ؼ���ʾ���Ա�*/
	D_U32			transparence;						/*�ؼ�͸����־*/
	D_U16			max;			/**< ������*/
	D_U16			pal_row;		/**< ��ʾһҳ����*/
	D_U16			ntsc_row;		/**< ��ʾһҳ����*/
	D_U16			col;				/**< ����*/
	D_Coord			rh;				/**< �и�*/
	D_Coord	const D_FAR	*cw;		/**< �п�����*/
	D_U16			rowSpace;		/**< �м��*/
	D_U16			colSpace;		/**< �м��*/
	D_ListFocusType	focusType;		/**< �۽�����(��/ ��/ ��Ԫ��  �ۼ�)*/
	D_Ptr	 	cellCtrDescr;		/**< ����Ԫ�����Ա�*/
	D_Ptr	 	rowCtrDescr;		/**< �������Ա�*/	
} D_FrameListDescr;




/** @brief ����������*/
typedef struct {
	D_ImageID	startImageId;	/**< ��ʼͼid*/
	D_ImageID	endImageId;	/**< ��βͼid*/
	D_ImageID	middleImageId;	/**< �м�ͼid*/
	D_ImageID	vernierImageId;	/**< �α�ͼid*/
}D_ScrollBarImage;

typedef struct {
	D_CtrlAttribute 	*ctrlAttributeList[D_CTR_STATUS_MAX];/**< �ؼ���ʾ���Ա�*/	
	D_U32			transparence;						/*�ؼ�͸����־*/
	D_U16			max;			/**< �ܲ���*/
	D_U16			step;			/**< ����*/
	D_U8			HV_flag;			/**< ˮƽ��ֱ�����ʶ*/
	D_ScrollBarImage	image;			/**< ������ͼƬ ��Դ*/	
} D_FrameScrollBarDescr;

/** @brief �����ڲ��ؼ�����*/
typedef struct {
	D_ControlType	type;			/**< �ؼ�����*/
	D_ID			parent_id;		/**< ���ؼ�ID*/
	D_Coord		 	x;				/**< x����*/
	D_Coord		 	paly;			/**< PAL���µ�y����*/
	D_Coord		 	ntscy;			/**< NTSC���µ�y����*/
	D_Coord		 	w;				/**< �ؼ����*/
	D_Coord		 	palh;			/**< PAL���µĿؼ��߶�*/
	D_Coord		 	ntsch;			/**< NTSC���µĿؼ��߶�*/
	//D_Ptr			ptr;				/**< �ؼ�����ָ��*/
	D_ID			param_id;		/**< �����ؼ�ID*/
	D_FrameCtrlDescr	*pCtrlDescr;		/**< �ؼ�������������ָ��*/
} D_FrameControlDescr;

/** @brief ��������*/
typedef struct _D_Frame D_Frame;
struct _D_Frame {
	D_Visual*	*ctrls;			/**< ��Ŵ����ڿؼ�����ָ��*/
	D_FrameControlDescr	const D_FAR *ctrl_descrs;		/**< �ؼ�����*/
	D_Result	(*init) (D_Frame *frm); /**< �����ʼ��*/
	D_Bool		 loaded;		/**< �����Ƿ��Ѿ�����*/
};

/** @brief ���һ�������Ƿ��Ѿ�����*/
#define d_frame_is_loaded(_f)	((_f)->loaded)

/** @brief ����һ������
* @param frm	Ҫ���صĴ������ݽṹָ��
* @return �ɹ�����D_OK, ʧ�ܷ���D_ERR
*/
D_Result	d_frame_load (D_Frame *frm) D_FUNCPOSTFIT;

/** @brief ж��һ������
* @param frm	Ҫж�صĴ������ݽṹָ��
* @return �ɹ�����D_OK, ʧ�ܷ���D_ERR
*/
D_Result	d_frame_unload (D_Frame *frm) D_FUNCPOSTFIT;

/** @brief ���ش�����һ���ؼ���ָ��
* @param frm	�������ݽṹָ��
* @param id		�ؼ�ID
* @return �ɹ�����D_OK, ʧ�ܷ���D_ERR
*/
D_Visual*	d_frame_get_control (D_Frame *frm, D_ID id) D_FUNCPOSTFIT;

/** @brief ���ش�����һ���ؼ���ID
* @param frm	�������ݽṹָ��
* @param vis	�ؼ�
* @return �ɹ����ؿؼ�ID, ʧ�ܷ���-1
*/
D_ID d_frame_get_control_id (D_Frame *frm, D_Visual *vis) D_FUNCPOSTFIT;

/** @brief �������ô����ڵ�ȫ���ؼ���λ�ô�С
* @param frm �������ݽṹָ��
* @return �ɹ�����D_OK, ʧ�ܷ���D_ERR
*/
D_Result	d_frame_reload_size (D_Frame *frm) D_FUNCPOSTFIT;

#ifdef  __cplusplus
}
#endif
#endif

