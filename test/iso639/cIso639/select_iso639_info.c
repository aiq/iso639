#include "clingo/lang/expect.h"
#include "iso639/cIso639.h"

TEMP_SLICE_DEF_C_(
   test,
   {
      char const* inp;
      char const* expBib;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
      t_( "aa", "aar" )
   );

   for_each_c_( test const*, t, tests )
   {
      cIso639 val = iso639_c_( t->inp );
      cIso639Info const* info = select_iso639_info_c( val );
      require_c_( info != NULL );

      int res = cmp_iso639_c( info->bib, iso639_c_( t->expBib ) );
      tap_descf_c( res == 0, "test: %s gets %s", t->inp, info->bib.code );
   }

   return finish_tap_c_();
}
