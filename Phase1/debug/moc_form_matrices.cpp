/****************************************************************************
** Meta object code from reading C++ file 'form_matrices.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../form_matrices.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'form_matrices.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN13Form_matricesE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN13Form_matricesE = QtMocHelpers::stringData(
    "Form_matrices",
    "showMainWindow",
    "",
    "on_Back_clicked",
    "on_Add_clicked",
    "validateInput",
    "input",
    "parseFraction",
    "on_Apply_clicked",
    "onRowHeaderClicked",
    "index",
    "updateOperationsTable",
    "operationName",
    "Saved_Matricies_Table",
    "Rows",
    "Columns",
    "on_Is_Unit_clicked",
    "on_Is_Skew_clicked",
    "on_Is_Symmetric_clicked",
    "on_Transpose_clicked",
    "on_Swap_Rows_clicked",
    "on_Swap_Columns_clicked",
    "on_Get_Row_clicked",
    "on_Get_Column_clicked",
    "on_Norm_clicked",
    "on_Power_clicked",
    "on_Determinant_clicked",
    "on_inverse_clicked",
    "on_tableWidget_destroyed",
    "on_tableWidget_2_destroyed",
    "on_Doolittle_clicked",
    "on_Croute_clicked",
    "on_Cholesky_clicked"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN13Form_matricesE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      26,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  170,    2, 0x06,    1 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       3,    0,  171,    2, 0x08,    2 /* Private */,
       4,    0,  172,    2, 0x08,    3 /* Private */,
       5,    1,  173,    2, 0x08,    4 /* Private */,
       7,    1,  176,    2, 0x08,    6 /* Private */,
       8,    0,  179,    2, 0x08,    8 /* Private */,
       9,    1,  180,    2, 0x08,    9 /* Private */,
      11,    1,  183,    2, 0x08,   11 /* Private */,
      13,    2,  186,    2, 0x08,   13 /* Private */,
      16,    0,  191,    2, 0x08,   16 /* Private */,
      17,    0,  192,    2, 0x08,   17 /* Private */,
      18,    0,  193,    2, 0x08,   18 /* Private */,
      19,    0,  194,    2, 0x08,   19 /* Private */,
      20,    0,  195,    2, 0x08,   20 /* Private */,
      21,    0,  196,    2, 0x08,   21 /* Private */,
      22,    0,  197,    2, 0x08,   22 /* Private */,
      23,    0,  198,    2, 0x08,   23 /* Private */,
      24,    0,  199,    2, 0x08,   24 /* Private */,
      25,    0,  200,    2, 0x08,   25 /* Private */,
      26,    0,  201,    2, 0x08,   26 /* Private */,
      27,    0,  202,    2, 0x08,   27 /* Private */,
      28,    0,  203,    2, 0x08,   28 /* Private */,
      29,    0,  204,    2, 0x08,   29 /* Private */,
      30,    0,  205,    2, 0x08,   30 /* Private */,
      31,    0,  206,    2, 0x08,   31 /* Private */,
      32,    0,  207,    2, 0x08,   32 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool, QMetaType::QString,    6,
    QMetaType::Double, QMetaType::QString,    6,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   14,   15,
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

Q_CONSTINIT const QMetaObject Form_matrices::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_ZN13Form_matricesE.offsetsAndSizes,
    qt_meta_data_ZN13Form_matricesE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN13Form_matricesE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<Form_matrices, std::true_type>,
        // method 'showMainWindow'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_Back_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_Add_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'validateInput'
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'parseFraction'
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'on_Apply_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onRowHeaderClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'updateOperationsTable'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'Saved_Matricies_Table'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_Is_Unit_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_Is_Skew_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_Is_Symmetric_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_Transpose_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_Swap_Rows_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_Swap_Columns_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_Get_Row_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_Get_Column_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_Norm_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_Power_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_Determinant_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_inverse_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_tableWidget_destroyed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_tableWidget_2_destroyed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_Doolittle_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_Croute_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_Cholesky_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void Form_matrices::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<Form_matrices *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->showMainWindow(); break;
        case 1: _t->on_Back_clicked(); break;
        case 2: _t->on_Add_clicked(); break;
        case 3: { bool _r = _t->validateInput((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 4: { double _r = _t->parseFraction((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = std::move(_r); }  break;
        case 5: _t->on_Apply_clicked(); break;
        case 6: _t->onRowHeaderClicked((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 7: _t->updateOperationsTable((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 8: _t->Saved_Matricies_Table((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 9: _t->on_Is_Unit_clicked(); break;
        case 10: _t->on_Is_Skew_clicked(); break;
        case 11: _t->on_Is_Symmetric_clicked(); break;
        case 12: _t->on_Transpose_clicked(); break;
        case 13: _t->on_Swap_Rows_clicked(); break;
        case 14: _t->on_Swap_Columns_clicked(); break;
        case 15: _t->on_Get_Row_clicked(); break;
        case 16: _t->on_Get_Column_clicked(); break;
        case 17: _t->on_Norm_clicked(); break;
        case 18: _t->on_Power_clicked(); break;
        case 19: _t->on_Determinant_clicked(); break;
        case 20: _t->on_inverse_clicked(); break;
        case 21: _t->on_tableWidget_destroyed(); break;
        case 22: _t->on_tableWidget_2_destroyed(); break;
        case 23: _t->on_Doolittle_clicked(); break;
        case 24: _t->on_Croute_clicked(); break;
        case 25: _t->on_Cholesky_clicked(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (Form_matrices::*)();
            if (_q_method_type _q_method = &Form_matrices::showMainWindow; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject *Form_matrices::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Form_matrices::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN13Form_matricesE.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Form_matrices::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 26)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 26;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 26)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 26;
    }
    return _id;
}

// SIGNAL 0
void Form_matrices::showMainWindow()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
