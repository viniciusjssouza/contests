/****************************************************************
* UVA 450 - Little Black Book
*
* Autor: Vinicius J. S. Souza
* Data: 27/01/2010
* Tecnicas utilizadas: sorting
*************************************************************/
import java.util.*;
import java.io.*;

public class Main
{
	static int N;
	
	static class People
	{
		String department;
		String title;
		String fName;
		String lName;
		String street;
		String hPhone;
		String wPhone;
		String mailbox; 

		public boolean equals(Object o)
		{
			People p = (People) o;
			return (p.fName.equals(this.fName) && p.lName.equals(this.lName));
		}
	}
		
	public static void main(String... args) throws Exception
	{
		BufferedReader input = new BufferedReader(new InputStreamReader(System.in));		
		N = Integer.parseInt(input.readLine());
		Map<String, People> mapa = new HashMap<String, People>();
		List<String> names = new ArrayList<String>();
		for (int i = 0; i < N; i++)
		{
			String dep = input.readLine();
			while (true)
			{
				String line = input.readLine();
				if (line.length() == 0 && !line.equals(" "))
					break;
				StringTokenizer t = new StringTokenizer(line, ",");
				if (!t.hasMoreTokens())
					break;
				People p = new People();
				p.department = dep;
				p.title = t.nextToken();
				p.fName = t.nextToken();
				p.lName = t.nextToken();
				p.street = t.nextToken();
				p.hPhone = t.nextToken();
				p.wPhone = t.nextToken();
				p.mailbox = t.nextToken();
				mapa.put(p.lName, p);
				names.add(p.lName);
			}
		}
		Collections.sort(names);
		for (String lname : names)
		{
			System.out.println("----------------------------------------");
			People p = mapa.get(lname);
			System.out.printf("%s %s %s\n%s\nDepartment: %s\nHome Phone: %s\nWork Phone: " +
				"%s\nCampus Box: %s\n", p.title, p.fName, p.lName, p.street, p.department, 
				p.hPhone, p.wPhone, p.mailbox);			
		}
	}
}
