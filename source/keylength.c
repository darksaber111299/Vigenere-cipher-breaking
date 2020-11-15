#include <stdio.h>
#include <string.h>
#include <stdlib.h>

float maximum(float* array);

int main() {
    char ctext[] = "F96DE8C227A259C87EE1DA2AED57C93FE5DA36ED4EC87EF2C63AAE5B9A7EFFD673BE4ACF7BE8923CAB1ECE7AF2DA3DA44FCF7AE29235A24C963FF0DF3CA3599A70E5DA36BF1ECE77F8DC34BE129A6CF4D126BF5B9A7CFEDF3EB850D37CF0C63AA2509A76FF9227A55B9A6FE3D720A850D97AB1DD35ED5FCE6BF0D138A84CC931B1F121B44ECE70F6C032BD56C33FF9D320ED5CDF7AFF9226BE5BDE3FF7DD21ED56CF71F5C036A94D963FF8D473A351CE3FE5DA3CB84DDB71F5C17FED51DC3FE8D732BF4D963FF3C727ED4AC87EF5DB27A451D47EFD9230BF47CA6BFEC12ABE4ADF72E29224A84CDF3FF5D720A459D47AF59232A35A9A7AE7D33FB85FCE7AF5923AA31EDB3FF7D33ABF52C33FF0D673A551D93FFCD33DA35BC831B1F43CBF1EDF67F0DF23A15B963FE5DA36ED68D378F4DC36BF5B9A7AFFD121B44ECE76FEDC73BE5DD27AFCD773BA5FC93FE5DA3CB859D26BB1C63CED5CDF3FE2D730B84CDF3FF7DD21ED5ADF7CF0D636BE1EDB79E5D721ED57CE3FE6D320ED57D469F4DC27A85A963FF3C727ED49DF3FFFDD24ED55D470E69E73AC50DE3FE5DA3ABE1EDF67F4C030A44DDF3FF5D73EA250C96BE3D327A84D963FE5DA32B91ED36BB1D132A31ED87AB1D021A255DF71B1C436BF479A7AF0C13AA14794";
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
        // printf("%ld\t%s\n", strlen(bytestream)-1 , bytestream);

        float frequency[256] = {0};
        for (size_t k=1; k<strlen(bytestream); k+=2) {
            const char cipher_char[3] = {bytestream[k-1], bytestream[k], '\0'};
            int number = (int)strtol(cipher_char, NULL, 16);
            frequency[number]++;
        }
        for (int i=0; i<256; i++)
            frequency[i]/=(strlen(bytestream)/2);
        // printf("N=%d: %.4f\n", N, maximum(frequency));
        float permutation = 0;
        for (int i=0; i<256; i++) {
            permutation += frequency[i] * frequency[i];
        }

        if (permutation > maxPermutation) {
            keylength = N;
            maxPermutation = permutation;
        }
    }
    printf("N=%d: %.4f\n", keylength, maxPermutation);
    return 0;
}

float maximum(float* array) {
    float max =  array[0];
    for(int i=1; i<256; i++)
        if (max < array[i])
            max = array[i];
    return max;
}