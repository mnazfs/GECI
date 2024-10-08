#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void passOne(char label[10],char opcode[10],char operand[10],char code[10],char mnemonic[3]) 
{
    int locctr, start, length;
    FILE *fp1,*fp2,*fp3,*fp4;
    fp1 = fopen("InputProgram.txt","r");
    fp2 = fopen("OpTab.txt","r");
    fp3 = fopen("SymTab.txt","w");
    fp4 = fopen("Intermediate.txt","w");
    fscanf(fp1, "%s\t%s\t%s",label,opcode,operand);
    if (strcmp(opcode,"START")==0) { 
        start=atoi(operand);
        locctr=start;
        fprintf(fp4,"\t%s\t%s\t%s\n",label,opcode,operand);
        fscanf(fp1, "%s\t%s\t%s",label,opcode,operand);
    } 
    else {
        locctr=0;
    }
    while (strcmp(opcode,"END")!=0) {
        fprintf(fp4, "%d\t%s\t%s\t%s\n",locctr,label,opcode,operand);
        if (strcmp(label,"**")!=0) {
            fprintf(fp3, "%s\t%d\n",label,locctr);
        }
        fscanf(fp2,"%s\t%s",code,mnemonic);
         while (strcmp(code,"END")!=0) {
            if (strcmp(opcode,code)==0) { 
                locctr+=3;
                break;
            }
            fscanf(fp2,"%s\t%s",code,mnemonic);
        }
        if (strcmp(opcode,"WORD")==0) {
            locctr+=3;
        }
        else if (strcmp(opcode,"RESW")==0) {
            locctr+=(3*(atoi(operand)));
        }
        else if (strcmp(opcode,"BYTE")==0) {
            ++locctr;
        }
        else if (strcmp(opcode,"RESB")==0) {
            locctr+=atoi(operand);
        }
        fscanf(fp1,"%s\t%s\t%s",label,opcode,operand);
    }
    fprintf(fp4,"%d\t%s\t%s\t%s\n",locctr,label,opcode,operand);
    fclose(fp4);
    fclose(fp3);
    fclose(fp2);
    fclose(fp1);
    length=locctr-start;
    printf("\nThe length of the code : %d\n",length);
}

void main()
{
    char label[10],opcode[10],operand[10];
    char code[10],mnemonic[3];
    passOne(label,opcode,operand,code,mnemonic);
}
