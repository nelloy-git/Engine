#pragma once

namespace GLwrap {

class Timer {
public:
    Timer();
    virtual ~Timer();

    void start();
    void stop();
    double elapsed();
    double elapsed() const;

private:
    double _start;

};

}