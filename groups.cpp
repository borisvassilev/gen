// Copyright Boris Vassilev
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

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
