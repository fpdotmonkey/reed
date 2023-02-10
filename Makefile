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
  -I./3rd/CuraEngine/include/ \
  -Wall -Wextra -Wpedantic -Werror \
  #

LDFLAGS:=\
  #

LDLIBS:=\
  -L./3rd/CuraEngine/build/Debug/lib_CuraEngine.a \
  -fprofile-arcs \
  #

CMAKE_BIN:=~/.local/share/cmake-3.25.2-linux-x86_64/bin/cmake
CPU_COUNT:=$(shell grep -c ^processor /proc/cpuinfo)

HEADERS=$(wildcard $(SOURCE_DIRECTORY)/*.h)
SOURCES=$(wildcard $(SOURCE_DIRECTORY)/*.cxx)
OBJECTS=$(patsubst \
  $(SOURCE_DIRECTORY)/%.cxx, $(BUILD_DIRECTORY)/%.o, $(SOURCES))
DEPENDENCIES=$(OBJECTS:.o=.d)
EXECUTABLE:=$(BUILD_DIRECTORY)/reed

.PHONY: all
all: build

.PHONY: build
build: 3rd/CuraEngine/build/Debug/lib_CuraEngine.a $(EXECUTABLE)

.ONESHELL:
3rd/CuraEngine/build/Debug/lib_CuraEngine.a: .git/modules/3rd/CuraEngine/HEAD
	cd ./3rd/CuraEngine/
	pip install conan --upgrade
	conan config install https://github.com/ultimaker/conan-config.git
	conan profile new default --detect --force
	conan install . --build=missing --update -s build_type=Debug
	$(CMAKE_BIN) --preset debug
	$(CMAKE_BIN) --build --preset debug

.PHONY: clean
clean:
	rm -rf build/ 3rd/CuraEngine/build

.PHONY: open-doc
doc-open: doc
	xdg-open build/doc/html/index.html

.PHONY: doc
doc: build/doc/ Doxyfile .git/modules/3rd/CuraEngine/HEAD $(HEADERS)
	cd build/doc && doxygen ../../Doxyfile

$(BUILD_DIRECTORY)/%.o: $(SOURCE_DIRECTORY)/%.cxx build/
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(LDFLAGS) $^ -o $@ $(LDLIBS)

build/:
	mkdir $@

build/doc: build/
	mkdir $@
