#include "../../include/common.h"
#include <string>
using namespace std;

string formatRupiahBaru(int angka) {
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