#include<memory>

#ifndef HASHER_H
#define HASHER_H

//Just template for _Hasher function
//You can find specialisation _Hasher<std::string> in .cpp file

template <typename T>
struct _Hasher {
    static size_t hash(const T& x) {
        return static_cast<size_t>(x);
    }
};

#endif // HASHER_H
