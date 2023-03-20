#ifndef POLYNOM_H
#define POLYNOM_H
#include <string>

class polynom{
private:
    std::string data{"x^3 + xyz + yz^2"};

public:
    void set_data(const std::string& str) {
        data = str;
    }
};

#endif // POLYNOM_H
