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
    std::vector<int64_t> requests(n);
    if (n < 1) {
        return 0;
    }
    for (int line = 0; line < n; ++line) {
        std::cin >> requests[line];
    }
    std::sort(requests.begin(), requests.end());
    auto sieve = AtkinSieve(limit, requests);
    auto primesCount = sieve.getPrimesCount();
    for (int line = 0; line < n; ++line) {
        std::cout << primesCount[line] << std::endl;
    }
    return 0;
}

