#include <iostream>
#include "PeminjamanBukuHeader.h"

int main() {
	int page;
	bool is_admin = true;
	
	do {
		page = DashBoard();
		if (page == 1) {
        	PrintTitle("DASHBOARD USER");
    	} else if (page == 2) {
    		if (!is_admin){
			LoginAdmin();	
			} else {
				printf("DASHBOARD NADMINININNI");
//				DashboardAdmin();
			}
    	} else {
        	printf("Mohon masukan angka yang benar.\n");
    	}
	} while (page != 1 && page != 2);
}
