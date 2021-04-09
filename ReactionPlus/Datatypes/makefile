include ../makefile.objs

OBJS = $(foreach obj, $(DATATYPES), $(obj).o)

.phony : Datatypes


all : ../$(LIB_DA)

../$(LIB_DA) : $(OBJS)
	$(MAKE) -C ../


Datatypes.o : Datatypes.cpp Datatypes.hpp ../DOS/File.hpp
	g++ $(FLAGS) -c -o Datatypes.o Datatypes.cpp

Picture.o : Picture.cpp Picture.hpp Datatypes.hpp ../DOS/DOS.hpp ../DOS/File.hpp
	g++ $(FLAGS) -c -o Picture.o Picture.cpp

Datatypes : $(OBJS)


# clean up

clean:
	delete *.(o|ii|s)

