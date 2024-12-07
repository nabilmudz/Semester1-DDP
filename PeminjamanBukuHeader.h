#include <stdio.h>

typedef struct {
	int no;
	char *nama;
	char *email;
	char *password;
	bool is_admin;
} User;

typedef struct {
    int day;  
    int month; 
    int year;  
} Date;

typedef struct {
	int nomor;
	char id[10];
	char judul[50];
	char genre[20];
	char penerbit[50];
	int jml;
	char rak[10];
} Buku;

typedef struct {
	int nomor;
	char nama[50];
	char email[50];
	Date peminjaman;
	Date pengembalian;
} Peminjaman;

void PrintTitle(char *text);
int DashBoard();
int LoginAdmin();

// Fungsi Tambah Buku (Baru) NOMOR INCREMENT (akan terus bertambah (ambil nomor terakhir dan ditambah 1))

// Fungsi Menampilkan semua buku & Search Bar (Optional)

/* Fungsi update Buku (Helper: Get Data Buku By ID, Ambil data subvar, simpen di temp, read mau update apa (bisa apa aja judul, penerbit, jumlah buku) 
dipilih dari nomor kolom pake selection CONTOH: kalau admin pilih 1 maka akan update judul dan sterusnya. */

/* Fungsi Delete Buku. NOTE: Nomor bisa diabaikan jika tidak berurut, tetapi lebih baik kalau diurutkan ulang */

