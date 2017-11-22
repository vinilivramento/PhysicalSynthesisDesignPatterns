add_subdirectory(command)

add_library(physicalsynthesisdesignpatterns_behavioral ${SOURCE})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/command/)

