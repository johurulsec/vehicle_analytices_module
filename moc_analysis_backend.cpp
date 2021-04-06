/****************************************************************************
** Meta object code from reading C++ file 'analysis_backend.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "analysis_backend.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'analysis_backend.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_analysis_backend_t {
    QByteArrayData data[7];
    char stringdata0[124];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_analysis_backend_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_analysis_backend_t qt_meta_stringdata_analysis_backend = {
    {
QT_MOC_LITERAL(0, 0, 16), // "analysis_backend"
QT_MOC_LITERAL(1, 17, 5), // "ui_go"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 7), // "cv::Mat"
QT_MOC_LITERAL(4, 32, 32), // "std::vector<watchcam::rectangle>"
QT_MOC_LITERAL(5, 65, 49), // "std::vector<dlib::matrix<floa..."
QT_MOC_LITERAL(6, 115, 8) // "inf_loop"

    },
    "analysis_backend\0ui_go\0\0cv::Mat\0"
    "std::vector<watchcam::rectangle>\0"
    "std::vector<dlib::matrix<float,(long)0,(long)1> >\0"
    "inf_loop"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_analysis_backend[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    5,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   35,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3, 0x80000000 | 4, QMetaType::Long, 0x80000000 | 5,    2,    2,    2,    2,    2,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void analysis_backend::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        analysis_backend *_t = static_cast<analysis_backend *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ui_go((*reinterpret_cast< cv::Mat(*)>(_a[1])),(*reinterpret_cast< cv::Mat(*)>(_a[2])),(*reinterpret_cast< std::vector<watchcam::rectangle>(*)>(_a[3])),(*reinterpret_cast< long(*)>(_a[4])),(*reinterpret_cast< std::vector<dlib::matrix<float,(long)0,(long)1> >(*)>(_a[5]))); break;
        case 1: _t->inf_loop(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (analysis_backend::*_t)(cv::Mat , cv::Mat , std::vector<watchcam::rectangle> , long , std::vector<dlib::matrix<float,(long)0,(long)1>> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&analysis_backend::ui_go)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject analysis_backend::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_analysis_backend.data,
      qt_meta_data_analysis_backend,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *analysis_backend::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *analysis_backend::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_analysis_backend.stringdata0))
        return static_cast<void*>(const_cast< analysis_backend*>(this));
    return QObject::qt_metacast(_clname);
}

int analysis_backend::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void analysis_backend::ui_go(cv::Mat _t1, cv::Mat _t2, std::vector<watchcam::rectangle> _t3, long _t4, std::vector<dlib::matrix<float,(long)0,(long)1>> _t5)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
