include ../makefile.objs

OBJS = $(foreach obj, $(PREFS), $(obj).o)

.phony : Prefs


all : ../$(LIB_PR)

../$(LIB_PR) : $(OBJS)
	make -C ../


Prefs.o : Prefs.cpp Prefs.hpp ../IFFParse/IFF.hpp
	g++ $(FLAGS) -c -o Prefs.o Prefs.cpp

WBPattern.o : WBPattern.cpp WBPattern.hpp Prefs.hpp ../InvalidStateException.hpp ../DOS/File.hpp
	g++ $(FLAGS) -c -o WBPattern.o WBPattern.cpp

Prefs : $(OBJS)


# clean up

clean:
	delete *.(o|ii|s)

