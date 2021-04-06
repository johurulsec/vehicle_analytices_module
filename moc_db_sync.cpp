/****************************************************************************
** Meta object code from reading C++ file 'db_sync.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "db_sync/db_sync.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'db_sync.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_db_sync_t {
    QByteArrayData data[16];
    char stringdata0[138];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_db_sync_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_db_sync_t qt_meta_stringdata_db_sync = {
    {
QT_MOC_LITERAL(0, 0, 7), // "db_sync"
QT_MOC_LITERAL(1, 8, 17), // "workRequestedSyTh"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 12), // "finishedSyTh"
QT_MOC_LITERAL(4, 40, 10), // "insertToDb"
QT_MOC_LITERAL(5, 51, 2), // "Id"
QT_MOC_LITERAL(6, 54, 3), // "pic"
QT_MOC_LITERAL(7, 58, 3), // "str"
QT_MOC_LITERAL(8, 62, 4), // "indx"
QT_MOC_LITERAL(9, 67, 10), // "confidence"
QT_MOC_LITERAL(10, 78, 9), // "date_time"
QT_MOC_LITERAL(11, 88, 11), // "sync_states"
QT_MOC_LITERAL(12, 100, 4), // "date"
QT_MOC_LITERAL(13, 105, 10), // "image_path"
QT_MOC_LITERAL(14, 116, 10), // "image_name"
QT_MOC_LITERAL(15, 127, 10) // "doWarkSync"

    },
    "db_sync\0workRequestedSyTh\0\0finishedSyTh\0"
    "insertToDb\0Id\0pic\0str\0indx\0confidence\0"
    "date_time\0sync_states\0date\0image_path\0"
    "image_name\0doWarkSync"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_db_sync[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,
       3,    0,   35,    2, 0x06 /* Public */,
       4,   12,   36,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      15,    6,   61,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::QPixmap, QMetaType::QString, QMetaType::Int, QMetaType::Double, QMetaType::QString, QMetaType::Int, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::Int, QMetaType::QString,    5,    6,    7,    8,    9,   10,   11,   12,   13,   14,    2,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::QPixmap, QMetaType::QString, QMetaType::Int, QMetaType::Double, QMetaType::QString,    5,    2,    2,    2,    2,    2,

       0        // eod
};

void db_sync::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        db_sync *_t = static_cast<db_sync *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->workRequestedSyTh(); break;
        case 1: _t->finishedSyTh(); break;
        case 2: _t->insertToDb((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QPixmap(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< double(*)>(_a[5])),(*reinterpret_cast< QString(*)>(_a[6])),(*reinterpret_cast< int(*)>(_a[7])),(*reinterpret_cast< QString(*)>(_a[8])),(*reinterpret_cast< QString(*)>(_a[9])),(*reinterpret_cast< QString(*)>(_a[10])),(*reinterpret_cast< int(*)>(_a[11])),(*reinterpret_cast< QString(*)>(_a[12]))); break;
        case 3: _t->doWarkSync((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QPixmap(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< double(*)>(_a[5])),(*reinterpret_cast< QString(*)>(_a[6]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (db_sync::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&db_sync::workRequestedSyTh)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (db_sync::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&db_sync::finishedSyTh)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (db_sync::*_t)(int , QPixmap , QString , int , double , QString , int , QString , QString , QString , int , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&db_sync::insertToDb)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject db_sync::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_db_sync.data,
      qt_meta_data_db_sync,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *db_sync::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *db_sync::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_db_sync.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int db_sync::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void db_sync::workRequestedSyTh()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void db_sync::finishedSyTh()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void db_sync::insertToDb(int _t1, QPixmap _t2, QString _t3, int _t4, double _t5, QString _t6, int _t7, QString _t8, QString _t9, QString _t10, int _t11, QString _t12)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)), const_cast<void*>(reinterpret_cast<const void*>(&_t6)), const_cast<void*>(reinterpret_cast<const void*>(&_t7)), const_cast<void*>(reinterpret_cast<const void*>(&_t8)), const_cast<void*>(reinterpret_cast<const void*>(&_t9)), const_cast<void*>(reinterpret_cast<const void*>(&_t10)), const_cast<void*>(reinterpret_cast<const void*>(&_t11)), const_cast<void*>(reinterpret_cast<const void*>(&_t12)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
