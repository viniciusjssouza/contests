using System;
using System.Collections.Generic;

public class Cartas
{
    static void Main(string[] args)
    {
        while (true)
        {
            string[] line = Console.ReadLine().Split(' ');
            int sz1 = int.Parse(line[0]);
            int sz2 = int.Parse(line[1]);
            if (sz1 == 0 && sz2 == 0)
                break;
            line = Console.ReadLine().Split(' ');
            Dictionary<int, int> d1 = new Dictionary<int, int>();
            Dictionary<int, int> d2 = new Dictionary<int, int>();
            foreach (string str in line) {
                int v = int.Parse(str);
                if (!d1.ContainsKey(v))
                    d1.Add(v,0);
                d1[v]++;
            }
            line = Console.ReadLine().Split(' ');
            foreach (string str in line)
            {
                int v = int.Parse(str);
                if (!d2.ContainsKey(v))
                    d2.Add(v,0);
                d2[v]++;
            }
            int cnt1 = 0, cnt2 = 0;
            foreach (KeyValuePair<int, int> pair in d1)
            {
                if (!d2.ContainsKey(pair.Key))
                    cnt1++;                   
            }
            foreach (KeyValuePair<int, int> pair in d2)
            {
                if (!d1.ContainsKey(pair.Key))
                    cnt2++;
            }
            Console.WriteLine("{0}", Math.Min(cnt1, cnt2));    
        }
    }
}
