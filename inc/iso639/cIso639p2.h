#ifndef ISO639_CISO639P2_H
#define ISO639_CISO639P2_H

#include "clingo/type/cChars.h"
#include "iso639/apidecl.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 
*******************************************************************************/

union cIso639p2
{
   uint32_t ctrl;
   char code[4];
};
typedef union cIso639p2 cIso639p2;

/*******************************************************************************
 generated
*******************************************************************************/

SLICE_DEF_C_(
   cIso639p2,           // Type
   cIso639p2Slice,      // SliceType
   iso639p2_slice_c,    // FuncName
   cVarIso639p2Slice,   // VarSliceType
   var_iso639p2_slice_c // VarFuncName
)

/*******************************************************************************

*******************************************************************************/

ISO639_API extern cIso639p2Slice const C_Iso639p2BibValues;

ISO639_API extern cIso639p2Slice const C_Iso639p2TerValues;

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/

#define build_iso639p2_c_( A, B, C )                                           \
(                                                                              \
   (cIso639p2){ .code={ (A), (B), (C), '\0' } }                                \
)

ISO639_API int cmp_iso639p2_c( cIso639p2 a, cIso639p2 b );

#define iso639p2_c_( Code )                                                    \
   iso639p2_c( c_c( Code ) )
ISO639_API cIso639p2 iso639p2_c( cChars code );

ISO639_API bool is_bib_iso639p2_c( cIso639p2 val );

ISO639_API bool is_ter_iso639p2_c( cIso639p2 val );

#endif