/****************************************************************************
** Meta object code from reading C++ file 'overcrowdthread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "overcrowdthread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'overcrowdthread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_OvercrowdThread_t {
    QByteArrayData data[6];
    char stringdata0[75];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_OvercrowdThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_OvercrowdThread_t qt_meta_stringdata_OvercrowdThread = {
    {
QT_MOC_LITERAL(0, 0, 15), // "OvercrowdThread"
QT_MOC_LITERAL(1, 16, 20), // "requestedOverThStart"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 14), // "finishedOverTh"
QT_MOC_LITERAL(4, 53, 14), // "valueFRChanged"
QT_MOC_LITERAL(5, 68, 6) // "dowark"

    },
    "OvercrowdThread\0requestedOverThStart\0"
    "\0finishedOverTh\0valueFRChanged\0dowark"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_OvercrowdThread[] = {

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
       4,    2,   36,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   41,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPixmap, QMetaType::Int,    2,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

void OvercrowdThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        OvercrowdThread *_t = static_cast<OvercrowdThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->requestedOverThStart(); break;
        case 1: _t->finishedOverTh(); break;
        case 2: _t->valueFRChanged((*reinterpret_cast< QPixmap(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->dowark((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (OvercrowdThread::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OvercrowdThread::requestedOverThStart)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (OvercrowdThread::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OvercrowdThread::finishedOverTh)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (OvercrowdThread::*_t)(QPixmap , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OvercrowdThread::valueFRChanged)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject OvercrowdThread::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_OvercrowdThread.data,
      qt_meta_data_OvercrowdThread,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *OvercrowdThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *OvercrowdThread::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_OvercrowdThread.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int OvercrowdThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void OvercrowdThread::requestedOverThStart()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void OvercrowdThread::finishedOverTh()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void OvercrowdThread::valueFRChanged(QPixmap _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
