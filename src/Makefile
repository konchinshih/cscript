DEBUGFLAGS += -DDEBUG -g -fsanitize=address,undefined
CXXFLAGS +=

.PHONY: all clean

all: *.c *.h
	gcc -o ../cscript $(CXXFLAGS) $^

debug: *.c *.h
	gcc -o ../cscript $(CXXFLAGS) $(DEBUGFLAGS) $^

clean:
	rm ../cscript


