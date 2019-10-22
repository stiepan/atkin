#ifndef LATTICE_POINTS_H_
#define LATTICE_POINTS_H_

#include <iostream>
#include <cstdint>
#include <vector>
#include <tuple>
#include <cassert>

using pair = std::tuple<int64_t, int64_t>;

// Multipilcative group Z*60
std::vector<int64_t> const z60 = {1, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 49, 53, 59};
// elements of Z*60 congruent to 1 mod 4
std::vector<int64_t> const z60_4_1 = {1, 13, 17, 29, 37, 41, 49, 53};
// elements of Z*60 congruent to 7 mod 12
std::vector<int64_t> const z60_4_2 = {7, 19, 31, 43};
// elements of Z*60 congruent to 11 mod 12
std::vector<int64_t> const z60_4_3 = {11, 23, 47, 59};

/* Generic scheme for algorithms 4.1-4.3 from the paper, requires 
 quadratic form and the algorithm to track all the solutions given
 base solutions (which is these whose quadration form does not exceed 60).
*/
template <typename QF, typename Augmenter, int modX, int modY>
class LatticePoints
{

private:
    // we're looking for some quadratic form solutions of the form
    // qf(x, y) = 60k + r where 0 <= k <= bound
    int64_t bound, r;

public:
    LatticePoints(int64_t bound, int64_t r) : bound{bound}, r{r} {}
    // only for points with qf value not exceeding 60
    std::vector<pair> base_solutions()
    {
        std::vector<pair> solutions;
        for (int64_t f = 1; f <= modX; f++) {
            for (int64_t g = 1; g <= modY; g++) {
                if ((60 + (QF::qf(f, g) % 60)) % 60 == r) {
                   solutions.push_back(std::make_tuple(f, g)); 
                }
            }
        }
        return solutions;
    }
    // all points with qf value not exceeding the bound
    void solutions(std::vector<bool> & range)
    {
        auto base = base_solutions();
        for (auto solution : base) {
            int64_t f = std::get<0>(solution);
            int64_t g = std::get<1>(solution);
            Augmenter::augment(range, bound, r, f, g);
        }
    }
};


class QF4_1
{
public:
    static int64_t qf(int64_t x, int64_t y);
};

class Augmenter4_1
{
public:
    static void augment(std::vector<bool> & range, int64_t bound, int64_t r, int64_t f, int64_t g);
}; 

class QF4_2
{
public:
    static int64_t qf(int64_t x, int64_t y);
};

class Augmenter4_2
{
public:
    static void augment(std::vector<bool> & range, int64_t bound, int64_t r, int64_t f, int64_t g);
};

class QF4_3
{
public:
    static int64_t qf(int64_t x, int64_t y);
};

class Augmenter4_3
{
public:
    static void augment(std::vector<bool> & range, int64_t bound, int64_t r, int64_t f, int64_t g);
};



using Solutions4_1 = LatticePoints<QF4_1, Augmenter4_1, 15, 30>;
using Solutions4_2 = LatticePoints<QF4_2, Augmenter4_2, 10, 30>;
using Solutions4_3 = LatticePoints<QF4_3, Augmenter4_3, 10, 30>;

#endif /* LATTICE_POINTS_H_ */
