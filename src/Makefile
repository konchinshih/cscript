DEBUGFLAGS += -DDEBUG -g -fsanitize=address,undefined
CXXFLAGS +=

.PHONY: all clean

all: ../cscript

../cscript: *.c *.h
	gcc -o $@ $(CXXFLAGS) $^

clean:
	rm ../cscript


