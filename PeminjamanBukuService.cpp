#include <stdio.h>
#include "PeminjamanBukuHeader.h"
#include <cctype>
#include <string.h>
#include <stdlib.h>

void PrintTitle(char *text){
    int textLength, textBorder;
    
	textLength = strlen(text);
	textBorder = textLength + 20;
	
	system("cls");
	for (int i = 0; i < textBorder; i++){
		printf("=");
	}
	printf("\n");
	
	printf("%10s%s%10s\n", "", text, "");
	
	for (int i = 0; i < textBorder; i++){
		printf("=");
	}
	printf("\n\n");
}

int DashBoard(){
	int condition;
	PrintTitle("SELAMAT DATANG DI PERPUSTAKAAN SISTEM HITAM");
	
	printf("1. Cari Buku\n2. Masuk sebagai Admin\n");
	printf("Pilih perintah (1 atau 2): ");
	scanf("%d", &condition);
	
	return condition;
}

int LoginAdmin(){
	int condition;
	
	system("cls");
	
	PrintTitle("SELAMAT DATANG ADMIN!");
	printf("Silahkan pilih opsi login atau register\n");
	printf("1. Login\n2. Register\n\n");
	 ]
	 
	do {
		printf("Pilih opsi: ");
		scanf("%d", &condition);
		if (condition == 1){
			
		} else if(condition == 2){
		Register();
		} else {
			printf("Mohon masukan angka yang benar.\n\n");
		}
	} while (condition != 1 && condition != 2);
}

int Register(char *filename) {
    FILE *file = fopen(filename, "a");
    
    if (!file) {
        printf("File tidak bisa dibuka.\n");
        return;
    }
    
    User newUser;
    
    printf("Masukkan nomor ID: ");
}









