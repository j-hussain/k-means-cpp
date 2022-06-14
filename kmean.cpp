// import the following for reading files
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <ctime> // random seeding

/*
Though I understand it's bad practice, it saves a lot of time to use the std namespace
*/
using namespace std;

struct Point {
    double x, y;
    double minimum_distance;
    int cluster;

    Point(double x, double y):
        x(x),
        y(y),
        cluster(-1),
        minimum_distance(__DBL_MAX__) {}

    Point():
        x(0.0),
        y(0.0),
        cluster(-1),
        minimum_distance(__DBL_MAX__) {}

    double distance(Point p) {
        return (p.x - x) * (p.x - x) + (p.y - y) * (p.y - y);
    }
};