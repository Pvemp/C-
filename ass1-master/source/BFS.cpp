#include "comp6771/BFS.hpp"
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <list>
#include <queue>
#include <vector>
#include <utility>

//Naive BFS implementation

namespace BFS {
	void DFSPathFinder(std::string node,
	                   std::string from,
	                   std::unordered_map<std::string, std::vector<std::string>>& Predecessors,
	                   std::list<std::string>& currentPath,
	                   std::vector<std::vector<std::string>>& TotalPaths) {
		currentPath.push_front(node);
		if (node == from) {
			std::vector<std::string> V(currentPath.begin(), currentPath.end());
			TotalPaths.push_back(V);
		}
		else {
			for (auto const& parent : Predecessors[node]) {
				DFSPathFinder(parent, from, Predecessors, currentPath, TotalPaths);
			}
		}
		currentPath.pop_front();
	}

	auto NaiveBFS(std::string const& from,
	              std::string const& to,
	              std::unordered_set<std::string> const& lexicon)
	   -> unsigned long {
		auto VisitedMap = std::unordered_map<std::string, unsigned long> {};
		auto Predecessors = std::unordered_map<std::string, std::vector<std::string>>{};
		auto StringQ = std::queue<std::string> {};
		auto DepthQ = std::queue<unsigned long> {};
		StringQ.push(from);
		DepthQ.push(1);
		VisitedMap[from] = 1;
		while (!StringQ.empty()) {
			auto Depth = DepthQ.front();
			auto Vertex = StringQ.front();
			DepthQ.pop(), StringQ.pop();
			if (VisitedMap.find(to) != VisitedMap.end() && Depth > VisitedMap[to]) {
				break;
			}
			auto Holder = Vertex;
			for (std::string::size_type i = 0; i < Holder.size(); i++) {
				char s = Holder[i];
				for (char c = 'a'; c <= 'z'; c++) {
					Holder[i] = c;
					if (s == c) {
						continue;
					}
					if (lexicon.find(Holder) != lexicon.end()) { // If it is an edge of Vertex
						if (VisitedMap.find(Holder) == VisitedMap.end()) { // If it has never ever been
							VisitedMap[Holder] = Depth, StringQ.push(Holder),
							Predecessors[Holder].push_back(Vertex);
							DepthQ.push(Depth + 1); // Update
						}
						else if (VisitedMap[Holder] == Depth) {
							Predecessors[Holder].push_back(Vertex);
						}
					}
				}
				Holder[i] = s;
			}
		}
		/*
		std::list<std::string> currentPath2;
		std::vector<std::vector<std::string>> TotalPaths2;
		DFSPathFinder(to, from, Predecessors, currentPath2, TotalPaths2);
		sort(TotalPaths2.begin(), TotalPaths2.end());
		*/
		return VisitedMap[to] + 1;
	}
}