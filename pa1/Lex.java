//Katerina Chinnappan
//kachinna
//PA1

import java.io.*;
import java.util.Scanner;
import static java.lang.System.*;

public class Lex {
   public static void main(String[] args) throws IOException {
      Scanner in = null;
      PrintWriter out = null;
      String[] array = null;
      int count = -1;
      int i,j;
      
      // Check for two arguments
      if(args.length != 2) {
         System.err.println("Usage: Lex input output");
         System.exit(1);
      }

      in = new Scanner(new File(args[0]));
		try{
			out = new PrintWriter (new FileWriter(args[1]));
		}
		catch (FileNotFoundException exception){
			System.err.println("Usage:Lex cannot create file");
			exit(1);
		}
		catch (IOException exception){
			System.err.println("Usage: Lex cannot create file");
			exit(1);
		}

    //Count the number of lines 
	//n in the file named by args[0].
      int lines = 0;
      while(in.hasNextLine()) {
         lines++;
         in.nextLine();
      }

      in.close();
      in = null;

      //Create a String array of length 
      //n and read in the lines of the file 
      //as Strings, placing them into the array
      List list = new List();
      array = new String[lines];
      //open again file
      in = new Scanner(new File(args[0]));
      

      // Put all lines of the file into the String array
      while(in.hasNext()) {
         array[++count] = in.nextLine();
      }
      
      list.append(0);
      // Insertion Sort 
      for(i = 1; i < array.length; i++) {
    	 j = i - 1;
         String temp = array[i];
     
         list.moveBack();
         while(j >= 0 && temp.compareTo(array[list.get()]) <= 0) {
            j--;
            list.movePrev();
         }
         
         if(list.index() >= 0)
            list.insertAfter(i);
         
         else
            list.prepend(i);
      }

      
      list.moveFront();
      
      while(list.index() >= 0) {
         out.println(array[list.get()]);
         list.moveNext();
      }
     
      in.close();
      out.close();
   }
}