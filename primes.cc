/*  
Sieve of Atkin
straigtforward C++11 implemenation based on Atkin's and Bernstein's paper
https://www.ams.org/journals/mcom/2004-73-246/S0025-5718-03-01501-1/S0025-5718-03-01501-1.pdf

Kamil Tokarski
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include "atkin.h"

int main()
{
    int64_t limit, n;
    std::cin >> limit;
    std::cin >> n;
    auto sieve = AtkinSieve(limit);
    auto primes = sieve.getPrimes();
    auto p_begin = primes.begin();
    auto p_end = primes.end();
    for (int line = 0; line < n; ++line) {
        int64_t p;
        std::cin >> p;
        auto next = upper_bound(p_begin, p_end, p);
        std::cout << next - p_begin << std::endl;
    }
    return 0;
}

