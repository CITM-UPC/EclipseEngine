#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "lcms2::lcms2" for configuration "Release"
set_property(TARGET lcms2::lcms2 APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(lcms2::lcms2 PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/lcms2.lib"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/lcms2.dll"
  )

list(APPEND _cmake_import_check_targets lcms2::lcms2 )
list(APPEND _cmake_import_check_files_for_lcms2::lcms2 "${_IMPORT_PREFIX}/lib/lcms2.lib" "${_IMPORT_PREFIX}/bin/lcms2.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
