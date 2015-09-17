## Options

# General Options
OPTION(LIBCHAOS_SHARED                      "Build LibChaos as a shared library"        OFF )
OPTION(IBERTY_DEMANGLE                      "Use libiberty to demangle symbols"         OFF )

# Library Components
OPTION(LIBCHAOS_EXTERN                      "Build LibChaos with External Libraries"    ON  )
OPTION(LIBCHAOS_UI                          "Build LibChaos UI library"                 OFF )
OPTION(LIBCHAOS_TEST                        "Build and Run LibChaos Test suite"         ON  )
OPTION(LIBCHAOS_UTIL                        "Build LibChaos Utilities"                  OFF )

# ZParcel Tool
OPTION(LIBCHAOS_ZPARCEL                     "Build ZParcel tool"                        OFF )

# Extern Library Support
OPTION(DISABLE_ZPNG                         "Disable PNG support"                       OFF )
OPTION(DISABLE_ZJPEG                        "Disable JPEG support"                      OFF )
OPTION(DISABLE_ZWEBP                        "Disable WebP support"                      OFF )
OPTION(DISABLE_ZH264                        "Disable H264 support"                      OFF )

# Util Executables
OPTION(LIBCHAOS_UTIL_EXTENSION_FIXER        "Build LibChaos Extension Fixer"            OFF )
OPTION(LIBCHAOS_UTIL_AUDIOBOOK_SORTER       "Build LibChaos Audiobook Sorter"           OFF )
OPTION(LIBCHAOS_UTIL_DUPLICATE_FINDER       "Build LibChaos Duplicate Finder"           OFF )
OPTION(LIBCHAOS_UTIL_IMAGE_DOWNLOADER       "Build LibChaos Image Downloader"           OFF )
OPTION(LIBCHAOS_UTIL_IMAGE_LIBRARY_MANAGER  "Build LibChaos Image Library Manager"      OFF )
OPTION(LIBCHAOS_UTIL_IMAGE_REVERSE_SEARCH   "Build LibChaos Image Reverse Search"       OFF )

# All Extra Targets Excluded from All
IF(LIBCHAOS_EXTERN)
    SET(LIBCHAOS_EXTERN_ALL)
ELSE()
    SET(LIBCHAOS_EXTERN_ALL     EXCLUDE_FROM_ALL)
ENDIF()

IF(LIBCHAOS_UI)
    SET(LIBCHAOS_UI_ALL)
ELSE()
    SET(LIBCHAOS_UI_ALL         EXCLUDE_FROM_ALL)
ENDIF()

IF(LIBCHAOS_TEST)
    SET(LIBCHAOS_TEST_ALL)
ELSE()
    SET(LIBCHAOS_TEST_ALL       EXCLUDE_FROM_ALL)
ENDIF()

IF(LIBCHAOS_UTIL)
    SET(LIBCHAOS_UTIL_ALL)
ELSE()
    SET(LIBCHAOS_UTIL_ALL       EXCLUDE_FROM_ALL)
ENDIF()

IF(LIBCHAOS_ZPARCEL)
    SET(LIBCHAOS_ZPARCEL_ALL)
ELSE()
    SET(LIBCHAOS_ZPARCEL_ALL    EXCLUDE_FROM_ALL)
ENDIF()