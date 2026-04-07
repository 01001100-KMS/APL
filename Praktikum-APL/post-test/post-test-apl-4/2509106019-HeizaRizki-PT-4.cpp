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

//Login (pointer)
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

// TAMBAH DATA (pointer)
void tambahData(Developer *dataDeveloper, int *jumlahDataDeveloper){

    system("cls");

    cout<<"=== TAMBAH DATA PERUMAHAN YANG DIKEMBANGKAN ==="<<endl;

    if(*jumlahDataDeveloper >= 100){
        cout<<"Data perumahan sudah penuh (maksimal 100 data)."<<endl;
        system("pause");
    }
    else{

        cin.ignore(1000,'\n');

        cout<<"Nama Developer : ";
        getline(cin,dataDeveloper[*jumlahDataDeveloper].namaDeveloper);

        cout<<"Nama Perumahan : ";
        getline(cin,dataDeveloper[*jumlahDataDeveloper].namaPerumahan);

        cout<<"Lokasi Perumahan : ";
        getline(cin,dataDeveloper[*jumlahDataDeveloper].lokasiPerumahan);

        cout<<"Jumlah Unit Rumah : ";

        while(!(cin>>dataDeveloper[*jumlahDataDeveloper].jumlahUnitRumah) || dataDeveloper[*jumlahDataDeveloper].jumlahUnitRumah <=0){
            cin.clear();
            cin.ignore(1000,'\n');
            cout<<"Input tidak valid. Masukkan angka positif: ";
        }

        cout<<"Harga Rumah : ";

        while(!(cin>>dataDeveloper[*jumlahDataDeveloper].hargaRumah) || dataDeveloper[*jumlahDataDeveloper].hargaRumah <=0){
            cin.clear();
            cin.ignore(1000,'\n');
            cout<<"Input tidak valid. Masukkan angka positif: ";
        }

        (*jumlahDataDeveloper)++;

        cout<<"Data perumahan berhasil ditambahkan"<<endl;

        system("pause");
    }
}

// TAMPIL DATA
void tampilData(Developer dataDeveloper[], int jumlahDataDeveloper){

    system("cls");

    cout<<"=== DATA PERUMAHAN ==="<<endl;

    if(jumlahDataDeveloper == 0){
        cout<<"Belum ada data."<<endl;
    }
    else{

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

// UBAH DATA (balikin, tanpa pointer biar konsisten)
void ubahData(Developer dataDeveloper[], int jumlahDataDeveloper){

    system("cls");

    int nomorData;

    cout<<"=== UBAH DATA PERUMAHAN ==="<<endl;

    if(jumlahDataDeveloper == 0){
        cout<<"Tidak ada data."<<endl;
        system("pause");
    }
    else{

        cout<<"Masukkan nomor data (1 - "<<jumlahDataDeveloper<<") : ";
        cin>>nomorData;

        if(cin.fail() || nomorData < 1 || nomorData > jumlahDataDeveloper){
            cin.clear();
            cin.ignore(1000,'\n');
            cout<<"Input tidak valid"<<endl;
            system("pause");
        }
        else{

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

            cout<<"Data berhasil diubah"<<endl;
            system("pause");
        }
    }
}

// HAPUS DATA (pointer)
void hapusData(Developer *dataDeveloper, int *jumlahDataDeveloper){

    system("cls");

    int nomorData;

    cout<<"=== HAPUS DATA ==="<<endl;

    if(*jumlahDataDeveloper == 0){
        cout<<"Belum ada data."<<endl;
        system("pause");
    }
    else{

        cout<<"Masukkan nomor data: ";
        cin>>nomorData;

        nomorData--;

        for(int i = nomorData; i < (*jumlahDataDeveloper)-1; i++){
            dataDeveloper[i] = dataDeveloper[i+1];
        }

        (*jumlahDataDeveloper)--;

        cout<<"Data berhasil dihapus"<<endl;

        system("pause");
    }
}

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
        cout<<"5. Keluar"<<endl;

        cout<<"Pilih Menu : ";
        cin>>pilihanMenu;

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

    }while(pilihanMenu != 5);

    cout<<"Program selesai."<<endl;
}