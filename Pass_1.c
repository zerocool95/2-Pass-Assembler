#include <stdio.h>
#include <string.h>

#define AN 48
//#include "fetchLabel.c"

void strrev1(char *st,char *rst)
{
	int i, j;
	for(i=0,j=strlen(st)-1; i<strlen(st)-1,j>=0; i++,j--)
		rst[i] = st[j];
	rst[i] = '\0';
}

void decToBinary(int n,char b[])
{
	char rb[7] = {0};	//reverse of binary
	int i;
	for(i=0; i<7; i++)
	{
		if(n>0)
		{
			rb[i] = (n%2) + AN;
			n = n/2;
		}
		else	rb[i] = AN;	
	}
	rb[i] = '\0';
	//printf("%s\n",rb); 
	strrev1(rb,b); //reverse string rb to b
}

int fetchLabel(FILE *finp, FILE *fout)
{
	char *d;	//dummy
	char s[40];	//stores current line
	char ct[5] = " \n";	//delimeter
	char b[7] = {0};
	char *tok;
	int count;	//label counter
	int l = 0;
	char lbl[10];
	int lcnt = 0;	//stores current line number
	int i;
	//printf("FFFFFF\n");
	
	while(fgets(s,40,finp)!=NULL)
	{
		tok = strtok(s,ct);
		if(strchr(tok,':')!=NULL)
		{
			decToBinary(lcnt,b);	
			tok[strlen(tok)-1] = '\0';
			fprintf(fout,"%s %s %d\n",tok,b,lcnt);
		}
		lcnt++;
	}
	return lcnt;
}

int main()
{
	FILE *finp, *fout, *flin, *flout, *freg, *fop, *fcon;

	int lcnt;	//Count line of code
	
	char inp[40] = {0};
	char s[40] = {0};
	char ct[] = " \t\n";
	char *tok, *tokR, *tokL, *tokO, *tokD, *tokI, *tokC; 
	
	char ele[1000][10][20] = {{{0}}};	int i,j,k;
	char eleR[100][3][20] = {{{0}}};
	char eleL[100][3][20] = {{{0}}};
	char eleO[100][3][20] = {{{0}}};
	
	finp = fopen("Input.txt", "r");
	fout = fopen("Output.txt", "w");
	flout = fopen("Label.txt", "w");
	fop = fopen("opcodes.txt", "r");
	freg = fopen("register.txt", "r");
	fcon = fopen("hex2bin.txt","r");
		
	lcnt = fetchLabel(finp,flout);
	
	fclose(flout);
	
	flin = fopen("Label.txt", "r");
	
	rewind(finp);
	rewind(fout);
	
	//write in the code in ele
	for(i=0; (i<lcnt); i++)
	{
		if(fgets(inp,40,finp)!=NULL)
		{
			for (tok=strtok(inp,ct),j=0; tok!=NULL && j<10; tok=strtok(NULL, ct),j++)
			{		
				if(strcpy(ele[i][j],tok));
				//puts(ele[i][j]);
			}
		}
	}
	
	for(i=0; i<lcnt; i++)
	{
		for(j=0; strlen(ele[i][j]); j++)
		{
			rewind(flin);
			rewind(freg);
			rewind(fop);
			rewind(fcon);

			while(fgets(s,40,freg)!=NULL)
			{

				tokD = strtok(s,ct);
				tokI = strtok(NULL,ct);
				if(!strcmp(tokD,ele[i][j]))
				{
					for(k=0; k<strlen(tokI)-1; k++)
						fprintf(fout,"%c",tokI[k]);
				}		
			}
			
			while(fgets(s,40,fop)!=NULL)
			{

				tokD = strtok(s,ct);
				tokO = strtok(NULL,ct);
				if(!strcmp(tokD,ele[i][j]))
				{
					for(k=0; k<strlen(tokO)-1; k++)
						fprintf(fout,"%c",tokO[k]);
				}		
			}
			
			while(fgets(s,40,flin)!=NULL)
			{

				tokD = strtok(s,ct);
				tokL = strtok(NULL,ct);
				tokO = strtok(NULL,ct);
				if(!strcmp(tokD,ele[i][j]))
				{
					for(k=0; k<strlen(tokL); k++)
						fprintf(fout,"%c",tokL[k]);
				}		
			}
			
			while(fgets(s,40,fcon)!=NULL)
			{

				tokD = strtok(s,ct);
				tokC = strtok(NULL,ct);
				if(!strcmp(tokD,ele[i][j]))
				{
					for(k=0; k<strlen(tokC); k++)
						fprintf(fout,"%c",tokC[k]);
				}		
			}
				    
		}
	
	fprintf(fout,"\n");
	}
	printf("The code was successfully executed!\n");
}


