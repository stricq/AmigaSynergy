#ifndef RAPLUS_INTUITION_SCREEN_HPP
#define RAPLUS_INTUITION_SCREEN_HPP

#include <intuition/screens.h>

#include <string>

#include "InvalidArgumentException.hpp"

#include "Rectangle.hpp"
#include "Point.hpp"


namespace RAPlus {
  namespace Intuition {

    class Screen {

      public:

        Screen(struct ::Screen *screen);
       ~Screen() { }

        bool nextScreen();

        Rectangle getRectangle();

        Point getMousePoint();

        int16 getLeftEdge() { return(screen->LeftEdge); }
        int16 getTopEdge()  { return(screen->TopEdge); }

        int16 getWidth()  { return(screen->Width); }
        int16 getHeight() { return(screen->Height); }

        int16 getMouseX() { return(screen->MouseX); }
        int16 getMouseY() { return(screen->MouseY); }

        void getTitle(std::string &str)        { str.assign((char *)screen->Title); }
        void getDefaultTitle(std::string &str) { str.assign((char *)screen->DefaultTitle); }

        int8 getBarHeight()   { return(screen->BarHeight); }
        int8 getBarVBorder()  { return(screen->BarVBorder); }
        int8 getBarHBorder()  { return(screen->BarHBorder); }
        int8 getMenuVBorder() { return(screen->MenuVBorder); }
        int8 getMenuHBorder() { return(screen->MenuHBorder); }

        int8 getWBorTop()    { return(screen->WBorTop); }
        int8 getWBorLeft()   { return(screen->WBorLeft); }
        int8 getWBorRight()  { return(screen->WBorRight); }
        int8 getWBorBottom() { return(screen->WBorBottom); }

        struct ::Screen *getScreen() { return(screen); }

      private:

        struct ::Screen *screen;

    };

  }
}

#endif // RAPLUS_INTUITION_SCREEN_HPP

