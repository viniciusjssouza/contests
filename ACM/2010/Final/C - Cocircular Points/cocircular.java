
import java.util.*;
import java.io.*;

public class cocircular {

    static int N;
    static Point[] pontos = new Point[110];

    public static void main(String args[]) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        while (true) {
            String[] line = in.readLine().split("\\s");
            N = Integer.parseInt(line[0]);
            if (N == 0) {
                break;
            }
            for (int i = 0; i < N; i++) {
                line = in.readLine().split("\\s");
                int x = Integer.parseInt(line[0]);
                int y = Integer.parseInt(line[1]);
                pontos[i] = new Point(x, y);
            }
            if (N < 3) {
                System.out.printf("%d\n", N);
                continue;
            }
			Map<Circle, Set<Integer> > counter = new HashMap<Circle, Set<Integer>>();
            int maxc = 0;
            for (int i = 0; i < N; i++) {
                for (int j = i + 1; j < N; j++) {
                    for (int k = j + 1; k < N; k++) {    
						Point A = pontos[j].sub(pontos[i]), B = pontos[j].sub(pontos[k]);
						if (cmp(Math.abs(A.dot(B)), Math.abs(A.norma() * B.norma())) == 0) {
                           continue;
                        }
                        Circle c = Circle.build(pontos[i], pontos[j], pontos[k]);
						Set<Integer> ss = null;
                        if ((ss = counter.get(c)) == null) {
							ss = new HashSet<Integer>();
							counter.put(c, ss);
						}
						//ss.add(i);
						//ss.add(j);
						//ss.add(k);
						//if (ss.size() > maxc)
						//	maxc = ss.size();
                    }
                }
            }
            System.out.println(maxc < 2 ? 2 : maxc);
        }
    }

    static int cmp(double x, double y) {
       return (x <= y + EPS) ? (x + EPS < y) ? -1 : 0 : 1;
    }
    static final double EPS = 1e-6;

    static class Point {

        double x, y;

        public Point(double x, double y) {
            this.x = x;
            this.y = y;
        }

        public Point sub(Point p) {
            return new Point(x - p.x, y - p.y);
        }

        public Point add(Point p) {
            return new Point(x + p.x, y + p.y);
        }

        public Point mult(double d) {
            return new Point(x * d, y * d);
        }

        public Point div(double d) {
            return new Point(x / d, y / d);
        }

        public double dot(Point p) {
            return (x * p.x + y * p.y);
        }

        public double cross(Point p) {
            return (x * p.y - y * p.x);
        }

        public double norma() {
            return Math.sqrt(x*x+y*y);
        }

        public double dist(Point p) {
            return (this.sub(p).norma());
        }

        public String toString() {
            return String.format("(%.4f %.4f)", x, y);
        }

        @Override
        public boolean equals(Object obj) {
            if (obj == null) {
                return false;
            }
            final Point other = (Point) obj;
            if (cmp(this.x, other.x) == 0 && cmp(this.y, other.y) == 0) {
                return true;
            }
            return false;
        }

        @Override
        public int hashCode() {
            int hash = 5;
            hash = 29 * hash + ((((int) x) ^ ((int) x)) >>> 3);
            hash = 29 * hash + ((((int) x) ^ ((int) x)) >>> 3);
            return hash;
        }
    }

    static class Circle implements Comparable<Circle>{
        Point center;
        double radius;

        public Circle(Point c, double r) {
            center = c;
            radius = r;
        }

		public int compareTo(Circle other) {
			return -1;
		} 

        static Circle build(Point p, Point q, Point r) {
            Point a = p.sub(r), b = q.sub(r), c = new Point(a.dot(p.add(r)) / 2, b.dot(q.add(r)) / 2);
            Point center = new Point(c.cross(new Point(a.y, b.y)), new Point(a.x, b.x).cross(c)).div(a.cross(b));
            return new Circle(center, center.dist(p));
        }

        @Override
        public boolean equals(Object obj) {
            if (obj == null) {
                return false;
            }
            final Circle other = (Circle) obj;
            if (cmp(this.radius, other.radius) == 0 && this.center.equals(other.center)) {
                return true;
            }
            return false;
        }

        @Override
        public int hashCode() {
            return (int) this.radius;
        }
    }
}
