from sys import argv, stdout, exit

def checkTimeFormat (parameter):
    ok = False
    checkHour = False
    checkMinute = False
    checkSecond = False
    checkMilisecond = False
    hour = ''
    minute = ''
    second = ''
    milisecond = ''
    result = {}
    aux = ''
    flag = 0
    for i in range (0, len (parameter)+1):
        if i != len(parameter) and parameter[i] != ':' and parameter[i] != ',':
            aux += parameter[i]
        else:
            if flag == 0:
                checkHour = True
                hour = aux
                aux = ''
                flag = 1
            elif flag == 1:
                checkMinute = True
                minute = aux
                aux = ''
                flag = 2
            elif flag == 2:
                checkSecond = True
                second = aux
                aux = ''
                flag = 3
            elif flag == 3:
               checkMilisecond = True
               milisecond = aux
               aux = ''
               flag = 4
    if checkHour and checkMinute and checkSecond and checkMilisecond:
        result['hour'] = hour
        result['minute'] = minute
        result['second'] = second
        result['milisecond'] = milisecond
        return (result)
    else:
        return (False)


def sumTime (operand1, operand2):
    operand1['milisecond'] = int (operand1['milisecond'])
    operand1['second'] = int (operand1['second'])
    operand1['minute'] = int (operand1['minute'])
    operand1['hour'] = int (operand1['hour'])

    operand2['milisecond'] = int (operand2['milisecond'])
    operand2['second'] = int (operand2['second'])
    operand2['minute'] = int (operand2['minute'])
    operand2['hour'] = int (operand2['hour'])

    hours = -1
    minutes = -1
    seconds = -1
    miliseconds = -1

    result = {}

    if operand1['milisecond'] + operand2['milisecond'] > 999:
        seconds = (operand1['milisecond'] + operand2['milisecond']) / 999
        result['milisecond'] = ((operand1['milisecond'] + operand2['milisecond']) % 999) -1
        operand1['second'] += seconds
    else:
        result['milisecond'] = operand1['milisecond'] + operand2['milisecond']

    if operand1['second'] + operand2['second'] > 60:
        minutes = (operand1['second'] + operand2['second']) / 60
        result['second'] = ((operand1['second'] + operand2['second']) % 60) - 1
        operand1['minute'] += minutes
    else:
        result['second'] = operand1['second'] + operand2['second']

    if operand1['minute'] + operand2['minute'] > 60:
        hours = (operand1['minute'] + operand2['minute']) / 60
        result['minute'] = ((operand1['minute'] + operand2['minute']) % 60) - 1
        operand1['hour'] += hours
    else:
        result['minute'] = operand1['minute'] + operand2['minute']

    if operand1['hour'] + operand2['hour'] > 99:
        result['hour'] = 99
        result['minute'] = 59
        result['second'] = 59
        result['milisecond'] = 999
    else:
        result['hour'] = operand1['hour'] + operand2['hour']

    result['hour'] = str (result['hour'])
    result['minute'] = str (result['minute'])
    result['second'] = str (result['second'])
    result['milisecond'] = str (result['milisecond'])

    if len (result['hour']) == 1: result['hour'] = '0'+result['hour']
    if len (result['minute']) == 1: result['minute'] = '0'+result['minute']
    if len (result['second']) == 1: result['second'] = '0'+result['second']
    if len (result['milisecond']) == 1: result['milisecond'] = '00'+result['milisecond']
    elif len (result['milisecond']) == 2: result['milisecond'] = '0'+result['milisecond']

    #print str(operand1['hour'])+':'+str(operand1['minute'])+':'+str(operand1['second'])+','+str(operand1['milisecond'])
    #print str(operand2['hour'])+':'+str(operand2['minute'])+':'+str(operand2['second'])+','+str(operand2['milisecond'])
    #print result['hour']+':'+result['minute']+':'+result['second']+','+result['milisecond']
    return (result)


#fixme
#corrigir o problema das casas decimais durante a divisao
def difTime (operand1, operand2):
    operand1['milisecond'] = int (operand1['milisecond'])
    operand1['second'] = int (operand1['second'])
    operand1['minute'] = int (operand1['minute'])
    operand1['hour'] = int (operand1['hour'])

    operand2['milisecond'] = int (operand2['milisecond'])
    operand2['second'] = int (operand2['second'])
    operand2['minute'] = int (operand2['minute'])
    operand2['hour'] = int (operand2['hour'])

    hours = -1
    minutes = 0
    seconds = -1
    miliseconds = -1

    result = {}

    if operand1['milisecond'] - operand2['milisecond'] < 0:
        seconds = ((operand1['milisecond'] - operand2['milisecond'])*-1) / 999
        result['milisecond'] = (((operand1['milisecond'] - operand2['milisecond'])*-1) % 999) -1
        operand1['second'] -= seconds
    else:
        result['milisecond'] = operand1['milisecond'] - operand2['milisecond']

    if operand1['second'] - operand2['second'] < 0:
        #minutes = ((operand1['second'] - operand2['second'])*-1) / 60
        #result['second'] = (((operand1['second'] + operand2['second'])*-1) % 60) - 1
        #operand1['minute'] -= minutes
        minutes = 1
        result['second'] = (operand1['second'] + 60) - operand2['second']
    else:
        result['second'] = operand1['second'] - operand2['second']

    if operand1['minute'] - operand2['minute'] < 0 and operand1['minute'] > 0 and operand2['minute'] > 0:
        hours = ((operand1['minute'] - operand2['minute'])*-1) / 60
        result['minute'] = (((operand1['minute'] - operand2['minute'])*-1) % 60) - 1
        operand1['hour'] -= hours
    else:
        result['minute'] = operand1['minute'] - operand2['minute'] - minutes
        minutes = 0

    if operand1['hour'] - operand2['hour'] > 99:
        result['hour'] = 0
        result['minute'] = 0
        result['second'] = 0
        result['milisecond'] = 0
    else:
        result['hour'] = operand1['hour'] - operand2['hour']

    result['hour'] = str (result['hour'])
    result['minute'] = str (result['minute'])
    result['second'] = str (result['second'])
    result['milisecond'] = str (result['milisecond'])

    if len (result['hour']) == 1: result['hour'] = '0'+result['hour']
    if len (result['minute']) == 1: result['minute'] = '0'+result['minute']
    if len (result['second']) == 1: result['second'] = '0'+result['second']
    if len (result['milisecond']) == 1: result['milisecond'] = '00'+result['milisecond']
    elif len (result['milisecond']) == 2: result['milisecond'] = '0'+result['milisecond']
    
    #print str(operand1['hour'])+':'+str(operand1['minute'])+':'+str(operand1['second'])+','+str(operand1['milisecond'])
    #print str(operand2['hour'])+':'+str(operand2['minute'])+':'+str(operand2['second'])+','+str(operand2['milisecond'])
    #print result['hour']+':'+result['minute']+':'+result['second']+','+result['milisecond'] + "\n\n"
    return (result)


#Completar a funcao 'parser'
#Essa funcao possui como responsabilidades:
#-> Realizar um parser no arquivo
#-> alterar o tempo das legendas baseado na operacao definida (forward, rewind)
def parser (file_path, operation, time):
    contents = open(file_path).read()
    output = open(file_path+'.output', 'w')
    buf = ''
    for i in range (0, len(contents)):
        if contents[i] != '\n':
            buf += contents[i]
        else:
            i2 = 0
            aux = ''
            timeA = ''
            timeB = ''
            flag = 0
            for a in range (0, len (buf)):
                if buf[a] != '\r':
                    aux += buf[a]
            buf = aux
            aux = ''
            while i2 <= len (buf):
                if i2 < len (buf) and buf[i2] != ' ':
                    aux += buf[i2]
                else:
                    if i2 == len (buf) and flag == 0: #nao eh linha de tempo, portanto salva no output
                        output.write (buf+"\n")
                        break
                    elif flag == 0:
                        while i2 < len (buf) and buf[i2] != '-': i2 += 1
                        if i2 == len (buf): #nao encontrou '-->', portanto nao eh linha de tempo
                            output.write (buf+"\n")
                            break
                        if i2+2 < len (buf) and buf[i2+1] == '-' and buf[i2+2] == '>':
                            i2 += 3
                            changedI2 = 0
                            while buf[i2] == ' ':
                                changedI2 = 1
                                i2 += 1
                            if changedI2:
                                i2 -= 1
                            timeA = aux
                            aux = ''
                            flag = 1
                    elif flag == 1:
                        #realizo o tratamento do segundo tempo, para evitar ultimo caractere ilegal
                        if aux[len(aux)-1] != '0' and aux[len(aux)-1] != '1' and aux[len(aux)-1] != '2' and aux[len(aux)-1] != '3' and aux[len(aux)-1] != '4' and aux[len(aux)-1] != '5' and aux[len(aux)-1] != '6' and aux[len(aux)-1] != '7' and aux[len(aux)-1] != '8' and aux[len(aux)-1] != '9':
                            timeB = aux[0:len(aux)-1]
                        else:
                            timeB = aux
                        timeA = checkTimeFormat (timeA)
                        timeB = checkTimeFormat (timeB)
                        dif = 0
                        if operation == 'forward': #-------------------------------finalizar-------------------------------------------
                            resultA = sumTime (timeA, time)
                            resultB = sumTime (timeB, time)
                            #salvar resultado no arquivo
                            output.write (resultA['hour']+':'+resultA['minute']+':'+resultA['second']+','+resultA['milisecond'])
                            output.write (" --> ")
                            output.write (resultB['hour']+':'+resultB['minute']+':'+resultB['second']+','+resultB['milisecond']+"\n")
                        if operation == 'rewind':
                            resultA = difTime (timeA, time)
                            resultB = difTime (timeB, time)
                            #salvar resultado no arquivo
                            output.write (resultA['hour']+':'+resultA['minute']+':'+resultA['second']+','+resultA['milisecond'])
                            output.write (" --> ")
                            output.write (resultB['hour']+':'+resultB['minute']+':'+resultB['second']+','+resultB['milisecond']+"\n")
                        break
                i2 += 1
            buf = ''
    return (True)

if len(argv) < 3:
    message = '\
               [file] [operation] [time]\n\
               [file]\t\tabsolute file path\n\
               [operation]\tcan be [forward] or [rewind]\n\
               [time]\t\tformat: hours:minutes:seconds:miliseconds\n'
    print (message)

else:
    file_path = argv[1]
    operation = argv[2]
    time = argv[3]

    if operation != 'forward' and operation != 'rewind':
        print ('Operation ['+operation+'] not supported!')
    else:
        time = checkTimeFormat (time)
        if time == False:
            print ('Incorrect time format!')
        else:
            if parser (file_path, operation, time) == -1:
                print ('Erro ao realizar parser')

