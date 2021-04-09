include ../makefile.objs

OBJS = $(foreach obj, $(LOCALE), $(obj).o)

.phony : Locale


all : ../$(LIB_LO)

../$(LIB_LO) : $(OBJS)
	$(MAKE) -C ../


Locale.o : Locale.cpp Locale.hpp ../InvalidArgumentException.hpp
	g++ $(FLAGS) -c -o Locale.o Locale.cpp

Locale : $(OBJS)


# clean up

clean:
	delete *.(o|ii|s)

