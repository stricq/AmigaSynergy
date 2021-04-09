include ../makefile.objs

OBJS = $(foreach obj, $(EXEC), $(obj).o)

.phony : Exec


all : ../$(LIB_EX)

../$(LIB_EX) : $(OBJS)
	make -C ../


Exec.o : Exec.cpp Exec.hpp Interrupt.hpp Task.hpp
	g++ $(FLAGS) -c -o Exec.o Exec.cpp

SignalEvents.o : SignalEvents.cpp SignalEvents.hpp
	g++ $(FLAGS) -c -o SignalEvents.o SignalEvents.cpp

IPC.o : IPC.cpp IPC.hpp MessagePortFactory.hpp MessagePort.hpp SignalSemaphoreFactory.hpp SignalSemaphore.hpp\
        ../Exception.hpp OutOfMemoryException.hpp
	g++ $(FLAGS) -c -o IPC.o IPC.cpp

MessagePort.o : MessagePort.cpp MessagePort.hpp ../Exception.hpp
	g++ $(FLAGS) -c -o MessagePort.o MessagePort.cpp

MessagePortFactory.o : MessagePortFactory.cpp MessagePortFactory.hpp MessagePort.hpp ../Exception.hpp OutOfMemoryException.hpp
	g++ $(FLAGS) -c -o MessagePortFactory.o MessagePortFactory.cpp

SignalSemaphore.o : SignalSemaphore.cpp SignalSemaphore.hpp ../Exception.hpp OutOfMemoryException.hpp
	g++ $(FLAGS) -c -o SignalSemaphore.o SignalSemaphore.cpp

SignalSemaphoreFactory.o : SignalSemaphoreFactory.cpp SignalSemaphoreFactory.hpp SignalSemaphore.hpp\
                           ../Exception.hpp OutOfMemoryException.hpp
	g++ $(FLAGS) -c -o SignalSemaphoreFactory.o SignalSemaphoreFactory.cpp

IORequestFactory.o : IORequestFactory.cpp IORequestFactory.hpp ../Exception.hpp IOBase.hpp IORequest.hpp StandardIORequest.hpp\
                     TimerRequest.hpp ClipboardRequest.hpp
	g++ $(FLAGS) -c -o IORequestFactory.o IORequestFactory.cpp

IOBase.o : IOBase.cpp IOBase.hpp MessagePort.hpp ../Exception.hpp
	g++ $(FLAGS) -c -o IOBase.o IOBase.cpp

TimerDevice.o : TimerDevice.cpp TimerDevice.hpp TimerRequest.hpp SignalEvents.hpp
	g++ $(FLAGS) -c -o TimerDevice.o TimerDevice.cpp

ClipboardDevice.o : ClipboardDevice.cpp ClipboardDevice.hpp ClipboardRequest.hpp
	g++ $(FLAGS) -c -o ClipboardDevice.o ClipboardDevice.cpp

InputDevice.o : InputDevice.cpp InputDevice.hpp StandardIORequest.hpp InputEvent.hpp StandardIORequest.hpp Interrupt.hpp
	g++ $(FLAGS) -c -o InputDevice.o InputDevice.cpp

InputEvent.o : InputEvent.cpp InputEvent.hpp ../InvalidArgumentException.hpp
	g++ $(FLAGS) -c -o InputEvent.o InputEvent.cpp

Interrupt.o : Interrupt.cpp Interrupt.hpp
	g++ $(FLAGS) -c -o Interrupt.o Interrupt.cpp

Task.o : Task.cpp Task.hpp ../InvalidArgumentException.hpp
	g++ $(FLAGS) -c -o Task.o Task.cpp

TimerRequest.o : TimerRequest.cpp TimerRequest.hpp IOBase.hpp
	g++ $(FLAGS) -c -o TimerRequest.o TimerRequest.cpp

ClipboardRequest.hpp : IOBase.hpp

Exec : $(OBJS)


# clean up

clean:
	delete *.(o|ii|s)

