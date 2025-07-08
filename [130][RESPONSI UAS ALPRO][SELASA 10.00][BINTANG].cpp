#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <algorithm>
using namespace std;

struct Tiket {
    string kode, maskapai, asal, tujuan, tanggal, jam_berangkat, jam_tiba;
    int harga;
};

const int MAKS = 100;
Tiket tiket[MAKS];
int jumlah_tiket = 0;

void bacaData() {
    ifstream file("data_tiket.txt");
    while (file >> tiket[jumlah_tiket].kode >> tiket[jumlah_tiket].maskapai >>
           tiket[jumlah_tiket].asal >> tiket[jumlah_tiket].tujuan >> tiket[jumlah_tiket].tanggal >>
           tiket[jumlah_tiket].jam_berangkat >> tiket[jumlah_tiket].jam_tiba >> tiket[jumlah_tiket].harga) {
        jumlah_tiket++;
    }
    file.close();
}

void tampilkanTiket() {
    cout << "\nDAFTAR TIKET:\n";
    for (int i = 0; i < jumlah_tiket; ++i) {
        cout << tiket[i].kode << " | " << tiket[i].maskapai << " | " << tiket[i].asal << " -> "
             << tiket[i].tujuan << " | " << tiket[i].tanggal << " | "
             << tiket[i].jam_berangkat << " - " << tiket[i].jam_tiba
             << " | Rp" << tiket[i].harga << endl;
    }
}

void cariRute(string asal, string tujuan) {
    cout << "\nTIKET DENGAN RUTE " << asal << " KE " << tujuan << ":\n";
    bool ditemukan = false;
    for (int i = 0; i < jumlah_tiket; ++i) {
        if (tiket[i].asal == asal && tiket[i].tujuan == tujuan) {
            cout << tiket[i].kode << " | " << tiket[i].maskapai << " | Rp" << tiket[i].harga << endl;
            ditemukan = true;
        }
    }
    if (!ditemukan) cout << "Tidak ditemukan.\n";
}

void cariMaskapai(string maskapai) {
    cout << "\nTIKET MASKAPAI " << maskapai << ":\n";
    bool ditemukan = false;
    for (int i = 0; i < jumlah_tiket; ++i) {
        if (tiket[i].maskapai == maskapai) {
            cout << tiket[i].kode << " | " << tiket[i].asal << " ke " << tiket[i].tujuan
                 << " | Rp" << tiket[i].harga << endl;
            ditemukan = true;
        }
    }
    if (!ditemukan) cout << "Tidak ditemukan.\n";
}

void sortHarga(bool ascending) {
    sort(tiket, tiket + jumlah_tiket, [ascending](Tiket a, Tiket b) {
        return ascending ? a.harga < b.harga : a.harga > b.harga;
    });
}

void cariHargaMaksimal(int batas) {
    cout << "\nTIKET DENGAN HARGA DI BAWAH Rp" << batas << ":\n";
    bool ditemukan = false;
    for (int i = 0; i < jumlah_tiket; ++i) {
        if (tiket[i].harga < batas) {
            cout << tiket[i].kode << " | " << tiket[i].maskapai << " | Rp" << tiket[i].harga << endl;
            ditemukan = true;
        }
    }
    if (!ditemukan) cout << "Tidak ada tiket dalam kisaran harga ini.\n";
}

void tampilkanTiketEkstrem(bool termurah) {
    int idx = 0;
    for (int i = 1; i < jumlah_tiket; ++i) {
        if (termurah) {
            if (tiket[i].harga < tiket[idx].harga) idx = i;
        } else {
            if (tiket[i].harga > tiket[idx].harga) idx = i;
        }
    }
    cout << "\nTIKET " << (termurah ? "TERMURAH" : "TERMAHAL") << ":\n";
    cout << tiket[idx].kode << " | " << tiket[idx].maskapai << " | Rp" << tiket[idx].harga << endl;
}

void simpanSorting() {
    ofstream file("hasil_sorting_tiket.txt");
    for (int i = 0; i < jumlah_tiket; ++i) {
        file << tiket[i].kode << " " << tiket[i].maskapai << " " << tiket[i].asal << " "
             << tiket[i].tujuan << " " << tiket[i].tanggal << " " << tiket[i].jam_berangkat << " "
             << tiket[i].jam_tiba << " " << tiket[i].harga << endl;
    }
    file.close();
}

void pesanTiket() {
    string kode, nama_penumpang;
    cout << "\nMasukkan kode penerbangan yang ingin dipesan: ";
    cin >> kode;
    bool ditemukan = false;
    for (int i = 0; i < jumlah_tiket; ++i) {
        if (tiket[i].kode == kode) {
            cout << "Masukkan nama penumpang: ";
            cin.ignore();
            getline(cin, nama_penumpang);
            ofstream file("transaksi_tiket.txt", ios::app);
            file << nama_penumpang << " " << tiket[i].maskapai << " "
                 << tiket[i].asal << "-" << tiket[i].tujuan << " "
                 << tiket[i].tanggal << " " << tiket[i].jam_berangkat
                 << " Rp" << tiket[i].harga << endl;
            file.close();
            cout << "Tiket berhasil dipesan.\n";
            ditemukan = true;
            break;
        }
    }
    if (!ditemukan) cout << "Kode penerbangan tidak ditemukan.\n";
}

int main() {
    bacaData();
    int pilihan;
    do {
        cout << "\n====== MENU APLIKASI TIKET PESAWAT ======\n";
        cout << "1. Tampilkan semua tiket\n";
        cout << "2. Cari berdasarkan rute\n";
        cout << "3. Cari berdasarkan maskapai\n";
        cout << "4. Urutkan tiket termurah ke termahal\n";
        cout << "5. Urutkan tiket termahal ke termurah\n";
        cout << "6. Cari tiket dengan harga di bawah batas tertentu\n";
        cout << "7. Tampilkan tiket termurah/termahal\n";
        cout << "8. Pesan tiket\n";
        cout << "9. Simpan hasil sorting ke file\n";
        cout << "0. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;
        switch (pilihan) {
            case 1: tampilkanTiket(); break;
            case 2: {
                string asal, tujuan;
                cout << "Masukkan asal: "; cin >> asal;
                cout << "Masukkan tujuan: "; cin >> tujuan;
                cariRute(asal, tujuan);
                break;
            }
            case 3: {
                string maskapai;
                cout << "Masukkan maskapai: "; cin >> maskapai;
                cariMaskapai(maskapai);
                break;
            }
            case 4: sortHarga(true); cout << "Tiket diurutkan dari termurah.\n"; break;
            case 5: sortHarga(false); cout << "Tiket diurutkan dari termahal.\n"; break;
            case 6: {
                int batas;
                cout << "Masukkan batas harga: "; cin >> batas;
                cariHargaMaksimal(batas);
                break;
            }
            case 7: {
                int opsi;
                cout << "1. Termurah\n2. Termahal\nPilih: "; cin >> opsi;
                tampilkanTiketEkstrem(opsi == 1);
                break;
            }
            case 8: pesanTiket(); break;
            case 9: simpanSorting(); cout << "Hasil sorting disimpan ke file.\n"; break;
            case 0: cout << "Terima kasih.\n"; break;
            default: cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 0);

    return 0;
}
