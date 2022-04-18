#include "comp6771/BFS.hpp"
#include "comp6771/word_ladder.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>

// Please note: it's not good practice to test your code via a main function that does
//  printing. Instead, you should be using your test folder. This file should only really
//  be used for more "primitive" debugging as we know that working solely with test
//  frameworks might be overwhelming for some.

void PrintFunction(auto& ladders, auto& filename) {
	std::ofstream myfile(filename);
	int count = 0;
	for (auto x : ladders) {
		count = 0;
		for (auto y : x) {
			if (count == 0) {
				myfile << y;
			}
			else {
				myfile << "," << y;
			}
			count++;
		}
		myfile << std::endl;
	}
	myfile.close();
}

auto main() -> int {
    auto const english_lexicon = word_ladder::read_lexicon("./test/word_ladder/english.txt");
    //ladders generated via Bi-directional BFS
	auto const ladders = word_ladder::generate("cabaret", "atlases", english_lexicon);
	std::cout << ladders.size() << std::endl;
	std::cout << ladders[0].size() << std::endl;


	// debug here
}
