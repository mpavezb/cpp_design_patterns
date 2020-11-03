project(visitor)

# intrusive visitor
add_executable(intrusive_visitor intrusive_visitor.cpp)
install(TARGETS intrusive_visitor DESTINATION Behavioral/${PROJECT_NAME})

# reflective visitor
add_executable(reflective_visitor reflective_visitor.cpp)
install(TARGETS reflective_visitor DESTINATION Behavioral/${PROJECT_NAME})

# double_dispatch visitor
add_executable(double_dispatch_visitor double_dispatch_visitor.cpp)
install(TARGETS double_dispatch_visitor DESTINATION Behavioral/${PROJECT_NAME})

# acyclic visitor
add_executable(acyclic_visitor acyclic_visitor.cpp)
install(TARGETS acyclic_visitor DESTINATION Behavioral/${PROJECT_NAME})

# multimethod visitor
add_executable(multimethod_visitor multimethod_visitor.cpp)
install(TARGETS multimethod_visitor DESTINATION Behavioral/${PROJECT_NAME})

# std_variant visitor
add_executable(std_variant_visitor std_variant_visitor.cpp)
install(TARGETS std_variant_visitor DESTINATION Behavioral/${PROJECT_NAME})
