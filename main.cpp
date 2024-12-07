#include <iostream>
#include <stdio.h>
#include "PeminjamanBukuHeader.h"

main(){
	
	FILE *file = fopen("data_buku.txt", "r");
	Buku b;
	int p;
	char pil;
	pil = 'y';
	PrintTitle("SELAMAT DATANG DI PERPUSTAKAAN SISTEM HITAM");
		
		while (pil == 'y' || pil == 'Y'){
		printf("Apa yang ingin atmin lakukan: \n");
		printf("1. Tambah Buku \n2. Update Buku \n3. Hapus Buku \n4. Lihat list Buku\n");
		printf("Pilih 1, 2, 3, atau 4: ");
		scanf("%d", &p);
		while ((getchar()) != '\n'); //Bersihkan input sisa yaitu newline
		printf("\n");
		if (p == 1) {
			tambahBuku(&b);
		}
		else if (p == 2){
			updateBuku(&b);
		}
		else if (p == 3){
			deleteBuku(&b);
			
		}
		else if (p == 4){
			printIsiFile(&b);
		}
	printf("Lakukan lagi? (y untuk iya / t untuk tidak): ");
	scanf(" %c", &pil);
	printf("\n");
		
	}
	
	
}
