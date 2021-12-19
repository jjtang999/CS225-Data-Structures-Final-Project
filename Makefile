EXENAME = main
OBJS = main.o graph.o DataParser.o

CXX = clang++
CXXFLAGS = $(CS225) -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lm

all : $(EXENAME)

output_msg: ; $(CLANG_VERSION_MSG)

$(EXENAME) : output_msg $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

#object file dependncies
main.o : graph/main.cpp graph/src/core/graph.cpp graph/include/core/graph.h parsing/DataParser.cpp parsing/DataParser.h
	$(CXX) $(CXXFLAGS) graph/main.cpp

graph.o : graph/src/core/graph.cpp graph/include/core/graph.h 
	$(CXX) $(CXXFLAGS) graph/src/core/graph.cpp

DataParser.o : parsing/DataParser.cpp parsing/DataParser.h
	$(CXX) $(CXXFLAGS) parsing/DataParser.cpp

# utility.o : utility.cpp utility.h
# 	$(CXX) $(CXXFLAGS) utility.cpp

# Custom Clang version enforcement Makefile rule:
# for using 'make test'
ccred=$(shell echo -e "\033[0;31m")
ccyellow=$(shell echo -e "\033[0;33m")
ccend=$(shell echo -e "\033[0m")

IS_EWS=$(shell hostname | grep "ews.illinois.edu")
IS_CORRECT_CLANG=$(shell clang -v 2>&1 | grep "version 6")
ifneq ($(strip $(IS_EWS)),)
ifeq ($(strip $(IS_CORRECT_CLANG)),)
CLANG_VERSION_MSG = $(error $(ccred) On EWS, please run 'module load llvm/6.0.1'. $(ccend))
endif
else
CLANG_VERSION_MSG = $(warning $(ccyellow) Looks like you are not on EWS. Be sure to test on EWS before the deadline. $(ccend))
endif

output_msg: ; $(CLANG_VERSION_MSG)

test: output_msg catch/catchmain.cpp graph/tests/test_graph.cpp graph/src/core/graph.cpp parsing/tests/test_parsing parsing/DataParser.cpp
	$(LD) catch/catchmain.cpp graph/tests/test_graph.cpp graph/src/core/graph.cpp parsing/tests/test_parsing parsing/DataParser.cpp $(LDFLAGS) -o test

.PHONY: output_msg