#pragma once
#include "Node.h"
#include <exception>

namespace LinkedList
{
	// Precondition: headPtr points to the head of a list
	// Postcondition: Info has been inserted at the head of the list, and headPtr is updated
	template<typename T>
	void headInsert(Node<T>*& headPtr, T info)
	{
		headPtr = new Node<T>(info, headPtr);
	}


	// Precondition: headPtr points to the head of a list
	// Postcondition: The head element has been removed and headPtr is updated to point to the new head element
	template<typename T>
	void headRemove(Node<T>*& headPtr)
	{
		if (headPtr == nullptr)
			throw std::exception("Nullptr exception");

		Node<T>* tmp = headPtr;
		headPtr = headPtr->next;
		delete[] tmp;
	}


	// Precondition: prevPtr points to Node just before insertion point
	// Postcondition: A new Node with data=info has been inserted into the list after prevPtr
	template<typename T>
	void insert(Node<T>*& prevPtr, T info)
	{
		if (prevPtr == nullptr)
			throw std::exception("Nullptr exception");
		else
		{
			Node<T>* tmp = prevPtr->next;
			Node<T>* p = new Node<T>(info, tmp);
			prevPtr->next = p;
		}
	}


	// Precondition: prevPtr points to Node just before Node to remove
	// Postcondition: The Node after prevPtr has been removed from the list
	template<typename T>
	void remove(Node<T>*& prevPtr)
	{
		if (prevPtr == nullptr || prevPtr->next == nullptr)
			throw std::exception("Nullptr exception");
		else
		{
			Node<T>* tmp = prevPtr->next;
			prevPtr->next = prevPtr->next->next;
			delete[] tmp;
		}
		
	}

	// Precondition: sourcePtr is the head pointer of a linked list.
	// Postcondition: A pointer to a deep copy of the linked list is returned. The original list is unaltered.
	template<typename T>
	Node<T>* copy(Node<T>*& sourcePtr)
	{
		if (sourcePtr == nullptr)
			return nullptr;

		Node<T>* cpy = new Node<T>(sourcePtr->info,nullptr);
		Node<T>* i = cpy;

		for (sourcePtr; sourcePtr->next != nullptr; sourcePtr = sourcePtr->next)
		{
			i->next = new Node<T>(sourcePtr->next->info);
			i = i->next;
		}

		return cpy;
	}

	// Precondition: sourcePtr is the head pointer of a linked list.
	// Postcondition: A pointer to a deep copy of the linked list is returned. The original list is unaltered.
	template<typename T>
	Node<T>* clone(Node<T>*& sourcePtr)
	{
		return sourcePtr==nullptr ? nullptr : new Node<T>(sourcePtr->info, clone(sourcePtr->next));
	}

	//Precondtion: headPtr is the head pointer of a linked list.
	//Postcondition: All nodes of the list have been deleted, and the headPtr is NULL
	template<typename T>
	void clear(Node<T>*& headPtr)
	{
		Node<T>* tmp;
		while (headPtr != nullptr)
		{
			tmp = headPtr->next;
			delete[] headPtr;
			headPtr = tmp;
		}
	}

	// Precondition: headPtr is the head pointer of a linked list.
	// Postcondition: The data item of each Node in the list has been printed to the screen in an easily readable way, e.g. “3 - 4 - 7 -/”
	template<typename T>
	void print(Node<T>*& headPtr)
	{
		for (Node<T>* i = headPtr; i != nullptr; i = i->next)
		{
			std::cout << i->info << "-";
		}
		std::cout << "/";
	}

	// Precondition: headPtr is the head pointer of a linked list.
	// Postcondition: headPtr points to the start of a list that is reversed with respect to the original list
	template<typename T>
	void reverse(Node<T>*& headPtr)
	{
		if (headPtr == nullptr)
			return;

		Node<T>* prev = nullptr;
		Node<T>* current = headPtr;
		Node<T>* nxt = nullptr;
		while (current != nullptr)
		{
			nxt = current->next;
			current->next = prev;
			prev = current;
			current = nxt;
		}
		headPtr = prev;
	}

	// Precondition: splitPtr points to the node before the split point
	// Postcondition: A pointer is returned that points to the first node after splitPtr. The
	// original list ends at the node pointed to by splitPtr
	template<typename T>
	Node<T>* split(Node<T>*& splitPtr)
	{
		if (splitPtr == nullptr)
			throw std::exception("Nullptr exception");

		Node<T>* split = splitPtr->next;
		splitPtr->next = nullptr;
		return split;
	}

	// Precondition: values points to an array of at least size n
	// Postcondition: A pointer is returned that points to the head of a list in which the nodes
	// contains values from the array values
	template<typename T>
	Node<T>* build(int* values, size_t n)
	{
		if (values == nullptr)
			throw std::exception("Nullptr exception");
		
		Node<T>* headPtr = nullptr;
		for (size_t i = n; i-- > 0;)
		{
			headInsert(headPtr, values[i]);
		}
		return headPtr;
	}

	// Precondition: head1 and head2 each point to the head of linked lists
	// Postcondition: head1 points to a list containing head1-lists' elements followed by head2-lists element.
	template<typename T>
	void join(Node<T>*& head1, Node<T>* head2)
	{
		if (head1 == nullptr)
			throw std::exception("Nullptr exception");
		if (head1 == head2)
			throw std::invalid_argument("head1 is equal to head2");
		Node<T>* i = head1;
		for (i; i->next != nullptr;i = i->next);
		i->next = head2;
	}

	// Precondition: head points to the head of a linked list
	// Postcondition: The list is rotated left by once - if it was 1-2-3-4, it is now 2-3-4-1
	template<typename T>
	void rotateLeft(Node<T>*& head)
	{
		if (head == nullptr)
			throw std::exception("Nullptr exception");
		
		Node<T> first = head;
		head = head->next;
		for (Node<T>* i = head; i != nullptr; i = i->next)
		{

		}
	}

	// Precondition: head points to the head of a linked list
	// Postcondition: The list is rotated right once - if it was 1-2-3-4, it is now 4-1-2-3
	template<typename T>
	void rotateRight(Node<T>*& head)
	{

	}


}