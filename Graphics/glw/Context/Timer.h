#pragma once

namespace glw {

class Timer {
public:
    Timer();
    virtual ~Timer();

    void start();
    void stop();
    double elapsed() const;

private:
    double _start;
    double _stop;

};

}