#pragma once

#include <iostream>
#include "custom_utlis.h"
#include "Attribute.h"

using namespace std;

template <typename T>
class List
{
private:

	int nodeDataSize;

	void AddNode(T& data) {
		ListNode* newNode = new ListNode(nodeDataSize);
		newNode->AddElement(data);

		if (tail == nullptr) {
			head = newNode;
			tail = newNode;

			return;
		}

		tail->next = newNode;
		newNode->previous = tail;
		tail = newNode;
	}

	void AssignNode(T* data) {
		ListNode* newNode = new ListNode(nodeDataSize);
		newNode->AssignElement(data);

		if (tail == nullptr) {
			head = newNode;
			tail = newNode;

			return;
		}

		tail->next = newNode;
		newNode->previous = tail;
		tail = newNode;
	}

public:
	class ListNode
	{
	private:

		void UpdateDataPopulated() {
			dataPopulated = 0;

			bool hasAlreadyEncounter = false;

			for (int i = dataSize -1; i >= 0; i--)
			{
				if (!data[i].IsEmpty()) {
					if (!hasAlreadyEncounter) {
						lastNonemptyIndex = i;
					}

					dataPopulated += 1;
					hasAlreadyEncounter = true;
				}
			}
		}

	public:

		ListNode* next;
		ListNode* previous;

		T* data;
		int dataSize;

		int dataPopulated;

		int lastNonemptyIndex;

		ListNode() {
			previous = nullptr;
			next = nullptr;

			dataSize = 1;
			dataPopulated = 0;
			lastNonemptyIndex = 0;

			data = nullptr;
		}

		ListNode(ListNode& other) {
			previous = nullptr;
			next = nullptr;

			dataSize = other.dataSize;
			dataPopulated = other.dataPopulated;
			lastNonemptyIndex = other.lastNonemptyIndex;

			if (dataSize == 0) {
				data = nullptr;
				return;
			}

			data = new T[dataSize];
			for (int i = 0; i <= lastNonemptyIndex; i++)
			{
				data[i] = other.data[i];
			}
		}

		ListNode& operator=(ListNode& other) {
			ListNode tmp = other;

			customSwap(&next, &tmp.next);
			customSwap(&previous, &tmp.previous);

			customSwap(&data, &tmp.data);

			dataSize = other.dataSize;
			dataPopulated = other.dataPopulated;
			lastNonemptyIndex = other.lastNonemptyIndex;

			return *this;
		}

		ListNode(int dataSize) : dataSize(dataSize) {
			previous = nullptr;
			next = nullptr;

			data = nullptr;
			dataPopulated = 0;
			lastNonemptyIndex = INVALID_INDEX;
		}

		// Assuming the node is not full - otherwise => bad allocation
		void AddElement(T& otherData) {
			T* dataCopy = new T(otherData);
			if (data == nullptr) {
				data = new T[dataSize];
				dataPopulated = 0;
			}
			lastNonemptyIndex += 1;
			data[lastNonemptyIndex] = *dataCopy;

			dataPopulated += 1;
		}

		void AssignElement(T* otherDataPtr) {
			if (data == nullptr) {
				data = new T[dataSize];
				dataPopulated = 0;
			}

			lastNonemptyIndex += 1;
			data[lastNonemptyIndex] = *otherDataPtr;
			dataPopulated += 1;
		}

		~ListNode() {
			if (previous != nullptr) {
				previous->next = nullptr;
			}

			if (next != nullptr) {
				next->previous = nullptr;
			}

			previous = nullptr;
			next = nullptr;

			delete[] data;
			data = nullptr;
		}

		bool RemoveElement(int index) {

			if (data[index].IsEmpty()) {
				return false;
			}

			data[index].Reset();

			UpdateDataPopulated();
			return true;
		}

	};

private:
	ListNode* head;
	ListNode* tail;
	
public:
	List() {
		head = nullptr;
		tail = nullptr;

		nodeDataSize = 1;
	}

	List(List& other) {
		nodeDataSize = other.nodeDataSize;

		if (other.head == nullptr) {
			head = nullptr;
			tail = nullptr;

			return;
		}

		//head = new ListNode(*other.head);

		ListNode* iteratorOther = other.head;
		while (iteratorOther != nullptr)
		{
			AssignElement(iteratorOther->data);
			iteratorOther = iteratorOther->next;
		}
	}

	List(int nodeDataSize): nodeDataSize(nodeDataSize) {
		head = nullptr;
		tail = nullptr;
	}

	~List() {
		while (tail != nullptr)
		{
			RemoveNode(tail);
		}
	}


	void AssignElement(T* data) {
		if (tail == nullptr) {
			ListNode* newNode = new ListNode(nodeDataSize);
			newNode->AssignElement(data);

			head = newNode;
			tail = newNode;

			return;
		}

		if (tail->dataSize == tail->lastNonemptyIndex+1) {
			AssignNode(data);

			return;
		}

		tail->AssignElement(data);
	}
	
	// Assuming that attributeNodes have maxSize == 1
	void AssignAttributeElement(Attribute* attribute) {
		if (tail == nullptr) {
			ListNode* newNode = new ListNode(nodeDataSize);
			newNode->AssignElement(attribute);

			head = newNode;
			tail = newNode;

			return;
		}

		ListNode* iterator = head;
		while (iterator != nullptr)
		{
			if (iterator->data != nullptr && ((Attribute)iterator->data[0]).DoesMatchName(attribute) ) {

				iterator->data[0] = *attribute;
				return;
			}
			iterator = iterator->next;
		}


		if (tail->dataSize == tail->lastNonemptyIndex + 1) {
			AssignNode(attribute);

			return;
		}

		tail->AssignElement(attribute);
	}

	int GetElementsCount() {
		int counter = 0;
		ListNode* iterator = head;
		while (iterator != nullptr)
		{
			counter += iterator->dataPopulated;
			iterator = iterator->next;
		}

		return counter;
	}

	T* GetElement(int elementIndex) {
		int currentIndex = 0;
		ListNode* iterator = head;
		while (iterator != nullptr)
		{
			for (int i = 0; i <= iterator->lastNonemptyIndex; i++)
			{
				if (!iterator->data[i].IsEmpty()) {
					if (currentIndex == elementIndex) {
						return &iterator->data[i];
					}
					currentIndex += 1;
				}
			}

			iterator = iterator->next;
		}

		return nullptr;
	}


	bool RemoveElement(int elementIndex) {

		int currentIndex = 0;
		ListNode* iterator = head;
		while (iterator != nullptr)
		{

			for (int i = 0; i <= iterator->lastNonemptyIndex; i++)
			{
				if (!iterator->data[i].IsEmpty()) {
					if (currentIndex == elementIndex) {

						bool wereRemoved = iterator->RemoveElement(i);

						if (wereRemoved && iterator->dataPopulated == 0) {
							//cout << "REMOVE NODE" << endl;
							// ADD - remove node !!!
							RemoveNode(iterator);
						}
						return wereRemoved;
					}
					currentIndex += 1;
				}
			}

			iterator = iterator->next;
		}

		return false;
	}

	void RemoveNode(ListNode* node) {
		if (head == tail) {
			head = nullptr;
			tail = nullptr;
		}
		else if (node == head) {
			head = node->next;
		}
		else if (node == tail) {
			tail = node->previous;
		}

		delete node;
		node = nullptr;
		return;
	}

	
	ListNode* GetHead() {
		return head;
	}
	
	ListNode* GetTail() {
		return tail;
	}
};

