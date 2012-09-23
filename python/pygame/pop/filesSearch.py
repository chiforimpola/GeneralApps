
import os

def getByType(types, path, recursive = False, maxdepth = 5):
        objs = os.listdir (path)
        files_found = []
        for i in objs:
                if maxdepth == 0: break
                if recursive:
                    if os.path.isdir (path + "/" + i):
                        aux = getByType (types, path + "/" + i, True, maxdepth-1)
                        if len (aux) > 0:
                            for i in aux:
                                files_found.append (i)

                if not i[-3:].islower():
                        if i[-3:].lower() in types:
                                files_found.append (os.path.normpath(path + "/" + i))

                elif i[-3:] in types:
                        files_found.append (os.path.normpath(path + "/" + i))

        return (files_found)

