#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char opcode[10], operand[10], label[10], hexcode[10], line[50];
int locctr, start, size;
FILE *fp1, *fp2, *fp3, *fp4;

struct SYMTAB {
    char label[10];
    int addr;
} ST[30];

struct OPTAB {
    char opcode[10], hexcode[10];
} OT[30];

void read_SYMTAB() {
    int i = 0;
    while (fscanf(fp2, "%s %d", ST[i].label, &ST[i].addr) != EOF) {
        i++;
    }
}

void read_OPTAB() {
    int i = 0;
    while (fscanf(fp1, "%s %s", OT[i].opcode, OT[i].hexcode) != EOF) {
        i++;
    }
}

int get_address(char *label) {
    for (int i = 0; i < 30; i++) {
        if (strcmp(ST[i].label, label) == 0) {
            return ST[i].addr;
        }
    }
    return -1; 
}

int main() {
    fp1 = fopen("OpTab.txt", "r");
    fp2 = fopen("SymTab.txt", "r");
    fp3 = fopen("Intermediate.txt", "r");
    fp4 = fopen("ObjectCode.txt", "w");

    if (!fp1 || !fp2 || !fp3 || !fp4) {
        printf("Error opening files.\n");
        return 1;
    }

    read_OPTAB();
    read_SYMTAB();

    
    fscanf(fp3, "%s %s %x", label, opcode, &start);
    fprintf(fp4, "H %s %06x %06x\n", label, start, size);

    while (fgets(line, sizeof(line), fp3)) {
        sscanf(line, "%x %s %s %s", &locctr, label, opcode, operand);
        if (strcmp(opcode, "END") == 0) {
            fprintf(fp4, "E %06x\n", start);
            break;
        }

        int opcode_found = 0;
        for (int i = 0; i < 30; i++) {
            if (strcmp(opcode, OT[i].opcode) == 0) {
                fprintf(fp4, "T %06x %s %s %s\n", locctr, OT[i].hexcode, operand, operand);
                opcode_found = 1;
                break;
            }
        }

        if (!opcode_found) {
           
            if (strcmp(opcode, "WORD") == 0) {
                fprintf(fp4, "T %06x %s %06x\n", locctr, "00", atoi(operand));
            } else if (strcmp(opcode, "BYTE") == 0) {
                if (operand[0] == 'C' || operand[0] == 'c') {
                    fprintf(fp4, "T %06x %s %s\n", locctr, "C", operand + 3); 
                } else {
                    fprintf(fp4, "T %06x %s %s\n", locctr, "H", operand + 3); 
                }
            }
        }
    }

    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);
	printf("Object program is written into ObjectCode.txt\n");

    return 0;
}

