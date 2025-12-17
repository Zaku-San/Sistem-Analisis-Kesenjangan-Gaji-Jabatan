#ifndef PEGAWAI_H
#define PEGAWAI_H

#include <string>
#include <vector>
using namespace std;

struct Pegawai {
    string nama;
    char gender;
    string pendidikan;
    string jabatan;
    int gaji;
};

extern vector<Pegawai> dataPegawai;

void menuCRUDPegawai();
void tampilkanPegawai();
void tambahPegawai();
void ubahPegawai();
void hapusPegawai();
void simpanKeFilePegawai();
void loadPegawai();
void analisisJabatan();

#endif
