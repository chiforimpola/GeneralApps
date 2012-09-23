import sys

def explode (source, startindex = 1, crv = []):
    result = {}
    result['error'] = 0
    cmdindex = 'command'
    paramindex = 'parameter'
    result[cmdindex] = []
    result[paramindex] = []
    error = {}
    error['error'] = 0
    i = startindex
    while i < len (source):
        if source[i][0] == '-':
            if len (crv) > 0:
                for i2 in range (0, len (crv)):
                    if crv[i2] == source[i][1:]:
                        try:
                            result[source[i][1:]] = source[i+1]
                            i += 1
                        except:
                            error['error'] = 1
                            return (error)
            else:
                result[cmdindex].append (source[i][1:])

        else:
            result[paramindex].append (source[i])
        i += 1
                        
    return (result)

def cmd_exists(source, parameter):
    slhparameter = 0
    while parameter[slhparameter] == '-': slhparameter += 1

    for i in source:
        slhsource = 0
        while i[slhsource] == '-': slhsource += 1
        if i[slhsource:] == parameter[slhparameter:] and slhsource > 0:
            return (1)
    return (0)
