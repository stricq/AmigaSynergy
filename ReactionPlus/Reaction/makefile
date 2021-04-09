include ../makefile.objs

OBJS = $(foreach obj, $(REACTION), $(obj).o)

.phony : Reaction


all : ../$(LIB_RA)

../$(LIB_RA) : $(OBJS)
	$(MAKE) -C ../


Application.o : Application.cpp Application.hpp AppWindow.hpp ../Exec/OutOfMemoryException.hpp
	g++ $(FLAGS) -c -o Application.o Application.cpp

AppWindow.o : AppWindow.cpp AppWindow.hpp Application.hpp Window.hpp ReactionGadget.hpp
	g++ $(FLAGS) -c -o AppWindow.o AppWindow.cpp

ReactionGadget.o : ReactionGadget.cpp ReactionGadget.hpp AppWindow.hpp Button.hpp CheckBox.hpp Chooser.hpp ClickTab.hpp \
                   FileRequest.hpp Integer.hpp Layout.hpp ListBrowser.hpp Page.hpp RadioButton.hpp \
                   Scroller.hpp Space.hpp String.hpp TextEditor.hpp \
                   ../InvalidStateException.hpp ../Exec/OutOfMemoryException.hpp
	g++ $(FLAGS) -c -o ReactionGadget.o ReactionGadget.cpp

Scroller.o : Scroller.cpp Scroller.hpp ReactionGadget.hpp ../Exec/OutOfMemoryException.hpp
	g++ $(FLAGS) -c -o Scroller.o Scroller.cpp

TextEditor.o : TextEditor.cpp TextEditor.hpp ReactionGadget.hpp
	g++ $(FLAGS) -c -o TextEditor.o TextEditor.cpp

Page.o : Page.cpp Page.hpp ReactionGadget.hpp
	g++ $(FLAGS) -c -o Page.o Page.cpp

RadioButton.o : RadioButton.cpp RadioButton.hpp ReactionGadget.hpp
	g++ $(FLAGS) -c -o RadioButton.o RadioButton.cpp

Space.o : Space.cpp Space.hpp ReactionGadget.hpp
	g++ $(FLAGS) -c -o Space.o Space.cpp

String.o : String.cpp String.hpp ReactionGadget.hpp
	g++ $(FLAGS) -c -o String.o String.cpp

ListBrowser.o : ListBrowser.cpp ListBrowser.hpp ReactionGadget.hpp
	g++ $(FLAGS) -c -o ListBrowser.o ListBrowser.cpp

Layout.o : Layout.cpp Layout.hpp ReactionGadget.hpp
	g++ $(FLAGS) -c -o Layout.o Layout.cpp

Integer.o : Integer.cpp Integer.hpp ReactionGadget.hpp
	g++ $(FLAGS) -c -o Integer.o Integer.cpp

FileRequest.o : FileRequest.cpp FileRequest.hpp ReactionGadget.hpp
	g++ $(FLAGS) -c -o FileRequest.o FileRequest.cpp

ClickTab.o : ClickTab.cpp ClickTab.hpp ReactionGadget.hpp
	g++ $(FLAGS) -c -o ClickTab.o ClickTab.cpp

Chooser.o : Chooser.cpp Chooser.hpp ReactionGadget.hpp
	g++ $(FLAGS) -c -o Chooser.o Chooser.cpp

CheckBox.o : CheckBox.cpp CheckBox.hpp ReactionGadget.hpp
	g++ $(FLAGS) -c -o CheckBox.o CheckBox.cpp

Button.o : Button.cpp Button.hpp ReactionGadget.hpp
	g++ $(FLAGS) -c -o Button.o Button.cpp

ReactionClass.o : ReactionClass.cpp ReactionClass.hpp
	g++ $(FLAGS) -c -o ReactionClass.o ReactionClass.cpp

Window.o : Window.cpp Window.hpp ReactionClass.hpp
	g++ $(FLAGS) -c -o Window.o Window.cpp

ReactionImage.o : ReactionImage.cpp ReactionImage.hpp
	g++ $(FLAGS) -c -o ReactionImage.o ReactionImage.cpp

Label.o : Label.cpp Label.hpp ReactionImage.hpp
	g++ $(FLAGS) -c -o Label.o Label.cpp

Reaction : $(OBJS)


# clean up

clean:
	delete *.(o|ii|s)

