/****************************************************************************
** Meta object code from reading C++ file 'UsbThread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../QDesktop/usb/UsbThread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'UsbThread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_UsbThread_t {
    QByteArrayData data[15];
    char stringdata0[207];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_UsbThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_UsbThread_t qt_meta_stringdata_UsbThread = {
    {
QT_MOC_LITERAL(0, 0, 9), // "UsbThread"
QT_MOC_LITERAL(1, 10, 13), // "sendDataToQml"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 4), // "data"
QT_MOC_LITERAL(4, 30, 22), // "usb_vaild_ports_to_qml"
QT_MOC_LITERAL(5, 53, 4), // "port"
QT_MOC_LITERAL(6, 58, 21), // "usb_open_flag_signals"
QT_MOC_LITERAL(7, 80, 4), // "flag"
QT_MOC_LITERAL(8, 85, 22), // "usb_close_flag_signals"
QT_MOC_LITERAL(9, 108, 20), // "usb_ready_read_slots"
QT_MOC_LITERAL(10, 129, 18), // "usb_sendData_slots"
QT_MOC_LITERAL(11, 148, 20), // "usb_search_com_slots"
QT_MOC_LITERAL(12, 169, 20), // "usb_open_close_slots"
QT_MOC_LITERAL(13, 190, 8), // "now_text"
QT_MOC_LITERAL(14, 199, 7) // "usbName"

    },
    "UsbThread\0sendDataToQml\0\0data\0"
    "usb_vaild_ports_to_qml\0port\0"
    "usb_open_flag_signals\0flag\0"
    "usb_close_flag_signals\0usb_ready_read_slots\0"
    "usb_sendData_slots\0usb_search_com_slots\0"
    "usb_open_close_slots\0now_text\0usbName"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UsbThread[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       4,    1,   57,    2, 0x06 /* Public */,
       6,    1,   60,    2, 0x06 /* Public */,
       8,    1,   63,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,   66,    2, 0x0a /* Public */,
      10,    1,   67,    2, 0x0a /* Public */,
      11,    0,   70,    2, 0x0a /* Public */,
      12,    2,   71,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    7,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   13,   14,

       0        // eod
};

void UsbThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<UsbThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendDataToQml((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->usb_vaild_ports_to_qml((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->usb_open_flag_signals((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->usb_close_flag_signals((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->usb_ready_read_slots(); break;
        case 5: _t->usb_sendData_slots((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->usb_search_com_slots(); break;
        case 7: _t->usb_open_close_slots((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (UsbThread::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UsbThread::sendDataToQml)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (UsbThread::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UsbThread::usb_vaild_ports_to_qml)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (UsbThread::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UsbThread::usb_open_flag_signals)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (UsbThread::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UsbThread::usb_close_flag_signals)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject UsbThread::staticMetaObject = { {
    &QThread::staticMetaObject,
    qt_meta_stringdata_UsbThread.data,
    qt_meta_data_UsbThread,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *UsbThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UsbThread::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_UsbThread.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int UsbThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void UsbThread::sendDataToQml(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void UsbThread::usb_vaild_ports_to_qml(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void UsbThread::usb_open_flag_signals(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void UsbThread::usb_close_flag_signals(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
