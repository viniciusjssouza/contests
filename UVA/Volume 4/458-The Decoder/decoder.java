import java.util.*;
import java.io.*;

public class decoder {
	static final int DIF = 'i' - 'p';
	
	public static void main(String args[]) throws Exception {
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		boolean open = true;
		while (in.ready()) {
			String line = in.readLine();
			StringBuilder builder = new StringBuilder("");
			for (int i = 0; i < line.length(); i++) {
				char c = line.charAt(i);
				if(Charac

				builder.append((char)(c + DIF));
			}
			System.out.println(builder.toString());
		}
	}
}
