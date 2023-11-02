#pragma once
#include <stdlib.h>

typedef long long i64;

#define MASK1 0xAAAAAAA
#define MASK2 0x5555555

enum e_cypher_mode
{
    XOR0 = 0,
    XOR1 = 1,
    XOR2 = 2,
    XOR3 = 3,
};

template<typename T>
class xval;

template<typename T>
class common
{
public:
    static __forceinline T rotate_left(T value, int count) {
        const unsigned int mask = (CHAR_BIT * sizeof(value) - 1);
        count &= mask;
        return (value << count) | (value >> (-count & mask));
    }

    static __forceinline int rand_int(int min, int max) {
        return min + rand() % (max - min + 1);
    }
};

template<typename T>
class __xv_e_0
{
public:
    static __forceinline T encrypt(T data, T key) {
        return data ^ key;
    }

    static __forceinline T decrypt(T data, T key) {
        return data ^ key;
    }
};

template<typename T>
class __xv_e_1
{
public:
    static __forceinline T encrypt(T data, T key) {
        T result = data ^ key;
        result = common<T>::rotate_left(result, 5);
        result ^= (key >> 2);
        return result;
    }

    static __forceinline T decrypt(T encrypted_data, T key) {
        encrypted_data ^= (key >> 2);
        encrypted_data = common<T>::rotate_left(encrypted_data, -5);
        return encrypted_data ^ key;
    }
};

template<typename T>
class __xv_e_2
{
public:
    static __forceinline T encrypt(T data, T key) {
        T result = data ^ key;

        result = common<T>::rotate_left(result, key % 7);
        result ^= (key >> 3) & (key << 2);
        result = common<T>::rotate_left(result, 3);
        result ^= (key & (common<T>::rotate_left(key, 2)));

        return result;
    }

    static __forceinline T decrypt(T encrypted_data, T key) {
        encrypted_data ^= (key & (common<T>::rotate_left(key, 2)));
        encrypted_data = common<T>::rotate_left(encrypted_data, -3);
        encrypted_data ^= (key >> 3) & (key << 2);
        encrypted_data = common<T>::rotate_left(encrypted_data, -(key % 7));

        return encrypted_data ^ key;
    }
};

template<typename T>
class __xv_e_3
{
public:
    static int _ok;

    static __forceinline T encrypt(T data, T key) {
        T result = data ^ key;

        result = common<T>::rotate_left(result, key % 7);
        result ^= (key >> 3) & (key << 2);
        result = common<T>::rotate_left(result, 3);
        result ^= (key & (common<T>::rotate_left(key, 2)));
        result ^= _ok;

        return result;
    }

    static __forceinline T decrypt(T encrypted_data, T key) {
        encrypted_data ^= _ok;
        encrypted_data ^= (key & (common<T>::rotate_left(key, 2)));
        encrypted_data = common<T>::rotate_left(encrypted_data, -3);
        encrypted_data ^= (key >> 3) & (key << 2);
        encrypted_data = common<T>::rotate_left(encrypted_data, -(key % 7));

        return encrypted_data ^ key;
    }
};
template<typename T>
int __xv_e_3<T>::_ok = (int)__TIMESTAMP__;

template<typename T>
class xval
{
    e_cypher_mode m;
    T v;
    T k;

public:
    xval(T _v)
    {
        srand(time(NULL));

        m = (e_cypher_mode)common<T>::rand_int(0, 2);
        k = common<T>::rand_int(0x0001000000, 0xFFFFFFFFFF);
        set(_v);
    }

    xval(T _v, e_cypher_mode _m)
    {
        srand(time(NULL));

        m = _m;
        k = common<T>::rand_int(0x0001000000, 0xFFFFFFFFFF);
        set(_v);
    }

    __forceinline T get()
    {
        switch (m)
        {
        case e_cypher_mode::XOR0:
            return __xv_e_0<T>::decrypt(v, k);
        case e_cypher_mode::XOR1:
            return __xv_e_1<T>::decrypt(v, k);
        case e_cypher_mode::XOR2:
            return __xv_e_2<T>::decrypt(v, k);
        case e_cypher_mode::XOR3:
            return __xv_e_3<T>::decrypt(v, k);
        }
    }

    __forceinline void set(T _v)
    {
        switch (m)
        {
        case e_cypher_mode::XOR0:
            v = __xv_e_0<T>::encrypt(_v, k);
            break;
        case e_cypher_mode::XOR1:
            v = __xv_e_1<T>::encrypt(_v, k);
            break;
        case e_cypher_mode::XOR2:
            v = __xv_e_2<T>::encrypt(_v, k);
            break;
        case e_cypher_mode::XOR3:
            v = __xv_e_3<T>::encrypt(__xv_e_3<T>::encrypt(_v, k), k);
            break;
        }
    }
};
