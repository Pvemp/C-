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

#include "catch2/catch.hpp"

bool isAdjacent(std::string a, std::string b) {
	int d = 0;
	for (std::string::size_type i = 0; i < a.size(); i++) {
		if (a[i] != b[i]) {
			d++;
		}
	}
	if (d == 1) {
		return true;
	}
	return false;
}

/*
	This test case covers all cases where
	the given words are not adjacent to each other.
	The first one represents the commented version of this case
*/
TEST_CASE("atlases", "cabaret") {
	auto const english_lexicon = word_ladder::read_lexicon("english.txt");
	auto const ladders = word_ladder::generate("atlases", "cabaret", english_lexicon);
	auto const shortestLength = BFS::NaiveBFS("atlases", "cabaret", english_lexicon);
	auto const from = std::string{"atlases"};
	auto const to = std::string{"cabaret"};
	/*
		Check how many paths they are, however this does not prove
		that each path is a valid path. As they may be of incorrect lengths
		or they may violate the condition of being 1 alphabet apart for each
		adjacent word.
	*/

	CHECK(std::size(ladders) == 840);

	/*
		Now we check if the size of one of the paths is correct.
		We use this information now to check if each path is of
		that particular size.
	*/
	//Check if it is also the shortest length as well.
	CHECK(std::size(ladders[0]) == shortestLength);
	CHECK(std::size(ladders[0]) == 58);
	unsigned long pathCount = 0;
	for (auto y : ladders) {
		unsigned long TotalWordCount = 0;
		for (auto x : y) {
			TotalWordCount++;
		}
		if (TotalWordCount == std::size(ladders[0])) {
			pathCount++;
		}
	}
	/*
		Now with the previous information, we are checking if the number
		of paths found is equal to all the paths there can be
		this proving there all of equal size.
	*/
	CHECK(std::size(ladders) == pathCount);

	/*
		Now despite confirming that we have the correct dimensions of ladders,
		We need to ensure that each path is valid by ensuring it does not violate
		the condition that each adjacent word differs by an alphabet.
	*/

	/*
		1. Check if each word are of a specific length before we check if
		they are adjacent or not. Depending on how we check if they are adjacent
		this step is important. If i were to run a nested loop and increment every time
		each char was different for equal index, then we might have the case
		where of words such as hello and hell. the difference between those words
		via that check is 1. hello and cello, the difference between those words via
		that way of checking is also 1. Hence we must check if all the words are of
		specific length
	*/
	unsigned long Words = 0;
	unsigned long ValidWords = 0;
	for (auto x : ladders) {
		for (auto y : x) {
			if (from.size() == y.size()) {
				ValidWords++;
			}
			Words++;
		}
	}
	/*
		If the number of words is equal to the number of valid words,
		this proves that all the words are of equal length and therefore
		we can move on and test if they are now adjacent or not.
	*/
	CHECK(Words == ValidWords);

	//Checking if each words in each path are adjacent to each other.
	bool check = false;
	for (auto x : ladders) {
		for (unsigned long i = 0, j = 1; j < x.size(); i++, j++) {
			if (!isAdjacent(x[i], x[j])) {
				check = true;
			}
		}
	}
	/*
		if check is false, than we havent found any pair of adjacent words
		that do not violate the condition that they differ by at most 1 letter.
		if check is true, then it indicates that we have violated that condition
		and hence there is a logical error in our algorithm.
	*/
	CHECK(check == false);

	/*
	   We now know that each path has not violated the condition that each adjacent word
	   differs by only 1 alphabet. Now must show that each Path starts from the word
	   "atlases" and ends in the word "cabaret". Thus proving that we have 840 paths, each
	   of the shortest length 58, each one starting from "atlases" and ending at "cabaret"
	   and each path not violating the condition that the adjacent words differ by only
	   1 alphabet.
	*/
	unsigned long CorrectStartAndEnd = 0;
	for (auto x : ladders) {
		if (x[0] == from and x[x.size()-1] == to) {
			CorrectStartAndEnd++;
		}
	}
	CHECK(CorrectStartAndEnd == std::size(ladders));

	/*
		Now, we can finally test if the order of insertion of each ladder in
		ladders has been sorted or not.
	*/
	CHECK(std::is_sorted(ladders.begin(), ladders.end()));
}

//More General Test cases which follow the exact same steps to validify
// this solution given the same type of parameters (given words are not adjacent,
// but there exists a path)

TEST_CASE("work", "play") {
	auto const english_lexicon = word_ladder::read_lexicon("english.txt");
	auto const ladders = word_ladder::generate("work", "play", english_lexicon);
	auto const shortestLength = BFS::NaiveBFS("work", "play", english_lexicon);
	auto const from = std::string{"work"};
	auto const to = std::string{"play"};

	CHECK(std::size(ladders) == 12);
	CHECK(std::size(ladders[0]) == shortestLength);
	CHECK(std::size(ladders[0]) == 7);

	unsigned long pathCount = 0;
	for (auto y : ladders) {
		unsigned long TotalWordCount = 0;
		for (auto x : y) {
			TotalWordCount++;
		}
		if (TotalWordCount == std::size(ladders[0])) {
			pathCount++;
		}
	}

	CHECK(std::size(ladders) == pathCount);

	unsigned long Words = 0;
	unsigned long ValidWords = 0;
	for (auto x : ladders) {
		for (auto y : x) {
			if (from.size() == y.size()) {
				ValidWords++;
			}
			Words++;
		}
	}

	CHECK(Words == ValidWords);

	bool check = false;
	for (auto x : ladders) {
		for (unsigned long i = 0, j = 1; j < x.size(); i++, j++) {
			if (!isAdjacent(x[i], x[j])) {
				check = true;
			}
		}
	}

	CHECK(check == false);

	unsigned long CorrectStartAndEnd = 0;
	for (auto x : ladders) {
		if (x[0] == from and x[x.size() - 1] == to) {
			CorrectStartAndEnd++;
		}
	}
	CHECK(CorrectStartAndEnd == std::size(ladders));

	CHECK(std::is_sorted(ladders.begin(), ladders.end()));
}

TEST_CASE("hello", "paste") {
	auto const english_lexicon = word_ladder::read_lexicon("english.txt");
	auto const ladders = word_ladder::generate("hello", "paste", english_lexicon);
	auto const shortestLength = BFS::NaiveBFS("hello", "paste", english_lexicon);
	auto const from = std::string{"hello"};
	auto const to = std::string{"paste"};

	CHECK(std::size(ladders) == 32);
	CHECK(std::size(ladders[0]) == shortestLength);
	CHECK(std::size(ladders[0]) == 8);

	unsigned long pathCount = 0;
	for (auto y : ladders) {
		unsigned long TotalWordCount = 0;
		for (auto x : y) {
			TotalWordCount++;
		}
		if (TotalWordCount == std::size(ladders[0])) {
			pathCount++;
		}
	}

	CHECK(std::size(ladders) == pathCount);

	unsigned long Words = 0;
	unsigned long ValidWords = 0;
	for (auto x : ladders) {
		for (auto y : x) {
			if (from.size() == y.size()) {
				ValidWords++;
			}
			Words++;
		}
	}

	CHECK(Words == ValidWords);

	bool check = false;
	for (auto x : ladders) {
		for (unsigned long i = 0, j = 1; j < x.size(); i++, j++) {
			if (!isAdjacent(x[i], x[j])) {
				check = true;
			}
		}
	}

	CHECK(check == false);

	unsigned long CorrectStartAndEnd = 0;
	for (auto x : ladders) {
		if (x[0] == from and x[x.size() - 1] == to) {
			CorrectStartAndEnd++;
		}
	}
	CHECK(CorrectStartAndEnd == std::size(ladders));

	CHECK(std::is_sorted(ladders.begin(), ladders.end()));
}
