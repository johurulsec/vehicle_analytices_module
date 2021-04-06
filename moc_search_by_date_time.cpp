/****************************************************************************
** Meta object code from reading C++ file 'search_by_date_time.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Database/search_by_date_time.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'search_by_date_time.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_search_by_date_time_t {
    QByteArrayData data[6];
    char stringdata0[106];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_search_by_date_time_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_search_by_date_time_t qt_meta_stringdata_search_by_date_time = {
    {
QT_MOC_LITERAL(0, 0, 19), // "search_by_date_time"
QT_MOC_LITERAL(1, 20, 13), // "emitImagePath"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 28), // "on_pushButton_search_clicked"
QT_MOC_LITERAL(4, 64, 35), // "on_tableView_search_by_date_c..."
QT_MOC_LITERAL(5, 100, 5) // "index"

    },
    "search_by_date_time\0emitImagePath\0\0"
    "on_pushButton_search_clicked\0"
    "on_tableView_search_by_date_clicked\0"
    "index"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_search_by_date_time[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   32,    2, 0x08 /* Private */,
       4,    1,   33,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,    5,

       0        // eod
};

void search_by_date_time::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        search_by_date_time *_t = static_cast<search_by_date_time *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->emitImagePath((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->on_pushButton_search_clicked(); break;
        case 2: _t->on_tableView_search_by_date_clicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (search_by_date_time::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&search_by_date_time::emitImagePath)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject search_by_date_time::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_search_by_date_time.data,
      qt_meta_data_search_by_date_time,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *search_by_date_time::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *search_by_date_time::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_search_by_date_time.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int search_by_date_time::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
void search_by_date_time::emitImagePath(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
