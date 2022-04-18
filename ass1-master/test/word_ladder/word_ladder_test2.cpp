//
//  Copyright UNSW Sydney School of Computer Science and Engineering
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#include "comp6771/word_ladder.hpp"
#include "comp6771/BFS.hpp"

#include <string>
#include <vector>
#include <iostream>

#include "catch2/catch.hpp"

/*
	This test file will cover all cases, when
	words given to you are adjacent words.
*/
TEST_CASE("at", "it") {
	auto const english_lexicon = word_ladder::read_lexicon("english.txt");
	auto const ladders = word_ladder::generate("at", "it", english_lexicon);
	auto const from = std::string{"at"};
	auto const to = std::string{"it"};
	/*
		Words that are adjacent to each other will only
		have 1 path, that is from the from -> to, any path
		would be greater than the shortest path.
	*/
	CHECK(std::size(ladders) == 1);
	/*
		The size of the path will always be 2
	*/
	CHECK(std::size(ladders[0]) == 2);
	/*
	    Check if the first word of the only path is the from word
	    Check if the second word of the only path is the to word
	*/
    int count = 0;
    bool check = true;
	for (auto x : ladders) {
        for (auto y : x) {
            if (count == 0) {
                if (y != from) {
                    check = false;
                }
            } else {
                if (y != to) {
                    check = false;
                }
            }
            count++;
        }
	}

	CHECK(check == true);
}
