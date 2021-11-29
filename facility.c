/** 
 * file facility.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include "facility.h"

facility_t *facility_create(){
    facility_t *facility;
    facility = malloc(sizeof(facility_t));
    if(facility == NULL){
        fprintf(stderr, "Unable to allocate the memory\n");
        return NULL;
    }

    facility->area = 0;
    facility->cost = 0.;
    facility->name = NULL;
    return facility;
}

void facility_free(facility_t *facility){
    free(facility->name);
    free(facility);
}
 
void facility_handle_f(facility_t facility){
    printf("%s, %d m2, %f USD\n", facility.name, facility.area, facility.cost);
}

void facility_handle_fc(facility_t facility,double cost){
    printf("%s, %d m2, %f USD\n", facility.name, facility.area, facility.cost);
}

void facility_handle_fcge(facility_t facility,double cost){
    printf("%s, %d m2, %f USD\n", facility.name, facility.area, facility.cost);
}

void facility_handle_fcgt(facility_t facility,double cost){
    printf("%s, %d m2, %f USD\n", facility.name, facility.area, facility.cost);
}

void facility_handle_fcle(facility_t facility,double cost){
    printf("%s, %d m2, %f USD\n", facility.name, facility.area, facility.cost);
}

void facility_handle_fclt(facility_t facility,double cost){
    printf("%s, %d m2, %f USD\n", facility.name, facility.area, facility.cost);
}

void facility_handle_fn(facility_t facility,const char *name){
    printf("%s, %d m2, %f USD\n", facility.name, facility.area, facility.cost);
}