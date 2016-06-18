import java.util.*;
import java.io.*;

public class quotes {
	static final String LEFT = "``";
	static final String RIGHT = "''";	
	static final char QUOTES = '"';

	public static void main(String args[]) throws Exception {
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		boolean open = true;
		while (in.ready()) {
			String line = in.readLine();
			StringBuilder builder = new StringBuilder("");
			for (int i = 0; i < line.length(); i++) {
				char c = line.charAt(i);
				if (c == QUOTES) {
					builder.append((open ? LEFT : RIGHT));
					open = !open;
				} else {
					builder.append(c);
				}
			}
			System.out.println(builder.toString());
		}
	}
}
