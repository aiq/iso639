#include "iso639/cIso639p1.h"

#include "clingo/lang/algo.h"
#include "clingo/type/uint32.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 
*******************************************************************************/

SLICE_IMPL_C_(
   cIso639p1,           // Type
   cIso639p1Slice,      // SliceType
   iso639p1_slice_c,    // FuncName
   cVarIso639p1Slice,   // VarSliceType
   var_iso639p1_slice_c // VarFuncName
)

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/

int cmp_iso639p1_c( cIso639p1 a, cIso639p1 b )
{
   int res = 0;
   for ( int i = 0; i < 4 and res == 0; ++i )
   {
      res = cmp_char_c( a.code[i], b.code[i] );
   }
   return res;
}

cIso639p1 iso639p1_c( cChars val )
{
   cIso639p1 res = (cIso639p1){0};
   for ( int64_t i = 0; i < val.s and i < 2; ++i )
   {
      res.code[i] = val.v[i];
   }
   return res;
}

static inline BSEARCH_C_(
   bsearch_iso639p1_c,  // FuncName
   cIso639p1Slice,      // SliceType
   cIso639p1 const,     // ValueType
   cIso639p1,           // SearchType
   cmp_iso639p1_c,      // CmpFunc
   do_deref_c_          // DoDeref
)

bool is_iso639p1_c( cIso639p1 val )
{
   return bsearch_iso639p1_c( C_Iso639p1Values, val ) != NULL;
}
