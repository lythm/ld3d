/****************************************************************************
** Meta object code from reading C++ file 'gamestudio.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.0.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stdafx.h"
#include "../../gamestudio.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gamestudio.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.0.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_GameStudio_t {
    QByteArrayData data[18];
    char stringdata[395];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_GameStudio_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_GameStudio_t qt_meta_stringdata_GameStudio = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 23),
QT_MOC_LITERAL(2, 35, 0),
QT_MOC_LITERAL(3, 36, 30),
QT_MOC_LITERAL(4, 67, 32),
QT_MOC_LITERAL(5, 100, 31),
QT_MOC_LITERAL(6, 132, 31),
QT_MOC_LITERAL(7, 164, 29),
QT_MOC_LITERAL(8, 194, 14),
QT_MOC_LITERAL(9, 209, 4),
QT_MOC_LITERAL(10, 214, 28),
QT_MOC_LITERAL(11, 243, 29),
QT_MOC_LITERAL(12, 273, 32),
QT_MOC_LITERAL(13, 306, 29),
QT_MOC_LITERAL(14, 336, 12),
QT_MOC_LITERAL(15, 349, 11),
QT_MOC_LITERAL(16, 361, 16),
QT_MOC_LITERAL(17, 378, 15)
    },
    "GameStudio\0on_menuFile_aboutToShow\0\0"
    "on_actionNew_Project_triggered\0"
    "on_actionClose_Project_triggered\0"
    "on_actionSave_Project_triggered\0"
    "on_actionOpen_Project_triggered\0"
    "on_mdiArea_subWindowActivated\0"
    "QMdiSubWindow*\0pSub\0on_actionNew_Scene_triggered\0"
    "on_actionSave_Scene_triggered\0"
    "on_actionSave_Scene_As_triggered\0"
    "on_actionOpen_Scene_triggered\0"
    "GetFormScene\0Form_Scene*\0GetFormHierarchy\0"
    "Form_Hierarchy*\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GameStudio[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x0a,
       3,    0,   75,    2, 0x0a,
       4,    0,   76,    2, 0x0a,
       5,    0,   77,    2, 0x0a,
       6,    0,   78,    2, 0x0a,
       7,    1,   79,    2, 0x0a,
      10,    0,   82,    2, 0x0a,
      11,    0,   83,    2, 0x0a,
      12,    0,   84,    2, 0x0a,
      13,    0,   85,    2, 0x0a,
      14,    0,   86,    2, 0x0a,
      16,    0,   87,    2, 0x0a,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    0x80000000 | 15,
    0x80000000 | 17,

       0        // eod
};

void GameStudio::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GameStudio *_t = static_cast<GameStudio *>(_o);
        switch (_id) {
        case 0: _t->on_menuFile_aboutToShow(); break;
        case 1: _t->on_actionNew_Project_triggered(); break;
        case 2: _t->on_actionClose_Project_triggered(); break;
        case 3: _t->on_actionSave_Project_triggered(); break;
        case 4: _t->on_actionOpen_Project_triggered(); break;
        case 5: _t->on_mdiArea_subWindowActivated((*reinterpret_cast< QMdiSubWindow*(*)>(_a[1]))); break;
        case 6: _t->on_actionNew_Scene_triggered(); break;
        case 7: _t->on_actionSave_Scene_triggered(); break;
        case 8: _t->on_actionSave_Scene_As_triggered(); break;
        case 9: _t->on_actionOpen_Scene_triggered(); break;
        case 10: { Form_Scene* _r = _t->GetFormScene();
            if (_a[0]) *reinterpret_cast< Form_Scene**>(_a[0]) = _r; }  break;
        case 11: { Form_Hierarchy* _r = _t->GetFormHierarchy();
            if (_a[0]) *reinterpret_cast< Form_Hierarchy**>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObject GameStudio::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_GameStudio.data,
      qt_meta_data_GameStudio,  qt_static_metacall, 0, 0}
};


const QMetaObject *GameStudio::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GameStudio::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GameStudio.stringdata))
        return static_cast<void*>(const_cast< GameStudio*>(this));
    if (!strcmp(_clname, "Ui::GameStudioClass"))
        return static_cast< Ui::GameStudioClass*>(const_cast< GameStudio*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int GameStudio::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
