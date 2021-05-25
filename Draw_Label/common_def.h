#ifndef COMMON_DEF_H
#define COMMON_DEF_H

#include "qstring.h"
#include "common_res.h"
#include <QMetaType>    //自定义参数类型的头文件----***
#include <QRectF>
#include <QPen>


/*
    自定义的一个全局文件，这个文件只包含基本类型的通用头文件
*/

/********************************枚举定义相关**********************************/

enum GRAPHIC_ITEM_TYPE
{
    ENUM_MIN = 0,
    ENUM_TEXT_EDIT = 1,
    ENUM_ONECODE_EDIT = 2,
    ENUM_TWOCODE_EDIT = 3,
    ENUM_PIC_EDIT = 4,
    ENUM_LINE_EDIT = 5,
    ENUM_RECT_EDIT = 6,
    //**
    ENUM_MAX
};


//线条类型
enum GRAPHIC_LINE_TYPE
{
    ENUM_GRAPHIC_LINE_MIN,
    ENUM_GRAPHIC_LINE_SOLID,         //实线
    ENUM_GRAPHIC_LINE_DUMMY,         //虚线
    //**
    ENUM_GRAPHIC_LINE_MAX
};


//字体类型类型，具体请参照 g_font_type[GRAPHIC_FONT_STYLE_MAX]变量
enum GRAPHIC_FONT_TYPE
{
    GRAPHIC_FONT_TYPE_MIN,
    GRAPHIC_FONT_TYPE_SONG,                    //宋体
    GRAPHIC_FONT_TYPE_BLACK,                   //黑体
    //**
    GRAPHIC_FONT_STYLE_MAX
};


//字体大小，只列举枚举，具体参照 common_def文件 g_font_size[GRAPHIC_FONT_SIZE_MAX]
enum GRAPHIC_FONT_SIZE
{
    GRAPHIC_FONT_SIZE_MIN,
    GRAPHIC_FONT_SIZE_TINY = 1,       //微小字号
    GRAPHIC_FONT_SIZE_SMALL = 2,
    GRAPHIC_FONT_SIZE_NORMAL = 3,
    GRAPHIC_FONT_SIZE_MEDIUM = 4,
    GRAPHIC_FONT_SIZE_LARGE = 5,
    GRAPHIC_FONT_SIZE_EXLARGE = 6,
    GRAPHIC_FONT_SIZE_HUGE = 7,
    //**
    GRAPHIC_FONT_SIZE_MAX
};

//文本字符字体高度，有效值范围为{16, 24, 32, 48, 64, 80, 96}。根据协议而定
//具体参照 common_def文件 g_text_font_size[GRAPHIC_FONT_SIZE_INDEX_MAX]
enum GRAPHIC_TEXT_FONT_HEIGHT_INDEX
{
    GRAPHIC_FONT_HEIGHT_INDEX_8,
    GRAPHIC_FONT_HEIGHT_INDEX_10,
    GRAPHIC_FONT_HEIGHT_INDEX_12,
    GRAPHIC_FONT_HEIGHT_INDEX_14,
    //以下是打印机支持的字符高度,但是发现并不是..mmp,所以在上面增加了4个，用作pc级text上显示的文本大小
    GRAPHIC_FONT_HEIGHT_INDEX_16,
    GRAPHIC_FONT_HEIGHT_INDEX_24,
    GRAPHIC_FONT_HEIGHT_INDEX_32,
    GRAPHIC_FONT_HEIGHT_INDEX_48,
    GRAPHIC_FONT_HEIGHT_INDEX_64,
    GRAPHIC_FONT_HEIGHT_INDEX_80,
    GRAPHIC_FONT_HEIGHT_INDEX_86,
    GRAPHIC_FONT_HEIGHT_INDEX_MAX
};

//字体的放大倍数,字体大小范围（11、22、33、44、55、66）,分别可以放大宽和高
enum GRAPHIC_TEXT_FONT_MAG
{
    MAG_INDEX_MIN = 0,
    MAG_INDEX_1,
    MAG_INDEX_2,
    MAG_INDEX_3,
    MAG_INDEX_4,
    MAG_INDEX_5,
    MAG_INDEX_6 ,
    MAG_INDEX_MAX
};

//文本来源类型
enum GRAPHIC_TEXT_FROM_TYPE
{
    GRAPHIC_TEXT_FROM_MIN,
    GRAPHIC_TEXT_FROM_CUSTOM,         //自定义编辑
    GRAPHIC_TEXT_FROM_OTHER,          //虚线

    //**

    GRAPHIC_TEXT_FROM_MAX
};


//一维条形码的编码方式, 参考自 BarcodeTypes 枚举类型
enum GRAPHIC_ONECODE_TYPE
{
    GRAPHIC_ONECODE_MIN,
    GRAPHIC_ONECODE_CODE11		=1,
    GRAPHIC_ONECODE_C25MATRIX	=2,
    GRAPHIC_ONECODE_C25INTER	=3,
    GRAPHIC_ONECODE_C25IATA		=4,
    GRAPHIC_ONECODE_C25LOGIC	=6,
    GRAPHIC_ONECODE_C25IND		=7,
    GRAPHIC_ONECODE_CODE39		=8,
    GRAPHIC_ONECODE_EXCODE39	=9,

    GRAPHIC_ONECODE_EANX		=13,

    GRAPHIC_ONECODE_EAN128		=16,
    GRAPHIC_ONECODE_CODABAR		=18,
    GRAPHIC_ONECODE_CODE128		=20,
    GRAPHIC_ONECODE_DPLEIT		=21,
    GRAPHIC_ONECODE_DPIDENT		=22,
    GRAPHIC_ONECODE_CODE16K		=23,
    GRAPHIC_ONECODE_CODE93		=25,
    GRAPHIC_ONECODE_FLAT		=28,
    GRAPHIC_ONECODE_RSS14		=29,
    GRAPHIC_ONECODE_RSS_LTD		=30,
    GRAPHIC_ONECODE_RSS_EXP		=31,
    GRAPHIC_ONECODE_TELEPEN		=32,
    GRAPHIC_ONECODE_UPCA		=34,
    GRAPHIC_ONECODE_UPCE		=37,        //协议不支持
    GRAPHIC_ONECODE_POSTNET		=40,
    GRAPHIC_ONECODE_MSI_PLESSEY	=47,
    GRAPHIC_ONECODE_FIM		=49,
    GRAPHIC_ONECODE_LOGMARS		=50,
    GRAPHIC_ONECODE_PHARMA		=51,
    GRAPHIC_ONECODE_PZN		=52,
    GRAPHIC_ONECODE_PHARMA_TWO	=53,
    GRAPHIC_ONECODE_PDF417		=55,
    GRAPHIC_ONECODE_PDF417TRUNC	=56,
    GRAPHIC_ONECODE_MAXICODE	=57,
    GRAPHIC_ONECODE_QRCODE		=58,
    GRAPHIC_ONECODE_CODE128B	=60,
    GRAPHIC_ONECODE_AUSPOST		=63,
    GRAPHIC_ONECODE_AUSREPLY	=66,
    GRAPHIC_ONECODE_AUSROUTE	=67,
    GRAPHIC_ONECODE_AUSREDIRECT	=68,
    GRAPHIC_ONECODE_ISBNX		=69,
    GRAPHIC_ONECODE_RM4SCC		=70,
    GRAPHIC_ONECODE_DATAMATRIX	=71,
    GRAPHIC_ONECODE_ITF14		=72,
    GRAPHIC_ONECODE_CODABLOCKF	=74,
    GRAPHIC_ONECODE_NVE18		=75,
    GRAPHIC_ONECODE_KOREAPOST	=77,
    GRAPHIC_ONECODE_RSS14STACK	=79,
    GRAPHIC_ONECODE_RSS14STACK_OMNI	=80,
    GRAPHIC_ONECODE_RSS_EXPSTACK	=81,
    GRAPHIC_ONECODE_PLANET		=82,
    GRAPHIC_ONECODE_MICROPDF417	=84,
    GRAPHIC_ONECODE_ONECODE		=85,
    GRAPHIC_ONECODE_PLESSEY		=86,

    /* TBarcodeItem 8 codes */
    GRAPHIC_ONECODE_KIX		=90,
    GRAPHIC_ONECODE_AZTEC		=92,
    GRAPHIC_ONECODE_DAFT		=93,
    GRAPHIC_ONECODE_ITALYPOST	=94,
    GRAPHIC_ONECODE_DPD		=96,
    GRAPHIC_ONECODE_MICROQR		=97,

    /* Zint specific */
    GRAPHIC_ONECODE_TELEPEN_NUM	=128,
    GRAPHIC_ONECODE_CODE32		=129,
    GRAPHIC_ONECODE_EANX_CC		=130,
    GRAPHIC_ONECODE_EAN128_CC	=131,
    GRAPHIC_ONECODE_RSS14_CC	=132,
    GRAPHIC_ONECODE_RSS_LTD_CC	=133,
    GRAPHIC_ONECODE_RSS_EXP_CC	=134,
    GRAPHIC_ONECODE_UPCA_CC		=135,
    GRAPHIC_ONECODE_UPCE_CC		=136,
    GRAPHIC_ONECODE_RSS14STACK_CC	=137,
    GRAPHIC_ONECODE_RSS14_OMNI_CC	=138,
    GRAPHIC_ONECODE_RSS_EXPSTACK_CC	=139,

    GRAPHIC_ONECODE_MAX
};


//一维条形码的编码方式的下标
enum GRAPHIC_ONECODE_TYPE_INDEX
{
    GRAPHIC_ONECODE_MIN_INDEX = 0,

    GRAPHIC_ONECODE_CODE11_INDEX		,
    GRAPHIC_ONECODE_C25MATRIX_INDEX	,
    GRAPHIC_ONECODE_C25INTER_INDEX	,
    GRAPHIC_ONECODE_C25IATA_INDEX		,
    GRAPHIC_ONECODE_C25LOGIC_INDEX	,           //5

    GRAPHIC_ONECODE_C25IND_INDEX		,
    GRAPHIC_ONECODE_CODE39_INDEX		,
    GRAPHIC_ONECODE_EXCODE39_INDEX	,
    GRAPHIC_ONECODE_EANX_INDEX		,
    GRAPHIC_ONECODE_EAN128_INDEX		,           //10


    GRAPHIC_ONECODE_CODABAR_INDEX	,               //11
    GRAPHIC_ONECODE_CODE128_INDEX		,
    GRAPHIC_ONECODE_DPLEIT_INDEX		,
    GRAPHIC_ONECODE_DPIDENT_INDEX		,
    GRAPHIC_ONECODE_CODE16K_INDEX		,

    GRAPHIC_ONECODE_CODE93_INDEX		,
    GRAPHIC_ONECODE_FLAT_INDEX		,
    GRAPHIC_ONECODE_RSS14_INDEX		,
    GRAPHIC_ONECODE_RSS_LTD_INDEX		,
    GRAPHIC_ONECODE_RSS_EXP_INDEX		,       //20


    GRAPHIC_ONECODE_TELEPEN_INDEX		,
    GRAPHIC_ONECODE_UPCA_INDEX		,
    GRAPHIC_ONECODE_UPCE_INDEX		,
    GRAPHIC_ONECODE_POSTNET_INDEX		,
    GRAPHIC_ONECODE_MSI_PLESSEY_INDEX	,

    GRAPHIC_ONECODE_FIM_INDEX		,
    GRAPHIC_ONECODE_LOGMARS_INDEX		,
    GRAPHIC_ONECODE_PHARMA_INDEX		,
    GRAPHIC_ONECODE_PZN_INDEX		,
    GRAPHIC_ONECODE_PHARMA_TWO_INDEX	,       //30


    GRAPHIC_ONECODE_PDF417_INDEX		,
    GRAPHIC_ONECODE_PDF417TRUNC_INDEX	,
    GRAPHIC_ONECODE_MAXICODE_INDEX	,
    GRAPHIC_ONECODE_QRCODE_INDEX		,
    GRAPHIC_ONECODE_CODE128B_INDEX	,

    GRAPHIC_ONECODE_AUSPOST_INDEX		,
    GRAPHIC_ONECODE_AUSREPLY_INDEX	,
    GRAPHIC_ONECODE_AUSROUTE_INDEX,
    GRAPHIC_ONECODE_AUSREDIRECT_INDEX,
    GRAPHIC_ONECODE_ISBNX_INDEX,            //40


    GRAPHIC_ONECODE_RM4SCC_INDEX,
    GRAPHIC_ONECODE_DATAMATRIX_INDEX,
    GRAPHIC_ONECODE_ITF14_INDEX,
    GRAPHIC_ONECODE_CODABLOCKF_INDEX,
    GRAPHIC_ONECODE_NVE18_INDEX,

    GRAPHIC_ONECODE_KOREAPOST_INDEX,
    GRAPHIC_ONECODE_RSS14STACK_INDEX,
    GRAPHIC_ONECODE_RSS14STACK_OMNI_INDEX,
    GRAPHIC_ONECODE_RSS_EXPSTACK_INDEX,
    GRAPHIC_ONECODE_PLANET_INDEX,               //50


    GRAPHIC_ONECODE_MICROPDF417_INDEX,
    GRAPHIC_ONECODE_ONECODE_INDEX,
    GRAPHIC_ONECODE_PLESSEY_INDEX,

    /* TBarcodeItem 8 codes */
    GRAPHIC_ONECODE_KIX_INDEX,
    GRAPHIC_ONECODE_AZTEC_INDEX,

    GRAPHIC_ONECODE_DAFT_INDEX,
    GRAPHIC_ONECODE_ITALYPOST_INDEX,
    GRAPHIC_ONECODE_DPD_INDEX,
    GRAPHIC_ONECODE_MICROQR_INDEX,


    /* Zint specific */
    GRAPHIC_ONECODE_TELEPEN_NUM_INDEX,      //60


    GRAPHIC_ONECODE_CODE32_INDEX,
    GRAPHIC_ONECODE_EANX_CC_INDEX,
    GRAPHIC_ONECODE_EAN128_CC_INDEX,
    GRAPHIC_ONECODE_RSS14_CC_INDEX,
    GRAPHIC_ONECODE_RSS_LTD_CC_INDEX,

    GRAPHIC_ONECODE_RSS_EXP_CC_INDEX,
    GRAPHIC_ONECODE_UPCA_CC_INDEX,
    GRAPHIC_ONECODE_UPCE_CC_INDEX,
    GRAPHIC_ONECODE_RSS14STACK_CC_INDEX,
    GRAPHIC_ONECODE_RSS14_OMNI_CC_INDEX,    //70

    GRAPHIC_ONECODE_RSS_EXPSTACK_CC_INDEX,                  //71

    GRAPHIC_ONECODE_MAX_INDEX
};

//一维条形码的编码方式的下拉菜单的下标
enum GRAPHIC_SELECT_INDEX
{
    SELECT_INDEX_0 = 0,
    SELECT_INDEX_1 = 1,
    SELECT_INDEX_2 = 2,
    SELECT_INDEX_3 = 3,
    SELECT_INDEX_4 = 4,
    SELECT_INDEX_6 = 5,
    SELECT_INDEX_7 = 6,
};

//一维条形码边框边框
enum GRAPHIC_ONECODE_FRAME
{
    GRAPHIC_ONECODE_FRAME_NO_BORDER = 0,    //无边框
    GRAPHIC_ONECODE_FRAME_BIND = 2,         //有
    GRAPHIC_ONECODE_FRAME_BOX = 4,
    GRAPHIC_ONECODE_FRAME_MAX
};

//二维码容错率等级,参考枚举 QRecLevel
enum GRAPHIC_TWOCODE_ECLEVEL
{
    GRAPHIC_TWOCODE_ECLEVEL_L = 0,      // lowest
    GRAPHIC_TWOCODE_ECLEVEL_M,
    GRAPHIC_TWOCODE_ECLEVEL_Q,
    GRAPHIC_TWOCODE_ECLEVEL_H           // highest
};

//二维码编码模式,参考枚举 QRencodeMode
enum GRAPHIC_TWOCODE_MODE
{
    GRAPHIC_TWOCODE_MODE_NUL = -1,   //< Terminator (NUL character). Internal use only

    GRAPHIC_TWOCODE_MODE_NUM = 0,    //< Numeric mode
    GRAPHIC_TWOCODE_MODE_AN,         //< Alphabet-numeric mode
    GRAPHIC_TWOCODE_MODE_8,          //< 8-bit data mode
    GRAPHIC_TWOCODE_MODE_KANJI,      //< Kanji (shift-jis) mode
    GRAPHIC_TWOCODE_MODE_STRUCTURE,  //< Internal use only
    GRAPHIC_TWOCODE_MODE_ECI,        //< ECI mode
    GRAPHIC_TWOCODE_MODE_FNC1FIRST,  //< FNC1, first position
    GRAPHIC_TWOCODE_MODE_FNC1SECOND, //< FNC1, second position
};

//二维码编码宽度,二维码打印的实际宽度就是由码宽控制，发现1个码宽对应二维码实际宽度为5mm
enum GRAPHIC_TWOCODE_UINTW
{
    GRAPHIC_TWOCODE_UINTW_MIN = 0,
    GRAPHIC_TWOCODE_UINTW_1 = 1,
    GRAPHIC_TWOCODE_UINTW_2 = 2,
    GRAPHIC_TWOCODE_UINTW_3 = 3,
    GRAPHIC_TWOCODE_UINTW_4 = 4,
};

/**
/** * @brief The GRAPHIC_ONECODE_UINTW enum
 * 定义条码码宽。取值范围：[1, 4]。各值定义如下：
    Width取值	多级条码单位宽度（mm）	二进制条码窄线条宽度	二进制条码宽线条宽度
        1           0.125                   0.125                   0.25
        2           0.25                    0.25                    0.50
        3           0.375                   0.375                   0.75
        4           0.50                    0.50                    1.0
/** */
enum GRAPHIC_ONECODE_UINTW
{
    GRAPHIC_ONECODE_UINTW_MIN = 0,
    GRAPHIC_ONECODE_UINTW_1 = 1,
    GRAPHIC_ONECODE_UINTW_2 = 2,
    GRAPHIC_ONECODE_UINTW_3 = 3,
    GRAPHIC_ONECODE_UINTW_4 = 4,
};



//串口标号
enum ENUM_UART_SELECT_SER
{
    ENUM_UART_SELECT_NO = 0,            //0
    ENUM_UART_SELECT_0,
    ENUM_UART_SELECT_1,
    ENUM_UART_SELECT_2,
    ENUM_UART_SELECT_3,

    //**

    ENUM_UART_SELECT_MAX
};

//串口波特率
enum ENUM_UART_BOUND
{
    ENUM_UART_BOUND_4800,
    ENUM_UART_BOUND_9600,
    ENUM_UART_BOUND_115200,
    ENUM_UART_BOUND_921600,
    ENUM_UART_BOUND_MAX
};

/********************************全局变量定义相关**********************************/
extern QString g_font_type[GRAPHIC_FONT_STYLE_MAX];
extern int g_font_size[GRAPHIC_FONT_SIZE_MAX];
extern QString g_str_onecode_type[GRAPHIC_ONECODE_MAX_INDEX + 1];
extern GRAPHIC_ONECODE_TYPE g_onecode_type_index[GRAPHIC_ONECODE_MAX_INDEX + 1];
extern QString g_uart_name[ENUM_UART_SELECT_MAX];
extern int g_uart_bound_val[ENUM_UART_BOUND_MAX];
extern int g_text_font_height[GRAPHIC_FONT_HEIGHT_INDEX_MAX];     //图元text文本字体协议支持的大小

/********************************结构体定义相关**********************************/


//文本编辑框结构体属性
struct TextItemMetaPS
{
    QString name;                   //item的名字
    QString dataString;             //文本内容
    GRAPHIC_TEXT_FONT_HEIGHT_INDEX height;       //字符高度,请参考 g_text_font_height
    bool isbold;                    //true：粗体 b0
    bool isunderline;               //true：下划线,b1
    bool inverse_white;             //true：反白标志位，置 1 位图反白打印，清零正常打印b2
    int rotate;                     //b4:旋转标志位： 0 旋转 0° ； 1 旋转 90°；
    GRAPHIC_TEXT_FONT_MAG mag_w;    //字体宽度放大倍数 [11:8]
    GRAPHIC_TEXT_FONT_MAG mag_h;    //字体高度放大倍数 [15:12]
    QRectF viewRect;                //绘画的范围：左上角坐标(场景坐标)和文本整体宽高
    QRectF CoordRect;                   //图形的坐标和宽以及高
};

//一维码编辑框结构体属性
struct OneCodeItemMetaPS
{
    QString name;                       //item的名字
    QString dataString;                 //一维码内容字符串
    GRAPHIC_ONECODE_TYPE_INDEX type;    //编码类型对应的索引!!!根据索引 g_onecode_type_index[索引值] 能找到具体类型
    GRAPHIC_ONECODE_FRAME frame_type;
    bool display_boundframe;            //true，显示boundrect外接矩形框，方便了解实际的绘画范围,false,不显示
    qreal display_height;               //实际的一维码并不一定会占据 viewRect 的整个高度，这里是其显示的高度
    GRAPHIC_ONECODE_UINTW uintw;        //编码宽 取值[1, 4]
    qint16 rotate;                      //0:不旋转 [0, 3],0	条码不旋转绘制。1	条码旋转 90°绘制。2	条码旋转 180°绘制。3	条码旋转 270°绘制。
    qint16 sec_level;                   //安全等级
    QRectF viewRect;                    //绘画的范围：左上角坐标(场景坐标)和宽高
    QRectF CoordRect;                   //图形的坐标和宽以及高
};

//二维码编辑框结构体属性
struct TwoCodeItemMeta
{
    QString name;                       //item的名字
    QString dataString;                 //二维码内容字符串
    GRAPHIC_TWOCODE_ECLEVEL ecl;        //二维码容错率
    GRAPHIC_TWOCODE_MODE mode;          //二维码模式
    QRectF viewRect;                    //绘画的范围：左上角坐标(场景坐标)和宽高
    QRectF CoordRect;                   //图形的坐标和宽以及高
    bool display_boundframe;            //是否显示拉伸点
    GRAPHIC_TWOCODE_UINTW uintw;        //二维码码宽,
};

//矩形编辑框结构体属性
struct RectItemMeta
{
    QString name;                       //item的名字
    QPen pen;                           //画笔
    QRectF viewRect;                    //绘画的范围：左上角坐标(场景坐标)和宽高
    QRectF CoordRect;                   //图形的坐标和宽以及高
    bool display_boundframe;            //true，显示红色拉伸点
};

//画板label的结构体
struct LabelPanelMeta
{
    QString name;                       //画板和标签名字
    QRectF labelRect;                   //画板label的左上角坐标以及宽和高
    QRectF viewRect;                    //画板view的左上角坐标以及宽和高
    QRectF sceneRect;                   //画板scene的左上角坐标以及宽和高
    int scal_num;                       //放大缩小倍数(view和scene)
    QPointF tr_p;                       //坐标系平移(view和scene)
    qreal angle;                        //旋转角度(view和scene)
    int item_num;                       //图元个数(scene)
};

//直线编辑框结构体属性
struct LineItemMetaPS
{
    QString name;                      //名字
    bool display_boundframe;            //true，显示红色拉伸点
    QPointF xy_offset;                 //直线图元本身的原点偏移，暂时不使用
    qreal rotate;                      //直线基于坐标原点旋转的角度
    QPen pen;                          //画笔,包括了线条/画笔的宽度
    qreal len;                         //直线长度
    QPointF start_point;               //起始点
    QPointF end_point;                 //终止点
    QRectF viewRect;                   //绘画的范围：左上角坐标(场景坐标)和宽高
    QRectF CoordRect;                  //图形的坐标和宽以及高
};

//双字节 取 高低字节标记
enum ENUM_HIGH_LOW_BYTE
{
    ENUM_LOW_BYTE = 0,          //取低字节
    ENUM_HIGH_BYTE = 1,         //取高字节
    //**
    ENUM_BYTE_MAX
};


//TAB META属性框选项卡下标
enum ENUM_CENTRAL_TAB_META_INDEX
{
    TAB_META_INDEX_ATTR = 0,
    TAB_META_INDEX_UART = 1,
    TAB_META_INDEX_MANGER = 2,
    //**
    TAB_META_INDEX_MAX
};


//水平、垂直方向
enum ENUM_DIR_V_H_TYPE
{
    ENUM_DIR_H = 0,
    ENUM_DIR_V = 1,
};

#endif // COMMON_DEF_H
