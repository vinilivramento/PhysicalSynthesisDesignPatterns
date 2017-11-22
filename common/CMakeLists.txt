#file(GLOB physicalsynthesisdesignpatterns_common_SRC
    #"*.hpp"
    #"*.cpp"
#)

#add_library(physicalsynthesisdesignpatterns_common ${physicalsynthesisdesignpatterns_common_SRC})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
#set_target_properties(physicalsynthesisdesignpatterns_common PROPERTIES LINKER_LANGUAGE CXX)
