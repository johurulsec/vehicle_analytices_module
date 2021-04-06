/****************************************************************************
** Meta object code from reading C++ file 'feed.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "feed.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'feed.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Feed_t {
    QByteArrayData data[25];
    char stringdata0[286];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Feed_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Feed_t qt_meta_stringdata_Feed = {
    {
QT_MOC_LITERAL(0, 0, 4), // "Feed"
QT_MOC_LITERAL(1, 5, 8), // "emitFace"
QT_MOC_LITERAL(2, 14, 0), // ""
QT_MOC_LITERAL(3, 15, 7), // "cv::Mat"
QT_MOC_LITERAL(4, 23, 6), // "emitLP"
QT_MOC_LITERAL(5, 30, 13), // "emitVideoFeed"
QT_MOC_LITERAL(6, 44, 8), // "emitTile"
QT_MOC_LITERAL(7, 53, 6), // "notify"
QT_MOC_LITERAL(8, 60, 9), // "addCamera"
QT_MOC_LITERAL(9, 70, 16), // "initializeCamera"
QT_MOC_LITERAL(10, 87, 6), // "Fprior"
QT_MOC_LITERAL(11, 94, 6), // "Lprior"
QT_MOC_LITERAL(12, 101, 20), // "initializeCameraMain"
QT_MOC_LITERAL(13, 122, 6), // "camera"
QT_MOC_LITERAL(14, 129, 5), // "prior"
QT_MOC_LITERAL(15, 135, 11), // "closeCamera"
QT_MOC_LITERAL(16, 147, 13), // "enlargeCamera"
QT_MOC_LITERAL(17, 161, 9), // "tilesOpen"
QT_MOC_LITERAL(18, 171, 9), // "update_ui"
QT_MOC_LITERAL(19, 181, 32), // "std::vector<watchcam::rectangle>"
QT_MOC_LITERAL(20, 214, 11), // "changeColor"
QT_MOC_LITERAL(21, 226, 11), // "faceStation"
QT_MOC_LITERAL(22, 238, 10), // "lprStation"
QT_MOC_LITERAL(23, 249, 19), // "closeEnlargedWindow"
QT_MOC_LITERAL(24, 269, 16) // "closeTilesWindow"

    },
    "Feed\0emitFace\0\0cv::Mat\0emitLP\0"
    "emitVideoFeed\0emitTile\0notify\0addCamera\0"
    "initializeCamera\0Fprior\0Lprior\0"
    "initializeCameraMain\0camera\0prior\0"
    "closeCamera\0enlargeCamera\0tilesOpen\0"
    "update_ui\0std::vector<watchcam::rectangle>\0"
    "changeColor\0faceStation\0lprStation\0"
    "closeEnlargedWindow\0closeTilesWindow"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Feed[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   99,    2, 0x06 /* Public */,
       4,    2,  104,    2, 0x06 /* Public */,
       5,    1,  109,    2, 0x06 /* Public */,
       6,    3,  112,    2, 0x06 /* Public */,
       7,    3,  119,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    1,  126,    2, 0x0a /* Public */,
       9,    5,  129,    2, 0x0a /* Public */,
      12,    2,  140,    2, 0x0a /* Public */,
      15,    1,  145,    2, 0x0a /* Public */,
      16,    1,  148,    2, 0x0a /* Public */,
      17,    1,  151,    2, 0x0a /* Public */,
      18,    3,  154,    2, 0x0a /* Public */,
      20,    0,  161,    2, 0x0a /* Public */,
      21,    2,  162,    2, 0x0a /* Public */,
      22,    2,  167,    2, 0x0a /* Public */,
      23,    1,  172,    2, 0x0a /* Public */,
      24,    1,  175,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::QPixmap, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::QPixmap,    2,
    QMetaType::Void, QMetaType::QPixmap, QMetaType::QString, QMetaType::Int,    2,    2,    2,
    QMetaType::Void, QMetaType::QPixmap, QMetaType::QString, QMetaType::Int,    2,    2,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool,    2,    2,    2,   10,   11,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   13,   14,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3, 0x80000000 | 19,    2,    2,    2,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::QPixmap, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

void Feed::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Feed *_t = static_cast<Feed *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->emitFace((*reinterpret_cast< cv::Mat(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->emitLP((*reinterpret_cast< QPixmap(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->emitVideoFeed((*reinterpret_cast< QPixmap(*)>(_a[1]))); break;
        case 3: _t->emitTile((*reinterpret_cast< QPixmap(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 4: _t->notify((*reinterpret_cast< QPixmap(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 5: _t->addCamera((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->initializeCamera((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4])),(*reinterpret_cast< bool(*)>(_a[5]))); break;
        case 7: _t->initializeCameraMain((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 8: _t->closeCamera((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->enlargeCamera((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->tilesOpen((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: _t->update_ui((*reinterpret_cast< cv::Mat(*)>(_a[1])),(*reinterpret_cast< cv::Mat(*)>(_a[2])),(*reinterpret_cast< std::vector<watchcam::rectangle>(*)>(_a[3]))); break;
        case 12: _t->changeColor(); break;
        case 13: _t->faceStation((*reinterpret_cast< cv::Mat(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 14: _t->lprStation((*reinterpret_cast< QPixmap(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 15: _t->closeEnlargedWindow((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->closeTilesWindow((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (Feed::*_t)(cv::Mat , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Feed::emitFace)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (Feed::*_t)(QPixmap , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Feed::emitLP)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (Feed::*_t)(QPixmap );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Feed::emitVideoFeed)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (Feed::*_t)(QPixmap , QString , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Feed::emitTile)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (Feed::*_t)(QPixmap , QString , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Feed::notify)) {
                *result = 4;
                return;
            }
        }
    }
}

const QMetaObject Feed::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Feed.data,
      qt_meta_data_Feed,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Feed::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Feed::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Feed.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Feed::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void Feed::emitFace(cv::Mat _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Feed::emitLP(QPixmap _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Feed::emitVideoFeed(QPixmap _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Feed::emitTile(QPixmap _t1, QString _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Feed::notify(QPixmap _t1, QString _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
