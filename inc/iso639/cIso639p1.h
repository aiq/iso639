#ifndef ISO639_CISO639P1_H
#define ISO639_CISO639P1_H

#include "clingo/type/cChars.h"
#include "iso639/apidecl.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 
*******************************************************************************/

union cIso639p1
{
   uint32_t ctrl;
   char code[4];
};
typedef union cIso639p1 cIso639p1;

/*******************************************************************************
 generated
*******************************************************************************/

SLICE_DEF_C_(
   cIso639p1,           // Type
   cIso639p1Slice,      // SliceType
   iso639p1_slice_c,    // FuncName
   cVarIso639p1Slice,   // VarSliceType
   var_iso639p1_slice_c // VarFuncName
)

/*******************************************************************************

*******************************************************************************/

ISO639_API extern cIso639p1Slice const C_Iso639p1Values;

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/

#define build_iso639p1_c_( A, B )                                              \
(                                                                              \
   (cIso639p1){ .code={ (A), (B), '\0', '\0' } }                               \
)

#define iso639p1_c_( Code )                                                    \
   iso639p1_c( c_c( Code ) )
ISO639_API cIso639p1 iso639p1_c( cChars code );

ISO639_API bool is_iso639p1_c( cIso639p1 val );

#endif