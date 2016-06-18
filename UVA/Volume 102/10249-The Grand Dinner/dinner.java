/*************************************************************************
* UVA 10249 - The Grand Dinner - Programming Challenges
*
* Autor: Vinicius J. S. Souza
* Data: 12/07/2009
* Tecnicas utilizadas: algoritmo greedy, como descrito abaixo:
*		1 - Ordene os times por numero decrescente de membros;
*		2 - Distribua os membros pelas mesas
* Observacao: a implementacao em C++ da RunTimeError... A mesma implementacao
*			 em Java e acc
*************************************************************************/

import java.util.*;
import java.io.*;

public class dinner
{
    static int nTimes;
    static int nMesas;

    static class Time implements Comparable
    {
        public int id;
        public int nMembros;

        public int compareTo(Object o)
        {
            if (o instanceof Time)
            {
                Time another = (Time)o;
                if (this.nMembros >= another.nMembros)
                    return -1;
                return 1;
            }
            return 0;
        }
    }

    public static void main(String[] args) throws FileNotFoundException
    {
        Scanner in = new Scanner(new File("in.txt"));
        //Scanner in = new Scanner(System.in);
        while (true)
        {
            nTimes = in.nextInt();
            nMesas = in.nextInt();
            if (nTimes == 0 && nMesas == 0)
                break;
            List<Integer> mesas = new ArrayList<Integer>();
            List<Time> times = new ArrayList<Time>();
            for (int i = 0; i < nTimes; i++)
            {
                Time t = new Time();
                t.id = i;
                t.nMembros = in.nextInt();
                times.add(t);
            }
            for (int i = 0; i < nMesas; i++)
                mesas.add(in.nextInt());
            Collections.sort(times);

           // printVetores(times, mesas);

            List<List<Integer>> path = new ArrayList<List<Integer>>();
            for (int i = 0; i < nTimes; i++)
                path.add(new ArrayList<Integer>());
            if (distribuiTimes(times, mesas, path) == false)
                System.out.println("0");
            else
            {
                System.out.println('1');
                for (List<Integer> list : path)
                {
                    for (int k = 0; k < list.size(); k++)
                    {
                        if (k > 0)
                            System.out.print(' ');
                         System.out.print(list.get(k));
                    }
                    System.out.print('\n');
                }
            }
        }
    }

    public static void printVetores(List<Time> times, List<Integer> mesas)
    {
        for (Time time : times)
        {
            System.out.println("Time:" + time.id + "   nMembros:" + time.nMembros);
        }
        for (Integer i : mesas)
        {
            System.out.println("Mesa:" + i);
        }
    }

    public static boolean distribuiTimes(List<Time> times, List<Integer> mesas, List<List<Integer>> path)
    {
       for (Time time : times)
       {
            int k = 0;
            int m = 0;
            while (k < mesas.size() && m < time.nMembros)
            {
                if (mesas.get(k) > 0)
                {
                    mesas.set(k, mesas.get(k)-1);
                    m++;
                    path.get(time.id).add(k+1);
                }
                k++;
            }
            if (k >= mesas.size() && m < time.nMembros)
                return false;
       }
       return true;
    }
}
