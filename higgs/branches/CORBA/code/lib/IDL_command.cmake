MACRO (MacroGenerateIDL)
	IF(NOT IDL_COMPILER)
		SET(IDL_COMPILER tao_idl)
	ENDIF(NOT IDL_COMPILER)
	IF(NOT IDL_DIR)
		SET(IDL_DIR ../../idl)
	ENDIF(NOT IDL_DIR)
	FOREACH(_in_FILE ${ARGN})
		GET_FILENAME_COMPONENT(_base_FILE ${_in_FILE} NAME_WE)
		ADD_CUSTOM_COMMAND(
			OUTPUT ${_base_FILE}S.h ${_base_FILE}S.cpp ${_base_FILE}S.inl ${_base_FILE}C.h ${_base_FILE}C.cpp ${_base_FILE}C.inl
			MAIN_DEPENDENCY ${IDL_DIR}/${_base_FILE}.idl
			COMMAND ${IDL_COMPILER} -I${IDL_DIR} ${IDL_DIR}/${_base_FILE}.idl
			)
	ENDFOREACH(_in_FILE ${ARGN})
ENDMACRO (MacroGenerateIDL)
