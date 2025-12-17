#include "../../include/jabatan/jabatan.h"
#include "../../include/common.h"
#include "../../include/pegawai/pegawai.h"
#include "../../include/warna.h"
#include <iostream>
#include <fstream>
using namespace std;

vector<Pegawai> dataPegawai;
string filePegawai = "../data/pegawai.txt";

void menuCRUDPegawai(){
    int pilih;
    do {
        cout << YELLOW << BOLD << "\n=== MENU PEGAWAI ===\n" << RESET;
        cout << "1. Lihat Pegawai\n";
        cout << "2. Tambah Pegawai\n";
        cout << "3. Ubah Pegawai\n";
        cout << "4. Hapus Pegawai\n";
        cout << "5. Kembali\n";
        cout << "Pilih: ";
        cin >> pilih;

        if (cin.fail()) {
            cin.clear();                    
            cin.ignore(10000, '\n');        
            cout << RED << "Input tidak valid! Harap masukkan angka.\n" << RESET;
            continue;                       
        }

        switch (pilih) {
            case 1: tampilkanPegawai(); break;
            case 2: tambahPegawai(); break;
            case 3: ubahPegawai(); break;
            case 4: hapusPegawai(); break;
            case 5: break;
            default: cout << RED << "Pilihan tidak valid!\n" << RESET;
        }

    } while (pilih != 5);
}

void tampilkanPegawai() {
    cout << BLUE << BOLD << "\n=== DAFTAR PEGAWAI ===\n" << RESET;

    if (dataPegawai.empty()) {
        cout << RED << "Belum ada data pegawai.\n" << RESET;
        return;
    }

    for (int i = 0; i < dataPegawai.size(); i++) {
        cout << i + 1 << ". " << dataPegawai[i].nama
             << " | Gender: " << dataPegawai[i].gender
             << " | Pendidikan: " << dataPegawai[i].pendidikan
             << " | Jabatan: " << dataPegawai[i].jabatan
             << " | Gaji: Rp " << formatRupiah(dataPegawai[i].gaji) 
             << endl;
    }
}

void tambahPegawai() {
    Pegawai p;

    cout << BLUE << "\n=== TAMBAH PEGAWAI ===\n" << RESET;

    cout << "Nama: ";
    cin >> p.nama;

    cout << "Gender (L/P): ";
    cin >> p.gender;
    p.gender = toupper(p.gender);

    cout << "Pendidikan (SMP/SMA/D4/S1/S2): ";
    cin >> p.pendidikan;

    p.jabatan = pilihJabatanPegawai();
    if (p.jabatan == "") return; 

    cout << "Gaji Aktual: ";
    cin >> p.gaji;

    dataPegawai.push_back(p);

    simpanKeFilePegawai(); 

    cout << GREEN << "Pegawai berhasil ditambahkan!\n" << RESET;
}

void ubahPegawai() {
    tampilkanPegawai();
    if (dataPegawai.empty()) return;

    int pilih;
    cout << "\nPilih nomor pegawai yang ingin diubah: ";
    cin >> pilih;

    if (pilih < 1 || pilih > dataPegawai.size()) {
        cout << RED << "Pilihan tidak valid.\n" << RESET;
        return;
    }

    Pegawai &p = dataPegawai[pilih - 1];

    cout << "Nama baru: ";
    cin >> p.nama;

    cout << "Gender baru (L/P): ";
    cin >> p.gender;
    p.gender = toupper(p.gender);

    cout << "Pendidikan baru: ";
    cin >> p.pendidikan;

    // pilih ulang jabatan
    p.jabatan = pilihJabatanPegawai();
    if (p.jabatan == "") return;

    cout << "Gaji baru: ";
    cin >> p.gaji;

    simpanKeFilePegawai();

    cout << GREEN << "Pegawai berhasil diubah!\n" << RESET;
}

void hapusPegawai() {
    tampilkanPegawai();
    if (dataPegawai.empty()) return;

    int pilih;
    cout << "\nPilih nomor pegawai yang ingin dihapus: ";
    cin >> pilih;

    if (pilih < 1 || pilih > dataPegawai.size()) {
        cout << RED << "Pilihan tidak valid.\n" << RESET;
        return;
    }

    dataPegawai.erase(dataPegawai.begin() + (pilih - 1));

    simpanKeFilePegawai();

    cout << GREEN << "Pegawai berhasil dihapus!\n" << RESET;
}

void simpanKeFilePegawai() {
     ofstream f(filePegawai);

    for (auto &j : dataPegawai) {
        f << j.nama << " " << j.gender << " " << j.pendidikan << " " << j.jabatan << " " << j.gaji << endl;
    }

    f.close();
    cout << GREEN << "Data Pegawai berhasil disimpan ke file.\n" << RESET;
}

void loadPegawai(){
    ifstream f(filePegawai);

    if (!f.is_open()) {
        cout << YELLOW << "File Pegawai belum ditemukan. Silahkan isi data pegawai terlebih dahulu...\n" << RESET;
        return;
    } 

    dataPegawai.clear();

    Pegawai p;
    while (f >> p.nama >> p.gender >> p.pendidikan >> p.jabatan >> p.gaji) {
        dataPegawai.push_back(p);
    }

    f.close();

    cout << GREEN << "Data Pegawai berhasil dimuat dari file.\n" << RESET;
}