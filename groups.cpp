#include <iostream>
#include <sstream>

int mult_rem_mod(int a, int b, int div) { return (a * b) % div; }

int element_order(int a, int e, int div)
{
	int an = mult_rem_mod(a, a, div);
	int order = int(2);
	while (an != e) {
		++order;
		an = mult_rem_mod(an, a, div);
	}
	return order;
}

int main(int argc, char* argv[])
{
    for (int an = 1; an < argc; ++an) {
        std::istringstream a(argv[an]);
        int n;
        if (a >> n && n > 0) {
            std::cout << "Orders of elements of multiplicative group "
                      << "of remainders mod " << n;
            std::cout << '\n' << "1 : 1";
            for (int i = 2; i < n; ++i) {
                    std::cout << '\n' << i << " : "
                              << element_order(i, 1, n);
            }
            std::cout << std::endl;
        }
    }
}
