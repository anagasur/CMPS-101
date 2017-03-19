//Katerina Chinnappan
//kachinna
//PA3
public class Matrix {
   private class Entry {
      int column;
      double data;
      
      //creates an Entry with column, int.
      Entry(int column1, double data1) {
         column = column1;
         data = data1;
      }
      
      //returns String representation of the data string.
      public String toString() {
         return "(" + column + ", " + data + ")";
      }
      
      // Returns true if two Entries column and data are equal.
      public boolean equals(Object x) {
         boolean equal = false;
         Entry entry;
         if(x instanceof Entry) {
            entry = (Entry) x;
            equal = (column == entry.column && data == entry.data);
         }
         return equal;
      }
   }

   List[] row;
   //Constructor
   // makes a new n x n zero Matrix.
   // pre: n >= 1
   Matrix(int n) {
      if(n < 1)
         throw new RuntimeException("Matrix Error: Matrix() called with negative number of columns");
      row = new List[n + 1];
      for(int i = 1; i < (n + 1); i++) {
         row[i] = new List();
      }
   }

   //returns n, the number of rows and columns of this Matrix.
   int getSize() {
      return row.length - 1;
   }
   
   //returns the number of non-zero entries in this Matrix.
   int getNNZ() {
      int NNZ = 0;
      for(int i = 1; i <= getSize(); i++) {
         NNZ += row[i].length();
      }
      return NNZ;
   }
   
   //overrides Object's equals() method.
   public boolean equals(Object x) {
      Matrix matrix;
      if(x instanceof Matrix) {
         matrix = (Matrix) x;
         if(getSize() != matrix.getSize())
            return false;
         for(int i = 1; i <= getSize(); i++) {
            if(!(row[i].equals(matrix.row[i])))
               return false;
         }
      }
      return true;
   }
   
   /****MANIPULATON PROCEDURES****/
   //sets this Matrix to the zero state.
   void makeZero() {
      for(int i = 1; i <= getSize(); i++) {
         row[i] = new List();
      }
   }

   //returns a new Matrix having the same entries as this Matrix.
   Matrix copy() {
      Matrix matrix = new Matrix(getSize());
      for(int i = 1; i <= getSize(); i++) {
         row[i].moveFront();
         while(row[i].index() >= 0) {
            Entry temp = (Entry) row[i].get();
            matrix.changeEntry(i, temp.column, temp.data);
            row[i].moveNext();
         }
      }
      return matrix;
   }
   
   // changes the ith row, jth column of this Matrix to x.
   // pre: 1 <= i <= getSize(), 1 <= j <= getSize()
   void changeEntry(int i, int j, double x) {
      if(i < 1 || i > getSize() || j < 1 || j > getSize())
         throw new RuntimeException("changeEntry() called Matrix on wrong ith, jth position");
      
      boolean found = false;
      row[i].moveFront();
      while(row[i].index() >= 0) {
         Entry entry = (Entry) row[i].get();
         if(entry.column == j)
         {
        	 found = true;
         }
         else
         {
        	 found = false;
         }
         if(found) {
            if(x == 0.0) 
            {
               row[i].delete();
               return;
            } 
            else 
            { 
               entry.data = x; 
               return;
            }
         }
         row[i].moveNext();
      }

      if(!found && x != 0.0) 
      {
         row[i].moveFront();
         if(row[i].index() == -1) 
         {
            row[i].append(new Entry(j, x)); 
            return;
         } 
         else 
         {
            while(row[i].index() > -1 && ((Entry)row[i].get()).column < j) 
            {
               row[i].moveNext();
            }
            if(row[i].index() > -1)
            {
               row[i].insertBefore(new Entry(j, x)); 
               return;
            } 
            else 
            {
               row[i].append(new Entry(j, x)); 
               return;
            }
         }
      }
   }

   // returns a new Matrix that is the scalar product of this Matrix with x.
   Matrix scalarMult(double x) {
      Matrix matrix = copy();
      for(int i = 1; i <= matrix.getSize(); i++) {
         matrix.row[i].moveFront();
         while(matrix.row[i].index() >= 0) {
            Entry temp = (Entry) matrix.row[i].get();
            matrix.changeEntry(i, temp.column, (x * temp.data));
            matrix.row[i].moveNext();
         }
      }
      return matrix;
   }

   // returns a new Matrix that is the sum of this Matrix with M.
   // pre: getSize() == M.getSize()
   Matrix add(Matrix M) {
      if(getSize() != M.getSize())
         throw new RuntimeException("Matrix: add() called on Matrix");
      if(M == this)
         return copy().scalarMult(2);
      Matrix matrix = new Matrix(getSize());
      for(int i = 1; i <= getSize(); i++) {
          matrix.row[i] = addSub(row[i], M.row[i], true);
      }
      return matrix;
   }
   
   // returns a new Matrix that is the difference of this Matrix with M.
   // pre: getSize() == M.getSize()
   Matrix sub(Matrix M) {
      if(getSize() != M.getSize())
         throw new RuntimeException("Matrix: sub() called on Matrix");
      if(M == this) {
         return new Matrix(getSize());
      }
      Matrix matrix = new Matrix(getSize());
      for(int i = 1; i <= getSize(); i++) {
         matrix.row[i] = addSub(row[i], M.row[i], false);
      }
      return matrix;
   }
   
   //help to add and subtract
   private List addSub(List P, List Q, boolean go) {
      List list = new List();
      P.moveFront();
      Q.moveFront();
      double ret;
      if(go)
      {
      	ret = 1.0;
      }
      else
      {
      	ret = -1.0;
      }
      while(P.index() >= 0 || Q.index() >= 0) {
         if(P.index() >= 0 && Q.index() >= 0) {
            Entry a = (Entry) P.get();
            Entry b = (Entry) Q.get();
            if(a.column > b.column) {
            	list.append(new Entry(b.column, (ret) * b.data));
               Q.moveNext();
            } else if(a.column < b.column) {
            	list.append(new Entry(a.column, a.data));
               P.moveNext();
            } else if(a.column == b.column) {
               if((go && a.data + b.data != 0) || (!go && a.data - b.data != 0))
            	   if(go)
            	   {
            		   ret = a.data + b.data;
            	   }
            	   else
            	   {
            		   ret = a.data - b.data;
            	   }
               list.append(new Entry(a.column, (ret)));
               P.moveNext();
               Q.moveNext();
            }
         } else if(P.index() >= 0) {
            Entry a = (Entry) P.get();
            list.append(new Entry(a.column, a.data));
            P.moveNext();
         } else {
            Entry b = (Entry) Q.get();
            list.append(new Entry(b.column, (ret) * b.data));
            Q.moveNext();
         }
      }
      return list;
   }


   //returns a new Matrix that is the transpose of this Matrix.
   Matrix transpose() {
      Matrix matrix = new Matrix(getSize());
      for(int i = 1; i <= getSize(); i++) {
         row[i].moveFront();
         while(row[i].index() >= 0) {
            matrix.changeEntry(((Entry)row[i].get()).column, i, ((Entry)row[i].get()).data);
            row[i].moveNext();
         }
      }
      return matrix;
   }

   // returns a new Matrix that is the product of this Matrix with M.
   // pre: getSize() == M.getSize()
   Matrix mult(Matrix M) {
      if(getSize() != M.getSize())
         throw new RuntimeException("Matrix: mult() called on Matrix");
      Matrix matrix = new Matrix(getSize());
      Matrix A = M.transpose();
      for(int i = 1; i <= getSize(); i++) {
         if(row[i].length() == 0) continue;
         for(int j = 1; j <= getSize(); j++) {
            if(A.row[j].length() == 0) continue;
            matrix.changeEntry(i, j, dot(row[i], A.row[j]));
         }
      }
      return matrix;   
   }
   // computes the vector dot product of two matrix rows represented by Lists P and Q
   private static double dot(List P, List Q) {
      double product = 0.0;
      P.moveFront();
      Q.moveFront();
      while(P.index() >= 0 && Q.index() >= 0) 
      {
         Entry entry1 = (Entry) P.get();
         Entry entry2 = (Entry) Q.get();
         if(entry1.column > entry2.column) 
         {
            Q.moveNext();
         } 
         else if(entry1.column < entry2.column) 
         {
            P.moveNext();
         } 
         else 
         {
            product += (entry1.data * entry2.data);
            P.moveNext();
            Q.moveNext();
         }
      }
      return product;
   }


   //overrides Object's toString() method.
   public String toString() {
      String out = "";
      for(int i = 1; i <= getSize(); i++) {
         if(row[i].length() > 0)
            out += (i + ": " + row[i] + "\n"); 
      }
      return out;
   }
}
   


  