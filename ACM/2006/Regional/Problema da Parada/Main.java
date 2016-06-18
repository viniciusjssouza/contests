/******************************************************************
* Problema da Parada - Maratona - Regional 2006
*
* Autor: Vinicius J. S. Souza
* Data: 12/03/2010
* Tecnicas: backtracking, simulacao
* Dificuldade(1-10): 7
*******************************************************************/

import java.io.*;
import java.util.*;
import static java.lang.System.*;

public class Main {
	static int N, L;
    static String[] program = new String[110];
    static HashSet<Integer> used = new HashSet<Integer>();
    static HashMap<Integer, Integer> result = new HashMap<Integer, Integer>();

    public static void main(String... arg) throws Exception{
        BufferedReader input = new BufferedReader(new InputStreamReader(new FileInputStream("parada.in")));
		long s = System.currentTimeMillis();
        while (true) {
            String line = input.readLine();
            String[] tok = line.split(" ");
            L = Integer.parseInt(tok[0]);
            N = Integer.parseInt(tok[1]);
            if (L == 0 && N == 0)
                break;
            used.clear();
            result.clear();
            for (int i = 0; i < L; i++) {
                program[i] = input.readLine();
            }
            int result = process(N);
            System.out.println(result < 0 ? "*" : result);
        }
		out.println(System.currentTimeMillis()-s);
    }

    static int process(int arg) {
        //out.println(arg);
        used.add(arg);
        int[] regs = new int[10];
        for (int i = 1; i < regs.length; i++)
            regs[i] = 0;
        regs[0] = arg;
        for (int pc = 0; pc < L; ) {
            /*
            out.println("--------------\nRegs:");
            for (int i : regs)
                out.print(i + " ");
            out.println("Command: " + program[pc]);
            */
            
            String[] cmd = program[pc].split("[ ,]");
            if (cmd[0].equals("CALL")) {
                int op2 = getOp(cmd[1], regs);
                if (used.contains(op2))
                    return -1;
                Integer r = result.get(op2);
                if (r != null)
                    regs[9]= r;
                else
                    regs[9] = process(op2);
                if (regs[9] < 0)
                    return -1;
                pc++;
            }else if (cmd[0].equals("RET")) {
                used.remove(arg);
                int ret = getOp(cmd[1], regs);
                result.put(arg,ret);
                return ret;
            }else {
                pc = execute(cmd, regs, pc);
                if (pc < 0)
                    return -1;
            }
        }
        used.remove(arg);
        result.put(arg, regs[9]);
        return regs[9];
    }

    static int getOp(String cmd, int[] regs) {
        int op;
        if (Character.isDigit(cmd.charAt(0))) {
            op = Integer.parseInt(cmd);
        } else{
            op = regs[Integer.parseInt(cmd.substring(1))];
        }
        return op;
    }

    static int execute(String[] cmd, int[] regs, int pc) {

        /*	out.println("------- Commands --------");
		for (String s : cmd)
			out.println(s);
*/
        if (cmd[0].equals("MOV")) {
            int r = Integer.parseInt(cmd[1].substring(1));
            regs[r] = getOp(cmd[2], regs);
            return pc+1;
        } else if (cmd[0].equals("ADD")) {
            int r = Integer.parseInt(cmd[1].substring(1));
            regs[r] = (regs[r]+getOp(cmd[2], regs)) % 1000;
            return pc+1;
        } else if (cmd[0].equals("SUB")) {
            int r = Integer.parseInt(cmd[1].substring(1));
            regs[r] = regs[r]-getOp(cmd[2], regs);
            if (regs[r] < 0)
                regs[r] += 1000;
            return pc+1;
        } else if (cmd[0].equals("MUL")) {
            int r = Integer.parseInt(cmd[1].substring(1));
            regs[r] = (regs[r]*getOp(cmd[2], regs)) % 1000;
            return pc+1;
        } else if (cmd[0].equals("DIV")) {
            int r = Integer.parseInt(cmd[1].substring(1));
            int op2 = getOp(cmd[2], regs);
            regs[r] = op2 == 0 ? 0 : (regs[r]/getOp(cmd[2], regs));
            return pc+1;
        } else if (cmd[0].equals("MOD")) {
            int r = Integer.parseInt(cmd[1].substring(1));
            int op2 = getOp(cmd[2], regs);
            regs[r] = op2 == 0 ? 0 : (regs[r]%getOp(cmd[2], regs));
            return pc+1;
        } else if (cmd[0].equals("IFEQ")) {
            int op1 = getOp(cmd[1], regs);
            int op2 = getOp(cmd[2], regs);
            if (op1 == op2)
                return pc+1;
            else {
                while (!program[pc++].equals("ENDIF") && pc < L);
                return pc;
            }
        }else if (cmd[0].equals("IFNEQ")) {
            int op1 = getOp(cmd[1], regs);
            int op2 = getOp(cmd[2], regs);
            if (op1 != op2)
                return pc+1;
            else {
                while (!program[pc++].equals("ENDIF") && pc < L);
                return pc;
            }
        }else if (cmd[0].equals("IFG")) {
            int op1 = getOp(cmd[1], regs);
            int op2 = getOp(cmd[2], regs);
            if (op1 > op2)
                return pc+1;
            else {
                while (!program[pc++].equals("ENDIF") && pc < L);
                return pc;
            }
        }else if (cmd[0].equals("IFL")) {
            int op1 = getOp(cmd[1], regs);
            int op2 = getOp(cmd[2], regs);
            if (op1 < op2)
                return pc+1;
            else {
                while (!program[pc++].equals("ENDIF") && pc < L);
                return pc;
            }
        }else if (cmd[0].equals("IFGE")) {
            int op1 = getOp(cmd[1], regs);
            int op2 = getOp(cmd[2], regs);
            if (op1 >= op2)
                return pc+1;
            else {
                while (!program[pc++].equals("ENDIF") && pc < L);
                return pc;
            }
        }else if (cmd[0].equals("IFLE")) {
            int op1 = getOp(cmd[1], regs);
            int op2 = getOp(cmd[2], regs);
            if (op1 <= op2)
                return pc+1;
            else {
                while (!program[pc++].equals("ENDIF") && pc < L);
                return pc;
            }
        } else return pc+1;
    }
}
