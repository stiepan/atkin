#include "atkin.h"

std::mutex toggler_m{};


std::vector<int64_t> first_primes = {2, 3, 5};

/* used as a last step in Atkin's sieve - range contains 
 oddity of the number of relevant solutions for each number in 0..limit range.
 switches 1 to 0 for all the integers within range that are multiple of
 square of some prime number
*/
std::vector<int64_t> AtkinSieve::getSquareFree(bitfields & ranges, int64_t limit)
{
    // atkin just omitts 2, 3, 5 primes
    std::vector<int64_t> primes{firstPrimes};
    for (int64_t k = 0, n = 1, n2 = 1; n <= limit; ++k) {
        for (auto r : z60) { 
            n = 60 * k + r;
            n2 = n * n;
            if (ranges[r][k]) {
                primes.push_back(n);
                if (n2 <= limit) {
                    // eliminate squares
                    for (int64_t j = 0, l = 1, n2l = n2; n2l <= limit; ++j) {
                        for (auto r : z60) {
                            l = 60 * j + r;
                            n2l = n2 * l;
                            if (n2l > limit) {
                                break;
                            }
                            // both n2 and l are part of z60 group so thier multiple is as well
                            // thus n2l % 60 has been initialized and contain values
                            // up to limit/60
                            ranges[n2l % 60][n2l / 60] = false;
                        }
                    }
                }
            }
        }
    }
    return primes;
}


std::vector<int64_t> const AtkinSieve::firstPrimes{2, 3, 5};


AtkinSieve::AtkinSieve(int64_t limit)
{
    bitfields ranges{60};
    // step 3.1
    auto t1 = std::thread(toggleComposite<Solutions4_1>, z60_4_1, std::ref(ranges), limit);
    // step 3.2
    auto t2 = std::thread(toggleComposite<Solutions4_2>, z60_4_2, std::ref(ranges), limit);
    // step 3.3
    auto t3 = std::thread(toggleComposite<Solutions4_3>, z60_4_3, std::ref(ranges), limit);
    t1.join();
    t2.join();
    t3.join();
    primes = getSquareFree(ranges, limit);
}


std::vector<int64_t> const & AtkinSieve::getPrimes() const
{
    return primes;
}
