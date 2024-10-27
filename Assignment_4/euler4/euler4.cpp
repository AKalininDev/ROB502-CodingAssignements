#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>

unsigned long reverse(unsigned long n)
{
    unsigned long reversed{0};

    while (n > 0)
    {
        reversed = reversed * 10 + n % 10;
        n /= 10;
    }
    return reversed;
}

bool isPalindrome(unsigned long n)
{
    return n == reverse(n);
}

unsigned long int largestPalindromeProduct(int lower_mult, int upper_mult)
{
    int new_lower = lower_mult;
    int new_upper = upper_mult - 1;
    long unsigned largestPalindrome = 0;

    if (lower_mult > upper_mult)
    {
        return 0;
    }

    for (int i = upper_mult; i >= lower_mult; i--)
    {
        if (isPalindrome(upper_mult * i))
        {
            largestPalindrome = upper_mult * i;
            new_lower = i;
            break;
        }
    }

    return std::max(largestPalindrome, largestPalindromeProduct(new_lower, new_upper));
}

int main()
{
    // HINT: consider using std::to_string and std::reverse
    unsigned long int largestPalindrome{0};
    // --- Your code here

    largestPalindrome = largestPalindromeProduct(100, 999);
    // ---
    std::cout << largestPalindrome << std::endl;
    return 0;
}