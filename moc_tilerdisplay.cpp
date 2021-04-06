/****************************************************************************
** Meta object code from reading C++ file 'tilerdisplay.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "tilerdisplay.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tilerdisplay.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TilerDisplay_t {
    QByteArrayData data[6];
    char stringdata0[115];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TilerDisplay_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TilerDisplay_t qt_meta_stringdata_TilerDisplay = {
    {
QT_MOC_LITERAL(0, 0, 12), // "TilerDisplay"
QT_MOC_LITERAL(1, 13, 29), // "displayLPCorespondingCarImage"
QT_MOC_LITERAL(2, 43, 0), // ""
QT_MOC_LITERAL(3, 44, 22), // "add_search_lp_To_tiles"
QT_MOC_LITERAL(4, 67, 29), // "uniqueLicencePlateShowInTiles"
QT_MOC_LITERAL(5, 97, 17) // "personShowInTiles"

    },
    "TilerDisplay\0displayLPCorespondingCarImage\0"
    "\0add_search_lp_To_tiles\0"
    "uniqueLicencePlateShowInTiles\0"
    "personShowInTiles"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TilerDisplay[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x0a /* Public */,
       3,    4,   37,    2, 0x0a /* Public */,
       4,    4,   46,    2, 0x0a /* Public */,
       5,    4,   55,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::QPixmap, QMetaType::QString, QMetaType::Int, QMetaType::QString,    2,    2,    2,    2,
    QMetaType::Void, QMetaType::QPixmap, QMetaType::QString, QMetaType::Int, QMetaType::QString,    2,    2,    2,    2,
    QMetaType::Void, QMetaType::QPixmap, QMetaType::QString, QMetaType::Int, QMetaType::QString,    2,    2,    2,    2,

       0        // eod
};

void TilerDisplay::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TilerDisplay *_t = static_cast<TilerDisplay *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->displayLPCorespondingCarImage((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->add_search_lp_To_tiles((*reinterpret_cast< QPixmap(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 2: _t->uniqueLicencePlateShowInTiles((*reinterpret_cast< QPixmap(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 3: _t->personShowInTiles((*reinterpret_cast< QPixmap(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        default: ;
        }
    }
}

const QMetaObject TilerDisplay::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_TilerDisplay.data,
      qt_meta_data_TilerDisplay,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *TilerDisplay::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TilerDisplay::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TilerDisplay.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int TilerDisplay::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
