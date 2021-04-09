#include "Screen.hpp"


namespace RAPlus {
  namespace Intuition {


    Screen::Screen(struct ::Screen *screen) :
      screen(screen) {

      if (screen == 0) throw InvalidArgumentException("Screen argument is NULL.");

    }


    bool Screen::nextScreen() {

      return((screen = screen->NextScreen) != 0);

    }


    Rectangle Screen::getRectangle() {

      return(Rectangle(getTopEdge(),getLeftEdge(),getWidth(),getHeight()));

    }


    Point Screen::getMousePoint() {

      return(Point(getMouseX(),getMouseY()));

    }


  }
}

