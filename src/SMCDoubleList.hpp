// Copyright (c) 2024 Nathan Greenfield. All rights reserved
#pragma once
template <typename T>
class smcList
{
private:

	// Node only used internally to list
	struct Node
	{
		// Data in this node
		T mData;
		// Link to previous node
		Node* mPrev;
		// Link to next node
		Node* mNext;
	};

	// Pointer to the head node
	Node* mHead;
	// Pointer to the tail node
	Node* mTail;
	// Number of nodes currently in the list
	unsigned mSize;

public:
	// Iterator helper class...
	class Iterator
	{
	private:
		Node* mCurr; 
	public:
		// Needed for List access
		friend class smcList;
		// Constructors
		Iterator()
		{
			mCurr = nullptr;
		}

		Iterator(Node* inCurr)
		{
			mCurr = inCurr;
		}

		Iterator(const Iterator& src)
		{
			mCurr= src.mCurr;
		}

		// Assignment
		Iterator& operator=(const Iterator& src)
		{
			mCurr = src.mCurr;
			return *this;
		}

		// Incrementors / Decrementors
		// ++i
		Iterator& operator++()
		{
			mCurr = mCurr -> mNext;
			return *this; 
		}

		// i++
		Iterator operator++(int)
		{
			//create retval
			Iterator retval(*this);
			//increment mCurr
			mCurr = mCurr -> mNext;
			//return retval
			return retval;
		}

		// --i
		Iterator& operator--()
		{
			//decriment mCurr
			mCurr = mCurr -> mPrev;
			return *this; 
		}

		// i--
		Iterator operator--(int)
		{
			//save the current node
			Iterator retval(*this);
			//decriment mCurr
			mCurr = mCurr -> mPrev;
			//return previously saved node
			return retval; 
		}

		// Dereference
		T& operator*() const
		{
			return mCurr -> mData;
		}

		Node* operator->() const
		{
			return mCurr;
		}

		// Comparison
		bool operator==(const Iterator& rhs) const
		{
			// TODO: Fill in
			return (mCurr == rhs.mCurr);
		}

		bool operator!=(const Iterator& rhs) const
		{
			// TODO: Fill in
			return (mCurr != rhs.mCurr);
		}
	};

	// List functions...

	// Function: Default Constructor
	// Purpose: Initializes size to 0 and head/tail to null
	// Input: None
	// Returns: Nothing
	smcList()
	{
		mSize = 0;
		mHead = nullptr;
		mTail = nullptr;
	}

	// Function: Copy Constructor
	// Purpose: Initializes this list as a deep copy of other
	// Input: Other list to copy (const reference)
	// Returns: Nothing
	smcList(const smcList & other)
	{
		//1. Set size to 0, head to null, tail to null
		mSize = 0;
		mHead = nullptr;
		mTail = nullptr;
		// 2. Create a temp that points to the head node in “other”
		Node* temp = other.mHead;
		//3. While temp is not null...
		while(temp != nullptr)
		{
			//1. push_back temp’s data into this list
			push_back(temp->mData);
			//2. Advance temp to the next node
			temp = temp -> mNext;
		}
	}

	// Function: Destructor
	// Purpose: Calls the clear function to delete the list
	// Input: None
	// Returns: Nothing
	~smcList()
	{
		clear();
	}

	// Function: clear
	// Purpose: Deletes every node in this list, sets size to 0, and head/tail to null
	// Input: None
	// Returns: Nothing
	void clear()
	{
		//pop everything
		while(mHead != nullptr)
		{
			pop_front();
		}
	}

	// Assignment Operator
	// Function: Assignment Operator
	// Purpose: Clear this list, and then make a deep copy of other
	// Input: Other list to copy (const reference)
	// Returns: *this
	smcList& operator=(const smcList & other)
	{
		//empty new list
		clear();
		//temporary node to others head
		Node* temp = other.mHead;
		while(temp != nullptr)
			{
				//1. push_back temp’s data into this list
				push_back(temp->mData);
				//2. Advance temp to the next node
				temp = temp -> mNext;
			}
		return *this; 
	}

	// Function: size
	// Purpose: Gets the current size of the linked list
	// Input: None
	// Returns: size of the list
	unsigned size() const
	{
		return mSize;  
	}

	// Function: push_front
	// Purpose: Inserts a node at the front of the linked list
	// Input: Value to store in the new node
	// Returns: Nothing
	void push_front(const T & value)
	{
		//1. Dynamically allocate a new node
		Node* newFront = new Node;
		//a) Set its data to the value
		newFront->mData = value;
		//b) Set its previous to null (since this will be the new head)
		newFront -> mPrev = nullptr;
		//c) Set its next to the current head
		newFront-> mNext = mHead;
		//2. if size is 0, tail is new node
		if(mSize == 0)
		{
			mTail = newFront;
		}
		//3. Otherwise...set the previous of the current head to the new node
		else
		{
			mHead-> mPrev = newFront;
		}
		//4. Set the head to the new node
		mHead = newFront;
		//5. Increment the size
		mSize++;
	}

	// Function: front
	// Purpose: Gets the value of the node at the front of the list
	// Input: None
	// Returns: Value of the node at the front of the list
	T& front()
	{
		//check if empty
		if(mSize == 0)
		{
			throw std::out_of_range("list is empty!"); 
		}
		//return head data
		return mHead -> mData;
	}

	// Function: pop_front
	// Purpose: Removes the node at the front of the list
	// Input: None
	// Returns: None
	void pop_front()
	{
		//check if empty
		if(mSize == 0)
		{
			throw std::out_of_range("list is empty!");
		}
		//check if size is 1 (acts like default constructor)
		else if(mSize == 1)
		{
			//delete the head
			delete mHead;
			//set size to 0 and head and tail to null
			mSize = 0;
			mHead = nullptr;
			mTail = nullptr;
		}
		//Otherwise
		else
		{		
			// 1. Set a temp equal to the next node after head
			Node* temp = mHead -> mNext;
			// 2. Delete the head node
			delete mHead;
			// 3. The new head is temp
			mHead = temp; 
			// 4. The new head previous is now null
			mHead -> mPrev = nullptr;
			// 5. Decrement size
			mSize--;
		}
	}

	// Function: push_back
	// Purpose: Inserts a node at the end of the linked list
	// Input: Value to store in the new node
	// Returns: Nothing
	void push_back(const T & value)
	{
		//1. Dynamically allocate a new node
		Node* backNode = new Node;
		//a) Set its data to the value
		backNode -> mData = value; 
		//b) Set its previous to the current tail
		backNode -> mPrev = mTail;
		//c) Set the next to null (since this will be the new tail)
		backNode -> mNext = nullptr;
		//2. If the size is 0...The head is the new node
		if(mSize == 0)
		{
			mHead = backNode;
		}
		//3. Otherwise...set the next of the current tail to the new node
		else
		{
			mTail -> mNext = backNode;
		}
		//4. Set the tail to the new node
		mTail = backNode;
		//5. Increment the size
		mSize++;
	}

	// Function: front
	// Purpose: Gets the value of the node at the front of the list
	// Input: None
	// Returns: Value of the node at the front of the list
	T& back()
	{
		//check if empty
		if(mSize == 0)
		{
			throw std::out_of_range("list is empty!");
		}
		//retrun tail
		return  mTail -> mData; 
	}

	// Function: pop_back
	// Purpose: Removes the node at the end of the list
	// Input: None
	// Returns: None
	void pop_back()
	{
		//check if empty
		if(mSize == 0)
		{
			throw std::out_of_range("list is empty!");
		}
		//check if empty after pop
		else if(mSize == 1)
		{
			//delete the head
			delete mTail;
			//set size to 0 and head and tail to null
			mSize = 0;
			mHead = nullptr;
			mTail = nullptr;
		}
		else
		{
			// 1. Set a temp equal to the next node before tail
			Node* temp = mTail -> mPrev;
			// 2. Delete the head node
			delete mTail;
			// 3. The new head is temp
			mTail = temp; 
			// 4. The new head previous is now null
			mTail -> mNext = nullptr;
			// 5. Decrement size
			mSize--;
		}
	}

	// Function: begin
	// Purpose: Gets an iterator for the start of the list
	// Input: None
	// Returns: Iterator pointing to beginning of list
	Iterator begin() const
	{
		//check if empty
		if(mSize == 0)
		{
			throw std::out_of_range("list is empty");
		}
		//return iterator to head
		return Iterator(mHead);
	}

	// Function: end
	// Purpose: Gets an iterator for the end of the list
	// Input: None
	// Returns: Iterator pointing to end of list
	Iterator end() const
	{
		if(mSize == 0)
		{
			throw std::out_of_range("list is empty");
		}
		//one after the tail
		return Iterator(mTail -> mNext);
	}

	// Function: erase
	// Purpose: Removes the item at the node pointed to by i
	// Input: Iterator pointing to a valid node to remove before
	// Returns: A new iterator pointing to the node after the removed item
	Iterator erase(Iterator & i)
	{
		
		//1. If the iterator is invalid ... error!
		if (i == nullptr)
		{
			throw std:: out_of_range("cannot erase empty index");
		}
		//. If the iterator is at begin
		else if(i == begin())
		{
			//1. pop_front
			pop_front();
			//2. Return begin
			return Iterator(mHead);
		}
		//3. If the iterator is at the tail
		else if (i.mCurr == mTail)
		{
			//1. pop_back
			pop_back();
			//2. Return end
			return Iterator(mTail -> mNext);
		}
		//4. Otherwise...
		else
		{
			//1. Make “before”, “after”, and “toDel” pointers
			Node* before = i.mCurr -> mPrev;
			Node* after = i.mCurr -> mNext;
			Node* toDel = i.mCurr;
			//2. Delete “toDel”
			delete toDel;
			//3. Set before’s next to after
			before -> mNext = after;
			//4. Set after’s previous to before
			after -> mPrev = before;
			//5. Decrement size
			mSize--;
			//6. Return an iterator to after
			return Iterator(after);
		}
	}

	// Function: insert
	// Purpose: Inserts a list item before node pointed to by i
	// Input: Iterator pointing to a valid node to insert before
	// Returns: A new iterator pointing to the inserted value
	Iterator insert(Iterator & i, const T & val)
	{
		//1. If the iterator is invalid ... error!
		if(i == nullptr)
		{
			throw std::out_of_range("ivalid iterator");
		}
		//2. If the iterator is at begin
		else if(i == begin())
		{
			//push_front
			push_front(val);
			//2. Return begin
			return begin();
		}
		//3. If the iterator is at end
		else if(i.mCurr == mTail->mNext)
		{
			//1. push_back
			push_back(val);
			//2. Return iterator to last element (not end!)
			return Iterator(mTail);
		}
		//4. Otherwise...
		else
		{
			//1. Make “before” and “after” pointers
			Node* before = i.mCurr -> mPrev;
			Node* after = i.mCurr;
			//2. Dynamically allocate a new node
			Node *newNode = new Node;
			//a) Set its data to the value
			newNode -> mData = val;
			//b) Set its previous to before
			newNode -> mPrev = before;
			//c) Set its next to after
			newNode -> mNext = after;
			//3. Set before’s next to the new node
			before -> mNext = newNode;
			//4. Set after’s previous to the new node
			after -> mPrev = newNode;
			//5. Increment size
			mSize++;
			//6. Return an iterator pointing to the inserted node
			return Iterator(newNode);
		}
	}

public:
	// Function: Output Stream Operator
	// Purpose: Prints the contents of the list to the provided stream
	// Written in the format of {x, y, ..., z}
	// Input: Stream to write to, list to write
	// Output: Stream after values are written
	friend std::ostream& operator<<(std::ostream & os, const smcList<T>&list)
	{
		//temp set to other head
		Node* temp = list.mHead;
		//if list is empty
		if(list.mHead == nullptr)
		{
			os << "{";
		}
		//
		else
		{
			os<<"{"<<temp->mData;

			while(temp ->mNext != nullptr)
			{
				temp = temp -> mNext;
				os<<","<<temp->mData;
			}
		}
		os<<"}";
		return os;
	}

	// Function: toString
	// Purpose: Converts list to a string
	// Input: None
	// Output: String (in the format as the ostream)
	std::string toString() const
	{
		std::string output;
		Node* temp = mHead;
		if(mHead == nullptr)
		{
			output += "{";
		}
		else
		{
			output += "{";
			output += std::to_string(temp->mData);
			while(temp -> mNext != nullptr)
			{
				temp = temp->mNext;
				output += ",";
				output += std::to_string(temp->mData);
			}	
		}

		output+= '}';
		return output;
	}

	// Function: toReverseString
	// Purpose: Outputs the list in reverse
	// Input: None
	// Output: String in reverse
	std::string toReverseString() const
	{
		std::string output;
		Node* temp = mTail;
		if(mTail == nullptr)
		{
			output += "{";
		}
		else
		{
			output += "{";
			output += std::to_string(temp->mData);
			while(temp -> mPrev != nullptr)
			{
				temp = temp->mPrev;
				output += ",";
				output += std::to_string(temp->mData);
			}	
		}

		output+= '}';
		return output;
	}
};