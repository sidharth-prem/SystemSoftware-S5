#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void pass(char label[10], char opcode[10], char operand[10], char code[10], char mnemonics[3])
{
	int locctr, start, length, opd;
	FILE *fp1, *fp2, *fp3, *fp4;
	
	fp1 = fopen("input.txt", "r");
    	fp2 = fopen("opcode.txt", "r");
    	fp3 = fopen("symtab.txt", "w");
    	fp4 = fopen("intermediate.txt", "w");
    	
    	fscanf(fp1, "%s\t%s\t%x", label, opcode, &opd);
    	if(strcmp(opcode, "START") == 0)
    	{
         start = opd;
         locctr = start;
      
         fprintf(fp4, "\t%s\t%s\t%x\n", label, opcode, opd);
         fscanf(fp1, "%s\t%s\t%s", label, opcode, operand);
    	}
    	else
    	{	
       locctr = 0;
    	}
    	while(strcmp(opcode, "END") != 0)
    	{	
    	fprintf(fp4, "%x\t%s\t%s\t%s\n", locctr, label, opcode, operand);	
           if (strcmp(label, "**") != 0) 
                {
                fprintf(fp3, "%s\t%x\n", label, locctr);
        	}
        	fscanf(fp2, "%s\t%s", code, mnemonics);
        	while(strcmp(code, "END") != 0)
        	{
        	if(strcmp(opcode, code) == 0)
        	  {
        	    locctr+=3;
        	    break;
                  }
        	fscanf(fp2, "%s\t%s", code, mnemonics);
        	}
                if(strcmp(opcode, "WORD") == 0)
        	{	
        	  locctr+=3;
        	}
        	else if(strcmp(opcode, "RESW") == 0)
        	{
        	  locctr+=(3*atoi(operand));
        	}
        	else if(strcmp(opcode, "RESB") == 0)
        	{
        	  locctr+=(atoi(operand));
        	}
        	else if(strcmp(opcode, "BYTE") == 0)
        	{
        	  int count = strlen(operand);
        	  locctr+=(count-3);
        	}
        	fscanf(fp1, "%s\t%s\t%s", label, opcode, operand);
        }
        fprintf(fp4, "%x\t%s\t%s\t%s\n",locctr, label, opcode, operand);
        
        fclose(fp1);
        fclose(fp2);
        fclose(fp3);
        fclose(fp4);
        
    	char str;
    	FILE *fp5, *fp6, *fp7;   

    	printf("\nThe contents of Input Table :\n\n");
    	fp5 = fopen("input.txt", "r");
    	
    	str = fgetc(fp5);
    	
    	while (str != EOF) 
    	{
         printf("%c", str);
         str = fgetc(fp5);
    	}
    	fclose(fp5);

    	printf("\n\nThe contents of Output Table :\n\n");
    	fp6 = fopen("intermediate.txt", "r");
    	
    	str = fgetc(fp6);
    	while (str != EOF) 
    	{
        	printf("%c", str);
        	str = fgetc(fp6);
    	}
    	fclose(fp6);
2

    	printf("\n\nThe contents of Symbol Table :\n\n");
    	fp7 = fopen("symtab.txt", "r");
    	
    	str = fgetc(fp7);
    	while (str != EOF) 
    	{
        	printf("%c", str);
        	str = fgetc(fp7);
    	}
    	fclose(fp7);
    
    	length = locctr - start;
    	printf("\nThe length of the code : %d\n", length);
}
void main()
{
   char label[10], opcode[10], operand[10], code[10], mnemonics[3];
   pass(label, opcode, operand, code, mnemonics);
}

/*
INPUT.TXT
** START 2000
** LDA FIVE
2
** STA ALPHA
** LDCH CHARZ
** STCH C1
ALPHA RESW 1
FIVE WORD 5
CHARZ BYTE C'Z'
C1 RESB 1
** END **

OUTPUT.TXT
**	2000
**	2003
**	2006
**	2009
ALPHA	200c
FIVE	200f
CHARZ	2012
C1	2015

INTERMEDIATE.TXT
	**	START	2000
2000	**	LDA	FIVE
2003	**	STA	ALPHA
2006	**	LDCH	CHARZ
2009	**	STCH	C1
200c	ALPHA	RESW	1
200f	FIVE	WORD	5
2012	CHARZ	BYTE	C'Z'
2013	C1	RESB	1
2014	**	END	**

OPCODE.TXT
LDA 00
STA 0C
LDCH 50
STCH 54
END *

SYMTAB.TXT
ALPHA	200c
FIVE	200f
CHARZ	2012
C1	2013
*/

