
public class List {
	//private inner class Node
	private class Node{
		Node next;
		Node prev;
		int data;
		
		//constructor - creating Node with data, next and prev
		Node(int data1, Node next1, Node prev1)
		{
			data = data1;
			next = next1;
			prev = prev1;
		}
		//Returns a String representation
		public String toString()
		{
			return String.valueOf(data);
		}
	}
	//private elements
	private Node cursor;
	private Node front;
	private Node back;
	private int length;
	private int index;
	//List constructor. Creates a new empty list.
	List()
	{
		cursor = null;
		front = null;
		back = null;
		length = 0;
		index = -1;
	}
	/*****ACCESS FUNCTIONS START HERE*****/
	// Returns the number of elements in this List.
	int length()
	{
		return length;
	}
	// If cursor is defined, returns the index of the cursor element,
	// otherwise returns -1.
	int index()
	{
		if(cursor == null)
		{
			return -1;
		}
		return index;
	}
	// Returns front element. Pre: length()>0
	int front()
	{
		if(length < 1)
		{
			throw new RuntimeException("Invalid, List Class Error: cannot call front() on empty list");
		}
		//otherwise return the front element
		return front.data;
	}
	// Returns back element. Pre: length()>0
	int back()
	{
		if(length < 1)
		{
			throw new RuntimeException("Invalid, List Class Error: cannot call back() on empty list");
		}
		//otherwise return the back element
		return back.data;
	}
	// Returns cursor element. Pre: length()>0, index()>=0
	int get()
	{
		if(length < 1)
		{
			throw new RuntimeException("Invalid, List Class Error: cannot call get() on empty list");
		}
		if(index() < 0)
		{
			throw new RuntimeException("Invalid, List Class Error: cannot call get() with undefined index");
		}
		//otherwise return the cursor element
		return cursor.data;
	}
	// Returns true if this List and L are the same integer
	// sequence. The cursor is ignored in both lists.
	boolean equals(List L)
	{
		if(L.length() != length)
		{
			return false;
		}
		Node temp = front;
		Node tmpfront = L.front;
		boolean btrue = true;
		
		if(length == L.length)
		{
			while (btrue && temp != null)
			{
				btrue = (temp.data == tmpfront.data);
				temp = temp.next;
				tmpfront = tmpfront.next;
			}
			return btrue;
		}
		else
		{
			return false;
		}
	}
	/*****ACCESS FUNCTIONS END HERE*****/
	
	/*****MANIPULATION PROCEDURES START HERE*****/
	// Resets this List to its original empty state.
	void clear()
	{
		cursor = null;
		front = null;
		back = null;
		length = 0;
		index = -1;
	}
	// If List is non-empty, places the cursor under the front element,
	// otherwise does nothing
	void moveFront()
	{
		if(length > 0)
		{
			//placing cursor under front element
			cursor = front;
			index = 0;
		}
	}
	// If List is non-empty, places the cursor under the back element,
	// otherwise does nothing.
	void moveBack()
	{
		if(length > 0)
		{
			//placing cursor under back element
			cursor = back;
			index = length - 1;
		}
	}
   // If cursor is defined and not at front, moves cursor one step toward
   // front of this List, if cursor is defined and at front, cursor becomes
   // undefined, if cursor is undefined does nothing.
	void movePrev()
	{
		//cursor defined and not at front
		if(cursor != null && index != 0)
		{
			cursor = cursor.prev;
			index--;
		}
		//cursor defined and at front
		else if(cursor != null && index == 0)
		{
			cursor = null;
			index = -1;
		}
	}
	// If cursor is defined and not at back, moves cursor one step toward
	// back of this List, if cursor is defined and at back, cursor becomes
   // undefined, if cursor is undefined does nothing.
	void moveNext()
	{
		//cursor defined and not at back
		if(cursor != null && index != length -1)
		{
			cursor = cursor.next;
			index++;
		}
		//cursor defined and at back
		else if(cursor != null && index == length - 1)
		{
			cursor = null;
			index = -1;
		}
	}
	// Insert new element into this List. If List is non-empty,
	// insertion takes place before front element.
	void prepend(int data)
	{
		//create new node
		Node newnode = new Node(data, front, null);
		if(front == null)
		{
			back = newnode;
		}
		else
		{
			front.prev = newnode;
		}
		front = newnode;
		length++;
	}
	// Insert new element into this List. If List is non-empty,
	// insertion takes place after back element.
	void append(int data)
	{
		//create new node
		Node newnode = new Node(data, null, back);
		if (front == null)
		{
			front = newnode;
		}
		else
		{
			back.next = newnode;
		}
		back = newnode;
		length++;
	}
	// Insert new element before cursor.
	// Pre: length()>0, index()>=0
	void insertBefore(int data)
	{
		if(length < 1)
		{
			throw new RuntimeException("Invalid, List Class Error: cannot call insertBefore() on empty list");
		}
		if(index() < 0)
		{
			throw new RuntimeException("Invalid, List Class Error: cannot call insertBefore() with undefined index");
		}
		//create new node
		Node newnode = new Node(data,cursor, cursor.prev);
		if(cursor.prev != null)
		{
			cursor.prev.next = newnode;
		}
		else
		{
			front = newnode;
		}
		cursor.prev = newnode;
		length++;
	}
	// Inserts new element after cursor.
	// Pre: length()>0, index()>=0
	void insertAfter(int data)
	{
		if(length < 1)
		{
			throw new RuntimeException("Invalid, List Class Error: cannot call insertAfter() on empty list");
		}
		if(index() < 0)
		{
			throw new RuntimeException("Invalid, List Class Error: cannot call insertAfter() with undefined index");
		}
		//create new node
		Node newnode = new Node(data, cursor.next, cursor);
		if(cursor.next != null)
		{
			cursor.next.prev = newnode;
		}
		else
		{
			back = newnode;
		}
		cursor.next = newnode;
		length++;
	}
	// Deletes the front element. Pre: length()>0
	void deleteFront()
	{
		if(length < 1)
		{
			throw new RuntimeException("Invalid, List Class Error: cannot call deleteFront() on empty list");
		}
		if(cursor == front)
		{
			cursor = null;
			index = -1;
		}
		front = front.next;
		front.prev = null;
		length--;
	}
	// Deletes the back element. Pre: length()>0
	void deleteBack()
	{
		if(length < 1)
		{
			throw new RuntimeException("Invalid, List Class Error: cannot call deleteBack() on empty list");
		}
		if(cursor == back)
		{
			cursor = null;
			index = -1;
		}
		back = back.prev;
		back.next = null;
		length--;
	}
	// Deletes cursor element, making cursor undefined.
	// Pre: length()>0, index()>=0
	void delete()
	{
		if(length < 1)
		{
			throw new RuntimeException("Invalid, List Class Error: cannot call delete() on empty list");
		}
		if(index() < 0)
		{
			throw new RuntimeException("Invalid, List Class Error: cannot call delete() with undefined index");
		}
		if(cursor == front)
		{
			deleteFront();
		}
		else if(cursor == back)
		{
			deleteBack();
		}
		else
		{
			cursor.prev.next = cursor.next;
			cursor.next.prev = cursor.prev;
			cursor = null;
			index = -1;
			length--;
		}
	}
	// Overrides Object's toString method. Returns a String
	// representation of this List consisting of a space
    // separated sequence of integers, with front on left.
	public String toString()
	{
		Node tmpfront = front;
		String output = new String();
		while(tmpfront != null)
		{
			output = output + String.valueOf(tmpfront.data) + " ";
			tmpfront = tmpfront.next;
		}
		return output;
	}
	// Returns a new List representing the same integer sequence as this
	// List. The cursor in the new list is undefined, regardless of the
	// state of the cursor in this List. This List is unchanged.
	List copy()
	{
		List copy = new List();
		Node tmpfront = front;
		while(tmpfront != null)
		{
			copy.append(tmpfront.data);
			tmpfront = tmpfront.next;
		}
		return copy;
	}


}


