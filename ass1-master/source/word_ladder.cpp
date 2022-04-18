#include "comp6771/word_ladder.hpp"
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <list>
#include <queue>
#include <vector>
// Write your implementation here
namespace word_ladder {
	//Standard recursive DFS to find all paths.
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

	void LevelBFS(std::queue<std::string>& Q,
	              std::unordered_map<std::string, std::vector<std::string>>& Parents,
	              std::unordered_map<std::string, int>& Visited1,
	              std::unordered_map<std::string, int>& Visited2,
	              bool& Intersection,
	              int& Depth,
	              bool const& side,
	              std::unordered_set<std::string> const& lexicon) {
	    //Since its a Level BFS, we need to keepcount of the initial given Q size
	    //and pop every node of level = depth out, so we can do appropriate checks.
		for (auto QSize = Q.size(); QSize > 0; --QSize) {
			auto Parent = Q.front();
			Q.pop();
			auto Child = Parent; //child = Parent, since child is going to be modified.
			for (std::string::size_type i = 0; i < Child.size(); i++) {
				auto s = Child[i];
				for (auto c = 'a'; c <= 'z'; c++) {
					Child[i] = c; //replace that index's character
					if (c == s) {
						continue;
					}
					if (lexicon.find(Child) != lexicon.end()) { // If child is a vertex
						//check if it has never been found before
						if (Visited1.find(Child) == Visited2.end()) {
							if (side) {
								Parents[Child].push_back(Parent);
							}
							else {
								Parents[Parent].push_back(Child);
							}
							Visited1[Child] = Depth; //update its Visited Map accordingly
							Q.push(Child); //Push Child into Q
						}
						//if it has been found make sure it is of the same depth
						else if (Visited1[Child] == Depth) {
							if (side) {
								Parents[Child].push_back(Parent);
							}
							else {
								Parents[Parent].push_back(Child);
							}
						}
						//This helps us check for intersecting words.
						if (Visited2.find(Child) != Visited2.end()) {
							Intersection = true;
						}
					}
				}
				Child[i] = s;
			}
		}
	}

	auto generate(std::string const& from,
	              std::string const& to,
	              std::unordered_set<std::string> const& lexicon)
	   -> std::vector<std::vector<std::string>> {
		// Initialise Everything necessary
		//FrontVisited is to keep track of all the nodes (and there depths)
		//visited from the source node - "from"
		auto FrontVisited = std::unordered_map<std::string, int>{};
		// BackVisited is to keep track of all the nodes (and there depths)
		// visited from the source node - "from"
		auto BackVisited = std::unordered_map<std::string, int>{};
		//Need Seperate Q's for the nodes being traversed from both "from" and "to"
		auto FrontQ = std::queue<std::string>{};
		auto BackQ = std::queue<std::string>{};
		//Parents, a string (the Child Node) maps to its vector of Parents- Used for Recursive DFS
		auto Parents = std::unordered_map<std::string, std::vector<std::string>>{};
		auto Depth = 1; // defined out of loop needs to have initial value
		//Important variable which keeps track if theres been a node inserted in both
		//FrontVisited and BackVisited
		auto Intersection = false; //defined out of loop needs to have initial value
		FrontVisited[from] = 1;
		BackVisited[to] = 1;
		FrontQ.push(from), BackQ.push(to);
		while (!FrontQ.empty() || !BackQ.empty()) {
			/*  1. This step is simple, we have a LevelBFS function which does a breadth first search
			               Level by Level, so we can have a level by level search if there are any
			   intersecting nodes, note there are 2 if statements, indicating either traversal from
			   "from" and "to" can identify intersecting nodes first.
			            2. Note how the FrontQ is BackQ are substituted this identifies where the
			   traversal is being done from FrontQ is for traversal from "from" and BackQ is for
			   traversals from "to"
			            3. FrontVisited and BackVisited are swapped around due to how LevelBFS is
			   implemented, this allows for generalisations and lets me use 1 function for both
			   traversals.
			            4. Note how we have a "true" and "false", these bools can helps us modify how
			   we update our Parents map, ensuring it is consistent and contributes to how it can be
			   used for both types of traversals.
			         */
			LevelBFS(FrontQ,Parents,FrontVisited,BackVisited,Intersection,Depth,true,lexicon);
			if (Intersection) break;
			LevelBFS(BackQ,Parents,BackVisited,FrontVisited,Intersection,Depth,false,lexicon);
			if (Intersection) break;
			Depth++;
		}
		//We use a list here instead of a vector, since it has a unique ability to
		//push nodes in the front and pop nodes from the front.
		auto currentPath2 = std::list<std::string>{};
		auto TotalPaths2 = std::vector<std::vector<std::string>>{};
		DFSPathFinder(to, from, Parents, currentPath2, TotalPaths2);
		sort(TotalPaths2.begin(), TotalPaths2.end());
		return TotalPaths2;
	}
}