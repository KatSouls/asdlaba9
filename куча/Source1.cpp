#include <iostream>
//#include <optional>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <cctype>
#include <stdlib.h>
#include < sstream>
#include "Header.h"

using namespace std;

Node::Node()
{
	key = 0;
}

Node::Node(int key)
{
	this->key = key;
}

int Node::compareTo(Node *other)
{
	if (this->key > other->key)
	{
		return 1;
	}
	else if(this->key < other->key)
	{
		return -1;
	}
	else return 0;
}

void Node::print(int level)
{
	string str;
	string str1;
	Node *curr = this;
	if (curr->parent == nullptr)
	{
		cout << endl;
	}
	while (curr != nullptr)
	{
		string sb;
		for (int i = 0; i < level; i++)
		{
			if (i == 0)
			{
				sb.append(" ");
			}
			else
			{
				sb.append("|  ");
			}
		}
		if (curr->parent != nullptr && curr->child != nullptr)
		{
			sb.append("|-");
			int a1 = curr->key;
			sb.append(to_string(a1));
		}
		else
		{
			sb.append("|-");
			int a = curr->key;
			sb.append(to_string(a));
		}
		cout << sb << endl;
		if (curr->child != nullptr)
		{
			curr->child->print(level + 1);
		}
		curr = curr->sibling;
	}
}

BinomialHeap::BinomialHeap()
{
	head = nullptr;
}

BinomialHeap::BinomialHeap(Node *head)
{
	this->head = head;
}

void BinomialHeap::insert(int key)
{
	Node *node = new Node(key);
	BinomialHeap *tempHeap = new BinomialHeap(node);
	head = union_Renamed(tempHeap);
}

int BinomialHeap::extractMin()
{
	if (head == nullptr)
	{
		return 0;
	}
	Node *min = head;
	Node *minPrev = nullptr;
	Node *next = min->sibling;
	Node *nextPrev = min;
	while (next != nullptr)
	{
		if (next->compareTo(min) < 0)
		{
			min = next;
			minPrev = nextPrev;
		}
		nextPrev = next;
		next = next->sibling;
	}
	removeTreeRoot(min, minPrev);
	return min->key;
}

void BinomialHeap::removeTreeRoot(Node *root, Node *prev)
{
	if (root == head)
	{
		head = root->sibling;
	}
	else
	{
		prev->sibling = root->sibling;
	}
	Node *newHead = nullptr;
	Node *child = root->child;
	while (child != nullptr)
	{
		Node *next = child->sibling;
		child->sibling = newHead;
		child->parent = nullptr;
		newHead = child;
		child = next;
	}
	BinomialHeap *newHeap = new BinomialHeap(newHead);
	head = union_Renamed(newHeap);
}

void BinomialHeap::linkTree(Node *minNodeTree, Node *other)
{
	other->parent = minNodeTree;
	other->sibling = minNodeTree->child;
	minNodeTree->child = other;
	minNodeTree->degree++;
}

Node *BinomialHeap::union_Renamed(BinomialHeap *heap)
{
	Node *newHead = merge(this, heap);
	head = nullptr;
	heap->head = nullptr;
	if (newHead == nullptr)
	{
		return nullptr;
	}
	Node *prev = nullptr;
	Node *curr = newHead;
	Node *next = newHead->sibling;

	while (next != nullptr)
	{
		if (curr->degree != next->degree || (next->sibling != nullptr && next->sibling->degree == curr->degree))
		{
			prev = curr;
			curr = next;
		}
		else
		{
			if (curr->compareTo(next) < 0)
			{
				curr->sibling = next->sibling;
				linkTree(curr, next);
			}
			else
			{
				if (prev == nullptr)
				{
					newHead = next;
				}
				else
				{
					prev->sibling = next;
				}

				linkTree(next, curr);
				curr = next;
			}
		}
		next = curr->sibling;
	}
	return newHead;
}

Node *BinomialHeap::merge(BinomialHeap *heap1, BinomialHeap *heap2)
{
	if (heap1->head == nullptr)
	{
		return heap2->head;
	}
	else if (heap2->head == nullptr)
	{
		return heap1->head;
	}
	else
	{
		Node *head;
		Node *heap1Next = heap1->head;
		Node *heap2Next = heap2->head;

		if (heap1Next->degree <= heap2Next->degree)
		{
			head = heap1->head;
			heap1Next = heap1Next->sibling;
		}
		else
		{
			head = heap2->head;
			heap2Next = heap2Next->sibling;
		}

		Node *tail = head;

		while (heap1Next != nullptr && heap2Next != nullptr)
		{
			if (heap1Next->degree <= heap2Next->degree)
			{
				tail->sibling = heap1Next;
				heap1Next = heap1Next->sibling;
			}
			else
			{
				tail->sibling = heap2Next;
				heap2Next = heap2Next->sibling;
			}

			tail = tail->sibling;
		}

		if (heap1Next != nullptr)
		{
			tail->sibling = heap1Next;
		}
		else
		{
			tail->sibling = heap2Next;
		}

		return head;
	}
}

void BinomialHeap::print()
{
	if (head != nullptr)
	{
		head->print(0);
	}
}
