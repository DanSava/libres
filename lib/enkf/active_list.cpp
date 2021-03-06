/*
   Copyright (C) 2011  Equinor ASA, Norway.

   The file 'active_list.c' is part of ERT - Ensemble based Reservoir Tool.

   ERT is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   ERT is distributed in the hope that it will be useful, but WITHOUT ANY
   WARRANTY; without even the implied warranty of MERCHANTABILITY or
   FITNESS FOR A PARTICULAR PURPOSE.

   See the GNU General Public License at <http://www.gnu.org/licenses/gpl.html>
   for more details.
*/

#include <stdlib.h>

#include <ert/util/util.h>
#include <ert/util/int_vector.hpp>

#include <ert/enkf/enkf_macros.hpp>
#include <ert/enkf/active_list.hpp>
#include <ert/enkf/local_config.hpp>


/**
   This file implements a small structure used to denote which
   elements of a node/observation which is active. At the lowest level
   the active elements in a node is just a list of integers. This
   list of integers, with som extra twists is what is implemented
   here.

   All the xxx_config objects have a pointer to an active_list
   instance. This pointer is passed to the enkf_serialize /
   enkf_deserialize routines.

   Observe that for the (very important!!) special case that all
   elements are active the (int *) pointer should not be accessed, and
   the code here is free to return NULL.


Example
-------

Consider a situation where faults number 0,4 and 5 should be active in
a fault object. Then the code will be like:


   ....
   active_list_add_index(multflt_config->active_list , 0);
   active_list_add_index(multflt_config->active_list , 4);
   active_list_add_index(multflt_config->active_list , 5);
   ....

   When this fault object is serialized/deserialized only the elements
   0,4,5 are updated.
*/


#define ACTIVE_LIST_TYPE_ID 66109

struct active_list_struct {
  UTIL_TYPE_ID_DECLARATION;
  active_mode_type  mode;           /* ALL_ACTIVE | INACTIVE | PARTLY_ACTIVE */
  int_vector_type  *index_list;     /* A list of active indices - if data_size == active_size this can be NULL. */
};

/*****************************************************************/


static UTIL_SAFE_CAST_FUNCTION(active_list , ACTIVE_LIST_TYPE_ID)
UTIL_IS_INSTANCE_FUNCTION( active_list , ACTIVE_LIST_TYPE_ID)




/**
   The newly created active_list default to setting all indices actiove.
*/
active_list_type * active_list_alloc( ) {
  active_list_type * active_list = (active_list_type *)util_malloc(sizeof * active_list);
  UTIL_TYPE_ID_INIT( active_list , ACTIVE_LIST_TYPE_ID );
  active_list->index_list  = int_vector_alloc(0 , -1);
  active_list->mode        = ALL_ACTIVE;
  return active_list;
}


active_list_type * active_list_alloc_copy( const active_list_type * src) {
  active_list_type * new_list = active_list_alloc(  );
  new_list->mode  = src->mode;
  int_vector_free( new_list->index_list ) ;
  new_list->index_list = int_vector_alloc_copy( src->index_list ); // CXX_CAST_ERROR
  return new_list;
}


void active_list_copy( active_list_type * target , const active_list_type * src) {
  target->mode = src->mode;
  int_vector_memcpy( target->index_list , src->index_list);
}


void active_list_free( active_list_type * active_list ) {
  int_vector_free(active_list->index_list);
  free(active_list);
}



void active_list_free__( void * arg ) {
  active_list_type * active_list = active_list_safe_cast ( arg );
  active_list_free(active_list);
}



/**
   Appends a new index to the current list of active indices, and
   setting the mode to PARTLY_ACTIVE.
*/
void active_list_add_index(active_list_type * active_list, int new_index) {
  if (int_vector_contains(active_list->index_list , new_index ))
    return;
  active_list->mode = PARTLY_ACTIVE;
  int_vector_append( active_list->index_list , new_index );
}








/**
   When mode == PARTLY_ACTIVE the active_list instance knows the size
   of the active set; if the mode is INACTIVE 0 will be returned and
   if the mode is ALL_ACTIVE the input parameter @total_size will be
   passed back to calling scope.
*/


int active_list_get_active_size(const active_list_type * active_list, int total_size) {
  int active_size;
  switch( active_list->mode ) {
  case PARTLY_ACTIVE:
    active_size = int_vector_size( active_list->index_list );
    break;
  case INACTIVE:
    active_size = 0;
    break;
  case ALL_ACTIVE:
    active_size = total_size;
    break;
  default:
    util_abort("%s: internal fuckup \n",__func__);
    active_size = -1;
  }
  return active_size;
}


active_mode_type active_list_get_mode(const active_list_type * active_list) {
  return active_list->mode;
}



/**
   This will return a (const int *) pointer to the active indices. IFF
   (mode == INACTIVE || mode == ALL_ACTIVE) it will instead just
   return NULL. In that case it is the responsability of the calling
   scope to not dereference the NULL pointer.
*/

const int * active_list_get_active(const active_list_type * active_list) {
  if (active_list->mode == PARTLY_ACTIVE)
    return int_vector_get_const_ptr( active_list->index_list );
  else
    return NULL;
}


bool active_list_iget( const active_list_type * active_list , int index ) {
  if (active_list->mode == ALL_ACTIVE)
    return true;
  else if (active_list->mode == INACTIVE)
    return false;
  else
    return int_vector_iget( active_list->index_list , index );
}

void active_list_summary_fprintf( const active_list_type * active_list , const char *dataset_key, const char *key , FILE * stream) {
  int number_of_active = int_vector_size( active_list->index_list );
  if (active_list->mode == ALL_ACTIVE){
    fprintf(stream , "NUMBER OF ACTIVE:%d,STATUS:%s,", number_of_active, "ALL_ACTIVE");
  }
  else if (active_list->mode == PARTLY_ACTIVE){
    fprintf(stream , "NUMBER OF ACTIVE:%d,STATUS:%s,", number_of_active, "PARTLY_ACTIVE");
  }
  else
    fprintf(stream , "NUMBER OF ACTIVE:%d,STATUS:%s,", number_of_active, "INACTIVE");
}



bool active_list_equal( const active_list_type * active_list1 , const active_list_type * active_list2) {
  if (active_list1 == active_list2)
    return true;
  else {
    if (active_list1->mode != active_list2->mode)
      return false;
    else {
      if (active_list1->mode == PARTLY_ACTIVE)
        return int_vector_equal( active_list1->index_list , active_list2->index_list);
      else
        return true;
    }
  }
}
