#pragma once

template <typename T>
class List
{
private:

	int nodeDataSize;

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

			data = nullptr;
		}

		ListNode(int dataSize): dataSize(dataSize){
			previous = nullptr;
			next = nullptr;

			data = nullptr;
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

		void AddElement(T* otherDataPtr) {
			if (data == nullptr) {
				data = new T[dataSize];
				dataPopulated = 0;
			}
			data[dataPopulated] = *otherDataPtr;
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

		// Assuming some elements exist
		void RemoveLastElement() {

			dataPopulated -= 1;

			//Should be deleting old data --> FIX this error
			//delete& (data[dataPopulated]);
			//data[dataPopulated] = T();

			if (dataPopulated == 0) {
				delete[] data;
				data = nullptr;
			}
		}
	};

	ListNode* head;
	ListNode* tail;


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

	void AddNode(T* data) {
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

public:
	List() {
		head = nullptr;
		tail = nullptr;

		nodeDataSize = 1;
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

	
	void AddElement(T& data) {
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
	}

	void AddElement(T* data) {
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
};

