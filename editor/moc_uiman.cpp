/****************************************************************************
** Meta object code from reading C++ file 'uiman.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "src/uiman.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'uiman.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_UIMan[] = {

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
       9,    7,    6,    6, 0x0a,
      55,    7,    6,    6, 0x0a,
     103,    6,    6,    6, 0x0a,
     128,    6,    6,    6, 0x0a,
     141,    6,    6,    6, 0x0a,
     153,    6,    6,    6, 0x0a,
     168,    6,    6,    6, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_UIMan[] = {
    "UIMan\0\0,\0changeItem(QListWidgetItem*,QListWidgetItem*)\0"
    "changeScript(QListWidgetItem*,QListWidgetItem*)\0"
    "toggleObjectVisibility()\0aboutPanel()\0"
    "addObject()\0deleteObject()\0saveCurScript()\0"
};

void UIMan::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        UIMan *_t = static_cast<UIMan *>(_o);
        switch (_id) {
        case 0: _t->changeItem((*reinterpret_cast< QListWidgetItem*(*)>(_a[1])),(*reinterpret_cast< QListWidgetItem*(*)>(_a[2]))); break;
        case 1: _t->changeScript((*reinterpret_cast< QListWidgetItem*(*)>(_a[1])),(*reinterpret_cast< QListWidgetItem*(*)>(_a[2]))); break;
        case 2: _t->toggleObjectVisibility(); break;
        case 3: _t->aboutPanel(); break;
        case 4: _t->addObject(); break;
        case 5: _t->deleteObject(); break;
        case 6: _t->saveCurScript(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData UIMan::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject UIMan::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_UIMan,
      qt_meta_data_UIMan, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &UIMan::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *UIMan::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *UIMan::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_UIMan))
        return static_cast<void*>(const_cast< UIMan*>(this));
    return QObject::qt_metacast(_clname);
}

int UIMan::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
