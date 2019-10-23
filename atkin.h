#ifndef ATKIN_H_
#define ATKIN_H_

#include <cstdint>
#include <vector>
#include <tuple>
#include <thread>
#include <future>
#include <mutex>

#include "lattice_points.h"

using bitfield = std::vector<bool>;
using bitfields = std::vector<bitfield>;

extern std::mutex toggler_m;

template <typename LatticePoints>
bitfield toggleWithRemainder(int64_t bound, int64_t r)
{
    bitfield range(bound + 1, false);
    LatticePoints{bound, r}.solutions(range);
    return range;
}

/* scheme for toggling oddity of the number of solutions 
 of some quadration form equations (algorithms 3.1-3.3 in the paper)
*/
template <typename LatticePoints>
void toggleComposite(std::vector<int64_t> remainders, bitfields & ranges, int64_t limit)
{
    std::vector<std::future<std::vector<bool>>> future_ranges{};
    int64_t bound = (limit / 60) + ((limit % 60) > 0);
    for (auto r : remainders) {
        future_ranges.push_back(
            std::async(std::launch::async, toggleWithRemainder<LatticePoints>, bound, r)
        );
    }
    for (int i = 0; i < future_ranges.size(); i++) {
        auto & f = future_ranges[i];
        f.wait();
        {
            std::lock_guard<std::mutex> guard{toggler_m};
            ranges[remainders[i]] = f.get();
        }
    }
}


class AtkinSieve
{

private:
    static std::vector<int64_t> const firstCounts;
    std::vector<int64_t> primesCount;
    void removeSquareFreeAndCount(bitfields &, int64_t, std::vector<int64_t> const &);

public:

    /* given the upper limit for the sieve returns bitfield for 
     each number in range with 1 iff the number is prime
    */
    AtkinSieve(int64_t limit, std::vector<int64_t> const &);
    std::vector<int64_t> const & getPrimesCount() const;
};

#endif /* ATKIN_H_ */
