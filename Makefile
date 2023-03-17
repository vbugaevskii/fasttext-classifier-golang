DEPS_FASTTEXT_HEADERS=./deps/fastText/src
DEPS_FASTTEXT_LIBS=./deps/fastText/build

srcfasttext = $(wildcard ${DEPS_FASTTEXT_HEADERS}/*.cc ${DEPS_FASTTEXT_HEADERS}/*.h)
libfasttext = ${DEPS_FASTTEXT_LIBS}/libfasttext.a ${DEPS_FASTTEXT_LIBS}/libfasttext.so.0

.PHONY: all clean build-fasttext-go build-fasttext-cpp build-fasttext-native

#BUILD FASTTEXT LIBRARIES

$(libfasttext): $(srcfasttext)
	cd deps/fastText ; \
	rm -r build || true ; \
	mkdir build && cd build && cmake .. ; \
	make

#BUILD FASTTEXT GO:

bin/fasttext_go: $(libfasttext) cmd/main.go pkg/fasttext/*
	go build -o bin/fasttext_go cmd/main.go

build-fasttext-go: bin/fasttext_go

#BUILD FASTTEXT CPP

bin/fasttext_cpp: $(libfasttext) cpp/main.cpp pkg/fasttext/*.cpp pkg/fasttext/*.h
	g++ -o bin/fasttext_cpp cpp/main.cpp pkg/fasttext/*.cpp \
		-I./pkg/ \
		-I${DEPS_FASTTEXT_HEADERS} -L${DEPS_FASTTEXT_LIBS} -lfasttext

build-fasttext-cpp: bin/fasttext_cpp

#BUILD FASTTEXT NATIVE

bin/fasttext_native: $(libfasttext) cpp/util.cpp
	g++ -o bin/fasttext_native cpp/util.cpp -I${DEPS_FASTTEXT_HEADERS} -L${DEPS_FASTTEXT_LIBS} -lfasttext

build-fasttext-native: bin/fasttext_native

#OTHER TARGETS

all: bin/fasttext_go bin/fasttext_cpp bin/fasttext_native

clean:
	rm -r deps/fastText/build bin/*
