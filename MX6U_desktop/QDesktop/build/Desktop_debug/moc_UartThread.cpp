/****************************************************************************
** Meta object code from reading C++ file 'UartThread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../uart/UartThread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'UartThread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_UartThread_t {
    QByteArrayData data[13];
    char stringdata0[173];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_UartThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_UartThread_t qt_meta_stringdata_UartThread = {
    {
QT_MOC_LITERAL(0, 0, 10), // "UartThread"
QT_MOC_LITERAL(1, 11, 16), // "sendDataToWdiget"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 4), // "data"
QT_MOC_LITERAL(4, 34, 23), // "uart_vaild_ports_to_qml"
QT_MOC_LITERAL(5, 58, 4), // "port"
QT_MOC_LITERAL(6, 63, 21), // "Uart_ready_read_slots"
QT_MOC_LITERAL(7, 85, 19), // "Uart_sendData_slots"
QT_MOC_LITERAL(8, 105, 21), // "uart_search_com_slots"
QT_MOC_LITERAL(9, 127, 21), // "uart_open_close_slots"
QT_MOC_LITERAL(10, 149, 8), // "now_text"
QT_MOC_LITERAL(11, 158, 8), // "portName"
QT_MOC_LITERAL(12, 167, 5) // "bound"

    },
    "UartThread\0sendDataToWdiget\0\0data\0"
    "uart_vaild_ports_to_qml\0port\0"
    "Uart_ready_read_slots\0Uart_sendData_slots\0"
    "uart_search_com_slots\0uart_open_close_slots\0"
    "now_text\0portName\0bound"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UartThread[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       4,    1,   47,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   50,    2, 0x0a /* Public */,
       7,    1,   51,    2, 0x0a /* Public */,
       8,    0,   54,    2, 0x0a /* Public */,
       9,    3,   55,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    5,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,   10,   11,   12,

       0        // eod
};

void UartThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<UartThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendDataToWdiget((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->uart_vaild_ports_to_qml((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->Uart_ready_read_slots(); break;
        case 3: _t->Uart_sendData_slots((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 4: _t->uart_search_com_slots(); break;
        case 5: _t->uart_open_close_slots((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (UartThread::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UartThread::sendDataToWdiget)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (UartThread::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UartThread::uart_vaild_ports_to_qml)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject UartThread::staticMetaObject = { {
    &QThread::staticMetaObject,
    qt_meta_stringdata_UartThread.data,
    qt_meta_data_UartThread,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *UartThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UartThread::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_UartThread.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int UartThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void UartThread::sendDataToWdiget(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void UartThread::uart_vaild_ports_to_qml(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
