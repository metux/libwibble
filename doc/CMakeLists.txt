add_custom_command(
  DEPENDS wibble ${CMAKE_CURRENT_BINARY_DIR}/wibble.dox
  OUTPUT doc-stamp
  COMMAND ${DOXYGEN} wibble.dox && touch doc-stamp )

add_custom_target( doc DEPENDS doc-stamp )

configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/wibble.dox.in
  ${CMAKE_CURRENT_BINARY_DIR}/wibble.dox @ONLY IMMEDIATE )
