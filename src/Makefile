OBJS = m2.o console.o envx.o para_list.o parser.o

all: $(OBJS)
	g++ -o ashell $(OBJS)
m2.o:m2.cpp console.o envx.o para_list.o parser.o 
	g++ -c m2.cpp
console.o:console.cpp envx.o
	g++ -c console.cpp
envx.o:envx.cpp
	g++ -c envx.cpp
para_list.o:para_list.cpp
	g++ -c para_list.cpp
parser.o:parser.cpp para_list.o console.o envx.o
	g++ -c parser.cpp
clean:
	-rm ashell $(OBJS)
