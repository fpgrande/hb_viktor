/*
 * __win_ProxyDetect()
 *
 * Copyright 2015 Viktor Szakats (vszakats.net/harbour)
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
 * along with this software; see the file COPYING.txt.  If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 * Boston, MA 02111-1307 USA (or visit the web site https://www.gnu.org/).
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

#include "hbwapi.h"

#undef HBWIN_HAS_WINHTTP
#if ! defined( HB_OS_WIN_CE ) && \
    !( defined( __BORLANDC__ ) && __BORLANDC__ < 1410 ) && \
    ! defined( __WATCOMC__ ) && \
    ! defined( __TINYC__ )
   #define HBWIN_HAS_WINHTTP
#endif

#if defined( HBWIN_HAS_WINHTTP )
   #include "winhttp.h"
#endif

HB_FUNC( __WIN_PROXYDETECT )
{
#if defined( HBWIN_HAS_WINHTTP )
   typedef HINTERNET ( WINAPI * _HB_WINHTTPOPEN )( LPCWSTR, DWORD, LPCWSTR, LPCWSTR, DWORD );
   typedef BOOL      ( WINAPI * _HB_WINHTTPSETTIMEOUTS )( HINTERNET, int, int, int, int );
   typedef BOOL      ( WINAPI * _HB_WINHTTPCLOSEHANDLE )( HINTERNET );
   typedef BOOL      ( WINAPI * _HB_WINHTTPGETPROXYFORURL )( HINTERNET, LPCWSTR, WINHTTP_AUTOPROXY_OPTIONS *, WINHTTP_PROXY_INFO * );
   typedef BOOL      ( WINAPI * _HB_WINHTTPGETIEPROXYCONFIGFORCURRENTUSER )( WINHTTP_CURRENT_USER_IE_PROXY_CONFIG * );

   static _HB_WINHTTPOPEN                           s_pWinHttpOpen = NULL;
   static _HB_WINHTTPSETTIMEOUTS                    s_pWinHttpSetTimeouts = NULL;
   static _HB_WINHTTPCLOSEHANDLE                    s_pWinHttpCloseHandle = NULL;
   static _HB_WINHTTPGETPROXYFORURL                 s_pWinHttpGetProxyForUrl = NULL;
   static _HB_WINHTTPGETIEPROXYCONFIGFORCURRENTUSER s_pWinHttpGetIEProxyConfigForCurrentUser = NULL;

   if( ! s_pWinHttpOpen )
   {
      HMODULE hModule = hbwapi_LoadLibrarySystem( TEXT( "winhttp.dll" ) );
      if( hModule )
      {
         s_pWinHttpOpen                           = ( _HB_WINHTTPOPEN )                           HB_WINAPI_GETPROCADDRESS( hModule, "WinHttpOpen" );
         s_pWinHttpSetTimeouts                    = ( _HB_WINHTTPSETTIMEOUTS )                    HB_WINAPI_GETPROCADDRESS( hModule, "WinHttpSetTimeouts" );
         s_pWinHttpCloseHandle                    = ( _HB_WINHTTPCLOSEHANDLE )                    HB_WINAPI_GETPROCADDRESS( hModule, "WinHttpCloseHandle" );
         s_pWinHttpGetProxyForUrl                 = ( _HB_WINHTTPGETPROXYFORURL )                 HB_WINAPI_GETPROCADDRESS( hModule, "WinHttpGetProxyForUrl" );
         s_pWinHttpGetIEProxyConfigForCurrentUser = ( _HB_WINHTTPGETIEPROXYCONFIGFORCURRENTUSER ) HB_WINAPI_GETPROCADDRESS( hModule, "WinHttpGetIEProxyConfigForCurrentUser" );
      }
   }

   if( s_pWinHttpOpen != NULL &&
       s_pWinHttpSetTimeouts != NULL &&
       s_pWinHttpCloseHandle != NULL &&
       s_pWinHttpGetProxyForUrl != NULL &&
       s_pWinHttpGetIEProxyConfigForCurrentUser != NULL )
   {
      WINHTTP_AUTOPROXY_OPTIONS options;
      WINHTTP_CURRENT_USER_IE_PROXY_CONFIG ieproxy;

      BOOL fDetect = TRUE;

      memset( &options, 0, sizeof( options ) );
      memset( &ieproxy, 0, sizeof( ieproxy ) );

      if( s_pWinHttpGetIEProxyConfigForCurrentUser( &ieproxy ) )
      {
         if( ieproxy.lpszAutoConfigUrl != NULL )
            options.lpszAutoConfigUrl = ieproxy.lpszAutoConfigUrl;
         else
            fDetect = ieproxy.fAutoDetect;
      }

      if( fDetect )
      {
         HINTERNET hSession =
            s_pWinHttpOpen( NULL,
               WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
               WINHTTP_NO_PROXY_NAME,
               WINHTTP_NO_PROXY_BYPASS,
               0 );

         if( hSession != NULL )
         {
            WINHTTP_PROXY_INFO proxy;

            void * hURL;
            LPCTSTR pURL = HB_PARSTRDEF( 1, &hURL, NULL );
            DWORD dwError;

            memset( &proxy, 0, sizeof( proxy ) );

            if( options.lpszAutoConfigUrl != NULL )
               options.dwFlags = WINHTTP_AUTOPROXY_CONFIG_URL;
            else
            {
               options.dwFlags = WINHTTP_AUTOPROXY_AUTO_DETECT;
               options.dwAutoDetectFlags = WINHTTP_AUTO_DETECT_TYPE_DNS_A;
               #if 0
               /* This flag has issues, according to Chromium code. */
               options.dwAutoDetectFlags |= WINHTTP_AUTO_DETECT_TYPE_DHCP;
               #endif
            }

            ( void ) s_pWinHttpSetTimeouts( hSession, 10000, 10000, 5000, 5000 );

            fDetect = s_pWinHttpGetProxyForUrl( hSession, pURL, &options, &proxy );
            hbwapi_SetLastError( dwError = GetLastError() );

            if( ! fDetect && dwError == ERROR_WINHTTP_LOGIN_FAILURE )
            {
               options.fAutoLogonIfChallenged = TRUE;

               fDetect = s_pWinHttpGetProxyForUrl( hSession, pURL, &options, &proxy );
               hbwapi_SetLastError( GetLastError() );
            }

            if( fDetect )
            {
               if( proxy.dwAccessType == WINHTTP_ACCESS_TYPE_NO_PROXY )
               {
                  hb_retc_null();
                  hb_storc( NULL, 2 );
               }
               else
               {
                  HB_RETSTR( proxy.lpszProxy );
                  HB_STORSTR( proxy.lpszProxyBypass, 2 );
               }
            }
            else
               fDetect = FALSE;

            if( proxy.lpszProxy != NULL )
               GlobalFree( proxy.lpszProxy );
            if( proxy.lpszProxyBypass != NULL )
               GlobalFree( proxy.lpszProxyBypass );

            hb_strfree( hURL );

            s_pWinHttpCloseHandle( hSession );
         }
         else
            fDetect = FALSE;
      }

      if( ! fDetect )
      {
         hbwapi_SetLastError( GetLastError() );
         HB_RETSTR( ieproxy.lpszProxy );
         HB_STORSTR( ieproxy.lpszProxyBypass, 2 );
      }

      if( ieproxy.lpszAutoConfigUrl != NULL )
         GlobalFree( ieproxy.lpszAutoConfigUrl );
      if( ieproxy.lpszProxy != NULL )
         GlobalFree( ieproxy.lpszProxy );
      if( ieproxy.lpszProxyBypass != NULL )
         GlobalFree( ieproxy.lpszProxyBypass );
   }
   else
   {
      hbwapi_SetLastError( ERROR_NOT_SUPPORTED );
      hb_retc_null();
      hb_storc( NULL, 2 );
   }
#elif defined( HB_OS_WIN_CE )
   /* TODO: Proxy detection for WinCE */
   hbwapi_SetLastError( ERROR_NOT_SUPPORTED );
   hb_retc_null();
   hb_storc( NULL, 2 );
#else
   hbwapi_SetLastError( ERROR_NOT_SUPPORTED );
   hb_retc_null();
   hb_storc( NULL, 2 );
#endif
}