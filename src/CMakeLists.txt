file(GLOB SRCS "*.cpp")

link_libraries(cuttle-parser cuttle-translator cuttle-generator)

add_library(cuttle-lang SHARED ${SRCS})
