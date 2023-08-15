from ctypes import *
import os

xss = cdll.LoadLibrary(os.path.abspath("/app/libtest.so"))
print(xss.test())