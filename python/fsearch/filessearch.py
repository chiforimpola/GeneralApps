
import os
import sys
from parameters import explode, param_exists

def getByType(types, path, recursive = False, maxdepth = 5):
        objs = os.listdir (path)
        files_found = []
        slash_index = 0

        if not isinstance (types, (list)):
            aux = []
            aux.append (types)
            types = aux

        if len (types) == 0: return (types)

        for i in objs:
                if maxdepth == 0: break
                if recursive:
                    if os.path.isdir (path + "/" + i) and i != '.' and i != '..':
                        aux = getByType (types, path + "/" + i, True, maxdepth-1)
                        if len (aux) > 0:
                            for i in aux:
                                files_found.append (i)

                i2 = len (i)-1 
		slash_index = 0
                while i2 != 0:
                    if i[i2] != '.': slash_index += 1
                    else: break
                    i2 -= 1

                if slash_index == 0 or i2 == 0:slash_index = 3

                if not i[-slash_index:].islower():
                        if i[-slash_index:].lower() in types:
                            files_found.append (os.path.normpath(path + "/" + i))

                for i2 in types:
                    if i2 == i[-slash_index:]:
                        files_found.append (os.path.normpath(path + "/" + i))

        return (files_found)

def showHelp():
    helpmessage = "\
        -dir           \t directory abspath\n\
        -maxdepth      \t max recursion level\n\
        -execute       \t excute command\n\
        -h, -help      \t show this menu\n\
                  "
    print (helpmessage)

if len (sys.argv) > 1:
    args = explode (sys.argv, 1, ('dir', 'maxdepth'))
    types = args['parameter']
    commands = args['command']

    source = "."
    maxdepth = 5
    count = False

    if param_exists (sys.argv, 'help') or param_exists(sys.argv, 'h'):
       showHelp()
       sys.exit ()
    if param_exists (sys.argv, 'dir'):
        source = args['dir']
    if param_exists (sys.argv, 'maxdepth'):
        maxdepth = args['maxdepth']
    if param_exists (sys.argv, 'count'):
        count = True

    query = []
    query = getByType (types, source, True, int (maxdepth))
    for i in query: print i
    if count: print ('Total: '+str(len (query)))
