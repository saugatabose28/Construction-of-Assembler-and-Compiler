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
	char opcode[10],mnemonic[10],operand[10],label[10],code[10];
	int locctr,start,length,i,f=0,n=0,line=1,err=0;
	FILE *fp1,*fp2,*fp3,*fp4,*fp5;
	char sym[15][10];

	fp1=fopen("input.dat","r");
	fp2=fopen("symtab.dat","w");
	fp3=fopen("out.dat","w");
	fp4=fopen("optab.dat","r");
	fp5=fopen("ERROR.DAT","w");
	fprintf(fp5,"-------------------------------------\n");
	fprintf(fp5,"LINE NO.\t|ERROR FOUND\n");
	fprintf(fp5,"-------------------------------------\n");
	
	fscanf(fp1,"%s%s%s",label,opcode,operand);
	//printf("%s %s %s\n",label,opcode,operand);
	
	i=upper(opcode);
	if(strcmp(opcode,"STRT")==0){
		start=atoi(operand);
		locctr=start;
		fprintf(fp3,"%s\t%s\t%s\n",label,opcode,operand);
		printf("%s %s %s\n",label,opcode,operand);
		fscanf(fp1,"%s%s%s",label,opcode,operand);
	} 
	else
		locctr=0;
		
	i=upper(opcode);	
	while(strcmp(opcode,"END")!=0){
		line++;
		//printf("%s\n",opcode);
		fprintf(fp3,"%d\t",locctr);
		//printf("%d\n",locctr);
		
		if(strcmp(label,"$$")!=0){			
			for(i=0;i<n;i++){	
				//printf("hi1 %s\n",lab);		
				if(strcmp(label,sym[i])==0){
					f=1;
					break;
				}
				f=0;
			}
			if(f==0){
				//printf("hi2 %s\n",lab);
				i=upper(label);	
				strcpy(sym[n],label);
				fprintf(fp2,"%s\t%d\n",label,locctr);
				//printf("%s %d\n",label,locctr);
				//printf("%d\n",lc);
				n++;
			} 
			if(f==1){
				fprintf(fp5,"%d\t\t|SYMBOL ALREADY DEFINED\n",line);
				err++;
			}
		}
		if(strcmp(opcode,"PRNT")==0){			
			for(i=0;i<n;i++){	
				//printf("hi1 %s\n",lab);		
				if(strcmp(label,sym[i])==0){
					f=1;
					break;
				}
				f=0;
			}
			if(f==0){
				//printf("hi2 %s\n",lab);
				strcpy(sym[n],opcode);
				fprintf(fp2,"%s\t%d\n",opcode,locctr);
				//printf("%s %d\n",label,locctr);
				//printf("%d\n",lc);
				n++;
				locctr+=3;
			} 
			if(f==1){
				fprintf(fp5,"%d\t\t|SYMBOL ALREADY DEFINED\n",line);
				err++;
			}
		}					
			
		//printf("hi3\n");	
		rewind(fp4);
		//printf("hi4\n");
		fscanf(fp4,"%s",mnemonic);
		//printf("hi5\n");
		//printf("%s\n",mnemonic);
		//printf("hi6\n");
		i=upper(mnemonic);
		
		while(strcmp(mnemonic,"END")!=0){ 
			// printf("m: %s\n",mnemonic);
			if(strcmp(opcode,mnemonic)==0){
				locctr+=3;
				//printf("m: %s %d\n",opcode,locctr);
				f=0;
				break;
			} 
			f=1;
			fscanf(fp4,"%s",mnemonic);
			i=upper(mnemonic);
		}
		
		//if(f==1){
		//	fprintf(fp5,"%d\t\t|Wrong Opcode\n",line);
		//	err++;
		//}
		if(f==1){
			printf("1.%s\n",opcode);
			if(strcmp(opcode,"PRNT")!=0){
				printf("2.%s\n",opcode);
				if((strcmp(opcode,"RESW")!=0))
					if((strcmp(opcode,"RESB")!=0))
						if((strcmp(opcode,"DD")!=0))
							if((strcmp(opcode,"DB")!=0)){
								fprintf(fp5,"\n%d\t\t|Wrong Opcode\n",line);
								printf("%d\t\t|Wrong Opcode\n",line);
								err++;
							}
			}
				
		}	
		if(strcmp(opcode,"DD")==0){
			locctr+=3;
			//printf("%d\n",locctr);
		}
		else if(strcmp(opcode,"RESW")==0){
			locctr+=(3*(atoi(operand)));
			//printf("%d\n",locctr);
		}
		else if(strcmp(opcode,"RESB")==0){
			locctr+=(atoi(operand));
			//printf("%d\n",locctr);
		}
		else if(strcmp(opcode,"DB")==0){
			++locctr;
			//printf("%d\n",locctr);
		}
			
		fprintf(fp3,"%s\t%s\t%s\n",label,opcode,operand);
		//printf("%s %s %s\n",label,opcode,operand);
		fscanf(fp1,"%s%s%s",label,opcode,operand);
		printf("Next: %s %s %s\n",label,opcode,operand);
		i=upper(opcode);
	}
	fprintf(fp3,"%d\t%s\t%s\t%s\n",locctr,label,opcode,operand);
	fprintf(fp5,"No of errors=%d\n--------------------------------------",err);
	//printf("%d %s %s %s\n",locctr,label,opcode,operand);
	length=locctr-start;
	printf("\nThe length of the program is %d",length);
	
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	fclose(fp4);
	fclose(fp5);
	
}
