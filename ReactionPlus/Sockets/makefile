include ../makefile.objs

OBJS = $(foreach obj, $(SOCKETS), $(obj).o)

.phony : Sockets


all : ../$(LIB_SO)

../$(LIB_SO) : $(OBJS)
	make -C ../


SocketEvents.o : SocketEvents.cpp SocketEvents.hpp Socket.hpp ../Exception.hpp ../Exec/SignalEvents.hpp
	g++ $(FLAGS) -c -o SocketEvents.o SocketEvents.cpp

Socket.o : Socket.cpp Socket.hpp ../Exception.hpp
	g++ $(FLAGS) -c -o Socket.o Socket.cpp

SocketReader.o : SocketReader.cpp SocketReader.hpp ../DOS/Reader.hpp
	g++ $(FLAGS) -c -o SocketReader.o SocketReader.cpp

SocketWriter.o : SocketWriter.cpp SocketWriter.hpp ../DOS/Writer.hpp
	g++ $(FLAGS) -c -o SocketWriter.o SocketWriter.cpp

Packet.o : Packet.cpp Packet.hpp SocketReader.hpp SocketWriter.hpp
	g++ $(FLAGS) -c -o Packet.o Packet.cpp


Sockets : $(OBJS)


# clean up

clean:
	delete *.(o|ii|s)

