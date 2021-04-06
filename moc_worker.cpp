/****************************************************************************
** Meta object code from reading C++ file 'worker.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "worker.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'worker.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Worker_t {
    QByteArrayData data[24];
    char stringdata0[207];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Worker_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Worker_t qt_meta_stringdata_Worker = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Worker"
QT_MOC_LITERAL(1, 7, 13), // "workRequested"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 12), // "valueChanged"
QT_MOC_LITERAL(4, 35, 3), // "pic"
QT_MOC_LITERAL(5, 39, 3), // "str"
QT_MOC_LITERAL(6, 43, 4), // "indx"
QT_MOC_LITERAL(7, 48, 9), // "first_pic"
QT_MOC_LITERAL(8, 58, 9), // "first_str"
QT_MOC_LITERAL(9, 68, 10), // "second_pic"
QT_MOC_LITERAL(10, 79, 10), // "second_str"
QT_MOC_LITERAL(11, 90, 8), // "finished"
QT_MOC_LITERAL(12, 99, 14), // "QNetworkReply*"
QT_MOC_LITERAL(13, 114, 3), // "rep"
QT_MOC_LITERAL(14, 118, 11), // "finishedLPR"
QT_MOC_LITERAL(15, 130, 9), // "plateData"
QT_MOC_LITERAL(16, 140, 1), // "p"
QT_MOC_LITERAL(17, 142, 6), // "doWork"
QT_MOC_LITERAL(18, 149, 7), // "cv::Mat"
QT_MOC_LITERAL(19, 157, 7), // "picture"
QT_MOC_LITERAL(20, 165, 6), // "LPRcap"
QT_MOC_LITERAL(21, 172, 5), // "encod"
QT_MOC_LITERAL(22, 178, 19), // "syncRequestFinished"
QT_MOC_LITERAL(23, 198, 8) // "LPRprint"

    },
    "Worker\0workRequested\0\0valueChanged\0"
    "pic\0str\0indx\0first_pic\0first_str\0"
    "second_pic\0second_str\0finished\0"
    "QNetworkReply*\0rep\0finishedLPR\0plateData\0"
    "p\0doWork\0cv::Mat\0picture\0LPRcap\0encod\0"
    "syncRequestFinished\0LPRprint"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Worker[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x06 /* Public */,
       3,    5,   65,    2, 0x06 /* Public */,
       3,    4,   76,    2, 0x06 /* Public */,
      11,    1,   85,    2, 0x06 /* Public */,
      14,    0,   88,    2, 0x06 /* Public */,
      15,    1,   89,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      17,    6,   92,    2, 0x0a /* Public */,
      20,    1,  105,    2, 0x0a /* Public */,
      22,    1,  108,    2, 0x0a /* Public */,
      23,    3,  111,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPixmap, QMetaType::QPixmap, QMetaType::QString, QMetaType::Int, QMetaType::QString,    2,    4,    5,    6,    2,
    QMetaType::Void, QMetaType::QPixmap, QMetaType::QString, QMetaType::QPixmap, QMetaType::QString,    7,    8,    9,   10,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   16,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 18, 0x80000000 | 18, QMetaType::QString, QMetaType::Int, QMetaType::QString, QMetaType::QString,    2,   19,    5,    6,    2,    2,
    QMetaType::QString, QMetaType::QString,   21,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, QMetaType::QPixmap, QMetaType::QString, QMetaType::Int,    4,    5,    6,

       0        // eod
};

void Worker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Worker *_t = static_cast<Worker *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->workRequested(); break;
        case 1: _t->valueChanged((*reinterpret_cast< QPixmap(*)>(_a[1])),(*reinterpret_cast< QPixmap(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5]))); break;
        case 2: _t->valueChanged((*reinterpret_cast< QPixmap(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QPixmap(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 3: _t->finished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 4: _t->finishedLPR(); break;
        case 5: _t->plateData((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->doWork((*reinterpret_cast< cv::Mat(*)>(_a[1])),(*reinterpret_cast< cv::Mat(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5])),(*reinterpret_cast< QString(*)>(_a[6]))); break;
        case 7: { QString _r = _t->LPRcap((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 8: _t->syncRequestFinished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 9: _t->LPRprint((*reinterpret_cast< QPixmap(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (Worker::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Worker::workRequested)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (Worker::*_t)(QPixmap , QPixmap , QString , int , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Worker::valueChanged)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (Worker::*_t)(QPixmap , QString , QPixmap , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Worker::valueChanged)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (Worker::*_t)(QNetworkReply * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Worker::finished)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (Worker::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Worker::finishedLPR)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (Worker::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Worker::plateData)) {
                *result = 5;
                return;
            }
        }
    }
}

const QMetaObject Worker::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Worker.data,
      qt_meta_data_Worker,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Worker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Worker::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Worker.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Worker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void Worker::workRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Worker::valueChanged(QPixmap _t1, QPixmap _t2, QString _t3, int _t4, QString _t5)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Worker::valueChanged(QPixmap _t1, QString _t2, QPixmap _t3, QString _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Worker::finished(QNetworkReply * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Worker::finishedLPR()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void Worker::plateData(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
