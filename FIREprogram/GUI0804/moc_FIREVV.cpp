/****************************************************************************
** Meta object code from reading C++ file 'FIREVV.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "FIREVV.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'FIREVV.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_FIREVV_t {
    QByteArrayData data[17];
    char stringdata0[161];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FIREVV_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FIREVV_t qt_meta_stringdata_FIREVV = {
    {
QT_MOC_LITERAL(0, 0, 6), // "FIREVV"
QT_MOC_LITERAL(1, 7, 7), // "created"
QT_MOC_LITERAL(2, 15, 0), // ""
QT_MOC_LITERAL(3, 16, 5), // "VVfin"
QT_MOC_LITERAL(4, 22, 7), // "minfunc"
QT_MOC_LITERAL(5, 30, 7), // "GenInit"
QT_MOC_LITERAL(6, 38, 10), // "PHIChanged"
QT_MOC_LITERAL(7, 49, 12), // "M_varChanged"
QT_MOC_LITERAL(8, 62, 10), // "EngChanged"
QT_MOC_LITERAL(9, 73, 7), // "pluseig"
QT_MOC_LITERAL(10, 81, 8), // "minuseig"
QT_MOC_LITERAL(11, 90, 10), // "eNumchaged"
QT_MOC_LITERAL(12, 101, 8), // "VerletDO"
QT_MOC_LITERAL(13, 110, 7), // "Tapping"
QT_MOC_LITERAL(14, 118, 5), // "Noise"
QT_MOC_LITERAL(15, 124, 12), // "SoftAnalysis"
QT_MOC_LITERAL(16, 137, 23) // "initializeParticleColor"

    },
    "FIREVV\0created\0\0VVfin\0minfunc\0GenInit\0"
    "PHIChanged\0M_varChanged\0EngChanged\0"
    "pluseig\0minuseig\0eNumchaged\0VerletDO\0"
    "Tapping\0Noise\0SoftAnalysis\0"
    "initializeParticleColor"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FIREVV[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      10,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   89,    2, 0x06 /* Public */,
       3,    0,   90,    2, 0x06 /* Public */,
       4,    0,   91,    2, 0x06 /* Public */,
       5,    0,   92,    2, 0x06 /* Public */,
       6,    0,   93,    2, 0x06 /* Public */,
       7,    0,   94,    2, 0x06 /* Public */,
       8,    0,   95,    2, 0x06 /* Public */,
       9,    0,   96,    2, 0x06 /* Public */,
      10,    0,   97,    2, 0x06 /* Public */,
      11,    0,   98,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      12,    0,   99,    2, 0x0a /* Public */,
      13,    0,  100,    2, 0x0a /* Public */,
      14,    0,  101,    2, 0x0a /* Public */,
      15,    0,  102,    2, 0x0a /* Public */,
      16,    0,  103,    2, 0x0a /* Public */,

 // signals: parameters
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

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void FIREVV::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FIREVV *_t = static_cast<FIREVV *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->created(); break;
        case 1: _t->VVfin(); break;
        case 2: _t->minfunc(); break;
        case 3: _t->GenInit(); break;
        case 4: _t->PHIChanged(); break;
        case 5: _t->M_varChanged(); break;
        case 6: _t->EngChanged(); break;
        case 7: _t->pluseig(); break;
        case 8: _t->minuseig(); break;
        case 9: _t->eNumchaged(); break;
        case 10: _t->VerletDO(); break;
        case 11: _t->Tapping(); break;
        case 12: _t->Noise(); break;
        case 13: _t->SoftAnalysis(); break;
        case 14: _t->initializeParticleColor(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (FIREVV::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FIREVV::created)) {
                *result = 0;
            }
        }
        {
            typedef void (FIREVV::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FIREVV::VVfin)) {
                *result = 1;
            }
        }
        {
            typedef void (FIREVV::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FIREVV::minfunc)) {
                *result = 2;
            }
        }
        {
            typedef void (FIREVV::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FIREVV::GenInit)) {
                *result = 3;
            }
        }
        {
            typedef void (FIREVV::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FIREVV::PHIChanged)) {
                *result = 4;
            }
        }
        {
            typedef void (FIREVV::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FIREVV::M_varChanged)) {
                *result = 5;
            }
        }
        {
            typedef void (FIREVV::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FIREVV::EngChanged)) {
                *result = 6;
            }
        }
        {
            typedef void (FIREVV::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FIREVV::pluseig)) {
                *result = 7;
            }
        }
        {
            typedef void (FIREVV::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FIREVV::minuseig)) {
                *result = 8;
            }
        }
        {
            typedef void (FIREVV::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FIREVV::eNumchaged)) {
                *result = 9;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject FIREVV::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_FIREVV.data,
      qt_meta_data_FIREVV,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *FIREVV::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FIREVV::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_FIREVV.stringdata0))
        return static_cast<void*>(const_cast< FIREVV*>(this));
    return QWidget::qt_metacast(_clname);
}

int FIREVV::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void FIREVV::created()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void FIREVV::VVfin()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void FIREVV::minfunc()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void FIREVV::GenInit()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}

// SIGNAL 4
void FIREVV::PHIChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, Q_NULLPTR);
}

// SIGNAL 5
void FIREVV::M_varChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, Q_NULLPTR);
}

// SIGNAL 6
void FIREVV::EngChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, Q_NULLPTR);
}

// SIGNAL 7
void FIREVV::pluseig()
{
    QMetaObject::activate(this, &staticMetaObject, 7, Q_NULLPTR);
}

// SIGNAL 8
void FIREVV::minuseig()
{
    QMetaObject::activate(this, &staticMetaObject, 8, Q_NULLPTR);
}

// SIGNAL 9
void FIREVV::eNumchaged()
{
    QMetaObject::activate(this, &staticMetaObject, 9, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
