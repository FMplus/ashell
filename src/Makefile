OBJS = m2.o console.o envx.o para_list.o parser.o

CPPC = g++ -c

LD	 = g++

CPPFLAGS =  

all: $(OBJS)
	$(LD) -o ashell $(OBJS)
m2.o:m2.cpp console.o envx.o para_list.o parser.o 
	$(CPPC) m2.cpp
console.o:console.cpp envx.o
	$(CPPC) console.cpp
envx.o:envx.cpp
	$(CPPC) envx.cpp
para_list.o:para_list.cpp
	$(CPPC) para_list.cpp
parser.o:parser.cpp para_list.o console.o envx.o
	$(CPPC) parser.cpp
clean:
	-rm ashell $(OBJS)
