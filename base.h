/** 
 * file base.h
 */
#ifndef BASE_H
#define BASE_H
#include "facility.h" /*for facility_t*/
/**
 * A base.
 */
typedef struct{
    char *country; /**< The base location (country).*/
    int day; /**< The base date (day).*/
    facility_t **facilities; /**< The base facilities.*/
    int month; /**< The base date (month).*/
    char *name; /**< The base name.*/
    int nfacilities; /**< The base number of facilities.*/
    int year; /**< The base date (year).*/
} base_t;

/**
 * Adds a facility to a base.
 * param base The base.
 * param facility The facility.
 * return -1 on error (i.e., if the memory allocation is a failure), else 0.
 */
int base_add_facility(base_t *base, facility_t *facility);

/**
 * Creates a base.
 * return NULL on error (i.e., if the memory allocation is a failure), else a base.
 */
base_t *base_create();

/**
 * Frees a base.
 * param base The base.
 */
void base_free(base_t *base);

/**
 * Handles the b command for a base.
 * param base The base.
 */
void base_handle_b(base_t base);

/**
 * Handles the c command for a base.
 * param base The base.
 */
void base_handle_c(base_t base);

/**
 * Handles the d command for a base.
 * param base The base.
 */
void base_handle_d(base_t base);

/**
 * Handles the f command for a base.
 * param base The base.
 */
void base_handle_f(base_t base);

/**
 * Handles the fc command for all the facilities of a base.
 * param base The base.
 * param cost The facility cost.
 */
void base_handle_fc(base_t base,double cost);

/**
 * Handles the fcge command for all the facilities of a base.
 * param base The base.
 * param cost The facility cost.
 */
void base_handle_fcge(base_t base,double cost);

/**
 * Handles the fcgt command for all the facilities of a base.
 * param base The base.
 * param cost The facility cost.
 */
void base_handle_fcgt(base_t base,double cost);

/**
 * Handles the fcle command for all the facilities of a base.
 * param base The base.
 * param cost The facility cost.
 */
void base_handle_fcle(base_t base,double cost);

/**
 * Handles the fclt command for all the facilities of a base.
 * param base The base.
 * param cost The facility cost.
 */
void base_handle_fclt(base_t base,double cost);

/**
 * Handles the fn command for all the facilities of a base.
 * param base The base.
 * param cost The facility name.
 */
void base_handle_fn(base_t base,const char* name);

/**
 * Handles the n command for a base.
 * param base The base.
 */
void base_handle_n(base_t base);

/**
 * Handles the t command for a base.
 * param base The base.
 */
void base_handle_t(base_t base); 

#endif