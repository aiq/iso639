#include "iso639/cIso639p2.h"

#include "clingo/lang/algo.h"
#include "clingo/type/uint32.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 
*******************************************************************************/

SLICE_IMPL_C_(
   cIso639p2,           // Type
   cIso639p2Slice,      // SliceType
   iso639p2_slice_c,    // FuncName
   cVarIso639p2Slice,   // VarSliceType
   var_iso639p2_slice_c // VarFuncName
)

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/

int cmp_iso639p2_c( cIso639p2 a, cIso639p2 b )
{
   int res = 0;
   for ( int i = 0; i < 4 and res == 0; ++i )
   {
      res = cmp_char_c( a.code[i], b.code[i] );
   }
   return res;
}

cIso639p2 iso639p2_c( cChars val )
{
   cIso639p2 res = (cIso639p2){0};
   for ( int64_t i = 0; i < val.s and i < 3; ++i )
   {
      res.code[i] = val.v[i];
   }
   return res;
}

static inline BSEARCH_C_(
   bsearch_iso639p2_c,  // FuncName
   cIso639p2Slice,      // SliceType
   cIso639p2 const,     // ValueType
   cIso639p2,           // SearchType
   cmp_iso639p2_c,      // CmpFunc
   do_deref_c_          // DoDeref
)

bool is_bib_iso639p2_c( cIso639p2 val )
{
   return bsearch_iso639p2_c( C_Iso639p2BibValues, val ) != NULL;
}

bool is_ter_iso639p2_c( cIso639p2 val )
{
   return bsearch_iso639p2_c( C_Iso639p2TerValues, val ) != NULL;
}