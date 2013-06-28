/****************************************************************************
** Meta object code from reading C++ file 'Widget_InspectorPropertyDouble.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.0.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stdafx.h"
#include "../../Widget_InspectorPropertyDouble.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Widget_InspectorPropertyDouble.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.0.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Widget_InspectorPropertyDouble_t {
    QByteArrayData data[3];
    char stringdata[50];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_Widget_InspectorPropertyDouble_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_Widget_InspectorPropertyDouble_t qt_meta_stringdata_Widget_InspectorPropertyDouble = {
    {
QT_MOC_LITERAL(0, 0, 30),
QT_MOC_LITERAL(1, 31, 16),
QT_MOC_LITERAL(2, 48, 0)
    },
    "Widget_InspectorPropertyDouble\0"
    "on_value_changed\0\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Widget_InspectorPropertyDouble[] = {

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
       1,    0,   19,    2, 0x0a,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void Widget_InspectorPropertyDouble::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Widget_InspectorPropertyDouble *_t = static_cast<Widget_InspectorPropertyDouble *>(_o);
        switch (_id) {
        case 0: _t->on_value_changed(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject Widget_InspectorPropertyDouble::staticMetaObject = {
    { &Widget_InspectorPropertySimple::staticMetaObject, qt_meta_stringdata_Widget_InspectorPropertyDouble.data,
      qt_meta_data_Widget_InspectorPropertyDouble,  qt_static_metacall, 0, 0}
};


const QMetaObject *Widget_InspectorPropertyDouble::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Widget_InspectorPropertyDouble::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Widget_InspectorPropertyDouble.stringdata))
        return static_cast<void*>(const_cast< Widget_InspectorPropertyDouble*>(this));
    return Widget_InspectorPropertySimple::qt_metacast(_clname);
}

int Widget_InspectorPropertyDouble::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
