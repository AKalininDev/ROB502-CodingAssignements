#include <iostream>

unsigned long sumOfSquares(const unsigned int &limit)
{
    unsigned long sum = 0;
    for (unsigned int i = 1; i <= limit; i++)
    {
        sum += i * i;
    }
    return sum;
}

unsigned long squareOfSum(const unsigned int &limit)
{
    unsigned long sum = 0;
    for (unsigned int i = 1; i <= limit; i++)
    {
        sum += i;
    }
    return sum * sum;
}

int main()
{
    int limit = 100;
    unsigned long sumOfSquaresResult = sumOfSquares(limit);
    unsigned long squareOfSumResult = squareOfSum(limit);

    long long difference = squareOfSumResult - sumOfSquaresResult;

    std::cout << difference << std::endl;
    return 0;
}