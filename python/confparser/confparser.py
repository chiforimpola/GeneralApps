

def parser(path):
    file_contents = open(path).read()
    buffer_contents = ""
    result = []
    parameter  = ""
    value = ""
    map_tags = {}
    ultra_map = {}

    for i in range (0, len(file_contents)):
        if file_contents[i] != " ":
            buffer_contents += file_contents[i]

    file_contents = ""
    i = 0
    flag = 1
    ultra_map_index = ""
    while i < len(buffer_contents):

        if buffer_contents[i] == '[':
            if len (map_tags) > 0:
               ultra_map[ultra_map_index] = map_tags
               map_tags = {}
            ultra_map_index = ''
            flag = 0

        elif flag == 0:
           if buffer_contents[i] != ']':
               ultra_map_index += buffer_contents[i]
           else:
               flag = 1
               ultra_map_index

        elif flag == 1:
            if buffer_contents[i] != '=':
                  if buffer_contents[i] != '\n':
                    parameter += buffer_contents[i]
            else:
                flag = 2

        elif flag == 2:
            if buffer_contents[i] != "\n":
                value += buffer_contents[i]
            else:
                flag = 1
                map_tags[parameter] = value
                parameter = value = ""

        i += 1
    if ultra_map_index != '':
        ultra_map[ultra_map_index] = map_tags

    return (ultra_map)
