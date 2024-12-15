#include <stdio.h>

typedef struct {
	int no;
	char nama[50];
	char email[50];
	char password[50];
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
	char judul[250];
	char jenis[100];
	char penerbit[100];
	int jml;
	char rak[10];
	int noId;
} Buku;

typedef struct {
	int nomor;
	char id[6];
	char nama[50];
	char email[50];
	Date peminjaman;
	Date pengembalian;
	int denda;
} Peminjaman;




void PrintTitle(char *text);
int Dashboard();
void Register();
int Admin();
int DashboardAdmin(bool is_admin);
int GetLastID(const char *filename);
int Login();
int DaftarBuku(bool is_admin);
int DaftarPeminjaman(bool is_admin);
void updatePeminjaman(Peminjaman *p);
void CreatePeminjaman(Peminjaman *p);
void deletePeminjaman();
void ListPeminjaman();
int selisihHari(Date d1, Date d2);
int EmailExists(const char *filename, const char *email);
int IsUniqueID(const char *filename, const char *id);
int GenerateRandomNumber();
void saveBuku(Buku *b);
void tambahBuku(Buku *b);
int kNomor(FILE *file);
void toUpperStr(char *str);
int dupes(FILE *file, Buku *b);
void printIsiFile(Buku *b);
void trim(char *str);
void updateBuku(Buku *b);
void deleteBuku(Buku *b);


