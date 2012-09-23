import marshal, types


def save_function(function, output_path):
    if isinstance(function, types.FunctionType):
        f = open(output_path, 'w')
        if f:
            f.write(marshal.dumps(function.func_code))
            f.close()
            return (True)
    return (None)

def load_function(function_name, file_path):
    f = open(file_path)
    if f:
        function_code = marshal.loads(f.read())
        if function_code:
            function = types.FunctionType(function_code, globals(), function_name)
            if function:
                return (function)
    return (None)
