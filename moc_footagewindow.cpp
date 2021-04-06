/****************************************************************************
** Meta object code from reading C++ file 'footagewindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dialogs/footagewindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'footagewindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_footageWindow_t {
    QByteArrayData data[20];
    char stringdata0[300];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_footageWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_footageWindow_t qt_meta_stringdata_footageWindow = {
    {
QT_MOC_LITERAL(0, 0, 13), // "footageWindow"
QT_MOC_LITERAL(1, 14, 9), // "openLocal"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 9), // "playPause"
QT_MOC_LITERAL(4, 35, 8), // "stopPlay"
QT_MOC_LITERAL(5, 44, 7), // "endPlay"
QT_MOC_LITERAL(6, 52, 18), // "on_analyze_clicked"
QT_MOC_LITERAL(7, 71, 9), // "update_ui"
QT_MOC_LITERAL(8, 81, 7), // "cv::Mat"
QT_MOC_LITERAL(9, 89, 32), // "std::vector<watchcam::rectangle>"
QT_MOC_LITERAL(10, 122, 49), // "std::vector<dlib::matrix<floa..."
QT_MOC_LITERAL(11, 172, 12), // "analyzeFaces"
QT_MOC_LITERAL(12, 185, 13), // "analyzeObject"
QT_MOC_LITERAL(13, 199, 16), // "analyzeBlacklist"
QT_MOC_LITERAL(14, 216, 10), // "analyzeAll"
QT_MOC_LITERAL(15, 227, 10), // "QList<int>"
QT_MOC_LITERAL(16, 238, 15), // "faceTileStation"
QT_MOC_LITERAL(17, 254, 17), // "objectTileStation"
QT_MOC_LITERAL(18, 272, 14), // "displayCluster"
QT_MOC_LITERAL(19, 287, 12) // "seekPlayTime"

    },
    "footageWindow\0openLocal\0\0playPause\0"
    "stopPlay\0endPlay\0on_analyze_clicked\0"
    "update_ui\0cv::Mat\0std::vector<watchcam::rectangle>\0"
    "std::vector<dlib::matrix<float,(long)0,(long)1> >\0"
    "analyzeFaces\0analyzeObject\0analyzeBlacklist\0"
    "analyzeAll\0QList<int>\0faceTileStation\0"
    "objectTileStation\0displayCluster\0"
    "seekPlayTime"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_footageWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   84,    2, 0x08 /* Private */,
       3,    1,   87,    2, 0x08 /* Private */,
       4,    1,   90,    2, 0x08 /* Private */,
       5,    0,   93,    2, 0x08 /* Private */,
       6,    0,   94,    2, 0x08 /* Private */,
       7,    5,   95,    2, 0x08 /* Private */,
      11,    1,  106,    2, 0x0a /* Public */,
      12,    2,  109,    2, 0x0a /* Public */,
      13,    1,  114,    2, 0x0a /* Public */,
      14,    8,  117,    2, 0x0a /* Public */,
      16,    4,  134,    2, 0x0a /* Public */,
      17,    3,  143,    2, 0x0a /* Public */,
      18,    1,  150,    2, 0x0a /* Public */,
      19,    1,  153,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8, 0x80000000 | 8, 0x80000000 | 9, QMetaType::Long, 0x80000000 | 10,    2,    2,    2,    2,    2,
    QMetaType::Void, QMetaType::QStringList,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    2,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::Bool, QMetaType::QStringList, QMetaType::Bool, 0x80000000 | 15, QMetaType::QStringList, QMetaType::Bool, QMetaType::QString, QMetaType::Int,    2,    2,    2,    2,    2,    2,    2,    2,
    QMetaType::Void, QMetaType::QPixmap, QMetaType::QString, QMetaType::Long, QMetaType::Int,    2,    2,    2,    2,
    QMetaType::Void, QMetaType::QPixmap, QMetaType::QString, QMetaType::Long,    2,    2,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Long,    2,

       0        // eod
};

void footageWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        footageWindow *_t = static_cast<footageWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->openLocal((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->playPause((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->stopPlay((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->endPlay(); break;
        case 4: _t->on_analyze_clicked(); break;
        case 5: _t->update_ui((*reinterpret_cast< cv::Mat(*)>(_a[1])),(*reinterpret_cast< cv::Mat(*)>(_a[2])),(*reinterpret_cast< std::vector<watchcam::rectangle>(*)>(_a[3])),(*reinterpret_cast< long(*)>(_a[4])),(*reinterpret_cast< std::vector<dlib::matrix<float,(long)0,(long)1> >(*)>(_a[5]))); break;
        case 6: _t->analyzeFaces((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 7: _t->analyzeObject((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 8: _t->analyzeBlacklist((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: _t->analyzeAll((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< QStringList(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< QList<int>(*)>(_a[4])),(*reinterpret_cast< QStringList(*)>(_a[5])),(*reinterpret_cast< bool(*)>(_a[6])),(*reinterpret_cast< QString(*)>(_a[7])),(*reinterpret_cast< int(*)>(_a[8]))); break;
        case 10: _t->faceTileStation((*reinterpret_cast< QPixmap(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< long(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 11: _t->objectTileStation((*reinterpret_cast< QPixmap(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< long(*)>(_a[3]))); break;
        case 12: _t->displayCluster((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->seekPlayTime((*reinterpret_cast< long(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 9:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 3:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<int> >(); break;
            }
            break;
        }
    }
}

const QMetaObject footageWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_footageWindow.data,
      qt_meta_data_footageWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *footageWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *footageWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_footageWindow.stringdata0))
        return static_cast<void*>(const_cast< footageWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int footageWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
