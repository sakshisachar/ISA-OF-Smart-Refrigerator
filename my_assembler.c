#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Opcodes              //This node is used for Hashing using Chaining
{
        char name[10], code[35], format[5];	// Name of Opcode, Machine code of 		Opcode, Format of Opcode
        /**
        ri  = reg imm.
        rr  = reg reg
        a   = add
        z   = zero
        */
	struct Opcodes *next;
};

struct Symbol_table           //Symbol_table Table is made using Linked List to save space
{
	int add;
	char name[50];
    	struct Symbol_table *next;
};

typedef struct Symbol_table Symbol_table;
typedef struct Opcodes Opcodes;

Opcodes* map[13] = {NULL};
Symbol_table *head=NULL;

//returns the index of Operations in the hash map

int get_map_index(char Name[]) {	

	int val=0,i;
	for(i=0 ; Name[i]!='\0' ; i++) {
		
		val+=Name[i];
	}
	return val%13;
}

// Inserts the node 'Node' in the hash map at position idx

void Insert_at_index(int idx, Opcodes*Node) {

	if(map[idx]==NULL) {
		
		map[idx]=Node;
		Node->next=NULL;
		return ;
	}
	
	Opcodes *temp=map[idx];
	while(temp->next!=NULL) {
	
		temp=temp->next;
	}
	temp->next=Node;
	Node->next=NULL;
}

// Finds index of Operation in the hash map and calss Insert_at_index()

void Insert_into_map(Opcodes *Node) {
	
	int idx=get_map_index(Node->name);
	Insert_at_index(idx,Node);	
}

// returns Node corresponding to Operation name 'op_code' by searching in hash map

Opcodes* get_Opcode_Node(char *op_code) {

	//puts(op_code);
	Opcodes*temp=NULL;
	int idx=get_map_index(op_code);
	//printf("%d index\n",idx);
	if(map[idx]==NULL) {
		
		//printf("Invalid Opcode\n");
        	return temp;
	}
	//printf("type\n");
	temp=map[idx];
	while(strcmp(temp->name,op_code)!=0) {
		//puts(temp->name);
		temp=temp->next;	
		if(temp==NULL)
			break;
	}
	//printf("%s %s %s\n",temp->name,temp->code,temp->format);
	//printf("value not returned\n");
	if(temp==NULL)
        {
            printf("Opcode not found!\n");
            return NULL;
        }
        else
        {
            return temp;
        }
}

// returns the binary equivalent of register name

char* get_register_binary(char *reg) {

	char *val;
	if(!strcmp(reg,"R00")) {
		val="00000";
		return val;
	}
	if(!strcmp(reg,"R01")) {
		val="00001";
		return val;
	}
	if(!strcmp(reg,"R02")) {
		val="00010";
		return val;
	}
	if(!strcmp(reg,"R03")) {
		val="00011";
		return val;
	}
	if(!strcmp(reg,"R04")) {
		val="00100";
		return val;
	}
	if(!strcmp(reg,"R05")) {
		val="00101";
		return val;
	}
	if(!strcmp(reg,"R06")) {
		val="00110";
		return val;
	}
	if(!strcmp(reg,"R07")) {
		val="00111";
		return val;
	}
	if(!strcmp(reg,"R08")) {
		val="01000";
		return val;
	}
	if(!strcmp(reg,"R09")) {
		val="01001";
		return val;
	}
	if(!strcmp(reg,"R10")) {
		val="01010";
		return val;
	}
	if(!strcmp(reg,"R11")) {
		val="01011";
		return val;
	}
	if(!strcmp(reg,"R12")) {
		val="01100";
		return val;
	}
	if(!strcmp(reg,"R13")) {
		val="01101";
		return val;
	}
	if(!strcmp(reg,"R14")) {
		val="01110";
		return val;
	}
	if(!strcmp(reg,"R15")) {
		val="01111";
		return val;
	}
	if(!strcmp(reg,"R16")) {
		val="10000";
		return val;
	}
	if(!strcmp(reg,"R17")) {
		val="10001";
		return val;
	}
	if(!strcmp(reg,"R18")) {
		val="10010";
		return val;
	}
	if(!strcmp(reg,"R19")) {
		val="10011";
		return val;
	}
	if(!strcmp(reg,"R20")) {
		val="10100";
		return val;
	}
	if(!strcmp(reg,"R21")) {
		val="10101";
		return val;
	}
	if(!strcmp(reg,"R22")) {
		val="10110";
		return val;
	}
	if(!strcmp(reg,"R23")) {
		val="10111";
		return val;
	}
	if(!strcmp(reg,"R24")) {
		val="11000";
		return val;
	}
	if(!strcmp(reg,"R25")) {
		val="11001";
		return val;
	}
	if(!strcmp(reg,"R26")) {
		val="11010";
		return val;
	}
	if(!strcmp(reg,"R27")) {
		val="11011";
		return val;
	}
	if(!strcmp(reg,"R28")) {
		val="11100";
		return val;
	}
	if(!strcmp(reg,"R29")) {
		val="11101";
		return val;
	}
	if(!strcmp(reg,"R30")) {
		val="11111";
		return val;
	}
	if(!strcmp(reg,"R31")) {
		val="00001";
		return val;
	}
}

// returns 8 bit binary conversion of a number

int* get_binary_conv8(int var) {

	int *ans,i;
	ans=(int*)malloc(8*sizeof(int));
	for(i=0 ; i<8 ; i++) {
		
		ans[i]=0;
	}
	i=i-1;
	int val=var,x,y;
	while(var!=0) {
	
		x=var%2;
		y=var/2;
        	ans[i--]=x;
         	var=y;
    	}
    	return 	ans;
}

// returns 10 bit binary conversion of a number

int* get_binary_conv10(int var) {

	int *ans,i;
	ans=(int*)malloc(sizeof(int)*10);
	for(i=0 ; i<10 ; i++) {
		
		ans[i]=0;
	}
	i=i-1;
	int val=var,x,y;
	while(var!=0) {
	
		x=var%2;
		y=var/2;
        	ans[i--]=x;
         	var=y;
    	}
    	return ans;
}

// returns 10 bit binary address of label from symbol table

int* get_add_from_symbol(char *label_name) {

	Symbol_table *tmp=head;
	if(tmp==NULL) {
		
		printf("No label found\n");
		return NULL;
	}
	while(strcmp(tmp->name,label_name)) {
	
		tmp=tmp->next;
	}
	int *converted_add=get_binary_conv10(tmp->add);
	return converted_add;
} 

void main() {

	char opcode[100],machine_ins[100],format_op[5];
	//printf("Open input opcode\n");
	FILE *opcode_ip=fopen("op_ip.txt","r+");
	//printf("Open input opcode succesfully\n");
	char foo1,foo2,foo3;
	int ILC=0,base=0;
	//printf("hi\n");
	do {
		
		foo1=fscanf(opcode_ip,"%s",opcode);
		foo2=fscanf(opcode_ip,"%s",machine_ins);
		foo3=fscanf(opcode_ip,"%s",format_op);
		if(foo1==EOF && foo2==EOF && foo3==EOF)
			break;
		Opcodes *Node=(Opcodes*)malloc(sizeof(Opcodes));
		
		strcpy(Node->name,opcode);
		strcpy(Node->code,machine_ins);
		strcpy(Node->format,format_op);
		//Node->next=NULL;
		Insert_into_map(Node);
		//printf("inf loop");
	} while(foo1!=EOF && foo2!=EOF && foo3!=EOF);
	
	//printf("While exe\n");
	
	printf("Hash map Created Successfully!\n");
	
	Opcodes *haha	;
	int q;
	for(q=0 ; q<=12 ; q++) {
	
		haha=map[q];
		printf("%d - ",q);
		while(haha!=NULL) {
			
			printf("%s::%s::%s\t",haha->name,haha->format,haha->code);
			haha=haha->next;
		}
		printf("\n");
	}
	    
	FILE *instructions_ip=fopen("instructions_ip.txt","r+");
	char op[100];
	int flag=0;
	//printf("FILE POINTER\n");
	printf("CREATING SYMBOL TABLE\n");
	while (fgets(op,sizeof op,instructions_ip)!=NULL) {		//read a line 		
		
		//printf("Line read using fgets %d\n",ILC);
		//int i;
		//printf("%lu    ",strlen(op));
		//for(i=0 ; op[i]!='\0' ; ++i)
		//	printf("%c",op[i]);
		//printf("\n");
		//printf("%d       ",ILC);
		//for(i=0 ; op[i]!='\0' ; ++i)
		//	printf("%c",op[i]);
		
		int len;
		//printf("%d   abcd    ",ILC);
		//printf("%lu \n",strlen(op));
		//printf("%c %c %c ",op[0],op[1],op[2]);
		
		//if(op[0]=='H' && op[1]=='L' && op[2]=='T') {
		
		//	printf("%c %c %c ",op[0],op[1],op[2]);
		//	break;
		//}
		for(len=0 ; op[len]!='\0' ; ++len) {
		
			//printf("%s",op);
			//printf("%d",op[len+1]);	
			if(op[len]==':') {
			
				//printf("Label Found!\n");
				Symbol_table *tmp2;
				Symbol_table *tmp=(Symbol_table*)malloc(sizeof(Symbol_table));
				int j;
				for(j=0 ; j<len ; j++) {
				
					tmp->name[j]=op[j];
				}	
				//printf("%c",op[len]);
				tmp->add=base+ILC+1;
				tmp->name[j]='\0';
				tmp->next=NULL;
				//int j;
				//printf("%d  ",tmp->add);
				//for(j=0 ; j<i ; j++)
				//	printf("%c",tmp->name[j]);
				//printf("\n");
				
				if(head==NULL) {
				
					head=tmp;
				}
				else {
				
					tmp2=head;
					while(tmp2->next!=NULL) {
					
						tmp2=tmp2->next;
					}
					tmp2->next=tmp;
				}
			}	
		}
		++ILC;
		//printf("%d ",ILC);
	}
	printf("PASS 1 COMPLETED SUCCESFULLY\n\nSymbol table :\n");
	FILE *fp=fopen("Symbol_table.txt","w+");	
	Symbol_table *print=head;
	while(print!=NULL) {
	
		printf("%s :: ",print->name);
		fprintf(fp,"%s :: ",print->name);
	        printf("%d\n",print->add);
        	fprintf(fp,"%d\n",print->add);
        	print=print->next;
	}
	printf("\n\n");
	//fflush(instructions_ip);	
	//fclose(instructions_ip);
	//printf("asdfgh\n");
	//instructions_ip=fopen("instructions_ip.txt","r+");
	rewind(instructions_ip);
	//puts(op);
	FILE *machine_code_op=fopen("machine_code_op.txt","w+");
	char c4,str[100],c5;
	//c4=fscanf(instructions_ip,"%s",str);
	//c4=fscanf(instructions_ip,"%s",str);
	do {
		//printf("line 374\n");
		c4=fscanf(instructions_ip," %s",str);
		if(c4==EOF)
			break;
		//printf("+2 lines\n");
		int len;
		for(len=0 ; str[len]!='\0' ; ++len) {
		//	printf("%c ",str[len]);
			continue;
		}
		//puts(str);
		//printf("\n");
		//puts("print hua");
		if(str[len-1]==':') {
		
			//printf("len\n");
			fprintf(machine_code_op,"\n");
			//printf("machine code 1\n");
		}	
		else {
		
			//printf("non label\n");
			char s1[100],s2[100],c5,c6;
			//printf("line 396\n");
			//puts(str);
			Opcodes *currnode=get_Opcode_Node(str);
			printf("%s::%s::%s\n",currnode->name,currnode->code,currnode->format);
			//puts(currnode->format);
			//printf("node mili\n");
			char *Op_format;
			Op_format=(char*)malloc(sizeof(char)*100);
			strcpy(Op_format,currnode->code);
			//int p;
			//printf("\n");	
			//puts(Op_format);
			fprintf(machine_code_op," %s",Op_format);
			//printf("machine code 2\n");	
			if(strcmp(currnode->format,"r")==0) {
				
				c5=fscanf(instructions_ip,"%s",s1);
				//printf("%s\n",s1);
				fprintf(machine_code_op,"%s",get_register_binary(s1));
				//printf("%s\n",s1);
				fprintf(machine_code_op,"\n");
				//printf("machine code 4\n");
			}
			else if(strcmp(currnode->format,"rr")==0) { 
			
				c5=fscanf(instructions_ip,"%s",s1);
				c6=fscanf(instructions_ip,"%s",s2);
				fprintf(machine_code_op,"%s",get_register_binary(s1));
				//printf("%s\n",s1);
				//printf("machine code 6\n");
				fprintf(machine_code_op,"%s",get_register_binary(s2));
				//printf("%s\n",s2);
				//printf("machine code 7\n");
				fprintf(machine_code_op,"\n");
				//printf("machine code 8\n");
			}
			else if(strcmp(currnode->format,"z")==0) {
				
				fprintf(machine_code_op,"\n");
				//printf("machine code 9\n");
			}
			else if(strcmp(currnode->format,"ri")==0) {
				
				//puts("reg imm");
				int var;
				c5=fscanf(instructions_ip,"%s",s1);
				//puts(s1);
				//printf("gaga\n");
				c6=fscanf(instructions_ip,"%d",&var);
				//printf("%d\n",var);
				fprintf(machine_code_op,"%s",get_register_binary(s1));
				int *conv;
				conv=get_binary_conv8(var);
				int j;
				for(j=0 ; j<8 ; j++) 
					fprintf(machine_code_op,"%d",conv[j]);
				fprintf(machine_code_op,"\n");
				//printf("machine code 10\n");	
			}
			else if(strcmp(currnode->format,"a")==0) {
				
				int var;
				c5=fscanf(instructions_ip,"%s",s1);
				int *conv;
				conv=get_add_from_symbol(s1);
				int j;
				for(j=0 ; j<10 ; j++)
					fprintf(machine_code_op,"%d",conv[j]);
				fprintf(machine_code_op,"\n");
			}
				 
		}
		//puts("while exe\n");

	} while(c4!=EOF);	
 
 	//printf("almost done\n");
}
