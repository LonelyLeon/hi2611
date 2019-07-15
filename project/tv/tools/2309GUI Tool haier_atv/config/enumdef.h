		
int D_Align[]={		
	{D_ALIGN_LEFT, 1, },	/**<水平左对齐*/
	{D_ALIGN_RIGHT, 2, },	/**<水平右对齐*/
	{D_ALIGN_CENTER, 4, },	/**<水平居中对齐*/
	{D_ALIGN_TOP, 8, },	/**<垂直上对齐*/
	{D_ALIGN_BOTTOM, 16, },	/**<垂直下对齐*/
	{D_ALIGN_MIDDLE, 32, },	/**<垂直居中对齐*/
};		
		
		
		
int D_TextScrollType[]={		
	{D_SCROLL_TYPE_NO, 0, },	/**<不滚流动*/
	{D_SCROLL_TYPE_R2L_PIXSEL, 1, },	/**<右向左像素滚动*/
	{D_SCROLL_TYPE_L2R_PIXSEL, 2, },	/**<左向右像素滚动*/
	{D_SCROLL_TYPE_R2L_CHAR, 3, },	/**<右向左字符滚动*/
	{D_SCROLL_TYPE_L2R_CHAR, 4, },	/**<左向右字符滚动*/
	{D_SCROLL_TYPE_DOWN2UP_PIXSEL, 5, },	/**<下向上像素滚动*/
	{D_SCROLL_TYPE_UP2DOWN_PIXSEL, 6, },	/**<上向下像素滚动*/
	{D_SCROLL_TYPE_LINE, 7, },	/**<行滚动(向上)*/
	{D_SCROLL_TYPE_PAGE, 8, },	/**<页滚动(向上)*/
	{D_SCROLL_TYPE_OTHER, 9, },	/**<其它*/
};		
		
		
		
int D_CursorType[]={		
	{D_CURSOR_TYPE_NO, 0, },	/**<无光标*/
	{D_CURSOR_TYPE_UNDERLINE, 1, },	/**<下横线光标*/
	{D_CURSOR_TYPE_VERTICAL, 2, },	/**<竖线光标*/
	{D_CURSOR_TYPE_OTHER, 3, },	/**<其它*/
};		
		
		
int D_ListFocusType[]={		
	{D_LIST_FOCUS_TYPE_NO, 0, },	/**<不聚焦*/
	{D_LIST_FOCUS_TYPE_ROW, 1, },	/**<行聚焦*/
	{D_LIST_FOCUS_TYPE_CELL, 2, },	/**<单元格聚焦*/
	{D_LIST_FOCUS_TYPE_ALL, 3, },	/**<整个列表聚焦*/
	{D_LIST_FOCUS_TYPE_OTHER, 4, },	/**<其它*/
};		
		
		
int D_InputBoxType[]={		
	{D_INPUTBOX_TYPE_NUMBER, 0, },	/**<数字输入框*/
	{D_INPUTBOX_TYPE_CHAR, 1, },	/**<英文字母(包括数字字符)输入框*/
	{D_INPUTBOX_TYPE_TEXT, 2, },	/**<任意字符输入框*/
	{D_INPUTBOX_TYPE_PASSWD_NUMBER, 3, },	/**<数字密码输入框*/
	{D_INPUTBOX_TYPE_PASSWD_CHAR, 4, },	/**<英文字母(包括数字字符)输入框*/
	{D_INPUTBOX_TYPE_FORMAT, 5,	},	/**< 格式化输入(如时间、日期、IP等)*/
	{D_INPUTBOX_TYPE_OTHER, 6, },	/**<其它*/
};
		
		
int D_Direction[]={		
	{D_DIR_HORIZONTAL, 0, },	/**<水平方向*/
	{D_DIR_VERTICAL, 1, },	/**<垂直方向*/
};		
int D_LineType[]={
	{D_LINE_SINGLE, 0},
	{D_LINE_MULTI, 1},
};

int D_FontType[]={
	{D_FONT_TRUE_TYPE, 0},
	{D_FONT_DOT_MATRIX, 1},
};