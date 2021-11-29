/** 
 * file facility.h
 */
#ifndef FACILITY_H
#define FACILITY_H

/**
 * A facility.
 */
typedef struct{
    int area; /**< The facility area (in m2).*/
    double cost; /**< The facility cost (in USD).*/
    char *name; /**< The facility name.*/
} facility_t;

/**
 * Creates a facility.
 * return NULL on error (i.e., if the memory allocation is a failure), else a facility.
 */
facility_t *facility_create();

/**
 * Frees a facility.
 * param facility The facility.
 */
void facility_free(facility_t *facility);

/**
 * Handles the f command for a facility.
 * param facility The facility.
 */
void facility_handle_f(facility_t facility);

/**
 * Handles the fc command for a facility.
 * param facility The facility.
 * param cost The facility cost.
 */
void facility_handle_fc(facility_t facility,double cost);

/**
 * Handles the fcge command for a facility.
 * param facility The facility.
 * param cost The facility cost.
 */
void facility_handle_fcge(facility_t facility,double cost);

/**
 * Handles the fcgt command for a facility.
 * param facility The facility.
 * param cost The facility cost.
 */
void facility_handle_fcgt(facility_t facility,double cost);

/**
 * Handles the fcle command for a facility.
 * param facility The facility.
 * param cost The facility cost.
 */
void facility_handle_fcle(facility_t facility,double cost);

/**
 * Handles the fclt command for a facility.
 * param facility The facility.
 * param cost The facility cost.
 */
void facility_handle_fclt(facility_t facility,double cost);

/**
 * Handles the fn command for a facility.
 * param facility The facility.
 * param name The facility name.
 */
void facility_handle_fn(facility_t facility,const char *name);
#endif