import sys
EXTERNAL_MODULES = '/media/PENDRIVE/principal/desenvolvimento/python/resource/modules/'
sys.path.append (EXTERNAL_MODULES)
import dircontroller
import parameters

def readdir (path, maxdepth = 1):
    return (dircontroller.parsedir (path, maxdepth))

