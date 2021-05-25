#include "common_def.h"
#include <QMetaType>                            //自定义参数类型的头文件----***

/********************************全局定义相关**********************************/
QString g_font_type[GRAPHIC_FONT_STYLE_MAX] =
{
    "",              //GRAPHIC_FONT_TYPE_MIN
    "宋体"            //GRAPHIC_FONT_TYPE_SONG
    "黑体"            //GRAPHIC_FONT_TYPE_BLACK
};


//g_font_size
int g_font_size[GRAPHIC_FONT_SIZE_MAX] =
{
    6, //GRAPHIC_FONT_SIZE_MIN
    8, //GRAPHIC_FONT_SIZE_TINY
    12,//GRAPHIC_FONT_SIZE_SMALL
    16,//GRAPHIC_FONT_SIZE_NORMAL =
    20,//GRAPHIC_FONT_SIZE_MEDIUM =
    24,//GRAPHIC_FONT_SIZE_LARGE =
    28,//GRAPHIC_FONT_SIZE_EXLARGE =
    32,//GRAPHIC_FONT_SIZE_HUGE =
};

//g_font_size
//文本字符字体高度，有效值范围为{16, 24, 32, 48, 64, 80, 96}。根据协议而定
int g_text_font_height[GRAPHIC_FONT_HEIGHT_INDEX_MAX] =
{
    8,
    10,
    12,
    14,
    16, //GRAPHIC_FONT_SIZE_MIN
    24, //GRAPHIC_FONT_SIZE_TINY
    32,//GRAPHIC_FONT_SIZE_SMALL
    48,//GRAPHIC_FONT_SIZE_NORMAL =
    64,//GRAPHIC_FONT_SIZE_MEDIUM =
    80,//GRAPHIC_FONT_SIZE_LARGE =
    96,//GRAPHIC_FONT_SIZE_EXLARGE =
};
//一维条形码编码类型字符串数组
QString g_str_onecode_type[GRAPHIC_ONECODE_MAX_INDEX + 1] =
{
    "min",               //0
    "CODE11",
    "C25MATRIX",
    "C25INTER",
    "C25IATA",
    "C25LOGIC",         //5
    "C25IND",
    "CODE39",
    "EXCODE39",
    "EANX",
    "EAN128",           //10


    "CODABAR",
    "CODE128",
    "DPLEIT",
    "DPIDENT",
    "CODE16K",          //15

    "CODE93",
    "FLAT",
    "RSS14",
    "RSS_LTD",
    "RSS_EXP",          //20


    "TELEPEN",
    "UPCA",
    "UPCE",
    "POSTNET",
    "MSI_PLESSEY",      //25

    "FIM",
    "LOGMARS",
    "PHARMA",
    "PZN",
    "PHARMA_TWO",       //30

    "PDF417",
    "PDF417TRUNC",
    "MAXICODE",
    "QRCODE",
    "CODE128B",
    "AUSPOST",
    "AUSREPLY",
    "AUSROUTE",
    "AUSREDIRECT",
    "ISBNX",            //40

    "RM4SCC",
    "DATAMATRIX",
    "ITF14",
    "CODABLOCKF",
    "NVE18",
    "KOREAPOST",
    "RSS14STACK",
    "RSS14STACK_OMNI",
    "RSS_EXPSTACK",
    "PLANET",       //50

    "MICROPDF417",
    "ONECODE",
    "PLESSEY",
    "KIX",
    "AZTEC",

    "DAFT",
    "ITALYPOST",
    "DPD",
    "MICROQR",
    "TELEPEN_NUM",       //60


    "CODE32",
    "EANX_CC",
    "EAN128_CC",
    "RSS14_CC",
    "RSS_LTD_CC",

    "RSS_EXP_CC",
    "UPCA_CC",
    "UPCE_CC",
    "RSS14STACK_CC",
    "RSS14_OMNI_CC",            //70

    "RSS_EXPSTACK_CC"           //71
    "max"
};


//以数组下标的方式返回类型
GRAPHIC_ONECODE_TYPE g_onecode_type_index[GRAPHIC_ONECODE_MAX_INDEX + 1] =
{
    GRAPHIC_ONECODE_MIN,
    GRAPHIC_ONECODE_CODE11	,
    GRAPHIC_ONECODE_C25MATRIX,
    GRAPHIC_ONECODE_C25INTER,
    GRAPHIC_ONECODE_C25IATA	,
    GRAPHIC_ONECODE_C25LOGIC,
    GRAPHIC_ONECODE_C25IND	,
    GRAPHIC_ONECODE_CODE39	,
    GRAPHIC_ONECODE_EXCODE39,

    GRAPHIC_ONECODE_EANX,

    GRAPHIC_ONECODE_EAN128,
    GRAPHIC_ONECODE_CODABAR	,
    GRAPHIC_ONECODE_CODE128	,
    GRAPHIC_ONECODE_DPLEIT,
    GRAPHIC_ONECODE_DPIDENT,
    GRAPHIC_ONECODE_CODE16K	,
    GRAPHIC_ONECODE_CODE93	,
    GRAPHIC_ONECODE_FLAT,
    GRAPHIC_ONECODE_RSS14,
    GRAPHIC_ONECODE_RSS_LTD,
    GRAPHIC_ONECODE_RSS_EXP,
    GRAPHIC_ONECODE_TELEPEN,
    GRAPHIC_ONECODE_UPCA,
    GRAPHIC_ONECODE_UPCE,
    GRAPHIC_ONECODE_POSTNET	,
    GRAPHIC_ONECODE_MSI_PLESSEY,
    GRAPHIC_ONECODE_FIM,
    GRAPHIC_ONECODE_LOGMARS,
    GRAPHIC_ONECODE_PHARMA,
    GRAPHIC_ONECODE_PZN,
    GRAPHIC_ONECODE_PHARMA_TWO,
    GRAPHIC_ONECODE_PDF417,
    GRAPHIC_ONECODE_PDF417TRUNC,
    GRAPHIC_ONECODE_MAXICODE,
    GRAPHIC_ONECODE_QRCODE,
    GRAPHIC_ONECODE_CODE128B,
    GRAPHIC_ONECODE_AUSPOST,
    GRAPHIC_ONECODE_AUSREPLY,
    GRAPHIC_ONECODE_AUSROUTE,
    GRAPHIC_ONECODE_AUSREDIRECT,
    GRAPHIC_ONECODE_ISBNX,
    GRAPHIC_ONECODE_RM4SCC,
    GRAPHIC_ONECODE_DATAMATRIX,
    GRAPHIC_ONECODE_ITF14,
    GRAPHIC_ONECODE_CODABLOCKF,
    GRAPHIC_ONECODE_NVE18,
    GRAPHIC_ONECODE_KOREAPOST,
    GRAPHIC_ONECODE_RSS14STACK,
    GRAPHIC_ONECODE_RSS14STACK_OMNI,
    GRAPHIC_ONECODE_RSS_EXPSTACK,
    GRAPHIC_ONECODE_PLANET,
    GRAPHIC_ONECODE_MICROPDF417,
    GRAPHIC_ONECODE_ONECODE,
    GRAPHIC_ONECODE_PLESSEY,

    /* TBarcodeItem 8 codes */
    GRAPHIC_ONECODE_KIX,
    GRAPHIC_ONECODE_AZTEC,
    GRAPHIC_ONECODE_DAFT,
    GRAPHIC_ONECODE_ITALYPOST,
    GRAPHIC_ONECODE_DPD,
    GRAPHIC_ONECODE_MICROQR,

    /* Zint specific */
    GRAPHIC_ONECODE_TELEPEN_NUM,
    GRAPHIC_ONECODE_CODE32,
    GRAPHIC_ONECODE_EANX_CC,
    GRAPHIC_ONECODE_EAN128_CC,
    GRAPHIC_ONECODE_RSS14_CC,
    GRAPHIC_ONECODE_RSS_LTD_CC,
    GRAPHIC_ONECODE_RSS_EXP_CC,
    GRAPHIC_ONECODE_UPCA_CC,
    GRAPHIC_ONECODE_UPCE_CC,
    GRAPHIC_ONECODE_RSS14STACK_CC,
    GRAPHIC_ONECODE_RSS14_OMNI_CC,
    GRAPHIC_ONECODE_RSS_EXPSTACK_CC,

    GRAPHIC_ONECODE_MAX
};

//以上位机一维码类型的方式返回打印机对应的一维码类型（做一个映射关系）
//标识条码类型，取值范围：[0,29]。各值定义如下：
//目前在上位机一维码库里，只有下面这些编码方式 在 协议也是存在的，暂时只加这些
//可以直接把协议编码方式全搞出来，直接传到打印机，只要打印机支持即OK
//GRAPHIC_ONECODE_TYPE g_onecode_type_ps[GRAPHIC_ONECODE_MAX_INDEX + 1] =
//{
//    GRAPHIC_ONECODE_UPCA = 0,       //0	UPC-A	11	48-57
//    GRAPHIC_ONECODE_CODE39 = 4,     //4	CODE39	1-	48-57,65-90,32,36,37,43,45,46,47
//    GRAPHIC_ONECODE_CODABAR  = 6,   //6	CODABAR 	1-	48-57,65-68,36,43,45,46,47,58
//    GRAPHIC_ONECODE_CODE93 = 7,
//    GRAPHIC_ONECODE_CODE128 = 8,
//    GRAPHIC_ONECODE_CODE11 = 9,
//    GRAPHIC_ONECODE_EAN128 = 12
//};


//串口名字文本 参考枚举 ENUM_UART_SELECT_SER
QString g_uart_name[ENUM_UART_SELECT_MAX] =
{
    "select",
    "uart0",
    "uart1",
    "uart2",
    "uart3",
};

//串口波特率 参考枚举 ENUM_UART_BOUND
int g_uart_bound_val[ENUM_UART_BOUND_MAX] =
{
    4800,
    9600,
    115200,
    921600,
};




/********************************结构体定义相关**********************************/


