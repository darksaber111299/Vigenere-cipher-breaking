#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define KEY_LENGTH 7

int main() {
    unsigned char ch;
    FILE *fpIn, *fpOut;  
    int i;
    unsigned char key[KEY_LENGTH] = {0xBA, 0x1F, 0x91, 0xB2, 0x53, 0xCD, 0x3E};

    fpIn = fopen("ctext.txt", "r");  
    fpOut = fopen("ptext.txt", "w");
    i=0;
    char rbyte[3] = {0};
    while (fscanf(fpIn, "%c", &ch) != EOF) {
        rbyte[i % 2] = ch;  
        if (i % 2 == 1) {
            int number = (int)strtol(rbyte, NULL, 16);
            fprintf(fpOut, "%02X", (unsigned char) number ^ key[((i-1)/2) % KEY_LENGTH]);
            memset(rbyte, 0, sizeof(rbyte)); 
        }
        i++; 
    }   

    fclose(fpIn);  
    fclose(fpOut);  
    return 0;
} 