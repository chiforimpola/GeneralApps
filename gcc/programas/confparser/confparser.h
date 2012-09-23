
#ifndef _CONF_PARSER_H
#define _CONF_PARSER_H

struct confparserparameters {
    char                  *parameter,
                          *value;
    unsigned long int      fatherid,
                           conffileid;
    unsigned short int     focused;
    struct confparserparameters     *next, *previous;
};

struct ConfParser {
    char                *node;
    unsigned long int    id,
                         conffileid;
    struct ConfParser   *next, *previous;
};

struct ConfParser* createNode (unsigned long int, char *);
int addParameter (struct ConfParser*, char *, char *);
struct confparserparameters *getNodeValue (unsigned long int, char *);
int parser (unsigned long int, char *);

#endif

