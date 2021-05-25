#ifndef COMMON_FUN_H
#define COMMON_FUN_H

#include <QString>
#include "common_def.h"


/********************************宏定义相关**********************************/
//----水平和垂直 像素转mm
#define PIX2MM_H(x)         (pix2mm(x, ENUM_DIR_H))
#define PIX2MM_V(y)         (pix2mm(y, ENUM_DIR_V))

//----水平和垂直 mm转像素
#define MM2PIX_H(x)         (mm2pix(x, ENUM_DIR_H))
#define MM2PIX_V(y)         (mm2pix(y, ENUM_DIR_V))

//点转毫米(不分水平还是垂直)
#define DOT2MM(x)           (dot2mm(x))

//毫米转点(不分水平还是垂直)
#define MM2DOT(x)           (mm2dot(x))



/********************************接口定义相关**********************************/

/**
 * @brief charToHex
 *      描述：把两个十六进制字符一个十六进制字节
 *      'a','A'>>0xAA
 * @param H
 * @param L
 * @return
 */
char charToHex(char H,char L);

/**
  * @brief dataTypeConversion::hexStr_To_Hexchar
  * 描述：把一个十六进制字符串转化为十六进制数数组
  * "01 15 26 581512"  >>    {0x01,0x15,0x26,0x58,0x15,0x12}
  * @param data
  * @return
  */
char* hexStr_To_Hexchar(QString data);


/**
 * @brief StringToHex
 *          字符串转成十六进制实现
 * @param str
 * @param senddata
 */
void StringToHex(QString str, QByteArray &senddata);

/**
 * @brief ConvertHexChar
 *      把字符转为HEX
 * @param ch
 * @return
 */
char ConvertHexChar(char ch);

/**
 * @brief ShortInt2Char
 * 双字节整型转为单字节整型
 */
void ShortInt2Char(qint16 s, qint8 arr[2]);

/**
  * @brief ShortInt2CharEX
  * 双字节转为单字节
  * @param s:待转换的双字节
  * @param flag:取高还是低字节
  * @return
  */
quint8 ShortInt2CharEX(quint16 num, ENUM_HIGH_LOW_BYTE flag);

/**
 * @brief pix2mm
 *      像素转为毫米的水平和垂直转化倍率（保留一个小数点）
 *       例如:100pix
 *      则要确定这100pix是水平还是垂直的，如果是垂直的，则
 *      100 * PIX2MM(ENUM_PIX2MM_V);//就是这一百像素的转换结果
 * @return
 */
float pix2mm(float val_pix, ENUM_DIR_V_H_TYPE type);

/**
 * @brief mm2pix
 *      每一毫米在水平和垂直方向的像素个数
 * @param type
 * @return
 */
float mm2pix(float val_mm, ENUM_DIR_V_H_TYPE type);

/**
 * @brief dot2mm
 * 打印机的单位点转为mm,根据打印机的协议，1点=0.125mm
 * @param val
 * @return
 */
float dot2mm(float val_mm);
/**
 * @brief mm2dot
 * 毫米转为点
 * @param val
 * @return
 */
float mm2dot(float val_dot);

/**
 * @brief pix2dot
 * 像素转为点（分水平和垂直像素，其实在一般的电脑，水平和垂直差不多）
 * @param val_dot
 */
float pix2dot(float val_pix, ENUM_DIR_V_H_TYPE type);

/**
 * @brief dot2pix
 *      点转为像素（分水平和垂直像素，其实在一般的电脑，水平和垂直差不多）
 * @param val_dot
 * @param type
 */
float dot2pix(float val_dot, ENUM_DIR_V_H_TYPE type);

/**
 * @brief isChineseString
 * 判断QString中是否存在中文(GB2312)，打印机固定的是两字节的GB2312
 * @param str
 * @return: true:表示存在
 */
bool isChineseString(QString str);

/**
 * @brief textString2HEX
 * 中英文混合字符串转为HEX，英文转为ASCII，中文转为GB2312
 * @return
 */
QByteArray textString2HEX();

/**
 * @brief utf8ToGb2312
 *  utf-8是unicode的一种实现方式,utf-8转GB2312
 * @param strUtf8
 * @return
 */
QString utf8ToGb2312(char *strUtf8);

/**
 * @brief utf8ToGb2312
 *          utf-8转Gb2312
 * @param strUtf8
 */
void utf8ToGb2312(char *strUtf8, char *out);

/**
 * @brief gb2312ToUtf8
 *  gb2312转UTF-8
 * @param strGb2312
 */
void gb2312ToUtf8(QString strGb2312);

/**
 * @brief utf8Tgb2312
 * @param data
 *          utf-8转gb2312
 * @return
 */
QString utf8Tgb2312(QString data);

/**
 * @brief utf8Tgb2312
 * @param data
 *          gb2312 转utf-8
 * @return
 */
QString gb2312Tutf8(QString data);



#endif // COMMON_FUN_H
