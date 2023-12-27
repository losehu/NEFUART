/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[27];
    char stringdata0[327];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 13), // "DataReceived1"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 16), // "on_open1_clicked"
QT_MOC_LITERAL(4, 43, 9), // "onTimeout"
QT_MOC_LITERAL(5, 53, 15), // "on_read_clicked"
QT_MOC_LITERAL(6, 69, 16), // "on_write_clicked"
QT_MOC_LITERAL(7, 86, 15), // "CHECK_MDC_TABLE"
QT_MOC_LITERAL(8, 102, 11), // "txt_to_byte"
QT_MOC_LITERAL(9, 114, 11), // "std::string"
QT_MOC_LITERAL(10, 126, 10), // "targetChar"
QT_MOC_LITERAL(11, 137, 14), // "unsigned char*"
QT_MOC_LITERAL(12, 152, 3), // "out"
QT_MOC_LITERAL(13, 156, 7), // "max_len"
QT_MOC_LITERAL(14, 164, 4), // "flag"
QT_MOC_LITERAL(15, 169, 3), // "row"
QT_MOC_LITERAL(16, 173, 23), // "on_read_param_triggered"
QT_MOC_LITERAL(17, 197, 23), // "on_save_param_triggered"
QT_MOC_LITERAL(18, 221, 21), // "isGBKChineseCharacter"
QT_MOC_LITERAL(19, 243, 12), // "std::string&"
QT_MOC_LITERAL(20, 256, 3), // "str"
QT_MOC_LITERAL(21, 260, 6), // "size_t"
QT_MOC_LITERAL(22, 267, 5), // "index"
QT_MOC_LITERAL(23, 273, 19), // "containsChineseChar"
QT_MOC_LITERAL(24, 293, 4), // "line"
QT_MOC_LITERAL(25, 298, 6), // "target"
QT_MOC_LITERAL(26, 305, 21) // "on_pushButton_clicked"

    },
    "MainWindow\0DataReceived1\0\0on_open1_clicked\0"
    "onTimeout\0on_read_clicked\0on_write_clicked\0"
    "CHECK_MDC_TABLE\0txt_to_byte\0std::string\0"
    "targetChar\0unsigned char*\0out\0max_len\0"
    "flag\0row\0on_read_param_triggered\0"
    "on_save_param_triggered\0isGBKChineseCharacter\0"
    "std::string&\0str\0size_t\0index\0"
    "containsChineseChar\0line\0target\0"
    "on_pushButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x0a /* Public */,
       3,    0,   75,    2, 0x08 /* Private */,
       4,    0,   76,    2, 0x08 /* Private */,
       5,    0,   77,    2, 0x08 /* Private */,
       6,    0,   78,    2, 0x08 /* Private */,
       7,    0,   79,    2, 0x08 /* Private */,
       8,    5,   80,    2, 0x08 /* Private */,
      16,    0,   91,    2, 0x08 /* Private */,
      17,    0,   92,    2, 0x08 /* Private */,
      18,    2,   93,    2, 0x08 /* Private */,
      23,    2,   98,    2, 0x08 /* Private */,
      26,    0,  103,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::UChar, 0x80000000 | 9, 0x80000000 | 11, QMetaType::Int, QMetaType::Bool, QMetaType::Int,   10,   12,   13,   14,   15,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool, 0x80000000 | 19, 0x80000000 | 21,   20,   22,
    QMetaType::Bool, 0x80000000 | 9, 0x80000000 | 9,   24,   25,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->DataReceived1(); break;
        case 1: _t->on_open1_clicked(); break;
        case 2: _t->onTimeout(); break;
        case 3: _t->on_read_clicked(); break;
        case 4: _t->on_write_clicked(); break;
        case 5: _t->CHECK_MDC_TABLE(); break;
        case 6: { unsigned char _r = _t->txt_to_byte((*reinterpret_cast< std::string(*)>(_a[1])),(*reinterpret_cast< unsigned char*(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])));
            if (_a[0]) *reinterpret_cast< unsigned char*>(_a[0]) = std::move(_r); }  break;
        case 7: _t->on_read_param_triggered(); break;
        case 8: _t->on_save_param_triggered(); break;
        case 9: { bool _r = _t->isGBKChineseCharacter((*reinterpret_cast< std::string(*)>(_a[1])),(*reinterpret_cast< size_t(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 10: { bool _r = _t->containsChineseChar((*reinterpret_cast< const std::string(*)>(_a[1])),(*reinterpret_cast< const std::string(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 11: _t->on_pushButton_clicked(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


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
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
