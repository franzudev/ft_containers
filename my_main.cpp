//
// Created by Federico Francois on 7/19/21.
//

#include <iostream>
#include <vector>
#include <algorithm>

int main() {
	int my_int[] = {3, 6, 7, 7};
	std::vector<int, std::allocator<int> > prova(std::begin(my_int), std::end(my_int));
	return 0;
}
