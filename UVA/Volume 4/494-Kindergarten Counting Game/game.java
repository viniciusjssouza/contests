import java.util.*;
import java.io.*;

public class game {
	public static void main(String args[]) throws Exception {
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		boolean open = true;
		while (in.ready()) {
			int count = 0;
			String line = in.readLine();
			if (Character.isLetter(line.charAt(0)))
				count++;
			for (int i = 1; i < line.length(); i++) {
				char c = line.charAt(i);
				if (Character.isLetter(c) && !Character.isLetter(line.charAt(i-1)))
					count++; 
			}
			System.out.println(count);
		}
	}
}
