#include<stdio.h>
#include<string.h>
#define q 12//no. of mnemonics in the array A

void main(){

	int lc,ad,address,err=0;
	int s,num,l,i=0,j,n=0,line=1,f=0,f1=0,t=0,ni=0,m=0,t1;
	FILE *fp1,*fp2,*fp3,*fp4;
	char lab[10],op[10],val[10],code[10];
	char a[20][15]={"STA","STL","LDA","LDB","J","JEQ","JL","SUB","COMP","STCH","ADD","SUB"};
	char b[20][15]={"14","32","03","69","34","30","48","28","24","16","0C","AB"};
	char sym[15][10];
	int symadd[15];

	fp1=fopen("INPUT.DAT","r");
	fp2=fopen("OBJFILE.DAT","w");
	fp3=fopen("ERROR.DAT","w");
	fp4=fopen("SYMTAB.DAT","w");
	
	while((!feof(fp1))){
		fscanf(fp1,"%s\t%s\t%s",lab,op,val);
		t++;
		m++;
		//printf("%s\t%s\t%s\n",lab,op,val);
		if(strcmp(op,".")==0){
			//printf("hi");
			m=0;
		}
		else if(strcmp(op,"END")==0)
			break;
		//printf("%d\n",m);
	} 
	t=t-1;
	m--;
	//printf("%d\n",m);
	fclose(fp1);
	
	fp1=fopen("INPUT.DAT","r");
	fscanf(fp1,"%s\t%s\t%x",lab,op,&lc);
	fprintf(fp3,"-------------------------------------\n");
	fprintf(fp3,"LINE NO.\t|ERROR FOUND\n");
	fprintf(fp3,"-------------------------------------");
	fprintf(fp4,"SYMBOL\tADDRESS");
	s=lc;
	fprintf(fp2,"H^%s^00%x^%x\n",lab,lc,t*3);
	fprintf(fp2,"T^00%x^",lc);
	//printf("%d\n",m);
	if(m>10)
		fprintf(fp2,"1E");
	else
		fprintf(fp2,"%x",m*3);
		
	while(strcmp(op,".")!=0&&(!feof(fp1))){
		fscanf(fp1,"%s\t%s\t%s",lab,op,val);
		//printf("%s\t%s\t%s\n",lab,op,val);
		//printf("%d\n",n);
		line++;
		if(strcmp(lab,"**")!=0){			//lab chekng for symtab
			for(i=0;i<n;i++){	
				//printf("hi1 %s\n",lab);		
				if(strcmp(lab,sym[i])==0){
					f=1;
					break;
				}
				f=0;
			}
			if(f==0){
				//printf("hi2 %s\n",lab);	
				strcpy(sym[n],lab);
				symadd[n]=lc;
				fprintf(fp4,"\n%s\t%x",lab,lc);
				//printf("%d\n",lc);
				n++;
			} 
			if(f==1){
				fprintf(fp3,"%d\t\t|SYMBOL ALREADY DEFINED\n",line);
				err++;
			}
		}
		
		num=atoi(val);
		//printf("%d\n",lc);
		if(strcmp(op,"RESW")==0)		//op
			lc=lc+(num*3);
		else if(strcmp(op,"RESB")==0)
			lc=lc+num;
		else if(strcmp(op,"DB")==0){
			num=strlen(val)-3;
			lc=lc+num;
			for(i=2,j=0;i<strlen(val)-1;i++){
				code[j]=val[i];
				j++;
			}
			code[j]='\0';
			fprintf(fp2,"^%s",code);
			ni++;
		}
		else
			lc=lc+3;
		if(strcmp(op,".")==0)
			break;
	}

	//printf("%d\n",line);
	while(strcmp(op,"END")!=0&&(!feof(fp1))){	//after . section
		fscanf(fp1,"%s\t%s\t%s",lab,op,val);
		//printf("%s\t%s\t%s\n",lab,op,val);
		
		line++;
		if(strcmp(op,"END")==0)
			break;
		if((strcmp(lab,"**")!=0)&&((strcmp(op,"RESW")!=0||strcmp(op,"RESB")!=0||strcmp(op,"DW")!=0||strcmp(op,"DB")!=0))){ //if new symbol appears
			//printf("hi1 %s\t%s\t%s\n",lab,op,val);
			
			for(i=0;i<n;i++){
				if(strcmp(lab,sym[i])==0){
					f=1;
					break;
				}
				f=0;
			}
			if(f==0){
				strcpy(sym[n],lab);
				symadd[n]=lc;
				fprintf(fp4,"\n%s\t%x",lab,lc);
				n++;
			} 
			else{
				fprintf(fp3,"%d\t\t|SYMBOL ALREADY DEFINED\n",line);
				err++;
			}
		}
		else if((strcmp(lab,"**")==0) && ((strcmp(op,"J")==0) || (strcmp(op,"JEQ")==0)||(strcmp(op,"JL")==0))){
						//lab chekng for symtab
			//printf("%s\n",op);		
			for(i=0;i<n;i++){	
					//printf("hi1 %s\n",lab);		
				if(strcmp(val,sym[i])==0){
					//printf("added: %s %s\n",val,sym[i]);
					f=1;
					break;
				}
				f=0;
			}
			if(f==0){
				//printf("hi2 %s\n",lab);
				//printf("Adding: %s\n",val);	
				strcpy(sym[n],val);
				symadd[n]=lc;
				fprintf(fp4,"\n%s\t%x",val,lc);
					//printf("%d\n",lc);
				n++;
			} 			
		}
		else if(strcmp(op,"RESW")==0||strcmp(op,"RESB")==0||strcmp(op,"DW")==0||strcmp(op,"DB")==0)
			fprintf(fp3,"\n%d\t\t|Declaration not allowed here",line);
		if(strcmp(op,"RESW")!=0 && strcmp(op,"RESB")!=0 && strcmp(op,"DW")!=0 && strcmp(op,"DB")!=0){	//find value of mnemonic and addrss of symbl
			for(i=0;i<q;i++){
				if(strcmp(op,a[i])==0){									//chakng wid mnemonics
					strcpy(code,b[i]);
					f1=0;
					break;
				}
				f1=1;
			}
			if(f1==1){
				fprintf(fp3,"\n%d\t\t|WRONG OPCODE",line);
				err++;
			}
			for(i=0;i<n;i++){							//mnemonics is matched so find symbol
				if(strcmp(val,sym[i])==0){
					address=symadd[i];
					f=0;
					break;
				}
				f=1;
			}
			if(f){
				fprintf(fp3,"\n%d\t\t|UNDEFINED SYMBOL",line);
				err++;
			}
		}
		//printf("%d",ni);
		if(ni<10){
			fprintf(fp2,"^%s%x",code,address);
			ni++;
		} 
		else{
			fprintf(fp2,"T^00%x^",lc);
			if(m>10){
				fprintf(fp2,"1E");
				m=m-10;
			} 
			else{
				fprintf(fp2,"%x",m*3);
				fprintf(fp2,"^%s%x",code,address);
				ni=0;
			}
		} 
		lc=lc+3;
	}
	fprintf(fp2,"\nE^00%x",s);
	fprintf(fp3,"No of errors=%d\n--------------------------------------",err);
	printf("Output file:OBJCODE.DAT\nErrors are described in ERROR.DAT\nSymbol table is in the file:SYMTAB.DAT");
	
	fcloseall();
}
