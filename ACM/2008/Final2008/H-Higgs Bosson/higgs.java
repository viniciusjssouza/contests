/*********************************************************
 * Higgs Boson - Final Sul Americana - 2008
 *
 * Autor: Vinicius J. S. Souza
 * Data: 23/08/2009
 * Tecnicas: teoria dos numeros
 */

import java.util.*;
import java.io.*;

public class higgs
{
    static class Particula
    {
        public long a, b, c, d;

        public Particula(long a, long b, long c, long d)
        {
            this.a = a;
            this.b = b;
            this.c = c;
            this.d = d;
        }
    }

    static class Fracao
    {
        public long num, den;
        public Fracao(long num, long den)
        {
            this.den = den;
            this.num = num;
            if (num == 0 && den != 0)
                den = 1;
        }
        
        public double getValue()
        {
            return ( (double)num / (double)den);
        }

        public void reduz()
        {
            if (num == 0)
                den = 1;
            long gcd = mdc(num, den);
            num /= gcd;
            den /= gcd;
        }
    }

    public static void main(String args[]) throws IOException
    {
        BufferedReader input = new BufferedReader(new
                InputStreamReader(System.in));
        while (true)
        {
            String line = input.readLine();
            long a1, b1, c1, d1, a2, b2, c2, d2;
            StringTokenizer tokenizer = new StringTokenizer(line);
            a1 = Long.parseLong(tokenizer.nextToken());
            b1 = Long.parseLong(tokenizer.nextToken());
            c1 = Long.parseLong(tokenizer.nextToken());
            d1 = Long.parseLong(tokenizer.nextToken());
            a2 = Long.parseLong(tokenizer.nextToken());
            b2 = Long.parseLong(tokenizer.nextToken());
            c2 = Long.parseLong(tokenizer.nextToken());
            d2 = Long.parseLong(tokenizer.nextToken());
            if (a1 ==0 && b1 == 0 && c1 == 0 && d1 == 0 && a2 == 0 && b2 == 0 &&
                    c2 == 0 && d2 == 0)
                break;
            Particula p1 = new Particula(a1, b1, c1, d1);
            Particula p21 = new Particula(a2, b2, c2, d2);
            Particula p22 = new Particula(-a2, -b2, c2, d2+180);
            
            Fracao solucao = getPontoColisao(p1, p21);
            Fracao f2 = getPontoColisao(p1, p22);
            if (solucao == null || (f2 != null && f2.getValue() < solucao.getValue()))
                solucao = f2;

            if (solucao == null)
                System.out.println("0 0");
            else
            {
                //if (solucao.den > 1)
                    solucao.reduz();
                System.out.println(solucao.num+ " " + solucao.den);
            }

        }
    }

    public static Fracao getPontoColisao(Particula p1, Particula p2)
    {
        Fracao result = new Fracao((p2.b - p1.b), (p1.a - p2.a));
        // os raios sao iguais pra qualquer t
        if (result.num == 0 && result.den == 0)
        {
            Fracao fracao = new Fracao(((p2.d - p1.d) % 360), (p1.c - p2.c));
            if (fracao.den > 0 && fracao.num < 0)
                fracao.num += 360;
            else if (fracao.den < 0 && fracao.num > 0)
                fracao.num -= 360;
            if ( fracao.getValue() < 0)
                return null;
            else if (fracao.den == 0 && fracao.num != 0)
                return null;
            else if (fracao.num == 0 && fracao.den == 0)
                return new Fracao(0,1);
            else if (fracao.num == 0)
                return fracao;
            else
            {
                fracao.den = Math.abs(fracao.den);
                fracao.num = Math.abs(fracao.num);
                long gcd = mdc(mdc(fracao.num, fracao.den),
                        360);
                fracao.den /= gcd;
                fracao.num /= gcd;
                return fracao;
            }
        }
        // denominador = 0... nao eh solucao
        else if (result.num != 0 && result.den == 0)
            return null;
        else
        {
            double t = result.getValue();
            if (t < 0.0)
             return null;
            //teste origem
            else if (Double.compare( (p1.a*t+p1.b), 0.0) == 0)
            {
                result.num = Math.abs(result.num);
                result.den = Math.abs(result.den);
                return result;
            }
            else if (t < 0)
                return null;
            else
            {
                double teta1 = p1.c*t + p1.d;
                double teta2 = p2.c*t + p2.d;
                double div = Math.abs(teta1 - teta2) / 360.0;
                if (Double.compare(Math.ceil(div), Math.floor(div)) == 0)
                {
                    result.num= Math.abs(result.num);
                    result.den = Math.abs(result.den);
                }
                else
                    return null;
            }
        }
        return result;
    }

    public static long mdc(long p, long q)
    {
        long g;                         /* value of gcd(p,q) */
        if (q > p) return(mdc(q,p));
        if (q == 0)
          return(p);
        g = mdc(q, p%q);
        return(g);
    }

}

