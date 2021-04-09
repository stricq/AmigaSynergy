include ../makefile.objs

OBJS = $(foreach obj, $(INTUITION), $(obj).o)

.phony : Intuition


all : ../$(LIB_IN)

../$(LIB_IN) : $(OBJS)
	make -C ../


IntuitionBase.o : IntuitionBase.cpp IntuitionBase.hpp Screen.hpp Point.hpp
	g++ $(FLAGS) -c -o IntuitionBase.o IntuitionBase.cpp

Screen.o : Screen.cpp Screen.hpp Rectangle.hpp Point.hpp ../InvalidArgumentException.hpp
	g++ $(FLAGS) -c -o Screen.o Screen.cpp

Pointer.o : Pointer.cpp Pointer.hpp
	g++ $(FLAGS) -c -o Pointer.o Pointer.cpp

Intuition : $(OBJS)


# clean up

clean:
	delete *.(o|ii|s)

