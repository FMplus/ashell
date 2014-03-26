OBJS = m2.o console.o envx.o para_list.o parser.o

CPPC = g++ -c

LD	 = g++

CPPFLAGS =  -O3

all: $(OBJS)
	$(LD) -o ashell $(OBJS) 
m2.o:m2.cpp console.o envx.o para_list.o parser.o 
	$(CPPC) m2.cpp $(CPPFLAGS)
console.o:console.cpp envx.o 
	$(CPPC) console.cpp $(CPPFLAGS)
envx.o:envx.cpp
	$(CPPC) envx.cpp $(CPPFLAGS)
para_list.o:para_list.cpp
	$(CPPC) para_list.cpp $(CPPFLAGS)
parser.o:parser.cpp para_list.o console.o envx.o
	$(CPPC) parser.cpp $(CPPFLAGS)
clean:
	-rm ashell $(OBJS)
