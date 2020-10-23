CPPFLAGS := -m64 -Wall -std=c++17 -pthread
BIN := crs
LIBBIN := lib$(BINARY)
MACROS :=
INCDIR := -I include/
LIBS := -lm
SRCS :=
TEST := test/main.cpp
MKDIR :=

ifeq ($(OS),Windows_NT)
 CPP := g++
 BIN :=  $(strip $(BINARY)).exe
 LIBBIN := $(strip $(LIBBIN)).dll
 MACROS += -D _CRT_SECURE_NO_WARNINGS -D NDEBUG
 SRCS += $(shell Get-Childitem –Path C:\ -Include *.cpp -File)
 MKDIR := New-Item -ItemType Directory -Force -Path bin/
 else
 CPP := clang++
 LIBBIN := $(strip $(LIBBIN)).so
 MACROS += -D NDEBUG
 SRCS += $(shell find . -name "*.cpp")
 MKDIR = mkdir -p bin/
endif

.PHONY: all test export clean

all: debug

prerequisite:
	$(shell $(MKDIR))

debug: prerequisite
	$(CPP) -g $(CPPFLAGS) $(MACROS) \
	$(INCDIR) $(LIBS) \
	$(TEST) -o bin/$(BIN)

test: prerequisite
	$(CPP) -O3 $(CPPFLAGS) $(MACROS) \
	$(INCDIR) $(LIBS) \
	$(TEST) -o bin/$(BIN)
