import java.util.*;
import java.io.*;

public class corretor
{
    public static void main(String[] args) throws FileNotFoundException
    {
        for (String arg : args)
            System.out.println(arg);
        if (args.length != 2)
        {
            System.out.println("Numero invalido de argumentos");
            System.exit(0);
        }
        Scanner input1 = new Scanner(new File(args[0]));
        Scanner input2 = new Scanner(new File(args[1]));
        int i = 1;
        while (input1.hasNextLine() && input2.hasNextLine())
        {
           if (!input1.nextLine().equals(input2.nextLine()))
           {
               System.out.println("Erro encontrado na linha " + i);
               System.exit(0);
           }
           i++;
        }
        System.out.println("Arquivos iguais.");
    }
}
