#ifndef PeminjamanBukuHeader_h
#define PeminjamanBukuHeader_h

typedef struct {
    int day;  
    int month; 
    int year;  
} Date;

typedef struct {
	int nomor;
	char id[10];
	char judul[250];
	char jenis[100];
	char penerbit[100];
	int jml;
	char rak[10];
	int noId;
} Buku;

typedef struct {
	int nomor;
	char nama[50];
	char email[50];
	Date peminjaman;
	Date pengembalian;
} Peminjaman;

void PrintTitle(char *text);
void saveBuku(Buku *b);
void tambahBuku(Buku *b);
int kNomor(FILE *file);
void toUpperStr(char *str);
int dupes(FILE *file, Buku *b);
void printIsiFile(Buku *b);
void trim(char *str);
void updateBuku(Buku *b);
void deleteBuku(Buku *b);
void sort();
