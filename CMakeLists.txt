include( FindDoxygen )
set( VERSION "0.1.28" )
option( HAVE_TUT ON )
add_custom_target( unit )
add_subdirectory( wibble )
add_subdirectory( doc )
