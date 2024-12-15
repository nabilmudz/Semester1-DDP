#include <stdio.h>
#include "PeminjamanBukuHeader.h"
#include <cctype>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <cstdlib>   // untuk rand() dan srand()
#include <ctime>  // Untuk time()
#include <errno.h>

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

int Dashboard(){
	int action;
	PrintTitle("SELAMAT DATANG DI PERPUSTAKAAN SISTEM HITAM");
	
	printf("1. Cari Buku\n2. Masuk sebagai Admin\n");
	printf("Pilih perintah (1 atau 2): ");
	scanf("%d", &action);
	
	return action;
}

int DashboardAdmin(bool is_admin){
	int action;
	if(is_admin){
		PrintTitle("Selamat datang admin!");
		printf("Pagi! Apa yang ingin anda lakukan hari ini.\n");
		printf("1. Daftar Buku\n2. Daftar Peminjaman\n3. Logout\n");
		printf("Pilih perintah (1 atau 2): ");
		scanf("%d", &action);
		
		if (action == 1){
			DaftarBuku(is_admin);
		} else if (action == 2) {
			DaftarPeminjaman(is_admin);
		} else if (action == 3){
			printf("Berhasil Logout!");
			sleep(1);
			return 0;	
		} else {
	        printf("Mohon masukan angka yang benar.\n");
	        return DashboardAdmin(is_admin);
		}
	} else {
		printf("Anda tidak memiliki akses!");
		return 0;
	}
	
}


void Register() {
    const char *filename = "data_admin.txt";
    char action;
    int last_id = GetLastID(filename);
    const char *code;
    char inputCode[50];

    code = "PerpustakaanHitam123";

    PrintTitle("Register");
    printf("Masukan Code Perpustakaan: ");
    scanf("%s", inputCode);

    if (strcmp(code, inputCode) == 0) {
        FILE *file = fopen(filename, "a");
        User adm;
        adm.no = last_id + 1;

        if (!file) {
            file = fopen("data_admin.txt", "w");
            printf("File data admin berhasil dibuat!\n");
        }

        PrintTitle("Register");

        printf("Masukkan nama: ");
        scanf(" %[^\n]", adm.nama);	

        printf("Masukkan email: ");
        scanf(" %[^\n]", adm.email);

        if (EmailExists(filename, adm.email)) {
            printf("Email sudah digunakan! Mohon gunakan email lain.\n");
            sleep(2);
            fclose(file);
            Admin();
            return;
        }

        printf("Masukkan password: ");
        scanf(" %[^\n]", adm.password);

        adm.is_admin = 1;

        fprintf(file, "%d;%s;%s;%s;%d\n", adm.no, adm.nama, adm.email, adm.password, adm.is_admin);
        fclose(file);

        printf("Data berhasil disimpan dengan ID %d.\n", adm.no);
        sleep(2);

        Admin();
    } else {
        printf("Kode perpustakaan salah, silahkan hubungi super admin!\n");
        sleep(2);
        Admin();
    }
}

int EmailExists(const char *filename, const char *email) {
    FILE *file = fopen(filename, "r");
    char line[256];
    char *token;
    char stored_email[100];
    
    if (!file) {
        return 0;
    }

    while (fgets(line, sizeof(line), file)) {

        strtok(line, ";"); 
        strtok(NULL, ";"); 
        token = strtok(NULL, ";");

        if (token) {
            strncpy(stored_email, token, sizeof(stored_email));
            stored_email[strcspn(stored_email, "\n")] = 0;

            if (strcmp(stored_email, email) == 0) {
                fclose(file);
                return 1;
            }
        }
    }

    fclose(file);
    return 0;
}

int Admin(){
	int condition;
	bool is_admin;
	
	is_admin = false;
	
	PrintTitle("SELAMAT DATANG ADMIN");
	printf("Silahkan pilih opsi login atau register\n");
	printf("1. Login\n2. Register\n3. Kembali\n\n");
	
	do {
		printf("Pilih opsi: ");
		scanf("%d", &condition);
		if (condition == 1){
			is_admin = Login();
			return is_admin;
		} else if(condition == 2){
			Register();
		} else if (condition == 3){
			return 0;
		} else {
			printf("Mohon masukan angka yang benar.\n\n");
		}
	} while (condition != 3);
	return is_admin;
}

int Login() {
    char email[50], password[50];
    User adm;
    bool email_found = false;
    char buffer[200];
    
    PrintTitle("Login");

    FILE *file = fopen("data_admin.txt", "r");
    if (!file) {
        printf("File data admin tidak ditemukan.\n");
        return 0;
    }


    printf("Masukkan Email: ");
    scanf(" %[^\n]", email);

    while (fgets(buffer, sizeof(buffer), file)) {
        sscanf(buffer, "%d;%49[^;];%49[^;];%49[^;];%d", 
               &adm.no, adm.nama, adm.email, adm.password, (int*)&adm.is_admin);
        if (strcmp(adm.email, email) == 0) {
            email_found = true;
            break;
        }
    }

    fclose(file);

    if (!email_found) {
        printf("Email tidak ditemukan. Silakan coba lagi.\n\n");
        sleep(2);
        return Login();
    }

    printf("Masukkan Password: ");
    scanf(" %[^\n]", password);

    if (strcmp(adm.password, password) == 0) {
        printf("\nLogin berhasil! Selamat datang, %s.\n", adm.nama);
        sleep(2);
        return DashboardAdmin(adm.is_admin);
    } else {
        printf("\nPassword salah. Silakan coba lagi.\n");
        sleep(2);
        return Login();
    }
}

int DaftarBuku(bool is_admin){
	FILE *file = fopen("data_buku.txt", "r");
	Buku b;
	int p;
	char action;
	
	if(is_admin){
		while (1) {
	        PrintTitle("Daftar Buku");
	        printf("Silahkan pilih opsi buku.\n");
	        printf("1. Tambah Buku \n2. Update Buku \n3. Hapus Buku \n4. Lihat list Buku\n5. Kembali ke Dashboard\n");
	        printf("Pilih 1, 2, 3, 4, atau 5: ");
	        scanf("%d", &p);
	        while ((getchar()) != '\n');
	        printf("\n");
	     
	        if (p == 1) {
	            tambahBuku(&b);
	        } else if (p == 2) {
	            updateBuku(&b);
	        } else if (p == 3) {
	            deleteBuku(&b);
	        } else if (p == 4) {
	            printIsiFile(&b);
	        } else if (p == 5) {
	            printf("Kembali ke Dashboard Admin.\n");
	            sleep(2);
	            return DashboardAdmin(is_admin);
	        } else {
	            printf("Pilihan tidak valid. Silakan coba lagi.\n");
	        }
	     
	        printf("\nApakah Anda ingin kembali ke menu Daftar Buku? (y/n): ");
	        scanf(" %c", &action);
	        while ((getchar()) != '\n'); 
	     
	        if (tolower(action) != 'y') {
	            printf("Kembali ke Dashboard.\n");
	            break;
	        }
	    }
	    return 0;
    
	} else {
		printf("Anda tidak memiliki akses!");
		return 0;
	}
	
}

int DaftarPeminjaman(bool is_admin){
	FILE *file = fopen("data_pinjaman.txt", "r");
	Peminjaman p;
	int pil;
	char action;
	
	if(is_admin){
		while (1) {
	        PrintTitle("Daftar Pinjaman");
	        printf("Silahkan pilih opsi aksi.\n");
	        printf("1. Tambah Pinjaman \n2. Update Pinjaman \n3. Hapus Pinjaman \n4. Lihat list Pinjaman\n5. Kembali ke Dashboard\n");
	        printf("Pilih 1, 2, 3, 4, atau 5: ");
	        scanf("%d", &pil);
	        while ((getchar()) != '\n');
	        printf("\n");
	     
	        if (pil == 1) {
    			CreatePeminjaman(&p);
			} else if (pil == 2) {
			    updatePeminjaman(&p);
			} else if (pil== 3) {
			    deletePeminjaman();
			} else if (pil == 4) {
			    ListPeminjaman();
			} else if (pil == 5) {
			    printf("Kembali ke Dashboard Admin.\n");
			    sleep(2);
			    return DashboardAdmin(is_admin);
			} else {
	            printf("Pilihan tidak valid. Silakan coba lagi.\n");
	        }
	     
	        printf("\nApakah Anda ingin kembali ke menu Daftar Pinjaman? (y/n): ");
	        scanf(" %c", &action);
	        while ((getchar()) != '\n');
	     
	        if (tolower(action) != 'y') {
	            printf("Kembali ke Dashboard.\n");
	            break;
	        }
	    }
	    return 0;
    
	} else {
		printf("Anda tidak memiliki akses!");
		return 0;
	}
	
}

int GetLastID(const char *filename) {
    FILE *file = fopen(filename, "r");
    int last_id = 0;
    char buffer[200];
    
    if (!file) {
        return 0;
    }

    while (fgets(buffer, sizeof(buffer), file)) {
        int id;
        sscanf(buffer, "%d;", &id);
        last_id = id;
    }

    fclose(file);
    return last_id;
}

void CreatePeminjaman(Peminjaman *p) {
    const char *filename = "data_pinjaman.txt";
    FILE *file;
    int last_id;

    last_id = GetLastID(filename);
    p->nomor = last_id + 1;
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);

    file = fopen(filename, "a");
    if (!file) {
        file = fopen(filename, "w");
        if (!file) {
            printf("Error saat membuat file %s!\n", filename);
            return;
        }
        printf("File %s berhasil dibuat!\n", filename);
    }

    PrintTitle("Tambah Pinjaman");

    printf("Masukkan nama peminjam: ");
    scanf(" %[^\n]", p->nama);

    printf("Masukkan email peminjam: ");
    scanf(" %[^\n]", p->email);

    p->peminjaman.day = tm_info->tm_mday;
    p->peminjaman.month = tm_info->tm_mon + 1;
    p->peminjaman.year = tm_info->tm_year + 1900;

    p->pengembalian.day = 0;
    p->pengembalian.month = 0;
    p->pengembalian.year = 0;
    p->denda = 0;

    do {
        for (int i = 0; i < 3 && p->nama[i] != '\0'; i++) {
            p->id[i] = tolower(p->nama[i]);
        }
        p->id[3] = '\0';

        int random_number = GenerateRandomNumber();
        snprintf(p->id + 3, sizeof(p->id) - 3, "%03d", random_number);
    } while (!IsUniqueID(filename, p->id));

    fprintf(file, "%d;%s;%s;%s;%02d-%02d-%04d;%02d-%02d-%04d;%d\n",
            p->nomor,
            p->id,  
            p->nama,
            p->email,
            p->peminjaman.day, p->peminjaman.month, p->peminjaman.year,
            p->pengembalian.day, p->pengembalian.month, p->pengembalian.year,
            p->denda);

    fclose(file);

    printf("Data pinjaman berhasil disimpan dengan ID %d.\n", p->nomor);
    printf("ID Pinjaman: %s\n", p->id);
    sleep(2); 
}
int GenerateRandomNumber() {
    unsigned int seed;
    int random_number;

    seed = (unsigned int)time(NULL) + rand();
    srand(seed);

    random_number = rand() % 1000;

    return random_number;
}

int IsUniqueID(const char *filename, const char *id) {
    FILE *file = fopen(filename, "r");
    char line[256];
    
    if (!file) {
        return 1;
    }

    while (fgets(line, sizeof(line), file)) {
        char stored_id[10];
        sscanf(line, "%*d;%9[^;]", stored_id);
        if (strcmp(stored_id, id) == 0) {
            fclose(file);
            printf("ID sudah ada! Silahkan coba ulangi!");
            sleep(2);
            return 0; 
        }
    }

    fclose(file);
    return 1;
}

int selisihHari(Date d1, Date d2) {
    int days1, days2;

	days1 = d1.year * 365 + d1.month * 30 + d1.day;
	days2 = d2.year * 365 + d2.month * 30 + d2.day;
    return abs(days2 - days1);
}

void updatePeminjaman(Peminjaman *p) {
    PrintTitle("Update Peminjaman");
    FILE *file = fopen("data_pinjaman.txt", "r");
    Peminjaman temp;
    int day, month, year, found, total_lines;
    char buffer[200];
    char data[1000][200];
    
    total_lines = 0;
	found = 0;
    if (file == NULL) {
        printf("Gagal Membuka file!\n");
        return;
    }

	ListPeminjaman();
    printf("Masukkan ID peminjaman yang akan di-update: ");
    fgets(p->id, sizeof(p->id), stdin);
    p->id[strcspn(p->id, "\n")] = '\0';

    while (fgets(buffer, sizeof(buffer), file)) {
        strcpy(data[total_lines], buffer);
        if (sscanf(buffer, "%d;%[^;];%[^;];%[^;];%d-%d-%d;%d-%d-%d",
                   &temp.nomor, temp.id, temp.nama, temp.email,
                   &temp.peminjaman.day, &temp.peminjaman.month, &temp.peminjaman.year,
                   &temp.pengembalian.day, &temp.pengembalian.month, &temp.pengembalian.year) == 10) {

            if (strcmp(temp.id, p->id) == 0) {
                found = 1;

                do {
                    printf("Masukkan Tanggal Pengembalian (DD-MM-YYYY): ");
                    if (scanf("%d-%d-%d", &day, &month, &year) != 3 || day < 1 || day > 31 || month < 1 || month > 12) {
                        printf("Input tanggal tidak valid. Silakan masukkan kembali.\n");
                        scanf("%*[^\n]");
                    }
                } while (day < 1 || day > 31 || month < 1 || month > 12);

                temp.pengembalian.day = day;
                temp.pengembalian.month = month;
                temp.pengembalian.year = year;
                
                int diff = selisihHari(temp.peminjaman, temp.pengembalian);
                temp.denda = (diff > 7) ? 5000 * (diff / 7) : 0;

                sprintf(data[total_lines], "%d;%s;%s;%s;%02d-%02d-%04d;%02d-%02d-%04d;%d\n",
                        temp.nomor, temp.id, temp.nama, temp.email,
                        temp.peminjaman.day, temp.peminjaman.month, temp.peminjaman.year,
                        temp.pengembalian.day, temp.pengembalian.month, temp.pengembalian.year,
                        temp.denda);

                printf("Data peminjaman berhasil diperbarui.\n");
            }
        }
        total_lines++;
    }

    fclose(file);

    if (!found) {
        printf("ID peminjaman tidak ditemukan.\n");
        return;
    }

    file = fopen("data_pinjaman.txt", "w");
    if (file == NULL) {
        printf("Gagal membuka file untuk menulis ulang data.\n");
        return;
    }

    for (int i = 0; i < total_lines; i++) {
        fputs(data[i], file);
    }

    fclose(file);
}

void deletePeminjaman() {
    PrintTitle("Delete Peminjaman");
    FILE *file = fopen("data_pinjaman.txt", "r");
    char buffer[200];
    char data[1000][200];
    int total_lines, found;
    char id_to_delete[50];
    Peminjaman temp;

    if (file == NULL) {
        printf("Gagal membuka file!\n");
        return;
    }
	total_lines = 0;
	found = 0;

	ListPeminjaman();
    printf("Masukkan ID peminjaman yang akan dihapus: ");
    fgets(id_to_delete, sizeof(id_to_delete), stdin);
    id_to_delete[strcspn(id_to_delete, "\n")] = '\0';

    while (fgets(buffer, sizeof(buffer), file)) {
        if (sscanf(buffer, "%d;%[^;];%[^;];%[^;];%d-%d-%d;%d-%d-%d",
                   &temp.nomor, temp.id, temp.nama, temp.email,
                   &temp.peminjaman.day, &temp.peminjaman.month, &temp.peminjaman.year,
                   &temp.pengembalian.day, &temp.pengembalian.month, &temp.pengembalian.year) == 10) {

            if (strcmp(temp.id, id_to_delete) == 0) {
                found = 1;
                printf("Data dengan ID '%s' berhasil dihapus.\n", id_to_delete);
                continue; 
            }
        }
        strcpy(data[total_lines], buffer);
        total_lines++;
    }

    fclose(file);

    if (!found) {
        printf("ID peminjaman tidak ditemukan.\n");
        return;
    }

    file = fopen("data_pinjaman.txt", "w");
    if (file == NULL) {
        printf("Gagal membuka file untuk menulis ulang data.\n");
        return;
    }

    for (int i = 0; i < total_lines; i++) {
        fputs(data[i], file);
    }

    fclose(file);
}

void ListPeminjaman() {
    PrintTitle("List Peminjaman");
    FILE *file = fopen("data_pinjaman.txt", "r");
    int nomor, denda;
    char id[12], nama[50], email[50], buffer[500];
    Date peminjaman, pengembalian;
    
    if (file == NULL) {
        printf("File tidak ditemukan atau tidak dapat dibuka!\n");
        return;
    }

    printf("%-5s | %-12s | %-20s | %-25s | %-15s | %-15s | %-8s\n", 
           "No", "ID", "Nama", "Email", "Tanggal Pinjam", "Tanggal Kembali", "Denda");
    printf("------------------------------------------------------------------------------------------------------------\n");

    while (fgets(buffer, sizeof(buffer), file)) {
        int ret = sscanf(buffer, "%d;%11[^;];%49[^;];%49[^;];%d-%d-%d;%d-%d-%d;%d",
                          &nomor, id, nama, email, 
                          &peminjaman.day, &peminjaman.month, &peminjaman.year,
                          &pengembalian.day, &pengembalian.month, &pengembalian.year,
                          &denda);

        if (ret == 11) {
            printf("%-5d | %-12s | %-20s | %-25s | %02d-%02d-%04d   | %02d-%02d-%04d   | %-8d\n", 
                   nomor, id, nama, email, 
                   peminjaman.day, peminjaman.month, peminjaman.year,
                   pengembalian.day, pengembalian.month, pengembalian.year,
                   denda);
        } else {
            printf("Error parsing line: %s", buffer);
        }
    }

    printf("------------------------------------------------------------------------------------------------------------\n");
    fclose(file);
}

int kNomor(FILE *file) {
    int nomor = 0;      
    int temp = 0;       
    char buffer[300];   

    rewind(file);       
    
    while (fgets(buffer, sizeof(buffer), file)) {
        if (sscanf(buffer, "%d", &temp) == 1) {
            nomor = temp; 
        }
    }
	nomor = nomor + 1;
    return nomor; 
}

void toUpperStr(char *str) {
	int i;
   while (str[i] != '\0') {
        if (str[i] == '\n' || str[i] == '\r') {
            str[i] = '\0';
            break; 
        }
        str[i] = toupper(str[i]);
        i = i + 1;
	}
}

void trim(char *str) {
    str[strcspn(str, "\n")] = '\0'; 
    int length = strlen(str);
    while (length > 0 && str[length - 1] == ' ') {
        str[length - 1] = '\0'; 
        length = length - 1;
    }
}

int dupes(FILE *file, Buku *b) {
    char buffer[300];
    int boo = 0;
    Buku temp;
    int input_num;
    char input_char;
    long posAwal = ftell(file);
    
    input_char = b->id[2];
	input_num = atoi(&b->id[3]);

    rewind(file); 

    while (fgets(buffer, sizeof(buffer), file)) {

        if (sscanf(buffer, "%d %15s %150[^\t] %45[^\t] %100[^\t] %d %s",
                   &temp.nomor, temp.id, temp.judul, temp.jenis, temp.penerbit, &temp.jml, temp.rak) == 7)
				    {
			
			toUpperStr(temp.judul);
            toUpperStr(temp.jenis);
            trim(temp.judul);
            trim(temp.jenis);

            if (strcmp(temp.judul, b->judul) == 0 && strcmp(temp.jenis, b->jenis) == 0) {
                temp.jml = temp.jml + 1;
                boo = 1;
				
				fflush(file);
				return boo;
            }
        }
    }
}

void saveBuku(Buku *b){
	int noId;
	char buffer[300];
	Buku temp;
    FILE *file = fopen("data_buku.txt", "r+");
    if (file == NULL) {
        file = fopen("data_buku.txt", "w+");
        if (file == NULL) {
            printf("Gagal membuka atau membuat file!\n");
            return;
        }
        fprintf(file, "0\n"); 
        rewind(file);         
    }
	
    if(dupes(file, b) == 0){
    	b->judul[strcspn(b->judul, "\n")] = '\0';
    	b->jenis[strcspn(b->jenis, "\n")] = '\0';
		b->penerbit[strcspn(b->penerbit, "\n")] = '\0';
		b->jml = 1;
		srand(time(0));
		noId = rand() % 1000;
		sprintf(b->id, "%s%d", b->id ,noId);
	
		b->nomor = kNomor(file);

    	fseek(file, 0, SEEK_END); 
    	fprintf(file, "%-5d\t %-5s\t %-25s\t %-10s\t %-15s\t %d\t %s \n", 
				b->nomor, b->id, b->judul, b->jenis, b->penerbit, b->jml, b->rak);
				
    	printf("Data buku berhasil disimpan!\n");
    	fclose(file);
	}
	else{
		printf("Buku sudah ada, tolong pilih opsi update jika ingin menambahkan jumlah.\n");
	}

}

void tambahBuku (Buku *b){
	PrintTitle("Tambah Buku");
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
	else{
		strcpy(b->id, "XX");
	}
	
    printf("Masukkan penerbit buku: ");
    fgets(b->penerbit, sizeof(b->penerbit), stdin);
    b->penerbit[strcspn(b->penerbit, "\n")] = '\0';
    
    printf("Masukkan dimana buku disimpan (rak): ");
    fgets(b->rak, sizeof(b->rak), stdin);
    b->rak[strcspn(b->rak, "\n")] = '\0';
    
    saveBuku(b);
}

void updateBuku(Buku *b) {
	PrintTitle("Update Buku");
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
    char input_char;
    int input_num;

    printf("Masukkan id buku yang akan di-update: ");
    fgets(b->id, sizeof(b->id), stdin);
    b->id[strcspn(b->id, "\n")] = '\0';
    
    input_char = b->id[2];
	input_num = atoi(&b->id[3]);

    rewind(file);
    while (fgets(buffer, sizeof(buffer), file)) {
        if(sscanf(buffer, "%d %15s %150[^\t] %45[^\t] %100[^\t] %d %s",
                   &temp.nomor, temp.id, temp.judul, temp.jenis, temp.penerbit, &temp.jml, temp.rak) == 7) {
				
            if (strcmp(temp.id, b->id) == 0) {
                found = 1;
                printf("Apa yang ingin diperbaiki? \n");
                printf("1. Judul \n2. Jenis \n3. Penerbit \n4. Rak \n5. Jumlah buku\n ");
                printf("Pilih 1, 2, 3, 4, atau 5: ");
                scanf("%d", &i);
                getchar();  

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

                long posisiBaris = ftell(file) - strlen(buffer);
                fseek(file, posisiBaris, SEEK_SET);
                fprintf(file,"    \t %-5s\t %-25s\t %-10s\t %-15s\t %d\t %s", 
                        temp.id, temp.judul, temp.jenis, temp.penerbit, temp.jml, temp.rak);
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
	PrintTitle("Delete Buku");
    FILE *file = fopen("data_buku.txt", "r+");
    if (file == NULL) {
        printf("Gagal membuka file\n");
        return;
    }

    char buffer[300];
    Buku temp;
    char data[100][300]; 
    int totalBaris = 0;
    int nomor = 0;  

    printf("Masukkan ID buku yang akan dihapus: ");
    fgets(b->id, sizeof(b->id), stdin);
    b->id[strcspn(b->id, "\n")] = '\0'; 

    int found = 0;  

    rewind(file);
    while (fgets(buffer, sizeof(buffer), file)) {
        if(sscanf(buffer, "%d %15s %150[^\t] %45[^\t] %100[^\t] %d %s",
                   &temp.nomor, temp.id, temp.judul, temp.jenis, temp.penerbit, &temp.jml, temp.rak) == 7) {
            if (strcmp(temp.id, b->id) == 0) {
                found = 1;  
                continue;  
            }
            nomor = nomor + 1;  
            temp.nomor = nomor;  
            snprintf(data[totalBaris], sizeof(data[totalBaris]),"%-5d\t %-5s\t %-25s\t %-10s\t %-15s\t %d\t %s\n",
                     nomor, temp.id, temp.judul, temp.jenis, temp.penerbit, temp.jml, temp.rak);
            totalBaris = totalBaris + 1;
        }
    }

    fclose(file);

    if (!found) {
        printf("ID buku yang dimasukkan tidak ditemukan.\n");
        return;
    }

    file = fopen("data_buku.txt", "w");
    if (file == NULL) {
        printf("Gagal membuka file untuk menulis.\n");
        return;
    }

    for (int i = 0; i < totalBaris; i++) {
        fputs(data[i], file); 
    }

    fclose(file);

    printf("Data berhasil dihapus.\n");
}

void printIsiFile(Buku *b) {
    FILE *file = fopen("data_buku.txt", "r");
    if (file == NULL) {
        printf("File tidak ditemukan atau tidak dapat dibuka!\n");
        return;
    }

    char buffer[500]; // Buffer untuk membaca setiap baris
    PrintTitle("Daftar Buku");
    printf("%-3s\t|%-4s\t|%-25s\t|%-10s\t|%-15s\t|%s|%s|\n",
		"No", "ID", "Judul", "Jenis", "Penerbit", "Jumlah", "Rak");
    printf("----------------------------------------------------------------------------------------------------\n");

    // Baca dan cetak setiap baris
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }

    printf("----------------------------------------------------------------------------------------------------\n");
    fclose(file);
}












