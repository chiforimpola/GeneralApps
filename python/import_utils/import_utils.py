# -*- coding: utf-8 -*-

import sys, os

PYTHON_FILE_EXTENSION = [
  'py',
  'pyc'
]

def recursive_import(dir_path, recursion_level=5, force_import=False):
    dir_path = os.path.realpath(dir_path)
    if os.path.isdir(dir_path):
        dir_elements = os.listdir(dir_path)
        result = []
        files_to_import = []
        if dir_elements:
            found_py_file = False
            for element in dir_elements:
                if os.path.isdir(dir_path + os.sep + element) and recursion_level > 0:
                    path_list = recursive_import( dir_path + os.sep + element, recursion_level-1, force_import )
                    if path_list:
                        for path in path_list:
                            result.append(path)
                if os.path.isfile(dir_path + os.sep + element) and element[-2:] in PYTHON_FILE_EXTENSION:
                    found_py_file = True
                    if force_import:
                        files_to_import.append(element)
            if found_py_file:
                result.append(dir_path)
                sys.path.append(dir_path)
                if files_to_import:
                    for imp in files_to_import:
                        if imp[-2:] in PYTHON_FILE_EXTENSION:
                            exec ('import ' +  imp[:-3])
                        else:
                            exec ('import ' + imp)
            if result:
                return (result)
    return (None)

