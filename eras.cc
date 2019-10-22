#include <iostream>
#include <cstdint>
#include <vector>


int main()
{
    int64_t n, foo;
    std::cin >> n >> foo >> foo;
    std::vector<bool> pms(n + 1, true);
    pms[1] = 0;
    pms[0] = 0;
    int64_t counter = 0;
    for (int64_t i = 2; i <= n; ++i) {
        if (pms[i]) {
            ++counter;
            int mltp;
            for (int64_t j = 1; (mltp = i * j) <= n; j++) {
                pms[mltp] = false;
            }
        }
    }
    return 0;
}
