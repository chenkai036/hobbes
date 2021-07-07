#include <Python.h>
#include <hobbes/storage.H>
#include <stdexcept>

#if PY_MAJOR_VERSION == 3
  #error "Python3 not supported yet"
#endif

#define DEFINE_PY_TYPE(MODULE, NAME, DESC)                \
 static PyTypeObject Py##NAME##Ty = {                     \
   PyVarObject_HEAD_INIT(NULL, 0)                         \
   #MODULE"."#NAME,              /* tp_name */            \
   sizeof(Py##NAME),             /* tp_basicsize  */      \
   0,                            /* tp_itemsize */        \
   0,                            /* tp_dealloc */         \
   0,                            /* tp_print */           \
   0,                            /* tp_getattr */         \
   0,                            /* tp_setattr */         \
   0,                            /* tp_compare */         \
   0,                            /* tp_repr */            \
   0,                            /* tp_as_number */       \
   0,                            /* tp_as_sequence */     \
   0,                            /* tp_as_mapping */      \
   0,                            /* tp_hash */            \
   0,                            /* tp_call */            \
   0,                            /* tp_str */             \
   0,                            /* tp_getattro */        \
   0,                            /* tp_setattro */        \
   0,                            /* tp_as_buffer */       \
   Py_TPFLAGS_DEFAULT,           /* tp_flags */           \
   DESC,                         /* tp_doc */             \
   0,                            /* tp_traverse */        \
   0,                            /* tp_clear */           \
   0,                            /* tp_richcompare */     \
   0,                            /* tp_weaklistoffset */  \
   0,                            /* tp_iter */            \
   0,                            /* tp_iternext */        \
   Py##NAME##_Methods,           /* tp_methods */         \
   0,                            /* tp_members */         \
   0,                            /* tp_getset */          \
   0,                            /* tp_base */            \
   0,                            /* tp_dict */            \
   0,                            /* tp_descr_get */       \
   0,                            /* tp_descr_set */       \
   0,                            /* tp_dictoffset */      \
   (initproc)Py##NAME##_Init,    /* tp_init */            \
   0,                            /* tp_alloc */           \
   PyType_GenericNew,            /* tp_new */             \
 };                                                       \
 do {                                                     \
   if (PyType_Ready(&Py##NAME##Ty) < 0) {                 \
     return;                                              \
   }                                                      \
   Py_INCREF(&Py##NAME##Ty);                              \
   PyModule_AddObject(module, #NAME, (PyObject*)&Py##NAME##Ty); \
 } while (0)

namespace storage = hobbes::storage;

///
/// $ python
/// >>> import storage
/// >>> qc = storage.QueueConfig("StorageGroupName.pid.tid")
/// >>> qc.waitstate()
/// >>> qc.readindex()
/// >>> qc.writeindex()
///

struct PyQueueConfig {
  PyObject_HEAD
  storage::pqueue_config* impl;
};

static int PyQueueConfig_Init(PyQueueConfig* self, PyObject* args) {
  const char* name = NULL;
  if (!PyArg_ParseTuple(args, "s", &name)) {
    return -1;
  }

  try {
    storage::reader reader(storage::consumeQueue(name), storage::Platform);
    self->impl = new storage::pqueue_config(reader.config());
  } catch (const std::exception& ex) {
    PyErr_SetString(PyExc_RuntimeError, ex.what());
    return -1;
  }

  return 0;
}

static PyObject* PyQueueConfig_WaitState(PyQueueConfig* self) {
  return PyInt_FromLong(*self->impl->wstate);
}

static PyObject* PyQueueConfig_ReadIndex(PyQueueConfig* self) {
  return PyInt_FromLong(*self->impl->readerIndex);
}

static PyObject* PyQueueConfig_WriteIndex(PyQueueConfig* self) {
  return PyInt_FromLong(*self->impl->writerIndex);
}

static PyMethodDef PyQueueConfig_Methods[] = {
  {"waitstate",  (PyCFunction)PyQueueConfig_WaitState,  METH_NOARGS, "Return the wait state of the SHM queue"},
  {"readindex",  (PyCFunction)PyQueueConfig_ReadIndex,  METH_NOARGS, "Return the read index of the SHM queue"},
  {"writeindex", (PyCFunction)PyQueueConfig_WriteIndex, METH_NOARGS, "Return the write index of the SHM queue"},
  {NULL}  /* Sentinel */
};

///
/// $ python
/// >>> import storage
/// >>> txn = storage.Transaction("path-to-txn-file")
/// >>> txn.data() # transaction data
///

struct PyTransaction {
  PyObject_HEAD
  storage::Transaction* impl;
  uint8_t*              data;
  int                   fd;
};

static int PyTransaction_Init(PyTransaction* self, PyObject* args) {
  const char* name = NULL;
  if (!PyArg_ParseTuple(args, "s", &name)) {
    return -1;
  }

  self->fd = ::open(name, O_RDONLY);
  if (self->fd == -1) {
    PyErr_SetString(PyExc_RuntimeError, ::strerror(errno));
    return -1;
  }

  struct stat s;
  if (::fstat(self->fd, &s) == -1) {
    PyErr_SetString(PyExc_RuntimeError, ::strerror(errno));
    ::close(self->fd);
    return -1;
  }

  self->data = reinterpret_cast<uint8_t*>(::mmap(nullptr, s.st_size, PROT_READ, MAP_PRIVATE, self->fd, 0));
  if (self->data == MAP_FAILED) {
    PyErr_SetString(PyExc_RuntimeError, ::strerror(errno));
    ::close(self->fd);
    return -1;
  }

  size_t dsize = *reinterpret_cast<size_t*>(self->data);
  self->impl = new storage::Transaction(self->data + sizeof(size_t), dsize);

  return 0;
}

static PyObject* PyTransaction_Data(PyTransaction* self) {
  return PyByteArray_FromStringAndSize(reinterpret_cast<const char*>(self->impl->ptr()), self->impl->size());
}

static PyMethodDef PyTransaction_Methods[] = {
  {"data",   (PyCFunction)PyTransaction_Data,   METH_NOARGS, "Return the data payload of the current unprocessed transactions"},
  {NULL}  /* Sentinel */
};

static PyMethodDef ModuleMethods[] = {
  {NULL}
};

/// Extension registration & initialization
PyMODINIT_FUNC initstorage(void) {
  PyObject* module = Py_InitModule("storage", ModuleMethods);

  DEFINE_PY_TYPE(storage, QueueConfig, "QueueConfig objects");
  DEFINE_PY_TYPE(storage, Transaction, "Transaction objects");
}

#undef DEFINE_PY_TYPE

