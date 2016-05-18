#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int version = 01;

#define stackSize 10000
int stackPointer = 0;
int stack[stackSize];

#define HALT 0
#define PUSHC (1<<24)
#define ADD (2<<24)
#define SUB (3<<24)
#define MUL (4<<24)
#define DIV1 (5<<24)
#define MOD (6<<24)
#define RDINT (7<<24)
#define WRINT (8<<24)
#define RDCHR (9<<24)
#define WRCHR (10<<24)
#define IMMEDIATE(x) ((x) & 0x00FFFFFF)
#define SIGN_EXTEND(i) ((i) & 0x00800000 ? (i) | 0xFF000000 : (i))

void push (int i);
int pop();
void add();
void sub();
void mul();
void div1();
void mod();
void rdint();
void wrint();
void rdchr();
void wrchr();
void execPC();
void listPC();
void execParam();
void printHelp();

unsigned int code[10000];

/*MAIN*/
int main(int argc, char * argv[]) {
	printf("Ninja virtual machine started\n");
	if (argc > 0) {
		int i;
		for (i = 1; i < argc; ++i) {
			execParam(argv[i]);
		}
	}
	printf("Ninja virtual machine stopped\n");
	return 0;
}

/*Erfasst die Parameter und führt diese aus*/
void execParam (char *param) {
	if (strcmp(param, "--help") == 0) {
		printHelp();
	} else if (strcmp(param, "--version") == 0) {
		printf("The current version %d",version);
	} else if (strcmp(param, "--prog1") == 0) {
		code[0] = PUSHC | IMMEDIATE(3);
		code[1] = PUSHC | IMMEDIATE(4);
		code[2] = ADD;
		code[3] = PUSHC | IMMEDIATE(10);
		code[4] = PUSHC | IMMEDIATE(6);
		code[5] = SUB;
		code[6] = MUL;
		code[7] = WRINT;
		code[8] = PUSHC | IMMEDIATE(10);
		code[9] = WRCHR;
		code[10] = HALT;
	} else if (strcmp(param, "--prog2") == 0) {
		code[0]=PUSHC|IMMEDIATE(-2);
		code[1]=RDINT;
		code[2]=MUL;
		code[3]=PUSHC|IMMEDIATE(3);
		code[4]=ADD;
		code[5]=WRINT;
		code[6]=PUSHC|'\n';
		code[7]=WRCHR;
		code[8]=HALT;
	} else if (strcmp(param, "--prog3") == 0) {
		code[0]=RDCHR;
		code[1]=WRINT;
		code[2]=PUSHC|'\n';
		code[3]=WRCHR;
		code[4]=HALT;
	} else {
		printf("Argument not found\n");
	}
	listPC();
	execPC();
}

/*Stack operations*/
void push (int i) {
	if (stackPointer < stackSize) {
		stack[stackPointer++] = i;
	}
	else { 
		printf("Stack ist voll\n");
		exit(-1);
	}
}
int pop() {
	if (stackPointer > 0) {
		stackPointer--;
	}
	else { 
		printf("Stack ist leer\n");
		exit(-1);
	}
	return stack[stackPointer];
}
void add() {
	int s1 = pop();
	int s2 = pop();
	push(s2 + s1);
}
void sub() {
	int s1 = pop();
	int s2 = pop();
	push(s2 - s1);
}
void mul() {
	int s1 = pop();
	int s2 = pop();
	push(s2 * s1);
}
void div1() {
	int s1 = pop();
	int s2 = pop();
	push(s2 / s1);
}
void mod() {
	int s1 = pop();
	int s2 = pop();
	push(s2 % s1);
}
void rdint() {
	int rd;
	scanf("%i", &rd);
	push(rd);
}
void wrint() {
	printf("%i", pop());
}
void rdchr() {
	char rd;
	scanf("%c", &rd);
	push(rd);
}
void wrchr() {
	printf("%c", pop());
}

/*verarbeitet den Befehl und ruft die passende Methode auf*/
void execPC () {
	int i;
	for (i=0;;i++){
		switch(code[i]&0xFF000000){
			case HALT: return;
			break;
			case PUSHC:
			push(SIGN_EXTEND(IMMEDIATE(code[i])));break;
			case ADD:
			add();break;
			case SUB:
			sub();break;
			case MUL:
			mul();break;
			case DIV1:
			div1();break;
			case MOD:
			mod();break;
			case RDINT:
			rdint();break;
			case WRINT:
			wrint();break;
			case RDCHR:
			rdchr();break;
			case WRCHR:
			wrchr();break;
			default: printf("flascher wert\n");
		}
		if((code[i]&0xFF000000)==HALT){break;}
	}
}

void listPC(){
	int i;
	for (i=0;;i++){
		switch(code[i]&0xFF000000){
			case HALT:
			printf("%d: HALT\n",i);break;
			case PUSHC:
			printf("%d: PUSHC\t %d \n",i,SIGN_EXTEND(IMMEDIATE(code[i])));break;
			case ADD:
			printf("%d: ADD\n",i);break;
			case SUB:
			printf("%d: SUB\n",i);break;
			case MUL:
			printf("%d: MUL\n",i);break;
			case DIV1:
			printf("%d: DIV1\n",i);break;
			case MOD:
			printf("%d: MOD\n",i);break;
			case RDINT:
			printf("%d: RDINT\n",i);break;
			case WRINT:
			printf("%d: WRINT\n",i);break;
			case RDCHR:
			printf("%d: RDCHR\n",i);break;
			case WRCHR:
			printf("%d: WRCHR\n",i);break;
			default: printf("flascher wert\n");
		}
		if((code[i]&0xFF000000)==HALT){break;}
	}
}

void printHelp() {
	printf("====ARGUMENTS====\n");
	printf("--help for help\n");
	printf("--version to get the current version\n");
	printf("--prog1\n");
	printf("--prog2\n");
	printf("--prog3\n");
}