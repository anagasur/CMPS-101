//Katerina Chinnappan
//kachinna
//List.java
//pa3
public class List
{
	private class Node
	{
		Object element;
		Node next;
		Node prev;
		
		//second constructor with parameters (when inserting a new node in the list)
		Node(Object element1)
		{
			element = element1;
			next = null;
			prev = null;
		}
		
		public String toString()
		{
			return String.valueOf(element);
		}
	}
	
	//List variables
	 private Node cursor;
	 private Node front;
	 private Node back;
	 private int index;
	 int length;
	
	//default constructor, creates a new empty list
	List()
	{
		cursor = null;
		front = null;
		back = null;
		length = 0;
		index = -1;
	}

	 //*** ACCESS FUNCTIONS***//
	 
	 //getSize method, returns the size
	int length()
	{
		return length;
	}
	
	// If cursor is defined, returns the index of the cursor element,
	int index()
	{
		return index;
	}
	
	// Returns front element. Pre: length()>0
	Object front()
	{
		if(length() == 0)
		{
			throw new RuntimeException("List Error: front() called on empty Queue");
		}
		
		return front.element;
	}
	
	// Returns back element. Pre: length()>0
	Object back()
	{
		if(length() == 0)
		{
			throw new RuntimeException("List Error: back() called on empty Queue");
		}
		
		return back.element;
	}
	
	// Returns cursor element. Pre: length()>0, index()>=0
	Object get()
	{
		if(index < 0 || index >= length)
		{
			throw new RuntimeException("Position of cursor not defined.");
		}
		else
		{
			return cursor.element;
		}
	}
	
	// Returns true if this List and L are the same integer
	// sequence. The cursor is ignored in both lists.
	public boolean equals(Object L)
	{
		if(L == null)
		{
			return false;
		}

		boolean flag = true;
		Node node = front;
		Node node1 = ((List)L).front;
		
		if(length == ((List)L).length)
		{
			while(flag && node != null)
			{
				flag = (node.element == node1.element);
				node = node.next;
				node1 = node1.next;

			}
			return flag;
		}
		else
		{
			return false;
		}
	}
	
	 //*** MANIPULATION PROCEDURES***//
	
	 // Resets this List to its original empty state.
	void clear()
	{
		if(length() > 0)
		{
			front = null;
			back = null;
			cursor = null;
			length = 0;
			index = -1;
			
		}
	}
	void moveFront()
	{
		if(length > 0)
		{
			cursor = front;
			index = 0;
		}
	
	}
	void moveBack()
	{
		if(length > 0)
		{
			cursor = back;
			index = length - 1;
		}
	}
	
	//moves to specified location
	/*void movetoLoc(int i)
	{
		if(i < length)
		{
			cursor = front;
			int moving = i;
			index = 0;
			
			while(moving > 0)
			{
				cursor = cursor.next;
				index++;
				moving--;
			}
		}
	}*/
	
	  // If cursor is defined and not at front, moves cursor one step toward
	 // front of this List, if cursor is defined and at front, cursor becomes
	// undefined, if cursor is undefined does nothing
	void movePrev()
	{
		if(index ==0)
		{
			cursor = null;
			index--;
		}
		else
		{
			if(index != -1)
			{
				cursor = cursor.prev;
				index--;
			}
		}
	}
	
	// If cursor is defined and not at back, moves cursor one step toward
	// back of this List, if cursor is defined and at back, cursor becomes
	// undefined, if cursor is undefined does nothing.
	void moveNext()
	{
		if(index == length-1)
		{
			cursor = null;
			index = -1;
		}
		else
		{
			if(index != -1)
			{
				cursor = cursor.next;
				index++;
			}
		}
	}
	
	// Insert new element into this List. If List is non-empty,
	// insertion takes place before front element.
	void prepend(Object element)
	{
		Node node = new Node(element);
		
		if(this.length() == 0)
		{
			front = node;
			back = node;
		}
		else
		{
			front.prev = node;
			node.next = front;
			front = node;
			
			if(index != -1)
			{
				index++;
			}
		}
		length++;
	}
	
	// Insert new element into this List. If List is non-empty,
	// insertion takes place after back element.
	void append(Object element)
	{
		Node node = new Node(element);
		
		if(length() == 0)
		{
			front = node;
			back = node;
		}
		else
		{
			node.prev = back;
			back.next = node;
			back = node;
		}
		length++;
	}
	
	// Insert new element before cursor.
	// Pre: length()>0, index()>=0
	void insertBefore(Object element)
	{
		if(index == -1)
		{
			throw new RuntimeException("List Error: insertBefore() - undefined cursor pos");
		}
		
		//cursor > front equiv.
		if(index > 0)
		{
			Node node = new Node(element);
			node.next = cursor;
			node.prev = cursor.prev;
			cursor.prev.next = node;
			cursor.prev = node;

			length++;
			index++;
		}
		else
		{
			Node node = new Node(element);
			node.next = cursor;
			node.prev = null;
			cursor.prev = node;
			front = node;
			
			length++;
			index++;
		}
			
	}

	 
	// Inserts new element after cursor.
	// Pre: length()>0, index()>=0
	void insertAfter(Object element)
	{
		if(index == -1)
		{
			throw new RuntimeException("List Error: insertAfter() - undefined cursor pos");
		}
		
		if(index >= 0)
		{
			//same as cursor < back
			if(index < length-1)
			{
				Node node = new Node(element);
				node.next = cursor.next;
				node.prev = cursor;
				cursor.next.prev = node;
				cursor.next = node;
				
				index++;
			}
			else
			{
				Node node = new Node(element);
				node.next = null;
				node.prev = cursor;
				cursor.next = node;
				back = node;
				
				index++;
			}
			length++;
		}		
	}
	
	// Deletes the front element. Pre: length()>0
	void deleteFront()
	{
		//if length is less than 1, then throw exception that can't delete empty list
		 if(length() > 1)
		 {
			 throw new RuntimeException("Error:List:cannot delete empty List");
		 }
				
		if(length>1)
		{
			front = front.next;
			front.prev = null;
		}
		else
		{
			front = null;
			back = null;
		}
		
		if(index > 0)
		{
			index--;
		} 
		else if(cursor == front)
		{
			cursor = null;
			index = -1;
		}
		
		length--;
	}
	
	// Deletes the back element. Pre: length()>0
	void deleteBack()
	{
		//if length is less than 1, then throw exception that can't delete empty list
		if(length() >1)
		{
			 throw new RuntimeException("Error:List:cannot delete empty List");
		}
		if(length>1) 
		{
			back = back.prev;
			back.next = null;
		}
		else
		{
			front = null;
			back = null;
		}
		if(cursor == back)
		{
			index = -1;
			cursor = null;
		}
		length--;
	}
	
	// Deletes cursor element, making cursor undefined.
	// Pre: length()>0, index()>=0
	void delete()
	{
		 if(index < 0){
			 throw new RuntimeException("Error:List:cannot delete empty List with undefined index");
		 }
		 //if length is less than 1, then throw exception that can't delete empty list
		 if(length() < 1){
			 throw new RuntimeException("Error:List:cannot delete empty List");
		 }
		
		if(index==0){
			deleteFront();
		}else{
			if(index==length-1){
				deleteBack();
			}else{
				cursor.prev.next = cursor.next;
				cursor.next.prev = cursor.prev;
				cursor = null;
				index = -1;
				length--;
			}
		}
	}
	
	// Overrides Object's toString method. Returns a String
	// representation of this List consisting of a space
	// separated sequence of integers, with front on left.
	public String toString()
	{
		 Node node = front;
		 String output = new String();
		 while(node != null){
			 output = output + String.valueOf(node.element)+" ";
			 node = node.next;
		 }
		 return output;
	}
	 // Returns a new List representing the same integer sequence as this
	 // List. The cursor in the new list is undefined, regardless of the
	 // state of the cursor in this List. This List is unchanged.
	/* public List copy(){
		 List list = new List();
		 Node node = front;
		 while(node != null){
			 list.append(get());
			 node = node.next;
		 }
		 return list;
	 }*/
	 
	 //*** MANIPULATION PROCEDURES FINISH***//	
	
}