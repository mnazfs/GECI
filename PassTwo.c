#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void passTwo(char label[10], char opcode[10], char operand[10], char code[10], char mnemonic[3]) 
{
    FILE *fp1, *fp2, *fp3, *fp4;
    int locctr, address;
    char symbol[10];
    char objcode[10];
    
    fp1 = fopen("Intermediate.txt", "r");
    fp2 = fopen("OpTab.txt", "r");
    fp3 = fopen("SymTab.txt", "r");
    fp4 = fopen("ObjectCode.txt", "w");
    
    fscanf(fp1, "%s\t%s\t%s\t%d", label, opcode, operand, &locctr);
    
    if (strcmp(opcode, "START") == 0) {
        fprintf(fp4, "Address\tObject Code\n");
        fscanf(fp1, "%s\t%s\t%s\t%d", label, opcode, operand, &locctr);
    }

    while (strcmp(opcode, "END") != 0) {
        fscanf(fp2, "%s\t%s", code, mnemonic);

        while (strcmp(code, "END") != 0) {
            if (strcmp(opcode, code) == 0) {
                strcpy(objcode, mnemonic);

                if (strcmp(operand, "**") != 0) {
                    rewind(fp3);
                    fscanf(fp3, "%s\t%d", symbol, &address);
                    while (strcmp(symbol, "END") != 0) {
                        if (strcmp(operand, symbol) == 0) {
                            sprintf(objcode + strlen(objcode), "%04X", address);
                            break;
                        }
                        fscanf(fp3, "%s\t%d", symbol, &address);
                    }
                }
                break;
            }
            fscanf(fp2, "%s\t%s", code, mnemonic);
        }

        if (strcmp(opcode, "BYTE") == 0) {
            if (operand[0] == 'C') {
                int i;
                for (i = 2; i < strlen(operand) - 1; i++) {
                    sprintf(objcode + strlen(objcode), "%X", operand[i]);
                }
            }
            else if (operand[0] == 'X') {
                strncpy(objcode, operand + 2, strlen(operand) - 3);
            }
        }
        else if (strcmp(opcode, "WORD") == 0) {
            sprintf(objcode, "%06X", atoi(operand));
        }

        fprintf(fp4, "%04X\t%s\n", locctr, objcode);
        
        strcpy(objcode, "");
        fscanf(fp1, "%s\t%s\t%s\t%d", label, opcode, operand, &locctr);
    }

    fprintf(fp4, "%s\t%s\t%s\n", label, opcode, operand);

    fclose(fp4);
    fclose(fp3);
    fclose(fp2);
    fclose(fp1);
}

void main()
{
    char label[10], opcode[10], operand[10];
    char code[10], mnemonic[3];
    passTwo(label, opcode, operand, code, mnemonic);
	printf("Object Code is written into ObjectCode.txt\n");
}

