/****************************************************************************
** Meta object code from reading C++ file 'LaserDev.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/LaserDev.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'LaserDev.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_LaserDev_t {
    QByteArrayData data[23];
    char stringdata0[171];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LaserDev_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LaserDev_t qt_meta_stringdata_LaserDev = {
    {
QT_MOC_LITERAL(0, 0, 8), // "LaserDev"
QT_MOC_LITERAL(1, 9, 10), // "debug_send"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 1), // "s"
QT_MOC_LITERAL(4, 23, 12), // "pos_received"
QT_MOC_LITERAL(5, 36, 6), // "getPos"
QT_MOC_LITERAL(6, 43, 12), // "processError"
QT_MOC_LITERAL(7, 56, 14), // "processTimeout"
QT_MOC_LITERAL(8, 71, 5), // "sread"
QT_MOC_LITERAL(9, 77, 4), // "init"
QT_MOC_LITERAL(10, 82, 4), // "move"
QT_MOC_LITERAL(11, 87, 1), // "x"
QT_MOC_LITERAL(12, 89, 1), // "y"
QT_MOC_LITERAL(13, 91, 4), // "movx"
QT_MOC_LITERAL(14, 96, 7), // "signDir"
QT_MOC_LITERAL(15, 104, 4), // "movy"
QT_MOC_LITERAL(16, 109, 4), // "stop"
QT_MOC_LITERAL(17, 114, 7), // "laserOn"
QT_MOC_LITERAL(18, 122, 8), // "laserOff"
QT_MOC_LITERAL(19, 131, 12), // "setIntensity"
QT_MOC_LITERAL(20, 144, 8), // "resetAll"
QT_MOC_LITERAL(21, 153, 9), // "CoarseAdj"
QT_MOC_LITERAL(22, 163, 7) // "FineAdj"

    },
    "LaserDev\0debug_send\0\0s\0pos_received\0"
    "getPos\0processError\0processTimeout\0"
    "sread\0init\0move\0x\0y\0movx\0signDir\0movy\0"
    "stop\0laserOn\0laserOff\0setIntensity\0"
    "resetAll\0CoarseAdj\0FineAdj"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LaserDev[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   99,    2, 0x06 /* Public */,
       4,    2,  102,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,  107,    2, 0x0a /* Public */,
       6,    1,  108,    2, 0x0a /* Public */,
       7,    1,  111,    2, 0x0a /* Public */,
       8,    1,  114,    2, 0x0a /* Public */,
       9,    0,  117,    2, 0x0a /* Public */,
      10,    2,  118,    2, 0x0a /* Public */,
      13,    1,  123,    2, 0x0a /* Public */,
      15,    1,  126,    2, 0x0a /* Public */,
      16,    0,  129,    2, 0x0a /* Public */,
      17,    0,  130,    2, 0x0a /* Public */,
      18,    0,  131,    2, 0x0a /* Public */,
      19,    1,  132,    2, 0x0a /* Public */,
      20,    0,  135,    2, 0x0a /* Public */,
      21,    0,  136,    2, 0x0a /* Public */,
      22,    0,  137,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    2,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double, QMetaType::Double,   11,   12,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void LaserDev::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        LaserDev *_t = static_cast<LaserDev *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->debug_send((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->pos_received((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 2: _t->getPos(); break;
        case 3: _t->processError((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->processTimeout((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->sread((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->init(); break;
        case 7: _t->move((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 8: _t->movx((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->movy((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->stop(); break;
        case 11: _t->laserOn(); break;
        case 12: _t->laserOff(); break;
        case 13: _t->setIntensity((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->resetAll(); break;
        case 15: _t->CoarseAdj(); break;
        case 16: _t->FineAdj(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (LaserDev::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&LaserDev::debug_send)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (LaserDev::*_t)(QString , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&LaserDev::pos_received)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject LaserDev::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_LaserDev.data,
      qt_meta_data_LaserDev,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *LaserDev::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LaserDev::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_LaserDev.stringdata0))
        return static_cast<void*>(const_cast< LaserDev*>(this));
    return QObject::qt_metacast(_clname);
}

int LaserDev::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void LaserDev::debug_send(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void LaserDev::pos_received(QString _t1, QString _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
