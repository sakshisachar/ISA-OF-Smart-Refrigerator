#include"functionsc.h"
#include <stdlib.h>

char buffer[17],immediate[9],reg_binary[6],addr_binary[11];
int pc=1;
int Register[32] = {0};
int flag_reg[3] = {0};
int MSFreg = 0;
FILE *fp_mach;

void show_stats(){
	int i;
	for(i=0; i<32; i++){
		if(i%10==0) putchar('\n');
		printf("R%d : %d  ",i,Register[i]);
	}
	printf("\nFlag register\n C:%d\tZ:%d\tN:%d\n",flag_reg[0],flag_reg[1],flag_reg[2]);
	printf("MSFregister : %d\n\n",MSFreg);
}

int conversion(char a[])
{
	int rem,base=1;
	long long int val = atoi(a);
	int dec=0;
	while(val>0)
	{
		rem=val % 10;
		dec=dec+rem*base;
		val=val/10;
		base=base*2;
	}
	return dec;
}	

short unsigned int ALU(const char* signal,short unsigned int a,short unsigned int b){
	flag_reg[0] = 0; flag_reg[1] = 0; flag_reg[2] = 0;		// All flags 0
	printf("ALU signal sent is %s\n",signal);
	if(!strcmp(signal,"0000")){
		if(a+b >= sizeof(short unsigned)) flag_reg[0] = 1;			// Raise Carry flag
	return a+b;
	}
	else if (!strcmp(signal,"0001")){
		if(a < b) flag_reg[2] = 1;						// Raise Negative flag
	return a-b;
	}
	else if (!strcmp(signal,"0010")){
	return a*b;
	}
	else if(!strcmp(signal,"0011")){
	return a/b;
	}
	else if(!strcmp(signal,"0100")){
	return a & b;
	}
	else if(!strcmp(signal,"0101")){
	return a | b;
	}
	else if(!strcmp(signal,"0110")){
	return a << b;
	}
	else if(!strcmp(signal,"0111")){
	return a >> b;
	}
	else if(!strcmp(signal,"1000")){
	return ~a;
	}

}

//-------------------------Arithmetic Functions----------------
void ADDI(int regI, int imm){
	int regV = Register[regI];
	Register[regI] = ALU("0000", regV, imm);
}

void ADD(int regI1, int regI2){
	int regV1 = Register[regI1];
	int regV2 = Register[regI2];
	Register[regI1] = ALU("0000", regV1, regV2);
}

void SUBI(int regI, int imm){
	int regV = Register[regI];
	Register[regI] = ALU("0001", regV, imm);
}

void SUB(int regI1, int regI2){
	int regV1 = Register[regI1];
	int regV2 = Register[regI2];
	Register[regI1] = ALU("0001", regV1, regV2);
}

void MULI(int regI, int imm){
	int regV = Register[regI];
	Register[regI] = ALU("0010", regV, imm);
}

void MUL(int regI1, int regI2){
	int regV1 = Register[regI1];
	int regV2 = Register[regI2];
	Register[regI1] = ALU("0010", regV1, regV2);
}

void DIVI(int regI, int imm){
	int regV = Register[regI];
	Register[regI] = ALU("0011", regV, imm);
}

void DIV(int regI1, int regI2){
	int regV1 = Register[regI1];
	int regV2 = Register[regI2];
	Register[regI1] = ALU("0011", regV1, regV2);
}

void AND(int regI1, int regI2){
	int regV1 = Register[regI1];
	int regV2 = Register[regI2];
	Register[regI1] = ALU("0100", regV1, regV2);
}

void OR(int regI1, int regI2){
	int regV1 = Register[regI1];
	int regV2 = Register[regI2];
	Register[regI1] = ALU("0101", regV1, regV2);
}

void LSHIFT(int regI){
	int regV = Register[regI];
	Register[regI] = ALU("0110", regV, 0);
}

void RSHIFT(int regI){
	int regV = Register[regI];
	Register[regI] = ALU("0111", regV, 0);
}

void NOT(int regI){
	int regV = Register[regI];
	Register[regI] = ALU("1000", regV, 0);
}

void CMPI(int regI, int imm){
	int regV = Register[regI];
	char diff = ALU("0001",regV,imm);
	if(diff == 0) flag_reg[1] = 1;						// Raise Zero Flag
}
void CMP(int regI1,int regI2 ){
	int regV1 = Register[regI1];
	int regV2 = Register[regI2];
	char diff = ALU("0001",regV1,regV2);
	if(diff == 0) flag_reg[1] = 1;						// Raise Zero Flag
}
//--------------------------------------------------

//--------Data Transfer----------------------------
void MOVI(int regI, int imm){
	Register[regI] = imm;
}

void MOV(int regI1, int regI2){
	Register[regI1] = Register[regI2];
}
//------------------------------------------------

//---------Control Transfer-----------------------

void JMP(int address){
	// Change the FILE pointer , pc and IR
	fseek(fp_mach,(address-1)*17,SEEK_SET);
	pc = address;
}

void JNQ(int address){
	if(flag_reg[1] == 0)						// Zero Flag not raised from last operation
		JMP(address);
}

void JEQ(int address){
	if(flag_reg[1] == 1)						// Zero Flag raised from last operation
		JMP(address);
}

void JLT(int address){
	if(flag_reg[2] == 1)						// Neg Flag raised from last operation
		JMP(address);
}

void JGT(int address){
	if(flag_reg[2] == 0)						// Neg Flag and zero flag not raised from last operation
		JMP(address);
}

void IN(int regI){
	switch(regI){
		case 0:{
			puts("Enter the password:");
		break;		
		}
		case 1:{
			puts("Enter the storage amount");
		break;		
		}
		case 2:{
			puts("Enter the voulume of water");
		break;		
		}
		case 3:{
			puts("\nPress 1 to enter password");
			puts("Press 2 to open door");
			puts("Press 3 to set temperature of refrigerator");
			puts("Press 4 to add load");
			puts("Press 5 to fill water container");
			puts("Press 6 for precise fill");
			puts("Press 7 to set timer to defrost");
			puts("Press 8 to check filter status");
			puts("Press 9 to see the power usage in a day in energy monitor");
			puts("Press 10 to close the door");
		break;		
		}
		case 18:{
			puts("Press enter the temprature for refrigerator");
		break;		
		}
		case 19:{
			puts("Please enter the time for defrost");		
		break;		
		}
		case 31:{
			puts("Press 1 if you want to call another function otherwise 0");
		break;
		}
	}
	scanf("%d",&Register[regI]);
	puts("");
}

void OUT(int regI){
	printf("The value of R%d : %d\n",regI,Register[regI]);
}

void MSF(){
	MSFreg = pc+1;
}
void RET(){
	pc = MSFreg;
	fseek(fp_mach,(pc-1)*17,SEEK_SET);
}
void HLT(){
	exit(0);
}

void doorTimer()
{
	Register[17] = 15;
	printf("YOUR DOOR IS OPEN FROM 15 Minutes\n Please close the door\n");
}

void energyMonitor()
{
Register[26]=(int)(Register[26]+((2.0/15.0)*Register[17]));			// Register[17] is time Register[26]
printf(" your power usage is  %d Watt ",Register[26]);
}

void filterStatus()
{
	if(Register[6]<2)				//current water in filter
	{
		printf("Your filter level is just 2 litres\n Add water to it\n");
	}
	else{
		printf("Water level is greater than 2\n");
	}
}

void addWater()
{
Register[6] = 10;
printf(" container is full\n");
}

void doorOpen()
{	printf("your door is open\n");
	Register[27]=1;
	printf("Lights On\n");
}

void doorClose()
{
	Register[27]=0;
	printf("Lights Off\n");
}
