/****************************************************************************
** Meta object code from reading C++ file 'attrtwocodetabwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../attrtwocodetabwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'attrtwocodetabwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AttrTwoCodeTabWidget_t {
    QByteArrayData data[10];
    char stringdata0[198];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AttrTwoCodeTabWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AttrTwoCodeTabWidget_t qt_meta_stringdata_AttrTwoCodeTabWidget = {
    {
QT_MOC_LITERAL(0, 0, 20), // "AttrTwoCodeTabWidget"
QT_MOC_LITERAL(1, 21, 25), // "attr_twocode_data_changed"
QT_MOC_LITERAL(2, 47, 0), // ""
QT_MOC_LITERAL(3, 48, 24), // "attr_twocode_x_y_changed"
QT_MOC_LITERAL(4, 73, 24), // "attr_twocode_ecl_changed"
QT_MOC_LITERAL(5, 98, 5), // "index"
QT_MOC_LITERAL(6, 104, 25), // "attr_twocode_mode_changed"
QT_MOC_LITERAL(7, 130, 34), // "attr_twocode_display_bound_ch..."
QT_MOC_LITERAL(8, 165, 5), // "state"
QT_MOC_LITERAL(9, 171, 26) // "attr_twocode_uintw_changed"

    },
    "AttrTwoCodeTabWidget\0attr_twocode_data_changed\0"
    "\0attr_twocode_x_y_changed\0"
    "attr_twocode_ecl_changed\0index\0"
    "attr_twocode_mode_changed\0"
    "attr_twocode_display_bound_changed\0"
    "state\0attr_twocode_uintw_changed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AttrTwoCodeTabWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x0a /* Public */,
       3,    0,   45,    2, 0x0a /* Public */,
       4,    1,   46,    2, 0x0a /* Public */,
       6,    1,   49,    2, 0x0a /* Public */,
       7,    1,   52,    2, 0x0a /* Public */,
       9,    1,   55,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,    5,

       0        // eod
};

void AttrTwoCodeTabWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AttrTwoCodeTabWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->attr_twocode_data_changed(); break;
        case 1: _t->attr_twocode_x_y_changed(); break;
        case 2: _t->attr_twocode_ecl_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->attr_twocode_mode_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->attr_twocode_display_bound_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->attr_twocode_uintw_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject AttrTwoCodeTabWidget::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_AttrTwoCodeTabWidget.data,
    qt_meta_data_AttrTwoCodeTabWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *AttrTwoCodeTabWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AttrTwoCodeTabWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AttrTwoCodeTabWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int AttrTwoCodeTabWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
