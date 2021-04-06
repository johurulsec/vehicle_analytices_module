/****************************************************************************
** Meta object code from reading C++ file 'face.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "face.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'face.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Face_t {
    QByteArrayData data[7];
    char stringdata0[59];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Face_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Face_t qt_meta_stringdata_Face = {
    {
QT_MOC_LITERAL(0, 0, 4), // "Face"
QT_MOC_LITERAL(1, 5, 11), // "emitCluster"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 9), // "emitPicDB"
QT_MOC_LITERAL(4, 28, 15), // "mousePressEvent"
QT_MOC_LITERAL(5, 44, 12), // "QMouseEvent*"
QT_MOC_LITERAL(6, 57, 1) // "e"

    },
    "Face\0emitCluster\0\0emitPicDB\0mousePressEvent\0"
    "QMouseEvent*\0e"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Face[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,
       3,    1,   32,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   35,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::QPixmap,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 5,    6,

       0        // eod
};

void Face::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Face *_t = static_cast<Face *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->emitCluster((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->emitPicDB((*reinterpret_cast< QPixmap(*)>(_a[1]))); break;
        case 2: _t->mousePressEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (Face::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Face::emitCluster)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (Face::*_t)(QPixmap );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Face::emitPicDB)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject Face::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Face.data,
      qt_meta_data_Face,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Face::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Face::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Face.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Face::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void Face::emitCluster(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Face::emitPicDB(QPixmap _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
