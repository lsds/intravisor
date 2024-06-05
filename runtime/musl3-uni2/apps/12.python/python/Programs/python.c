/* Minimal main program -- everything is loaded from the library */

#include "Python.h"
#include "pycore_pylifecycle.h"

#ifdef MS_WINDOWS
int
wmain(int argc, wchar_t **argv)
{
    return Py_Main(argc, argv);
}
#else
int
#ifndef INTRAVISOR
main(int argc, char **argv)
#else
python_main(int argc, char **argv)
#endif
{
    return Py_BytesMain(argc, argv);
}
#endif
