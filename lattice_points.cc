#include "lattice_points.h"

int64_t QF4_1::qf(int64_t x, int64_t y)
{
    return 4 * x * x + y * y;
}

void Augmenter4_1::augment(std::vector<bool> & range, int64_t bound, int64_t r, int64_t f, int64_t g)
{
    assert(f >= 1 && f <= 15 && g >= 1 && g <= 30);
    assert(r >= 1 && r < 60);
    assert((QF4_1::qf(f, g) - r) % 60 == 0);

    int64_t x = f;
    int64_t y0 = g;
    int k0 = (QF4_1::qf(f, g) - r) / 60;

    // move to the right edge of `4x^2 + y^2 <= 60 * bound` ellipse
    while (k0 < bound) {
        k0 += 2 * x + 15;
        x += 15;
    }
    // we're one step (of at most 15 length) outside the ellipse in x axis
    while (true) {
        // one step left
        x -= 15; 
        k0 -= 2 * x + 15;
        if (x <= 0) {
            break;
        }
        int64_t y = y0;
        int64_t k = k0;
        while (k < bound) {
            // go up as much as possible
            range[k] = !range[k];
            k += y + 15;
            y += 30;
        }
    }
}

int64_t QF4_2::qf(int64_t x, int64_t y)
{
    return 3 * x * x + y * y;
}

void Augmenter4_2::augment(std::vector<bool> & range, int64_t bound, int64_t r, int64_t f, int64_t g)
{
    assert(f >= 1 && f <= 10 && g >= 1 && g <= 30);
    assert(r >= 1 && r < 60);
    assert((QF4_2::qf(f, g) - r) % 60 == 0);

    int64_t x = f;
    int64_t y0 = g;
    int k0 = (QF4_2::qf(f, g) - r) / 60;

    // move to the right edge of `3x^2 + y^2 <= 60 * bound` ellipse
    while (k0 < bound) {
        k0 += x + 5;
        x += 10;
    }
    // we're one step (of at most 15 length) outside the ellipse in x axis
    while (true) {
        // one step left
        x -= 10; 
        k0 -= x + 5;
        if (x <= 0) {
            break;
        }
        int64_t y = y0;
        int64_t k = k0;
        while (k < bound) {
            // go up as much as possible
            range[k] = !range[k];
            k += y + 15;
            y += 30;
        }
    }
}

int64_t QF4_3::qf(int64_t x, int64_t y)
{
    return 3 * x * x - y * y;
}

void Augmenter4_3::augment(std::vector<bool> & range, int64_t bound, int64_t r, int64_t f, int64_t g)
{
    assert(f >= 1 && f <= 10 && g >= 1 && g <= 30);
    assert(r >= 1 && r < 60);
    assert((QF4_3::qf(f, g) - r) % 60 == 0);

    int64_t x = f;
    int64_t y0 = g;
    int k0 = (QF4_3::qf(f, g) - r) / 60;

    // we're walking in first quadrant under 
    // `y=sqrt(3)x` over `3x^2 - y^2 = 60 * bound` hyperbole
    while (true) {
        while (k0 >= bound && x > y0) {
            k0 -= y0 + 15;
            y0 += 30;
        }
        if (k0 >= bound && x <= y0) {
            break;
        }
        int64_t k = k0;
        int64_t y = y0;
        while (k >= 0 && y < x) {
            range[k] = !range[k];
            k -= y + 15;
            y += 30;
        }
        k0 += x + 5;
        x += 10;
    }
}

