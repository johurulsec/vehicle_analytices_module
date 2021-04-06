/****************************************************************************
** Meta object code from reading C++ file 'camera.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "camera.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'camera.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Camera_t {
    QByteArrayData data[14];
    char stringdata0[144];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Camera_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Camera_t qt_meta_stringdata_Camera = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Camera"
QT_MOC_LITERAL(1, 7, 15), // "start_requested"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 14), // "start_producer"
QT_MOC_LITERAL(4, 39, 16), // "requestUpdateLPR"
QT_MOC_LITERAL(5, 56, 3), // "enc"
QT_MOC_LITERAL(6, 60, 5), // "ui_go"
QT_MOC_LITERAL(7, 66, 7), // "cv::Mat"
QT_MOC_LITERAL(8, 74, 32), // "std::vector<watchcam::rectangle>"
QT_MOC_LITERAL(9, 107, 2), // "go"
QT_MOC_LITERAL(10, 110, 8), // "sendToUI"
QT_MOC_LITERAL(11, 119, 8), // "inf_loop"
QT_MOC_LITERAL(12, 128, 11), // "ui_response"
QT_MOC_LITERAL(13, 140, 3) // "img"

    },
    "Camera\0start_requested\0\0start_producer\0"
    "requestUpdateLPR\0enc\0ui_go\0cv::Mat\0"
    "std::vector<watchcam::rectangle>\0go\0"
    "sendToUI\0inf_loop\0ui_response\0img"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Camera[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06 /* Public */,
       3,    0,   55,    2, 0x06 /* Public */,
       4,    1,   56,    2, 0x06 /* Public */,
       6,    3,   59,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,   66,    2, 0x0a /* Public */,
      10,    3,   67,    2, 0x0a /* Public */,
      11,    0,   74,    2, 0x0a /* Public */,
      12,    1,   75,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, 0x80000000 | 7, 0x80000000 | 7, 0x80000000 | 8,    2,    2,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7, 0x80000000 | 7, 0x80000000 | 8,    2,    2,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPixmap,   13,

       0        // eod
};

void Camera::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Camera *_t = static_cast<Camera *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->start_requested(); break;
        case 1: _t->start_producer(); break;
        case 2: _t->requestUpdateLPR((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->ui_go((*reinterpret_cast< cv::Mat(*)>(_a[1])),(*reinterpret_cast< cv::Mat(*)>(_a[2])),(*reinterpret_cast< std::vector<watchcam::rectangle>(*)>(_a[3]))); break;
        case 4: _t->go(); break;
        case 5: _t->sendToUI((*reinterpret_cast< cv::Mat(*)>(_a[1])),(*reinterpret_cast< cv::Mat(*)>(_a[2])),(*reinterpret_cast< std::vector<watchcam::rectangle>(*)>(_a[3]))); break;
        case 6: _t->inf_loop(); break;
        case 7: _t->ui_response((*reinterpret_cast< QPixmap(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (Camera::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Camera::start_requested)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (Camera::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Camera::start_producer)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (Camera::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Camera::requestUpdateLPR)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (Camera::*_t)(cv::Mat , cv::Mat , std::vector<watchcam::rectangle> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Camera::ui_go)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject Camera::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Camera.data,
      qt_meta_data_Camera,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Camera::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Camera::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Camera.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Camera::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void Camera::start_requested()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Camera::start_producer()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Camera::requestUpdateLPR(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Camera::ui_go(cv::Mat _t1, cv::Mat _t2, std::vector<watchcam::rectangle> _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
