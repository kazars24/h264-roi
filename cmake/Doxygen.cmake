
FIND_PACKAGE(Doxygen)
IF(DOXYGEN_FOUND)
    IF(LIBCHAOS_DOXYGEN)
        SET(DOXYGEN_AUTO ALL)
    ENDIF()

    # General Doxygen Options
    SET(DOXYGEN_INPUT ${CMAKE_SOURCE_DIR})
    SET(DOXYGEN_OUTPUT ${CMAKE_BINARY_DIR})
    SET(DOXYGEN_VERSION ${LIBCHAOS_DESCRIBE})
    IF(DEBUG)
        SET(DOXYGEN_DEBUG "YES")
    ELSE()
        SET(DOXYGEN_DEBUG "NO")
    ENDIF()

    # Build Compressed HTML on Windows
    INCLUDE(cmake/FindHTMLHelp.cmake)
    IF(HTML_HELP_COMPILER)
        SET(DOXYGEN_HHC ${HTML_HELP_COMPILER})
        CONFIGURE_FILE("${CMAKE_SOURCE_DIR}/doc/Doxyfile-help.in" "${CMAKE_BINARY_DIR}/Doxyfile-help" @ONLY)
        ADD_CUSTOM_TARGET(doxyhelp ${DOXYGEN_AUTO}
            DEPENDS ${LibChaos_ALL_FILES}
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMAND ${DOXYGEN_EXECUTABLE} "${CMAKE_BINARY_DIR}/Doxyfile-help"
            COMMAND ${CMAKE_COMMAND} -E rename chm/LibChaos.chm LibChaos.chm
        )
    ENDIF()

    # Build Normal HTML
    CONFIGURE_FILE("${CMAKE_SOURCE_DIR}/doc/Doxyfile.in" "${CMAKE_BINARY_DIR}/Doxyfile" @ONLY)
    ADD_CUSTOM_TARGET(doxygen ${DOXYGEN_AUTO}
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMAND ${DOXYGEN_EXECUTABLE} "${CMAKE_BINARY_DIR}/Doxyfile"
    )
ENDIF()
