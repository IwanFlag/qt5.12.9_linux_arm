#include <QtQml/qqmlprivate.h>
#include <QtCore/qdir.h>
#include <QtCore/qurl.h>

static const unsigned char qt_resource_tree[] = {
0,
0,0,0,0,2,0,0,0,26,0,0,0,1,0,0,1,
128,0,2,0,0,0,1,0,0,0,80,0,0,0,102,0,
2,0,0,0,1,0,0,0,79,0,0,0,178,0,2,0,
0,0,1,0,0,0,78,0,0,5,94,0,2,0,0,0,
1,0,0,0,77,0,0,5,134,0,2,0,0,0,2,0,
0,0,75,0,0,0,138,0,2,0,0,0,1,0,0,0,
74,0,0,1,88,0,2,0,0,0,1,0,0,0,73,0,
0,2,58,0,2,0,0,0,3,0,0,0,70,0,0,0,
72,0,0,0,0,0,1,0,0,0,0,0,0,6,10,0,
2,0,0,0,10,0,0,0,60,0,0,2,244,0,2,0,
0,0,5,0,0,0,55,0,0,0,8,0,2,0,0,0,
1,0,0,0,54,0,0,5,210,0,2,0,0,0,1,0,
0,0,53,0,0,8,80,0,2,0,0,0,3,0,0,0,
50,0,0,8,36,0,2,0,0,0,1,0,0,0,49,0,
0,8,214,0,2,0,0,0,1,0,0,0,48,0,0,4,
52,0,2,0,0,0,1,0,0,0,47,0,0,0,252,0,
2,0,0,0,1,0,0,0,46,0,0,0,230,0,0,0,
0,0,1,0,0,0,0,0,0,4,108,0,2,0,0,0,
1,0,0,0,45,0,0,4,176,0,2,0,0,0,4,0,
0,0,41,0,0,1,160,0,2,0,0,0,4,0,0,0,
37,0,0,7,108,0,2,0,0,0,5,0,0,0,32,0,
0,1,40,0,2,0,0,0,1,0,0,0,31,0,0,2,
192,0,2,0,0,0,1,0,0,0,30,0,0,3,184,0,
2,0,0,0,3,0,0,0,27,0,0,3,232,0,0,0,
0,0,1,0,0,0,0,0,0,4,14,0,0,0,0,0,
1,0,0,0,0,0,0,3,204,0,0,0,0,0,1,0,
0,0,0,0,0,2,214,0,0,0,0,0,1,0,0,0,
0,0,0,1,60,0,0,0,0,0,1,0,0,0,0,0,
0,7,166,0,0,0,0,0,1,0,0,0,0,0,0,7,
194,0,0,0,0,0,1,0,0,0,0,0,0,7,226,0,
0,0,0,0,1,0,0,0,0,0,0,8,4,0,0,0,
0,0,1,0,0,0,0,0,0,7,134,0,0,0,0,0,
1,0,0,0,0,0,0,1,208,0,0,0,0,0,1,0,
0,0,0,0,0,1,246,0,0,0,0,0,1,0,0,0,
0,0,0,2,14,0,0,0,0,0,1,0,0,0,0,0,
0,1,180,0,0,0,0,0,1,0,0,0,0,0,0,5,
14,0,0,0,0,0,1,0,0,0,0,0,0,5,60,0,
0,0,0,0,1,0,0,0,0,0,0,4,206,0,0,0,
0,0,1,0,0,0,0,0,0,4,244,0,0,0,0,0,
1,0,0,0,0,0,0,4,136,0,0,0,0,0,1,0,
0,0,0,0,0,1,14,0,0,0,0,0,1,0,0,0,
0,0,0,4,76,0,0,0,0,0,1,0,0,0,0,0,
0,8,232,0,0,0,0,0,1,0,0,0,0,0,0,8,
54,0,0,0,0,0,1,0,0,0,0,0,0,8,142,0,
0,0,0,0,1,0,0,0,0,0,0,8,174,0,0,0,
0,0,1,0,0,0,0,0,0,8,104,0,0,0,0,0,
1,0,0,0,0,0,0,5,234,0,0,0,0,0,1,0,
0,0,0,0,0,0,34,0,0,0,0,0,1,0,0,0,
0,0,0,3,6,0,0,0,0,0,1,0,0,0,0,0,
0,3,116,0,0,0,0,0,1,0,0,0,0,0,0,3,
76,0,0,0,0,0,1,0,0,0,0,0,0,3,140,0,
0,0,0,0,1,0,0,0,0,0,0,3,42,0,0,0,
0,0,1,0,0,0,0,0,0,6,92,0,0,0,0,0,
1,0,0,0,0,0,0,6,64,0,0,0,0,0,1,0,
0,0,0,0,0,6,188,0,0,0,0,0,1,0,0,0,
0,0,0,6,38,0,0,0,0,0,1,0,0,0,0,0,
0,6,152,0,0,0,0,0,1,0,0,0,0,0,0,7,
24,0,0,0,0,0,1,0,0,0,0,0,0,6,224,0,
0,0,0,0,1,0,0,0,0,0,0,7,70,0,0,0,
0,0,1,0,0,0,0,0,0,6,252,0,0,0,0,0,
1,0,0,0,0,0,0,6,124,0,0,0,0,0,1,0,
0,0,0,0,0,2,122,0,0,0,0,0,1,0,0,0,
0,0,0,2,156,0,0,0,0,0,1,0,0,0,0,0,
0,2,80,0,0,0,0,0,1,0,0,0,0,0,0,1,
104,0,0,0,0,0,1,0,0,0,0,0,0,0,154,0,
0,0,0,0,1,0,0,0,0,0,0,5,174,0,0,0,
0,0,1,0,0,0,0,0,0,5,150,0,0,0,0,0,
1,0,0,0,0,0,0,5,110,0,0,0,0,0,1,0,
0,0,0,0,0,0,200,0,0,0,0,0,1,0,0,0,
0,0,0,0,116,0,0,0,0,0,1,0,0,0,0,0,
0,1,140,0,0,0,0,0,1,0,0,0,0};
static const unsigned char qt_resource_names[] = {
0,
1,0,0,0,47,0,47,0,10,6,145,99,62,0,104,0,
101,0,108,0,112,0,98,0,117,0,116,0,116,0,111,0,
110,0,16,7,176,182,28,0,72,0,101,0,108,0,112,0,
77,0,101,0,115,0,115,0,97,0,103,0,101,0,115,0,
46,0,113,0,109,0,108,0,12,5,188,48,92,0,72,0,
111,0,109,0,101,0,109,0,101,0,110,0,117,0,46,0,
113,0,109,0,108,0,4,0,7,184,148,0,117,0,97,0,
114,0,116,0,8,8,151,95,92,0,85,0,97,0,114,0,
116,0,46,0,113,0,109,0,108,0,5,0,116,201,243,0,
109,0,117,0,115,0,105,0,99,0,9,9,247,1,188,0,
77,0,117,0,115,0,105,0,99,0,46,0,113,0,109,0,
108,0,8,0,44,194,103,0,102,0,105,0,108,0,101,0,
118,0,105,0,101,0,119,0,12,6,106,5,188,0,70,0,
105,0,108,0,101,0,86,0,105,0,101,0,119,0,46,0,
113,0,109,0,108,0,8,8,1,90,92,0,109,0,97,0,
105,0,110,0,46,0,113,0,109,0,108,0,6,7,176,170,
189,0,115,0,121,0,115,0,116,0,101,0,109,0,10,10,
183,57,124,0,83,0,121,0,115,0,116,0,101,0,109,0,
46,0,113,0,109,0,108,0,7,11,182,158,100,0,117,0,
100,0,112,0,99,0,104,0,97,0,116,0,11,14,48,65,
28,0,85,0,100,0,112,0,67,0,104,0,97,0,116,0,
46,0,113,0,109,0,108,0,5,0,120,122,255,0,114,0,
97,0,100,0,105,0,111,0,9,11,2,232,220,0,82,0,
97,0,100,0,105,0,111,0,46,0,113,0,109,0,108,0,
3,0,0,124,146,0,117,0,115,0,98,0,7,12,149,88,
156,0,85,0,115,0,98,0,46,0,113,0,109,0,108,0,
7,10,202,43,160,0,100,0,101,0,115,0,107,0,116,0,
111,0,112,0,11,11,246,196,60,0,68,0,101,0,115,0,
107,0,84,0,111,0,112,0,46,0,113,0,109,0,108,0,
16,3,183,96,124,0,65,0,112,0,112,0,108,0,105,0,
99,0,97,0,116,0,105,0,111,0,110,0,115,0,46,0,
113,0,109,0,108,0,9,5,158,196,92,0,67,0,108,0,
111,0,99,0,107,0,46,0,113,0,109,0,108,0,19,6,
88,25,156,0,87,0,105,0,110,0,83,0,116,0,121,0,
108,0,101,0,68,0,101,0,115,0,107,0,116,0,111,0,
112,0,46,0,113,0,109,0,108,0,8,0,140,35,99,0,
119,0,105,0,114,0,101,0,108,0,101,0,115,0,115,0,
18,6,197,147,188,0,77,0,121,0,87,0,105,0,102,0,
105,0,75,0,101,0,121,0,73,0,110,0,112,0,117,0,
116,0,46,0,113,0,109,0,108,0,14,1,103,85,92,0,
77,0,121,0,87,0,105,0,114,0,101,0,108,0,101,0,
115,0,115,0,46,0,113,0,109,0,108,0,15,1,185,30,
92,0,77,0,121,0,84,0,101,0,120,0,116,0,70,0,
105,0,101,0,108,0,100,0,46,0,113,0,109,0,108,0,
8,12,187,11,195,0,115,0,101,0,116,0,116,0,105,0,
110,0,103,0,115,0,12,15,223,34,60,0,83,0,101,0,
116,0,116,0,105,0,110,0,103,0,115,0,46,0,113,0,
109,0,108,0,6,6,130,137,67,0,97,0,108,0,97,0,
114,0,109,0,115,0,15,2,124,42,156,0,65,0,108,0,
97,0,114,0,109,0,68,0,105,0,97,0,108,0,111,0,
103,0,46,0,113,0,109,0,108,0,14,15,173,14,156,0,
65,0,108,0,97,0,114,0,109,0,77,0,111,0,100,0,
101,0,108,0,46,0,113,0,109,0,108,0,17,10,224,165,
220,0,65,0,108,0,97,0,114,0,109,0,68,0,101,0,
108,0,101,0,103,0,97,0,116,0,101,0,46,0,113,0,
109,0,108,0,9,8,144,200,124,0,65,0,108,0,97,0,
114,0,109,0,46,0,113,0,109,0,108,0,19,10,250,74,
92,0,84,0,117,0,109,0,98,0,108,0,101,0,114,0,
68,0,101,0,108,0,101,0,103,0,97,0,116,0,101,0,
46,0,113,0,109,0,108,0,7,13,184,174,34,0,119,0,
101,0,97,0,116,0,104,0,101,0,114,0,11,14,126,41,
124,0,87,0,101,0,97,0,116,0,104,0,101,0,114,0,
46,0,113,0,109,0,108,0,16,8,74,214,252,0,87,0,
101,0,97,0,116,0,104,0,101,0,114,0,80,0,97,0,
103,0,101,0,50,0,46,0,113,0,109,0,108,0,16,8,
79,214,252,0,87,0,101,0,97,0,116,0,104,0,101,0,
114,0,80,0,97,0,103,0,101,0,49,0,46,0,113,0,
109,0,108,0,9,7,156,105,130,0,116,0,99,0,112,0,
115,0,101,0,114,0,118,0,101,0,114,0,13,9,142,112,
124,0,84,0,99,0,112,0,83,0,101,0,114,0,118,0,
101,0,114,0,46,0,113,0,109,0,108,0,11,8,208,189,
113,0,99,0,97,0,109,0,101,0,114,0,97,0,109,0,
101,0,100,0,105,0,97,0,17,12,56,121,92,0,77,0,
121,0,67,0,97,0,109,0,101,0,114,0,97,0,77,0,
101,0,100,0,105,0,97,0,46,0,113,0,109,0,108,0,
12,9,177,188,158,0,97,0,105,0,114,0,99,0,111,0,
110,0,100,0,105,0,116,0,105,0,111,0,110,0,16,12,
186,55,92,0,65,0,105,0,114,0,99,0,111,0,110,0,
100,0,105,0,116,0,105,0,111,0,110,0,46,0,113,0,
109,0,108,0,10,15,117,207,124,0,77,0,121,0,68,0,
105,0,97,0,108,0,46,0,113,0,109,0,108,0,20,0,
127,198,60,0,67,0,105,0,114,0,99,0,117,0,108,0,
97,0,114,0,80,0,114,0,111,0,103,0,114,0,101,0,
115,0,115,0,46,0,113,0,109,0,108,0,14,6,41,137,
220,0,67,0,117,0,115,0,116,0,111,0,109,0,68,0,
105,0,97,0,108,0,46,0,113,0,109,0,108,0,5,0,
115,93,254,0,108,0,111,0,103,0,105,0,110,0,9,14,
1,242,156,0,76,0,111,0,103,0,105,0,110,0,46,0,
113,0,109,0,108,0,5,0,115,186,241,0,109,0,101,0,
100,0,105,0,97,0,9,10,244,243,92,0,77,0,101,0,
100,0,105,0,97,0,46,0,113,0,109,0,108,0,15,0,
189,43,124,0,66,0,117,0,116,0,116,0,111,0,110,0,
73,0,109,0,97,0,103,0,101,0,46,0,113,0,109,0,
108,0,9,6,162,17,20,0,116,0,99,0,112,0,99,0,
108,0,105,0,101,0,110,0,116,0,13,1,30,20,156,0,
84,0,99,0,112,0,67,0,108,0,105,0,101,0,110,0,
116,0,46,0,113,0,109,0,108,0,11,6,120,67,60,0,
102,0,97,0,99,0,116,0,111,0,114,0,121,0,116,0,
111,0,111,0,108,0,10,1,205,155,124,0,80,0,97,0,
99,0,107,0,101,0,116,0,46,0,113,0,109,0,108,0,
11,0,253,195,92,0,83,0,101,0,116,0,116,0,105,0,
110,0,103,0,46,0,113,0,109,0,108,0,13,0,19,224,
156,0,83,0,119,0,101,0,101,0,112,0,67,0,111,0,
100,0,101,0,46,0,113,0,109,0,108,0,11,15,39,199,
188,0,83,0,101,0,114,0,118,0,105,0,99,0,101,0,
46,0,113,0,109,0,108,0,15,3,51,40,188,0,70,0,
97,0,99,0,116,0,111,0,114,0,121,0,116,0,111,0,
111,0,108,0,46,0,113,0,109,0,108,0,15,1,60,93,
156,0,70,0,97,0,99,0,116,0,111,0,114,0,121,0,
77,0,101,0,110,0,117,0,46,0,113,0,109,0,108,0,
11,6,116,225,28,0,83,0,101,0,110,0,100,0,79,0,
117,0,116,0,46,0,113,0,109,0,108,0,11,11,8,127,
92,0,80,0,114,0,111,0,100,0,117,0,99,0,116,0,
46,0,113,0,109,0,108,0,20,3,121,177,92,0,70,0,
97,0,99,0,116,0,111,0,114,0,121,0,83,0,116,0,
97,0,116,0,117,0,115,0,66,0,97,0,114,0,46,0,
113,0,109,0,108,0,16,10,208,126,220,0,80,0,104,0,
111,0,116,0,111,0,83,0,101,0,116,0,116,0,105,0,
110,0,103,0,46,0,113,0,109,0,108,0,10,10,207,187,
34,0,99,0,97,0,108,0,99,0,117,0,108,0,97,0,
116,0,111,0,114,0,13,13,240,81,156,0,78,0,117,0,
109,0,98,0,101,0,114,0,80,0,97,0,100,0,46,0,
113,0,109,0,108,0,11,2,30,68,220,0,68,0,105,0,
115,0,112,0,108,0,97,0,121,0,46,0,113,0,109,0,
108,0,13,8,100,112,124,0,67,0,97,0,108,0,98,0,
117,0,116,0,116,0,111,0,110,0,46,0,113,0,109,0,
108,0,14,11,48,195,92,0,67,0,97,0,108,0,99,0,
117,0,108,0,97,0,116,0,111,0,114,0,46,0,113,0,
109,0,108,0,13,11,179,12,243,0,99,0,97,0,108,0,
99,0,117,0,108,0,97,0,116,0,111,0,114,0,46,0,
106,0,115,0,6,7,6,172,164,0,105,0,111,0,116,0,
101,0,115,0,116,0,10,12,173,93,124,0,73,0,111,0,
116,0,101,0,115,0,116,0,46,0,113,0,109,0,108,0,
9,6,182,34,39,0,112,0,104,0,111,0,116,0,111,0,
118,0,105,0,101,0,119,0,16,8,245,91,92,0,68,0,
105,0,115,0,112,0,108,0,97,0,121,0,80,0,104,0,
111,0,116,0,111,0,46,0,113,0,109,0,108,0,13,2,
39,64,252,0,80,0,104,0,111,0,116,0,111,0,86,0,
105,0,101,0,119,0,46,0,113,0,109,0,108,0,17,6,
244,225,124,0,80,0,104,0,111,0,116,0,111,0,76,0,
105,0,115,0,116,0,86,0,105,0,101,0,119,0,46,0,
113,0,109,0,108,0,6,7,156,90,98,0,115,0,101,0,
110,0,115,0,111,0,114,0,10,10,110,112,156,0,83,0,
101,0,110,0,115,0,111,0,114,0,46,0,113,0,109,0,
108};
static const unsigned char qt_resource_empty_payout[] = { 0, 0, 0, 0, 0 };
QT_BEGIN_NAMESPACE
extern Q_CORE_EXPORT bool qRegisterResourceData(int, const unsigned char *, const unsigned char *, const unsigned char *);
QT_END_NAMESPACE
namespace QmlCacheGeneratedCode {
namespace _sensor_Sensor_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _photoview_PhotoListView_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _iotest_Iotest_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _calculator_calculator_js { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _factorytool_PhotoSetting_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _photoview_PhotoView_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _tcpclient_TcpClient_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _media_ButtonImage_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _login_Login_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _aircondition_CustomDial_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _cameramedia_MyCameraMedia_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _tcpserver_TcpServer_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _factorytool_FactoryStatusBar_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _aircondition_CircularProgress_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _weather_WeatherPage1_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _alarms_TumblerDelegate_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _settings_Settings_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _alarms_Alarm_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _wireless_MyTextField_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _calculator_Calculator_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _factorytool_Product_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _desktop_WinStyleDesktop_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _usb_Usb_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _alarms_AlarmDelegate_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _alarms_AlarmModel_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _radio_Radio_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _factorytool_SendOut_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _factorytool_FactoryMenu_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _photoview_DisplayPhoto_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _factorytool_Factorytool_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _aircondition_MyDial_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _udpchat_UdpChat_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _system_System_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _desktop_Clock_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f__main_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _factorytool_Service_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _fileview_FileView_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _media_Media_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _calculator_Calbutton_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _desktop_Applications_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _weather_WeatherPage2_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _desktop_DeskTop_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _wireless_MyWireless_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _music_Music_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _calculator_Display_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _aircondition_Aircondition_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _weather_Weather_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _uart_Uart_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f__Homemenu_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _alarms_AlarmDialog_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _factorytool_SweepCode_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _factorytool_Setting_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _helpbutton_HelpMessages_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _factorytool_Packet_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _calculator_NumberPad_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _wireless_MyWifiKeyInput_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}

}
namespace {
struct Registry {
    Registry();
    ~Registry();
    QHash<QString, const QQmlPrivate::CachedQmlUnit*> resourcePathToCachedUnit;
    static const QQmlPrivate::CachedQmlUnit *lookupCachedUnit(const QUrl &url);
};

Q_GLOBAL_STATIC(Registry, unitRegistry)


Registry::Registry() {
        resourcePathToCachedUnit.insert(QStringLiteral("/sensor/Sensor.qml"), &QmlCacheGeneratedCode::_sensor_Sensor_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/photoview/PhotoListView.qml"), &QmlCacheGeneratedCode::_photoview_PhotoListView_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/iotest/Iotest.qml"), &QmlCacheGeneratedCode::_iotest_Iotest_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/calculator/calculator.js"), &QmlCacheGeneratedCode::_calculator_calculator_js::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/factorytool/PhotoSetting.qml"), &QmlCacheGeneratedCode::_factorytool_PhotoSetting_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/photoview/PhotoView.qml"), &QmlCacheGeneratedCode::_photoview_PhotoView_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/tcpclient/TcpClient.qml"), &QmlCacheGeneratedCode::_tcpclient_TcpClient_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/media/ButtonImage.qml"), &QmlCacheGeneratedCode::_media_ButtonImage_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/login/Login.qml"), &QmlCacheGeneratedCode::_login_Login_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/aircondition/CustomDial.qml"), &QmlCacheGeneratedCode::_aircondition_CustomDial_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/cameramedia/MyCameraMedia.qml"), &QmlCacheGeneratedCode::_cameramedia_MyCameraMedia_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/tcpserver/TcpServer.qml"), &QmlCacheGeneratedCode::_tcpserver_TcpServer_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/factorytool/FactoryStatusBar.qml"), &QmlCacheGeneratedCode::_factorytool_FactoryStatusBar_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/aircondition/CircularProgress.qml"), &QmlCacheGeneratedCode::_aircondition_CircularProgress_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/weather/WeatherPage1.qml"), &QmlCacheGeneratedCode::_weather_WeatherPage1_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/alarms/TumblerDelegate.qml"), &QmlCacheGeneratedCode::_alarms_TumblerDelegate_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/settings/Settings.qml"), &QmlCacheGeneratedCode::_settings_Settings_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/alarms/Alarm.qml"), &QmlCacheGeneratedCode::_alarms_Alarm_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/wireless/MyTextField.qml"), &QmlCacheGeneratedCode::_wireless_MyTextField_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/calculator/Calculator.qml"), &QmlCacheGeneratedCode::_calculator_Calculator_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/factorytool/Product.qml"), &QmlCacheGeneratedCode::_factorytool_Product_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/desktop/WinStyleDesktop.qml"), &QmlCacheGeneratedCode::_desktop_WinStyleDesktop_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/usb/Usb.qml"), &QmlCacheGeneratedCode::_usb_Usb_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/alarms/AlarmDelegate.qml"), &QmlCacheGeneratedCode::_alarms_AlarmDelegate_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/alarms/AlarmModel.qml"), &QmlCacheGeneratedCode::_alarms_AlarmModel_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/radio/Radio.qml"), &QmlCacheGeneratedCode::_radio_Radio_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/factorytool/SendOut.qml"), &QmlCacheGeneratedCode::_factorytool_SendOut_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/factorytool/FactoryMenu.qml"), &QmlCacheGeneratedCode::_factorytool_FactoryMenu_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/photoview/DisplayPhoto.qml"), &QmlCacheGeneratedCode::_photoview_DisplayPhoto_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/factorytool/Factorytool.qml"), &QmlCacheGeneratedCode::_factorytool_Factorytool_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/aircondition/MyDial.qml"), &QmlCacheGeneratedCode::_aircondition_MyDial_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/udpchat/UdpChat.qml"), &QmlCacheGeneratedCode::_udpchat_UdpChat_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/system/System.qml"), &QmlCacheGeneratedCode::_system_System_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/desktop/Clock.qml"), &QmlCacheGeneratedCode::_desktop_Clock_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/main.qml"), &QmlCacheGeneratedCode::_0x5f__main_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/factorytool/Service.qml"), &QmlCacheGeneratedCode::_factorytool_Service_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/fileview/FileView.qml"), &QmlCacheGeneratedCode::_fileview_FileView_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/media/Media.qml"), &QmlCacheGeneratedCode::_media_Media_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/calculator/Calbutton.qml"), &QmlCacheGeneratedCode::_calculator_Calbutton_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/desktop/Applications.qml"), &QmlCacheGeneratedCode::_desktop_Applications_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/weather/WeatherPage2.qml"), &QmlCacheGeneratedCode::_weather_WeatherPage2_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/desktop/DeskTop.qml"), &QmlCacheGeneratedCode::_desktop_DeskTop_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/wireless/MyWireless.qml"), &QmlCacheGeneratedCode::_wireless_MyWireless_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/music/Music.qml"), &QmlCacheGeneratedCode::_music_Music_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/calculator/Display.qml"), &QmlCacheGeneratedCode::_calculator_Display_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/aircondition/Aircondition.qml"), &QmlCacheGeneratedCode::_aircondition_Aircondition_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/weather/Weather.qml"), &QmlCacheGeneratedCode::_weather_Weather_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/uart/Uart.qml"), &QmlCacheGeneratedCode::_uart_Uart_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/Homemenu.qml"), &QmlCacheGeneratedCode::_0x5f__Homemenu_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/alarms/AlarmDialog.qml"), &QmlCacheGeneratedCode::_alarms_AlarmDialog_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/factorytool/SweepCode.qml"), &QmlCacheGeneratedCode::_factorytool_SweepCode_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/factorytool/Setting.qml"), &QmlCacheGeneratedCode::_factorytool_Setting_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/helpbutton/HelpMessages.qml"), &QmlCacheGeneratedCode::_helpbutton_HelpMessages_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/factorytool/Packet.qml"), &QmlCacheGeneratedCode::_factorytool_Packet_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/calculator/NumberPad.qml"), &QmlCacheGeneratedCode::_calculator_NumberPad_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/wireless/MyWifiKeyInput.qml"), &QmlCacheGeneratedCode::_wireless_MyWifiKeyInput_qml::unit);
    QQmlPrivate::RegisterQmlUnitCacheHook registration;
    registration.version = 0;
    registration.lookupCachedQmlUnit = &lookupCachedUnit;
    QQmlPrivate::qmlregister(QQmlPrivate::QmlUnitCacheHookRegistration, &registration);
QT_PREPEND_NAMESPACE(qRegisterResourceData)(/*version*/0x01, qt_resource_tree, qt_resource_names, qt_resource_empty_payout);
}

Registry::~Registry() {
    QQmlPrivate::qmlunregister(QQmlPrivate::QmlUnitCacheHookRegistration, quintptr(&lookupCachedUnit));
}

const QQmlPrivate::CachedQmlUnit *Registry::lookupCachedUnit(const QUrl &url) {
    if (url.scheme() != QLatin1String("qrc"))
        return nullptr;
    QString resourcePath = QDir::cleanPath(url.path());
    if (resourcePath.isEmpty())
        return nullptr;
    if (!resourcePath.startsWith(QLatin1Char('/')))
        resourcePath.prepend(QLatin1Char('/'));
    return unitRegistry()->resourcePathToCachedUnit.value(resourcePath, nullptr);
}
}
int QT_MANGLE_NAMESPACE(qInitResources_qml)() {
    ::unitRegistry();
    Q_INIT_RESOURCE(qml_qmlcache);
    return 1;
}
Q_CONSTRUCTOR_FUNCTION(QT_MANGLE_NAMESPACE(qInitResources_qml))
int QT_MANGLE_NAMESPACE(qCleanupResources_qml)() {
    Q_CLEANUP_RESOURCE(qml_qmlcache);
    return 1;
}
