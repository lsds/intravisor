/* C pointer type, a subtype of int */

#include "Python.h"
#include "longintrepr.h"
#include "pointerobject.h"

/* The type object for C pointers.  Note that this cannot be subclassed! */
typedef struct {
        PyObject_HEAD
        /* TODO: store the type of the pointer + whether it's valid? */
        void* pointer;
} PyNativePointerObject;

/* Methods */
static PyObject *
pointer_richcompare(PyObject *self, PyObject *other, int op)
{
    int result;
    uintptr_t a;
    uintptr_t b;

    if (self == other)
        Py_RETURN_RICHCOMPARE(0, 0, op);

    /* TODO: ?
     * Not an integer;  try to use __index__ to convert:
     * if (PyIndex_Check(v)) {
     *   v = PyNumber_Index(v);
     */

    /* Allow comparisons against longs with the same value: */
    if (PyNativePointer_Check(self))
        a = (uintptr_t)PyNativePointer_AsVoidPointer(self);
    else if (PyLong_Check(self))
        a = (uintptr_t)PyLong_AsPyAddr(self);
    else
        Py_RETURN_NOTIMPLEMENTED;

    if (PyNativePointer_Check(other))
        b = (uintptr_t)PyNativePointer_AsVoidPointer(other);
    else if (PyLong_Check(other))
        b = (uintptr_t)PyLong_AsPyAddr(other);
    else
        Py_RETURN_NOTIMPLEMENTED;

    if ((uintptr_t)a == (uintptr_t)b)
        result = 0;
    else
        result = a < b ? -1 : 1;
    Py_RETURN_RICHCOMPARE(result, 0, op);
}

static Py_hash_t
pointer_hash(PyObject *v)
{
    assert(PyNativePointer_CheckExact(v));
    return _Py_HashPointer(((PyNativePointerObject *)v)->pointer);
}

static int
pointer_bool(PyObject *v)
{
    assert(PyNativePointer_CheckExact(v));
    return ((PyNativePointerObject *)v)->pointer != NULL;
}

static PyObject *
pointer_int(PyObject *v)
{
    assert(PyNativePointer_CheckExact(v));
    PyNativePointerObject *cp = (PyNativePointerObject *)v;
    return PyLong_FromPyAddr((Py_addr_t)cp->pointer);
}

static PyObject *
pointer_repr(PyObject *v)
{
    assert(PyNativePointer_CheckExact(v));
    PyNativePointerObject *cp = (PyNativePointerObject *)v;
    /* TODO: print CHERI permissions? */
    return PyUnicode_FromFormat("<native pointer:%p>", cp->pointer);
}


static PyNumberMethods pointer_as_number = {
    .nb_bool = pointer_bool,
    .nb_int = pointer_int,
    .nb_index = pointer_int,
};

static PyObject *
pointer_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    PyNativePointerObject *self = (PyNativePointerObject *) type->tp_alloc(type, 0);
    if (self != NULL) {
        self->pointer = NULL;
    }
    return (PyObject *) self;
}

static void
pointer_dealloc(PyObject *obj)
{
    // PyNativePointerObject *self = (PyNativePointerObject *)obj;
    // fprintf(stderr, "releasing c pointer %p\n", self->pointer);
    Py_TYPE(obj)->tp_free(obj);
}

static PyObject *
pointer_reduce(PyObject* self, PyObject *Py_UNUSED(ignored)) {
    PyErr_Format(PyExc_TypeError, "Attempting to pickle a native pointer (%p). "
                 "This is a terrible idea and will not work on all systems!");
    return NULL;
}

static PyMethodDef pointer_methods[] = {
    {"__reduce__", (PyCFunction)pointer_reduce, METH_NOARGS,
        "Should not be called."},
    {NULL, NULL}  // sentinel
};

PyTypeObject _PyNativePointer_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "_native_pointer",
    .tp_doc = "native pointer",
    .tp_basicsize = sizeof(PyNativePointerObject),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT, /* TODO: Py_TPFLAGS_LONG_SUBCLASS */
    .tp_richcompare = pointer_richcompare,
    .tp_repr = pointer_repr,
    .tp_new = pointer_new,
    .tp_dealloc = pointer_dealloc,
    .tp_hash = pointer_hash,
    .tp_as_number = &pointer_as_number,
    .tp_alloc = PyType_GenericAlloc,
    .tp_free = PyObject_Del,
    .tp_methods = pointer_methods,
};

static PyNativePointerObject _Py_NativeNullStruct = {
    PyObject_HEAD_INIT(&_PyNativePointer_Type)
    .pointer = NULL,
};
#define Py_NativeNULL ((PyObject*)(&_Py_NativeNullStruct))

PyObject *
PyNativePointer_FromVoidPointer(void* value) {
    PyNativePointerObject *p;
    /* Return the same instance for all NULL pointers: */
    if (value == NULL) {
        Py_INCREF(Py_NativeNULL);
        return Py_NativeNULL;
    }
#ifdef __CHERI_PURE_CAPABILITY__
    if (!__builtin_cheri_tag_get(value)) {
        PyErr_Format(PyExc_TypeError, "%s: a valid pointer or a NULL pointer is required, got %p", __func__, value);
        return NULL;
    }
#endif
    p = PyObject_New(PyNativePointerObject, &_PyNativePointer_Type);
    if (p == NULL)
        return NULL;
    p->pointer = value;
    return (PyObject *)p;
}

void *
PyNativePointer_AsVoidPointer(PyObject *vv)
{
    if (PyNativePointer_CheckExact(vv)) {
        assert(!PyErr_Occurred());
        return ((PyNativePointerObject*)vv)->pointer;
    } else if (PyNativePointer_IsNull(vv)) {
        assert(!PyErr_Occurred());
        return NULL;
    }
    /* Handle the ctypes.c_void_p type: */
    if (PyObject_HasAttrString(vv, "value")) {
      PyObject* pv = PyObject_GetAttrString(vv, "value");
      if (pv == NULL)
        return NULL;
      /* We could also check that _type_ is "P" */
      if (PyNativePointer_CheckExact(pv)) {
        void* result = ((PyNativePointerObject*)pv)->pointer;
        Py_DECREF(pv);
        return result;
      }
      Py_DECREF(pv);
    }
#ifdef WONT_WORK_ON_CHERI
    Py_addr_t addr = PyLong_AsPyAddr(vv);
    if (addr == (Py_addr_t)-1 && PyErr_Occurred())
        return NULL;

    /* Probably not correct since it's not a valid pointer... */
    return (void*)(uintptr_t)addr;
#else
    PyErr_Format(PyExc_TypeError, "%s: a valid pointer or a NULL pointer is required, got %R", __func__, vv);
    return NULL;
#endif
}

uintptr_t
PyNativePointer_AsUIntPtr(PyObject *vv)
{
    if (PyNativePointer_CheckExact(vv)) {
        assert(!PyErr_Occurred());
        return (uintptr_t)((PyNativePointerObject*)vv)->pointer;
    } else if (PyNativePointer_IsNull(vv)) {
        assert(!PyErr_Occurred());
        return (uintptr_t)NULL;
    }
    Py_addr_t addr = PyLong_AsPyAddr(vv);
    if (addr == (Py_addr_t)-1 && PyErr_Occurred())
        return (uintptr_t)NULL; /* XXX: or -1? */

    return (uintptr_t)addr;

}
