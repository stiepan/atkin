#include "atkin.h"

std::mutex toggler_m{};


std::vector<int64_t> first_primes = {2, 3, 5};

/* used as a last step in Atkin's sieve - range contains 
 oddity of the number of relevant solutions for each number in 0..limit range.
 switches 1 to 0 for all the integers within range that are multiple of
 square of some prime number
*/
void AtkinSieve::removeSquareFreeAndCount(bitfields & ranges, int64_t limit, std::vector<int64_t> const & count_requests)
{
    assert(count_requests.size() > 0);
    
    // atkin just omitts 2, 3, 5 primes
    uint32_t req_it = 0;
    int64_t request = count_requests[req_it];
    while (req_it < count_requests.size() && request <= 5) {
        primesCount[req_it] = firstCounts[request];
        if (count_requests.size() > ++req_it) {
            request = count_requests[req_it];
        }
    }
    int64_t count = 3;
    int64_t const overflow = 3037000499L; // floor(sqrt(2^63-1))
    for (int64_t k = 0, n = 1, n2 = 1; n <= limit && count_requests.size() > req_it; ++k) {
        for (auto r : z60) { 
            n = 60 * k + r;
            n2 = n * n;
            if (ranges[r][k]) {
                ++count;
                bool pending_requests = true;
                while (n >= request && pending_requests) {
                    primesCount[req_it] = count - (n > request);
                    pending_requests = (count_requests.size() > ++req_it);
                    if (pending_requests) {
                        request = count_requests[req_it];
                    }
                }
                if (!pending_requests) {
                    break;
                }
                if (n <= overflow && n2 <= limit) {
                    // eliminate squares
                    for (int64_t j = 0, l = 1, n2l = n2; n <= overflow && l <= overflow && n2l <= limit; ++j) {
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
    while (req_it < primesCount.size()) {
        primesCount[req_it++] = count;
    }
}


// answer to 0, 1, 2, 3, 4, 5 requests
std::vector<int64_t> const AtkinSieve::firstCounts = {0, 0, 1, 2, 2, 3};


AtkinSieve::AtkinSieve(int64_t limit, std::vector<int64_t> const & count_requests) 
    : primesCount(count_requests.size())
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
    removeSquareFreeAndCount(ranges, limit, count_requests);
}


std::vector<int64_t> const & AtkinSieve::getPrimesCount() const
{
    return primesCount;
}
