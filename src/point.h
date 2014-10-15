#ifndef POINT_H
#define POINT_H

struct Point {
    long x;
    long y;

    bool operator ==(Point const& other) {
        return x == other.x && y == other.y;
    }
};

#endif // POINT_H
