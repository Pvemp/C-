// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef COMP6771_BFS_HPP
#define COMP6771_BFS_HPP

#include <unordered_set>
#include <string>
#include <vector>
#include <utility>

namespace BFS {
    //Given a valid source and destination word find the length of the shortest path
	 [[nodiscard]] auto NaiveBFS(std::string const& from,
	                                           std::string const& to,
	                                           std::unordered_set<std::string> const& lexicon)
	    -> unsigned long;

} // namespace BFS

#endif // COMP6771_BFS_HPP