#ifndef COMMON_FACTORYTOOL_H
#define COMMON_FACTORYTOOL_H



//------------------------------ENUM------------------------

/**
 * @brief The DEVICE_TYPE enum
        1、代表旧八宝（数据包含：设备类型，设备IMEI，物联网卡号，二维码信息，适配器编号）（见注释 2）
        2、代表三宝（数据包含：设备类型，设备IMEI，物联网卡号，二维码信息，适配器编号）
        3、代表密码线（数据包含：设备类型，设备IMEI，二维码信息）
        6、代表彩宝主机（数据包含：设备类型，设备IMEI，物联网信息，二维码信息）
        7、代表彩宝从机（数据包含：设备类型，设备IMEI，彩宝从机外壳条码信息）（见注释3）
        8、代表彩宝充电宝（数据包含：设备类型，充电宝ID，充电宝外壳条码信息）（见注释4）
        ‘；’、代表6口彩宝控制层（数据包含：设备类型，设备IMEI，物联网信息，二维码信息）
        ‘<’、代表6口彩宝充电层（数据包含：设备类型，设备IMEI，彩宝从机外壳条码信息）（见注释3）
        ‘=’、代表街电6口彩宝主机（数据包含：设备类型，设备CPU ID，设备型号，软件版本，硬件版本，IMEI G网络模块IMEI，SIM卡ICCID，二维码信息）（见注释5）
        ‘>’、代表街电6口彩宝从机（数据包含：设备类型，CPU_ID，设备型号，软件版本，硬件版本，IMEI，彩宝从机外壳条码信息）（见注释5）
        ‘?’、代表街电4口彩宝从机（数据包含：设备类型，CPU_ID，设备型号，软件版本，硬件版本，IMEI，彩宝从机外壳条码信息）（见注释5）
 */


enum ENUM_DEVICE_TYPE
{
    DEVICE_TYPE_MIN,
    DEVICE_TYPE_OLD_8BAO,
    DEVICE_TYPE_3BAO,
    DEVICE_TYPE_SERCERT_LINE,
    DEVICE_TYPE_COLORBAO_MASTER,
    DEVICE_TYPE_COLORBAO_SLAVE,
    DEVICE_TYPE_COLORBAO_CHARGE_BAO,
    DEVICE_TYPE_COLORBAO_6MOUTH_CONTROL,
    DEVICE_TYPE_COLORBAO_6MOUTH_CHARGE,
    DEVICE_TYPE_JD_COLORBAO_6MOUTH_MASTER,
    DEVICE_TYPE_JD_COLORBAO_6MOUTH_SLAVE,
    DEVICE_TYPE_JD_COLORBAO_4MOUTH_SLAVE,
    DEVICE_TYPE_MAX
};


/**
 * @brief The ENUM_DEVICE_SEND_CMD enum
 *
 *
 */
enum ENUM_DEVICE_SEND_CMD
{
    ENUM_DEVICE_CMD_MIN,
    ENUM_DEVICE_CMD_BIND = 0X7F,
    ENUM_DEVICE_CMD_QUERY_NUM = 0X9F,
    ENUM_DEVICE_CMD_UNBIND = 0XAF,
    ENUM_DEVICE_CMD_CHARGE_BAO_40IN1 = 0XCF,
};

#endif // COMMON_FACTORYTOOL_H
