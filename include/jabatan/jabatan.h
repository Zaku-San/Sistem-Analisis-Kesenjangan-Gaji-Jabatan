#ifndef JABATAN_H
#define JABATAN_H

#include "../pegawai/pegawai.h"
#include <vector>
#include <string>
using namespace std;

struct Jabatan {
    string nama;
    int gajiMin;
    int gajiMax;
};

extern vector<Jabatan> daftarJabatan;

void menuCRUDJabatan();
void tampilkanJabatan();
string pilihJabatanPegawai();
void tambahJabatan();
void ubahJabatan();
void hapusJabatan();
void simpanKeFileJabatan();
void analisisJabatan(const vector<Pegawai>& data);
void loadJabatan();

#endif
