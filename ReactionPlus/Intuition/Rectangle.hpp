#ifndef RAPLUS_INTUITION_RECTANGLE_HPP
#define RAPLUS_INTUITION_RECTANGLE_HPP

#include <exec/types.h>


namespace RAPlus {
  namespace Intuition {

    class Rectangle {

      public:

        Rectangle(const Rectangle &rect) : top(rect.top), left(rect.left), width(rect.width), height(rect.height) { }
        Rectangle(int32 top, int32 left, int32 width, int32 height) : top(top), left(left), width(width), height(height) { }
        Rectangle() : top(0), left(0), width(0), height(0) { }
       ~Rectangle() { }

        int32 getTop()  { return(top); }
        int32 getLeft() { return(left); }

        int32 getWidth()  { return(width); }
        int32 getHeight() { return(height); }

        void setTop(int32 top)   { this->top = top; }
        void setLeft(int32 left) { this->left = left; }

        void setWidth(int32 width)   { this->width = width; }
        void setHeight(int32 height) { this->height = height; }

        bool operator==(const Rectangle &rhs) { return(top == rhs.top && left == rhs.left && width == rhs.width && height == rhs.height); }

        Rectangle &operator=(const Rectangle &rhs) { top = rhs.top; left = rhs.left; width = rhs.width; height = rhs.height; return(*this); }

      private:

        int32 top;
        int32 left;

        int32 width;
        int32 height;

    };

  }
}

#endif // RAPLUS_INTUITION_RECTANGLE_HPP

