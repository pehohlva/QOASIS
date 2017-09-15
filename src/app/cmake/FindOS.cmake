# access over console to speeach on various OS.
# QNX
if (QNXNTO)
    exec_program(uname ${PWD} OUTPUT_VARIABLE SAYUNAME)
	add_definitions(-DUNIXCONSOLE_OPEN)
endif()
if(APPLE)
    exec_program(uname ${PWD} OUTPUT_VARIABLE SAYUNAME)
	add_definitions(-DUNIXCONSOLE_OPEN)
endif()
if(UNIX AND NOT APPLE)
    exec_program(uname ${PWD} OUTPUT_VARIABLE SAYUNAME)
	add_definitions(-DUNIXCONSOLE_OPEN)
endif()

if(SAYUNAME MATCHES "(Darw*)")
message(STATUS "OS MAC Based: ${SAYUNAME}")
add_definitions(-DDARWINOS_DETECT)
add_definitions(-DUNIXCONSOLE_OPEN)
endif()

if(MSVS OR MSYS OR MINGW)
    set(SAYUNAME "WINDOWOS_")
	# detect WINE run cmd vol give 0000-0000
	# window have also way to speech access registry
	add_definitions(-DUNIXCONSOLE_CLOSE)
endif()