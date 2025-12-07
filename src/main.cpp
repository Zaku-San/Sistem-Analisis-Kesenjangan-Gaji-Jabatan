#include <iostream>
#include "../include/warna.h"
#include "../include/jabatan/jabatan.h"
#include "../include/pegawai/pegawai.h"
using namespace std;

int main() {
    loadJabatan();
    loadPegawai();

    int pilihan;

    while (true) {

        cout << GREEN << BOLD << "[SELAMAT DATANG DI APLIKASI BLABLABLA] \n\n"<< RESET;
        cout << "Aplikasi Sistem Analisis Upah dan Kesenjangan Gaji digunakan untuk\n"
                "menghitung rata-rata gaji antar kelompok dan menganalisis tingkat\n"
                "kesenjangan menggunakan koefisien Gini sederhana. Program menerima\n"
                "data pegawai, mengolah perbandingan gaji tiap kelompok, dan\n"
                "menghasilkan laporan ringkas tentang tingkat ketimpangan upah.\n\n\n";

        cout << BLUE << BOLD << "TUJUAN APLIKASI:\n" << RESET;
        cout << "- Mengidentifikasi ketimpangan gaji antar karyawan dengan jabatan,\n"
                "  tanggung jawab, dan kualifikasi yang setara.\n"
                "- Menganalisis struktur penggajian berdasarkan parameter kuantitatif\n"
                "  seperti tingkat pendidikan, masa kerja, beban kerja, dan standar\n"
                "  gaji industri.\n"
                "- Memberikan rekomendasi penyesuaian gaji secara otomatis berdasarkan\n"
                "  hasil analisis kesetaraan.\n"
                "- Menyediakan laporan evaluasi gaji yang dapat digunakan oleh manajemen\n"
                "  untuk pengambilan keputusan strategis terkait kompensasi.\n"
                "- Meningkatkan transparansi internal dalam sistem penggajian untuk\n"
                "  mencegah diskriminasi dan meningkatkan kepuasan kerja.\n\n";

        cout << "MENU:\n"
                "1. List Jabatan dan Range Gaji\n"
                "2. List Data Pegawai\n"
                "3. Program Menghitung Kesenjangan Gaji\n"
                "0. Exit\n\n"
                "Silahkan Pilih Menu Yang Diinginkan (1/2/3/0): ";
        cin >> pilihan;
        cout << "\n\n";

        switch (pilihan) {

            case 1:
                menuCRUDJabatan();      
                break;

            case 2:
                menuCRUDPegawai();          
                break;

            case 3:
                analisisJabatan(dataPegawai);
                break;

            case 0:
                cout << "Terima kasih sudah menggunakan program kami :)" << RESET;
                return 0;

            default:
                cout << RED << "Pilihan tidak valid.\n" << RESET;
        }
    }

    return 0;

}