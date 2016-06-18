/******************************************************************
* Problema da Parada - Maratona - Regional 2006
*
* Autor: Vinicius J. S. Souza
* Data: 12/03/2010
* Tecnicas: backtracking, simulacao
* Dificuldade(1-10): 7
*******************************************************************/
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<map>
#include<set>

using namespace std; 

int N, L, i, k;
char program[110][30];
map<int, bool> used;
map<int, int> result;

int getOp(char* cmd, int* regs) {
	if (isdigit(cmd[0]))
		return atoi(cmd);
	cmd++;
	return regs[atoi(cmd)];	
		
}

int execute(char* str, int* &regs, int pc) {
	char* cmd = strtok(str, " ");
	if (!strcmp(cmd, "MOV")) {
		char* str = strtok(NULL, ",");
		str++;
		int r = atoi(str);
		regs[r] = getOp(strtok(NULL, ","), regs);
		return pc+1;
	} else if (!strcmp(cmd, "ADD")) {
		char* str = strtok(NULL, ",");
		str++;
		int r = atoi(str);
		regs[r] = (regs[r] + getOp(strtok(NULL, ","), regs)) % 1000;
		return pc+1;
	} else if (!strcmp(cmd, "SUB")) {
		char* str = strtok(NULL, ",");
		str++;
		int r = atoi(str);
		regs[r] = (regs[r] - getOp(strtok(NULL, ","), regs));
		if (regs[r] < 0)
			regs[r] += 1000;
		return pc+1;
	} else if (!strcmp(cmd, "MUL")) {
		char* str = strtok(NULL, ",");
		str++;
		int r = atoi(str);
		regs[r] = (regs[r] * getOp(strtok(NULL, ","), regs)) % 1000;
		return pc+1;
	} else if (!strcmp(cmd, "DIV")) {
		char* str = strtok(NULL, ",");
		str++;
		int r = atoi(str);
		int op2 = getOp(strtok(NULL, ","), regs);
		regs[r] =  (op2 == 0) ? 0 : (regs[r] / op2);
		return pc+1;
	} else if (!strcmp(cmd, "MOD")) {
		char* str = strtok(NULL, ",");
		str++;
		int r = atoi(str);
		int op2 = getOp(strtok(NULL, ","), regs);
		regs[r] =  (op2 == 0) ? 0 : (regs[r] % op2);
		return pc+1;
	} else if (!strcmp(cmd, "IFEQ")) {
		int op1 = getOp(strtok(NULL, ","), regs);
		int op2 = getOp(strtok(NULL, ","), regs);
		if (op1 == op2)
			return pc+1;
		else {
			while (strcmp(program[pc++], "ENDIF") && pc < L);
			return pc;
		}
	} else if (!strcmp(cmd, "IFNEQ")) {
		int op1 = getOp(strtok(NULL, ","), regs);
		int op2 = getOp(strtok(NULL, ","), regs);
		if (op1 != op2)
			return pc+1;
		else {
			while (strcmp(program[pc++], "ENDIF") && pc < L);
			return pc;
		}
	} else if (!strcmp(cmd, "IFG")) {
		int op1 = getOp(strtok(NULL, ","), regs);
		int op2 = getOp(strtok(NULL, ","), regs);
		if (op1 > op2)
			return pc+1;
		else {
			while (strcmp(program[pc++], "ENDIF") && pc < L);
			return pc;
		}
	} else if (!strcmp(cmd, "IFL")) {
		int op1 = getOp(strtok(NULL, ","), regs);
		int op2 = getOp(strtok(NULL, ","), regs);
		if (op1 < op2)
			return pc+1;
		else {
			while (strcmp(program[pc++], "ENDIF") && pc < L);
			return pc;
		}
	} else if (!strcmp(cmd, "IFGE")) {
		int op1 = getOp(strtok(NULL, ","), regs);
		int op2 = getOp(strtok(NULL, ","), regs);
		if (op1 >= op2)
			return pc+1;
		else {
			while (strcmp(program[pc++], "ENDIF") && pc < L);
			return pc;
		}
	} else if (!strcmp(cmd, "IFLE")) {
		int op1 = getOp(strtok(NULL, ","), regs);
		int op2 = getOp(strtok(NULL, ","), regs);
		if (op1 <= op2)
			return pc+1;
		else {
			while (strcmp(program[pc++], "ENDIF") && pc < L);
			return pc;
		}
	} else
		return pc+1;
}

int process(int arg) {
	used[arg] = true;
	int* regs = new int[10];
	for (i = 1; i < 10; i++)
		regs[i] = 0;
	regs[0] = arg;
	for (int pc = 0; pc < L; ) {
		char* token = new char[30];
		strcpy(token, program[pc]);
		strtok(token, " ");
		if (!strcmp(token, "CALL")) {
			token = strtok(NULL, " ");
			int op2 = getOp(token, regs);
			if (used[op2])
				return -1;
			int r = result[op2];
			if (r != 0)
				regs[9] = r;
			else
				regs[9] = process(op2);
			if (regs[9] < 0)
				return -1;
			pc++;
		} else if (!strcmp(token, "RET")) {
			used[arg] = false;
			token = strtok(NULL, " ");
			int ret = getOp(token, regs);
			result[arg] = ret;
			return ret;
		} else {
			char* cmd = new char[30];
			strcpy(cmd, program[pc]);
			pc = execute(cmd, regs, pc);
		}			
	}
	used[arg] = false;;
	result[arg] = regs[9];
	return regs[9];
}

int main() {
	while (true) {
		scanf("%d %d", &L, &N);	
		getchar();
		if (!L && !N)
			break;
		used.clear();
		result.clear();
		for (i =0; i < L; i++) {
			gets(program[i]);
		}
		int r = process(N);
		if (r < 0)
			printf("*\n");
		else
			printf("%d\n", r);		
	}
}


