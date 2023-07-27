#include <iostream>
#include <optional>

using namespace std;

class Node {
public:
	int key;
	int degree = 0;
	Node *parent;
	Node *child;
	Node *sibling;
	~Node()
	{
		delete parent;
		delete child;
		delete sibling;
	}
	Node();
	Node(int key);
	int compareTo(Node *other);
	void print(int level);
};

class BinomialHeap {
private:
	Node *head;
	void removeTreeRoot(Node *root, Node *prev);
	void linkTree(Node *minNodeTree, Node *other);
	Node *union_Renamed(BinomialHeap *heap);
	Node *merge(BinomialHeap *heap1, BinomialHeap *heap2);
public:
	BinomialHeap();
	~BinomialHeap()
	{
		delete head;
	}
	BinomialHeap(Node *head);
	void insert(int key);
	int extractMin();
	void print();
};