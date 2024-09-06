#include <iostream>

bool is_factor(const int &x, const int &factor)
{
    return x % factor == 0;
}

bool is_factor_2_or_3(const int &x)
{
    return is_factor(x, 2) || is_factor(x, 3);
}

int main()
{
    // determines whether a number (from stdin) is a factor of 2 or 3
    // the answer should be stored in a variable `is_factor`. Printing of this variable
    // is handled for you, but you must create the variable, or you'll get a compiler error.
    int x;
    std::cout << "Type an integer then press Enter: ";
    std::cin >> x;
    bool is_factor = is_factor_2_or_3(x);
    std::cout << is_factor << std::endl;
    return 0;
}