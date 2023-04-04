#pragma once

#include <iostream>
#include "Attribute.h"
#include "custom_utlis.h"

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
	public:


		ListNode* next;
		ListNode* previous;

		T* data;
		int dataSize;
		int dataPopulated;

		ListNode() {
			previous = nullptr;
			next = nullptr;

			dataSize = 1;
			dataPopulated = 0;

			data = nullptr;
		}

		ListNode(ListNode& other) {
			previous = nullptr;
			next = nullptr;

			dataSize = other.dataSize;
			dataPopulated = other.dataPopulated;

			if (dataSize == 0) {
				data = nullptr;
				return;
			}

			data = new T[dataSize];
			for (int i = 0; i < dataPopulated; i++)
			{
				data[i] = other.data[i];
			}
		}

		ListNode& operator=(ListNode& other) {
			ListNode tmp = other;

			customSwap(next, tmp.next);
			customSwap(previous, tmp.previous);

			customSwap(data, tmp.data);

			dataSize = other.dataSize;
			dataPopulated = other.dataPopulated;

			return *this;
		}

		ListNode(int dataSize) : dataSize(dataSize) {
			previous = nullptr;
			next = nullptr;

			data = nullptr;
			dataPopulated = 0;
		}

		// Assuming the node is not full - otherwise => bad allocation
		void AddElement(T& otherData) {
			T* dataCopy = new T(otherData);
			if (data == nullptr) {
				data = new T[dataSize];
				dataPopulated = 0;
			}
			data[dataPopulated] = *dataCopy;
			dataPopulated += 1;
		}

		void AssignElement(T* otherDataPtr) {
			if (data == nullptr) {
				data = new T[dataSize];
				dataPopulated = 0;
			}

			data[dataPopulated] = *otherDataPtr;
			dataPopulated += 1;
		}

		/*void AssignAttributeElement(Attribute* otherDataPtr) {
			if (data == nullptr) {
				data = new T[dataSize];
				dataPopulated = 0;
			}

			for (int i = 0; i < dataPopulated; i++)
			{
				if (((Attribute)data[i]).DoesMatchName(otherDataPtr)) {
					data[i] = *otherDataPtr;
					return;
				}
			}

			data[dataPopulated] = *otherDataPtr;
			dataPopulated += 1;
		}*/


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

		// Assuming some elements exist
		/*void RemoveLastElement() {

			dataPopulated -= 1;

			//Should be deleting old data --> FIX this error
			delete& (data[dataPopulated]);
			data[dataPopulated] = T();

			if (dataPopulated == 0) {
				delete[] data;
				data = nullptr;
			}
		}*/

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
			RemoveLastNode();
		}
	}

	
	/*void AddElement(T& data) {
		if (tail == nullptr) {
			ListNode* newNode = new ListNode(nodeDataSize);
			newNode->AddElement(data);

			head = newNode;
			tail = newNode;

			return;
		}

		if (tail->dataSize == tail->dataPopulated) {
			AddNode(data);
			
			return;
		}

		tail->AddElement(data);
	}*/

	void AssignElement(T* data) {
		if (tail == nullptr) {
			ListNode* newNode = new ListNode(nodeDataSize);
			newNode->AssignElement(data);

			head = newNode;
			tail = newNode;

			return;
		}

		if (tail->dataSize == tail->dataPopulated) {
			AssignNode(data);

			return;
		}

		tail->AssignElement(data);
	}
	
	//Should probably be replaced with some extention of template etc.
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


		if (tail->dataSize == tail->dataPopulated) {
			AssignNode(attribute);

			return;
		}

		tail->AssignElement(attribute);
	}

	void RemoveLastElement() {
		tail->RemoveLastElement();

		if (tail->data == nullptr) {
			RemoveLastNode();
		}
	}

	void RemoveLastNode() {
		ListNode* prevTail = tail;

		bool hasOneNode = false;
		if (tail == head) {
			hasOneNode = true;
		}

		if (hasOneNode) {
			delete tail;
			tail = nullptr;
			head = nullptr;
		}
		else {
			tail = tail->previous;
			delete prevTail;
		}

		/*if (tail->previous != nullptr) {
			tail = tail->previous;
		}
		else {
			tail = nullptr;
			head = nullptr;
		}

		delete prevTail;
		prevTail = nullptr;*/
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
		int nodesCounter = 0;
		ListNode* iterator = head;
		while (iterator != nullptr)
		{
			int lowerBoundary = nodesCounter * nodeDataSize;
			int upperBoundary = (nodesCounter + 1) * nodeDataSize;
			if (elementIndex >= lowerBoundary && elementIndex < upperBoundary) {
				int exactIndex = elementIndex - lowerBoundary;
				return &iterator->data[exactIndex];
			}

			nodesCounter += iterator->dataPopulated;
			iterator = iterator->next;
		}

		return nullptr;
	}

	
	ListNode* GetHead() {
		return head;
	}
	
	ListNode* GetTail() {
		return tail;
	}

	
};

