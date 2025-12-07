#include "../../include/jabatan/jabatan.h"
#include "../../include/pegawai/pegawai.h"
#include "../../include/warna.h"
#include <iostream>
#include <fstream>
#include <limits> 
#include <iomanip>
#include <algorithm>
using namespace std;

vector<Jabatan> daftarJabatan;
string fileJabatan = "../data/jabatan.txt";

void menuCRUDJabatan() {
    int pilih;

    while (true) {
        cout << YELLOW << BOLD << "\n=== MENU CRUD JABATAN ===\n" << RESET;
        cout << "1. Lihat Jabatan\n";
        cout << "2. Tambah Jabatan\n";
        cout << "3. Ubah Jabatan\n";
        cout << "4. Hapus Jabatan\n";
        cout << "5. Kembali ke Menu Utama\n";
        cout << "Pilih: ";
        cin >> pilih;

        switch (pilih) {
            case 1: tampilkanJabatan(); break;
            case 2: tambahJabatan(); break;
            case 3: ubahJabatan(); break;
            case 4: hapusJabatan(); break;
            case 5: return;
            default: cout << RED << "Pilihan tidak valid.\n" << RESET;
        }
    }
}

void tampilkanJabatan() {
    cout << BLUE << BOLD << "\n=== DAFTAR JABATAN ===\n" << RESET;

    if (daftarJabatan.empty()) {
        cout << RED << "Belum ada data jabatan.\n" << RESET;
        return;
    }

    for (int i = 0; i < daftarJabatan.size(); i++) {
        cout << i + 1 << ". " << daftarJabatan[i].nama
             << " | Range Gaji: Rp " << daftarJabatan[i].gajiMin
             << " - Rp " << daftarJabatan[i].gajiMax << endl;
    }
}

string pilihJabatanPegawai() {
    tampilkanJabatan();
    if (daftarJabatan.empty()) {
        cout << RED << "Tidak bisa memilih jabatan karena belum ada data.\n" << RESET;
        return "";
    }

    int pilihan;
    cout << "Pilih nomor jabatan: ";
    cin >> pilihan;

    if (pilihan < 1 || pilihan > daftarJabatan.size()) {
        cout << RED << "Pilihan tidak valid.\n" << RESET;
        return "";
    }

    return daftarJabatan[pilihan - 1].nama; 
}

void tambahJabatan() {
    Jabatan j;
    cout << BLUE << "\n=== TAMBAH JABATAN ===\n" << RESET;

    cout << "Nama Jabatan: ";
    cin >> j.nama;

    cout << "Gaji Minimum: ";
    cin >> j.gajiMin;

    cout << "Gaji Maksimum: ";
    cin >> j.gajiMax;

    daftarJabatan.push_back(j);

    simpanKeFileJabatan(); 

    cout << GREEN << "Jabatan berhasil ditambahkan!\n" << RESET;
}

void ubahJabatan() {
    tampilkanJabatan();
    if (daftarJabatan.empty()) return;

    int pilih;
    cout << "\nPilih nomor jabatan yang ingin diubah: ";
    cin >> pilih;

    if (pilih < 1 || pilih > daftarJabatan.size()) {
        cout << RED << "Pilihan tidak valid.\n" << RESET;
        return;
    }

    pilih--;
    string namaLama = daftarJabatan[pilih].nama;

    cout << "Nama Jabatan baru: ";
    cin >> daftarJabatan[pilih].nama;

    cout << "Gaji Minimum baru: ";
    cin >> daftarJabatan[pilih].gajiMin;

    cout << "Gaji Maksimum baru: ";
    cin >> daftarJabatan[pilih].gajiMax;

    simpanKeFileJabatan();

    cout << GREEN << "Jabatan berhasil diubah!\n" << RESET;

    bool adaPerubahan = false;

    for (auto &p : dataPegawai) {
        if (p.jabatan == namaLama) {
            p.jabatan = daftarJabatan[pilih].nama;
            adaPerubahan = true;
        }
    }

    if (adaPerubahan) {
        simpanKeFilePegawai();
        cout << GREEN << "Data Pegawai sudah disesuaikan dengan jabatan yang baru!" << RESET;
    }
    
}

void hapusJabatan() {
    tampilkanJabatan();
    if (daftarJabatan.empty()) return;

    int pilih;
    cout << "\nPilih nomor jabatan yang ingin dihapus: ";
    cin >> pilih;

    if (pilih < 1 || pilih > daftarJabatan.size()) {
        cout << RED << "Pilihan tidak valid.\n" << RESET;
        return;
    }

    daftarJabatan.erase(daftarJabatan.begin() + (pilih - 1));

    simpanKeFileJabatan();

    cout << GREEN << "Jabatan berhasil dihapus!\n" << RESET;
}

void simpanKeFileJabatan() {
  ofstream f(fileJabatan);

    for (auto &j : daftarJabatan) {
        f << j.nama << " " << j.gajiMin << " " << j.gajiMax << endl;
    }

    f.close();
    cout << GREEN << "Data jabatan berhasil disimpan ke file.\n" << RESET;
}

void loadJabatan() {
    ifstream f(fileJabatan);

    if (!f.is_open()) {
        cout << YELLOW << "File jabatan belum ditemukan. Menggunakan data default...\n" << RESET;
        daftarJabatan.push_back({"Manager", 8000000, 12000000});
        daftarJabatan.push_back({"Supervisor", 5000000, 8000000});
        daftarJabatan.push_back({"Staff", 3000000, 5000000});

        simpanKeFileJabatan();
        return;
    } 

    daftarJabatan.clear();

    Jabatan j;
    while (f >> j.nama >> j.gajiMin >> j.gajiMax) {
        daftarJabatan.push_back(j);
    }

    f.close();

    cout << GREEN << "Data jabatan berhasil dimuat dari file.\n" << RESET;
}

string formatRupiah(int angka) {
    string s = to_string(angka);
    string hasil;

    int hitung = 0;
    for (int i = s.size() - 1; i >= 0; i--) {
        hasil.push_back(s[i]);
        hitung++;

        if (hitung == 3 && i > 0) {
            hasil.push_back('.');
            hitung = 0;
        }
    }

    reverse(hasil.begin(), hasil.end());
    return hasil;
}



void analisisJabatan(const vector<Pegawai>& data) {
    cout << GREEN << "\n=== HASIL ANALISIS PER JABATAN ===\n" << RESET;

    for (auto &jab : daftarJabatan) {

        cout << BLUE << "\n=== Jabatan: " << jab.nama << " ===\n" << RESET;

        cout << left << setw(20) << "Nama"
             << setw(10) << "Gender"
             << setw(12) << "Pendidikan"
             << setw(12) << "Gaji (Rp)"
             << setw(35) << "Status"
             << setw(12) << "Selisih (Rp)\n";

        cout << string(100, '-') << endl;

        bool adaPegawai = false;

        vector<int> gajiList;   
        int gapTerbesar = 0;    

        for (auto &p : data) {
            if (p.jabatan != jab.nama) continue;
            adaPegawai = true;

            gajiList.push_back(p.gaji);

            string status;
            int selisih = 0;

            if (p.gaji < jab.gajiMin) {
                status = "Di Bawah Gaji Perusahaan";
                selisih = jab.gajiMin - p.gaji;
                gapTerbesar = max(gapTerbesar, selisih);
            }
            else if (p.gaji > jab.gajiMax) {
                status = "Di Atas Gaji Perusahaan";
                selisih = p.gaji - jab.gajiMax;
                gapTerbesar = max(gapTerbesar, selisih);
            }
            else {
                status = "Sesuai Dalam Range Gaji Perusahaan";
            }

            cout << left << setw(20) << p.nama
                 << setw(10) << p.gender
                 << setw(12) << p.pendidikan
                 << setw(12) << formatRupiah(p.gaji)
                 << setw(35) << status
                 << setw(12) << formatRupiah(selisih)
                 << endl;
        }

        if (!adaPegawai) {
            cout << YELLOW << "Tidak ada pegawai dalam jabatan ini.\n" << RESET;
            continue;
        }

        // ===========================
        //        ANALISIS DASAR
        // ===========================

        // cout << "\n" << GREEN << "--- Analisis Jabatan " << jab.nama << " ---\n" << RESET;

        // int totalGap = 0;
        // int countGap = 0;

        // for (auto &p : data) {
        //     if (p.jabatan != jab.nama) continue;

        //     if (p.gaji < jab.gajiMin) {
        //         totalGap += (jab.gajiMin - p.gaji);
        //         countGap++;
        //     }
        //     else if (p.gaji > jab.gajiMax) {
        //         totalGap += (p.gaji - jab.gajiMax);
        //         countGap++;
        //     }
        // }

        // if (countGap == 0) {
        //     cout << GREEN << "Semua gaji pegawai sesuai dengan standar jabatan.\n" << RESET;
        // } else {
        //     cout << RED << "Total kesenjangan gaji: Rp " << totalGap << RESET << endl;
        //     cout << YELLOW << "Ada " << countGap << " pegawai dengan gaji tidak sesuai rentang.\n" << RESET;
        // }


        double rata2 = 0;
        for (int g : gajiList) rata2 += g;
        rata2 /= gajiList.size();

        double gini = 0;
        if (gajiList.size() > 1) {
            for (int i = 0; i < gajiList.size(); i++) {
                for (int j = 0; j < gajiList.size(); j++) {
                    gini += abs(gajiList[i] - gajiList[j]);
                }
            }
            gini /= (2.0 * gajiList.size() * gajiList.size() * rata2);
        }

        string kategoriGini;
        if (gini < 0.2) kategoriGini = "Ketimpangan Rendah";
        else if (gini < 0.4) kategoriGini = "Ketimpangan Sedang";
        else kategoriGini = "Ketimpangan Tinggi";


        cout << CYAN << "\n--- LAPORAN ANALISIS " << jab.nama << "---\n" <<RESET;
        cout << "Rata-rata gaji: Rp " << formatRupiah(rata2) << endl;
        cout << "Gap terbesar: Rp " << formatRupiah(gapTerbesar)  << endl;
        cout << "Koefisien Gini: " << fixed << setprecision(3) << gini << endl;
        cout << "Interpretasi: " << kategoriGini << endl;

        cout << "\n";
    }

    cout << endl << endl;
    cout << YELLOW << "Tekan ENTER untuk kembali..." << RESET;
    cin.ignore();
    cin.get();
}


    

