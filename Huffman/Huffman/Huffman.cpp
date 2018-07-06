// Huffman.cpp : Defines the entry point for the console application.
//

// 1. Using struct OOP
// 2. Using std objects
// 3. Creating comparator objects to feed into priority queue
// 4. String Nulls
// 5. Pointers
// 6. Iterators

#include "stdafx.h"
#include "iostream"
#include "string"
#include "queue"
#include "unordered_map"
#include "stack"
#include "utility"
using namespace std;

struct mNode {
	int val;
	char ch;
	mNode* left;
	mNode* right;

	mNode(char ch, int val) {
		left = right = NULL;
		this->val = val;
		this->ch = ch;
	}
};

struct comPair {

	bool operator()(mNode* p1, mNode* p2)
	{
		return p1->val > p2->val;
	}
};



int main()
{
	string monkey = "This is a test.";
	unordered_map<char, int> counter;
	cout << "Hello World\n";
	cout << monkey << "\n";


	// Pre-Tree Work
	// 1. Count all Chars - (Except newline, tbd)
	// 
	// 
	for (int i = 0; i < monkey.size(); i++) {
		auto temp = counter.find(monkey[i]);
		if (temp == counter.end()) counter[monkey[i]] = 1;
		else counter[monkey[i]] += 1;
	}

	for (auto pair : counter) {
		cout << pair.first << " : " << pair.second << "\n";
	}
	cout << endl;
	// Generate Codes
	// 1. Feed into Priority Queue
	// 2. Create Tree
	// 3. Assign Codes
	// 
	priority_queue< mNode*, std::vector<mNode*>, comPair > pq;

	for (auto pair : counter) {
		struct mNode *mn;
		mn = new mNode(pair.first, pair.second);
		pq.push(mn);
	}
	cout << pq.size() << endl;;
	// Feed in key:values
	unordered_map<char, string> codes;

	while (pq.size() > 1) {
		mNode* temp1 = pq.top();
		cout << temp1->ch << " : " << temp1->val << "|";
		pq.pop();
		mNode* temp2 = pq.top();
		pq.pop();

		cout << temp2->ch << " : " << temp2->val << endl;
		struct mNode* parent;
		parent = new mNode('\0', temp1->val + temp2->val);
		parent->left = temp1;
		parent->right = temp2;
		pq.push(parent);

	}
	mNode* current = pq.top();
	cout << "printing codes" << endl;
	stack< pair<mNode*, string>> walker;
	string code = "";
	walker.push(make_pair(current, code));
	pair<mNode*, string> temp;
	while (!walker.empty()) {
		temp = walker.top();
		walker.pop();
		mNode* mn = temp.first;
		code = temp.second;

		if (!mn) {
			cout << "DOUB";

		}
		else if (mn->ch != '\0') {
			codes[mn->ch] = code;
		}
		else {
			walker.push(make_pair(mn->left, code + "0"));
			walker.push(make_pair(mn->right, code + "1"));

		}
	}


	cout << "printing codes2" << endl;
	for (auto pair : codes) {
		cout << pair.first << " : " << pair.second << endl;
		cout << typeid(pair.first).name() << endl;
	}
	cout << codes.size() << endl;
	cout << "printing codes2" << endl;
	string output = "";

	for (int i = 0; i < monkey.size(); i++) {
		string t = codes[monkey[i]];
		output = output + t;

	}

	cout << output << endl;


	// Generate Codes
	cout << "Done";
	return 0;
}


