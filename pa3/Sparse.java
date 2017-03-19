//Katerina Chinnappan
//kachinna
//pa3
//Sparse.java

import java.util.Scanner;
import java.io.*;

public class Sparse
{
	public static void main(String[] args) throws IOException, FileNotFoundException
	{		
		//check that the correct # of arguments are entered
		if(args.length != 2){
			System.err.println("USAGE: Sparse inputfile wfile");
			System.exit(1);
		}
		
		Scanner input = new Scanner(new File(args[0]));
		PrintWriter w = null;
		try{
			w = new PrintWriter (new FileWriter(args[1]));
		}
		catch (FileNotFoundException exception){
			System.err.println("invalid: cannot create file");
			System.exit(1);
		}
		catch (IOException exception){
			System.err.println("invalid: cannot create file");
			System.exit(1);
		}
		
		
		int nmatrix = Integer.parseInt(input.next())+1;
		int amatrix = Integer.parseInt(input.next());
		int bmatrix = Integer.parseInt(input.next());
		
		Matrix A = new Matrix(nmatrix);
		Matrix B = new Matrix(nmatrix);
		
		
		for(int i=0; i<amatrix; i++)
		{
			int a = Integer.parseInt(input.next());
			int b = Integer.parseInt(input.next());
			double c = Double.parseDouble(input.next());
			
			A.changeEntry(a,b,c);
		}
		for(int i=0; i<bmatrix; i++)
		{
			int x = Integer.parseInt(input.next());
			int y = Integer.parseInt(input.next());
			double z = Double.parseDouble(input.next());
			
			B.changeEntry(x,y,z);
		}
		
		w.println("A has "+A.getNNZ()+" non-zero entries:");
		w.println(A);
		w.println("B has "+B.getNNZ()+" non-zero entries:");
		w.println(B);
		
		w.println("(1.5)*A =");
		w.println(A.scalarMult(1.5));
		
		w.println("A+B =");
		w.println(A.add(B));
		
		w.println("A+A =");
		w.println(A.add(A));
		
		w.println("B-A =");
		w.println(B.sub(A));
		
		w.println("A-A =");
		w.println(A.sub(A));
		
		w.println("Transpose(A) =");
		w.println(A.transpose());
		
		w.println("A*B =");
		w.println(A.mult(B));
		
		w.println("B*B =");//B^2
		w.println(B.mult(B));
		
		input.close();
		w.close();
		
}
}
