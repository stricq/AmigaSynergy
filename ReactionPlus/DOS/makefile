include ../makefile.objs

OBJS = $(foreach obj, $(DOS), $(obj).o)

.phony : DOS


all : ../$(LIB_DO)

../$(LIB_DO) : $(OBJS)
	$(MAKE) -C ../


FileNotFoundException.hpp : ../Exception.hpp

DOS.o : DOS.cpp DOS.hpp File.hpp
	g++ $(FLAGS) -c -o DOS.o DOS.cpp

DateTime.o : DateTime.cpp DateTime.hpp ../InvalidStateException.hpp
	g++ $(FLAGS) -c -o DateTime.o DateTime.cpp

File.o : File.cpp File.hpp FileNotFoundException.hpp ../InvalidStateException.hpp
	g++ $(FLAGS) -c -o File.o File.cpp

Reader.o : Reader.cpp Reader.hpp
	g++ $(FLAGS) -c -o Reader.o Reader.cpp

Writer.o : Writer.cpp Writer.hpp
	g++ $(FLAGS) -c -o Writer.o Writer.cpp

FileReader.o : FileReader.cpp FileReader.hpp File.hpp Reader.hpp FileNotFoundException.hpp IOException.hpp ../IndexRangeException.hpp
	g++ $(FLAGS) -c -o FileReader.o FileReader.cpp

FileWriter.o : FileWriter.cpp FileWriter.hpp File.hpp Writer.hpp FileNotFoundException.hpp IOException.hpp ../IndexRangeException.hpp
	g++ $(FLAGS) -c -o FileWriter.o FileWriter.cpp

BufferedReader.o : BufferedReader.cpp BufferedReader.hpp Reader.hpp ../IndexRangeException.hpp
	g++ $(FLAGS) -c -o BufferedReader.o BufferedReader.cpp

BufferedWriter.o : BufferedWriter.cpp BufferedWriter.hpp Writer.hpp ../IndexRangeException.hpp
	g++ $(FLAGS) -c -o BufferedWriter.o BufferedWriter.cpp

DOS : $(OBJS)


# clean up

clean:
	delete *.(o|ii|s)

