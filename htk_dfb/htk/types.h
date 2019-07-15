/**
 * @file
 * @brief 类型定义
 */
#ifndef __HTK_TYPES_H__
#define __HTK_TYPES_H__

#include <glib-object.h>

/***************************************************************************/

#define helperbar_colors 3

/***************************************************************************/

typedef struct HtkAdjustment       HtkAdjustment;
typedef struct HtkAdjustmentClass  HtkAdjustmentClass;

typedef struct HtkArrow      HtkArrow;
typedef struct HtkArrowClass HtkArrowClass;

typedef struct HtkBin      HtkBin;
typedef struct HtkBinClass HtkBinClass;

typedef struct HtkBox      HtkBox;
typedef struct HtkBoxClass HtkBoxClass;

typedef struct HtkBuilder      HtkBuilder;
typedef struct HtkBuilderClass HtkBuilderClass;

typedef struct HtkButton      HtkButton;
typedef struct HtkButtonClass HtkButtonClass;

typedef struct HtkCellLayout      HtkCellLayout;
typedef struct HtkCellLayoutIface HtkCellLayoutIface;

typedef struct HtkCellList      HtkCellList;
typedef struct HtkCellListClass HtkCellListClass;

typedef struct HtkCellRenderer      HtkCellRenderer;
typedef struct HtkCellRendererClass HtkCellRendererClass;

typedef struct HtkCellRendererPixbuf      HtkCellRendererPixbuf;
typedef struct HtkCellRendererPixbufClass HtkCellRendererPixbufClass;

typedef struct HtkCellRendererText      HtkCellRendererText;
typedef struct HtkCellRendererTextClass HtkCellRendererTextClass;

typedef struct HtkCellView      HtkCellView;
typedef struct HtkCellViewClass HtkCellViewClass;

typedef struct HtkCheckButton      HtkCheckButton;
typedef struct HtkCheckButtonClass HtkCheckButtonClass;

typedef struct HtkChoiceButton      HtkChoiceButton;
typedef struct HtkChoiceButtonClass HtkChoiceButtonClass;

typedef struct HtkCList       HtkCList;
typedef struct HtkCListClass  HtkCListClass;

typedef struct HtkComboBox      HtkComboBox;
typedef struct HtkComboBoxClass HtkComboBoxClass;

typedef struct HtkContainer      HtkContainer;
typedef struct HtkContainerClass HtkContainerClass;

typedef struct HtkDialog      HtkDialog;
typedef struct HtkDialogClass HtkDialogClass;

typedef struct HtkDrawingArea      HtkDrawingArea;
typedef struct HtkDrawingAreaClass HtkDrawingAreaClass;

typedef struct HtkDynamicIconBox   HtkDynamicIconBox;
typedef struct HtkDynamicIconBoxClass HtkDynamicIconBoxClass;

typedef struct HtkEntry       HtkEntry;
typedef struct HtkEntryClass  HtkEntryClass;

typedef struct HtkFileChooser      HtkFileChooser;
typedef struct HtkFileChooserClass HtkFileChooserClass;

typedef struct HtkFileChooserDialog      HtkFileChooserDialog;
typedef struct HtkFileChooserDialogClass HtkFileChooserDialogClass;

typedef struct HtkFileChooserWidget      HtkFileChooserWidget;
typedef struct HtkFileChooserWidgetClass HtkFileChooserWidgetClass;

typedef struct HtkFixed      HtkFixed;
typedef struct HtkFixedClass HtkFixedClass;

typedef struct HtkHBox      HtkHBox;
typedef struct HtkHBoxClass HtkHBoxClass;

typedef struct HtkHelperbar      HtkHelperbar;
typedef struct HtkHelperbarClass HtkHelperbarClass;

typedef struct HtkHelperbarContext      HtkHelperbarContext;
typedef struct HtkHelperbarContextClass HtkHelperbarContextClass;

typedef struct HtkHelperbarSlot      HtkHelperbarSlot;
typedef struct HtkHelperbarSlotClass HtkHelperbarSlotClass;

typedef struct HtkHPaned      HtkHPaned;
typedef struct HtkHPanedClass HtkHPanedClass;

typedef struct HtkHScale	HtkHScale;
typedef struct HtkHScaleClass	HtkHScaleClass;

typedef struct HtkHScrollbar       HtkHScrollbar;
typedef struct HtkHScrollbarClass  HtkHScrollbarClass;

typedef struct HtkIconBar      HtkIconBar;
typedef struct HtkIconBarClass HtkIconBarClass;

typedef struct HtkIconBarCore      HtkIconBarCore;
typedef struct HtkIconBarCoreClass HtkIconBarCoreClass;

typedef struct HtkIconBarImpl      HtkIconBarImpl;
typedef struct HtkIconBarImplClass HtkIconBarImplClass;

typedef struct HtkIconBox      HtkIconBox;
typedef struct HtkIconBoxClass HtkIconBoxClass;

typedef struct HtkIconView      HtkIconView;
typedef struct HtkIconViewClass HtkIconViewClass;

typedef struct HtkHSeparator      HtkHSeparator;
typedef struct HtkHSeparatorClass HtkHSeparatorClass;

typedef struct HtkIconFactory      HtkIconFactory;
typedef struct HtkIconFactoryClass HtkIconFactoryClass;

typedef struct HtkIMContext       HtkIMContext;
typedef struct HtkIMContextClass  HtkIMContextClass;

typedef struct HtkImage       HtkImage;
typedef struct HtkImageClass  HtkImageClass;

typedef struct HtkItem      HtkItem;
typedef struct HtkItemClass HtkItemClass;

typedef struct HtkLabel       HtkLabel;
typedef struct HtkLabelClass  HtkLabelClass;

typedef struct HtkListStore       HtkListStore;
typedef struct HtkListStoreClass  HtkListStoreClass;

typedef struct HtkMemoryPool HtkMemoryPool;
typedef struct HtkMemoryPoolClass HtkMemoryPoolClass;

typedef struct HtkMenu      HtkMenu;
typedef struct HtkMenuClass HtkMenuClass;

typedef struct HtkMenuItem      HtkMenuItem;
typedef struct HtkMenuItemClass HtkMenuItemClass;

typedef struct HtkMenuShell      HtkMenuShell;
typedef struct HtkMenuShellClass HtkMenuShellClass;

typedef struct HtkMisc       HtkMisc;
typedef struct HtkMiscClass  HtkMiscClass;

typedef struct HtkNotebook       HtkNotebook;
typedef struct HtkNotebookClass  HtkNotebookClass;

typedef struct HtkObject      HtkObject;
typedef struct HtkObjectClass HtkObjectClass;

typedef struct HtkPaned      HtkPaned;
typedef struct HtkPanedClass HtkPanedClass;

typedef struct HtkProgress      HtkProgress;
typedef struct HtkProgressClass HtkProgressClass;

typedef struct HtkProgressBar      HtkProgressBar;
typedef struct HtkProgressBarClass HtkProgressBarClass;

typedef struct HtkRadioButton      HtkRadioButton;
typedef struct HtkRadioButtonClass HtkRadioButtonClass;

typedef struct HtkRange       HtkRange;
typedef struct HtkRangeClass  HtkRangeClass;

typedef struct HtkSeparator      HtkSeparator;
typedef struct HtkSeparatorClass HtkSeparatorClass;

typedef struct HtkScale		HtkScale;
typedef struct HtkScaleClass	HtkScaleClass;

typedef struct HtkScrollbar       HtkScrollbar;
typedef struct HtkScrollbarClass  HtkScrollbarClass;

typedef struct HtkScrolledWindow       HtkScrolledWindow;
typedef struct HtkScrolledWindowClass  HtkScrolledWindowClass;

typedef struct HtkSpinner       HtkSpinner;
typedef struct HtkSpinnerClass  HtkSpinnerClass;

typedef struct HtkStyle       HtkStyle;
typedef struct HtkStyleClass  HtkStyleClass;

typedef struct HtkStyleDefault       HtkStyleDefault;
typedef struct HtkStyleDefaultClass  HtkStyleDefaultClass;

typedef struct HtkStyleDesktop       HtkStyleDesktop;
typedef struct HtkStyleDesktopClass  HtkStyleDesktopClass;

typedef struct HtkStyleHtv	HtkStyleHtv;
typedef struct HtkStyleHtvClass HtkStyleHtvClass;

typedef struct HtkStyleItRemote HtkStyleItRemote;
typedef struct HtkStyleItRemoteClass HtkStyleItRemoteClass;

typedef struct HtkStyleIptv HtkStyleIptv;
typedef struct HtkStyleIptvClass HtkStyleIptvClass;

typedef struct HtkStyleSkin       HtkStyleSkin;
typedef struct HtkStyleSkinClass  HtkStyleSkinClass;

typedef struct HtkStyleDvb       HtkStyleDvb;
typedef struct HtkStyleDvbClass  HtkStyleDvbClass;

typedef struct HtkTextBuffer      HtkTextBuffer;
typedef struct HtkTextBufferClass HtkTextBufferClass;

typedef struct HtkTextView      HtkTextView;
typedef struct HtkTextViewClass HtkTextViewClass;

typedef struct HtkToggleButton      HtkToggleButton;
typedef struct HtkToggleButtonClass HtkToggleButtonClass;

typedef struct HtkTooltip	HtkTooltip;
typedef struct HtkTooltipClass	HtkTooltipClass;

typedef struct HtkTreeModel      HtkTreeModel;
typedef struct HtkTreeModelClass HtkTreeModelClass;

//typedef struct HtkTreeRowReference      HtkTreeRowReference;
//typedef struct HtkTreeRowReferenceClass HtkTreeRowReferenceClass;

typedef struct HtkTreeSelection      HtkTreeSelection;
typedef struct HtkTreeSelectionClass HtkTreeSelectionClass;

typedef struct HtkTreeView      HtkTreeView;
typedef struct HtkTreeViewClass HtkTreeViewClass;

typedef struct HtkTreeViewColumn      HtkTreeViewColumn;
typedef struct HtkTreeViewColumnClass HtkTreeViewColumnClass;

typedef struct HtkVBox      HtkVBox;
typedef struct HtkVBoxClass HtkVBoxClass;

typedef struct HtkViewport       HtkViewport;
typedef struct HtkViewportClass  HtkViewportClass;

typedef struct HtkVPaned      HtkVPaned;
typedef struct HtkVPanedClass HtkVPanedClass;

typedef struct HtkVScale	HtkVScale;
typedef struct HtkVScaleClass	HtkVScaleClass;

typedef struct HtkVScrollbar       HtkVScrollbar;
typedef struct HtkVScrollbarClass  HtkVScrollbarClass;

typedef struct HtkVSeparator      HtkVSeparator;
typedef struct HtkVSeparatorClass HtkVSeparatorClass;

typedef struct HtkWidget      HtkWidget;
typedef struct HtkWidgetClass HtkWidgetClass;

typedef struct HtkWindow      HtkWindow;
typedef struct HtkWindowClass HtkWindowClass;

typedef struct HtkWordBox      HtkWordBox;
typedef struct HtkWordBoxClass HtkWordBoxClass;

typedef struct HtkXaml      HtkXaml;
typedef struct HtkXamlClass HtkXamlClass;

/***************************************************************************/

typedef struct HtkBoxChild HtkBoxChild;

typedef struct HtkCellInfo HtkCellInfo;

typedef struct HtkCListCell   HtkCListCell;
typedef struct HtkCListRow    HtkCListRow;
typedef struct HtkCListColumn HtkCListColumn;

typedef struct HtkFixedChild HtkFixedChild;

typedef struct HtkIconBoxChild   HtkIconBoxChild;

typedef struct HtkIconSet     HtkIconSet;
typedef struct HtkIconSource  HtkIconSource;

typedef struct HtkNotebookPage   HtkNotebookPage;

typedef struct HtkStockItem HtkStockItem;

typedef struct HtkTaskList    HtkTaskList;
typedef struct HtkTaskManager HtkTaskManager;

typedef struct HtkTextIter      HtkTextIter;

typedef struct HtkTreeIter HtkTreeIter;
typedef struct HtkTreePath HtkTreePath;
typedef struct HtkTreeRowReference      HtkTreeRowReference;

typedef struct HtkWidgetAuxInfo HtkWidgetAuxInfo;

/***************************************************************************/

/**
 * @brief 箭头方向
 */
typedef enum {
	HTK_ARROW_UP,
	HTK_ARROW_DOWN,
	HTK_ARROW_LEFT,
	HTK_ARROW_RIGHT,
	HTK_ARROW_NONE,
} HtkArrowType;

typedef enum {
	HTK_BUILDER_ERROR_INVALID_TYPE_FUNCTION,
	HTK_BUILDER_ERROR_UNHANDLED_TAG,
	HTK_BUILDER_ERROR_MISSING_ATTRIBUTE,
	HTK_BUILDER_ERROR_INVALID_ATTRIBUTE,
	HTK_BUILDER_ERROR_INVALID_TAG,
	HTK_BUILDER_ERROR_MISSING_PROPERTY_VALUE,
	HTK_BUILDER_ERROR_INVALID_VALUE,
	HTK_BUILDER_ERROR_VERSION_MISMATCH,
	HTK_BUILDER_ERROR_DUPLICATE_ID
} HtkBuilderError;

typedef enum {
	HTK_CELL_RENDERER_SELECTED    = 1 << 0,
	HTK_CELL_RENDERER_PRELIT      = 1 << 1,
	HTK_CELL_RENDERER_INSENSITIVE = 1 << 2,
	HTK_CELL_RENDERER_SORTED      = 1 << 3,
	HTK_CELL_RENDERER_FOCUSED     = 1 << 4,
} HtkCellRendererState;

/**
 * @brief cell 类型
 */
typedef enum {
	HTK_CELL_EMPTY,		/**< 空 */
	HTK_CELL_TEXT,		/**< 文字 */
	HTK_CELL_PIXMAP,	/**< 图片 */
	HTK_CELL_PIXTEXT,	/**< 未使用 */
	HTK_CELL_WIDGET,	/**< 控件 */
	HTK_CELL_CHECK,		/**< 未使用 */
} HtkCellType;

/**
 * @brief 删除类型，主要用于文字处理
 */
typedef enum {
	HTK_DELETE_CHARS,
	HTK_DELETE_WORD_ENDS,
	HTK_DELETE_WORDS,
	HTK_DELETE_DISPLAY_LINES,
	HTK_DELETE_DISPLAY_LINE_ENDS,
	HTK_DELETE_PARAGRAPH_ENDS,
	HTK_DELETE_PARAGRAPHS,
	HTK_DELETE_WHITESPACE,
} HtkDeleteType;

typedef enum {
	HTK_DIR_TAB_FORWARD,
	HTK_DIR_TAB_BACKWARD,
	HTK_DIR_UP,
	HTK_DIR_DOWN,
	HTK_DIR_LEFT,
	HTK_DIR_RIGHT,
} HtkDirectionType;

typedef enum {
	HTK_FILE_CHOOSER_ACTION_OPEN,
	HTK_FILE_CHOOSER_ACTION_SAVE,
	HTK_FILE_CHOOSER_ACTION_SELECT_FOLDER,
	HTK_FILE_CHOOSER_ACTION_CREATE_FOLDER,
} HtkFileChooserAction;

typedef enum {
	HTK_FOCUS_POLICY_DISTANCE,
	HTK_FOCUS_POLICY_ARTICLE,
} HtkFocusPolicy;

/**
 * @brief 文字大小
 */
typedef enum {
	HTK_FONT_SIZE_TINY_SMALL,
	HTK_FONT_SIZE_VERY_SMALL,
	HTK_FONT_SIZE_SMALL,
	HTK_FONT_SIZE_MEDIUM,
	HTK_FONT_SIZE_LARGE,
	HTK_FONT_SIZE_VERY_LARGE,
	HTK_FONT_SIZE_HIM,
	HTK_FONT_SIZE_DVB,
	HTK_FONT_SIZE_SPECIAL_LARGE,
} HtkFontSize;

typedef enum {
	HTK_ICON_SIZE_INVALID,
	HTK_ICON_SIZE_MENU,
	HTK_ICON_SIZE_SMALL_TOOLBAR,
	HTK_ICON_SIZE_LARGE_TOOLBAR,
	HTK_ICON_SIZE_BUTTON,
	HTK_ICON_SIZE_DND,
	HTK_ICON_SIZE_DIALOG,
} HtkIconSize;

typedef enum {
	HTK_IMAGE_EMPTY,
	HTK_IMAGE_STOCK,
	HTK_IMAGE_CAIRO,
} HtkImageType;

typedef enum {
	HTK_JUSTIFY_LEFT,
	HTK_JUSTIFY_RIGHT,
	HTK_JUSTIFY_CENTER,
	HTK_JUSTIFY_FILL,
} HtkJustification;

typedef enum {
	HTK_MOVEMENT_LOGICAL_POSITIONS,
	HTK_MOVEMENT_VISUAL_POSITIONS,
	HTK_MOVEMENT_WORDS,
	HTK_MOVEMENT_DISPLAY_LINES,
	HTK_MOVEMENT_DISPLAY_LINE_ENDS,
	HTK_MOVEMENT_PARAGRAPHS,
	HTK_MOVEMENT_PARAGRAPH_ENDS,
	HTK_MOVEMENT_PAGES,
	HTK_MOVEMENT_BUFFER_ENDS,
	HTK_MOVEMENT_HORIZONTAL_PAGES,
} HtkMovementStep;

typedef enum {
	HTK_ORIENTATION_HORIZONTAL,
	HTK_ORIENTATION_VERTICAL,
} HtkOrientation;

typedef enum {
	HTK_PACK_START,
	HTK_PACK_END,
} HtkPackType;

typedef enum {
	HTK_POLICY_ALWAYS,
	HTK_POLICY_AUTOMATIC,
	HTK_POLICY_NEVER,
} HtkPolicyType;

typedef enum {
	HTK_POS_LEFT,
	HTK_POS_RIGHT,
	HTK_POS_TOP,
	HTK_POS_BOTTOM,
} HtkPositionType;

typedef enum {
	HTK_RESPONSE_NONE,
	HTK_RESPONSE_REJECT,
	HTK_RESPONSE_ACCEPT,
	HTK_RESPONSE_DELETE_EVENT,
	HTK_RESPONSE_OK,
	HTK_RESPONSE_CANCEL,
	HTK_RESPONSE_CLOSE,
	HTK_RESPONSE_YES,
	HTK_RESPONSE_NO,
	HTK_RESPONSE_APPLY,
	HTK_RESPONSE_HELP,
} HtkResponseType;

typedef enum {
	HTK_SCROLL_NONE,
	HTK_SCROLL_JUMP,
	HTK_SCROLL_STEP_BACKWARD,
	HTK_SCROLL_STEP_FORWARD,
	HTK_SCROLL_PAGE_BACKWARD,
	HTK_SCROLL_PAGE_FORWARD,
	HTK_SCROLL_STEP_UP,
	HTK_SCROLL_STEP_DOWN,
	HTK_SCROLL_PAGE_UP,
	HTK_SCROLL_PAGE_DOWN,
	HTK_SCROLL_STEP_LEFT,
	HTK_SCROLL_STEP_RIGHT,
	HTK_SCROLL_PAGE_LEFT,
	HTK_SCROLL_PAGE_RIGHT,
	HTK_SCROLL_START,
	HTK_SCROLL_END,
} HtkScrollType;

typedef enum {
	HTK_SELECTION_NONE,
	HTK_SELECTION_SINGLE,
	HTK_SELECTION_BROWSE,
	HTK_SELECTION_MULTIPLE,
	HTK_SELECTION_EXTENDED,
} HtkSelectionMode;

typedef enum {
	HTK_SHADOW_NONE,
	HTK_SHADOW_IN,
	HTK_SHADOW_OUT,
	HTK_SHADOW_ETCHED_IN,
	HTK_SHADOW_ETCHED_OUT,
} HtkShadowType;

typedef enum {
	HTK_STATE_NORMAL,
	HTK_STATE_ACTIVE,
	HTK_STATE_PRELIGHT,
	HTK_STATE_SELECTED,
	HTK_STATE_INSENSITIVE,
} HtkStateType;

typedef enum {
	HTK_TEXT_DIR_NONE,
	HTK_TEXT_DIR_LTR,
	HTK_TEXT_DIR_RTL,
} HtkTextDirection;

typedef enum {
	HTK_TREE_VIEW_GRID_LINES_NONE,
	HTK_TREE_VIEW_GRID_LINES_HORIZONTAL,
	HTK_TREE_VIEW_GRID_LINES_VERTICAL,
	HTK_TREE_VIEW_GRID_LINES_BOTH,
} HtkTreeViewGridLines;

/**
 * @brief 窗口位置
 */
typedef enum {
	HTK_WIN_POS_NONE,
	HTK_WIN_POS_CENTER,
	HTK_WIN_POS_MOUSE,
	HTK_WIN_POS_CENTER_ALWAYS,
	HTK_WIN_POS_CENTER_ON_PARENT,
} HtkWindowPosition;

/**
 * @brief 窗口类型
 */
typedef enum {
	HTK_WINDOW_TOPLEVEL,
	HTK_WINDOW_POPUP,
	HTK_WINDOW_HIM,
	HTK_WINDOW_TOOLTIP,
} HtkWindowType;

typedef enum {
	HTK_GESTURE_SWIPE_LEFT,
	HTK_GESTURE_SWIPE_RIGHT,
	HTK_GESTURE_SWIPE_UP,
	HTK_GESTURE_SWIPE_DOWN,
	HTK_GESTURE_SWIPE_RIGHT_UP,
	HTK_GESTURE_SWIPE_LEFT_DOWN,
	HTK_GESTURE_SWIPE_RIGHT_DOWN,
	HTK_GESTURE_SWIPE_LEFT_UP,
	HTK_GESTURE_CIRCULAR_CLOCKWISE,
	HTK_GESTURE_CIRCULAR_COUNTERCLOCKWISE
} HtkGestureType;
/***************************************************************************/

typedef struct {
	gint x;
	gint y;
	gint width;
	gint height;
} HtkAllocation;

typedef struct {
	gint width;
	gint height;
} HtkRequisition;

/***************************************************************************/

typedef void (* HtkCallback) (HtkWidget * widget, gpointer user_data);

typedef gboolean (* HtkHelperbarEvent) (HdkEventKey * event,
		gpointer user_data);

typedef void (* HtkIMNotify) (HtkIMContext * context, gpointer user_data);

typedef gboolean (* HtkKeySnoopFunc) (HtkWidget * grab_widget,
		HdkEventKey * event, gpointer user_data);

typedef void (* HtkMenuPositionFunc) (HtkMenu * menu,
		gint * x, gint * y, gboolean * push_in, gpointer user_data);

typedef void (* HtkTaskListFunc) (HtkTaskList * tasklist);

/***************************************************************************/

#endif//__HTK_TYPES_H__

/* vim: set ts=8 sts=8 sw=8 noet: */
