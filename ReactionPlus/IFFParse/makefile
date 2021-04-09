include ../makefile.objs

OBJS = $(foreach obj, $(IFFPARSE), $(obj).o)

.phony : IFFParse


all : ../$(LIB_IF)

../$(LIB_IF) : $(OBJS)
	$(MAKE) -C ../


IFF.o : IFF.cpp IFF.hpp ../InvalidStateException.hpp
	g++ $(FLAGS) -c -o IFF.o IFF.cpp

IFFDOS.o : IFFDOS.cpp IFFDOS.hpp IFF.hpp ../InvalidStateException.hpp ../DOS/FileNotFoundException.hpp
	g++ $(FLAGS) -c -o IFFDOS.o IFFDOS.cpp

IFFClipboard.o : IFFClipboard.cpp IFFClipboard.hpp IFF.hpp ../Exception.hpp ../DOS/IOException.hpp
	g++ $(FLAGS) -c -o IFFClipboard.o IFFClipboard.cpp

IFFParse : $(OBJS)


# clean up

clean:
	delete *.(o|ii|s)

