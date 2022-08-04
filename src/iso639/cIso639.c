#include "iso639/cIso639.h"

#include "clingo/lang/algo.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 
*******************************************************************************/

SLICE_IMPL_C_(
   cIso639,             // Type
   cIso639Slice,        // SliceType
   iso639_slice_c,      // FuncName
   cVarIso639Slice,     // VarSliceType
   var_iso639_slice_c   // VarFuncName
)

SLICE_IMPL_C_(
   cIso639Info,            // Type
   cIso639InfoSlice,       // SliceType
   iso639_info_slice_c,    // FuncName
   cVarIso639InfoSlice,    // VarSliceType
   var_iso639_info_slice_c // VarFuncName
)

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/

int cmp_iso639_c( cIso639 a, cIso639 b )
{
   int res = 0;
   for ( int i = 0; i < 4 and res == 0; ++i )
   {
      res = cmp_char_c( a.code[i], b.code[i] );
      if ( res != 0 ) return res;
   }
   return res;
}

cIso639 iso639_c( cChars val )
{
   cIso639 res = (cIso639){0};
   for ( int64_t i = 0; i < val.s and i < 3; ++i )
   {
      res.code[i] = val.v[i];
   }
   return res;
}

static inline BSEARCH_C_(
   bsearch_iso639_c, // FuncName
   cIso639Slice,     // SliceType
   cIso639 const,    // ValueType
   cIso639,          // SearchType
   cmp_iso639_c,     // CmpFunc
   do_deref_c_       // DoDeref
)

bool is_iso639_alpha2_c( cIso639 val )
{
   return bsearch_iso639_c( C_Iso639Alpha2Values, val ) != NULL;
}

bool is_iso639_bib_c( cIso639 val )
{
   return bsearch_iso639_c( C_Iso639BibValues, val ) != NULL;
}

bool is_iso639_ter_c( cIso639 val )
{
   return bsearch_iso639_c( C_Iso639TerValues, val ) != NULL;
}

/*******************************************************************************

*******************************************************************************/

static inline bool cmp_func( cIso639Info const* info, cIso639 val )
{
   if ( cmp_iso639_c( info->alpha2, val ) == 0 ) return 0;
   if ( cmp_iso639_c( info->bib, val ) == 0 ) return 0;
   if ( cmp_iso639_c( info->ter, val ) == 0 ) return 0;

   return -1;
}

FIND_VAL_C_(
   find_iso639_info_c,  // FuncName
   cIso639InfoSlice,    // SliceType
   cIso639Info const,   // ValueType
   cIso639,             // SearchType
   cmp_func,            // CmpFunc
   do_not_deref_c_      // DoDeref
)

cIso639Info const* select_iso639_info_c( cIso639 val )
{
  return find_iso639_info_c( C_Iso639InfoValues, val );
}
