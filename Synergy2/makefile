
EXE = asynergyc
OBJS = synergyc.o Command.o InputInjector.o
FLAGS = -Wall -Wextra -mcrt=newlib -ggdb -Os -I. -I/RAPlus
LIBS  = -mcrt=newlib -L/RAPlus -lm -liffparse -lintuition -lcommodities -lexec -lsockets -ldos -lraplus -lraauto -lauto
EXTRA = -Wl,-Ttext,0

all : $(EXE)

synergyc.o : synergyc.cpp synergyc.hpp asynergyc_rev.h Command.hpp InputInjector.hpp
	g++ $(FLAGS) -c -o synergyc.o synergyc.cpp

Command.o : Command.cpp Command.hpp InputInjector.hpp
	g++ $(FLAGS) -c -o Command.o Command.cpp

InputInjector.o : InputInjector.cpp InputInjector.hpp
	g++ $(FLAGS) -c -o InputInjector.o InputInjector.cpp

$(EXE) : $(OBJS)
	g++ -o $(EXE).debug $(OBJS) $(LIBS) $(EXTRA)
	strip $(EXE).debug -R.comment -o $(EXE)

# clean up

clean:
	delete $(EXE)
	delete $(EXE).debug
	delete *.o
	delete *.ii
	delete *.s

# Program Revision

revision:
	BumpRevision BUMP NOASM PROJECTNAME=$(EXE)

# Archive for distribution

archive:
	delete AmiSynergyc.lha
	lha a AmiSynergyc.lha asynergyc Readme

