//Katerina Chinnappan
//CruzID: kachinna
//PA 1
import java.io.*;
import java.util.Scanner;
import static java.lang.System.*;


public class Lex {
	public static void main(String[] args) throws IOException
	{
	     Scanner in = null;
	     PrintWriter out = null;
	     String line = null;
	     String[] token = null;
	     String[] array = null;
	     int i, n, lines = 0;
	     int lineNum = 0;
	     
	     if(args.length < 2){
	         System.err.println("Usage: Lex infile outfile");
	         System.exit(1);
	      }
	     
	     in = new Scanner(new File(args[0]));
	     out = new PrintWriter(new FileWriter(args[1]));
	     
	     //Count the number of lines 
	     //n in the file named by args[0].
	      while(in.hasNextLine()) {
	         ++lines;
	         in.nextLine();
	      }

	      in.close();
	      in = null;
	      //Create a String array of length 
	      //n and read in the lines of the file 
	      //as Strings, placing them into the array
	      array = new String[lineNum];
	      //open file again
	      in = new Scanner(new File(args[0]));
	      List list = new List();
	      for(i = 0; i < lineNum;i++)
	      {
	    	  array[i] = line;
	      }
	      list.append(0);
	      //Insertion sort
	      for(i = 1; i < array.length; i++)
	      {
	    	  String temp = array[i];
	    	  int j = i - 1;
	    	  list.moveBack();
	    	  while(j >= 0 && temp.compareTo(array[list.get()]) <= 0)
	    	  {
	    		  j--;
	    		  list.movePrev();
	    	  }
	    	  if(list.index() >= 0)
	    	  {
	    		  list.insertAfter(i);
	    	  }
	    	  else
	    	  {
	    		  list.prepend(i);
	    	  }
	      }
	    	  list.moveFront();
	    	  
	    	  //print in correct orders
	    	  while(list.index() >= 0)
	    	  {
	    		  out.println(array[list.get()]);
	    		  list.moveNext();
	    	  }
	    	  in.close();
	    	  out.close();
	      
	}
}
