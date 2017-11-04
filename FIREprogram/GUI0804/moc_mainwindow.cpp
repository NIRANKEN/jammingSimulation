/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[41];
    char stringdata0[824];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 8), // "startSim"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 7), // "stopSim"
QT_MOC_LITERAL(4, 29, 13), // "calculatedSim"
QT_MOC_LITERAL(5, 43, 7), // "quitApp"
QT_MOC_LITERAL(6, 51, 12), // "calculatedVV"
QT_MOC_LITERAL(7, 64, 11), // "calculateVV"
QT_MOC_LITERAL(8, 76, 24), // "on_seed_in_returnPressed"
QT_MOC_LITERAL(9, 101, 23), // "on_phi_in_returnPressed"
QT_MOC_LITERAL(10, 125, 26), // "on_crrate_in_returnPressed"
QT_MOC_LITERAL(11, 152, 21), // "on_N_in_returnPressed"
QT_MOC_LITERAL(12, 174, 23), // "on_pex_in_returnPressed"
QT_MOC_LITERAL(13, 198, 24), // "on_mix2_in_returnPressed"
QT_MOC_LITERAL(14, 223, 22), // "on_lx_in_returnPressed"
QT_MOC_LITERAL(15, 246, 22), // "on_ly_in_returnPressed"
QT_MOC_LITERAL(16, 269, 22), // "on_sr_in_returnPressed"
QT_MOC_LITERAL(17, 292, 24), // "on_mix1_in_returnPressed"
QT_MOC_LITERAL(18, 317, 25), // "on_tstep_in_returnPressed"
QT_MOC_LITERAL(19, 343, 24), // "on_damp_in_returnPressed"
QT_MOC_LITERAL(20, 368, 23), // "on_IFT_in_returnPressed"
QT_MOC_LITERAL(21, 392, 23), // "on_DFT_in_returnPressed"
QT_MOC_LITERAL(22, 416, 24), // "on_DFDT_in_returnPressed"
QT_MOC_LITERAL(23, 441, 26), // "on_DTinit_in_returnPressed"
QT_MOC_LITERAL(24, 468, 24), // "on_maxT_in_returnPressed"
QT_MOC_LITERAL(25, 493, 29), // "on_delayFIRE_in_returnPressed"
QT_MOC_LITERAL(26, 523, 19), // "on_sysdefBt_clicked"
QT_MOC_LITERAL(27, 543, 18), // "on_MDdefBt_clicked"
QT_MOC_LITERAL(28, 562, 18), // "on_startBt_clicked"
QT_MOC_LITERAL(29, 581, 18), // "on_noiseBt_clicked"
QT_MOC_LITERAL(30, 600, 16), // "on_repBt_clicked"
QT_MOC_LITERAL(31, 617, 20), // "on_resetPtBt_clicked"
QT_MOC_LITERAL(32, 638, 17), // "on_burnBt_clicked"
QT_MOC_LITERAL(33, 656, 17), // "on_readBt_clicked"
QT_MOC_LITERAL(34, 674, 21), // "on_calcmodeBt_clicked"
QT_MOC_LITERAL(35, 696, 21), // "on_writeeigBt_clicked"
QT_MOC_LITERAL(36, 718, 16), // "on_ccgBt_clicked"
QT_MOC_LITERAL(37, 735, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(38, 757, 18), // "on_exit_bt_clicked"
QT_MOC_LITERAL(39, 776, 20), // "on_startBt_2_clicked"
QT_MOC_LITERAL(40, 797, 26) // "on_eignum_le_returnPressed"

    },
    "MainWindow\0startSim\0\0stopSim\0calculatedSim\0"
    "quitApp\0calculatedVV\0calculateVV\0"
    "on_seed_in_returnPressed\0"
    "on_phi_in_returnPressed\0"
    "on_crrate_in_returnPressed\0"
    "on_N_in_returnPressed\0on_pex_in_returnPressed\0"
    "on_mix2_in_returnPressed\0"
    "on_lx_in_returnPressed\0on_ly_in_returnPressed\0"
    "on_sr_in_returnPressed\0on_mix1_in_returnPressed\0"
    "on_tstep_in_returnPressed\0"
    "on_damp_in_returnPressed\0"
    "on_IFT_in_returnPressed\0on_DFT_in_returnPressed\0"
    "on_DFDT_in_returnPressed\0"
    "on_DTinit_in_returnPressed\0"
    "on_maxT_in_returnPressed\0"
    "on_delayFIRE_in_returnPressed\0"
    "on_sysdefBt_clicked\0on_MDdefBt_clicked\0"
    "on_startBt_clicked\0on_noiseBt_clicked\0"
    "on_repBt_clicked\0on_resetPtBt_clicked\0"
    "on_burnBt_clicked\0on_readBt_clicked\0"
    "on_calcmodeBt_clicked\0on_writeeigBt_clicked\0"
    "on_ccgBt_clicked\0on_pushButton_clicked\0"
    "on_exit_bt_clicked\0on_startBt_2_clicked\0"
    "on_eignum_le_returnPressed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      39,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  209,    2, 0x06 /* Public */,
       3,    0,  210,    2, 0x06 /* Public */,
       4,    0,  211,    2, 0x06 /* Public */,
       5,    0,  212,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,  213,    2, 0x0a /* Public */,
       7,    0,  214,    2, 0x0a /* Public */,
       8,    0,  215,    2, 0x08 /* Private */,
       9,    0,  216,    2, 0x08 /* Private */,
      10,    0,  217,    2, 0x08 /* Private */,
      11,    0,  218,    2, 0x08 /* Private */,
      12,    0,  219,    2, 0x08 /* Private */,
      13,    0,  220,    2, 0x08 /* Private */,
      14,    0,  221,    2, 0x08 /* Private */,
      15,    0,  222,    2, 0x08 /* Private */,
      16,    0,  223,    2, 0x08 /* Private */,
      17,    0,  224,    2, 0x08 /* Private */,
      18,    0,  225,    2, 0x08 /* Private */,
      19,    0,  226,    2, 0x08 /* Private */,
      20,    0,  227,    2, 0x08 /* Private */,
      21,    0,  228,    2, 0x08 /* Private */,
      22,    0,  229,    2, 0x08 /* Private */,
      23,    0,  230,    2, 0x08 /* Private */,
      24,    0,  231,    2, 0x08 /* Private */,
      25,    0,  232,    2, 0x08 /* Private */,
      26,    0,  233,    2, 0x08 /* Private */,
      27,    0,  234,    2, 0x08 /* Private */,
      28,    0,  235,    2, 0x08 /* Private */,
      29,    0,  236,    2, 0x08 /* Private */,
      30,    0,  237,    2, 0x08 /* Private */,
      31,    0,  238,    2, 0x08 /* Private */,
      32,    0,  239,    2, 0x08 /* Private */,
      33,    0,  240,    2, 0x08 /* Private */,
      34,    0,  241,    2, 0x08 /* Private */,
      35,    0,  242,    2, 0x08 /* Private */,
      36,    0,  243,    2, 0x08 /* Private */,
      37,    0,  244,    2, 0x08 /* Private */,
      38,    0,  245,    2, 0x08 /* Private */,
      39,    0,  246,    2, 0x08 /* Private */,
      40,    0,  247,    2, 0x08 /* Private */,

 // signals: parameters
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
        case 0: _t->startSim(); break;
        case 1: _t->stopSim(); break;
        case 2: _t->calculatedSim(); break;
        case 3: _t->quitApp(); break;
        case 4: _t->calculatedVV(); break;
        case 5: _t->calculateVV(); break;
        case 6: _t->on_seed_in_returnPressed(); break;
        case 7: _t->on_phi_in_returnPressed(); break;
        case 8: _t->on_crrate_in_returnPressed(); break;
        case 9: _t->on_N_in_returnPressed(); break;
        case 10: _t->on_pex_in_returnPressed(); break;
        case 11: _t->on_mix2_in_returnPressed(); break;
        case 12: _t->on_lx_in_returnPressed(); break;
        case 13: _t->on_ly_in_returnPressed(); break;
        case 14: _t->on_sr_in_returnPressed(); break;
        case 15: _t->on_mix1_in_returnPressed(); break;
        case 16: _t->on_tstep_in_returnPressed(); break;
        case 17: _t->on_damp_in_returnPressed(); break;
        case 18: _t->on_IFT_in_returnPressed(); break;
        case 19: _t->on_DFT_in_returnPressed(); break;
        case 20: _t->on_DFDT_in_returnPressed(); break;
        case 21: _t->on_DTinit_in_returnPressed(); break;
        case 22: _t->on_maxT_in_returnPressed(); break;
        case 23: _t->on_delayFIRE_in_returnPressed(); break;
        case 24: _t->on_sysdefBt_clicked(); break;
        case 25: _t->on_MDdefBt_clicked(); break;
        case 26: _t->on_startBt_clicked(); break;
        case 27: _t->on_noiseBt_clicked(); break;
        case 28: _t->on_repBt_clicked(); break;
        case 29: _t->on_resetPtBt_clicked(); break;
        case 30: _t->on_burnBt_clicked(); break;
        case 31: _t->on_readBt_clicked(); break;
        case 32: _t->on_calcmodeBt_clicked(); break;
        case 33: _t->on_writeeigBt_clicked(); break;
        case 34: _t->on_ccgBt_clicked(); break;
        case 35: _t->on_pushButton_clicked(); break;
        case 36: _t->on_exit_bt_clicked(); break;
        case 37: _t->on_startBt_2_clicked(); break;
        case 38: _t->on_eignum_le_returnPressed(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::startSim)) {
                *result = 0;
            }
        }
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::stopSim)) {
                *result = 1;
            }
        }
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::calculatedSim)) {
                *result = 2;
            }
        }
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::quitApp)) {
                *result = 3;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 39)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 39;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 39)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 39;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::startSim()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void MainWindow::stopSim()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void MainWindow::calculatedSim()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void MainWindow::quitApp()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
