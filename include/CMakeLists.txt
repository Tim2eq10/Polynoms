set(target ${MP2_INCLUDE})

file(GLOB hdrs "*.h*")

add_custom_target(${target} SOURCES ${hdrs})
