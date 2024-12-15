#include <iostream>
#include "PeminjamanBukuHeader.h"
#include <ctime>
#include<unistd.h>

int main() {
	int page;
	
    while (1) {
        page = Dashboard();
        if (page == 1) {
            FILE *file = fopen("data_buku.txt", "r");
            if (file) {
                Buku b;
                printIsiFile(&b);
                fclose(file);
            } else {
                printf("File not found!\n");
            }
            printf("\nTekan Enter untuk kembali ke Dashboard... ");
            getchar();
            getchar();
        } else if (page == 2) {
            Admin();
        } else {
            printf("Mohon masukan angka yang benar. (1 atau 2)\n");
        }
    }
    return 0;
}
