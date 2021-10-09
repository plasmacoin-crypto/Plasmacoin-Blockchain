/****************************************************************************
** Meta object code from reading C++ file 'firebase-auth.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../plasmacoin-client/firebase-auth.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'firebase-auth.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Auth_t {
    QByteArrayData data[13];
    char stringdata0[168];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Auth_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Auth_t qt_meta_stringdata_Auth = {
    {
QT_MOC_LITERAL(0, 0, 4), // "Auth"
QT_MOC_LITERAL(1, 5, 15), // "FinishedRequest"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 12), // "UserSignedIn"
QT_MOC_LITERAL(4, 35, 14), // "RequestedToken"
QT_MOC_LITERAL(5, 50, 11), // "EmailExists"
QT_MOC_LITERAL(6, 62, 13), // "UsernameTaken"
QT_MOC_LITERAL(7, 76, 12), // "InvalidEmail"
QT_MOC_LITERAL(8, 89, 15), // "InvalidUsername"
QT_MOC_LITERAL(9, 105, 15), // "InvalidPassword"
QT_MOC_LITERAL(10, 121, 15), // "FoundAuthErrors"
QT_MOC_LITERAL(11, 137, 17), // "NetworkReplyReady"
QT_MOC_LITERAL(12, 155, 12) // "RequestToken"

    },
    "Auth\0FinishedRequest\0\0UserSignedIn\0"
    "RequestedToken\0EmailExists\0UsernameTaken\0"
    "InvalidEmail\0InvalidUsername\0"
    "InvalidPassword\0FoundAuthErrors\0"
    "NetworkReplyReady\0RequestToken"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Auth[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x06 /* Public */,
       3,    0,   70,    2, 0x06 /* Public */,
       4,    0,   71,    2, 0x06 /* Public */,
       5,    0,   72,    2, 0x06 /* Public */,
       6,    0,   73,    2, 0x06 /* Public */,
       7,    0,   74,    2, 0x06 /* Public */,
       8,    0,   75,    2, 0x06 /* Public */,
       9,    0,   76,    2, 0x06 /* Public */,
      10,    0,   77,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    0,   78,    2, 0x0a /* Public */,
      12,    0,   79,    2, 0x0a /* Public */,

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

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Auth::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Auth *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->FinishedRequest(); break;
        case 1: _t->UserSignedIn(); break;
        case 2: _t->RequestedToken(); break;
        case 3: _t->EmailExists(); break;
        case 4: _t->UsernameTaken(); break;
        case 5: _t->InvalidEmail(); break;
        case 6: _t->InvalidUsername(); break;
        case 7: _t->InvalidPassword(); break;
        case 8: _t->FoundAuthErrors(); break;
        case 9: _t->NetworkReplyReady(); break;
        case 10: _t->RequestToken(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Auth::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Auth::FinishedRequest)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Auth::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Auth::UserSignedIn)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Auth::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Auth::RequestedToken)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Auth::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Auth::EmailExists)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (Auth::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Auth::UsernameTaken)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (Auth::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Auth::InvalidEmail)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (Auth::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Auth::InvalidUsername)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (Auth::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Auth::InvalidPassword)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (Auth::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Auth::FoundAuthErrors)) {
                *result = 8;
                return;
            }
        }
    }
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject Auth::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_Auth.data,
    qt_meta_data_Auth,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Auth::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Auth::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Auth.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "Ui_MainWindow"))
        return static_cast< Ui_MainWindow*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int Auth::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void Auth::FinishedRequest()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Auth::UserSignedIn()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Auth::RequestedToken()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void Auth::EmailExists()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void Auth::UsernameTaken()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void Auth::InvalidEmail()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void Auth::InvalidUsername()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void Auth::InvalidPassword()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void Auth::FoundAuthErrors()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
