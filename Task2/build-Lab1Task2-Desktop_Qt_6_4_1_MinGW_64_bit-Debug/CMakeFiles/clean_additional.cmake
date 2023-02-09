# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Lab1Task2_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Lab1Task2_autogen.dir\\ParseCache.txt"
  "Lab1Task2_autogen"
  )
endif()
