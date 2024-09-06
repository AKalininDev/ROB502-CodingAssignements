#include <iostream>
#include <string>

unsigned long fibonacciSumEvens(const unsigned int &firstFibNumber, const unsigned int &secondFibNumber, const unsigned int &maxFibNumber)
{
    // trivial case
    if (firstFibNumber > maxFibNumber)
    {
        return 0;
    }

    long unsigned int previousFibNumber = firstFibNumber;
    long unsigned int currentFibNumber = secondFibNumber;
    long unsigned int temp = 0;

    long unsigned int runningSum = previousFibNumber * (previousFibNumber % 2 == 0);

    while (currentFibNumber <= maxFibNumber)
    {
        runningSum += currentFibNumber * (currentFibNumber % 2 == 0);

        // update the Fibonacci numbers.
        temp = currentFibNumber;
        currentFibNumber += previousFibNumber;
        previousFibNumber = temp;
    }
    return runningSum;
}

int main()
{

    unsigned long sum = fibonacciSumEvens(1, 2, 4'000'000);
    std::cout << sum << std::endl;
    return 0;
}