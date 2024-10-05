#include <iostream>
#include <vector>

#define ERROR_MESSAGE std::invalid_argument("Error: vectors must be the same size")

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &v)
{
    os << "[";
    for (const T &elem : v)
    {
        os << elem;
        if (&elem != &v.back())
        {
            os << ", ";
        }
    }
    os << "]";
    return os;
};

template <typename T1, typename T2>
auto operator+(const std::vector<T1> &v1, const std::vector<T2> &v2)
{
    if (v1.size() != v2.size())
    {
        throw ERROR_MESSAGE;
    }

    using ResultType = decltype(T1{} + T2{});

    std::vector<ResultType> result;
    for (size_t i = 0; i < v1.size(); i++)
    {
        result.push_back(v1[i] + v2[i]);
    }
    return result;
};

template <typename T1, typename T2>
auto operator-(const std::vector<T1> &v1, const std::vector<T2> &v2)
{
    if (v1.size() != v2.size())
    {
        throw ERROR_MESSAGE;
    }

    using ResultType = decltype(T1{} - T2{});

    std::vector<ResultType> result;
    for (size_t i = 0; i < v1.size(); i++)
    {
        result.push_back(v1[i] - v2[i]);
    }
    return result;
};

template <typename T1, typename T2>
auto operator*(const std::vector<T1> &v1, const std::vector<T2> &v2)
{
    if (v1.size() != v2.size())
    {
        throw ERROR_MESSAGE;
    }

    using ResultType = decltype(T1{} * T2{});

    std::vector<ResultType> result;
    for (size_t i = 0; i < v1.size(); i++)
    {
        result.push_back(v1[i] * v2[i]);
    }
    return result;
};

template <typename T1, typename T2>
auto operator*(T1 scalar, const std::vector<T2> &v)
{

    using ResultType = decltype(T1{} * T2{});

    std::vector<ResultType> result;
    for (const T2 &elem : v)
    {
        result.push_back(scalar * elem);
    }
    return result;
};

template <typename T1, typename T2>
auto operator*(const std::vector<T2> &v, T1 scalar)
{

    using ResultType = decltype(T1{} * T2{});

    std::vector<ResultType> result;
    for (const T2 &elem : v)
    {
        result.push_back(scalar * elem);
    }
    return result;
};

template <typename T1, typename T2>
auto operator/(const std::vector<T2> &v, T1 scalar)
{

    using ResultType = decltype(T2{} / T1{});

    std::vector<ResultType> result;
    for (const T2 &elem : v)
    {
        result.push_back(elem / scalar);
    }
    return result;
};

template <typename T1, typename T2>
auto operator,(const std::vector<T1> &v1, const std::vector<T2> &v2)
{
    using ResultType = decltype(T1{} + T2{});

    std::vector<ResultType> result;
    result = v1;
    for (size_t i = 0; i < v2.size(); i++)
    {
        result.push_back(v2[i]);
    }
    return result;
};