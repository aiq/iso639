#include "clingo/lang/expect.h"
#include "iso639/cIso639p2.h"

TEMP_SLICE_DEF_C_(
   test,
   {
      char const* inp;
      bool exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
      t_( "aar", true ),
      t_( "arm", false ),
      t_( "hye", true ),
      t_( "zza", true )
   );

   for_each_c_( test const*, t, tests )
   {
      cIso639p2 val = iso639p2_c_( t->inp );
      bool res = is_ter_iso639p2_c( val );

      tap_descf_c( res == t->exp, "test: %s", val.code );
   }

   return finish_tap_c_();
}
