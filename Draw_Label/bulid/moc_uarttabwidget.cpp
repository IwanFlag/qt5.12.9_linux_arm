/****************************************************************************
** Meta object code from reading C++ file 'uarttabwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../uarttabwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'uarttabwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_UartTabWidget_t {
    QByteArrayData data[13];
    char stringdata0[287];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_UartTabWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_UartTabWidget_t qt_meta_stringdata_UartTabWidget = {
    {
QT_MOC_LITERAL(0, 0, 13), // "UartTabWidget"
QT_MOC_LITERAL(1, 14, 21), // "uart_search_com_slots"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 25), // "uart_open_close_com_slots"
QT_MOC_LITERAL(4, 63, 32), // "uart_send_char_stream_data_slots"
QT_MOC_LITERAL(5, 96, 36), // "uart_send_HEX_byte_stream_dat..."
QT_MOC_LITERAL(6, 133, 24), // "uart_clearall_data_slots"
QT_MOC_LITERAL(7, 158, 21), // "uart_recv_data_handle"
QT_MOC_LITERAL(8, 180, 4), // "data"
QT_MOC_LITERAL(9, 185, 24), // "uart_send_cut_over_slots"
QT_MOC_LITERAL(10, 210, 24), // "uart_send_cut_half_slots"
QT_MOC_LITERAL(11, 235, 21), // "uart_send_reset_slots"
QT_MOC_LITERAL(12, 257, 29) // "uart_send_cut_testPrint_slots"

    },
    "UartTabWidget\0uart_search_com_slots\0"
    "\0uart_open_close_com_slots\0"
    "uart_send_char_stream_data_slots\0"
    "uart_send_HEX_byte_stream_data_slots\0"
    "uart_clearall_data_slots\0uart_recv_data_handle\0"
    "data\0uart_send_cut_over_slots\0"
    "uart_send_cut_half_slots\0uart_send_reset_slots\0"
    "uart_send_cut_testPrint_slots"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UartTabWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x0a /* Public */,
       3,    0,   65,    2, 0x0a /* Public */,
       4,    0,   66,    2, 0x0a /* Public */,
       5,    0,   67,    2, 0x0a /* Public */,
       6,    0,   68,    2, 0x0a /* Public */,
       7,    1,   69,    2, 0x0a /* Public */,
       9,    0,   72,    2, 0x0a /* Public */,
      10,    0,   73,    2, 0x0a /* Public */,
      11,    0,   74,    2, 0x0a /* Public */,
      12,    0,   75,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void UartTabWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<UartTabWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->uart_search_com_slots(); break;
        case 1: _t->uart_open_close_com_slots(); break;
        case 2: _t->uart_send_char_stream_data_slots(); break;
        case 3: _t->uart_send_HEX_byte_stream_data_slots(); break;
        case 4: _t->uart_clearall_data_slots(); break;
        case 5: _t->uart_recv_data_handle((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->uart_send_cut_over_slots(); break;
        case 7: _t->uart_send_cut_half_slots(); break;
        case 8: _t->uart_send_reset_slots(); break;
        case 9: _t->uart_send_cut_testPrint_slots(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject UartTabWidget::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_UartTabWidget.data,
    qt_meta_data_UartTabWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *UartTabWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UartTabWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_UartTabWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int UartTabWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
