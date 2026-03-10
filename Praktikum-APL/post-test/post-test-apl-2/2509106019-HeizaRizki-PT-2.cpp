#include <iostream>
#include <string>
#include <conio.h> //password and arrow keys
using namespace std;

struct User {
    string username;
    string password;
};

struct Developer {
    string namaDeveloper;
    string namaPerumahan;
    string lokasiPerumahan;
    int jumlahUnitRumah;
    long hargaRumah;
};

int main(){

    User pengguna;
    pengguna.username = "Heiza";
    pengguna.password = "019";

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

        if(inputUsername == pengguna.username && inputPassword == pengguna.password){
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
        return 0;
    }

    Developer dataDeveloper[100];
    int jumlahDataDeveloper = 0;
    int pilihanMenu;

    //Menu (Command di buat supaya saya gk pusing)
    do{

        system("cls");

        cout<<"===== SISTEM MANAJEMEN DATA DEVELOPER PERUMAHAN ====="<<endl;
        cout<<"1. Tambah Data Perumahan"<<endl;
        cout<<"2. Tampilkan Data Perumahan"<<endl;
        cout<<"3. Ubah Data Perumahan"<<endl;
        cout<<"4. Hapus Data Perumahan"<<endl;
        cout<<"5. Keluar"<<endl;
        cout<<"Pilih Menu : ";
        cin>>pilihanMenu;

        if(cin.fail()){
            cin.clear();
            cin.ignore(1000, '\n');
            pilihanMenu = 0;
        }
        //Bagian Create Data Perum
        if(pilihanMenu == 1){

            system("cls");
            cout<<"=== TAMBAH DATA PERUMAHAN YANG DIKEMBANGKAN ==="<<endl;

            if(jumlahDataDeveloper >= 100){
                cout<<"Data perumahan sudah penuh (maksimal 100 data)."<<endl;
                system("pause");
            }
            else{
                cin.ignore(1000, '\n');

                cout<<"Nama Developer : ";
                getline(cin, dataDeveloper[jumlahDataDeveloper].namaDeveloper);

                cout<<"Nama Perumahan : ";
                getline(cin, dataDeveloper[jumlahDataDeveloper].namaPerumahan);

                cout<<"Lokasi Perumahan : ";
                getline(cin, dataDeveloper[jumlahDataDeveloper].lokasiPerumahan);

                cout<<"Jumlah Unit Rumah : ";
                while(!(cin >> dataDeveloper[jumlahDataDeveloper].jumlahUnitRumah) || dataDeveloper[jumlahDataDeveloper].jumlahUnitRumah <= 0){
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout<<"Input tidak valid. Masukkan angka positif untuk Jumlah Unit Rumah : ";
                }

                cout<<"Harga Rumah : ";
                while(!(cin >> dataDeveloper[jumlahDataDeveloper].hargaRumah) || dataDeveloper[jumlahDataDeveloper].hargaRumah <= 0){
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout<<"Input tidak valid. Masukkan angka positif untuk Harga Rumah : ";
                }

                jumlahDataDeveloper++;

                cout<<"Data perumahan berhasil ditambahkan"<<endl;
                system("pause");
            }
        }
        //Read Data Perum
        else if(pilihanMenu == 2){

            system("cls");

            cout<<"=== DATA PERUMAHAN YANG SEDANG DIKEMBANGKAN ==="<<endl;

            if(jumlahDataDeveloper == 0){
                cout<<"Belum ada data perumahan."<<endl;
            }
            else{

                cout<<"--------------------------------------------------------------------------"<<endl;
                cout<<"No | Developer | Perumahan | Lokasi | Unit Rumah | Harga Rumah"<<endl;
                cout<<"--------------------------------------------------------------------------"<<endl;

                for(int i = 0; i < jumlahDataDeveloper; i++){

                    cout<<i+1<<" | "
                        <<dataDeveloper[i].namaDeveloper<<" | "
                        <<dataDeveloper[i].namaPerumahan<<" | "
                        <<dataDeveloper[i].lokasiPerumahan<<" | "
                        <<dataDeveloper[i].jumlahUnitRumah<<" | "
                        <<dataDeveloper[i].hargaRumah<<endl;
                }
            }

            system("pause");
        }

        //Upt Data Perum
        else if(pilihanMenu == 3){

            system("cls");

            int nomorData;

            cout<<"=== UBAH DATA PERUMAHAN ==="<<endl;

            if(jumlahDataDeveloper == 0){
                cout<<"Tidak ada data perumahan yang bisa diubah."<<endl;
                system("pause");
            }
            else{
                cout<<"Masukkan nomor data yang ingin diubah (1 - "<<jumlahDataDeveloper<<") : ";
                cin>>nomorData;

                if(cin.fail() || nomorData < 1 || nomorData > jumlahDataDeveloper){
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout<<"Nomor data tidak valid."<<endl;
                    system("pause");
                }
                else{
                    nomorData--;

                    cin.ignore(1000, '\n');

                    cout<<"Nama Developer Baru : ";
                    getline(cin, dataDeveloper[nomorData].namaDeveloper);

                    cout<<"Nama Perumahan Baru : ";
                    getline(cin, dataDeveloper[nomorData].namaPerumahan);

                    cout<<"Lokasi Perumahan Baru : ";
                    getline(cin, dataDeveloper[nomorData].lokasiPerumahan);

                    cout<<"Jumlah Unit Rumah Baru : ";
                    while(!(cin >> dataDeveloper[nomorData].jumlahUnitRumah) || dataDeveloper[nomorData].jumlahUnitRumah <= 0){
                        cin.clear();
                        cin.ignore(1000, '\n');
                        cout<<"Input tidak valid. Masukkan angka positif untuk Jumlah Unit Rumah : ";
                    }

                    cout<<"Harga Rumah Baru : ";
                    while(!(cin >> dataDeveloper[nomorData].hargaRumah) || dataDeveloper[nomorData].hargaRumah <= 0){
                        cin.clear();
                        cin.ignore(1000, '\n');
                        cout<<"Input tidak valid. Masukkan angka positif untuk Harga Rumah : ";
                    }

                    cout<<"Data berhasil diperbarui"<<endl;

                    system("pause");
                }
            }
        }
        
        //Del Data Perum
        else if(pilihanMenu == 4){

            system("cls");

            int nomorData;

            cout<<"=== HAPUS DATA PERUMAHAN ==="<<endl;

            if(jumlahDataDeveloper == 0){
                cout<<"Belum ada data perumahan yang bisa dihapus."<<endl;
                system("pause");
            }
            else{
                cout<<"Masukkan nomor data yang ingin dihapus (1 - "<<jumlahDataDeveloper<<") : ";
                cin>>nomorData;

                if(cin.fail() || nomorData < 1 || nomorData > jumlahDataDeveloper){
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout<<"Nomor data tidak valid."<<endl;
                    system("pause");
                }
                else{
                    nomorData--;

                    for(int i = nomorData; i < jumlahDataDeveloper - 1; i++){
                        dataDeveloper[i] = dataDeveloper[i+1];
                    }

                    jumlahDataDeveloper--;

                    cout<<"Data perumahan berhasil dihapus"<<endl;

                    system("pause");
                }
            }
        }
        //Ext
        else if(pilihanMenu != 5){
            cout<<"Pilihan menu tidak valid. Silakan pilih 1-5."<<endl;
            system("pause");
        }

    }while(pilihanMenu != 5);

    cout<<"Program selesai."<<endl;


    // Note, karna saya memiliki kapasitas otak yang
    // kurang mumpuni jadi saya tidak mengerti gimana cara 
    // masang tabeloid alhasil make ai buat benerin output 
    // yang kurang bagus dengan menggunakan == guna mempercantik

}