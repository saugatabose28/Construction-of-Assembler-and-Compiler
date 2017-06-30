#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int upper(char *sPtr){
	int count=0;
	while ( *sPtr != '\0' ) {
		*sPtr = toupper ( ( unsigned char ) *sPtr );
		++sPtr;
		count++;
	}
	//sPtr[count--]='\0';
	//printf("%c\n",*sPtr);
	return 0;
}

void main(){ 
	char a[10],ad[10],label[10],opcode[10],operand[10],mnemonic[10],symbol[10];
	int i,locctr,code,add,len,actual_len,f=1,line=1,l=1;
	FILE *fp1,*fp2,*fp3,*fp4;
	int j1,j2;
	
	fp1=fopen("twoout.dat","w");
	fp2=fopen("symtab.dat","r");
	fp3=fopen("out.dat","r");
	fp4=fopen("optab.dat","r");
	
	printf("hi");
	fscanf(fp3,"%s%s%s",label,opcode,operand);
	printf("%s %s %s\n",label,opcode,operand);
	j1=upper(opcode);
	if(strcmp(opcode,"STRT")==0){
		fprintf(fp1,"\t%s\t%s\t%s\n",label,opcode,operand);
		fscanf(fp3,"%d%s%s%s",&locctr,label,opcode,operand);
	}
	j1=upper(opcode);
	while(strcmp(opcode,"END")!=0){ 
		line++;
		if(strcmp(opcode,"DB")==0){
			fprintf(fp1,"%d\t%s\t%s\t%s\t",locctr,label,opcode,operand);
			len=strlen(operand);
			printf("len: %d\n",len);
			actual_len=len-3;
			for(i=2;i<(actual_len+2);i++){ 
				snprintf(ad,sizeof(ad),"%x",operand[i]);
				printf("%x\n",operand[i]);
				fprintf(fp1,"%s",ad);
			}
			printf("%d %s %s\n",locctr,opcode,operand);
			fprintf(fp1,"\n");
		} 
		else if(strcmp(opcode,"DD")==0){
			len=strlen(operand);
			snprintf(ad,sizeof(ad),"%d",operand[i]);
			printf("%d %s %s\n",locctr,opcode,operand);
			fprintf(fp1,"%d\t%s\t%s\t%s\t00000%s\n",locctr,label,opcode,operand,a);
		} 
		else if((strcmp(opcode,"RESB")==0)||(strcmp(opcode,"RESW")==0)){
			printf("%d %s %s\n",locctr,opcode,operand);
			fprintf(fp1,"%d\t%s\t%s\t%s\n",locctr,label,opcode,operand);
		} 
		else if((strcmp(opcode,"PRNT")==0)){
			printf("%d %s %s\n",locctr,opcode,operand);
			//fprintf(fp1,"%d\t%s\t%s\t%s\n",locctr,label,opcode,operand);
			rewind(fp2);
				fscanf(fp2,"%s%d",symbol,&add);
				j2=upper(symbol);
				while(strcmp(operand,symbol)!=0){
					fscanf(fp2,"%s%d",symbol,&add);
					j2=upper(symbol);
				}
				printf("%d %s %s\n",locctr,opcode,operand);
				fprintf(fp1,"%d\t%s\t%s\t%s\t11%d\n",locctr,label,opcode,operand,code,add);
		} 
		else{
			rewind(fp4);
			fscanf(fp4,"%s %x",mnemonic,&code);
			j2=upper(mnemonic);
			printf("1.%s 2.%s\n",opcode, mnemonic);
			while(strcmp(opcode,mnemonic)!=0){
				fscanf(fp4,"%s%x",mnemonic,&code);
				printf("1.%s 2.%s\n",opcode, mnemonic);
				j2=upper(mnemonic);
				if(strcmp(mnemonic,"STRT")==0){
					printf("hi\n");
					l=0;
					break;
				}
				f=0;
			}
			f=1;
			//printf("hello:\n");
			if(f==0 || l==0){
				printf("Error: %d\n",line);
				break;
			}
			else if(f==1){	
				printf("hello:\n");
				if(strcmp(operand,"$$")==0){
					printf("%d %s %s\n",locctr,opcode,operand);
					fprintf(fp1,"%d\t%s\t%s\t%s\t%d0000\n",locctr,label,opcode,operand,code);
				} 
				else{
					rewind(fp2);
					fscanf(fp2,"%s%d",symbol,&add);
					j2=upper(symbol);
					while(strcmp(operand,symbol)!=0){
						fscanf(fp2,"%s%d",symbol,&add);
						j2=upper(symbol);
					}
					printf("Added: %d %s %s\n",locctr,opcode,operand);
					fprintf(fp1,"%d\t%s\t%s\t%s\t%d%d\n",locctr,label,opcode,operand,code,add);
				}
			}
		} 
		fscanf(fp3,"%d%s%s%s\n",&locctr,label,opcode,operand);
		j1=upper(opcode);
	}
	printf("%d %s %s\n",locctr,opcode,operand);
	fprintf(fp1,"%d\t%s\t%s\t%s\n",locctr,label,opcode,operand);
	
	printf("FINISHED");
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	fclose(fp4);

}
