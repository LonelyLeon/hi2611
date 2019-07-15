		
int D_Align[]={		
	{D_ALIGN_LEFT, 1, },	/**<ˮƽ�����*/
	{D_ALIGN_RIGHT, 2, },	/**<ˮƽ�Ҷ���*/
	{D_ALIGN_CENTER, 4, },	/**<ˮƽ���ж���*/
	{D_ALIGN_TOP, 8, },	/**<��ֱ�϶���*/
	{D_ALIGN_BOTTOM, 16, },	/**<��ֱ�¶���*/
	{D_ALIGN_MIDDLE, 32, },	/**<��ֱ���ж���*/
};		
		
		
		
int D_TextScrollType[]={		
	{D_SCROLL_TYPE_NO, 0, },	/**<��������*/
	{D_SCROLL_TYPE_R2L_PIXSEL, 1, },	/**<���������ع���*/
	{D_SCROLL_TYPE_L2R_PIXSEL, 2, },	/**<���������ع���*/
	{D_SCROLL_TYPE_R2L_CHAR, 3, },	/**<�������ַ�����*/
	{D_SCROLL_TYPE_L2R_CHAR, 4, },	/**<�������ַ�����*/
	{D_SCROLL_TYPE_DOWN2UP_PIXSEL, 5, },	/**<���������ع���*/
	{D_SCROLL_TYPE_UP2DOWN_PIXSEL, 6, },	/**<���������ع���*/
	{D_SCROLL_TYPE_LINE, 7, },	/**<�й���(����)*/
	{D_SCROLL_TYPE_PAGE, 8, },	/**<ҳ����(����)*/
	{D_SCROLL_TYPE_OTHER, 9, },	/**<����*/
};		
		
		
		
int D_CursorType[]={		
	{D_CURSOR_TYPE_NO, 0, },	/**<�޹��*/
	{D_CURSOR_TYPE_UNDERLINE, 1, },	/**<�º��߹��*/
	{D_CURSOR_TYPE_VERTICAL, 2, },	/**<���߹��*/
	{D_CURSOR_TYPE_OTHER, 3, },	/**<����*/
};		
		
		
int D_ListFocusType[]={		
	{D_LIST_FOCUS_TYPE_NO, 0, },	/**<���۽�*/
	{D_LIST_FOCUS_TYPE_ROW, 1, },	/**<�о۽�*/
	{D_LIST_FOCUS_TYPE_CELL, 2, },	/**<��Ԫ��۽�*/
	{D_LIST_FOCUS_TYPE_ALL, 3, },	/**<�����б�۽�*/
	{D_LIST_FOCUS_TYPE_OTHER, 4, },	/**<����*/
};		
		
		
int D_InputBoxType[]={		
	{D_INPUTBOX_TYPE_NUMBER, 0, },	/**<���������*/
	{D_INPUTBOX_TYPE_CHAR, 1, },	/**<Ӣ����ĸ(���������ַ�)�����*/
	{D_INPUTBOX_TYPE_TEXT, 2, },	/**<�����ַ������*/
	{D_INPUTBOX_TYPE_PASSWD_NUMBER, 3, },	/**<�������������*/
	{D_INPUTBOX_TYPE_PASSWD_CHAR, 4, },	/**<Ӣ����ĸ(���������ַ�)�����*/
	{D_INPUTBOX_TYPE_FORMAT, 5,	},	/**< ��ʽ������(��ʱ�䡢���ڡ�IP��)*/
	{D_INPUTBOX_TYPE_OTHER, 6, },	/**<����*/
};
		
		
int D_Direction[]={		
	{D_DIR_HORIZONTAL, 0, },	/**<ˮƽ����*/
	{D_DIR_VERTICAL, 1, },	/**<��ֱ����*/
};		
int D_LineType[]={
	{D_LINE_SINGLE, 0},
	{D_LINE_MULTI, 1},
};

int D_FontType[]={
	{D_FONT_TRUE_TYPE, 0},
	{D_FONT_DOT_MATRIX, 1},
};