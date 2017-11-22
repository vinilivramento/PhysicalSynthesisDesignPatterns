set(SOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
   )

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_executable( run_tests ${SOURCE} )
target_link_libraries( run_tests physicalsynthesisdesignpatterns_creational physicalsynthesisdesignpatterns_behavioral )

