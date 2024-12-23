/*
#ifndef LINE_H
#define LINE_H

#include <vector>
#include "cinder/gl/gl.h" // Assuming you need this

namespace MyLines { //Optional Namespace
    class Line {
    public:
        std::vector<ci::vec2> points;
        double lifetime;
        double birthTime;

        Line(const std::vector<ci::vec2>& pts) : points(pts), lifetime(5.0), birthTime(app::getElapsedSeconds()) {}
    };
}

#endif
*/