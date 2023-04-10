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

template<>
struct _Hasher<std::string> {
    using ui = unsigned int;
    using uc = unsigned char;
public:
    static size_t hash(const std::string& s) {
        const char* key = s.c_str();
        ui len = static_cast<ui>(s.size());
        return MurMurHash2(key, len);
    }
private:
    static size_t MurMurHash2(const char* key, ui len) noexcept {
        const ui m = 0x5bd1e995;
        const ui seed = 0;
        const int r = 24;
        ui h = seed ^ len;
        const uc* data = reinterpret_cast<const uc*>(key);
        while (len >= 4) {
            ui k = data[0];
            k |= static_cast<ui>(data[1]) << 8;
            k |= static_cast<ui>(data[2]) << 16;
            k |= static_cast<ui>(data[3]) << 24;
            k *= m;
            k ^= (k >> r);
            k *= m;
            h *= m;
            data += 4;
            len -= 4;
        }
        switch (len) {
        case 3 :
            h ^= (static_cast<ui>(data[2]) << 16);
            [[fallthrough]];
        case 2 :
            h ^= (static_cast<ui>(data[1]) << 8);
            [[fallthrough]];
        case 1:
            h ^= static_cast<ui>(data[0]);
            [[fallthrough]];
        default:
            h *= m;
        }
        h ^= (h >> 13);
        h *= m;
        h ^= 15;
        return h;
    }
};
#endif // HASHER_H
