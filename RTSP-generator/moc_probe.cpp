/****************************************************************************
** Meta object code from reading C++ file 'probe.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "probe.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'probe.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[16];
    char stringdata0[393];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 18), // "onDiscoveredDevice"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 10), // "DescDevice"
QT_MOC_LITERAL(4, 42, 22), // "on_btnSendProb_clicked"
QT_MOC_LITERAL(5, 65, 25), // "on_btnGetMediaURL_clicked"
QT_MOC_LITERAL(6, 91, 34), // "on_btnGetDeviceInformation_cl..."
QT_MOC_LITERAL(7, 126, 21), // "on_btnPTZTest_clicked"
QT_MOC_LITERAL(8, 148, 26), // "on_btnReceiverTest_clicked"
QT_MOC_LITERAL(9, 175, 23), // "on_btnEventTest_clicked"
QT_MOC_LITERAL(10, 199, 27), // "on_btnAnalyticsTest_clicked"
QT_MOC_LITERAL(11, 227, 38), // "on_btnVideoAnalyticsDeviceTes..."
QT_MOC_LITERAL(12, 266, 34), // "on_btnRecordingControlTest_cl..."
QT_MOC_LITERAL(13, 301, 33), // "on_btnRecordingSearchTest_cli..."
QT_MOC_LITERAL(14, 335, 31), // "on_btnReplayControlTest_clicked"
QT_MOC_LITERAL(15, 367, 25) // "on_btnDisplayTest_clicked"

    },
    "MainWindow\0onDiscoveredDevice\0\0"
    "DescDevice\0on_btnSendProb_clicked\0"
    "on_btnGetMediaURL_clicked\0"
    "on_btnGetDeviceInformation_clicked\0"
    "on_btnPTZTest_clicked\0on_btnReceiverTest_clicked\0"
    "on_btnEventTest_clicked\0"
    "on_btnAnalyticsTest_clicked\0"
    "on_btnVideoAnalyticsDeviceTest_clicked\0"
    "on_btnRecordingControlTest_clicked\0"
    "on_btnRecordingSearchTest_clicked\0"
    "on_btnReplayControlTest_clicked\0"
    "on_btnDisplayTest_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x08 /* Private */,
       4,    0,   82,    2, 0x08 /* Private */,
       5,    0,   83,    2, 0x08 /* Private */,
       6,    0,   84,    2, 0x08 /* Private */,
       7,    0,   85,    2, 0x08 /* Private */,
       8,    0,   86,    2, 0x08 /* Private */,
       9,    0,   87,    2, 0x08 /* Private */,
      10,    0,   88,    2, 0x08 /* Private */,
      11,    0,   89,    2, 0x08 /* Private */,
      12,    0,   90,    2, 0x08 /* Private */,
      13,    0,   91,    2, 0x08 /* Private */,
      14,    0,   92,    2, 0x08 /* Private */,
      15,    0,   93,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onDiscoveredDevice((*reinterpret_cast< DescDevice(*)>(_a[1]))); break;
        case 1: _t->on_btnSendProb_clicked(); break;
        case 2: _t->on_btnGetMediaURL_clicked(); break;
        case 3: _t->on_btnGetDeviceInformation_clicked(); break;
        case 4: _t->on_btnPTZTest_clicked(); break;
        case 5: _t->on_btnReceiverTest_clicked(); break;
        case 6: _t->on_btnEventTest_clicked(); break;
        case 7: _t->on_btnAnalyticsTest_clicked(); break;
        case 8: _t->on_btnVideoAnalyticsDeviceTest_clicked(); break;
        case 9: _t->on_btnRecordingControlTest_clicked(); break;
        case 10: _t->on_btnRecordingSearchTest_clicked(); break;
        case 11: _t->on_btnReplayControlTest_clicked(); break;
        case 12: _t->on_btnDisplayTest_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< DescDevice >(); break;
            }
            break;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
