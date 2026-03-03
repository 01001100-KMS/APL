#include <iostream>
#include <string>

using namespace std;

int main() {
    string namaBenar = "Heiza";
    string passwordBenar = "019";
    int attempt = 0;

    string namaInput;
    string passwordInput;
    bool loginBerhasil = false;

    while (attempt < 3) {
        cout << "\n=============================================\n";
        cout << "                   LOGIN                     \n";
        cout << "=============================================\n";
        cout << "  Username  : ";
        cin >> namaInput;
        cout << "  Password  : ";
        cin >> passwordInput;
        cout << "---------------------------------------------\n";

        if (namaInput == namaBenar && passwordInput == passwordBenar) {
            cout << "Login Berhasil!\n";
            loginBerhasil = true;
            break;
        } else {
            cout << "Login Salah!\n";
            attempt++;
        }
    }

    if (!loginBerhasil) {
        cout << "\nAnda gagal login 3 kali. Program berhenti.\n";
        return 0;
    }
    
    int pilihanMenu = 0;
    double nilaiWaktu;

    while (pilihanMenu != 4) {
        cout << "\n=====================================\n";
        cout << "        MENU KONVERSI WAKTU           \n";
        cout << "=====================================\n";
        cout << "  1. Jam    -> Menit & Detik          \n";
        cout << "  2. Menit  -> Jam & Detik            \n";
        cout << "  3. Detik  -> Jam & Menit            \n";
        cout << "  4. Keluar                          \n";
        cout << "-------------------------------------\n";
        cout << "  Pilih menu [1-4] : ";
        cin >> pilihanMenu;

        if (pilihanMenu == 1) {
            cout << "Masukkan jumlah jam: ";
            cin >> nilaiWaktu;
            cout << "Menit  : " << nilaiWaktu * 60 << endl;
            cout << "Detik  : " << nilaiWaktu * 3600 << endl;
        }
        else if (pilihanMenu == 2) {
            cout << "Masukkan jumlah menit: ";
            cin >> nilaiWaktu;
            cout << "Jam    : " << nilaiWaktu / 60 << endl;
            cout << "Detik  : " << nilaiWaktu * 60 << endl;
        }
        else if (pilihanMenu == 3) {
            cout << "Masukkan jumlah detik: ";
            cin >> nilaiWaktu;
            cout << "Jam    : " << nilaiWaktu / 3600 << endl;
            cout << "Menit  : " << nilaiWaktu / 60 << endl;
        }
        else if (pilihanMenu == 4) {
            cout << "Program selesai. Terima kasih!\n";
        }
        else {
            cout << "Pilihan tidak valid!\n";
        }
    }

    return 0;
}