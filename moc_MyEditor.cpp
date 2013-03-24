/****************************************************************************
** Meta object code from reading C++ file 'MyEditor.h'
**
** Created: Wed Feb 13 06:16:25 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "MyEditor.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MyEditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MyEditor[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x08,
      22,    9,   17,    9, 0x08,
      29,    9,    9,    9, 0x08,
      37,    9,    9,    9, 0x08,
      50,    9,    9,    9, 0x08,
      60,    9,   17,    9, 0x08,
      69,    9,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MyEditor[] = {
    "MyEditor\0\0open()\0bool\0save()\0about()\0"
    "isModified()\0newFile()\0saveAs()\0"
    "openRecentFile()\0"
};

void MyEditor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MyEditor *_t = static_cast<MyEditor *>(_o);
        switch (_id) {
        case 0: _t->open(); break;
        case 1: { bool _r = _t->save();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 2: _t->about(); break;
        case 3: _t->isModified(); break;
        case 4: _t->newFile(); break;
        case 5: { bool _r = _t->saveAs();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 6: _t->openRecentFile(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MyEditor::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MyEditor::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MyEditor,
      qt_meta_data_MyEditor, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MyEditor::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MyEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MyEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MyEditor))
        return static_cast<void*>(const_cast< MyEditor*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MyEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
