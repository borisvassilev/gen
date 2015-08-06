#include <iostream>

#include "matrix.hpp"
#include "power.hpp"

int main()
{
    Matrix<bool> graph = from_input<bool>(std::cin);
    if (graph.nrow == 0 || graph.nrow != graph.ncol) return 1;

    size_t power = graph.nrow - 1;
    if (power < 1) return 2;

    auto m = multiplier<bool>(std::logical_or<bool>(),
                        std::logical_and<bool>());

    std::cout << power_semigroup(graph, power, m) << std::endl;
}
