#ifndef VALIDATOR_H
#define VALIDATOR_H
#include <iostream>
#include <string>
#include <stdexcept>
#include <limits>

class DataPenuhException : public std::exception {
public:
    const char* what() const noexcept override {
        return "[!] ERROR: Data sudah penuh! Kapasitas maksimal 100 entri.";
    }
};

class DataKosongException : public std::exception {
public:
    const char* what() const noexcept override {
        return "[!] ERROR: Belum ada data yang tersimpan.";
    }
};

class IndexTidakValidException : public std::exception {
public:
    const char* what() const noexcept override {
        return "[!] ERROR: Nomor data yang dimasukkan tidak valid.";
    }
};

class LoginGagalException : public std::exception {
public:
    const char* what() const noexcept override {
        return "[!] AKSES DITOLAK: Anda telah gagal login 3 kali berturut-turut.";
    }
};

class InputTidakValidException : public std::exception {
private:
    std::string pesanKesalahan;
public:
    explicit InputTidakValidException(const std::string& pesan)
        : pesanKesalahan("[!] INPUT TIDAK VALID: " + pesan) {}

    const char* what() const noexcept override {
        return pesanKesalahan.c_str();
    }
};

class NilaiNegatifException : public std::exception {
private:
    std::string pesanKesalahan;
public:
    explicit NilaiNegatifException(const std::string& namaField)
        : pesanKesalahan("[!] ERROR: " + namaField + " tidak boleh bernilai nol atau negatif.") {}

    const char* what() const noexcept override {
        return pesanKesalahan.c_str();
    }
};


namespace Validator {

    // Membaca integer dari cin; lempar exception jika gagal
    int bacaInteger(const std::string& namaField) {
        int nilai;
        if (!(std::cin >> nilai)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            throw InputTidakValidException(namaField + " harus berupa bilangan bulat.");
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return nilai;
    }

    // Membaca long dari cin; throw exception jika gagal
    long bacaLong(const std::string& namaField) {
        long nilai;
        if (!(std::cin >> nilai)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            throw InputTidakValidException(namaField + " harus berupa angka.");
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return nilai;
    }

    // Validasi integer dalam rentang tertentu
    int validasiRentang(int nilai, int nilaiMin, int nilaiMax,
                        const std::string& namaField) {
        if (nilai < nilaiMin || nilai > nilaiMax) {
            throw InputTidakValidException(
                namaField + " harus antara " +
                std::to_string(nilaiMin) + " dan " +
                std::to_string(nilaiMax) + "."
            );
        }
        return nilai;
    }

    // Validasi string tidak kosong
    std::string validasiStringTidakKosong(const std::string& teks,
                                          const std::string& namaField) {
        if (teks.empty()) {
            throw InputTidakValidException(namaField + " tidak boleh kosong.");
        }
        return teks;
    }

    // Validasi nilai positif (int)
    int validasiPositif(int nilai, const std::string& namaField) {
        if (nilai <= 0) {
            throw NilaiNegatifException(namaField);
        }
        return nilai;
    }

    // Validasi nilai positif (long)
    long validasiPositifLong(long nilai, const std::string& namaField) {
        if (nilai <= 0) {
            throw NilaiNegatifException(namaField);
        }
        return nilai;
    }

}

#endif