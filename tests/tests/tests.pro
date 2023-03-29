CONFIG += console c++17

HEADERS += \
    ../../include/tables/connector.h \
    ../../include/tables/hasher.h \
    ../../include/tables/hashmap_chains.h \
    ../../include/tables/sorted_array.h \
    ../../include/tables/unsorted_array.h \
    ../../include/tables/unsorted_list.h \
    ../../include/polynoms/Monom.h \
    ../../include/polynoms/Polynom.h


SOURCES += \
    ../../src/tables/connector.cpp \
    ../../src/tables/hasher.cpp \
    ../../src/tables/hashmap_chains.cpp \
    ../../src/tables/sorted_array.cpp \
    ../../src/tables/unsorted_array.cpp \
    ../../src/tables/unsorted_list.cpp \
    ../../src/polynoms/Monom.cpp \
    ../../src/polynoms/Polynom.cpp

# sources for test project
SOURCES += \
    main.cpp




# includepath for main project
INCLUDEPATH += "../../"

# includepath for gtest-framework
INCLUDEPATH += "gtest/include/"
INCLUDEPATH += "gtest/"

# sources for gtest-framework
SOURCES += \
    gtest/src/gtest.cc \
    gtest/src/gtest-all.cc \
    gtest/src/gtest-assertion-result.cc \
    gtest/src/gtest-death-test.cc \
    gtest/src/gtest-filepath.cc \
    gtest/src/gtest-matchers.cc \
    gtest/src/gtest-port.cc \
    gtest/src/gtest-printers.cc \
    gtest/src/gtest-test-part.cc \
    gtest/src/gtest-typed-test.cc
