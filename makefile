SRC_FILES := $(wildcard src/*.cc)
OBJ_FILES := $(addprefix obj/,$(notdir $(SRC_FILES:.cc=.o)))
CXX := g++
DEBUG := -g
CFLAGS := -Wall -c -std=c++11 $(DEBUG)
LFLAGS := -Wall $(DEBUG)

interpreter: $(OBJ_FILES)
	$(CXX) $(LFLAGS) -o $@ $^

obj/%.o: src/%.cc
	$(CXX) $(CFLAGS) -o $@ $<

Token: obj/Token.o
Lexer: obj/Lexer.o
Interpreter: obj/Interpreter.o

clean:
	\rm $(OBJ_FILES) interpreter
