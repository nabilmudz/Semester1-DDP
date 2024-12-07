#include <stdio.h>
#include "PeminjamanBukuHeader.h"
#include <cctype>
#include <string.h>
#include <ctype.h>
#include <cstdlib>   // untuk rand() dan srand()
#include <ctime>  // Untuk time()


void PrintTitle(char *text){
    int textLength, textBorder;
    
	textLength = strlen(text);
	textBorder = textLength + 20;
	
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

void tambahBuku (Buku *b){
	
	printf("Masukkan judul buku: ");
    fgets(b->judul, sizeof(b->judul), stdin);
    b->judul[strcspn(b->judul, "\n")] = '\0'; // Menghapus newline
    
    toUpperStr(b->judul);
    
    printf("Masukkan jenis buku: ");
    fgets(b->jenis, sizeof(b->jenis), stdin);
    b->jenis[strcspn(b->jenis, "\n")] = '\0';
    
    toUpperStr(b->jenis);
    
    if(strcmp(b->jenis, "NOVEL") == 0){
    	strcpy(b->id, "NV");
	}
	else if(strcmp(b->jenis, "FIKSI") == 0){
		strcpy(b->id, "FS");
	}
	else if(strcmp(b->jenis, "KOMIK") == 0){
		strcpy(b->id, "KM");
	}
	else if(strcmp(b->jenis, "BIOGRAFI") == 0){
		strcpy(b->id, "BG");
	}
	else if(strcmp(b->jenis, "AUTOBIOGRAFI") == 0){
		strcpy(b->id, "AB");
	}
	else if(strcmp(b->jenis, "KARYA ILMIAH") == 0){
		strcpy(b->id, "KI");
	}
	else if(strcmp(b->jenis, "NONFIKSI") == 0){
		strcpy(b->id, "NF");
	}
	
    printf("Masukkan penerbit buku: ");
    fgets(b->penerbit, sizeof(b->penerbit), stdin);
    b->penerbit[strcspn(b->penerbit, "\n")] = '\0';
    
    printf("Masukkan dimana buku disimpan (rak): ");
    fgets(b->rak, sizeof(b->rak), stdin);
    b->rak[strcspn(b->rak, "\n")] = '\0';
    
    saveBuku(b);
}


int kNomor(FILE *file) {
    int nomor = 0;      
    int temp = 0;       
    char buffer[300];   

    rewind(file);       

    // Baca setiap baris file
    while (fgets(buffer, sizeof(buffer), file)) {
        // Cek apakah baris ini berisi nomor di kolom pertama
        if (sscanf(buffer, "%d", &temp) == 1) {
            nomor = temp; // Update nomor jika valid
        }
    }
	nomor = nomor + 1;
    return nomor; // Tambahkan 1 untuk nomor baru
}

int dupes(FILE *file, Buku *b) {
    char buffer[300];
    int boo = 0;
    Buku temp;
    long posAwal = ftell(file);

    rewind(file); // Mulai membaca dari awal file

    while (fgets(buffer, sizeof(buffer), file)) {
    	printf("DEBUG: Membaca baris: [%s\n", buffer);

        if (sscanf(buffer, "%d %150[^\t] %45s %45[^\t] %s %2s %d  %d", 
                   &temp.nomor, temp.judul, temp.jenis, temp.penerbit, temp.rak, temp.id, &temp.noId, &temp.jml) == 8) {
			
			toUpperStr(temp.judul);
            toUpperStr(temp.jenis);
            trim(temp.judul);
			
			
            printf("DEBUG: Membandingkan [%s] dengan [%s]\n", temp.judul, b->judul);
            printf("DEBUG: Membandingkan [%s] dengan [%s]\n", temp.jenis, b->jenis);

            if (strcmp(temp.judul, b->judul) == 0 && strcmp(temp.jenis, b->jenis) == 0) {
                temp.jml = temp.jml + 1; // Perbarui jumlah
                boo = 1;
				
				fflush(file);
				return boo;
            }
        }
    }
}


void toUpperStr(char *str) {
	int i;
   while (str[i] != '\0') {
        // Hapus newline atau carriage return
        if (str[i] == '\n' || str[i] == '\r') {
            str[i] = '\0';
            break; // Keluar dari loop setelah newline dihapus
        }
        // Ubah karakter menjadi huruf besar
        str[i] = toupper(str[i]);
        i++;
	}
}

void trim(char *str) {
    str[strcspn(str, "\n")] = '\0';  // Menghapus newline
    int length = strlen(str);
    while (length > 0 && str[length - 1] == ' ') {
        str[length - 1] = '\0';  // Menghapus spasi di akhir
        length--;
    }
}

void saveBuku(Buku *b){
	char buffer[300];
	Buku temp;
    FILE *file = fopen("data_buku.txt", "r+");
    if (file == NULL) {
        // Jika file tidak ada, buat file baru
        file = fopen("data_buku.txt", "w+");
        if (file == NULL) {
            printf("Gagal membuka atau membuat file!\n");
            return;
        }
        fprintf(file, "0\n"); // Inisialisasi file dengan nomor awal
        rewind(file);         // Kembali ke awal file untuk pembacaan berikutnya
    }
	
    if(dupes(file, b) == 0){
    	b->judul[strcspn(b->judul, "\n")] = '\0';
    	b->jenis[strcspn(b->jenis, "\n")] = '\0';
		b->penerbit[strcspn(b->penerbit, "\n")] = '\0';
		b->jml = 1;
		srand(time(0));
		b->noId = rand() % 1000;
	
		// Membaca nomor terakhir
		b->nomor = kNomor(file);

    	// Tambahkan data buku baru di akhir file
    	fseek(file, 0, SEEK_END); // Pindah ke akhir file
    	fprintf(file, "%-5d\t %-25s\t %-10s\t %-15s\t %-5s\t %s%d\t %-5d\n", 
				b->nomor, b->judul, b->jenis, b->penerbit, b->rak, b->id, b->noId, b->jml);
				
    	printf("Data buku berhasil disimpan!\n");
    	fclose(file);
	}
	else{
		printf("Buku udh ada jirr\n");
	}

}

void updateBuku(Buku *b) {
    FILE *file = fopen("data_buku.txt", "r+");
    if (file == NULL) {
        printf("Gagal Membuka file!\n");
        return;
    }

    char buffer[300];
    Buku temp;
    int i;
    long posAwal = ftell(file);
    int found = 0;

    printf("Masukkan id buku yang akan di-update: ");
    fgets(b->id, sizeof(b->id), stdin);
    b->id[strcspn(b->id, "\n")] = '\0';

    printf("Masukkan No. Id buku yang akan di-update: ");
    scanf("%d", &b->noId);

    rewind(file);
    // Baca seluruh data file dan simpan dalam array sementara
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("DEBUG: Membaca baris: [%s]\n", buffer);
        if (sscanf(buffer,"%d %150[^\t] %45s %45[^\t] %s %2s %d %d", 
                   &temp.nomor, temp.judul, temp.jenis, temp.penerbit, temp.rak, temp.id, &temp.noId, &temp.jml) == 8) {

            // Cek jika id dan nomor id sesuai untuk update
            if (strcmp(temp.id, b->id) == 0 && temp.noId == b->noId) {
                found = 1;
                printf("Apa yang ingin diperbaiki? \n");
                printf("1. Judul \n2. Jenis \n3. Penerbit \n4. Rak \n5. Jumlah buku\n ");
                printf("Pilih 1, 2, 3, 4, atau 5: ");
                scanf("%d", &i);
                getchar();  // Untuk membersihkan buffer

                if (i == 1) {
                    printf("Masukkan Judul baru: ");
                    fgets(b->judul, sizeof(b->judul), stdin);
                    b->judul[strcspn(b->judul, "\n")] = '\0';
                    toUpperStr(b->judul);
                    strcpy(temp.judul, b->judul);  // Update judul
                }
                else if (i == 2) {
                    printf("Masukkan Jenis baru: ");
                    fgets(b->jenis, sizeof(b->jenis), stdin);
                    b->jenis[strcspn(b->jenis, "\n")] = '\0';
                    toUpperStr(b->jenis);
                    strcpy(temp.jenis, b->jenis);  // Update jenis
                }
                else if (i == 3) {
                    printf("Masukkan Penerbit baru: ");
                    fgets(b->penerbit, sizeof(b->penerbit), stdin);
                    b->penerbit[strcspn(b->penerbit, "\n")] = '\0';
                    strcpy(temp.penerbit, b->penerbit);  // Update penerbit
                }
                else if (i == 4) {
                    printf("Masukkan Rak baru: ");
                    fgets(b->rak, sizeof(b->rak), stdin);
                    b->rak[strcspn(b->rak, "\n")] = '\0';
                    strcpy(temp.rak, b->rak);  // Update rak
                }
                else if (i == 5) {
                    printf("Masukkan Jumlah buku baru: ");
                    scanf("%d", &b->jml);
                    temp.jml = b->jml;  // Update jumlah
                }

                // Setelah update, kembali ke posisi awal dan tulis ulang data yang sudah diperbaharui
                long posisiBaris = ftell(file) - strlen(buffer);
                fseek(file, posisiBaris, SEEK_SET);
                fprintf(file,"    \t %-25s\t %-10s\t %-15s\t %-5s\t %s%d\t %-5d\n", 
                        temp.judul, temp.jenis, temp.penerbit, temp.rak, temp.id, temp.noId, temp.jml);
                fflush(file);
                printf("Data Berhasil di-Update!\n");
                break;
            }
        }
    }

    if (!found) {
        printf("Buku tidak ditemukan!\n");
    }

    fclose(file);
}


void deleteBuku(Buku *b) {
    FILE *file = fopen("data_buku.txt", "r+");
    if (file == NULL) {
        printf("Gagal membuka file\n");
        return;
    }

    char buffer[300];
    Buku temp;
    char data[100][300];  // Array untuk menyimpan data sementara
    int totalBaris = 0;
    int nomor = 0;  // Untuk mengurutkan nomor kembali

    printf("Masukkan ID buku yang akan dihapus: ");
    fgets(b->id, sizeof(b->id), stdin);
    b->id[strcspn(b->id, "\n")] = '\0';  // Menghapus karakter newline

    printf("Masukkan No. ID buku yang akan dihapus: ");
    scanf("%d", &b->noId);
    getchar();  // Mengonsumsi newline setelah scanf

    int found = 0;  // Flag untuk mengecek apakah ID ditemukan

    rewind(file);
    // Baca seluruh data file dan simpan dalam array sementara
    while (fgets(buffer, sizeof(buffer), file)) {
        if (sscanf(buffer, "%d %150[^\t] %45s %45[^\t] %s %2s %d %d",
                   &temp.nomor, temp.judul, temp.jenis, temp.penerbit, temp.rak, temp.id, &temp.noId, &temp.jml) == 8) {
            // Jika ID dan NoId cocok, jangan masukkan data ke array (hapus baris)
            if (strcmp(temp.id, b->id) == 0 && temp.noId == b->noId) {
                found = 1;  // Menandakan data ditemukan
                continue;  // Lewati baris ini
            }

            // Jika data tidak dihapus, simpan dan perbarui nomor urut
            nomor = nomor + 1;  
            temp.nomor = nomor;  // Perbarui nomor urut
            // Simpan data yang telah diperbarui dalam array
            snprintf(data[totalBaris], sizeof(data[totalBaris]), "%-5d\t %-25s\t %-10s\t %-15s\t %-5s\t %s%d\t %-5d\n",
                     temp.nomor, temp.judul, temp.jenis, temp.penerbit, temp.rak, temp.id, temp.noId, temp.jml);
            totalBaris = totalBaris + 1;
        }
    }

    fclose(file);

    if (!found) {
        printf("ID buku yang dimasukkan tidak ditemukan.\n");
        return;
    }

    // Tulis ulang data yang tersisa ke dalam file
    file = fopen("data_buku.txt", "w");
    if (file == NULL) {
        printf("Gagal membuka file untuk menulis.\n");
        return;
    }

    for (int i = 0; i < totalBaris; i++) {
        fputs(data[i], file);  // Tulis data yang telah diperbarui ke file
    }

    fclose(file);

    printf("Data berhasil dihapus.\n");
    printf("Data berhasil diurutkan kembali.\n");
}


void sort() { 
    FILE *file = fopen("data_buku.txt", "r");
    if (file == NULL) {
        printf("Gagal membuka file untuk membaca.\n");
        return;
    }

    char buffer[300];
    Buku temp;
    int nomor = 0;

    // Simpan data sementara di array
    char data[100][300];
    int totalBaris = 0;

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        if (sscanf(buffer, "%d %150[^\t] %45s %45[^\t] %s %2s %d %d",
                   &temp.nomor, temp.judul, temp.jenis, temp.penerbit, temp.rak, temp.id, &temp.noId, &temp.jml) == 8) {
            nomor++;
            snprintf(data[totalBaris], sizeof(data[totalBaris]), //Menyimpan hasil print ke dalam suatu array, dalam konteks ini ke array data
                     "%-5d\t %-25s\t %-10s\t %-15s\t %-5s\t %s%d\t %-5d\n",
                     nomor, temp.judul, temp.jenis, temp.penerbit, temp.rak, temp.id, temp.noId, temp.jml);
            totalBaris++;
        }
    }
    fclose(file);

    // Tulis ulang file dengan nomor yang diperbarui
    file = fopen("data_buku.txt", "w");
    if (file == NULL) {
        printf("Gagal membuka file untuk menulis.\n");
        return;
    }
    for (int i = 0; i < totalBaris; i++) {
        fputs(data[i], file);
    }
    fclose(file);

    printf("Data berhasil diurutkan kembali.\n");
}

void printIsiFile(Buku *b) {
    FILE *file = fopen("data_buku.txt", "r");
    if (file == NULL) {
        printf("File tidak ditemukan atau tidak dapat dibuka!\n");
        return;
    }

    char buffer[500]; // Buffer untuk membaca setiap baris
    printf("Isi file data_buku.txt:\n");
    printf("----------------------------------------------------------------------------------------------------\n");

    // Baca dan cetak setiap baris
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }

    printf("----------------------------------------------------------------------------------------------------\n");
    fclose(file);
}

