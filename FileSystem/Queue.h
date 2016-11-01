#pragma once

template<typename T>
class Queue
{
private:
	class Node
	{
	public:
		T data;
		Node *next;
		Node(T const& _data, Node* _next = nullptr) : data(_data), next(_next) {}
		~Node() {}
	};

	Node *root;
	Node *tail;
	size_t nrOfElements;

public:

	Queue()
	{
		nrOfElements = 0;
		root = nullptr;
		tail = nullptr;
	}

	virtual ~Queue()
	{
		Node *trash, *walker = root;
		
		while (walker != nullptr)
		{
			trash = walker;
			walker = walker->next;
			delete trash;
		}
	}

	void enqueue(T const& data)
	{
		if (tail != nullptr)
		{
			tail->next = new Node(data);
			tail = tail->next;
		}
		else
		{
			root = new Node(data);
			tail = root;
		}

		nrOfElements++;
	}

	T dequeue()
	{
		if (nrOfElements == 0)
			throw out_of_range("queue empty");

		T output;
		Node* trash;

		trash = root;
		root = trash->next;
		output = trash->data;
		delete trash;

		nrOfElements--;

		return output;		
	}

	size_t size()
	{
		return nrOfElements;
	}

	void empty()
	{
		Node *trash, *walker = root;

		while (walker != nullptr)
		{
			trash = walker;
			walker = walker->next;
			delete trash;
		}
		
		root = nullptr;
		tail = nullptr;
		nrOfElements = 0;
	}
};

