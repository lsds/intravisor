/* C pointer object interface */

#ifndef Py_CPOINTEROBJECT_H
#define Py_CPOINTEROBJECT_H

#include "longobject.h"

#ifdef __cplusplus
extern "C" {
#endif


PyAPI_DATA(PyTypeObject) _PyNativePointer_Type;
#define PyNativePointer_CheckExact(x) (Py_TYPE(x) == &_PyNativePointer_Type)
#define PyNativePointer_Check(x) (PyNativePointer_CheckExact(x) || PyNativePointer_IsNull(x))
static inline _Bool PyNativePointer_IsNull(PyObject* x) {
    /* Also allow NULL pointers */
    if (x == Py_None || x == Py_False)
        return 1;
    if (PyLong_Check(x))
        return _PyLong_Sign(x) == 0;
    /* TODO: do we need this fallback? */
#if 0
    /* Otherwise convert to long and check if the value is zero */
    PyObject * aslong = _PyLong_FromNbIndexOrNbInt(x);
    /* Ignore conversion errors */
    if (PyErr_Occurred())
        PyErr_Clear();
    if (aslong && _PyLong_Sign(aslong) == 0)
        return 1;
#endif
     return 0;
}
/* Function to return a bool from a C long */
PyAPI_FUNC(PyObject *) PyNativePointer_FromVoidPointer(void *);
PyAPI_FUNC(void *) PyNativePointer_AsVoidPointer(PyObject *);
PyAPI_FUNC(uintptr_t) PyNativePointer_AsUIntPtr(PyObject *);

#ifdef __cplusplus
}
#endif
#endif /* !Py_CPOINTEROBJECT_H */
