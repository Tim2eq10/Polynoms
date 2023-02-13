set(target ${MP2_CUSTOM})

file(GLOB hdrs "*.h*")
file(GLOB srcs "*.cpp")

add_executable(${target} ${srcs} ${hdrs})
