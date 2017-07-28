/*
Instruction Set Architecture

Computer Architecture Project
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* getbits: get n bits from position p */
unsigned getbits(unsigned x, int p, int n)
{
	return (x >> (p+1-n)) & ~(~0 << n);
}


int bin2dec(char* str)      //Binary string to decimal convert
{
 int n = 0;
 int size = strlen(str) - 1;
        int count = 0;
 while ( *str != '\0' ) {
  if ( *str == '1' )
      n = n + pow(2, size - count );
  count++;
  str++;
 }
 return n;

}

static int flagRegister=0;

char *substring(char *string, int position, int length)  //substring method . Returns substring (pointer to the string)
{
   char *pointer;
   int c;

   pointer = malloc(length+1);

   if (pointer == NULL)
   {
      printf("Unable to allocate memory.\n");
      exit(EXIT_FAILURE);
   }

   for (c = 0 ; c < position -1 ; c++)
      string++;

   for (c = 0 ; c < length ; c++)
   {
      *(pointer+c) = *string;
      string++;
   }

   *(pointer+c) = '\0';

   return pointer;
}
int checkSetBit(int flag)     //to check which flag is set.
{
   
    if((flag&flagRegister)!=0)
        return 1;
    else
        return 0;
  
}



int main()                                                         //Main Method
{
    FILE *finp,*fout,*fh;
    int R[20],i,j,k,inputNumber,outputNumber,tt;
    char ch;
    int num,temp;
    char str[33],subReg[6],subImm[8],subReg1[6],subReg2[6],subAdd[4],strJmp[33];
    int SF[3];SF[0]=0;SF[1]=0;SF[2]=0;                              // 0-positive  ,1-Zero ,  2-negative
    finp=fopen("Output.txt","r");                                   //output of assembler
    for(i=0;i<20;i++)
    {
        R[i]=0;
    }
        printf("\n\n<---Welcome to sauravRohanParadox ISA Binary to machine code conversion--->\n\n ");

        printf("This program executes machine code.\n Some Points to be noted:\nA)Label syntax label:Add r1 r2 \n B) ALL OPERATIONS ON INSTRUCTIONS ARE DONE USING BITWISE OPERATORS AVAILABLE IN C\nPress 1 for help of opcode design.\n Press 2 for running the code.\n");
        scanf("%d",&tt);
        if(tt==1)
        {
            fh=fopen("help.txt", "r");
				while(1)
   				{
     					ch = fgetc(fh);
      					if( feof(fh) )
      					{
          					break ;
      					}
      					printf("%c", ch);
   				}
				fclose(fh);
        }
        else
    while(!feof(finp))
    {
    	 JumpAdd:
         fscanf(finp,"%s",str);
		 if(str[0]=='0'&&str[1]=='0'&&str[2]=='0')
            {
            	printf("End of program\n\n");
                exit(0);
            }
           else if(getbits(strtol(str,NULL,2),31,3) == 4)  //1 address 1 immediate
            {
               
                if(getbits(strtol(str,NULL,2),14,3) == 1) //MOVX
                {
                   
                    //strcpy(subReg,substring(str,21,5));
                
                 	//strcpy(subImm,substring(str,26,7));
                   
                    R[getbits(strtol(str,NULL,2),11,5)]=getbits(strtol(str,NULL,2),6,7);

                   printf("%d is moved in R%d\n",getbits(strtol(str,NULL,2),6,7),getbits(strtol(str,NULL,2),11,5));
                }
                else if(getbits(strtol(str,NULL,2),14,3) == 2)  //ADDX
                {
                    
                 //   strcpy(subReg,substring(str,21,5));
                  
                   // strcpy(subImm,substring(str,26,7));
                   
                    R[getbits(strtol(str,NULL,2),11,5)] += getbits(strtol(str,NULL,2),6,7);
                   
                    printf("%d is added in R%d\n",getbits(strtol(str,NULL,2),6,7),getbits(strtol(str,NULL,2),11,5));

                }
                else if(getbits(strtol(str,NULL,2),14,3) == 3)  //SUBX
                {
                    
                    //strcpy(subReg,substring(str,21,5));
                  
                    //strcpy(subImm,substring(str,26,7));
                   
                    R[getbits(strtol(str,NULL,2),11,5)] -= getbits(strtol(str,NULL,2),6,7);
                  
                   printf("%d is subtracted from R%d\n",getbits(strtol(str,NULL,2),6,7),getbits(strtol(str,NULL,2),11,5));

                }
                else if(getbits(strtol(str,NULL,2),14,3) == 4)  //MULX
                {
                    
                    //strcpy(subReg,substring(str,21,5));
                  
                  //  strcpy(subImm,substring(str,26,7));
                   
                    R[getbits(strtol(str,NULL,2),11,5)] *= getbits(strtol(str,NULL,2),6,7);
                   
                   printf("%d is multiplied in R%d\n",getbits(strtol(str,NULL,2),6,7),getbits(strtol(str,NULL,2),11,5));
                }
                else if(getbits(strtol(str,NULL,2),14,3) == 5)  //DIVX
                {
                    
                    //strcpy(subReg,substring(str,21,5));
                  
                  //  strcpy(subImm,substring(str,26,7));
                   
                    R[getbits(strtol(str,NULL,2),11,5)] /= getbits(strtol(str,NULL,2),6,7);
                   
                   printf("%d is divided by R%d\n",getbits(strtol(str,NULL,2),6,7),getbits(strtol(str,NULL,2),11,5));
                }
                else if(getbits(strtol(str,NULL,2),14,3) == 0)  //CMPX
                {
                    
                    //strcpy(subReg,substring(str,21,5));
                   
                    //strcpy(subImm,substring(str,26,7));

                    if(R[getbits(strtol(str,NULL,2),11,5)] == getbits(strtol(str,NULL,2),6,7))
                    {
                       
                        flagRegister|=2;
                        flagRegister&=2;
                       printf("Zero flag set \t\t\t(0|1|0)\n");

                    }else if(R[getbits(strtol(str,NULL,2),11,5)] < getbits(strtol(str,NULL,2),6,7))
                    {
                       
                        flagRegister|=1;
                        flagRegister&=1;
                        printf("Negative flag set\t\t(0|0|1)\n");

                    }else if(R[getbits(strtol(str,NULL,2),11,5)] > getbits(strtol(str,NULL,2),6,7))
                    {
                       
                        flagRegister|=4;
                        flagRegister&=4;
                       printf("Positive flag set       \t(1|0|0)\n");

                    }
                   
                }
            }

           else if(getbits(strtol(str,NULL,2),31,3) == 3)  //2 address
            {
                
                if(getbits(strtol(str,NULL,2),12,3) == 1) //MOV
                {
                  
                    //strcpy(subReg1,substring(str,23,5));

                    //strcpy(subReg2,substring(str,28,5));

                    R[getbits(strtol(str,NULL,2),9,5)]=R[getbits(strtol(str,NULL,2),4,5)];
                   
                   printf("R%d is copied in R%d\n",getbits(strtol(str,NULL,2),4,5),getbits(strtol(str,NULL,2),9,5));
                }
                else if(getbits(strtol(str,NULL,2),12,3) == 2)  //ADD
                {

                   
                   // strcpy(subReg1,substring(str,23,5));
                   
                   // strcpy(subReg2,substring(str,28,5));
                   
                    R[getbits(strtol(str,NULL,2),9,5)]+=R[getbits(strtol(str,NULL,2),4,5)];
                   
                    printf("R%d is added in R%d and stored in R%d\n",getbits(strtol(str,NULL,2),4,5),getbits(strtol(str,NULL,2),9,5),getbits(strtol(str,NULL,2),4,5));
                }
                else if(getbits(strtol(str,NULL,2),12,3) == 3)  //SUB
                {

                  
                    //strcpy(subReg1,substring(str,23,5));
                   
                    //strcpy(subReg2,substring(str,28,5));
                   
                    R[getbits(strtol(str,NULL,2),9,5)]-=R[getbits(strtol(str,NULL,2),4,5)];
                   
                   printf("R%d is subtracted R%d and stored in R%d\n",getbits(strtol(str,NULL,2),4,5),getbits(strtol(str,NULL,2),9,5),getbits(strtol(str,NULL,2),4,5));
                }
                else if(getbits(strtol(str,NULL,2),12,3) == 4)  //MUL
                {

                  
                    //strcpy(subReg1,substring(str,23,5));
                   
                    //strcpy(subReg2,substring(str,28,5));
                   
                    R[getbits(strtol(str,NULL,2),9,5)]*=R[getbits(strtol(str,NULL,2),4,5)];
                   
                   printf("R%d is multiplied R%d and stored in R%d\n",getbits(strtol(str,NULL,2),4,5),getbits(strtol(str,NULL,2),9,5),getbits(strtol(str,NULL,2),4,5));
                }
                else if(getbits(strtol(str,NULL,2),12,3) == 5)  //DIV
                {


                   
                  //  strcpy(subReg1,substring(str,23,5));
                   
                  //  strcpy(subReg2,substring(str,28,5));
                   
                    R[getbits(strtol(str,NULL,2),9,5)]/=R[getbits(strtol(str,NULL,2),4,5)];
                   
                   printf("R%d is divided by R%d and stored in R%d\n",getbits(strtol(str,NULL,2),4,5),getbits(strtol(str,NULL,2),9,5),getbits(strtol(str,NULL,2),4,5));
                }
                else if(getbits(strtol(str,NULL,2),12,3) == 0)  //CMP
                {

                   
                  //  strcpy(subReg1,substring(str,23,5));
                   
                   // strcpy(subReg2,substring(str,28,5));

                    if( R[getbits(strtol(str,NULL,2),9,5)]==R[getbits(strtol(str,NULL,2),4,5)])
                    {
                       
                        flagRegister|=2;
                        flagRegister&=2;
                        printf("~Zero flag set\t\t\t(0|1|0)\n");
                    }else if( R[getbits(strtol(str,NULL,2),9,5)]<R[getbits(strtol(str,NULL,2),4,5)])
                    {
                        
                        flagRegister|=1;
                        flagRegister&=1;
                        printf("~Negative flag set\t\t(0|0|1)\n");
                    }else if( R[getbits(strtol(str,NULL,2),9,5)]>R[getbits(strtol(str,NULL,2),4,5)])
                    {
                        
                        flagRegister|=4;
                        flagRegister&=4;
                        printf("~Positive flag set       \t(1|0|0)\n");
                    }
                   
                }
            }
            else if(getbits(strtol(str,NULL,2),31,3) == 1)// 1 opcode 1 address
            {
                    if(str[26]=='0')                       //INC
                {
                  
                   // strcpy(subReg,substring(str,28,5));
              

                 
                    R[getbits(strtol(str,NULL,2),4,5)]++;
                   
                   printf("R%d is incremented\n",getbits(strtol(str,NULL,2),4,5));
                }
                else                                        //DEC
                 {
                   
                   // strcpy(subReg,substring(str,28,5));
                   

                  
                    R[getbits(strtol(str,NULL,2),4,5)]--;
                   
                   printf("R%d is decremented\n",getbits(strtol(str,NULL,2),4,5));
                }
            }
             else if(getbits(strtol(str,NULL,2),31,3) == 2)//1 opcode 1 memory address
            {
                if(getbits(strtol(str,NULL,2),9,3) == 0) //JMP
                {

                      
                        int bytes = 33 * (getbits(strtol(str,NULL,2),6,7));
                       
                        fseek (finp, bytes, SEEK_SET);  // no "+1" here.
                        
                        printf("Jumping to line number: %d \n",getbits(strtol(str,NULL,2),6,7));
                        goto JumpAdd;
                        break;
                }
                else if(getbits(strtol(str,NULL,2),9,3) == 1) //JNE
                {
                    if(checkSetBit(1) || checkSetBit(4))         //SF[0] || SF[2]       //If > or < of the previous comparison
                    {
                    	 int bytes = 33 * getbits(strtol(str,NULL,2),6,7);
                        fseek (finp, bytes, SEEK_SET);  // no "+1" here.
                        char test[34];
                        printf("Jumping to line number: %d \n",getbits(strtol(str,NULL,2),6,7));
                        goto JumpAdd;
                        break;
                    }else                          //if JNE not set then continue scanning the next instruction
                    {

                        continue;
                    }

                }
                 else if(getbits(strtol(str,NULL,2),9,3) == 2) //JEQ
                 {
                   if(checkSetBit(2))         //SF[1]       //If = of the previous comparison
                    {
                        int bytes = 33 * getbits(strtol(str,NULL,2),6,7);
                        fseek (finp, bytes, SEEK_SET);  // no "+1" here.
                        char test[34];
                        printf("Jumping to line number: %d \n",getbits(strtol(str,NULL,2),6,7));
                        goto JumpAdd;
                        break;
                    }else                          //if JEQ not set then continue scanning the next instruction
                    {

                        continue;
                    }

                }
                else if(getbits(strtol(str,NULL,2),9,3) == 3) //JGT
                 {
                    if(checkSetBit(4))   //SF[0]                //If >  of the previous comparison
                    {
                       int bytes = 33 * getbits(strtol(str,NULL,2),6,7);
                        fseek (finp, bytes, SEEK_SET);  // no "+1" here.
                        char test[34];
                        printf("Jumping to line number: %d \n",getbits(strtol(str,NULL,2),6,7));
                        goto JumpAdd;
                        break;
                    }else                          //if JGT not set then continue scanning the next instruction
                    {

                        continue;
                    }

                }
                else if(getbits(strtol(str,NULL,2),9,3) == 5) //JLE
                 {
                 
                   if(checkSetBit(2) || checkSetBit(1)  )   //SF[2] || SF[1]             //If  < of the previous comparison
                    {
                  
                     	int bytes = 33 * getbits(strtol(str,NULL,2),6,7);
                     	fseek (finp, bytes, SEEK_SET);
                      
                        
                      fscanf(finp,"%s",str);
                        printf("Jumping to line number: %d \n",getbits(strtol(str,NULL,2),6,7));
                        goto JumpAdd;
                        break;
                    }else                          //if JLE not set then continue scanning the next instruction
                    {

                        continue;
                    }

                }
                else //JNZ
                {
                    strcpy(subAdd,substring(str,26,7));
                }
            }
            else if(getbits(strtol(str,NULL,2),31,3) == 5)  //IN / OUT
            {
                if(str[26]=='0')
                {
                        printf("\n\nEnter Input:");
                        scanf("%d",&inputNumber);
                        
                      //  strcpy(subReg,substring(str,28,5));
                        R[getbits(strtol(str,NULL,2),4,5)]=inputNumber;

                }
                else
                {
                   // strcpy(subReg,substring(str,28,5));
                        outputNumber=R[getbits(strtol(str,NULL,2),4,5)];
                        printf("\n\nThe Output is: %d\n",outputNumber);
                }

            }
    }

    return 0;
}
