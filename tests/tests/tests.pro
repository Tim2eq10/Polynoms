CONFIG += console c++17

# sources for test project
SOURCES += \
    main.cpp

# includepath for main project
INCLUDEPATH += "../../"

# sources from main project
SOURCES += \
    ../../src/tables/hasher.cpp \
    ../../src/polynoms/Monom.cpp \
    ../../src/polynoms/Polynom.cpp

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

HEADERS += \
    tables_tests.h
