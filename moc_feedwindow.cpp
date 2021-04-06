/****************************************************************************
** Meta object code from reading C++ file 'feedwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "feedwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'feedwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_FeedWindow_t {
    QByteArrayData data[13];
    char stringdata0[169];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FeedWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FeedWindow_t qt_meta_stringdata_FeedWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "FeedWindow"
QT_MOC_LITERAL(1, 11, 16), // "receiveVideoFeed"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 11), // "resizeEvent"
QT_MOC_LITERAL(4, 41, 13), // "QResizeEvent*"
QT_MOC_LITERAL(5, 55, 14), // "mouseMoveEvent"
QT_MOC_LITERAL(6, 70, 12), // "QMouseEvent*"
QT_MOC_LITERAL(7, 83, 15), // "mousePressEvent"
QT_MOC_LITERAL(8, 99, 17), // "mouseReleaseEvent"
QT_MOC_LITERAL(9, 117, 21), // "mouseDoubleClickEvent"
QT_MOC_LITERAL(10, 139, 10), // "wheelEvent"
QT_MOC_LITERAL(11, 150, 12), // "QWheelEvent*"
QT_MOC_LITERAL(12, 163, 5) // "event"

    },
    "FeedWindow\0receiveVideoFeed\0\0resizeEvent\0"
    "QResizeEvent*\0mouseMoveEvent\0QMouseEvent*\0"
    "mousePressEvent\0mouseReleaseEvent\0"
    "mouseDoubleClickEvent\0wheelEvent\0"
    "QWheelEvent*\0event"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FeedWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x0a /* Public */,
       3,    1,   52,    2, 0x0a /* Public */,
       5,    1,   55,    2, 0x0a /* Public */,
       7,    1,   58,    2, 0x0a /* Public */,
       8,    1,   61,    2, 0x0a /* Public */,
       9,    1,   64,    2, 0x0a /* Public */,
      10,    1,   67,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QPixmap,    2,
    QMetaType::Void, 0x80000000 | 4,    2,
    QMetaType::Void, 0x80000000 | 6,    2,
    QMetaType::Void, 0x80000000 | 6,    2,
    QMetaType::Void, 0x80000000 | 6,    2,
    QMetaType::Void, 0x80000000 | 6,    2,
    QMetaType::Void, 0x80000000 | 11,   12,

       0        // eod
};

void FeedWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FeedWindow *_t = static_cast<FeedWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->receiveVideoFeed((*reinterpret_cast< QPixmap(*)>(_a[1]))); break;
        case 1: _t->resizeEvent((*reinterpret_cast< QResizeEvent*(*)>(_a[1]))); break;
        case 2: _t->mouseMoveEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 3: _t->mousePressEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 4: _t->mouseReleaseEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 5: _t->mouseDoubleClickEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 6: _t->wheelEvent((*reinterpret_cast< QWheelEvent*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject FeedWindow::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_FeedWindow.data,
      qt_meta_data_FeedWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *FeedWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FeedWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_FeedWindow.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int FeedWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
