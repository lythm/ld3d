/****************************************************************************
** Meta object code from reading C++ file 'Widget_InspectorPropertyBool.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.0.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stdafx.h"
#include "../../Widget_InspectorPropertyBool.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Widget_InspectorPropertyBool.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.0.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Widget_InspectorPropertyBool_t {
    QByteArrayData data[3];
    char stringdata[48];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_Widget_InspectorPropertyBool_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_Widget_InspectorPropertyBool_t qt_meta_stringdata_Widget_InspectorPropertyBool = {
    {
QT_MOC_LITERAL(0, 0, 28),
QT_MOC_LITERAL(1, 29, 16),
QT_MOC_LITERAL(2, 46, 0)
    },
    "Widget_InspectorPropertyBool\0"
    "on_value_changed\0\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Widget_InspectorPropertyBool[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x0a,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

void Widget_InspectorPropertyBool::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Widget_InspectorPropertyBool *_t = static_cast<Widget_InspectorPropertyBool *>(_o);
        switch (_id) {
        case 0: _t->on_value_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject Widget_InspectorPropertyBool::staticMetaObject = {
    { &Widget_InspectorPropertySimple::staticMetaObject, qt_meta_stringdata_Widget_InspectorPropertyBool.data,
      qt_meta_data_Widget_InspectorPropertyBool,  qt_static_metacall, 0, 0}
};


const QMetaObject *Widget_InspectorPropertyBool::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Widget_InspectorPropertyBool::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Widget_InspectorPropertyBool.stringdata))
        return static_cast<void*>(const_cast< Widget_InspectorPropertyBool*>(this));
    return Widget_InspectorPropertySimple::qt_metacast(_clname);
}

int Widget_InspectorPropertyBool::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Widget_InspectorPropertySimple::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
