# Find the f2py program, which comes as part of NumPy.
#
# This code sets the following variables:
#
#  F2PY_EXECUTABLE
#  F2py_FOUND
#  F2PY_VERSION
#  F2PY_VERSION_MAJOR
#  F2PY_VERSION_MINOR
#  F2PY_VERSION_MICRO
#
# This code uses the following variables
#
#  DEPS_BIN_HINTS
#


find_package(Numpy)

find_program(F2PY_EXECUTABLE f2py ${DEPS_BIN_HINTS})
if(NOT F2PY_EXECUTABLE)
  if(${PYTHON_VERSION_MAJOR} GREATER 2)
    find_program(F2PY_EXECUTABLE3 f2py3 ${DEPS_BIN_HINTS})
    if(F2PY_EXECUTABLE3)
      set(F2PY_EXECUTABLE ${F2PY_EXECUTABLE3})
    endif(F2PY_EXECUTABLE3)
  elseif(${PYTHON_VERSION_MAJOR} LESS 3)
    # because arch is dumb
    find_program(F2PY_EXECUTABLE2 f2py2 ${DEPS_BIN_HINTS})
    if(F2PY_EXECUTABLE2)
      set(F2PY_EXECUTABLE ${F2PY_EXECUTABLE2})
    endif(F2PY_EXECUTABLE2)
  endif(${PYTHON_VERSION_MAJOR} GREATER 2)
endif(NOT F2PY_EXECUTABLE)

if(F2PY_EXECUTABLE)
  SET(F2py_FOUND TRUE)

  # get the version string
  execute_process(COMMAND "${F2PY_EXECUTABLE}" "-v"
                  OUTPUT_VARIABLE F2PY_VERSION_RTN
                  OUTPUT_STRIP_TRAILING_WHITESPACE)
  string(REPLACE " " ";" F2PY_VERSION_RTN_LIST ${F2PY_VERSION_RTN})
  list(GET F2PY_VERSION_RTN_LIST -1 F2PY_VERSION)
  string(REPLACE "." ";" F2PY_VERSION_LIST ${F2PY_VERSION})
  list(LENGTH F2PY_VERSION_LIST F2PY_VERSION_N)
  list(GET F2PY_VERSION_LIST 0 F2PY_VERSION_MAJOR)
  if(F2PY_VERSION_N GREATER 1)
    list(GET F2PY_VERSION_LIST 1 F2PY_VERSION_MINOR)
  else(F2PY_VERSION_N GREATER 1)
    set(F2PY_VERSION_MINOR 0)
  endif(F2PY_VERSION_N GREATER 1)
  if(F2PY_VERSION_N GREATER 2)
    list(GET F2PY_VERSION_LIST 2 F2PY_VERSION_MICRO)
  else(F2PY_VERSION_N GREATER 2)
    set(F2PY_VERSION_MICRO 0)
  endif(F2PY_VERSION_N GREATER 2)
else()
  SET(F2py_FOUND FALSE)
endif()

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(F2py REQUIRED_VARS F2PY_EXECUTABLE)

mark_as_advanced(F2PY_EXECUTABLE)
