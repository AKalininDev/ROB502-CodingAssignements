#include <iostream>

void getAPythagoreanTripleWSum(unsigned int &a, unsigned int &b, unsigned int &c, const int &sum)
{
    // iterate over all possible a, b c from 1 to sum/2 to find the triplet that satisfies the condition a + b + c = sum
    // returns 0 if no such triplet is found

    // note that a < b < c <= sum/2.
    // Otherwise a^2 + b^2 = c^2 > (sum/2)**2.
    // At the same time, a^2 + b^2 < (a + b)^2 = (sum - c)^2 < (sum/2),^2 leading to contradiction with above.

    unsigned int maxC = sum / 2;

    for (unsigned int temp_a = 1; temp_a < maxC; temp_a++)
    {
        for (unsigned int temp_b = temp_a + 1; temp_b < maxC; temp_b++)
        {
            unsigned temp_c = sum - temp_a - temp_b;
            if (temp_a * temp_a + temp_b * temp_b == temp_c * temp_c)
            {
                a = temp_a;
                b = temp_b;
                c = temp_c;
                return;
            }
        }
    }

    // if no such triplet is found, return a = b = c = 0
    a = b = c = 0;
}

int euler9()
{
    unsigned int a, b, c;
    getAPythagoreanTripleWSum(a, b, c, 1000);
    return a * b * c;
}

int main()
{
    // This code is a lot cleaner if you write it as a function, because you can use `return` once you find the answer
    unsigned const product = euler9();
    std::cout << product << std::endl;
    return 0;
}