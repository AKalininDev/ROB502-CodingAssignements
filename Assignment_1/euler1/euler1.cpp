#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// validation functions
bool validNatural(const unsigned &number)
{
    if (number < 1)
    {
        std::cerr << "Invalid input: natural number must be positive" << std::endl;
        return false;
    }
    return true;
}

bool validVectorOfNatural(const std::vector<unsigned> &numbers)
{
    if (numbers.empty())
    {
        std::cerr << "Invalid input: vector of naturals must not be empty" << std::endl;
        return false;
    }

    for (const unsigned &number : numbers)
    {
        if (!validNatural(number))
        {
            return false;
        }
    }

    return true;
}

// checks if a number is a multiple of any of the numbers in the vector. All inputs must be validated naturals.
bool isMultiple(const unsigned &validated_natural_number, const std::vector<unsigned> &validated_natural_multiples)
{
    //(!!NOT SAFE!!) No validation on input is performed.
    // passing sorted vector of multiples improves the performance

    for (const unsigned &multiple : validated_natural_multiples)
    {
        if (validated_natural_number % multiple == 0)
        {
            return true;
        }
    }
    return false;
}

// computes the sum of all natural numbers below the limit that are multiples of any of the numbers in the vector. Returns -1 if the input is invalid.
long long computeSumOfNatMultiplesBelow(const unsigned &limit, const std::vector<unsigned> &multiples)
{
    long unsigned runningSum = 0;

    // validate the input data
    if (!validNatural(limit))
    {
        return -1;
    }

    if (!validVectorOfNatural(multiples))
    {
        return -1;
    }

    // sorting the vector improves the performance for large numbers
    // performance for small numbers is good enough either way, justifying the sorting
    std::vector<unsigned> sortedMultiples = multiples;
    std::sort(sortedMultiples.begin(), sortedMultiples.end());

    for (unsigned i = 1; i < limit; i++)
    {
        if (isMultiple(i, sortedMultiples))
        {
            runningSum += i;
        }
    }
    return runningSum;
}

int main()
{
    long long answer = 0;
    std::vector<unsigned> multiples = {3, 5};

    answer = computeSumOfNatMultiplesBelow(1000, multiples);

    if (answer != -1)
    {
        std::cout << answer << std::endl;
        return 0;
    }
    else
    {
        // indicates the computeSumOfNatMultiplesBelow function failed
        return 1;
    }
}