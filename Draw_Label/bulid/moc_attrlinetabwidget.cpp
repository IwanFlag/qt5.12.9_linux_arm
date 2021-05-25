/****************************************************************************
** Meta object code from reading C++ file 'attrlinetabwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../attrlinetabwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'attrlinetabwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AttrLineTabWidget_t {
    QByteArrayData data[11];
    char stringdata0[282];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AttrLineTabWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AttrLineTabWidget_t qt_meta_stringdata_AttrLineTabWidget = {
    {
QT_MOC_LITERAL(0, 0, 17), // "AttrLineTabWidget"
QT_MOC_LITERAL(1, 18, 27), // "attr_line_rotate_bt_clicked"
QT_MOC_LITERAL(2, 46, 0), // ""
QT_MOC_LITERAL(3, 47, 35), // "attr_line_penwidth_lab_edit_c..."
QT_MOC_LITERAL(4, 83, 36), // "attr_line_line_len_edit_edit_..."
QT_MOC_LITERAL(5, 120, 31), // "attr_line_start_x_ledit_changed"
QT_MOC_LITERAL(6, 152, 31), // "attr_line_start_y_ledit_changed"
QT_MOC_LITERAL(7, 184, 29), // "attr_line_end_x_ledit_changed"
QT_MOC_LITERAL(8, 214, 29), // "attr_line_end_y_ledit_changed"
QT_MOC_LITERAL(9, 244, 31), // "attr_line_display_bound_changed"
QT_MOC_LITERAL(10, 276, 5) // "state"

    },
    "AttrLineTabWidget\0attr_line_rotate_bt_clicked\0"
    "\0attr_line_penwidth_lab_edit_changed\0"
    "attr_line_line_len_edit_edit_changed\0"
    "attr_line_start_x_ledit_changed\0"
    "attr_line_start_y_ledit_changed\0"
    "attr_line_end_x_ledit_changed\0"
    "attr_line_end_y_ledit_changed\0"
    "attr_line_display_bound_changed\0state"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AttrLineTabWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x0a /* Public */,
       3,    0,   55,    2, 0x0a /* Public */,
       4,    0,   56,    2, 0x0a /* Public */,
       5,    0,   57,    2, 0x0a /* Public */,
       6,    0,   58,    2, 0x0a /* Public */,
       7,    0,   59,    2, 0x0a /* Public */,
       8,    0,   60,    2, 0x0a /* Public */,
       9,    1,   61,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   10,

       0        // eod
};

void AttrLineTabWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AttrLineTabWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->attr_line_rotate_bt_clicked(); break;
        case 1: _t->attr_line_penwidth_lab_edit_changed(); break;
        case 2: _t->attr_line_line_len_edit_edit_changed(); break;
        case 3: _t->attr_line_start_x_ledit_changed(); break;
        case 4: _t->attr_line_start_y_ledit_changed(); break;
        case 5: _t->attr_line_end_x_ledit_changed(); break;
        case 6: _t->attr_line_end_y_ledit_changed(); break;
        case 7: _t->attr_line_display_bound_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject AttrLineTabWidget::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_AttrLineTabWidget.data,
    qt_meta_data_AttrLineTabWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *AttrLineTabWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AttrLineTabWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AttrLineTabWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int AttrLineTabWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
