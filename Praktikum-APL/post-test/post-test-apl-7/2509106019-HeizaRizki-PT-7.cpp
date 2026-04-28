#include <iostream>
#include <string>
#include <iomanip>
#include <conio.h>
#include <windows.h>
#include "validator.h"

using namespace std;

//KONSTANTA & WARNA KONSOL

const int KAPASITAS_MAKS = 100;

//Color Pallate Windows Console
enum KodeWarna {
    WARNA_PUTIH    = 7,
    WARNA_HIJAU    = 10,
    WARNA_MERAH    = 12,
    WARNA_KUNING   = 14,
    WARNA_BIRU_MUD = 11,
    WARNA_BIRU_TUA = 9,
    WARNA_UNGU     = 13
};

//STRUCT

struct Pengguna {
    string namaAkun;
    string kataSandi;
};

struct Developer {
    string namaDeveloper;
    string namaPerumahan;
    string lokasiPerumahan;
    int    jumlahUnitRumah;
    long   hargaRumah;
};

//FUNGSI UTILITAS TAMPILAN

void aturWarna(int kodeWarna) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kodeWarna);
}

void resetWarna() {
    aturWarna(WARNA_PUTIH);
}

void cetakGaris(char karakter = '=', int panjang = 74) {
    for (int i = 0; i < panjang; i++) cout << karakter;
    cout << endl;
}

void cetakBanner() {
    system("cls");
    aturWarna(WARNA_BIRU_MUD);
    cetakGaris('=');
    cout << setw(45) << "  SISTEM MANAJEMEN DATA DEVELOPER PERUMAHAN  " << endl;
    cetakGaris('=');
    resetWarna();
}

void cetakPesan(const string& pesan, int kodeWarna = WARNA_HIJAU) {
    aturWarna(kodeWarna);
    cout << endl << pesan << endl;
    resetWarna();
}

void cetakError(const string& pesanError) {
    aturWarna(WARNA_MERAH);
    cout << endl << pesanError << endl;
    resetWarna();
}

//FUNGSI REKURSIF  -  Menghitung jumlah data

int hitungRekursif(int jumlahDataDeveloper) {
    if (jumlahDataDeveloper == 0) return 0;
    return 1 + hitungRekursif(jumlahDataDeveloper - 1);
}

//ALGORITMA SORTING

void bubbleSortNamaAscending(Developer* dataDeveloper, int jumlahDataDeveloper) {
    for (int i = 0; i < jumlahDataDeveloper - 1; i++) {
        for (int j = 0; j < jumlahDataDeveloper - i - 1; j++) {
            if (dataDeveloper[j].namaDeveloper > dataDeveloper[j + 1].namaDeveloper) {
                Developer temp         = dataDeveloper[j];
                dataDeveloper[j]       = dataDeveloper[j + 1];
                dataDeveloper[j + 1]   = temp;
            }
        }
    }
}

void selectionSortHargaDescending(Developer* dataDeveloper, int jumlahDataDeveloper) {
    for (int i = 0; i < jumlahDataDeveloper - 1; i++) {
        int indeksMaks = i;
        for (int j = i + 1; j < jumlahDataDeveloper; j++) {
            if (dataDeveloper[j].hargaRumah > dataDeveloper[indeksMaks].hargaRumah) {
                indeksMaks = j;
            }
        }
        Developer temp             = dataDeveloper[i];
        dataDeveloper[i]           = dataDeveloper[indeksMaks];
        dataDeveloper[indeksMaks]  = temp;
    }
}

void insertionSortUnitAscending(Developer* dataDeveloper, int jumlahDataDeveloper) {
    for (int i = 1; i < jumlahDataDeveloper; i++) {
        Developer kunci = dataDeveloper[i];
        int j = i - 1;
        while (j >= 0 && dataDeveloper[j].jumlahUnitRumah > kunci.jumlahUnitRumah) {
            dataDeveloper[j + 1] = dataDeveloper[j];
            j--;
        }
        dataDeveloper[j + 1] = kunci;
    }
}

//ALGORITMA PENCARIAN

void sequentialSearchNama(Developer* dataDeveloper, int jumlahDataDeveloper) {
    cetakBanner();
    aturWarna(WARNA_KUNING);
    cout << "  [ CARI DATA - SEQUENTIAL SEARCH (NAMA DEVELOPER) ]" << endl;
    resetWarna();
    cetakGaris('-');

    try {
        if (jumlahDataDeveloper == 0) throw DataKosongException();

        string namaDicari;
        cout << "  Masukkan nama developer yang dicari : ";
        getline(cin, namaDicari);
        Validator::validasiStringTidakKosong(namaDicari, "Nama pencarian");

        bool  statusDitemukan  = false;
        int   indeksDitemukan  = -1;

        for (int posisi = 0; posisi < jumlahDataDeveloper; posisi++) {
            if (dataDeveloper[posisi].namaDeveloper == namaDicari) {
                statusDitemukan = true;
                indeksDitemukan = posisi;
                break;
            }
        }

        if (statusDitemukan) {
            cetakGaris('-');
            aturWarna(WARNA_HIJAU);
            cout << "  Data ditemukan pada nomor " << indeksDitemukan + 1 << endl;
            resetWarna();
            cetakGaris('-');
            cout << "  Nama Developer  : " << dataDeveloper[indeksDitemukan].namaDeveloper  << endl;
            cout << "  Nama Perumahan  : " << dataDeveloper[indeksDitemukan].namaPerumahan   << endl;
            cout << "  Lokasi          : " << dataDeveloper[indeksDitemukan].lokasiPerumahan << endl;
            cout << "  Jumlah Unit     : " << dataDeveloper[indeksDitemukan].jumlahUnitRumah << " unit" << endl;
            cout << "  Harga Rumah     : Rp " << dataDeveloper[indeksDitemukan].hargaRumah  << endl;
        } else {
            cetakPesan("  Data dengan nama \"" + namaDicari + "\" tidak ditemukan.", WARNA_KUNING);
        }

    } catch (const DataKosongException& e) {
        cetakError(e.what());
    } catch (const InputTidakValidException& e) {
        cetakError(e.what());
    }

    cetakGaris('-');
    system("pause");
}

void binarySearchUnit(Developer* dataDeveloper, int jumlahDataDeveloper) {
    cetakBanner();
    aturWarna(WARNA_KUNING);
    cout << "  [ CARI DATA - BINARY SEARCH (JUMLAH UNIT RUMAH) ]" << endl;
    resetWarna();
    cetakGaris('-');

    try {
        if (jumlahDataDeveloper == 0) throw DataKosongException();

        // Salin data ke array temp, lalu sort ascending
        Developer dataSementara[KAPASITAS_MAKS];
        for (int i = 0; i < jumlahDataDeveloper; i++) {
            dataSementara[i] = dataDeveloper[i];
        }
        insertionSortUnitAscending(dataSementara, jumlahDataDeveloper);

        cout << "  Masukkan jumlah unit yang dicari : ";
        int unitDicari = Validator::bacaInteger("Jumlah unit");
        Validator::validasiPositif(unitDicari, "Jumlah unit");

        int  posisiKiri     = 0;
        int  posisiKanan    = jumlahDataDeveloper - 1;
        int  posisiTengah   = 0;
        bool statusDitemukan = false;
        int  indeksDitemukan = -1;

        while (posisiKiri <= posisiKanan) {
            posisiTengah = (posisiKiri + posisiKanan) / 2;
            if (dataSementara[posisiTengah].jumlahUnitRumah == unitDicari) {
                statusDitemukan = true;
                indeksDitemukan = posisiTengah;
                break;
            } else if (dataSementara[posisiTengah].jumlahUnitRumah < unitDicari) {
                posisiKiri = posisiTengah + 1;
            } else {
                posisiKanan = posisiTengah - 1;
            }
        }

        if (statusDitemukan) {
            cetakGaris('-');
            aturWarna(WARNA_HIJAU);
            cout << "  Data ditemukan!" << endl;
            resetWarna();
            cetakGaris('-');
            cout << "  Nama Developer  : " << dataSementara[indeksDitemukan].namaDeveloper  << endl;
            cout << "  Nama Perumahan  : " << dataSementara[indeksDitemukan].namaPerumahan   << endl;
            cout << "  Lokasi          : " << dataSementara[indeksDitemukan].lokasiPerumahan << endl;
            cout << "  Jumlah Unit     : " << dataSementara[indeksDitemukan].jumlahUnitRumah << " unit" << endl;
            cout << "  Harga Rumah     : Rp " << dataSementara[indeksDitemukan].hargaRumah  << endl;
        } else {
            cetakPesan("  Data dengan jumlah unit " + to_string(unitDicari) + " tidak ditemukan.", WARNA_KUNING);
        }

    } catch (const DataKosongException& e) {
        cetakError(e.what());
    } catch (const InputTidakValidException& e) {
        cetakError(e.what());
    } catch (const NilaiNegatifException& e) {
        cetakError(e.what());
    }

    cetakGaris('-');
    system("pause");
}

//LOGIN

bool login(Pengguna* akun) {
    string inputNamaAkun;
    string inputKataSandi;
    int    jumlahPercobaan = 0;
    bool   statusBerhasil  = false;

    while (jumlahPercobaan < 3) {
        cetakBanner();
        aturWarna(WARNA_KUNING);
        cout << "  [ LOGIN SISTEM - PERCOBAAN " << jumlahPercobaan + 1 << "/3 ]" << endl;
        resetWarna();
        cetakGaris('-');

        cout << "  Username (Nama) : ";
        cin >> inputNamaAkun;

        cout << "  Password (NIM)  : ";
        inputKataSandi = "";
        char karakterInput;

        while ((karakterInput = _getch()) != 13) {
            if (karakterInput == 8) {
                if (!inputKataSandi.empty()) {
                    cout << "\b \b";
                    inputKataSandi.pop_back();
                }
            } else {
                cout << "*";
                inputKataSandi += karakterInput;
            }
        }
        cout << endl;

        if (inputNamaAkun == akun->namaAkun && inputKataSandi == akun->kataSandi) {
            statusBerhasil = true;
            break;
        } else {
            cetakError("  Login salah! Periksa kembali username dan password Anda.");
            jumlahPercobaan++;
            system("pause");
        }
    }

    try {
        if (!statusBerhasil) throw LoginGagalException();
    } catch (const LoginGagalException& e) {
        cetakError(e.what());
        system("pause");
        return false;
    }

    aturWarna(WARNA_HIJAU);
    cout << endl << "  Login berhasil! Selamat datang, " << akun->namaAkun << "!" << endl;
    resetWarna();
    system("pause");
    return true;
}

//OPERASI CRUD

void tambahData(Developer* dataDeveloper, int* jumlahDataDeveloper) {
    cetakBanner();
    aturWarna(WARNA_KUNING);
    cout << "  [ TAMBAH DATA DEVELOPER PERUMAHAN ]" << endl;
    resetWarna();
    cetakGaris('-');

    try {
        if (*jumlahDataDeveloper >= KAPASITAS_MAKS) throw DataPenuhException();

        string inputNama, inputPerumahan, inputLokasi;
        int    inputUnit;
        long   inputHarga;

        cout << "  Nama Developer   : ";
        getline(cin, inputNama);
        Validator::validasiStringTidakKosong(inputNama, "Nama Developer");

        cout << "  Nama Perumahan   : ";
        getline(cin, inputPerumahan);
        Validator::validasiStringTidakKosong(inputPerumahan, "Nama Perumahan");

        cout << "  Lokasi Perumahan : ";
        getline(cin, inputLokasi);
        Validator::validasiStringTidakKosong(inputLokasi, "Lokasi");

        cout << "  Jumlah Unit Rumah: ";
        inputUnit = Validator::bacaInteger("Jumlah Unit");
        Validator::validasiPositif(inputUnit, "Jumlah Unit Rumah");

        cout << "  Harga Rumah (Rp) : ";
        inputHarga = Validator::bacaLong("Harga Rumah");
        Validator::validasiPositifLong(inputHarga, "Harga Rumah");

        //Simpan ke array
        dataDeveloper[*jumlahDataDeveloper].namaDeveloper   = inputNama;
        dataDeveloper[*jumlahDataDeveloper].namaPerumahan    = inputPerumahan;
        dataDeveloper[*jumlahDataDeveloper].lokasiPerumahan  = inputLokasi;
        dataDeveloper[*jumlahDataDeveloper].jumlahUnitRumah  = inputUnit;
        dataDeveloper[*jumlahDataDeveloper].hargaRumah       = inputHarga;
        (*jumlahDataDeveloper)++;

        cetakPesan("  [OK] Data berhasil ditambahkan!", WARNA_HIJAU);

    } catch (const DataPenuhException& e) {
        cetakError(e.what());
    } catch (const InputTidakValidException& e) {
        cetakError(e.what());
    } catch (const NilaiNegatifException& e) {
        cetakError(e.what());
    }

    cetakGaris('-');
    system("pause");
}

void tampilData(Developer* dataDeveloper, int jumlahDataDeveloper) {
    cetakBanner();
    aturWarna(WARNA_KUNING);
    cout << "  [ DAFTAR DATA DEVELOPER PERUMAHAN ]" << endl;
    resetWarna();
    cetakGaris('-');

    try {
        if (jumlahDataDeveloper == 0) throw DataKosongException();

        // Header tabel
        aturWarna(WARNA_BIRU_MUD);
        cout << left
             << setw(4)  << "No"
             << setw(18) << "Nama Developer"
             << setw(20) << "Nama Perumahan"
             << setw(15) << "Lokasi"
             << setw(8)  << "Unit"
             << setw(16) << "Harga (Rp)"
             << endl;
        resetWarna();
        cetakGaris('-');

        for (int i = 0; i < jumlahDataDeveloper; i++) {
            cout << left
                 << setw(4)  << i + 1
                 << setw(18) << dataDeveloper[i].namaDeveloper
                 << setw(20) << dataDeveloper[i].namaPerumahan
                 << setw(15) << dataDeveloper[i].lokasiPerumahan
                 << setw(8)  << dataDeveloper[i].jumlahUnitRumah
                 << setw(16) << dataDeveloper[i].hargaRumah
                 << endl;
        }

        cetakGaris('-');
        aturWarna(WARNA_KUNING);
        cout << "  Total data (rekursif) : " << hitungRekursif(jumlahDataDeveloper) << " entri" << endl;
        resetWarna();

    } catch (const DataKosongException& e) {
        cetakError(e.what());
    }

    cetakGaris('-');
    system("pause");
}

void ubahData(Developer* dataDeveloper, int jumlahDataDeveloper) {
    cetakBanner();
    aturWarna(WARNA_KUNING);
    cout << "  [ UBAH DATA DEVELOPER ]" << endl;
    resetWarna();
    cetakGaris('-');

    try {
        if (jumlahDataDeveloper == 0) throw DataKosongException();

        cout << "  Masukkan nomor data (1-" << jumlahDataDeveloper << ") : ";
        int nomorData = Validator::bacaInteger("Nomor data");
        Validator::validasiRentang(nomorData, 1, jumlahDataDeveloper, "Nomor data");

        int indeksData = nomorData - 1;

        string inputNama, inputPerumahan, inputLokasi;
        int    inputUnit;
        long   inputHarga;

        cout << "  Nama Developer Baru  : ";
        getline(cin, inputNama);
        Validator::validasiStringTidakKosong(inputNama, "Nama Developer");

        cout << "  Nama Perumahan Baru  : ";
        getline(cin, inputPerumahan);
        Validator::validasiStringTidakKosong(inputPerumahan, "Nama Perumahan");

        cout << "  Lokasi Baru          : ";
        getline(cin, inputLokasi);
        Validator::validasiStringTidakKosong(inputLokasi, "Lokasi");

        cout << "  Jumlah Unit Baru     : ";
        inputUnit = Validator::bacaInteger("Jumlah Unit");
        Validator::validasiPositif(inputUnit, "Jumlah Unit Rumah");

        cout << "  Harga Baru (Rp)      : ";
        inputHarga = Validator::bacaLong("Harga Rumah");
        Validator::validasiPositifLong(inputHarga, "Harga Rumah");

        dataDeveloper[indeksData].namaDeveloper   = inputNama;
        dataDeveloper[indeksData].namaPerumahan    = inputPerumahan;
        dataDeveloper[indeksData].lokasiPerumahan  = inputLokasi;
        dataDeveloper[indeksData].jumlahUnitRumah  = inputUnit;
        dataDeveloper[indeksData].hargaRumah       = inputHarga;

        cetakPesan("  [OK] Data berhasil diubah!", WARNA_HIJAU);

    } catch (const DataKosongException& e) {
        cetakError(e.what());
    } catch (const InputTidakValidException& e) {
        cetakError(e.what());
    } catch (const NilaiNegatifException& e) {
        cetakError(e.what());
    }

    cetakGaris('-');
    system("pause");
}

void hapusData(Developer* dataDeveloper, int* jumlahDataDeveloper) {
    cetakBanner();
    aturWarna(WARNA_KUNING);
    cout << "  [ HAPUS DATA DEVELOPER ]" << endl;
    resetWarna();
    cetakGaris('-');

    try {
        if (*jumlahDataDeveloper == 0) throw DataKosongException();

        cout << "  Masukkan nomor data (1-" << *jumlahDataDeveloper << ") : ";
        int nomorData = Validator::bacaInteger("Nomor data");
        Validator::validasiRentang(nomorData, 1, *jumlahDataDeveloper, "Nomor data");

        int indeksData = nomorData - 1;

        //Geser data ke kiri
        for (int i = indeksData; i < (*jumlahDataDeveloper) - 1; i++) {
            dataDeveloper[i] = dataDeveloper[i + 1];
        }
        (*jumlahDataDeveloper)--;

        cetakPesan("  [OK] Data nomor " + to_string(nomorData) + " berhasil dihapus!", WARNA_HIJAU);

    } catch (const DataKosongException& e) {
        cetakError(e.what());
    } catch (const InputTidakValidException& e) {
        cetakError(e.what());
    }

    cetakGaris('-');
    system("pause");
}

//FUNGSI TAMPIL MENU UTAMA

void tampilMenuUtama() {
    cetakBanner();
    aturWarna(WARNA_BIRU_MUD);
    cout << "  MENU UTAMA" << endl;
    resetWarna();
    cetakGaris('-');
    cout << "  [1]  Tambah Data" << endl;
    cout << "  [2]  Tampilkan Data" << endl;
    cout << "  [3]  Ubah Data" << endl;
    cout << "  [4]  Hapus Data" << endl;
    cetakGaris('-');
    aturWarna(WARNA_KUNING);
    cout << "  -- SORTING --" << endl;
    resetWarna();
    cout << "  [5]  Sort Nama Developer (Bubble Sort  - Ascending)" << endl;
    cout << "  [6]  Sort Harga Rumah    (Selection Sort - Descending)" << endl;
    cout << "  [7]  Sort Jumlah Unit    (Insertion Sort - Ascending)" << endl;
    cetakGaris('-');
    aturWarna(WARNA_KUNING);
    cout << "  -- PENCARIAN --" << endl;
    resetWarna();
    cout << "  [8]  Cari Nama Developer  (Sequential Search)" << endl;
    cout << "  [9]  Cari Jumlah Unit     (Binary Search)" << endl;
    cetakGaris('-');
    aturWarna(WARNA_MERAH);
    cout << "  [10] Keluar" << endl;
    resetWarna();
    cetakGaris('=');
    cout << "  Pilih Menu : ";
}

//MAIN

int main() {
    Pengguna akun;
    akun.namaAkun  = "Heiza";
    akun.kataSandi = "019";

    if (!login(&akun)) return 0;

    Developer dataDeveloper[KAPASITAS_MAKS];
    int       jumlahDataDeveloper = 0;
    int       pilihanMenu         = 0;

    do {
        tampilMenuUtama();

        try {
            pilihanMenu = Validator::bacaInteger("Pilihan menu");
            Validator::validasiRentang(pilihanMenu, 1, 10, "Pilihan menu");

        } catch (const InputTidakValidException& e) {
            cetakError(e.what());
            system("pause");
            continue;
        }

        switch (pilihanMenu) {
            case 1:
                tambahData(dataDeveloper, &jumlahDataDeveloper);
                break;
            case 2:
                tampilData(dataDeveloper, jumlahDataDeveloper);
                break;
            case 3:
                ubahData(dataDeveloper, jumlahDataDeveloper);
                break;
            case 4:
                hapusData(dataDeveloper, &jumlahDataDeveloper);
                break;
            case 5:
                try {
                    if (jumlahDataDeveloper == 0) throw DataKosongException();
                    bubbleSortNamaAscending(dataDeveloper, jumlahDataDeveloper);
                    cetakPesan("  [OK] Data berhasil diurutkan berdasarkan Nama (Ascending).", WARNA_HIJAU);
                } catch (const DataKosongException& e) {
                    cetakError(e.what());
                }
                system("pause");
                break;
            case 6:
                try {
                    if (jumlahDataDeveloper == 0) throw DataKosongException();
                    selectionSortHargaDescending(dataDeveloper, jumlahDataDeveloper);
                    cetakPesan("  [OK] Data berhasil diurutkan berdasarkan Harga (Descending).", WARNA_HIJAU);
                } catch (const DataKosongException& e) {
                    cetakError(e.what());
                }
                system("pause");
                break;
            case 7:
                try {
                    if (jumlahDataDeveloper == 0) throw DataKosongException();
                    insertionSortUnitAscending(dataDeveloper, jumlahDataDeveloper);
                    cetakPesan("  [OK] Data berhasil diurutkan berdasarkan Jumlah Unit (Ascending).", WARNA_HIJAU);
                } catch (const DataKosongException& e) {
                    cetakError(e.what());
                }
                system("pause");
                break;
            case 8:
                sequentialSearchNama(dataDeveloper, jumlahDataDeveloper);
                break;
            case 9:
                binarySearchUnit(dataDeveloper, jumlahDataDeveloper);
                break;
            case 10:
                cetakBanner();
                aturWarna(WARNA_HIJAU);
                cout << "  Terima kasih telah menggunakan sistem ini. Sampai jumpa!" << endl;
                resetWarna();
                cetakGaris('=');
                break;
            default:
                break;
        }

    } while (pilihanMenu != 10);

    return 0;
}