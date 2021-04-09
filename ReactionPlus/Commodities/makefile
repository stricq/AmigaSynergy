include ../makefile.objs

OBJS = $(foreach obj, $(COMMODITIES), $(obj).o)

.phony : Commodities


all : ../$(LIB_CO)

../$(LIB_CO) : $(OBJS)
	$(MAKE) -C ../


Commodity.o : Commodity.cpp Commodity.hpp CommodityMessage.hpp CommodityException.hpp ../Exec/SignalEvents.hpp
	g++ $(FLAGS) -c -o Commodity.o Commodity.cpp

CommodityMessage.o : CommodityMessage.cpp CommodityMessage.hpp CommodityException.hpp ../Exec/MessagePort.hpp
	g++ $(FLAGS) -c -o CommodityMessage.o CommodityMessage.cpp

Commodities : $(OBJS)


# clean up

clean:
	delete *.(o|ii|s)

