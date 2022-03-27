TARGET = dancing_event_simulator

TEMPLATE = subdirs

QMAKE_CXXFLAGS += -std=c++17

SUBDIRS += application \
    library \
    test

application.subdir = src/application
library.subdir  = src/library
test.subdir  = src/test

application.depends = library
test.depends = library
