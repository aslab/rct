# @author Francisco Jesús Arjonilla
# Last Change: Thu Feb 17 06:00 PM 2011 C
# Busca el Doxygen
INCLUDE( FindDoxygen )
# Comprueba si lo ha encontrado, si no no hace nada (no da error)
IF (DOXYGEN_EXECUTABLE)
	# Avisa de que lo ha encontrado
	MESSAGE(STATUS " Setting Doxygen Generator " )
	# Define la nueva salida "doc" como resultado de ejecutar Doxygen sobre el
	# directorio actual (Doxygen debe de estar perfectamente configurado)
	ADD_CUSTOM_TARGET(
		doc
		COMMAND ${DOXYGEN_EXECUTABLE}
		VERBATIM)
ENDIF(DOXYGEN_EXECUTABLE)

