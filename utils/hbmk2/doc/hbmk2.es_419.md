Harbour Make \(hbmk2\) 3.4.0dev \(c390da90ad\) \(2017-10-10 16:11\)  
Copyright &copy; 1999-present, Viktor Szakats  
<https://github.com/vszakats/hb/>  
Traducción \(es\_419\): Guillermo Varona Silupú &lt;gvaronas@gmail.com&gt;  

Sintáxis:  
  
  hbmk2 \[options\] \[&lt;script\[s\]&gt;\] &lt;src\[s\]\[.prg|.hbc|.c|.obj|.o|.rc|.res|.def|.po|.pot|.hbl|@.clp|.d|.ch\]&gt;  
  
Descripción:  


  hbmk2 is an integrated and portable build tool, making it possible to create various types of executable binaries \(executable, dynamic library, static library, Harbour portable binary\) out of multiple types of source files \(C, C\+\+, Objective-C, Harbour, gettext translations, Windows resources\). 'Integrated' means that a single hbmk2 project file can control all or most aspects of the build process. 'Portable' means that a single hbmk2 project file can control the build on all supported OS platforms and across all supported C compilers. It also aims to cover the majority of build tasks via short and simple project files \(options\). hbmk2 supports pure -non-Harbour- C/C\+\+/Objective-C projects as well. In order to achieve above goals, hbmk2 will auto-detect Harbour, C compiler and other required tools, then configure and call them appropriately. hbmk2 allows to extend the types of supported source files via plugins.  
Besides building executables, hbmk2 is able to run Harbour scripts \(both source and precompiled\) directly, and it also features an interactive shell prompt.
  
Opciones:  


 - **-o&lt;outname&gt;** nombre de archivo de salida
 - **-l&lt;libname&gt;** enlaza con biblioteca &lt;libname&gt;. &lt;libname&gt; no debe incluir ruta, extensión o prefijo 'lib' \(excepto que sea parte del nombre\). No agregue bibliotecas principales de Harbour, estas son agregadas automáticamente cuando se necesitan. Si &lt;libname&gt; comienza con un caracter '-', la biblioteca será removida de la lista de bibliotecas principales al momento de enlazar.
 - **-L&lt;libpath&gt;** ruta adicional para buscar librerías
 - **-i&lt;p&gt;|-incpath=&lt;p&gt;** ruta adicional para buscar cabeceras
 - **-static|-shared** enlazar con librerías estáticas/compartidas
 - **-gt&lt;name&gt;** enlaza con el driver GT GT&lt;name&gt;, puede repetirse para enlazar con mas GTs. El primero será utilzado por defecto en tiempo de ejecución
 - **-inc\[-\]** habilita modo de compilación incremental
 - **-hbexe** crea ejecutable \(por defecto\)
 - **-hblib** crear librería estática
 - **-hbdyn** crea biblioteca dinámica \(sin enlace a Harbour VM\)
 - **-hbdynvm** crear librería dinámica \(con enlace a Harbour VM\)
 - **-strip\[-\]** strip \(or don't\) debugging \(and other extra\) information from target binary. They are included by default by certain C compilers, e.g.: gcc\*, clang\*, mingw\*, djgpp.


 - **-mt|-st** enlazar con soporte multi/single-thread Harbour VM
 - **-gui|-std|-cli** create GUI/console/command-line executable
 - **-main=&lt;mainfunc&gt;** reemplaza nombre de función/procedimento inicial
 - **-request=&lt;func&gt;** fuerza función/procedimiento a enlazarse
 - **-fullstatic** enlazar con todas las librerías estáticas
 - **-pic\[-\]** crear código objeto independiente de la posición \(siempre activado en los modos -hbdyn/-hbdynvm\)
 - **-\[full|fix\]shared** crear para compartir archivos binarios Harbour sin/con referencia absoluta a librerías de Harbour \(por defecto: 'fullshared' cuando Harbour se instala en ubicación del sistema, 'fixshared' en otro caso\) \(opción fix/full en \*nix solamente\)
 - **-nulrdd\[-\]** enlazar con nulrdd
 - **-debug\[-\]** adicionar/excluir información de debug de compilador C. Para activar el debug de Harbour utilize la Opción -b como de costumbre.
 - **-optim\[-\]** alternar optimizaciones del compilador C \(por defecto: on\)
 - **-cpp\[-\]** fuerza modo C\+\+/C
 - **-cpp=&lt;value&gt;** selecciona modo C\+\+. Los valores permitidos son: def, yes, no
 - **-c=&lt;value&gt;** select C standard. Allowed values are: iso90, iso99, iso11, gnu90, gnu99, gnu11
 - **-cpp=&lt;value&gt;** select C\+\+ mode or standard. Allowed values are: def, yes, no, iso98, iso11, iso14, gnu98, gnu11, gnu14
 - **-map\[-\]** crear \(o no\) un archivo map
 - **-implib\[-\]** crear \(o no\) una biblioteca de importación \(en modo -hbdyn/-hbexe\). El nombre tendrá un sufijo añadido.
 - **-implib=&lt;output&gt;** crear biblioteca de importación \(en modo -hbdyn/-hbexe\) Nombre de &lt;output&gt; \(por defecto: igual que la salida\)
 - **-ln=&lt;link&gt;** crea enlace simbólico apuntando a &lt;output&gt; \(&lt;link&gt; se asocia a &lt;output&gt;\)
 - **-trace\[-\]** mostrar comandos ejecutados
 - **-beep\[-\]** activa \(o desactiva\) beep simple en caso de éxito, doble beep en caso de falla
 - **-ignore\[-\]** ignore errores cuando ejecute herramienta de compilador \(por defecto: off\)
 - **-hbcppmm\[-\]** reemplaza las funciones de administración de memoria estandar de C\+\+ con las de Harbour
 - **-winuni\[-\]** select between UNICODE \(WIDE\) and ANSI Windows API and C runtime usage for C/C\+\+ input files \(default: ANSI\) \(Windows only. For WinCE it is always set to UNICODE\)
 - **-nohblib\[-\]** do not use static core Harbour libraries when linking \(default in -hbdyn mode or when neither .prg nor object files are specified as input\)
 - **-nodefgt\[-\]** no enlaza GTs por defecto \(efectivo en modo -static\)
 - **-nolibgrouping\[-\]** desactivar agrupamiento de LIBs en compiladores basados en gcc.
 - **-nomiscsyslib\[-\]** no agregue lista adicional de librerías del sistema a lista de librerías por defecto
 - **-traceonly** mostrar comandos a ser ejecutados, pero no ejecutarlos
 - **-warn=&lt;level&gt;** Establece el nivel de advertencia del compilador C  
&lt;level&gt; puede ser: max, yes, low, no, def \(default: yes\)
 - **-harden\[-\]** enable hardening options in C compiler/linker \(default: enabled on Windows, disabled on other systems\)
 - **-vcsts\[-\]** set timestamp of output file\(s\) to the last repository commit \(Supported with: Git\)
 - **-compr=&lt;level&gt;** compress executable/dynamic lib \(needs UPX tool\)  
&lt;level&gt; can be: yes, no, min, high, max
 - **-run\[-\]** ejecutar/no ejecutar aplicativo generado.
 - **-vcshead=&lt;file&gt;** generate .ch header file with local repository information. Git, SVN, Mercurial, Bazaar, Fossil, CVS and Monotone are currently supported. Generated header will define preprocessor constant \_HBMK\_VCS\_TYPE\_ with the name of detected VCS and \_HBMK\_VCS\_ID\_ with the unique ID of local repository. VCS specific information is added as \_HBMK\_VCS\_&lt;TYPE&gt;\_\*\_ constants, where supported. If no VCS system is detected, a sequential number will be rolled automatically on each build.
 - **-vcsdir=&lt;dir&gt;** override VCS repository root
 - **-bldhead=&lt;file&gt;** generate .ch header file with build information, like build sequence number and timestamp. Generated header will define preprocessor constants \_HBMK\_BUILD\_ID\_ and \_HBMK\_BUILD\_ID\_NUM\_ with sequence number \(incremented on each build\), \_HBMK\_BUILD\_YEAR\_, \_HBMK\_BUILD\_DATE\_, \_HBMK\_BUILD\_TIME\_, \_HBMK\_BUILD\_TIMESTAMP\_ with the date/time of build and \_HBMK\_BUILD\_RANDSTR\_32\_ with a random string of 32 bytes in hexadecimal format
 - **-haltrev\[-\]** do not increase revision numbers in -bldhead= \(\_HBMK\_BUILD\_ID\_\) and -vcshead= \(\_HBMK\_VCS\_ID\_\) options \(default: do increase\)
 - **-icon=&lt;file&gt;** establece &lt;file&gt; como ícono de la aplicación. &lt;file&gt; debe ser un formato soportado en la plataforma destino \(puede no ser soportado por algunas plataformas/compiladores\). En Windows, es implementado generando y enlazando un archivo de recursos.
 - **-manifest=&lt;file&gt;** incrustar manifiesto &lt;file&gt; en ejecutable/lib dinámica \(sólo Windows\)
 - **-sign=&lt;key&gt;** sign executable with &lt;key&gt; \(Windows and Darwin only\). On Windows signtool.exe is used \(part of MS Windows SDK\) or posign.exe \(part of Pelles C 7\), in that order, both auto-detected.
 - **-signpw=&lt;pw&gt;** use &lt;pw&gt; como contraseña al firmar ejecutables \(solo Windows y Darwin\)
 - **-signts=&lt;\[std:\]url&gt;** use &lt;url&gt; as trusted timestamp server. Optional &lt;std&gt; might specify the standard as 'rfc3161' or 'authenticode' \(without quotes\). The default is 'rfc3161'. Empty value disables timestamping. Default: http://timestamp.digicert.com
 - **-instfile=&lt;g:file&gt;** anadir &lt;archivo&gt; a la lista de archivos que desea copiar a la ruta especificada por la opción -instpath. &lt;g&gt; es un grupo opcional de copia \(distingue mayúsculas y minúsculas\), debe haber al menos dos caracteres. En caso de que no se especifica &lt;archivo&gt;, la lista de archivos en ese grupo se vaciará.
 - **-instpath=&lt;g:path&gt;** copia el/los archivo\(s\) objetivo a la ruta &lt;path&gt;. Si &lt;path&gt; es un directorio, debería terminar con un separador de rutas, en este caso los archivos especificados en la opción '-instfile' también son copiados. Puede ser especificado varias veces. &lt;g&gt; es grupo de copia opcional, debe tener al menos dos caracteres de largo. El objetivo final será copiado automaticamente al grupo de copia por defecto \(sin asignación de &lt;g&gt;\). Existen los siguientes grupos de copia ya incluidos: 'depimplib' para las bibliotecas importadas y 'depimplibsrc' para los archivos fuente de las bibliotecas importadas \(.dll\), ambos pertenecientes a las dependencias.
 - **-instforce\[-\]** copia archivo\(s\) destino a ruta de instalación incluso si está\(n\) actualizado\(s\)
 - **-depimplib\[-\]** activar \(o desactivar\) la generación de Bibliotecas de Importación para fuentes de biblioteca de importación especificados en la opción -depimplibs= \(por defecto: yes\)
 - **-stop\[=&lt;text&gt;\]** parar sin hacer nada y mostrar &lt;text&gt; si se ha especificado
 - **-echo=&lt;text&gt;** Muestra texto en la pantalla
 - **-skip** skip processing the rest of the project file \(filters not supported\)
 - **-pause** forzar pause para presionar una tecla en caso de error \(solo con driver GT alternativo\)
 - **-exitstr** mostrar resultado de error como texto legible al salir
 - **-info** activar los mensajes informativos
 - **-quiet\[-\]** suprimir todos los mensajes en pantalla


 - **-bldf\[-\]** heredar flags de Harbour: todos/ninguno \(por defecto\)
 - **-bldf=\[p\]\[c\]\[l\]** heredar todos los flags .prg/.c/linker \(o ninguno\) desde construcción de Harbour
 - **-F&lt;framework&gt;** Enlace con marco &lt;framework&gt; \(Sólo Darwin\)
 - **-prgflag=&lt;f&gt;** pasar bandera única al compilador Harbour
 - **-cflag=&lt;f&gt;** pasar bandera única al compilador C
 - **-resflag=&lt;f&gt;** pasar bandera única al compilador de recursos \(sólo Windows\)
 - **-ldflag=&lt;f&gt;** pasar bandera única al enlazador \(ejecutable\)
 - **-dflag=&lt;f&gt;** pasar bandera única al enlazador \(librería dinánica\)
 - **-aflag=&lt;f&gt;** pasa flag a linkeditor \(lib estática\)
 - **-iflag=&lt;f&gt;** pasar bandera única a comando de creación de biblioteca de importación
 - **-signflag=&lt;f&gt;** pasar bandera única al comando de firma de código
 - **-comprflag=&lt;f&gt;** pass single flag to executable compressor
 - **-runflag=&lt;f&gt;** pasar bandera única al ejecutable de salida cuando se utiliza la opción -run
 - **-cflag\+=&lt;f&gt;** pasar bandera única al compilador C reemplazando las opciones del compilador C añadidas por el mismo hbmk2. Usar con precaución.
 - **-ldflag\+=&lt;f&gt;** pasar una sola opción al enlazador \(ejecutable\) después de la lista de bibliotecas. Usar con precaución.
 - **-dflag\+=&lt;f&gt;** pasar una sola opción al enlazador \(biblioteca dinámica\) después de la lista de bibliotecas. Usar con precaución.
 - **-3rd=&lt;f&gt;** opciones/flags reservados para herramientas de terceros, siempre ignorado por hbmk2 en sí
 - **-env:&lt;e&gt;\[&lt;o&gt;\[&lt;v&gt;\]\]** alterar el ambiente local. &lt;e&gt; es el nombre de la variable de entorno a alterar. &lt;o&gt; puede ser '=' para establecer/reemplazar, '-' para borrar, '\+' para anadir al final de valor existente, '\#' para insertar al principio del valor existente. &lt;v&gt; es el valor a poner/agregar/insertar.
 - **-jobs=&lt;n&gt;** start n compilation threads \(multiprocess platforms only\) \(default: number of processors available or 1 if not detectable/applicable; on this system: 8\)
 - **-head=&lt;m&gt;** analizando fuente de control de encabezado \(en construcción en modo incremental\)  
&lt;m&gt; puede ser: nativo \(compilador utilizado para extraer las dependencias\), completa \(por defecto, utiliza analizador de texto simple en el fichero entero\), dep, off
 - **-rebuild** reconstrucción \(en modo incremental\)
 - **-rebuildall** reconstruir con sub-proyectos \(contrucción en modo incremental\)
 - **-clean** compilación limpia \(en modo incremental\)
 - **-workdir=&lt;dir&gt;** directorio de trabajo  
\(por defecto: .hbmk/&lt;platform&gt;/&lt;compiler&gt; \[\*\] en modo incremental, directorio temporal del SO de otra manera\)


 - **-hbcontainer** destino de construcción virtual, no crea nada. Útil para crear un .hbp con el solo propósito de referenciar sub-proyectos
 - **-hbimplib** crear biblioteca de importación \(solo Windows\)


 - **-hbl\[=&lt;output&gt;\]** nombre-de-archivo .hbl resultante. macro %\{hb\_lng\} es aceptada en nombre-de-archivo.
 - **-lng=&lt;languages&gt;** lista de idiomas a ser reemplazados en %\{hb\_lng\} macros en archivos .pot/.po y nombres de archivos y salida .hbl/.po. Lista separada por comas:  
-lng=en,hu-HU,de
 - **-po=&lt;output&gt;** crear/actualizar archivo .po desde fuentes. Combinar con anterior archivo .po del mismo nombre.
 - **-minipo\[-\]** do \(not\) add source file reference to .po \(default: add them\)
 - **-rebuildpo** recrea archivo .po, eliminando todas las entradas obsoletas en el mismo.
 - **-inithbl** if they are missing, create empty .hbl file\(s\) before starting the build


 - **-hbx=&lt;n\[.hbx&gt;\]&gt;** create Harbour header \(in .hbx format\) with all external symbols. Empty parameter will disable it. Default extension is .hbx. If set, &lt;n&gt; will be automatically added to the list of Harbour input files and built into the project. Therefore, the name part of &lt;n&gt; must not be the same as any other input file present in the project.
 - **-hbx\[-\]** update \(or don't\) .hbx file specified in -hbx= option \(default: update\)
 - **-autohbc=&lt;.ch:.hbc&gt;** &lt;.ch&gt; es un nombre de archivo de cabecera. &lt;.hbc&gt; es un nombre de archivo .hbc para ser incluido automáticamente en caso la cabecera se encuentra en cualquiera de las fuentes compiladas. \(EXPERIMENTAL\)


 - **-depurlbase=&lt;d:u&gt;** &lt;d&gt; is the name of the dependency. &lt;u&gt; is the URL of the project. Can be specified multiple times.
 - **-deppkgname=&lt;d:n&gt;** &lt;d&gt; es el nombre de la dependencia. &lt;n&gt; nombre de la dependencia de un paquete. Se puede especificar varias veces.
 - **-depkeyhead=&lt;d:h&gt;** &lt;d&gt; es el nombre de la dependencia. &lt;h&gt; es la cabecera clave \(.h\) de la dependencia de un paquete. Varios encabezados alternativos pueden ser especificados.
 - **-depoptional=&lt;d:f&gt;** &lt;d&gt; es el nombre de la dependencia. &lt;f&gt; puede ser 'yes' o 'no', especifica si la dependencia es opcional. Por defecto: no
 - **-depcontrol=&lt;d:v&gt;** &lt;d&gt; es el nombre de la dependencia. &lt;v&gt; es un valor que controla como se hace la detección. Valores aceptados: no, yes, force, nolocal, local. Por defecto: contenido de envvar HBMK\_WITH\_&lt;d&gt;
 - **-depincroot=&lt;d:r&gt;** &lt;d&gt; es el nombre de la dependencia. Establecer &lt;r&gt; como directorio raíz para las rutas especificadas en la opción -depincpath.
 - **-depincpath=&lt;d:i&gt;** &lt;d&gt; es el nombre de la dependencia. Anadir &lt;i&gt; a la lista de rutas de detección de encabezados.
 - **-depincpathlocal=&lt;d:i&gt;** &lt;d&gt; es el nombre de la dependencia. Agregue &lt;i&gt; a la lista de detección de rutas de cabeceras, donde &lt;i&gt; apunta a un directorio local del proyecto y que contiene una dependencia incrustada \(tambien conocida como "localmente hospedada"\).
 - **-depimplibs=&lt;d:dll\[:lib\]&gt;** &lt;d&gt; is the name of the dependency. Add &lt;dll&gt; to the import library source list. Optionally override the name of the generated implib to become &lt;lib&gt;.
 - **-depimplibd=&lt;d:lib&gt;** &lt;d&gt; es el nombre de la dependencia. Establecer nombre generado de biblioteca de importación a &lt;lib&gt;
 - **-depfinish=&lt;d&gt;** &lt;d&gt; es el nombre de la dependencia. Cierra la definición de dependencias y ejecuta la detección, estableciendo las variables macro de filtro predefinidas y las opciones de construcción relacionadas. Opcional, si se omite, la detección tendrá lugar después de procesar todas las opciones.


 - **-plugin=&lt;filename&gt;** agregar plugin \(módulo\). &lt;filename&gt; puede ser: .hb, .prg, .hrb
 - **-pi=&lt;filename&gt;** pasar archivo de entrada a plugins
 - **-pflag=&lt;f&gt;** pasar bandera única a plugins
  
Las opciones de mas abajo están disponibles en la línea de comandos:  


 - **-target=&lt;script&gt;** especifica una nueva construcción destino. &lt;script&gt; puede ser .prg \(o sin extensión\) o .hbp archivo. Tenga en cuenta que los archivos .hbp son automáticamente considerados como construcción destino separados.


 - **-hbrun** ejecutar la construcción de destino
 - **-hbraw** parar después de ejecutar compilador Harbour
 - **-hbcmp|-clipper** para después de la creación de los archivos objeto  
crear un enlace/copia a hbmk2 para hbcmp/clipper resultará el mismo efecto
 - **-hbcc** acepta raw C flags  
create enlace/copia hbmk2 para hbcc para el mismo efecto
 - **-hblnk** aceptar flags primas del enlazador
 - **-autohbm\[-\]** activar \(o desactivar\) procesamiento de hbmk.hbm en el directorio actual \(por defecto: yes\)
 - **-hb10** habilita modo de compatibilidad 'Harbour 1.0.x'
 - **-hb20** activa el modo de compatibilidad Harbour 2.0.x
 - **-hb30** activa el modo de compatibilidad Harbour 3.0.x
 - **-hb32** enable Harbour 3.2.0dev compatibility mode
 - **-xhb** habilitar modo xHarbour
 - **-hbc** activa modo puro C
 - **-blinker** emulate Cl\*pper compatible linker behavior  
create link/copy hbmk2 to rtlink/blinker/exospace for the same effect
 - **-exospace** see above
 - **-rtlink** see above


 - **-hbreg\[=global\]** registra script Harbour \(.hb\) con hbmk2 \(solo Windows\)
 - **-hbunreg\[=global\]** desregistra script Harbour \(.hb\) desde hbmk2 \(solo Windows\)


 - **-find &lt;text&gt;** list all known Harbour functions that contain &lt;text&gt; in their name, along with their package \(case insensitive, accepts multiple values, can contain wildcard characters\)
 - **-doc &lt;text&gt;** show documentation for function\[s\]/command\[s\] in &lt;text&gt;
 - **-docjson &lt;text&gt;** output documentation in JSON format for function\[s\]/command\[s\] in &lt;text&gt;
 - **-fixcase &lt;file\[s\]&gt;** fix casing of Harbour function names to their 'official' format. Core functions and functions belonging to all active contribs/addons with an .hbx file will be processed.
 - **-sanitize &lt;file\[s\]&gt;** convert filenames to lowercase, EOLs to platform native and remove EOF character, if present.
 - **-urlize \[&lt;file&gt;\]** convert .prg source or .hrb file \(or stdin\) to base64 encoded string on stdout.
 - **-deurlize \[&lt;str&gt;\]** convert base64 encoded source string \(or stdin\) to .prg source/.hrb file on stdout.


 - **-hbmake=&lt;file&gt;** convierte proyecto hbmake en un archivo .hbp
 - **-xbp=&lt;file&gt;** convierte proyecto .xbp \(xbuild\) en un archivo .hbp
 - **-xhp=&lt;file&gt;** convierte un proyecto .xhp \(xMate\) en un archivo .hbp


 - **--hbdirbin** muestra el directorio de binarios de Harbour
 - **--hbdirdyn** muestra el directorio de bibliotecas dinámicas de Harbour
 - **--hbdirlib** muestra el directorio de bibliotecas estáticas de Harbour
 - **--hbdirinc** muestra el directorio de cabeceras de Harbour
 - **--hbinfo\[=nested\]** muestra información de la construcción de Harbour. La salida es en formato JSON. Las rutas incluidas siempre contienen barras invertidas. Cada bloque JSON siempre es seguido por un byte 0x0A.


 - **-plat=&lt;platform&gt;** reemplaza la plataforma destino por defecto \(por defecto: automático\)
 - **-cpu=&lt;cpu&gt;** reemplaza la CPU de destino por defecto \(por defecto: automática\) \(EXPERIMENTAL\)
 - **-comp=&lt;compiler&gt;** override C compiler auto-detection  
Special value:  
 - bld: use original build settings \(default on \*nix\)
 - **-build=&lt;name&gt;** utilizar un nombre de build especifico
 - **-lang=&lt;lang&gt;** reemplaza lenguaje por defecto. &lt;lang&gt; es un código de lenguaje ISO.
 - **-width=&lt;n&gt;** establecer el ancho de salida a &lt;n&gt; caracteres \(0=sin límite\).
 - **-shl** mostrar nivel de subproyecto en las líneas de salida
 - **-viewhelp** full help in text viewer
 - **-fullhelp** full help
 - **-fullhelpmd** full help in [Markdown](https://daringfireball.net/projects/markdown/) format
 - **-harbourhelp** Ayuda de compilador Harbour \(todas las opciones del compilador Harbour son aceptadas como tal por hbmk2\)
 - **-credits** Créditos de compilador Harbour
 - **-build** Información de construcción de compilador Harbour
 - **-version** muestra solo versión de cabecera
  
Las opciones de mas abajo son internas o de desarrollador \(no se garantiza compatibilidad\):  


 - **-debugtime** mide el tiempo transcurrido durante la construcción
 - **-debuginc** muestra detalles internos del modo de construcción incremental
 - **-debugstub** muestra el contenido de todos los archivos fuente generados internamente
 - **-debugi18n** muestra
 - **-debugdepd** muestra detalles internos de la búsqueda de dependencia
 - **-debugpars** muestra todos los parámetros de entrada en orden de procesamiento
 - **-debugcmdl\[-\]** simulate command-line length limit of 0, or unlimited
 - **-debugrte** genera un error en tiempo de ejecución


Usted puede enlazar/copiar/renombrar hbmk2 a los siguientes nombres para alterar el modo de operación por defecto:


 - **hbrun\*|\*hbrun** modo ejecución de script / consola interactiva
 - **hbrund|hbrun\*d** modo ejecución de script / consola interactiva en modo depuración
 - **harbour** modo -hbraw \(emula compilador - puro - Harbour\)
 - **clipper** mode -hbcmp \(emulate Cl\*pper compiler\)
 - **rtlink** mode -rtlink \(emulate Cl\*pper linker\)
 - **exospace** mode -rtlink \(emulate Cl\*pper linker\)
 - **blinker** mode -rtlink \(emulate Cl\*pper linker\)
 - **\*10** opción -hb10
 - **\*20** opción -hb20
 - **\*30** opción -hb30
 - **\*32** opción -hb32
 - **x\*** opción -xhb
 - **hbcmp\*|\*hbcmp** modo -hbcmp \(emula compilador produciendo un objeto binario\)
 - **hbcc\*|\*hbcc** modo -hbcc \(emula compilador C\)
 - **hblnk\*|\*hblnk** modo -hblnk \(emula enlazador C\)
 - **hbexe\*|\*hbexe** modo -hbexe
 - **hblib\*|\*hblib** modo -hblib
 - **hbdyn\*|\*hbdyn** modo -hbdyn
  
Archivos:  


 - **\*.hbp** archivo de proyecto. Puede contener cualquier número de opciones de línea de comandos, que deben generar una salida. Las líneas que comienzan con "\#" son ignoradas, de otra manera, una nueva línea es opcional y las opciones están separadas por espacio, tal como en la línea de comandos. Se deben encomillar las opciones que contengan espacios. Cada referencia a un archivo .hbp será ejecutada como un sub-proyecto.
 - **\*.hbm** Conjunto de opciones. Puede ser usado para agrupar opciones comunes dentro de un archivo e incluirlo entre los archivos del projecto. Utiliza el mismo formato que los archivos .hbp.
 - **\*.hbc** colección de opciones que acompañan a los componentes \(conocidos como 'bibliotecas' o paquetes\). Usa una sintaxis diferente a la línea de comandos y a los archivos '.hbp'/'.hbm'. Las líneas que comienzan con "\#" son ignoradas, cada directiva debe ser ubicada en líneas separadas.
 - **\*.ch** si se envía como archivo fuente, será usado como cabecera estándar adicional
 - **hbmk.hbc** archivo .hbc estandar que es automáticamente procesado, si existe. Ubicación\(es\) posibles \(en orden de precedencia\) v \[\*\]: $HOME/.harbour, /etc/harbour, etc/harbour, etc, &lt;directorio hbmk2&gt;
 - **hbmk.hbm** archivo .hbm opcional ubicado en el directorio de trabajo actual, que es automáticamente procesado antes que otras opciones
 - **$hb\_pkg\_dynlib.hbm** special .hbm file built-in inside hbmk2. It manages the details of creating a dynamic library \(in the style of Harbour contribs\).
 - **$hb\_pkg\_install.hbm** special .hbm file built-in inside hbmk2. It manages the details of installing build targets and related package files to standard locations \(in the style of Harbour contribs\).


 - **\*.hb** script Harbour
 - **\*.hrb** Binario portable Harbour \(aka script precompilado Harbour\)
 - **hbstart.hb** Script de inicio Harbour para la consola interactiva. Es ejecutado automáticamente al iniciar la consola, si existe. Ubicación\(es\) posible\(s\) \(en orden de precedencia\) \[\*\]: ./, $HOME/.harbour, /etc/harbour, etc/harbour, etc, &lt;directorio hbmk2&gt;
 - **shell plugins** plugins .hb y .hrb para la consola interactiva Harbour. Pueden residir en \[\*\]: $HOME/.harbour/
 - **.hb\_history** guarda el historial de comandos del intérprete de comandos de Harbour. Puede deshabilitar el historial haciendo que la primera linea sea 'no' \(sin comillas y con salto de línea\). Se guarda en \[\*\]: $HOME/.harbour/
 - **hb\_extension** lista de extensiones para cargar en el interprete de comandos interactivo de Harbour. Una extensión por línea, y se ignora todo lo que hay detrás del caracter '\#'. Nombre de fichero alternativo en MS-DOS: hb\_ext.ini. Reside en \[\*\]: $HOME/.harbour/
  
Variables macro:  


 - **$\{hb\_root\}** directorio de hbmk2
 - **$\{hb\_prefix\}** Harbour root directory
 - **$\{hb\_dir\}** directorio del archivo en que es usado
 - **$\{hb\_dirname\}** directorio raiz del archivo en que es utilizado
 - **$\{hb\_name\}** nombre del archivo en que es usado \(sin directorio ni extensión\)
 - **$\{hb\_self\}** nombre completo del archivo en que es utilizado
 - **$\{hb\_curdir\}** directorio de trabajo actual
 - **$\{hb\_tempdir\}** Directorio del sistema operativo para archivos temporales
 - **$\{hb\_targetname\}** nombre del proyecto \(sin directorio ni extensión\). Devuelve .adhoc. si no existe archivo de proyecto.
 - **$\{hb\_targettype\}** tipo de proyecto \(hbexe, hblib, hbdyn, hbdynvm, hbimplib, hbppo, hbhrb, hbcontainer\)
 - **$\{hb\_plat\}** plataforma seleccionada
 - **$\{hb\_comp\}** compilador C seleccionado
 - **$\{hb\_comp\_ver\}** C compiler version. Caveat: Returns '0' on \*nix systems, because at macro evaluation time the C compiler version is not queried yet.
 - **$\{hb\_build\}** nombre de construcción
 - **$\{hb\_cpu\}** CPU seleccionada
 - **$\{hb\_work\}** directorio de trabajo base por defecto
 - **$\{hb\_workdynsub\}** subdirectorio de trabajo por defecto para destino de bibliotecas dinámicas
 - **$\{hb\_dynprefix\}** prefijo de librería dinámica
 - **$\{hb\_dynsuffix\}** sufijo de librería dinámica
 - **$\{hb\_dynext\}** extensión de librería dinámica
 - **$\{hb\_ver\}** Harbour version in hexadecimal triple byte format. E.g.: 030400
 - **$\{hb\_verstr\}** Harbour version in human readable format &lt;major&gt;.&lt;minor&gt;.&lt;release&gt;&lt;status&gt;. E.g.: 3.4.0dev
 - **$\{hb\_major\}** Número mayor de versión Harbour
 - **$\{hb\_minor\}** Número menor de versión Harbour
 - **$\{hb\_release\}** Número de versión de Harbour liberada
 - **$\{hb\_status\}** estado de versión Harbour
 - **$\{hb\_ver\_id\}** Harbour version ID
 - **$\{hb\_ver\_id\_short\}** Harbour version ID \(short\)
 - **$\{hb\_revision\}** revisión Harbour
 - **$\{hb\_host\_plat\}** plataforma huésped Harbour
 - **$\{hb\_host\_plat\_unix\}** devuelve '1' si la plataforma huésped Harbour es compatible \*nix
 - **$\{hb\_bin\}** directorio de binarios Harbour
 - **$\{hb\_lib\}** Directorio de librerías estáticas de Harbour
 - **$\{hb\_lib3rd\}** Directorio de librerías estáticas de terceros de Harbour
 - **$\{hb\_dyn\}** Directorio de librerías dinámicas de Harbour
 - **$\{hb\_inc\}** directorio de cabeceras Harbour
 - **$\{hb\_addons\}** directorio base de complementos de Harbour
 - **$\{hb\_first\}** nombre del archivo fuente que contiene la función principal \(sin directorio ni extensión\)
 - **$\{hb\_outputdir\}** directorio de salida
 - **$\{hb\_outputname\}** nombre de la salida \(sin extensión\)
 - **$\{hb\_level\}** nivel de recursión de sub-proyecto
 - **$\{&lt;depname&gt;\}** devuelve el directorio cabecera de la dependencia &lt;depname&gt; fue detectado, o '1' si no se ha detectado.
 - **$\{&lt;envvar&gt;\}** devuelve el valor de la variable de entorno &lt;envvar&gt;
  
Filtros \(puede combinar y/o negarlos\):  


 - **\{&lt;platform&gt;\}** plataforma destino. Donde &lt;platform&gt; puede ser cualquier valor aceptado por la opción -plat= .
 - **\{&lt;compiler&gt;\}** compilador C destino. Donde &lt;compiler&gt; puede ser cualquier valor aceptado por la opción -comp= .
 - **\{&lt;cpu&gt;\}** CPU destino. Donde &lt;cpu&gt; puede ser uno de: x86, x86\_64, ia64, arm, mips, sh
 - **\{&lt;targettype&gt;\}** tipo de construcción destino. Donde &lt;targettype&gt; es cualquiera de los valores retornados por la variable macro $\{hb\_targettype\}.
 - **\{&lt;package-manager&gt;\}** package manager. Where &lt;package-manager&gt; can be any of: deb, rpm, portage, homebrew, nix, macports, fink, pkg, cygwin
 - **\{mt\}** construcción destino es multihilo \(ver opción -mt\)
 - **\{st\}** construcción destino es monohilo \(ver opción -st\)
 - **\{gui\}** GUI destino \(vea opción -gui\)
 - **\{std\}** consola destino \(vea opción -console\)
 - **\{debug\}** El nivel de depuración C está habilitado \(ver la opción -debug-\)
 - **\{nodebug\}** El nivel de depuración C está deshabilitado \(vea la opción -debug-\)
 - **\{shared\}** construcción compartida \(ver -shared y opciones relacionadas\)
 - **\{static\}** construcción estática \(ver -static y opciones relacionadas\)
 - **\{lngcpp\}** modo C\+\+ forzado \(ver opción -cpp\)
 - **\{lngc\}** modo C forzado \(ver opción -cpp-\)
 - **\{winuni\}** modo UNICODE \(WIDE\) de Windows \(ver opción -winuni\)
 - **\{winansi\}** modo ANSI de Windows \(ver opción -winuni-\)
 - **\{unix\}** plataforma destino es compatible \*nix \(bsd, hpux, sunos, beos, qnx, android, vxworks, linux, darwin, cygwin, minix, aix\)
 - **\{allwin\}** plataforma destino es compatible con Windows \(win, wce\)
 - **\{allwinar\}** target platform is Windows using .a libraries \(mingw, mingw64, mingwarm, clang, clang64\)
 - **\{allgcc\}** compilador C destino pertenece a la familia gcc \(gcc, mingw, mingw64, mingwarm, djgpp, gccomf, clang, clang64, open64, pcc\)
 - **\{allmingw\}** compilador C destino es mingw\* \(mingw, mingw64, mingwarm\)
 - **\{allclang\}** target C compiler is clang\* \(clang, clang64\)
 - **\{allmsvc\}** target C compiler is msvc\* \(msvc, msvc64, msvcia64, msvcarm, clang-cl, clang-cl64\)
 - **\{allbcc\}** compilador C destino es bcc\* \(bcc, bcc64\)
 - **\{allpocc\}** compilador C destino es pocc\* \(pocc, pocc64, poccarm\)
 - **\{allicc\}** target C compiler is icc\* \(icc, icc64, iccia64\)
 - **\{hb10\}** Modo de compatibilidad Harbour 1.0.x \(ver opción -hb10\)
 - **\{hb20\}** Modo de compatibilidad Harbour 2.0.x \(ver opción -hb20\)
 - **\{hb30\}** Modo de compatibilidad Harbour 3.0.x \(ver opción -hb30\)
 - **\{hb32\}** Harbour 3.2.0dev compatibility mode \(see -hb32 option\)
 - **\{xhb\}** mode xHarbour \(ver opción -xhb\)
 - **\{hb\_ispath='&lt;file|dir&gt;'\}** el filtro pasará si el nombre de &lt;file&gt; o &lt;dir&gt; existe en disco.
 - **\{MACRO\}** el filtro pasará si el valor de $\{MACRO\} no está vacio y no es igual a '0' o 'no' \(insensible a minúsculas y mayúsculas\)
 - **\{MACRO='&lt;value&gt;'\}** el filtro pasará si el valor de $\{MACRO\} es igual a &lt;value&gt; \(insensible a minúsculas y mayúsculas\)
 - **\{MACRO&gt;'&lt;value&gt;'\}** el filtro pasará si el valor de $\{MACRO\} es mayor a &lt;value&gt; \(insensible a minúsculas y mayúsculas\)
 - **\{MACRO&lt;'&lt;value&gt;'\}** el filtro pasará si el valor de $\{MACRO\} es menor a &lt;value&gt; \(insensible a minúsculas y mayúsculas\)


Predefined constants in sources \(do not define them manually\):


 - **\_\_HBSCRIPT\_\_HBMK\_PLUGIN** cuando un script .hb es compilado como plugin hbmk2
 - **\_\_HBEXTREQ\_\_** cuando una fuente .hbx existe en un proyecto \(disponible en las fuentes Harbour\)
 - **HBMK\_HAS\_&lt;hbcname&gt;** cuando el paquete &lt;hbcname&gt;.hbc se enlaza al objetivo final. El valor se obtiene de la entrada 'version=' del archivo .hbc, convertido a número decimal, '1' si no se especifica. \(disponible en el código fuente de Harbour\)
 - **HBMK\_HAS\_&lt;depname&gt;** cuando la dependencia &lt;depname&gt; ha sido detectada \(disponible en fuentes C\)


 - **\_\_HBSCRIPT\_\_HBSHELL** cuando un archivo fuente Harbour es ejecutado como un script de consola
 - **&lt;standard Harbour&gt;** \_\_PLATFORM\_\_\*, \_\_ARCH\*BIT\_\_, \_\_\*\_ENDIAN\_\_, etc.


Predefined constants in build files \(they are available after '-depfinish=&lt;depname&gt;' / 'depfinish=&lt;depname&gt;'\) \(do not define them manually\):


 - **HBMK\_HAS\_&lt;depname&gt;** cuando la dependencia &lt;depname&gt; ha sido detectada
 - **HBMK\_DIR\_&lt;depname&gt;** devuelve el directorio cabecera en donde &lt;depname&gt; fue detectado, o un valor vacío so no se ha detectado.
 - **HBMK\_HAS\_&lt;depname&gt;\_LOCAL** cuando la dependencia &lt;depname&gt; ha sido detectada en una ubicación establecida por la opción -depincpathlocal=
  
Variables de entorno  


 - **HBMK\_OPTIONS** acepta cualquier opción como si se pasaran al inicio de la línea de comandos
 - **HB\_PLATFORM** acepta los mismos valores que la opción -plat=
 - **HB\_COMPILER** acepta los mismos valores que la opción -comp=
 - **HB\_CPU** acepta los mismos valores que la opción -cpu=
 - **HB\_BUILD\_NAME** acepta los mismos valores que la opción -build=
 - **HB\_LANG** acepta los mismos valores que la opción -lang=
 - **HB\_USER\_LIBS** acepta los mismos valores \(separador por espacio\) que la opción -l
 - **HB\_USER\_LIBPATHS** acepta los mismos valores \(separador por espacio\) que la opción -L
 - **HB\_USER\_PRGFLAGS** opciones para pasar al compilador Harbour \(antes de las opciones de línea de comandos\)
 - **HB\_USER\_CFLAGS** opciones para pasar al compilador C \(antes de las opciones de línea de comandos\)
 - **HB\_USER\_RESFLAGS** opciones para pasar al compilador de recursos \(antes de las opciones de línea de comandos\) \(solo Windows\)
 - **HB\_USER\_LDFLAGS** opciones para pasar al enlazador \(ejecutable\) \(antes de las opciones de línea de comandos\)
 - **HB\_USER\_DFLAGS** opciones para pasar al enlazador \(biblioteca dinámica\) \(antes de las opciones de línea de comandos\)
 - **HB\_USER\_AFLAGS** opciones para pasar al enlazador \(biblioteca estática\) \(antes de las opciones de línea de comandos\)
 - **HB\_CCPATH** reemplaza directorio del ejecutable del compilador C \(solo familias del compilador gcc\)
 - **HB\_CCPREFIX** reemplaza prefijo del ejecutable del compilador C \(solo familias del compilador gcc\)
 - **HB\_CCSUFFIX** reemplaza sufijo del ejecutable del compilador C \(solo familias del compilador gcc/clang\)
 - **HB\_INSTALL\_PREFIX** reemplaza el directorio base de instalación de Harbour
 - **HB\_INSTALL\_ADDONS** reemplaza el directorio base de complementos de Harbour


 - **HB\_EXTENSION** lista separada por espacio de extensiones a cargar en la consola Harbour interactiva
  
directivas .hbc \(deben ser escritas en líneas separadas\):  


 - **echo=&lt;msg&gt;** mostrar &lt;msg&gt;
 - **skip=\[&lt;msg&gt;\]** omite el procesamiento del resto del archivo .hbc. Muestra &lt;msg&gt;, si está especificado.
 - **stop=\[&lt;msg&gt;\]** detiene la construcción. Muestra &lt;msg&gt;, si está especificado.
 - **sources=** agregar lista de archivos de entrada separados por espacio
 - **headers=** agregar lista de archivos de cabecera .ch separados por espacios como cabeceras estándar
 - **libs=** agregar lista de bibliotecas separadas por espacio \(vea mas en la opción -l\)
 - **frameworks=** agregar lista de frameworks separados por espacio \(solo Darwin\)
 - **requests=** agrega lista de símbolos separados por espacio para forzar el enlace a la construcción destino.
 - **syslibs=** agregar lista de bibliotecas separadas por espacio como bibliotecas de sistema \(antes de las bibliotecas regulares\)
 - **hbcs=** incrusta una lista de archivos .hbc separados por espacios. Se aceptan nombres sin extensión. Estas referencias se procesan en el momento.
 - **autohbcs=** lista de valores separados por espacio como en opción -autohbc=
 - **libpaths=** lista de rutas de biblioteca adicionales separadas por espacio
 - **incpaths=** agrega lista de rutas adicionales de cabecera separada por espacio \(para Harbour y C\)
 - **instfiles=** lista de valores separados por espacio como en opción -instfile=
 - **instpaths=** lista de valores separados por espacio como en opción -instpath=
 - **prgflags=** lista de valores separados por espacio como en opción -prgflag=
 - **cflags=** lista de valores separados por espacio como en opción -cflag=
 - **resflags=** lista de valores separados por espacio como en opción -resflag=
 - **ldflags=** lista de valores separados por espacio como en opción -ldflag=
 - **ldflags\+=** lista de valores separados por espacio como en opción -ldflag\+=
 - **dflags=** lista de valores separados por espacio como en opción -dflag=
 - **dflags\+=** lista de valores separados por espacio como en opción -dflag\+=
 - **pflags=** lista de valores separados por espacio como en opción -pflag=
 - **psources=** lista de valores separados por espacio como en opción -pi=
 - **gui=&lt;bool&gt;** opción 'yes' = -gui, 'no' = -std
 - **mt=&lt;bool&gt;** opción 'yes' = -mt, 'no' = -st
 - **pic=&lt;bool&gt;** opción 'yes' = -pic, 'no' = -pic-
 - **shared=&lt;bool&gt;** opción 'yes' = -shared, 'no' = -static
 - **shareddef=&lt;bool&gt;** similar a shared=, pero funciona solo si el modo shared/static no ha sido establecido con anterioridad
 - **fullstatic=&lt;bool&gt;** opción 'yes' = -fullstatic, 'no' = -static
 - **debug=&lt;bool&gt;** opción 'yes' = -debug, 'no' = -debug-
 - **optim=** opción 'yes' = -optim, 'no' = -optim-
 - **nulrdd=&lt;bool&gt;** opción 'yes' = -nulrdd, 'no' = -nulrdd-
 - **nodefgt=&lt;bool&gt;** opción 'yes' = -nodefgt, 'no' = -nodefgt-
 - **map=&lt;bool&gt;** opción 'yes' = -map, 'no' = -map-
 - **hbcppmm=&lt;bool&gt;** opción 'yes' = -hbcpmm, 'no' = -hbcpmm-
 - **implib=&lt;bool&gt;** opción 'yes' = -implib, 'no' = -implib-
 - **winuni=&lt;bool&gt;** opción 'yes' = -winuni, 'no' = -winuni-
 - **strip=&lt;bool&gt;** opción 'yes' = -strip, 'no' = -strip-
 - **run=&lt;bool&gt;** opción 'yes' = -run, 'no' = -run-
 - **inc=&lt;bool&gt;** opción 'yes' = -inc, 'no' = -inc-
 - **harden=&lt;bool&gt;** opción 'yes' = -harden, 'no' = -harden-
 - **cpp=** igual que la opción -cpp=
 - **warn=** igual que la opción -warn=
 - **compr=** igual que la opción -compr=
 - **head=** igual que la opción -head=
 - **plugins=** lista separada por espacio de hbmk2 plugins a cargar
 - **gt=&lt;name&gt;** igual que la opción -gt&lt;name&gt;
 - **gtdef=&lt;name&gt;** establece el GT por defecto a utilizar
 - **env=** igual que la opción -env:
 - **depurlbase=** igual que la opción -depurlbase=
 - **deppkgname=** igual que la opción -deppkgname=
 - **depkeyhead=** igual que la opción -depkeyhead=
 - **depoptional=** igual que la opción -depoptional=
 - **depcontrol=** igual que la opción -depcontrol=
 - **depincroot=** igual que la opción -depincroot=
 - **depincpath=** igual que la opción -depincpath=
 - **depincpathlocal=** igual que la opción -depincpathlocal=
 - **depimplibs=** igual que la opción -depimplibs=
 - **depimplibd=** igual que la opción -depimplibd=
 - **depfinish=** igual que la opción -depfinish=
 - **signts=** igual que la opción -signts=
 - **name=** Nombre de paquete
 - **description=** descripción del paquete
 - **version=&lt;x.y.z&gt;** número de versión del paquete, donde x,y,z &gt;= 0 &lt;= 255. Por defecto 0.0.1, si no es especificado.
 - **keywords=** lista de palabras clave separadas por espacio
 - **licences=** lista de licencias separadas por espacio
 - **repository=** lista separada por espacio de referencias a repositorios fuente


API de plugin:  
\('hbmk' es la variable de contexto recibida por la función principal del plugin\)


 - **hbmk\_Register\_Input\_File\_Extension\( hbmk, &lt;cExt&gt; \) -&gt; NIL**  
Register input file extension to be passed to plugin \(by default all unrecognized file extensions are passed to Harbour compiler\).
 - **hbmk\_AddInput\_PRG\( hbmk, &lt;cFileName&gt; \) -&gt; NIL**  
Agregar un archivo Harbour al proyecto.
 - **hbmk\_AddInput\_C\( hbmk, &lt;cFileName&gt; \) -&gt; NIL**  
Agregar un archivo C al proyecto.
 - **hbmk\_AddInput\_CPP\( hbmk, &lt;cFileName&gt; \) -&gt; NIL**  
Agregar un archivo C\+\+ al proyecto.
 - **hbmk\_AddInput\_RC\( hbmk, &lt;cFileName&gt; \) -&gt; NIL**  
Agregar un archivo de recursos Windows al proyecto.
 - **hbmk\_AddInput\_OBJ\( hbmk, &lt;cFileName&gt; \) -&gt; NIL**  
Agregar un archivo binario objeto al proyecto.
 - **hbmk\_AddInput\_INSTFILE\( hbmk, &lt;cFileName&gt;, \[&lt;cGroup&gt;\] \) -&gt; NIL**  
Agrega un archivo a instalar, con un nombre de grupo opcional -instpath=
 - **hbmk\_AddOption\_PRG\( hbmk, &lt;cOption&gt; \) -&gt; NIL**  
Add a Harbour compiler option.
 - **hbmk\_AddOption\_C\( hbmk, &lt;cOption&gt; \) -&gt; NIL**  
Add a C compiler option.
 - **hbmk\_OutStd\( hbmk, &lt;cText&gt; \) -&gt; NIL**  
Texto de salida a stdout.
 - **hbmk\_OutErr\( hbmk, &lt;cText&gt; \) -&gt; NIL**  
Texto de salida a stderr.
 - **hbmk\_OutStdRaw\( hbmk, &hellip; \) -&gt; NIL**  
Enviar texto a stdout sin ningún formato.
 - **hbmk\_OutErrRaw\( hbmk, &hellip; \) -&gt; NIL**  
Enviar texto a stderr sin ningún formato.
 - **hbmk\_Macro\( hbmk, &lt;cMacro&gt; \) -&gt; &lt;cResult&gt;**  
Evaluate la expresión macro hbmk2.
 - **hbmk\_FNameEscape\( hbmk, &lt;cFileName&gt; \) -&gt; &lt;cFileName&gt;**  
Escapa/encomilla el nombre de archivo para utilizarlo como parámetro de un comando externo
 - **hbmk\_PathSepToTarget\( hbmk, &lt;cFileName&gt; \) -&gt; &lt;cFileName&gt;**  
Convierte el nombre del fichero al formato requerido por la plataforma/compilador C destino
 - **hbmk\_PathSepToForward\( &lt;cPath&gt; \) -&gt; &lt;cPath&gt;**  
Convierte el nombre de archivo para que tenga barras invertidas como separadores de directorios.
 - **hbmk\_PathFromWorkdirToCWD\( hbmk \) -&gt; &lt;cRelativePath&gt;**  
Devuelve la ruta relativa del valor de -workdir= desde el directorio de trabajo actual.
 - **hbmk\_FindInPath\( &lt;cFileName&gt;, \[&lt;xPath&gt;\], \[&lt;aExtDef&gt;\] \) -&gt; &lt;cFNFound&gt; | NIL**  
Busca el archivo en &lt;xPath&gt; \(se admite una matriz o una cadena delimitada con separadores de ruta\) con una lista de extensiones alternativas &lt;aExtDef&gt; \(por defecto ejecutables binarios\). Devuelve un nombre de archivo si se encuentra, NIL si no.
 - **hbmk\_FNameDirExtSet\( &lt;cFileName&gt;, \[&lt;cDirNew&gt;\], \[&lt;cExtNew&gt;\] \) -&gt; &lt;cFileName&gt;**  
Cambiar directorio y/o extensión en nombre de archivo.
 - **hbmk\_FuncNameEncode\( &lt;cFuncName&gt; \) -&gt; &lt;cFuncNameEncoded&gt;**  
Codifica el nombre de la función de acuerdo a las reglas del compilador Harbour para formar los nombres de función HB\_FUNC\(\) en el código C.
 - **hbmk\_StrStripQuote\( &lt;cString&gt; \) -&gt; &lt;cString&gt;**  
Remueve doble encomillado de una cadena.
 - **hbmk\_ArrayToList\( &lt;aList&gt;, \[&lt;cSeparator&gt;\] \) -&gt; &lt;cList&gt;**  
Convertir array de cadenas a cadena. El separador por defecto es un espacio simple.


Variables de plugin:  
\(ítems de contexto 'hbmk', insensibles a mayúsculas/minúsculas, solo lectura salvo que se haya establecido lo contrario\)


 - **"apiver"** versión API como un entero
 - **"cSTATE"** Esta
 - **"params"** arreglo de parámetros pasados a los plugins vía -pflag=/pi=, o a con una extensión registrada vía hbmk\_Register\_Input\_File\_Extension\(\)
 - **"vars"** 'hash' de variables para uso del complemento. Modificable, local para cada complemento.
 - **"cPLAT"** valor -plat
 - **"cCOMP"** valor -comp
 - **"cCOMPVer"** detected compiler version in &lt;MMmm&gt; format \(and '0' if undetermined\)
 - **"nCOMPVer"** detected compiler version as a number: &lt;major&gt; \* 100 \+ &lt;minor&gt; \(deprecated\)
 - **"cCPU"** valor -cpu
 - **"cBUILD"** valor -build=
 - **"cOUTPUTNAME"** valor -o
 - **"cTARGETNAME"** ver macro $\{hb\_targetname\}
 - **"cTARGETTYPE"** ver macro $\{hb\_targettype\}
 - **"lREBUILD"** estado de opción -rebuild
 - **"lCLEAN"** estado de opción -clean
 - **"lDEBUG"** estado de opción -debug
 - **"lMAP"** estado de opción -map
 - **"lSTRIP"** estado de opción -strip
 - **"lDONTEXEC"** estado de opción -traceonly
 - **"lIGNOREERROR"** estado de opción -ignore
 - **"lTRACE"** estado de opción -trace
 - **"lQUIET"** estado de opción -q
 - **"lINFO"** estado de opción -info
 - **"lBEEP"** estado de opción -beep
 - **"lRUN"** estado de opción -run
 - **"lINC"** estado de opción -inc
 - **"cCCPATH"** ver envvar HB\_CCPATH
 - **"cCCPREFIX"** ver envvar HB\_CCPREFIX
 - **"cCCSUFFIX"** ver envvar HB\_CCSUFFIX
 - **"cCCEXT"** ver envvar HB\_CCEXT
 - **"cWorkDir"** valor -workdir=
 - **"nExitCode"** Código de salida actual
  
API de consola disponible en scripts Harbour:  


 - **hbshell\_gtSelect\( \[&lt;cGT&gt;\] \) -&gt; NIL**  
Intercambia GT. Por defecto \[\*\]: 'gttrm'
 - **hbshell\_Clipper\(\) -&gt; NIL**  
Enable Cl\*pper compatibility \(non-Unicode\) mode.
 - **hbshell\_include\( &lt;cHeader&gt; \) -&gt; &lt;lSuccess&gt;**  
Cargar cabecera Harbour.
 - **hbshell\_uninclude\( &lt;cHeader&gt; \) -&gt; &lt;lSuccess&gt;**  
Descargar cabecera Harbour.
 - **hbshell\_include\_list\(\) -&gt; NIL**  
Muestra lista de cabecera Harbour cargada.
 - **hbshell\_ext\_load\( &lt;cPackageName&gt; \) -&gt; &lt;lSuccess&gt;**  
Carga paquete. Similar a la directiva PP \#request.
 - **hbshell\_ext\_unload\( &lt;cPackageName&gt; \) -&gt; &lt;lSuccess&gt;**  
Descargar paquete.
 - **hbshell\_ext\_get\_list\(\) -&gt; &lt;aPackages&gt;**  
Lista de paquetes cargados
 - **hbshell\_DirBase\(\) -&gt; &lt;cBaseDir&gt;**  
hb\_DirBase\(\) no mapeado al script.
 - **hbshell\_ProgName\(\) -&gt; &lt;cPath&gt;**  
hb\_ProgName\(\) no mapeado al script.
 - **hbshell\_ScriptName\(\) -&gt; &lt;cPath&gt;**  
Name of the script executing.


Ejemplos para comenzar con hbmk2:


 - **Para ejecutar la consola interactiva \(indicador 'punto'\)**  
$ hbmk2 .
 - **Para ejecutar un script Harbour**  
$ hbmk2 myscript.hb \[&lt;parameter\[s\]&gt;\]


Ejemplos para construir y ejecutar un binario portable Harbour \(tambien llamado script Harbour precompilado\):


 - **A construir**  
$ hbmk2 -gh myscript.hb
 - **Para ejecutar el resultado de mas arriba**  
$ hbmk2 myscript.hrb \[&lt;parameter\[s\]&gt;\]


Ejemplos para construir una aplicación Harbour


 - **Para construir un solo .prg**  
$ hbmk2 hello.prg
 - **Para construir multiples fuentes .prg en una única aplicación en modo incremental**  
$ hbmk2 mymain.prg myfuncs.prg -inc
 - **para construir una aplicación usando un archivo de projecto**  
$ hbmk2 myapp.hbp
 - **Para construir una aplicación usando el modo incremental**  
$ hbmk2 myapp.hbp -inc
 - **Para construir una aplicación que utiliza un paquete de contribución o un complemento que se envia con un archivo .hbc**  
$ hbmk2 myapp.prg hbct.hbc
 - **Para construir una aplicación que utiliza una biblioteca pura**  
$ hbmk2 myapp.prg -lmylib -L&lt;path\_to\_mylib&gt;
 - **Para construir una aplicación que utiliza un recurso Windows**  
$ hbmk2 mymain.prg myres.rc
 - **Para construir una aplicación que enlaza con bibliotecas dinámicas Harbour**  
$ hbmk2 -shared myapp.prg
 - **Para construir una aplicación desde todas las fuentes .prg y .c ubicadas en el subdirectorio 'fuente'**  
$ hbmk2 -omyapp src/\*.prg src/\*.c


Ejemplos para construir una librería estática Harbour


 - **Para construir librería 'mylib' desde las fuentes**  
$ hbmk2 -hblib mylibsrc.prg -omylib
 - **Para construir librería 'mylib' desde las fuentes utilizando el modo incremental**  
$ hbmk2 -hblib mylibsrc.prg -omylib -inc
  
Códigos de salida \("errorlevels"\):  


 - **0** sin error
 - **1** unrecognized platform
 - **2** unrecognized compiler
 - **3** detección de Harbour fallida
 - **5** no se pudo crear fragmento de código
 - **6** failed in compilation phase
 - **7** falló en ensamblado final \(enlazador o administrador de bibliotecas\)
 - **8** no soportado
 - **9** fallo al crear directorio de trabajo
 - **19** ayuda
 - **10** dependencia faltante o deshabilitada
 - **20** Inicialización de plugin
 - **30** anidamiento demasiado profundo
 - **50** detención solicitada
 - **&lt;otro&gt;** cuando la opción -run es utilizada, el código de salida será el retornado por el ejecutable destino
  
Notas:  


  - &lt;script&gt; puede ser:  
&lt;@script&gt; o &lt;script.hbm&gt;: comandos de opciones de línea en el archivo  
&lt;script.hbp&gt;: comandos de opciones de línea en el archivo, también marca una nueva construcción destino si se especifica en la línea de comandos  
&lt;script.hbc&gt;: archivo de configuración del paquete
  - Un archivo fuente sin extensión cargará el archivo .hbp, si este .hbp existe en el directorio actual. De otra manera, se usará la extensión .prg.
  - Múltiples parámetros son aceptados -l, -L, -i y &lt;script&gt;.
  - las opciones regulares de compilador Harbour también son aceptadas.  
\(Verlos con la opción -harbourhelp\)
  - hbmk.hbc option file in hbmk2 directory is always processed if it exists. On \*nix platforms ~/harbour, /etc/.harbour, &lt;base&gt;/etc/.harbour, &lt;base&gt;/etc are checked \(in that order\) before the hbmk2 directory.
  - hbmk.hbm hace script en el directorio actual siempre se procesa, si existe.
  - Se recomienda usar barras inclinadas en los valores de opciones de directorios, pero tambien se aceptan igualmente barras invertidas.
  - filtros para plataformas son aceptados en cada linea de archivo .hbc y con varias opciones.  
Formato de filtro: \{\[\!\]\[&lt;plataforma&gt;|&lt;compilador&gt;|&lt;cpu&gt;|&lt;palabra-clave&gt;\]\}. Filtros pueden ser combinados usando los operadores '&amp;', '|' y agrupados en parénteses. Ej.: \{win\}, \{gcc\}, \{linux|darwin\}, \{win&amp;\!pocc\}, \{\(win|linux\)&amp;\!watcom\}, \{unix&amp;mt&amp;gui\}, -cflag=\{win\}-DMYDEF, -stop\{dos\}, -stop\{\!allwin\}
  - La mayoría de las líneas .hbc \(libs=, hbcs=, prgflags=, cflags=, ldflags=, libpaths=, instfiles=, instpaths=, echo=\) y sus parámetros de línea de comando correspondientes aceptarán variables macro. libpaths= tambien acepta %\{hb\_name\} que se traduce al nombre del archivo .hbc buscado.
  - Options accepting macro variables also support command substitution. Enclose command inside \`\`, and, if the command contains space, also enclose in double quotes. Standard output of the command will be used as the value. E.g. "-cflag=\`wx-config --cflags\`", or ldflags=\{unix&amp;gcc\}"\`wx-config --libs\`".
  - Cuando se especifican múltiples opciones de tipo de construcción destino \(-hblib, -hbdyn, etc.\), solo se utilizará la primera, las demás serán ignoradas silenciosamente.
  - Bibliotecas y archivos objeto construidos con/para CA-Cl\*pper no funcionaran con ninguna plataforma/compilador seleccionado.
  - Modos por defecto y soporte de características pueden variar por plataforma/compilador.
  - No se necesita GNU Make u otra utilidad 'make' específica de un compilador C y MSYS \(en Windows\) para ejecutar hbmk2.
  - '.' \(dot\) passed as first parameter will enter the interactive Harbour shell.


  - .hb, .hrb o .dbf file passed as first parameter will be run as Harbour script. If the filename contains no path components, it will be searched in current working directory and in PATH. If not extension is given, .hb and .hrb extensions are searched, in that order. .dbf file will be opened automatically in shared mode and interactive Harbour shell launched. .dbf files with non-standard extension can be opened by prepending '-dbf:' to the file name. Otherwise, non-standard extensions will be auto-detected for source and precompiled script types. Note, for Harbour scripts, the codepage is set to UTF-8 by default. The default core header 'hb.ch' is automatically \#included at the interactive shell prompt. The default date format is the ISO standard: yyyy-mm-dd. SET EXACT is set to ON. Set\( \_SET\_EOL \) is set to OFF. The default GT is 'gtcgi', unless full-screen CUI calls are detected, when 'gttrm' \[\*\] is automatically selected \(except for INIT PROCEDUREs\).
  - You can use key &lt;Ctrl\+V&gt; in interactive Harbour shell to paste text from the clipboard.
  - Valores marcados con \[\*\] pueden ser dependientes de la plataforma huésped o de la configuración. Esta ayuda ha sido generada en la plataforma huésped 'darwin' .


Valores suportados para &lt;compiler&gt; conforme a &lt;platform&gt; disponible:


 - **linux** gcc, clang, icc, watcom, sunpro, open64
 - **darwin** gcc, clang, icc
 - **win** mingw, mingw64, clang, clang64, msvc, msvc64, clang-cl, clang-cl64, watcom, icc, icc64, iccia64, msvcia64, bcc, bcc64, pocc, pocc64
 - **wce** mingwarm, mingw, msvcarm, poccarm
 - **os2** gcc, gccomf, watcom
 - **dos** djgpp, watcom
 - **bsd** gcc, clang, pcc
 - **hpux** gcc
 - **beos** gcc
 - **qnx** gcc
 - **android** gcc, gccarm
 - **vxworks** gcc, diab
 - **cygwin** gcc
 - **minix** clang, gcc
 - **aix** gcc
 - **sunos** gcc, sunpro
  
Licencia:  


  This program is free software; you can redistribute it and/or modify  
it under the terms of the GNU General Public License as published by  
the Free Software Foundation; either version 2 of the License, or  
\(at your option\) any later version.  
  
This program is distributed in the hope that it will be useful,  
but WITHOUT ANY WARRANTY; without even the implied warranty of  
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  
GNU General Public License for more details.  
  
You should have received a copy of the GNU General Public License  
along with this program; if not, write to the Free Software Foundation,  
Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.  
\(or visit their website at https://www.gnu.org/licenses/\).  
  
License extensions:  
  - This source code must be kept and distributed as part  
    of the Harbour package and/or the placement of the tool sources  
    and files must reflect that it is part of Harbour Project.  
  - Copyright information must always be presented by  
    projects including this tool or help text.  
  - Modified versions of the tool must clearly state this  
    fact on the copyright screen.  
  - Source code modifications shall always be made available  
    along with binaries.  
  - Help text and documentation is licensed under  
    Creative Commons Attribution-ShareAlike 4.0 International:  
    https://creativecommons.org/licenses/by-sa/4.0/  

  
Autor:  


 - Viktor Szakats 
