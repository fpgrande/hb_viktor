/*
 * Ghostscript high-level API
 *
 * Copyright 2011 Viktor Szakats
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file LICENSE.txt.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA (or visit https://www.gnu.org/licenses/).
 *
 * As a special exception, the Harbour Project gives permission for
 * additional uses of the text contained in its release of Harbour.
 *
 * The exception is that, if you link the Harbour libraries with other
 * files to produce an executable, this does not by itself cause the
 * resulting executable to be covered by the GNU General Public License.
 * Your use of that executable is in no way restricted on account of
 * linking the Harbour library code into it.
 *
 * This exception does not however invalidate any other reasons why
 * the executable file might be covered by the GNU General Public License.
 *
 * This exception applies only to the code released by the Harbour
 * Project under the name Harbour.  If you copy code from other
 * Harbour Project or Free Software Foundation releases into a copy of
 * Harbour, as the General Public License permits, the exception does
 * not apply to the code that you add in this way.  To avoid misleading
 * anyone as to the status of such modified files, you must delete
 * this exception notice from them.
 *
 * If you write modifications of your own for Harbour, it is your choice
 * whether to permit this exception to apply to your modifications.
 * If you do not wish that, delete this exception notice.
 *
 */

/* #define HB_GS_UTF8_SUPPORT */  /* requires Ghostscript 9.10 or upper */

#include "hbapi.h"
#if defined( HB_GS_UTF8_SUPPORT )
#  include "hbapistr.h"
#endif

#if defined( HB_OS_WIN )
#  if ! defined( _Windows )
#     define _Windows
#  endif
#  include <windows.h>
#  define GSDLLEXPORT  __declspec( dllimport )
#  define GSDLLAPI  /* Some binary builds may need this to be commented */
#endif

#include "ierrors.h"
#include "iapi.h"

/* Workaround to build with pre-9.18 versions */
#if defined( e_Quit )
#  define gs_error_Quit  e_Quit
#endif

HB_FUNC( HB_GS )
{
   HB_BOOL  bResult = HB_FALSE;
   PHB_ITEM pParam  = hb_param( 1, HB_IT_ARRAY );

   if( pParam )
   {
      void *  minst;
      int     pos;
      int     gsargc = ( int ) hb_arrayLen( pParam ) + 1;
      char ** gsargv = ( char ** ) hb_xgrab( gsargc * sizeof( const char * ) );
      #if defined( HB_GS_UTF8_SUPPORT )
      void ** gsargf = ( void ** ) hb_xgrab( gsargc * sizeof( void * ) );
      #endif

      gsargv[ 0 ] = ( char * ) "hbgs";  /* actual value doesn't matter */

      for( pos = 1; pos < gsargc; ++pos )
      {
         const char * pszParam;
         #if defined( HB_GS_UTF8_SUPPORT )
         gsargf[ pos ] = NULL;
         pszParam = hb_arrayGetStrUTF8( pParam, pos, &gsargf[ pos ], NULL );
         #else
         pszParam = hb_arrayGetCPtr( pParam, pos );
         #endif
         gsargv[ pos ] = ( char * ) HB_UNCONST( pszParam ? pszParam : "" );
      }

      if( gsapi_new_instance( &minst, NULL ) >= 0 )
      {
         int code, code1;

         #if defined( HB_GS_UTF8_SUPPORT )
         gsapi_set_arg_encoding( minst, GS_ARG_ENCODING_UTF8 );
         #endif

         code  = gsapi_init_with_args( minst, gsargc, gsargv );
         code1 = gsapi_exit( minst );

         if( code == 0 || code == gs_error_Quit )
            code = code1;

         gsapi_delete_instance( minst );

         bResult = ( code == 0 || code == gs_error_Quit );
      }

      #if defined( HB_GS_UTF8_SUPPORT )
      for( pos = 1; pos < gsargc; ++pos )
         hb_strfree( gsargf[ pos ] );
      #endif

      hb_xfree( gsargv );
      #if defined( HB_GS_UTF8_SUPPORT )
      hb_xfree( gsargf );
      #endif
   }

   hb_retl( bResult );
}

HB_FUNC( HB_GSAPI_REVISION )
{
   gsapi_revision_t r;
   int result = gsapi_revision( &r, sizeof( r ) );

   if( result == 0 )
   {
      hb_storc( r.product, 1 );
      hb_storc( r.copyright, 2 );
      hb_stornl( r.revision, 3 );
      hb_stornl( r.revisiondate, 4 );
   }
   else
   {
      hb_storc( NULL, 1 );
      hb_storc( NULL, 2 );
      hb_stornl( 0, 3 );
      hb_stornl( 0, 4 );
   }

   hb_retni( result );
}
