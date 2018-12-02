//#include "stdafx.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <utility>

using std::cin;
using std::cout;
using std::endl;
using std::make_pair;
using std::pair;
using std::string;
using std::vector;

const int letters = 5;
size_t letterToInt(char c) {
	switch (c) {
	case '$': return 0; break;
	case 'A': return 1; break;
	case 'C': return 2; break;
	case 'G': return 3; break;
	case 'T': return 4; break;
	default: return letters+1;
	}
}
//Given a string returns the sorted order of the character
vector<int> SortCharacters(const string& S) {
	vector<int> order(S.size(),-1);
	vector<int> count(letters, 0);
	for (char c : S) {
		count[letterToInt(c)]++;
	}
	for (int i = 1;i < count.size();++i) {
		count[i] += count[i - 1];
	}
	for (int idx = S.size() - 1;idx >= 0;--idx) {
		count[letterToInt(S[idx])]--;
		order[count[letterToInt(S[idx])]] = idx;
	}
	return order;
}

//Computes the classes for the String S and its sorted order
vector<int> ComputeCharClasses(const string& S, const vector<int>& order) {
	vector<int> classes(order.size(), -1);

	//initialize the class for the first char(usually it is '$')
	classes[order[0]] = 0;
	for (int idx = 1;idx < order.size();++idx) {
		if (S[order[idx]] == S[order[idx - 1]]) {
			classes[order[idx]] = classes[order[idx - 1]];
		}
		else {
			classes[order[idx]] = classes[order[idx - 1]] + 1;
		}
	}

	return classes;
}

vector<int> SortDoubled(const string& S, int L, 
	const vector<int>& order, const vector<int>& classes) {
	vector<int> newOrder(S.size(), -1);

	//this is similar to count in counting sort, but since
	//here we will be sorting the equivalence classes of cyclic shift of length L
	//and there can at most S.size() such classes
	vector<size_t> count(S.size(), 0);

	//standard counting sort loops for the counting part of the sort
	for (int idx = 0;idx < S.size();++idx) {
		count[classes[idx]]++;
	}
	for (int idx = 1;idx < S.size();++idx) {
		count[idx] += count[idx - 1];
	}

	//now the sort loop
	for (int idx = S.size() - 1;idx >= 0;--idx) {
		// Variable startstart goes through the starts of the 
		// doubled cyclic shifts in the reversed order of their sorted by second halves, 
		// not in the direct order.
		int start = (order[idx]-L+S.size())%S.size();

		//rest is regular counting sort
		//class of the first half of the double shift, by which we want to sort
		int cl = classes[start]; 
		count[cl]--;//decrease the partial sum for this class
		newOrder[count[cl]] = start;
	}
	return newOrder;
}

vector<int> UpdateClasses(const vector<int>& newOrder, const vector<int>& classes, int L) {
	int n = newOrder.size();
	vector<int> newClasses(n, 0);
	newClasses[newOrder[0]] = 0;
	for (int i = 1;i < n;++i) {
		int curr = newOrder[i];
		int prev = newOrder[i - 1];
		int mid = (curr + L) % n;
		int midPrev = (prev + L) % n;
		if (classes[curr] == classes[prev] && classes[mid] == classes[midPrev]) {
			newClasses[curr] = newClasses[prev];
		}
		else {
			newClasses[curr] = newClasses[prev] + 1;
		}
	}
	return newClasses;
}
// Build suffix array of the string text and
// return a vector result of the same length as the text
// such that the value result[i] is the index (0-based)
// in text where the i-th lexicographically smallest
// suffix of text starts.
vector<int> BuildSuffixArray(const string& S) {
  vector<int> order = SortCharacters(S);
  vector<int> classes = ComputeCharClasses(S, order);
  int L = 1;
  while (L <= S.size()) {
	  order = SortDoubled(S, L, order, classes);
	  classes = UpdateClasses(order, classes, L);
	  L *= 2;
  }
  return order;
}

int main() {
  string text;
  cin >> text;
  vector<int> suffix_array = BuildSuffixArray(text);
  for (int i = 0; i < suffix_array.size(); ++i) {
    cout << suffix_array[i] << ' ';
  }
  cout << endl;
  return 0;
}
