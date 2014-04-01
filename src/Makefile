OBJS = m2.o console.o envx.o para_list.o parser.o
TEST = pipex.o testpipe.o
TESTAPP = sender getter

CPPC = g++ -c

LD	 = g++

CPPFLAGS =  -O3

all: $(OBJS)
	$(LD) -o ashell $(OBJS) 
testpipe:$(TEST)
	$(LD) -o testpipe $(TEST)
	$(LD) -o sender sender.cpp
	$(LD) -o getter getter.cpp

pipex.o:pipex.cpp pipex.h pipe_api.h
	$(CPPC) pipex.cpp
testpipe.o:testpipe.cpp pipex.o
	$(CPPC) testpipe.cpp

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
	-rm ashell $(OBJS) $(TEST) testpipe $(TESTAPP)
