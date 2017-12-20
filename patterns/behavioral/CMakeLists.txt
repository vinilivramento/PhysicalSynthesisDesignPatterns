file(GLOB behavioral_patterns_SRC 
    "*.hpp"
    "*.cpp"
)

add_library(physicalsynthesisdesignpatterns_behavioral ${behavioral_patterns_SRC})

