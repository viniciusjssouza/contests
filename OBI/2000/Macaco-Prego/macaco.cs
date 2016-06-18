using System;

public class Macaco
{
    class point
    {
        public int x, y;
        public point(int x, int y)
        {
            this.x = x; 
            this.y = y;
        }
    }
    class rect
    {
        public point p1, p2;
        public rect(point p1, point p2)
        {
            this.p1 = p1; 
            this.p2 = p2;
        }

        public bool pertence(point p)
        {
            if (p.x >= this.p1.x && p.x <= this.p2.x && p.y >= this.p2.y && p.y <= this.p1.y)
                return true;
            return false;
        }

        public rect intersect(rect r2){
            point sup = new point(Math.Max(this.p1.x, r2.p1.x), Math.Min(this.p1.y, r2.p1.y));
            point inf = new point(Math.Min(this.p2.x, r2.p2.x), Math.Max(this.p2.y, r2.p2.y));
            if (this.pertence(sup) && this.pertence(inf) && r2.pertence(sup) &&
                r2.pertence(inf))
            {
                return new rect(sup, inf);
            }
            return null;
        }
    }
	static int N;
   
    static void Main(string[] args) {
        int tcase = 1;
        while (true)
        {
            N = int.Parse(Console.ReadLine());
            if (N == 0) 
                 break;
            string[] line = Console.ReadLine().Split(' ');
            rect result = new rect(new point(int.Parse(line[0]), int.Parse(line[1])),
                    new point(int.Parse(line[2]), int.Parse(line[3])));
            bool ok = true;
            for (int i = 1; i < N; i++)
            {
                line = Console.ReadLine().Split(' ');
                if (ok)
                {
                    rect aux = new rect(new point(int.Parse(line[0]), int.Parse(line[1])),
                    new point(int.Parse(line[2]), int.Parse(line[3])));
                    rect r = null;
                    if ((r = result.intersect(aux)) == null)
                        ok = false;
                    else result = r;
                }
            }
            if (ok)
                Console.Write("Teste {0}\n{1} {2} {3} {4}\n\n", tcase++, result.p1.x, result.p1.y,
                    result.p2.x, result.p2.y);
            else
                Console.Write("Teste {0}\nnenhum\n\n", tcase++);
        }
    }
}
