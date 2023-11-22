#pragma once
#pragma warning(disable: 4244) // T to i64 loss of data

typedef __int64 i64;

#define MASK1 0xAAAAAAA
#define MASK2 0x5555555

namespace xv
{
    enum e_cypher_mode
    {
        XOR1,
        XOR2,
        XOR3,
    };

    template<typename T>
    class xval;

    class common
    {
    public:
        static __forceinline i64 rotate_left(i64 value, i64 count) {
            const unsigned int mask = (CHAR_BIT * sizeof(value) - 1);
            count &= mask;
            return (value << count) | (value >> (-count & mask));
        }

        static __forceinline i64 rand_int(i64 min, i64 max) {
            return min + rand() % (max - min + 1);
        }
    };


    class __xv_e_1
    {
    public:
        static __forceinline i64 encrypt(i64 data, i64 key) {
            i64 result = data ^ key;
            result = common::rotate_left(result, 5);
            result ^= (key >> 2);
            return result;
        }

        static __forceinline i64 decrypt(i64 encrypted_data, i64 key) {
            encrypted_data ^= (key >> 2);
            encrypted_data = common::rotate_left(encrypted_data, -5);
            return encrypted_data ^ key;
        }
    };

    class __xv_e_2
    {
    public:
        static __forceinline i64 encrypt(i64 data, i64 key) {
            i64 result = data ^ key;

            result = common::rotate_left(result, key % 7);
            result ^= (key >> 3) & (key << 2);
            result = common::rotate_left(result, 3);
            result ^= (key & (common::rotate_left(key, 2)));

            return result;
        }

        static __forceinline i64 decrypt(i64 encrypted_data, i64 key) {
            encrypted_data ^= (key & (common::rotate_left(key, 2)));
            encrypted_data = common::rotate_left(encrypted_data, -3);
            encrypted_data ^= (key >> 3) & (key << 2);
            encrypted_data = common::rotate_left(encrypted_data, -(key % 7));

            return encrypted_data ^ key;
        }
    };

    class __xv_e_3
    {
    public:
        static __int64 _ok;

        static __forceinline i64 encrypt(i64 data, i64 key) {
            i64 result = data ^ key;

            result = common::rotate_left(result, key % 7);
            result ^= (key >> 3) & (key << 2);
            result = common::rotate_left(result, 3);
            result ^= (key & (common::rotate_left(key, 2)));
            result ^= _ok;

            return result;
        }

        static __forceinline i64 decrypt(i64 encrypted_data, i64 key) {
            encrypted_data ^= _ok;
            encrypted_data ^= (key & (common::rotate_left(key, 2)));
            encrypted_data = common::rotate_left(encrypted_data, -3);
            encrypted_data ^= (key >> 3) & (key << 2);
            encrypted_data = common::rotate_left(encrypted_data, -(key % 7));

            return encrypted_data ^ key;
        }
    };
    __int64 __xv_e_3::_ok = reinterpret_cast<__int64>(__TIMESTAMP__);

    template<typename T>
    class xval
    {
        e_cypher_mode m;
        i64 v;
        i64 k;

    public:
        __forceinline xval()
        {
            srand(time(NULL));

            m = (e_cypher_mode)common::rand_int(0, 2);
            k = common::rand_int(0x0001000000, 0xFFFFFFFFFF);
            set(0);
        }

        __forceinline xval(T _v)
        {
            srand(time(NULL));

            m = (e_cypher_mode)common::rand_int(0, 2);
            k = common::rand_int(0x0001000000, 0xFFFFFFFFFF);
            set(_v);
        }

        __forceinline xval(T _v, e_cypher_mode _m)
        {
            srand(time(NULL));

            m = _m;
            k = common::rand_int(0x0001000000, 0xFFFFFFFFFF);
            set(_v);
        }

        void operator =(const T _v)
        {
            set(_v);
        }

        __forceinline T get()
        {
            switch (m)
            {
            case e_cypher_mode::XOR1:
                return __xv_e_1::decrypt(v, k);
            case e_cypher_mode::XOR2:
                return __xv_e_2::decrypt(v, k);
            case e_cypher_mode::XOR3:
                return __xv_e_3::decrypt(v, k);
            }

            return 0;
        }

        __forceinline void set(T _v)
        {
            switch (m)
            {
            case e_cypher_mode::XOR1:
                v = __xv_e_1::encrypt(_v, k);
                break;
            case e_cypher_mode::XOR2:
                v = __xv_e_2::encrypt(_v, k);
                break;
            case e_cypher_mode::XOR3:
                v = __xv_e_3::encrypt(_v, k);
                break;
            }
        }
    };
}
