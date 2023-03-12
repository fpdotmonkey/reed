CXX=g++
SOURCE_DIRECTORY:=source
BUILD_DIRECTORY:=build

CPPFLAGS:=\
        -MMD \
        -MP \
        #

CXXFLAGS:=\
        -x c++ \
        -std=gnu++20 \
        -Og -g3 \
        -I./$(SOURCE_DIRECTORY) \
        -Wall -Wextra -Wpedantic -Werror \
        #

LDFLAGS:=\
        #

LDLIBS:=\
        #

CPU_COUNT:=$(shell grep -c ^processor /proc/cpuinfo)

HEADERS=$(wildcard $(SOURCE_DIRECTORY)/*.h)
SOURCES= $(wildcard $(SOURCE_DIRECTORY)/*.cxx)
OBJECTS=$(patsubst \
        $(SOURCE_DIRECTORY)/%.cxx, $(BUILD_DIRECTORY)/%.o, $(SOURCES))
DEPENDENCIES=$(OBJECTS:.o=.d)
EXECUTABLE:=$(BUILD_DIRECTORY)/reed

.PHONY: all
all: build/ build

.PHONY: build
build: $(EXECUTABLE)

.PHONY: clean
clean:
	rm -rf \
		build/ \
		#

.PHONY: open-doc
doc-open: doc
	xdg-open build/doc/html/index.html

.PHONY: doc
doc: build/doc Doxyfile $(HEADERS)
	cd build/doc && doxygen ../../Doxyfile

$(BUILD_DIRECTORY)/%.o: $(SOURCE_DIRECTORY)/%.cxx
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(LDFLAGS) $^ -o $@ $(LDLIBS)

build/:
	mkdir $@

build/doc: build/
	mkdir $@

-include $(DEPENDENCIES)
