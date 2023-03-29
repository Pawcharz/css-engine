#pragma once

template <typename T>
class List
{
private:

	class ListNode
	{
	public:
		T* data;
		ListNode* next;
		ListNode* previous;


		ListNode() {
			previous = nullptr;
			next = nullptr;

			data = nullptr;
		}

		ListNode(T& otherData) {
			previous = nullptr;
			next = nullptr;

			T* newData = new T(otherData);
			data = newData;
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

			delete data;
			data = nullptr;
		}
	};

	ListNode* head;
	ListNode* tail;

public:
	List() {
		head = nullptr;
		tail = nullptr;
	}

	~List() {

	}

	void AddNode(T& data) {
		ListNode* newNode = new ListNode(data);

		if (tail == nullptr) {
			head = newNode;
			tail = newNode;

			return;
		}

		tail->next = newNode;
		newNode->previous = tail;
		tail = newNode;
	}

	void Remove_Last() {
		ListNode* prevTail = tail;

		if (tail->previous != nullptr) {
			tail = tail->previous;
		}
		else {
			tail = nullptr;
		}

		delete prevTail;
	}
};

