include makefile.objs

.phony : dirs $(DIRS)


all : $(LIB)


InvalidArgumentException.hpp : Exception.hpp

InvalidStateException.hpp : Exception.hpp

IndexRangeException.o : IndexRangeException.cpp IndexRangeException.hpp Exception.hpp
	g++ $(FLAGS) -c -o IndexRangeException.o IndexRangeException.cpp

Exception.o : Exception.cpp Exception.hpp
	g++ $(FLAGS) -c -o Exception.o Exception.cpp

dirs : $(DIRS)

$(DIRS) :
	$(MAKE) -j 5 -C $@ $@

$(LIB_RP) : $(RP_OBJS) $(DIRS)
	SDK:gcc/bin/ar rvs $(LIB_RP) $(RP_OBJS)

$(LIB_RA) : $(DIRS)
	SDK:gcc/bin/ar rvs $(LIB_RA) $(REACTION_OBJS)

$(LIB_CO) : $(DIRS)
	SDK:gcc/bin/ar rvs $(LIB_CO) $(COMMODITIES_OBJS)

$(LIB_DA) : $(DIRS)
	SDK:gcc/bin/ar rvs $(LIB_DA) $(DATATYPES_OBJS)

$(LIB_DO) : $(DIRS)
	SDK:gcc/bin/ar rvs $(LIB_DO) $(DOS_OBJS)

$(LIB_EX) : $(DIRS)
	SDK:gcc/bin/ar rvs $(LIB_EX) $(EXEC_OBJS)

$(LIB_IF) : $(DIRS)
	SDK:gcc/bin/ar rvs $(LIB_IF) $(IFFPARSE_OBJS)

$(LIB_IN) : $(DIRS)
	SDK:gcc/bin/ar rvs $(LIB_IN) $(INTUITION_OBJS)

$(LIB_LO) : $(DIRS)
	SDK:gcc/bin/ar rvs $(LIB_LO) $(LOCALE_OBJS)

$(LIB_PR) : $(DIRS)
	SDK:gcc/bin/ar rvs $(LIB_PR) $(PREFS_OBJS)

$(LIB_SP) : $(DIRS)
	SDK:gcc/bin/ar rvs $(LIB_SP) $(SOCKET_OBJS)

$(LIB_UT) : $(DIRS)
	SDK:gcc/bin/ar rvs $(LIB_UT) $(UTILITY_OBJS)


# clean up

clean:
	Delete $(LIB)
	Delete *.(o|ii|s) */*.(o|ii|s)

