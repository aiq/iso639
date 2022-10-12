#ifndef ISO639_CISO639_H
#define ISO639_CISO639_H

#include "iso639/apidecl.h"
#include "clingo/type/cChars.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 
*******************************************************************************/

struct cIso639
{
   char code[4];
};
typedef struct cIso639 cIso639;

struct cIso639Info
{
   cIso639 alpha2;
   cIso639 bib;
   cIso639 ter;
   cChars name;
};
typedef struct cIso639Info cIso639Info;

/*******************************************************************************
 generated
*******************************************************************************/

SLICES_C_(
   cIso639,          // Type
   cIso639Slice,     // SliceType
   cVarIso639Slice   // VarSliceType
)

SLICES_C_(
   cIso639Info,         // Type
   cIso639InfoSlice,    // SliceType
   cVarIso639InfoSlice  // VarSliceType
)

/*******************************************************************************

*******************************************************************************/

ISO639_API extern cIso639InfoSlice const C_Iso639InfoValues;

ISO639_API extern cIso639Slice const C_Iso639Alpha2Values;

ISO639_API extern cIso639Slice const C_Iso639BibValues;

ISO639_API extern cIso639Slice const C_Iso639TerValues;

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/

ISO639_API int cmp_iso639_c( cIso639 a, cIso639 b );

#define iso639_c_( Code )                                                      \
   iso639_c( c_c( Code ) )
ISO639_API cIso639 iso639_c( cChars code );

ISO639_API bool is_iso639_alpha2_c( cIso639 val );

ISO639_API bool is_iso639_bib_c( cIso639 val );

ISO639_API bool is_iso639_ter_c( cIso639 val );

/*******************************************************************************

*******************************************************************************/

ISO639_API cIso639Info const* find_iso639_info_c( cIso639InfoSlice slice,
                                                  cIso639 val );

ISO639_API cIso639Info const* select_iso639_info_c( cIso639 val );

#endif
