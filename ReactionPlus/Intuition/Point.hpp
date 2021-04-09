#ifndef RAPLUS_INTUITION_POINT_HPP
#define RAPLUS_INTUITION_POINT_HPP


namespace RAPlus {
  namespace Intuition {

    class Point {

      public:

        Point(const Point &pt) : x(pt.x), y(pt.y) { }
        Point(int32 x, int32 y) : x(x), y(y) { }
        Point() : x(0), y(0) { }
       ~Point() { }

        int32 getX() { return(x); }
        int32 getY() { return(y); }

        void setX(int32 x) { this->x = x; }
        void setY(int32 y) { this->y = y; }

        bool operator==(const Point &rhs) { return(x == rhs.x && y == rhs.y); }

        Point &operator=(const Point &rhs) { x = rhs.x; y = rhs.y; return(*this); }

      private:

        int32 x;
        int32 y;

    };

  }
}

#endif // RAPLUS_INTUITION_POINT_HPP

