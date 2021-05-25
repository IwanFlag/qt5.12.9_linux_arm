#include "common_fun.h"
#include "common_def.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>
#include <QTextCodec>


/**
 * @brief charToHex
 *      描述：把两个十六进制字符一个十六进制字节
 *      'a','A'>>0xAA
 * @param H
 * @param L
 * @return
 */
char charToHex(char H,char L)
{
  if((H >= '0') && (H <= '9'))
    H-='0';
  else if((H >= 'A') && (H <= 'F'))
    H=H-'A'+10;
  else H='*';

  if((L >= '0') && (L <= '9'))
    L-='0';
  else if((L >= 'A') && (L <= 'F'))
    L=L-'A'+10;
  else L='*';
  return ((H&0x0F)<<4)|(L&0x0F);
}

/**
  * @brief dataTypeConversion::hexStr_To_Hexchar
  * 描述：把一个十六进制字符串转化为十六进制数数组
  * "01 15 26 581512"  >>    {0x01,0x15,0x26,0x58,0x15,0x12}
  * !!!!!注意，这个有点问题，先废弃不使用，用 StringToHex这个接口
  * @param data
  * @return
  */
char* hexStr_To_Hexchar(QString data)
{
    //"19885984ac418df"
    static char re[200];

    for(int re_num=0;re_num<200;re_num++)
    {
        re[re_num]=0;
    }

    int Lenth,cnt=0;
    data.remove(' ');    //删除字符串中的空格
    data=data.toUpper();
    Lenth=data.length();   //获取长度

    if(Lenth%2==1)
    {
        data+="0";
        Lenth++;
    }

    std::string ch = data.toStdString();
    const char*p = ch.c_str();
    char high = 0, low = 0;
    int i=0;

    for (cnt=0; cnt<Lenth; cnt+=2)
    {
        high = p[cnt];
        low = p[cnt+1];
        re[i++]=charToHex(high,low);
    }
    return re;
}


/**
 * @brief StringToHex
 *          16进制字符串转成十六进制实现
 * @param str
 * @param senddata
 */
void StringToHex(QString str, QByteArray &senddata)
{

    int hexdata,lowhexdata;

    int hexdatalen = 0;

    int len = str.length();

    senddata.resize(len/2);

    char lstr,hstr;

    for(int i=0; i<len; )
    {
        //char lstr,
        hstr=str[i].toLatin1();
        if(hstr == ' ')
        {
            i++;
            continue;
        }
        i++;
        if(i >= len)
           break;
        lstr = str[i].toLatin1();
        hexdata = ConvertHexChar(hstr);
        lowhexdata = ConvertHexChar(lstr);
        if((hexdata == 16) || (lowhexdata == 16))
            break;
        else
            hexdata = hexdata*16+lowhexdata;
        i++;
        senddata[hexdatalen] = (char)hexdata;
        hexdatalen++;
    }
    senddata.resize(hexdatalen);
}


/**
  * @brief dataTypeConversion::hexStr_To_Hexchar
  * 描述：把一个十六进制字符 转化 为十六进制字符串
  * {0x01,0x15,0x26,0x58,0x15,0x12} >> "01 15 26 581512"
  * @param data
  * @return
  */
QString HexToString(QByteArray data)
{
    QString str;

    for(int i = 0; i < data.size(); i++)
    {
        str = str.append(QString::number(data.at(i), 16));
    }
    return str;
}

/**
 * @brief ConvertHexChar
 *      把字符转为HEX
 * @param ch
 * @return
 */
char ConvertHexChar(char ch)
{
   if((ch >= '0') && (ch <= '9'))
            return ch-0x30;
        else if((ch >= 'A') && (ch <= 'F'))
           return ch-'A'+10;
        else if((ch >= 'a') && (ch <= 'f'))
            return ch-'a'+10;
        else return (-1);
}

/**
 * @brief ShortInt2Char
 * 双字节转为单字节
 */
void ShortInt2Char(qint16 s, qint8 arr[2])
{
    arr[0] = 0x00FF & s;            //低位字节
    arr[1] = (0xFF00 & s) >> 8;     //高位字节
}

/**
  * @brief ShortInt2CharEX
  * 双字节转为单字节
  * @param s:待转换的双字节
  * @param flag:取高还是低字节
  * @return
  */
quint8 ShortInt2CharEX(quint16 num, ENUM_HIGH_LOW_BYTE flag)
{
    quint8 arr[2] = {0x00};
    arr[0] = (quint8)(0x00FF & num);            //低位字节
    arr[1] = (0xFF00 & num) >> 8;              //高位字节

//    if(num >= 0x00FF)
//    {
//        arr[0] = (num - 0xFF00);               //低位字节
//    }
//    else
//    {
//        arr[0] = 0x00;              //低位字节
//    }


//    if(num >= 0x00FF)
//    {
//        arr[1] = (num - 0x00FF) >> 8;              //高位字节
//    }
//    else
//    {
//        arr[1] = 0x00;              //高位字节
//    }


    //qDebug("[common_fun--%s]>>num:%d,[%d,%d],%d", __FUNCTION__, num, arr[0], arr[1], flag);
    return arr[flag];
}

/**
 * @brief pix2mm
 *      每个像素多少毫米
 *      像素转为毫米的水平和垂直转化倍率（必须保留3个小数点）
 *       例如:100pix
 *      则要确定这100pix是水平还是垂直的，如果是垂直的，则
 *      100 * PIX2MM(ENUM_PIX2MM_V);//就是这一百像素的转换结果
 * @return
 */
float pix2mm(float val_pix, ENUM_DIR_V_H_TYPE type)
{
     QDesktopWidget* desk_top = QApplication::desktop();
//     qDebug()<<"屏幕的物理宽 = "<<QDesktopWidget().widthMM ()<<"mm";
//     qDebug()<<"屏幕的物理高 = "<<QDesktopWidget().heightMM()<<"mm";
//     qDebug()<<"屏幕的分辨率宽 = "<<desk_top->width();
//     qDebug()<<"屏幕的分辨率高 = "<<desk_top->height();


//     float p2mmX = (QDesktopWidget().widthMM()) / ((desk_top->width()) *1.0);    //每个像素水平宽度
//     float p2mmY = (QDesktopWidget().heightMM()) / ((desk_top->height()) *1.0);  //每个像素水平高度
//     qDebug()<<"屏幕每个像素水平为多少毫米的 p2mmX = "<<p2mmX;
//     qDebug()<<"屏幕每个像素垂直为多少毫米的 p2mmY = "<<p2mmY;
    float p2mmX =  25.4 / QDesktopWidget().logicalDpiX();
    float p2mmY = 25.4 /QDesktopWidget().logicalDpiY();
    //qDebug("[common_fun--%s]>>[p2mmX:%f,p2mmY:%f]", __FUNCTION__, p2mmX, p2mmY);
     //先获取在不同的分辨率下的每一英寸的横纵像素个数
    //float dpiX = QApplication::primaryScreen()->physicalDotsPerInchX();
    //float dpiY = QApplication::primaryScreen()->physicalDotsPerInchY();

    //每一英寸是25.4mm，然后算出每个像素的 水平和垂直各占有多少mm
    //float x_p2mm = 1.0 / dpiX*25.4;
    //float y_p2mm = 1.0 / dpiY*25.4;
     //qDebug("type:%d",type);

    if(type)
    {
        //qDebug("aaa,%f", p2mmY);
        return val_pix * p2mmY;
    }
    else
    {
        //qDebug("bbbb,%f", p2mmX);
        return val_pix * p2mmX;
    }
}

/**
 * @brief mm2pix
 *      每一毫米在水平和垂直方向的像素个数
 * @param type
 * @return
 */
float mm2pix(float val_mm, ENUM_DIR_V_H_TYPE type)
{
    QDesktopWidget* desk_top = QApplication::desktop();
//    qDebug()<<"屏幕的物理宽 = "<<QDesktopWidget().widthMM ()<<"mm";
//    qDebug()<<"屏幕的物理高 = "<<QDesktopWidget().heightMM()<<"mm";
//    qDebug()<<"屏幕的分辨率宽 = "<<desk_top->width();
//    qDebug()<<"屏幕的分辨率高 = "<<desk_top->height();


//    float mm2pX = (desk_top->width()/(QDesktopWidget().widthMM()) * 1.0 );    //每个像素水平宽度
//    float mm2pY = (desk_top->height()/(QDesktopWidget().heightMM()) * 1.0 );  //每个像素水平高度

    float mm2pX = QDesktopWidget().logicalDpiX() / 25.4;
    float mm2pY = QDesktopWidget().logicalDpiY() / 25.4;
    //qDebug("[common_fun--%s]>>[mm2pX:%f, mm2pY:%f, 1 / mm2pX:%f]", __FUNCTION__, mm2pX, mm2pY, 1 / mm2pX);

//    qDebug()<<"屏幕每个毫米水平方向为多少像素的 mm2pX = " << mm2pX;
//    qDebug()<<"屏幕每个毫米垂直方向为多少像素的 mm2pY = " << mm2pY;


    if(type)
    {
        return ((val_mm) * (mm2pX));
    }
    else
    {
        return (val_mm) * (mm2pY);
    }
}

/**
 * @brief dot2mm
 * 打印机的单位点转为mm,根据打印机的协议，1点=0.125mm
 * @param val
 * @return
 */
float dot2mm(float val_mm)
{
    return val_mm*0.125;
}

/**
 * @brief mm2dot
 * 毫米转为点
 * @param val
 * @return
 */
float mm2dot(float val_dot)
{
    return val_dot*(1/0.125);
}

/**
 * @brief pix2dot
 * 像素转为点（分水平和垂直像素，其实在一般的电脑，水平和垂直差不多）
 * @param val_dot
 */
float pix2dot(float val_pix, ENUM_DIR_V_H_TYPE type)
{
    //先把像素转为毫米
    float val_mm = pix2mm(val_pix, type);
    //再把毫米转为 打印点数
    float val_dot = mm2dot(val_mm);
    return val_dot;
}

/**
 * @brief dot2pix
 *      点转为像素（分水平和垂直像素，其实在一般的电脑，水平和垂直差不多）
 * @param val_dot
 * @param type
 */
float dot2pix(float val_dot, ENUM_DIR_V_H_TYPE type)
{
    //先把点转为mm
    float val_mm = dot2mm(val_dot);
    //再把mm转为pix
    float val_pix = mm2pix(val_mm, type);
    return val_pix;
}

/**
 * @brief isChineseString
 * 判断QString中是否存在中文(GB2312)，打印机固定的是两字节的GB2312
 * @param str
 * @return
 */
bool isChineseString(QString str)
{
    return str.contains(QRegExp("[\\x4E00-\\x9fa5]+"));
}

/**
 * @brief textString2HEX
 * 中英文混合字符串转为HEX，英文转为ASCII，中文转为GB2312
 * @return
 */
QByteArray textString2HEX()
{
    QString str;
    int nCount = str.count();
    for(int i = 0 ; i < nCount ; i++)
    {
        QChar cha = str.at(i);
        ushort uni = cha.unicode();
        if(uni >= 0x4E00 && uni <= 0x9FA5)
        {
            //这个字符是中文
        }
        else
        {
            //这里是英文

        }
    }
}

/**
 * @brief utf8ToGb2312
 *  utf-8是unicode的一种实现方式,utf-8转GB2312
 * @param strUtf8
 * @return
 */
QString utf8ToGb2312(char *strUtf8)
{
    QTextCodec* utf8Codec= QTextCodec::codecForName("UTF-8");
    QTextCodec* gb2312Codec = QTextCodec::codecForName("GB2312");

    QString strUnicode= utf8Codec->toUnicode(strUtf8);
    QByteArray ByteGb2312= gb2312Codec->fromUnicode(strUnicode);

    strUtf8= ByteGb2312.data();
    return QString::fromLocal8Bit(strUtf8);//注意这里要fromLocal8Bit()
}

/**
 * @brief utf8ToGb2312
 *          utf-8转Gb2312
 * @param strUtf8
 */
void utf8ToGb2312(char *strUtf8, char *out)
{
    QTextCodec* utf8Codec = QTextCodec::codecForName("utf-8");
    QTextCodec* gb2312Codec = QTextCodec::codecForName("gb2312");

    QString strUnicode = utf8Codec ->toUnicode(strUtf8);
    QByteArray ByteGb2312 = gb2312Codec ->fromUnicode(strUnicode);

    out = ByteGb2312.data();
}

/**
 * @brief gb2312ToUtf8
 *  gb2312转UTF-8
 * @param strGb2312
 */
void gb2312ToUtf8(QString strGb2312)
{
    QTextCodec* utf8Codec= QTextCodec::codecForName("utf-8");
    QTextCodec* gb2312Codec = QTextCodec::codecForName("gb2312");

    QString strUnicode= gb2312Codec->toUnicode(strGb2312.toLocal8Bit().data());
    QByteArray ByteUtf8= utf8Codec->fromUnicode(strUnicode);

    char *utf8code = ByteUtf8.data();
}

/**
 * @brief utf8Tgb2312
 * @param data
 *          utf-8转gb2312
 * @return
 */
QString utf8Tgb2312(QString data)
{
    QTextCodec* utf8Codec = QTextCodec::codecForName("utf-8");
    QTextCodec* gb2312Codec = QTextCodec::codecForName("gb2312");

    QString strUnicode = utf8Codec->toUnicode(data.toLocal8Bit());    //无编码
    QByteArray ByteGb2312 = gb2312Codec->fromUnicode(strUnicode);     //无编码转换

    char* pTmp= new char[ByteGb2312.length() + 1];
    memset(pTmp, 0, ByteGb2312.length() + 1);
    strncpy(pTmp, ByteGb2312.data(), ByteGb2312.length());
    printf("%s\n", pTmp);

    delete pTmp;

    return QString::fromLocal8Bit(ByteGb2312);
}

/**
 * @brief utf8Tgb2312
 * @param data
 *          gb2312 转utf-8
 * @return
 */
QString gb2312Tutf8(QString data)
{
    QTextCodec* utf8Codec = QTextCodec::codecForName("utf-8");
    QTextCodec* gb2312Codec = QTextCodec::codecForName("gb2312");

    QString strUnicode = gb2312Codec ->toUnicode(data.toLocal8Bit());    //无编码
    QByteArray ByteUTF8 = utf8Codec ->fromUnicode(strUnicode);     //无编码转换

    return QString::fromLocal8Bit(ByteUTF8);
}

