/** 
 * file bm.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include "base.h"

/* Fetch the base name from the XML file */
void base_name(xmlDocPtr doc, xmlNodePtr cur, base_t* base){
    xmlChar *uri;
    while (cur != NULL) {
	    if ((!xmlStrcmp(cur->name, (const xmlChar *)"base"))) {
		    uri = xmlGetProp(cur, (xmlChar *)"name");
		    base->name = (char *)uri;
	    }
	    cur = cur->next;
	}
}

/* Fetch the base date from the XML file */
void base_date(xmlDocPtr doc, xmlNodePtr cur, base_t* base){
    char *endPtr;
    xmlChar *key;
    xmlNodePtr curBis;
 	cur = cur->xmlChildrenNode;
    while (cur != NULL) {
	   if ((!xmlStrcmp(cur->name, (const xmlChar *)"date"))) {
            curBis = cur->xmlChildrenNode;
            while(curBis != NULL){
                if ((!xmlStrcmp(curBis->name, (const xmlChar *)"day"))) {
                    key = xmlNodeListGetString(doc, curBis->xmlChildrenNode, 1);
                    base->day = strtol((char*)key, &endPtr, 10);
                    free(key);
                }
                if ((!xmlStrcmp(curBis->name, (const xmlChar *)"month"))) {
                    key = xmlNodeListGetString(doc, curBis->xmlChildrenNode, 1);
                    base->month = strtol((char*)key, &endPtr, 10);
                    free(key);
                }
                if ((!xmlStrcmp(curBis->name, (const xmlChar *)"year"))) {
                    key = xmlNodeListGetString(doc, curBis->xmlChildrenNode, 1);
                    base->year = strtol((char*)key, &endPtr, 10);
                    free(key);
                }
                curBis = curBis->next;
            }
 	    }
        cur = cur->next;
	}
}

/* Fetch the base country from the XML file */
void base_country(xmlDocPtr doc, xmlNodePtr cur, base_t* base){
    xmlChar *key;
    cur = cur->xmlChildrenNode;
    while (cur != NULL) {
	    if ((!xmlStrcmp(cur->name, (const xmlChar *)"country"))) {
		    key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
		    base->country = (char *)key;
	    }
	    cur = cur->next;
	}
}

/* Fetch the base facilities from the XML file */
void base_facilities(xmlDocPtr doc, xmlNodePtr cur, base_t *base){
    facility_t *facility;
    char *endPtr;
    xmlChar *key;
    xmlChar *uri;
    xmlNodePtr curBis;
    xmlNodePtr curBBis;
    cur = cur->xmlChildrenNode;
    while (cur != NULL) {
	    if ((!xmlStrcmp(cur->name, (const xmlChar *)"facilities"))) {
		    curBis = cur->xmlChildrenNode;
            while(curBis != NULL){
                if((!xmlStrcmp(curBis->name, (const xmlChar *)"facility"))){
                    facility = facility_create();
                    uri = xmlGetProp(curBis, (xmlChar *)"name");
                    facility->name = (void *)uri;
                    curBBis = curBis->xmlChildrenNode;
                    while(curBBis != NULL){
                        if ((!xmlStrcmp(curBBis->name, (const xmlChar *)"area"))) {
                            key = xmlNodeListGetString(doc, curBBis->xmlChildrenNode, 1);
                            facility->area = strtol((char*)key, &endPtr, 10);
                            free(key);
                        }
                        if ((!xmlStrcmp(curBBis->name, (const xmlChar *)"cost"))) {
                            key = xmlNodeListGetString(doc, curBBis->xmlChildrenNode, 1);
                            facility->cost = strtod((char*)key, &endPtr); 
                            free(key);
                        }
                        curBBis = curBBis->next;
                    }
                    base_add_facility(base, facility);
                }
                curBis = curBis->next;
            }
	    }
	    cur = cur->next;
	}
}

/* Reusable function to check if the command is correct */
int command_verif(char *check, double *cost, char *params, char *command){
    char *endPtr;
    errno = 0;
    if(check != NULL && strlen(params) > 0){
        *cost = strtod(params, &endPtr);
        if(*endPtr != '\0' || errno != 0){
            fprintf(stderr, "Invalid parameter for the %s command\n", command);
            return 1;
        } else {
            return 0;
        }
    } else {
        fprintf(stderr, "Missing parameter for the %s command\n", command);
        return 1;
    }   
}

int main(int argc, char *argv[]){
    base_t *base;
    char *str, params[18], *command, *check, *endPtr;
    int i, j;
    double *cost;
    xmlDocPtr doc;
    xmlNodePtr cur;

    cost = malloc(sizeof(double));
    str = malloc(sizeof(char*)*18);
    command = malloc(sizeof(char*)*18);

    doc = xmlParseFile(argv[1]);

    /* Check if there is the argument we are searching for */
    if(argc != 2){
        fprintf(stderr, "Invalid number of arguments\n");
        return 1;
    }

    /* Check if the XML file is well parsed */
    if (doc == NULL ) {
        fprintf(stderr,"Unable to parse the document\n");
        return 1;
    }

    cur = xmlDocGetRootElement(doc);

    /* Check if the XML file is empty or not */
    if (cur == NULL) {
        fprintf(stderr,"empty document\n");
        xmlFreeDoc(doc);
        return 1;
    }

    /* Search for the root element on the XML file and check if it exists */
    if (xmlStrcmp(cur->name, (const xmlChar *) "base")) {
        fprintf(stderr,"document of the wrong type, root node != base\n");
        xmlFreeDoc(doc);
        return 1;
    }    

    base = base_create();

    base_name(doc, cur, base);
    base_country(doc, cur, base);
    base_date(doc, cur, base);
    base_facilities(doc, cur, base);

    do{
        params[0] = '\0';
        printf("BM> ");
        fgets(str, 25, stdin);

        check = strstr(str, " "); /* Identify when there is a space character detected */
        str[strlen(str) - 1] = '\0';

        /* If there is a space character then manipulate all the variables to separate command and params */
        if(check != NULL){
            i = 0;
            while(str[i] != ' '){
                i++;
            }
            for(j = 0; j < i; j++){
                command[j] = str[j];
            }
            for(i = i+1, j = 0; i < strlen(str); i++, j++){
                params[j] = str[i];
            }
            params[j] = '\0';
        }

        
        /* Menu creator */
        if(strlen(str)<=18){
            if(strcmp(str, "h") == 0){
                printf("b: Prints the base\n");
                printf("c: Prints the base country\n");
                printf("d: Prints the base date\n");
                printf("f: Prints the base facilities\n");
                printf("fc COST: Prints the base facilities with the cost equal to COST\n");
                printf("fcge COST: Prints the base facilities with the cost greater than or equal to COST\n");
                printf("fcgt COST: Prints the base facilities with the cost greater than COST\n");
                printf("fcle COST: Prints the base facilities with the cost less than or equal to COST\n");
                printf("fclt COST: Prints the base facilities with the cost less than COST\n");
                printf("fn NAME: Prints the base facilities with the name containing NAME\n");
                printf("h: Prints this help\n");
                printf("n: Prints the base name\n");
                printf("t: Prints the base total cost\n");
                printf("v: Prints the BM version\n");
                printf("q: Quits BM\n");
            } else if (strcmp(str, "b") == 0){
                base_handle_b(*base);
            } else if (strcmp(str, "c") == 0){
                base_handle_c(*base);
            } else if (strcmp(str, "d") == 0){
                base_handle_d(*base);
            } else if (strcmp(str, "f") == 0){
                base_handle_f(*base);
            } else if (check != NULL ? strcmp(command, "fc") == 0 : strcmp(str, "fc") == 0){ /* This line means that if there is a space character, just handle the command, if not, handle the whole string */
                if(command_verif(check, cost, params, command) == 0){
                    base_handle_fc(*base, *cost);
                }
            } else if (check != NULL ? strcmp(command, "fcge") == 0 : strcmp(str, "fcge") == 0){
                if(command_verif(check, cost, params, command) == 0){
                    base_handle_fcge(*base, *cost);
                }
            } else if (check != NULL ? strcmp(command, "fcgt") == 0 : strcmp(str, "fcgt") == 0){
                if(command_verif(check, cost, params, command) == 0){
                    base_handle_fcgt(*base, *cost);
                }
            } else if (check != NULL ? strcmp(command, "fcle") == 0 : strcmp(str, "fcle") == 0){
                if(command_verif(check, cost, params, command) == 0){
                    base_handle_fcle(*base, *cost);
                }
            } else if (check != NULL ? strcmp(command, "fclt") == 0 : strcmp(str, "fclt") == 0){
                if(command_verif(check, cost, params, command) == 0){
                    base_handle_fclt(*base, *cost);
                }
            } else if (check != NULL ? strcmp(command, "fn") == 0 : strcmp(str, "fn") == 0){
                if(check != NULL && strlen(params) > 0){
                    strtod(params, &endPtr);
                    base_handle_fn(*base, params);
                } else {
                    fprintf(stderr, "Missing parameter for the fn command\n");
                }
            } else if (strcmp(str, "n") == 0){
                base_handle_n(*base);
            } else if (strcmp(str, "t") == 0){
                base_handle_t(*base);
            } else if (strcmp(str, "v") == 0){
                printf("BM (Base Manager) 20211125\n\nCopyright (C) 2021 Pierre Amari and Mohamed Amine Saroh.\n\nWritten by Pierre Amari <pierre.amari@etud.univ-pau.fr> and Mohamed Amine Saroh <masaroh@etud.univ-pau.fr>.\n");
            } else if (strcmp(str, "q") == 0);
            else{
                fprintf(stderr, "Invalid command\n");
            }
        }else {
            fprintf(stderr, "Too many characters for the command!\n");
        }  

    }while(strcmp(str, "q") != 0);

    /* Dynamically allocated memory is free here */
    base_free(base);
    xmlFreeDoc(doc);
    free(cost);
    free(str);
    free(command);
    xmlCleanupParser();

    return 0; 
}
