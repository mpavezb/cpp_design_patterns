project(interpreter)

# lexer_parser
add_executable(lexer_parser lexer_parser.cpp)
install(TARGETS lexer_parser DESTINATION Bahavioral/${PROJECT_NAME})
