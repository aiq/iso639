#include "clingo/io/print.h"
#include "iso639/cIso639.h"

static void println_header( void )
{
   println_c_( "   # | bib | ter | a2 | name" );
   println_c_( "-----+-----+-----+----+-------" );
}

static void print_info_row( int64_t row, cIso639Info const* info )
{
   print_c_( " {i64:(3r )} |", row );
   print_c_( " {s} |", info->bib.code );
   cmp_iso639_c( info->bib, info->ter ) == 0
      ? print_c_( "     |" )
      : print_c_( " {s} |", info->ter.code );
   info->alpha2.code[0] == '\0'
      ? print_c_( "    |" )
      : print_c_( " {s} |", info->alpha2.code );
   print_c_( " {cs}", info->name );
}

int main( int argc, char* argv[] )
{
   if ( argc < 2 )
   {
      println_header();
      int64_t row = 1;
      for_each_c_( cIso639Info const*, info, C_Iso639InfoValues )
      {
         print_info_row( row, info );
         println_c_( "" );
         ++row;
      }
      return EXIT_SUCCESS;
   }

   println_header();
   for ( int i = 1; i < argc; ++i )
   {
      char const* inp = argv[i];
      cIso639 val = iso639_c_( inp );
      cIso639Info const* info = select_iso639_info_c( val );
      if ( info == NULL )
      {
         println_c_( " ---- unknown ISO 639 Alpha-2 or Alpha-3 code {s:Q}", inp );
         continue;
      }
      print_info_row( i, info );
      println_c_( " < {s}", inp );
   }
}
