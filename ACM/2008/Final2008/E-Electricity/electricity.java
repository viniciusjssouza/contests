/***********************************************************
 * Eletricity - Final Sul-americana 2008
 *
 * Autor: Vinicius J. S. Souza
 * Data: 23/08/2009
 */

import java.io.*;
import java.util.*;

/**
 *
 * @author Vinicius
 */
public class electricity {

    static int consumo, dias;
    static final int DAY = 0, MONTH = 1, YEAR = 2, CONSUME = 3;

    public static void main(String[] args) throws FileNotFoundException, IOException {
        // TODO code application logic here
        BufferedReader input = new BufferedReader(new InputStreamReader(System.in));
        GregorianCalendar cal = (GregorianCalendar) Calendar.getInstance();
        final int[] daysInMonth = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        while (true)
        {
            int n = Integer.parseInt(input.readLine());
            if (n == 0) break;
            int[][] vet = new int[n][4];
            for (int i = 0; i < n; i++)
            {
                StringTokenizer tokenizer = new
                        StringTokenizer(input.readLine());
                for (int k = 0; k < 4; k++)
                    vet[i][k] = Integer.parseInt(tokenizer.nextToken());
            }
            consumo = 0;
            dias = 0;
            for (int i = 1; i < n; i++)
            {
                if (vet[i][YEAR] == vet[i-1][YEAR]+1)
                {
                   if (vet[i][MONTH] == 1 && vet[i-1][MONTH] == 12 &&
                           vet[i][DAY] == 1 && vet[i-1][DAY] == daysInMonth[12])
                        updateConsume(vet, i);
                }
                else if (vet[i][YEAR] == vet[i-1][YEAR])
                {
                    if (vet[i][MONTH] == vet[i-1][MONTH]+1 && vet[i][DAY] == 1)
                    {
                        if (vet[i-1][MONTH] == 2)
                        {
                            boolean leapYear = cal.isLeapYear(vet[i][YEAR]);
                            if (leapYear && vet[i-1][DAY] == 29)
                                updateConsume(vet, i);
                            else if (!leapYear && vet[i-1][DAY] == 28)
                                updateConsume(vet, i);
                        }
                        else if (vet[i-1][DAY] == daysInMonth[vet[i-1][MONTH]])
                            updateConsume(vet, i);                        
                    }
                    else if (vet[i][MONTH] == vet[i-1][MONTH])
                    {
                       if (vet[i][DAY] == vet[i-1][DAY]+1)
                           updateConsume(vet, i);
                    }
                }
            }
            System.out.println(dias + " " + consumo);
        }    
    }

    public static void updateConsume(int[][] vet, int i)
    {
        //System.out.println("updating...");
        consumo += (vet[i][CONSUME] - vet[i-1][CONSUME]);
        dias++;
    }
}
