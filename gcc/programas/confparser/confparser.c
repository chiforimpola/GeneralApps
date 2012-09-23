
#ifndef _CONF_PARSER_C
#define _CONF_PARSER_C
#include <string.h>
#include "confparser.h"
#include <stdlib.h>
#include <stdio.h>

struct confparserparameters     *cpfirst = NULL,
                                *cplast  = NULL;

struct ConfParser               *confparserfirst = NULL,
                                *confparserlast  = NULL;

struct ConfParser* createNode (unsigned long int conffileid, char *node) {
    struct ConfParser *c = (struct ConfParser*) malloc (sizeof (struct ConfParser)+strlen (node)+1);

    if (c == NULL) return (NULL);

    c->next = NULL;
    c->node = (char*) malloc (strlen (node)+1);
    strcpy (c->node, node);
    c->conffileid = conffileid;

    if (confparserfirst == NULL) {
        c->id = 0;
        confparserfirst = c;
        confparserfirst->previous = NULL;
        confparserlast = confparserfirst;
    } else {
        confparserlast->next = c;
        c->previous = confparserlast;
        c->id = c->previous->id+1;
        confparserlast = c;
    }
    return (c);
}

int addParameter (struct ConfParser *c, char *parameter, char *value) {
    struct confparserparameters *a = (struct confparserparameters*) malloc (sizeof (struct confparserparameters)+strlen (parameter)+strlen(value)+2);

    if  (a == NULL) return (-1);

    a->parameter = (char*) malloc (strlen (parameter)+1);
    a->value = (char *) malloc (strlen (value)+1);
    strcpy (a->parameter, parameter);
    strcpy (a->value, value);

    a->next = NULL;
    a->fatherid = c->id;
    a->conffileid = c->conffileid;
    a->focused = 0;

    if (cpfirst == NULL) {
        a->previous = NULL;
        cpfirst = a;
        cplast = cpfirst;
    } else {
        cplast->next = a;
        a->previous = cplast;
        cplast = a;
    }
    return (1);
}


/*
 * Recuperar a informacao de um atributo baseado em seu nodo e na identificacao
 * de seu arquivo de configuracao
 */
struct confparserparameters *getNodeValue (unsigned long int conffileid, char *node) {
    struct ConfParser   *c;
    struct confparserparameters   *a;
    static int           executed = 0;

    if (cpfirst == NULL || confparserfirst == NULL) return (NULL);

    else {
        for (c = confparserfirst;c != NULL;c = c->next) {
            if (strcmp (c->node, node) == 0) {
                for (a = cpfirst;a != NULL;a = a->next) {
                    if (a->conffileid == conffileid && a->fatherid == c->id) {
                        if (a->focused == 1) {
                            a->focused = 0;
                           if (a->next != NULL && a->next->conffileid == conffileid && a->next->fatherid == c->id) {
                               a->next->focused = 1;
                               return (a->next);
                           } else {
                               executed = 0;
                               a->focused = 0;
                               return (NULL);
                           }
                        } else {
                            if (executed == 0) {
                                a->focused = 1;
				executed = 1;
                                return (a);
                            }
                        }
                    }
                }
            }
        }
    }
    return (NULL);
}

int parser (unsigned long int conffileid, char *path) {
    FILE                  *f = fopen (path, "r");
    unsigned long int      fsize,
                           i,
                           i2;
    char                  *buffer,
                           node[100],
                           parameter[100],
                           value[1000];
    struct ConfParser     *c;

    if (f == NULL) return (-1);

    fseek (f, 0, SEEK_END);
    fsize = ftell (f);
    rewind (f);

    buffer = (char *) malloc (sizeof(char)*fsize+1);
    fread (buffer, 1, fsize, f);

    node[0] = '\0';

    for (i = 0;i < fsize;i++) {
        if (buffer[i] == '[') {
            i2 = 0;
            ++i;
            while (buffer[i] != ']') {
                node[i2++] = buffer[i++];
            }
            node[i2] = '\0';
            c = createNode (conffileid, node);
            while (buffer[i] != '\n') ++i;
        } else if (node[0] != '\0' && buffer[i] != '\n') {
            i2 = 0;
            while (buffer[i] != ' ' && buffer[i] != '=') parameter[i2++] = buffer[i++];
            parameter[i2] = '\0';

            while (buffer[i] == ' ' || buffer[i] == '=') i++;
            value[0] = buffer[i++];
            i2 = 1;
            while (buffer[i] != '\n') value[i2++] = buffer[i++];
            value[i2] = '\0';
            addParameter (c, parameter, value);
        }
    }
    return (1);
}


#endif

