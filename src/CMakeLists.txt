file(GLOB SRCS "*.cpp")

link_libraries(cuttle-parser cuttle-translator cuttle-generator cuttle-vm)

add_library(cuttle-lang SHARED ${SRCS})
