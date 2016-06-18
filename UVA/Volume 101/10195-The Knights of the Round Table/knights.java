/**************************************************************************
* UVa 10195 - The Knights of the Round Table
*
* Autor: Vinicius J. S. Souza
* Data: 03/02/2010
* Tecnicas: geometria computacional
* Dificuldade (1-10): 4
************************************************************************/
import java.io.*;
import java.util.*;
import static java.lang.System.*;
import static java.lang.Math.*;

public class knights {
	static double a,b,c;		
	
	public static void main(String... args) throws Exception{
		BufferedReader input = new BufferedReader(new InputStreamReader(in));
		while (true) {
			String line = input.readLine();
			if (line == null || line.length() == 0)
				break;
			StringTokenizer t = new StringTokenizer(line);
			a = Double.parseDouble(t.nextToken());
			b = Double.parseDouble(t.nextToken());
			c = Double.parseDouble(t.nextToken());		
			if (a == 0.0 || b== 0.0 || c == 0.0)
				out.println("The radius of the round table is: 0.000\n");
			else out.printf("The radius of the round table is: %.3f\n", incentro());
		}
	}	

	// retorna o raio da circunferencia cujo centro e o incentro do triangulo a,b,c
	static double incentro() {
		double a2 = pow(a, 2.0), b2 = pow(b, 2.0), c2 = pow(c, 2.0);
		double x1 = (a2 + c2 - b2) / (2.0*c);
		double y1 = sqrt(a2 - pow(x1,2.0));
		double alpha = acos( (a2 + c2 - b2) / (2.0*a*c));
		double beta  = acos( (b2 + c2 - a2) / (2.0*b*c)); 
		double mr = tan((alpha/2.0));
		double ms = tan(PI-(beta/2.0));
		double y = (-ms*c) / (1 - (ms / mr));
		return y;
	}
}
