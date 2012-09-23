#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "confparser.h"
#include "getfilecontents.h"

#define CONF_FILE "conf"
#define FILE_PREFIX "file"
#define PARSER_INDEX 0
#define PARSER_TIME 1
#define PARSER_MESSAGE 2

struct submanager_time {
    int                      hour,
                             minute,
                             second,
                             milisecond;
};
std::vector <struct submanager_time> vop1;
std::vector <struct submanager_time> vop2;
std::vector <std::string> vmessage;
std::vector <unsigned long int> vindex;

bool submanager_istime (std::string);
int  submanager_calculatetime(std::string operation);
int  submanager_parser (std::string);
int  submanager_init (std::string, std::string, std::string);

int main (int argc, char *argv[]) {
    struct confparserparameters *conf;
    unsigned long int            i = 0,
                                 chrid = 65;
    char                        *nodename,
                                 auxnodename[2];

    parser (0, CONF_FILE);

    nodename = (char *) malloc (strlen (FILE_PREFIX)+2);
    for (chrid = 65;chrid < 120;chrid++) {
        short int        found = 0;
        std::string      operation = "",
                         abspath = "",
                         time = "";
        auxnodename[0] = (char) chrid;
        auxnodename[1] = '\0';
        strcpy (nodename, FILE_PREFIX);
        strcat (nodename, auxnodename);
        while ( (conf=getNodeValue(i, nodename)) != NULL ) {
            std::string   parameter = conf->parameter,
                          value     = conf->value;

            if (parameter == "abspath") abspath = value;
            else if (parameter == "operation") operation = value;
            else if (parameter == "time") time = value;
        }
        if (abspath == "" && operation == "" && time == "") break;
        else {
            submanager_init (abspath, operation, time);
        }
    }
}



/*
 * implementacao das funcoes:
 *  -parser
 *  -calculo do tempo
 *  -save do arquivo de saida
 */

int submanager_init (std::string path, std::string operation, std::string time) {
    submanager_parser (path);
}


int submanager_parser (std::string path) {
    std::string         contents = getFileContents ((char*)path.c_str());
    short int           subbuffer = 0;//1 = leu valores da legenda | 0 = ainda nao leu nada
    unsigned long int   i,
                        flag = PARSER_INDEX,
                        index;
    std::string         buffer = "",
                        message = ""; 
    /*
     * declaracao das informacoes que serao inseridas na struct
     */
    submanager_time    op1, op2;
int msg = 0;
    for (i = 0;i < contents.size();i++) {
        if (contents[i] != '\n')
            buffer += contents[i];
        else if (buffer.size() > 1) {
            //linha de indice
            index = atoi (buffer.c_str());
            if (index !=0 ) {
std::cout << "index " << buffer << std::endl;
if (msg) exit(1);
            }
            //linha de tempo
            else if (submanager_istime(buffer)) {
std::cout << " tempo " << buffer << std::endl;
                /*std::string  aux = "";
                int          timeflag = 0,
                             operandflag = 0;
                for (int i2 = 0;i2 < buffer.size();i2++) {
                    if (buffer[i2] != ':' && i2+1 < buffer.size() && buffer[i2] != ' ' && buffer[i2] != '-' && buffer[i2] != ',') aux += buffer[i2];
                    else if (buffer[i2] == '-') {
                        operandflag = 1;
                        while (buffer[i2] == ' ' || buffer[i2] == '-' || buffer[i2] == '>') i2++;
                        i2--;
                        aux = "";
                        timeflag = 0;
                    }
                    else {
                        switch (timeflag) {
                            case 0: //hour
                                if (operandflag == 0) op1.hour = atoi (aux.c_str());
                                else op2.hour = atoi (aux.c_str());
                                timeflag = 1;
                                break;
                            case 1: //minuto
                                if (operandflag == 0) op1.minute = atoi (aux.c_str());
                                else op2.minute = atoi (aux.c_str());
                                timeflag = 2;
                                break;
                            case 2: //second
                               if (operandflag == 0) op1.second = atoi (aux.c_str());
                               else op2.second = atoi (aux.c_str());
                               timeflag = 3;
                               break;
                            case 3: //milisecond
                                if (operandflag == 0) op1.milisecond = atoi (aux.c_str());
                                else op2.milisecond = atoi (aux.c_str());
                                while (buffer[i2] != '-') i2++;
                                i2--;
                                timeflag = 0;
                                break;
                        }
                        aux = "";
                    }
                }
                //terminou de ler linha de tempo
                //std::cout << op1.hour << ", " << op1.minute << ", " << op1.second << ", " << op1.milisecond << std::endl;
                //std::cout << op2.hour << ", " << op2.minute << ", " << op2.second << ", " << op2.milisecond << std::endl;
                buffer = "";*/
            }
            //linha de mensagem
            else {
std::cout << " mensagem " << buffer << std::endl;msg = 1;
            }
            buffer = "";
        }
    }
}



/*
 * submanager_istime(std::string) : bool
 * retorna true se o parametro esta no formato de tempo padrao do arquivo de legendas
 * retorna false caso contrario
 */
bool submanager_istime (std::string str) {
    for (int i = 0;i < str.size();i++)
        if (str[i] == '-' && i+2 < str.size()){
            if (str[i+1] == '-' && str[i+2] == '>') return (true);
        }
    return (false);
}
