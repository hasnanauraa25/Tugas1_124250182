#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

struct Product{
    char nama[50];
    float harga;
    char kategori[30];
    int stok;
};

Product produk[120];
int jmlh = 0;

void loadData(){
    FILE *file = fopen("lelele.csv", "r");
    if(file == NULL){
        return;
    }

    while(fscanf(file,"%[^,],%f,%[^,],%d\n",
        produk[jmlh].nama,
        &produk[jmlh].harga,
        produk[jmlh].kategori,
        &produk[jmlh].stok) != EOF){

        jmlh++;
    }

    fclose(file);
}

// save data
void saveData(){
    FILE *file = fopen("lelele.csv","w");

    for(int i=0; i<jmlh; i++){
        fprintf(file,"%s,%.1f,%s,%d\n",
        produk[i].nama,
        produk[i].harga,
        produk[i].kategori,
        produk[i].stok);
    }

    fclose(file);
}

// tambah produk
void tambahProduk(){

    cout << "~~~~ TAMBAH PRODUK ~~~~\n";
    cin.ignore();

    cout << "Nama produk  : ";
    cin.getline(produk[jmlh].nama,50);

    cout << "Harga produk  : ";
    cin >> produk[jmlh].harga;

    do{
        cout << "Kategori (makanan/minuman)  : ";
        cin >> produk[jmlh].kategori;

        if(strcmp(produk[jmlh].kategori,"makanan")!=0 &&
           strcmp(produk[jmlh].kategori,"minuman")!=0){

            cout << "Kategori hanya boleh makanan atau minuman!\n";
        }

    }while(strcmp(produk[jmlh].kategori,"makanan")!=0 &&
           strcmp(produk[jmlh].kategori,"minuman")!=0);

    cout << "Stok produk  : ";
    cin >> produk[jmlh].stok;

    jmlh++;

    saveData();

    cout << "Produk berhasil ditambahkan\n";
}

// tampilkan data
void tampilData(){

    if(jmlh == 0){
        cout << "Data produk masih kosong.\n";
        return;
    }

    cout << "~~~~~ DATA PRODUK ~~~~~\n";

    for(int i=0; i<jmlh; i++){

        cout << "\nProduk ke-" << i+1 << endl;
        cout << "Nama     : " << produk[i].nama << endl;
        cout << "Harga    : " << produk[i].harga << endl;
        cout << "Kategori : " << produk[i].kategori << endl;
        cout << "Stok     : " << produk[i].stok << endl;
    }
}

// bubble sort
void bubbleSort(){

    for(int i=0; i<jmlh-1; i++){
        for(int j=0; j<jmlh-i-1; j++){

            if(strcmp(produk[j].nama,produk[j+1].nama)>0){

                Product temp = produk[j];
                produk[j] = produk[j+1];
                produk[j+1] = temp;
            }
        }
    }

    cout << "Data berhasil diurutkan berdasar nama\n";
}

// quick sort
void quickSort(int low, int high){

    int i = low;
    int j = high;
    float pivot = produk[(low+high)/2].harga;

    while(i<=j){

        while(produk[i].harga > pivot) i++;
        while(produk[j].harga < pivot) j--;

        if(i<=j){

            Product temp = produk[i];
            produk[i] = produk[j];
            produk[j] = temp;

            i++;
            j--;
        }
    }

    if(low < j) quickSort(low,j);
    if(i < high) quickSort(i,high);
}

// sequential search
void sequentialSearch(){

    char cari[50];

    cin.ignore();

    cout << "Masukkan nama produk yang dicari : ";
    cin.getline(cari,50);

    for(int i=0; i<jmlh; i++){

        if(strcmp(cari,produk[i].nama)==0){

            cout << "Produk ditemukan\n";

            cout << "Nama    : " << produk[i].nama << endl;
            cout << "Harga   : " << produk[i].harga << endl;
            cout << "Kategori: " << produk[i].kategori << endl;
            cout << "Stok    : " << produk[i].stok << endl;

            return;
        }
    }

    cout << "Produk tidak ditemukan!\n";
}

// binary search
void binarySearch(){

    bubbleSort();

    char cari[50];

    cin.ignore();

    cout << "Masukkan nama produk yang mau dicari : ";
    cin.getline(cari,50);

    int low = 0;
    int high = jmlh-1;

    while(low<=high){

        int mid = (low+high)/2;

        int hasil = strcmp(cari,produk[mid].nama);

        if(hasil==0){

            cout << "Produk ditemukan!\n";

            cout << "Nama    : " << produk[mid].nama << endl;
            cout << "Harga   : " << produk[mid].harga << endl;
            cout << "Kategori: " << produk[mid].kategori << endl;
            cout << "Stok    : " << produk[mid].stok << endl;

            return;
        }

        else if(hasil > 0)
            low = mid + 1;

        else
            high = mid - 1;
    }

    cout << "Produk tidak ditemukan!\n";
}

// menu
void menu(){

    cout << "\n===== SISTEM LE LELE =====\n";
    cout << "1. Tambah produk\n";
    cout << "2. Urutkan produk\n";
    cout << "3. Cari produk\n";
    cout << "4. Tampilkan produk\n";
    cout << "5. Keluar\n";
    cout << "Pilihlah : ";
}

// main
int main(){

    int pilih;

    loadData();

    do{

        menu();
        cin >> pilih;

        switch(pilih){

            case 1:
                tambahProduk();
                break;

            case 2:{
                int sort;

                cout << "Menu Sorting\n";
                cout << "1. Bubble Sort (Nama Ascending)\n";
                cout << "2. Quick Sort (Harga Descending)\n";
                cout << "Pilih : ";
                cin >> sort;

                if(sort==1){
                    bubbleSort();
                    tampilData();
                }
                else if(sort==2){
                    quickSort(0,jmlh-1);
                    cout << "Data berhasil diurutkan berdasar harga\n";
                    tampilData();
                }

                break;
            }

            case 3:{
                int cari;

                cout << "Menu Pencarian\n";
                cout << "1. Sequential Search\n";
                cout << "2. Binary Search\n";
                cout << "Pilih : ";
                cin >> cari;

                if(cari==1){
                    sequentialSearch();
                }
                else if(cari==2){
                    binarySearch();
                }

                break;
            }

            case 4:
                tampilData();
                break;

            case 5:
                cout << "Keluar dari program\n";
                break;

            default:
                cout << "Menu tidak tersedia\n";
        }

    }while(pilih!=5);
}