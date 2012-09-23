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



#Completar a funcao 'parser'
#Essa funcao possui como responsabilidades:
#-> Realizar um parser no arquivo
#-> alterar o tempo das legendas baseado na operacao definida (forward, rewind)
def parser (file_path, operation, time):
    contents = open(file_path).read()
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
            while i2 <= len (buf):
                if i2 < len (buf) and buf[i2] != ' ':
                    aux += buf[i2]
                else:
                    if i2 == len (buf) and flag == 0: #nao eh linha de tempo, portanto salva no output
                        print aux
                        break
                    elif flag == 0:
                        while i2 < len (buf) and buf[i2] != '-': i2 += 1
                        if i2 == len (buf): #nao encontrou '-->', portanto nao eh linha de tempo
                            break
                        if buf[i2+1] == '-' and buf[i2+2] == '>':
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
                        if aux[len(aux)] != '0' and 
                           aux[len(aux)] != '1' and:
                            timeB = aux[0:len(aux)-1]
                        else:
                            timeB = aux
                        timeA = checkTimeFormat (timeA)
                        timeB = checkTimeFormat (timeB)
                        print timeA
                        print timeB
                        exit()
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

