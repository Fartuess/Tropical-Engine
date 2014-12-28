/****************************************************************************
** Meta object code from reading C++ file 'TropicalEngineApplication.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Header Files/TropicalEngineApplication.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TropicalEngineApplication.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TropicalEngineApplication_t {
    QByteArrayData data[4];
    char stringdata[43];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TropicalEngineApplication_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TropicalEngineApplication_t qt_meta_stringdata_TropicalEngineApplication = {
    {
QT_MOC_LITERAL(0, 0, 25), // "TropicalEngineApplication"
QT_MOC_LITERAL(1, 26, 10), // "Initialize"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 4) // "Draw"

    },
    "TropicalEngineApplication\0Initialize\0"
    "\0Draw"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TropicalEngineApplication[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x0a /* Public */,
       3,    0,   25,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void TropicalEngineApplication::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TropicalEngineApplication *_t = static_cast<TropicalEngineApplication *>(_o);
        switch (_id) {
        case 0: _t->Initialize(); break;
        case 1: _t->Draw(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject TropicalEngineApplication::staticMetaObject = {
    { &QApplication::staticMetaObject, qt_meta_stringdata_TropicalEngineApplication.data,
      qt_meta_data_TropicalEngineApplication,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TropicalEngineApplication::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TropicalEngineApplication::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TropicalEngineApplication.stringdata))
        return static_cast<void*>(const_cast< TropicalEngineApplication*>(this));
    return QApplication::qt_metacast(_clname);
}

int TropicalEngineApplication::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QApplication::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
