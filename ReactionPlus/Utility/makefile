include ../makefile.objs

OBJS = $(foreach obj, $(UTILITY), $(obj).o)

.phony : Utility


all : ../$(LIB)

../$(LIB) : $(OBJS)
	make -C ../


ParseException.o : ParseException.cpp ParseException.hpp ../Exception.hpp
	g++ $(FLAGS) -c -o ParseException.o ParseException.cpp

ParseLine.o : ParseLine.cpp ParseLine.hpp
	g++ $(FLAGS) -c -o ParseLine.o ParseLine.cpp

Configuration.o : Configuration.cpp Configuration.hpp ParseLine.hpp ParseException.hpp
	g++ $(FLAGS) -c -o Configuration.o Configuration.cpp

Utility : $(OBJS)


# clean up

clean:
	delete *.(o|ii|s)

