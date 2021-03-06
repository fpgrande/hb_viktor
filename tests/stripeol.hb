#!/usr/bin/env hbmk2

/* Copyright 2013 Viktor Szakats */

/* Strips leading EOLs from source files */

#pragma -w3
#pragma -km+
#pragma -ko+

#include "directry.ch"

PROCEDURE Main()

   LOCAL aFile
   LOCAL eol
   LOCAL tmp, tmp1

   FOR EACH aFile IN hb_DirScan( ".", hb_osFileMask() )
      IF "|" + hb_FNameExt( aFile[ F_NAME ] ) + "|" $ "||.c|.h|.hb|.prg|.hbm|.hbp|.hbc|.ini|.bat|.sh|.vbs|.def|.api|.ch|.txt|.mk|"

         tmp := tmp1 := hb_MemoRead( aFile[ F_NAME ] )

         FOR EACH eol IN { Chr( 13 ) + Chr( 10 ), Chr( 10 ) }
            DO WHILE hb_LeftEq( tmp, eol )
               tmp := SubStr( tmp, Len( eol ) + 1 )
            ENDDO
         NEXT

         IF ! tmp == tmp1
            ? "saved", aFile[ F_NAME ], Len( tmp1 ) - Len( tmp )
            hb_MemoWrit( aFile[ F_NAME ], tmp )
         ENDIF
      ENDIF
   NEXT

   RETURN
