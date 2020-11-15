#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_KEY_LENGTH 13 // Program can decrypt up to key of 13 size

int findKeyLength(const char* ctext);
void findKey(const char* ctext, int keylength, char* key);

int main() {
    // Variable assignment
    unsigned char ch;  
    FILE *fpIn, *fpOut;
    char rbyte[3] = {0};
    int filepos=0;
    unsigned char key[MAX_KEY_LENGTH] = {0};
    char ctext[1000] = {0};

    // Main decrypting program
    printf("The Vigenere Cipher Breaking:\n\n");
    fpIn = fopen("ctext.txt", "r");
    fscanf(fpIn, "%s", ctext);
    fclose(fpIn);
    printf("Cipher text:\n%s\n\n", ctext);
    int finalKeyLength = findKeyLength(ctext);
    printf("Keylength: %d\n", finalKeyLength);
    findKey(ctext, finalKeyLength, key);
    printf("The final key is: 0x");
    for (int i=0; i<strlen(key); i++) {
        printf("%02X", key[i]);
    }
    printf("\n\nPlain text:\n");

    // Output
    fpIn = fopen("ctext.txt", "r");  
    fpOut = fopen("ptext.txt", "w");
    filepos=0;
    while (fscanf(fpIn, "%c", &ch) != EOF) {
        rbyte[filepos % 2] = ch;  
        if (filepos % 2 == 1) {
            int number = (int)strtol(rbyte, NULL, 16);
            printf("%c", (unsigned char) number ^ key[((filepos-1)/2) % finalKeyLength]);
            fprintf(fpOut, "%c", (unsigned char) number ^ key[((filepos-1)/2) % finalKeyLength]);
            memset(rbyte, 0, sizeof(rbyte)); 
        }
        filepos++; 
    }   
    fclose(fpIn);
    fclose(fpOut);
    printf("\n");
    return 0;
} 

// Simple find maximum of an array
float maximum(float* array) {
    float max =  array[0];
    for(int i=1; i<256; i++)
        if (max < array[i])
            max = array[i];
    return max;
}

// Find the key length
int findKeyLength(const char* ctext) {
    int keylength;
    float maxPermutation = 0;
    for (int N=1; N <= 13; N++) {
        char bytestream[941];
        size_t j = 1;

        for (size_t i=1; i<strlen(ctext); i+=N*2) {
            bytestream[j] = ctext[i];
            bytestream[j-1] = ctext[i-1];
            j+=2;
        }
        bytestream[j] = '\0';

        float frequency[256] = {0};
        for (size_t k=1; k<strlen(bytestream); k+=2) {
            const char cipher_char[3] = {bytestream[k-1], bytestream[k], '\0'};
            int number = (int)strtol(cipher_char, NULL, 16);
            frequency[number]++;
        }
        for (int i=0; i<256; i++)
            frequency[i]/=(strlen(bytestream)/2);
        float permutation = 0;
        for (int i=0; i<256; i++) {
            permutation += frequency[i] * frequency[i];
        }

        if (permutation > maxPermutation) {
            keylength = N;
            maxPermutation = permutation;
        }
    }
    return keylength;
}

// Find the key
void findKey(const char* ctext, int keylength, char* key) {
    for (int keypos=0; keypos<7; keypos++) {
        char bytestream[140];
        size_t j = 1;
        for (size_t i=1+keypos*2; i<strlen(ctext); i+=keylength*2) {
            bytestream[j] = ctext[i];
            bytestream[j-1] = ctext[i-1];
            j+=2;
        }
        bytestream[j] = '\0';

        float frequencyTable[256][26] = {0};
        for (int keybyte=0; keybyte<=255; keybyte++) {
            float frequency[96] = {0};
            for (size_t k=1; k<strlen(bytestream); k+=2) {
                const char cipher_char[3] = {bytestream[k-1], bytestream[k], '\0'};
                int number = (int)strtol(cipher_char, NULL, 16);
                number = (unsigned char) number ^ (unsigned char) keybyte;
                if (32 <= number && number <= 127)
                    frequency[number-32]++;
            }
            for (int i=0; i<96; i++) {
                frequency[i]/=(strlen(bytestream)/2);
                if (65 <= i && i <=90) {
                    frequencyTable[keybyte][i-65] = frequency[i];
                }
            }
        }

        float wikiTable[26] = {8.2, 1.5, 2.8, 4.3, 13, 2.2, 2, 6.1, 7, 0.15, 0.77, 4, 2.4, 6.7, 7.5, 1.9, 0.095, 6, 6.3, 9.1, 2.8, 0.98, 2.4, 0.15, 2, 0.074};
        float result[256] = {0};
        float maxResult = 0;
        int finalKey;
        for (int i=0; i<256; i++) {
            for (int j=0; j<26; j++) {
                result[i] += wikiTable[j]/100 * frequencyTable[i][j];
            }
            if (result[i] > maxResult) {
                maxResult = result[i];
                finalKey = i;
            }
        }
        key[keypos] = (unsigned char) finalKey;
    }
    return;
}