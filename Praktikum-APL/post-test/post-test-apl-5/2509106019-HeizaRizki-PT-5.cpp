#include <iostream>
#include <string>
#include <conio.h>
using namespace std;

struct User{
    string username;
    string password;
};

struct Developer{
    string namaDeveloper;
    string namaPerumahan;
    string lokasiPerumahan;
    int jumlahUnitRumah;
    long hargaRumah;
};

void tampilBaris(){
    cout<<"--------------------------------------------------------------------------"<<endl;
}

void tampilBaris(int panjang){
    for(int i=0;i<panjang;i++){
        cout<<"-";
    }
    cout<<endl;
}

int hitungRekursif(int jumlahDataDeveloper){
    if(jumlahDataDeveloper == 0){
        return 0;
    }
    return 1 + hitungRekursif(jumlahDataDeveloper-1);
}

//Sorting W Pointer

// Bubble Sort (ASC)
void bubbleSortNamaAscending(Developer *dataDeveloper, int jumlahDataDeveloper){
    for(int i = 0; i < jumlahDataDeveloper - 1; i++){
        for(int j = 0; j < jumlahDataDeveloper - i - 1; j++){
            if(dataDeveloper[j].namaDeveloper > dataDeveloper[j+1].namaDeveloper){
                Developer temp = dataDeveloper[j];
                dataDeveloper[j] = dataDeveloper[j+1];
                dataDeveloper[j+1] = temp;
            }
        }
    }
}

// Selection Sort (DESC)
void selectionSortHargaDescending(Developer *dataDeveloper, int jumlahDataDeveloper){
    for(int i = 0; i < jumlahDataDeveloper - 1; i++){
        int maxIndex = i;
        for(int j = i + 1; j < jumlahDataDeveloper; j++){
            if(dataDeveloper[j].hargaRumah > dataDeveloper[maxIndex].hargaRumah){
                maxIndex = j;
            }
        }

        Developer temp = dataDeveloper[i];
        dataDeveloper[i] = dataDeveloper[maxIndex];
        dataDeveloper[maxIndex] = temp;
    }
}

// Insertion Sort (ASC)
void insertionSortUnitAscending(Developer *dataDeveloper, int jumlahDataDeveloper){
    for(int i = 1; i < jumlahDataDeveloper; i++){
        Developer key = dataDeveloper[i];
        int j = i - 1;

        while(j >= 0 && dataDeveloper[j].jumlahUnitRumah > key.jumlahUnitRumah){
            dataDeveloper[j+1] = dataDeveloper[j];
            j--;
        }

        dataDeveloper[j+1] = key;
    }
}

//Login
bool login(User *pengguna){
    string inputUsername;
    string inputPassword;
    int logAttempt = 0;
    bool statusLog = false;

    while(logAttempt < 3){

        system("cls");
        cout<<"===== LOGIN SISTEM ====="<<endl;

        cout<<"Masukkan Username (Nama): ";
        cin>>inputUsername;

        cout<<"Masukkan Password (NIM): ";

        inputPassword = "";
        char ch;

        while((ch = _getch()) != 13){
            if(ch == 8){
                if(!inputPassword.empty()){
                    cout<<"\b \b";
                    inputPassword.pop_back();
                }
            }
            else{
                cout<<"*";
                inputPassword += ch;
            }
        }

        cout<<endl;

        if(inputUsername == pengguna->username && inputPassword == pengguna->password){
            statusLog = true;
            break;
        }
        else{
            cout<<"Login Salah"<<endl;
            logAttempt++;
            system("pause");
        }
    }

    if(statusLog == false){
        cout<<"Gagal login 3 kali"<<endl;
    }

    return statusLog;
}

//AddData
void tambahData(Developer *dataDeveloper, int *jumlahDataDeveloper){

    system("cls");

    cout<<"=== TAMBAH DATA PERUMAHAN YANG DIKEMBANGKAN ==="<<endl;

    if(*jumlahDataDeveloper >= 100){
        cout<<"Data penuh"<<endl;
        system("pause");
    }
    else{

        cout<<"Nama Developer : ";
        getline(cin,dataDeveloper[*jumlahDataDeveloper].namaDeveloper);

        cout<<"Nama Perumahan : ";
        getline(cin,dataDeveloper[*jumlahDataDeveloper].namaPerumahan);

        cout<<"Lokasi Perumahan : ";
        getline(cin,dataDeveloper[*jumlahDataDeveloper].lokasiPerumahan);

        cout<<"Jumlah Unit Rumah : ";
        cin>>dataDeveloper[*jumlahDataDeveloper].jumlahUnitRumah;

        cout<<"Harga Rumah : ";
        cin>>dataDeveloper[*jumlahDataDeveloper].hargaRumah;

        cin.ignore(1000,'\n');

        (*jumlahDataDeveloper)++;

        cout<<"Data berhasil ditambahkan"<<endl;
        system("pause");
    }
}

//Read
void tampilData(Developer *dataDeveloper, int jumlahDataDeveloper){

    system("cls");

    cout<<"=== DATA PERUMAHAN ==="<<endl;

    if(jumlahDataDeveloper == 0){
        cout<<"Belum ada data."<<endl;
    }
    else{

        tampilBaris();

        cout<<"No | Nama Developer | Nama Perumahan | Lokasi | Jumlah Unit | Harga Rumah"<<endl;

        tampilBaris();

        for(int i=0;i<jumlahDataDeveloper;i++){
            cout<<i+1<<" | "
                <<dataDeveloper[i].namaDeveloper<<" | "
                <<dataDeveloper[i].namaPerumahan<<" | "
                <<dataDeveloper[i].lokasiPerumahan<<" | "
                <<dataDeveloper[i].jumlahUnitRumah<<" | "
                <<dataDeveloper[i].hargaRumah<<endl;
        }

        tampilBaris(74);

        cout<<"Total Data : "<<hitungRekursif(jumlahDataDeveloper)<<endl;
    }

    system("pause");
}

//UbahData
void ubahData(Developer *dataDeveloper, int jumlahDataDeveloper){

    system("cls");

    int nomorData;

    cout<<"=== UBAH DATA ==="<<endl;

    if(jumlahDataDeveloper == 0){
        cout<<"Tidak ada data."<<endl;
        system("pause");
    }
    else{

        cout<<"Masukkan nomor data (1-"<<jumlahDataDeveloper<<"): ";
        cin>>nomorData;

        if(nomorData < 1 || nomorData > jumlahDataDeveloper){
            cout<<"Nomor data tidak valid."<<endl;
            system("pause");
            return;
        }

        nomorData--;

        cin.ignore(1000,'\n');

        cout<<"Nama Developer Baru : ";
        getline(cin,dataDeveloper[nomorData].namaDeveloper);

        cout<<"Nama Perumahan Baru : ";
        getline(cin,dataDeveloper[nomorData].namaPerumahan);

        cout<<"Lokasi Baru : ";
        getline(cin,dataDeveloper[nomorData].lokasiPerumahan);

        cout<<"Jumlah Unit Baru : ";
        cin>>dataDeveloper[nomorData].jumlahUnitRumah;

        cout<<"Harga Baru : ";
        cin>>dataDeveloper[nomorData].hargaRumah;

        cin.ignore(1000,'\n');

        cout<<"Data berhasil diubah"<<endl;
        system("pause");
    }
}

//Delete
void hapusData(Developer *dataDeveloper, int *jumlahDataDeveloper){

    system("cls");

    int nomorData;

    cout<<"=== HAPUS DATA ==="<<endl;

    if(*jumlahDataDeveloper == 0){
        cout<<"Belum ada data."<<endl;
        system("pause");
    }
    else{

        cout<<"Masukkan nomor data (1-"<<*jumlahDataDeveloper<<"): ";
        cin>>nomorData;

        if(nomorData < 1 || nomorData > *jumlahDataDeveloper){
            cout<<"Nomor data tidak valid."<<endl;
            system("pause");
            return;
        }

        nomorData--;

        for(int i = nomorData; i < (*jumlahDataDeveloper)-1; i++){
            dataDeveloper[i] = dataDeveloper[i+1];
        }

        (*jumlahDataDeveloper)--;

        cout<<"Data berhasil dihapus"<<endl;
        system("pause");
    }
}

//Main
int main(){

    User pengguna;
    pengguna.username = "Heiza";
    pengguna.password = "019";

    if(login(&pengguna) == false){
        return 0;
    }

    Developer dataDeveloper[100];
    int jumlahDataDeveloper = 0;
    int pilihanMenu;

    do{

        system("cls");

        cout<<"===== SISTEM MANAJEMEN ====="<<endl;
        cout<<"1. Tambah Data"<<endl;
        cout<<"2. Tampilkan Data"<<endl;
        cout<<"3. Ubah Data"<<endl;
        cout<<"4. Hapus Data"<<endl;
        cout<<"5. Sorting Nama (Ascending)"<<endl;
        cout<<"6. Sorting Harga (Descending)"<<endl;
        cout<<"7. Sorting Jumlah Unit (Ascending)"<<endl;
        cout<<"8. Keluar"<<endl;

        cout<<"Pilih Menu : ";
        cin>>pilihanMenu;
        cin.ignore(1000,'\n');

        if(pilihanMenu == 1){
            tambahData(dataDeveloper, &jumlahDataDeveloper);
        }
        else if(pilihanMenu == 2){
            tampilData(dataDeveloper, jumlahDataDeveloper);
        }
        else if(pilihanMenu == 3){
            ubahData(dataDeveloper, jumlahDataDeveloper);
        }
        else if(pilihanMenu == 4){
            hapusData(dataDeveloper, &jumlahDataDeveloper);
        }
        else if(pilihanMenu == 5){
            bubbleSortNamaAscending(dataDeveloper, jumlahDataDeveloper);
            cout<<"Sorting nama berhasil"<<endl;
            system("pause");
        }
        else if(pilihanMenu == 6){
            selectionSortHargaDescending(dataDeveloper, jumlahDataDeveloper);
            cout<<"Sorting harga berhasil"<<endl;
            system("pause");
        }
        else if(pilihanMenu == 7){
            insertionSortUnitAscending(dataDeveloper, jumlahDataDeveloper);
            cout<<"Sorting unit berhasil"<<endl;
            system("pause");
        }

    }while(pilihanMenu != 8);

    cout<<"Program selesai."<<endl;
}