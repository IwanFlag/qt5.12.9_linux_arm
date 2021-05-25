#ifndef COMMON_RES_H
#define COMMON_RES_H

/*
    自定义的一个公共资源文件,禁止在这个头文件包含任何头文件，这个文件只能被包含
*/
/********************************宏定义相关**********************************/

/********************************宏定义相关**********************************/
//-----坐标宽高值等定义
//主界面宽高(毫米)
#define WIDGET_MAIN_WIDE_MM        200
#define WIDGET_MAIN_HEGIHT_MM      100


//拉伸矩形的半径,也就是宽/高的（毫米）
#define ITEM_PULL_RECT_LEN_MM         1 //mm


//----图元 item 初始化范围,分别是 left top width height
//text
//#define GRAPHICS_TEXT_ITEM_RECT         0,0,500,30

#define TEXT_ITEM_X_MM      0
#define TEXT_ITEM_Y_MM      0
#define TEXT_ITEM_W_MM      100
#define TEXT_ITEM_H_MM      10


//条码默认参数（毫米）
#define ONECODE_ITEM_HEIGHT_DEFAULT_MM              7 //默认高度,宽度用户不可编辑,由代码自己计算


//二维码默认参数（毫米）
#define GRAPHICS_TWOCODE_ITEM_BOUNDRECT      0,0,50,50


//矩形默认参数（毫米）
#define RECT_ITEM_PEN_WIDTH_MM        1

#define RECT_ITEM_BOUNDRECT_X_MM      0
#define RECT_ITEM_BOUNDRECT_Y_MM      0
#define RECT_ITEM_BOUNDRECT_W_MM      5
#define RECT_ITEM_BOUNDRECT_H_MM      5


//直线默认参数(毫米)
#define LINE_ITEM_PEN_WIDTH_MM          1
#define LINE_ITEM_PEN_LEN_MM            10


//主界面标题
#define WIDGET_MAIN_TITLE       "DrawLabel"


//主菜单项名字
#define WIDGET_MAIN_MENU_BAR_FILE "File"                //文件
#define WIDGET_MAIN_MENU_BAR_EDIT "Edit"                //编辑
#define WIDGET_MAIN_MENU_BAR_TOOL "Tool"                //工具
#define WIDGET_MAIN_MENU_BAR_HELP "Help"                //编辑
#define WIDGET_MAIN_MENU_BAR_LANGUAGE "Language"        //语言


//Edit菜单子项的名字
#define WIDGET_MAIN_MENU_EDIT_TEXT "Text"
#define WIDGET_MAIN_MENU_EDIT_ONECODE "OneCode"
#define WIDGET_MAIN_MENU_EDIT_TWOCODE "TwoCode"
#define WIDGET_MAIN_MENU_EDIT_PIC "Picture"
#define WIDGET_MAIN_MENU_EDIT_LINE "Line"
#define WIDGET_MAIN_MENU_EDIT_RECT "Rect"


//工具菜单子项的名字
#define WIDGET_MAIN_MENU_TOOL_NEW "New"
#define WIDGET_MAIN_MENU_TOOL_OPEN "Open"
#define WIDGET_MAIN_MENU_TOOL_SAVE "Save"
#define WIDGET_MAIN_MENU_TOOL_PRINT "Print"
#define WIDGET_MAIN_MENU_TOOL_TEMPLATE "Template"
#define WIDGET_MAIN_MENU_TOOL_REPEAL "Repeal"
#define WIDGET_MAIN_MENU_TOOL_RECOVER "Recover"
#define WIDGET_MAIN_MENU_TOOL_REMOVE "Remove"
#define WIDGET_MAIN_MENU_TOOL_REMOVEALL "RemoveAll"



//language
#define MAIN_MENU_LANG_ZH "Chinese"
#define MAIN_MENU_LANG_EN "English"


//状态栏相关
#define WIDGET_MAIN_STATUS_BAR_FONT_SIZE 12



//central区域的工具菜单子项的名字
#define WIDGET_MAIN_CENTRAL_TOOL_TEXTEDIT "TextEdit"
#define WIDGET_MAIN_CENTRAL_TOOL_ONECODE "Onecode"
#define WIDGET_MAIN_CENTRAL_TOOL_TWOCODE "TwoCode"
#define WIDGET_MAIN_CENTRAL_TOOL_SELFPIC "Picture"
#define WIDGET_MAIN_CENTRAL_TOOL_LINE "LineEdit"
#define WIDGET_MAIN_CENTRAL_TOOL_RECT "RectEdit"
#define WIDGET_MAIN_CENTRAL_TOOL_INVALID "InvalidItem"



//-----图片ICON
//tool_icon
#define MAIN_NEW_ACTION_PNG      ":/icon/tool_icon/new.png"
#define MAIN_OPEN_ACTION_PNG      ":/icon/tool_icon/open.png"
#define MAIN_PRINT_ACTION_PNG      ":/icon/tool_icon/print.png"
#define MAIN_RECOVER_ACTION_PNG      ":/icon/tool_icon/recover.png"
#define MAIN_REPEAL_ACTION_PNG      ":/icon/tool_icon/repeal.png"
#define MAIN_SAVE_ACTION_PNG      ":/icon/tool_icon/save.png"
#define MAIN_TEMPLATE_ACTION_PNG      ":/icon/tool_icon/templateset.png"


//template_icon
#define MAIN_TEMPLATE_LINE_PNG      ":/icon/template_icon/line.png"
#define MAIN_TEMPLATE_ONECODE_PNG      ":/icon/template_icon/onecode.png"
#define MAIN_TEMPLATE_RECT_PNG      ":/icon/template_icon/rect.png"
#define MAIN_TEMPLATE_SELFPIC_PNG      ":/icon/template_icon/selfpic.png"
#define MAIN_TEMPLATE_TEXTEDIT_PNG      ":/icon/template_icon/textedit.png"
#define MAIN_TEMPLATE_TWOCODE_PNG      ":/icon/template_icon/twocode.png"


//-----颜色样式表字符串
#define COLOR_STYLE_LIGHT_WGRAY "background-color: rgb(245, 245, 245)"  //浅白灰色
#define COLOR_STYLE_LIGHT_GRAY "background-color: rgb(220, 220, 220)"  //浅灰色
#define COLOR_STYLE_GRAY "background-color: rgb(192, 192, 192)"  //灰色

#define COLOR_STYLE_BLACK "background-color: rgb(0, 0, 0)"  //黑色


#define BG_COLOR_STYLE_LIGHT_WGRAY "background-color: rgb(245, 245, 245)"  //浅白灰色
#define BG_COLOR_STYLE_LIGHT_GRAY "background-color: rgb(220, 220, 220)"  //浅灰色
#define BG_COLOR_STYLE_GRAY "background-color: rgb(192, 192, 192)"  //灰色
#define BG_COLOR_STYLE_WHITE "background-color: rgb(255, 255, 255)"  //白色
#define BG_COLOR_STYLE_BLACK "background-color: rgb(0, 0, 0)"  //黑色
#define BG_COLOR_STYLE_KHAKI "background-color: rgb(255, 246, 143)"  //鹅黄
#define BG_COLOR_STYLE_Cyan "background-color: rgb(0, 255, 255)"  //鲜艳蓝色


//-----字符串:(STR_控件名_字符含义)
#define STR_MAIN_MENU_FILE                              "File"
#define STR_TEXT_EDIT_WRITE_HERE                        "write here"
#define STR_TEXT_EDIT_FONT_SONG                         "song"
#define STR_TEXT_EDIT_FONT_BLACK                        "black"

//字体大小字符串
#define STR_TEXT_EDIT_FONT_SIZE_TINY_                        "tiny"
#define STR_TEXT_EDIT_FONT_SIZE_SMALL_                        "small"
#define STR_TEXT_EDIT_FONT_SIZE_NORMAL_                        "normal"
#define STR_TEXT_EDIT_FONT_SIZE_MID_                        "medium"
#define STR_TEXT_EDIT_FONT_SIZE_LARGE_                        "large"
#define STR_TEXT_EDIT_FONT_SIZE_EXLAR_                        "exlarge"
#define STR_TEXT_EDIT_FONT_SIZE_HUGE_                        "huge"


//label
#define STR_DRAW_LABEL                                 "DrawLabel"
#define STR_DRAW_LABEL_META                                 "LabelPanelMeta"
#define STR_DRAW_LABEL_META_NAME                                 "name"
#define STR_DRAW_LABEL_META_RECT                                 "labelRect"
#define STR_DRAW_LABEL_META_V                                 "viewRect"
#define STR_DRAW_LABEL_META_S                                 "sceneRect"






//二维码容错率字符串
#define STR_TWOCODE_ECL_LOW                                 "low"
#define STR_TWOCODE_ECL_MEDIUM                                 "medium"
#define STR_TWOCODE_ECL_QUALITY                                "quality"
#define STR_TWOCODE_ECL_HIGH                               "high"

//二维码 mode字符串
#define STR_TWOCODE_MODE_NUM            "Numeric"       //< Numeric mode
#define STR_TWOCODE_MODE_AN             "Alphabet"      //< Alphabet-numeric mode
#define STR_TWOCODE_MODE_8              "8-bit"         //< 8-bit data mode
#define STR_TWOCODE_MODE_KANJI          "Kanji"         //< Kanji (shift-jis) mode
#define STR_TWOCODE_MODE_STRUCTURE      "Internal"      //< Internal use only) mode
#define STR_TWOCODE_MODE_ECI            "ECI"           //< ECI mode
#define STR_TWOCODE_MODE_FNC1FIRST      "FNC1_first"          //< FNC1, first position
#define STR_TWOCODE_MODE_FNC1SECOND     "FNC1_second"//< FNC1, second position



//串口字符串
#define STR_UART_TITLE     "UART"
#define STR_UART_OPEN       "Open"
#define STR_UART_CLOSE       "Close"
#define STR_UART_SEARCH       "Search"


//文件目录相关
#define SAVE_DIR_NAME       "out/"                                              //输出目录名字
#define SAVE_DIR_PATH       "./"                                                //输出目录的路径


#define SAVE_UART_DATA_FILE_NAME       "uartData"                           //输出串口文件的名字


//TEXT
#define STR_TEXT_ITEM_META       "TextItemMetaPS"
#define STR_TEXT_ITEM_META_NAME       "name"
#define STR_TEXT_ITEM_DATA       "dataString"
#define STR_TEXT_ITEM_HEIGHT       "height"
#define STR_TEXT_ITEM_BOLD       "isbold"
#define STR_TEXT_ITEM_UNDERLINE       "isunderline"
#define STR_TEXT_ITEM_ROTATE       "rotate"
#define STR_TEXT_ITEM_MAGW       "mag_w"
#define STR_TEXT_ITEM_MAGH       "mag_h"
#define STR_TEXT_ITEM_VR       "viewRect"
#define STR_TEXT_ITEM_CR       "CoordRect"


//ONECODE
#define STR_OC_ITEM_META            "OneCodeItemMetaPS"
#define STR_OC_ITEM_META_NAME       "name"
#define STR_OC_ITEM_DATA            "dataString"
#define STR_OC_ITEM_TYPE          "type"
#define STR_OC_ITEM_FRAME_TYPE            "frame_type"
#define STR_OC_ITEM_DBF                     "display_boundframe"
#define STR_OC_ITEM_DHEIGHT       "display_height"
#define STR_OC_ITEM_UINTW                       "uintw"
#define STR_OC_ITEM_ROTATE       "rotate"
#define STR_OC_ITEM_SEC_LEVEL       "sec_level"
#define STR_OC_ITEM_VR                  "viewRect"
#define STR_OC_ITEM_CR                      "CoordRect"


//TWOCODE
#define STR_TC_ITEM_META            "TwoCodeItemMeta"
#define STR_TC_ITEM_META_NAME       "name"
#define STR_TC_ITEM_DATA            "dataString"
#define STR_TC_ITEM_ECL             "ecl"
#define STR_TC_ITEM_MODE            "mode"
#define STR_TC_ITEM_UINTW           "uintw"
#define STR_TC_ITEM_DBF           "display_boundframe"
#define STR_TC_ITEM_VR              "viewRect"
#define STR_TC_ITEM_CR              "CoordRect"


//LINE
#define STR_LINE_ITEM_META            "LineItemMetaPS"
#define STR_LINE_ITEM_META_NAME            "name"
#define STR_LINE_ITEM_META_DBF            "display_boundframe"
#define STR_LINE_ITEM_META_XYOFFSET    "xy_offset"
#define STR_LINE_ITEM_META_ROTATE            "rotate"
#define STR_LINE_ITEM_META_PEN            "pen"
#define STR_LINE_ITEM_META_LEN            "len"
#define STR_LINE_ITEM_META_SP           "start_point"
#define STR_LINE_ITEM_META_EP            "end_point"
#define STR_LINE_ITEM_VR                  "viewRect"
#define STR_LINE_ITEM_CR                      "CoordRect"


//RECT
#define STR_RECT_ITEM_META            "RectItemMeta"
#define STR_RECT_ITEM_META_NAME       "name"
#define STR_RECT_ITEM_META_PEN        "pen"
#define STR_RECT_ITEM_META_VR         "viewRect"
#define STR_RECT_ITEM_META_CR         "CoordRect"
#define STR_RECT_ITEM_META_DBF        "display_boundframe"

#define STR_FILE_UNSAVE_FLAG        "*"


/********************************结构体定义相关**********************************/





#endif // COMMON_RES_H
