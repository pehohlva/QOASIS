



function(Generate_PriFile arg1 arg2 filelist arg10)
	
	  string(TIMESTAMP PRODUCT_DEFAULT_BUILD_TIMESTAMP "%Y-%m-%dT%H:%M:%SZ" UTC)
	  set(LIBNAMECURRENT ${arg2})
	  set(DESTINATIONDIR ${arg1})
	  set(QTMODULEIN ${arg10})
	  set(NAMEPRIFILE ${arg2}_api.pri)
	  set(DESTINPRIFILE ${arg1}/${arg2}_api.pri)  
	  set(listVar "# ${NAMEPRIFILE} first line... ${PRODUCT_DEFAULT_BUILD_TIMESTAMP}  \n")
	  set(APPEND "# Copy this lib variable to qmake pro file or include this file. \n")
	  set(APPEND "# IF YOU WRITE INSIDE THIS FILE IS POSSIBEL BY NEXT GENERATING YOU LOST DATA \n")
	  string(APPEND listVar "# include(${NAMEPRIFILE}) detect qtlib ${DIR_LIBQT5}  Automatic generated file by cmake.. \n")
	  string(APPEND listVar "# Configuration to use STATIC_OR_SHARED LIB - api ending is shared only name static ${LIBNAMECURRENT} \n \n")
	  string(APPEND listVar "# require dir place of lib: ${DIR_LIBTARGET} \n")
	  string(APPEND listVar "QT += ${QTMODULEIN}   \n")
	  string(APPEND listVar "win32:LIBS += -luser32 \n")
	  string(APPEND listVar "mac:LIBS   += -lz \n")
	  string(APPEND listVar "unix:LIBS   += -lz  \n")
	  string(APPEND listVar "LIBS   += -L${DIR_LIBTARGET}  -l${LIBNAMECURRENT} \n")
	  string(APPEND listVar "#LIBS   += -L${DIR_LIBTARGET}  -l${LIBNAMECURRENT}_api \n")
	  string(APPEND listVar "INCLUDEPATH +=${DIR_LIBTARGET} \n") 
	  string(APPEND listVar "INCLUDEPATH +=${DIR_LIBTARGET} \n") 
	  string(APPEND listVar "message(\"CMAKE GENERATED FILE ${DESTINPRIFILE} default static DEFAULT STATIC SWAP IN THIS FILE IF NEED SHARED\")\n") 
	  
	  
  set(headerfilelist ${filelist})
  exec_program(pwd  OUTPUT_VARIABLE _PWD_)
  #set(${namepri} ${namepriValue} PARENT_SCOPE)
  set(${arg_c} ${arg_cValue} PARENT_SCOPE)
  #message(STATUS "MESSAGE: PREPARE to generate a prifile for qmake and app... inside dir ${_PWD_}")
  message(STATUS "MESSAGE Generate_PriFile: LIBNAME_STATIC_OR_SHARED ${LIBNAMECURRENT}")
  message(STATUS "MESSAGE: DSTDIR |${DESTINATIONDIR}| ")
  message(STATUS "MESSAGE: DSTDIRFROM_PRI_FILE |${DESTINPRIFILE}| ")
  # mkdir if not exist!
  file(MAKE_DIRECTORY ${DESTINATIONDIR})
  FOREACH(infileName ${headerfilelist})
  	set(HEADERstringFILE ${infileName}.h )
	set(HEADERsfile ${infileName} )
  	if (EXISTS ${HEADERstringFILE})
	  string(APPEND listVar "# require ${HEADERstringFILE} \n")
  	  get_filename_component(ITEM_PATH ${HEADERstringFILE} DIRECTORY)
	  string(APPEND listVar "INCLUDEPATH +=${ITEM_PATH} \n")
  	  MESSAGE( STATUS "PUBLICHEADER_OK: " ${HEADERstringFILE} - ${ITEM_PATH})
     endif()
	 
   	if (EXISTS ${HEADERsfile})
 	  string(APPEND listVar "# require ${HEADERsfile} \n")
   	  get_filename_component(ITEM_PATH ${HEADERsfile} DIRECTORY)
 	  string(APPEND listVar "INCLUDEPATH +=${ITEM_PATH} \n")
   	  MESSAGE( STATUS "PUBLICHEADER_OK: " ${HEADERsfile} - ${ITEM_PATH})
      endif()
  ENDFOREACH(infileName)
  
  file(WRITE ${DESTINPRIFILE} ${listVar})
  file(WRITE ${_PWD_}/${NAMEPRIFILE} ${listVar})
  
  
endfunction()



