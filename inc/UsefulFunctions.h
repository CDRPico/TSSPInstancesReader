// Created by CDRPico
// 09/06/2020 22:18

using namespace std;
#include<vector>
#include<iostream>

//Takes a vector which contains a string and split it based on char ch definition
//It returns a vector of strings where every position is a segment between two ch
size_t split(const string &txt, vector<string> &strs, char ch)
{
	size_t pos = txt.find(ch);
	size_t initialPos = 0;
	strs.clear();

	// Decompose statement
	while (pos != string::npos) {
		if (!txt.substr(initialPos, pos - initialPos).empty()) {
			strs.push_back(txt.substr(initialPos, pos - initialPos));
		}
		initialPos = pos + 1;

		pos = txt.find(ch, initialPos);
	}

	// Add the last one
	strs.push_back(txt.substr(initialPos, min(pos, txt.size()) - initialPos + 1));

	return strs.size();
}