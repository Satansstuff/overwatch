#ifndef _SENSORS_
#define _SENSORS_
#include <string>
#include <iostream>
#include <functional>
#include <cstdint>
#include <cstdio>
#include <cstring>
/*
    This is a "sensor", it holds values that are needed
    for recipies. It's not magic; It can't hold values
    from the stack. 


*/
class sensor
{
private:
    char *val = new char[8];

public:
    std::string name;
    size_t uval = 8;
    size_t valsize = 8;
    sensor() = default;
    sensor(size_t vsize)
    {
        delete val;
        uval = vsize;
        val = new char[vsize];
    }
    sensor(sensor &other)
    {
        other.name = name;
        other.uval = uval;
        other.valsize = valsize;
        std::memcpy(this->val, other.val, other.uval);
    }
    sensor operator=(const sensor &other)
    {
        sensor s(other.uval);
        s.valsize = other.valsize;
        std::memcpy(s.val, other.val, sizeof(other.uval));
        s.name = other.name;
        return s;
    }
    template<typename T>
    sensor operator+(const T &other) = delete;
    template<typename T>
    sensor operator-(const T &other) = delete;
    template<typename T>
    sensor operator+=(const T &other) = delete;
    template<typename T>
    sensor operator-=(const T &other) = delete;
    sensor operator++() = delete;
    sensor operator--() = delete;

    bool operator==(const std::string &other)
    {
        return name == other;
    }
    bool operator==(const sensor &other)
    {
        return name == (other.name) && (uval == other.uval) && (valsize == other.valsize);
    }
    template <typename T>
    void set(T v)
    {
        size_t size = sizeof(v);
        std::function<void(void)> f[] = 
        {
            // Standard types
            [&]()
            {
                valsize = sizeof(v);
                std::memcpy(val, &v, size);
                //std::cout << "uval f1: " << uval << std::endl;
            },
            [&]()
            {
                valsize = size;
                uval = size;
                delete val;
                val = new char[size];
                std::memcpy(val, &v, size);
            },
            [&]()
            {
                if constexpr(std::is_same<T, std::string>::value)
                {
                    valsize = sizeof(v.data()[0]);
                    size = v.size();
                    uval = size;
                    delete val;
                    val = new char[size];
                    std::memcpy(val, v.data(), size);
                }
            }
        };
        auto it = (size > uval) + (std::is_same<T, std::string>::value);
        f[it]();

            // strings and vectors. Potentially more
            // but not tested for say.. std::*maps.
            // If vectors, need size of individual type
/*          [&]()
            {
                valsize = sizeof(v.data()[0]);
                size = v.size();
                uval = size;
                delete val;
                val = new char[size];
                std::memcpy(val, v.data(), size);
            } */
    }
    template <typename T>
    auto get()
    {
        
        std::function<T(void)> f[2] = 
        {
            [&]()
            {
                T retvar;
                std::memcpy(&retvar, val, sizeof(T));
                return retvar;
            }
            // Eventuellt en för vectors också
            // liknande fast med sizeof(T)
        };
        if constexpr(std::is_same<T, std::string>::value)
        {
            auto func = [&]()
            {
                    //if (std::is_same<T, int>::value)
                    T retvar;

                    //newstuff
/*                  for(unsigned i = 0; i < uval; i++)
                    {
                        retvar.push_back(val[i]);
                    } */
                    retvar.resize(uval);
                    for (auto [i, ptr] = std::tuple{0, val}; 
                        i < uval; i++, ptr += valsize) 
                    {
                        std::memcpy(retvar.data() + i * valsize, ptr, valsize);
                    }
                    // iterera över minne med hjälp utav
                    // att du vet variabel-storleken
                    return retvar;
            };
            f[1] = func;
        }
        auto it = (std::is_same<T, std::string>::value);

        return f[it]();
    }
    ~sensor()
    {
        delete val;
    }
};
#endif