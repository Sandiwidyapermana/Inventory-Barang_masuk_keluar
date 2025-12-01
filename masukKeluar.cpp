#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <iomanip>

using namespace std;

struct Barang {
    string nama{};
    int kuantitas{ 0 };
    double hargaBeli{ 0.0 };
};

struct Transaksi {
    string namaBarang{};
    int jumlahJual{ 0 };
    double hargaBeliSatuan{ 0.0 };
    double hargaJualSatuan{ 0.0 };
    double subtotalJual{ 0.0 };
    double subtotalBeli{ 0.0 };
};

void tambahBarang(vector<Barang>& inventaris) {
    Barang baru;
    cout << "\n--- TAMBAH BARANG (BARANG MASUK) ---\n";
    cout << "Masukkan Nama Barang : ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, baru.nama);
    cout << "Masukkan Jumlah Barang (Stok) : ";
    while (!(cin >> baru.kuantitas) || baru.kuantitas <= 0) {
        cout << "Input tidak valid. Masukkan angka positif untuk barang masuk : ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cout << "Masukkan Harga Beli Satuan : Rp ";
    while (!(cin >> baru.hargaBeli) || baru.hargaBeli <= 0) {
        cout << "Input tidak valid. Masukkan angka positif untuk harga : Rp ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    inventaris.push_back(baru);
    cout << "\nBarang '" << baru.nama << "' Berhasil ditambahkan ke inventaris!\n";
}

void prosesPenjualan(vector<Barang>& inventaris, vector<Transaksi>& riwayat) {
    if (inventaris.empty()) {
        cout << "\nTidak bisa melakukan penjualan. Inventaris kosong!\n";
        return;
    }

    cout << "\n=== DAFTAR BARANG YANG TERSEDIA ===\n";
    cout << "----------------------------------------------\n";
    cout << "No | Nama Barang        | Stok      | Harga Beli Satuan \n";
    cout << "----------------------------------------------\n";
    for (size_t i = 0; i < inventaris.size(); ++i) {
        cout << i + 1 << ". | ";
        cout.width(18); cout << left << inventaris[i].nama;
        cout << " | ";
        cout.width(9); cout << right << inventaris[i].kuantitas;
        cout << " | Rp";
        cout.width(14); cout << right << fixed << setprecision(0) << inventaris[i].hargaBeli << "\n";
    }
    cout << "----------------------------------------------\n";


    int nomor;
    cout << "\n--- TRANSAKSI PENJUALAN (BARANG KELUAR) ---\n";
    cout << "Masukkan Nomor Barang yang dijual (1-" << inventaris.size() << "): ";
    while (!(cin >> nomor) || nomor < 1 || (size_t)nomor > inventaris.size()) {
        cout << "Nomor barang tidak valid. Masukkan nomor yang benar : ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    Barang& barangDijual = inventaris[nomor - 1];
    int jumlah;
    cout << "Masukkan Jumlah Jual (Maksimal : " << barangDijual.kuantitas << ") : ";
    while (!(cin >> jumlah) || jumlah <= 0 || jumlah > barangDijual.kuantitas) {
        cout << "Jumlah jual tidak valid atau melebihi stok. Masukkan angka positif (Max " << barangDijual.kuantitas << ") : ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    double hargaJualSatuan;
    cout << "Masukkan Harga Jual Satuan : Rp ";
    while (!(cin >> hargaJualSatuan) || hargaJualSatuan <= 0) {
        cout << "Harga jual tidak valid. Masukkan angka positif : Rp ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    Transaksi penjualanBaru;
    penjualanBaru.namaBarang = barangDijual.nama;
    penjualanBaru.jumlahJual = jumlah;
    penjualanBaru.hargaBeliSatuan = barangDijual.hargaBeli;
    penjualanBaru.hargaJualSatuan = hargaJualSatuan;
    penjualanBaru.subtotalJual = jumlah * hargaJualSatuan;
    penjualanBaru.subtotalBeli = jumlah * barangDijual.hargaBeli;
    riwayat.push_back(penjualanBaru);

    barangDijual.kuantitas -= jumlah;

    cout << "\nPenjualan " << jumlah << " " << barangDijual.nama << " Berhasil dicatat!\n";
    cout << "Total Penjualan : Rp " << fixed << setprecision(0) << penjualanBaru.subtotalJual << "\n";
    cout << "Stok tersisa untuk " << barangDijual.nama << ": " << barangDijual.kuantitas << "\n";
}

void tampilkanLaporan(const vector<Barang>& inventaris, const vector<Transaksi>& riwayat) {

    cout << "\n======================================\n";
    cout << "  LAPORAN INVENTARIS STOK SAAT INI\n";
    cout << "======================================\n";

    if (inventaris.empty()) {
        cout << "\nInventaris kosong.\n";
    }
    else {
        double totalNilaiInventaris = 0.0;
        cout << "--------------------------------------------------------\n";
        cout << "No | Nama Barang        | Stok      | Harga Beli Satuan | Nilai Stok \n";
        cout << "--------------------------------------------------------\n";
        for (size_t i = 0; i < inventaris.size(); ++i) {
            double nilaiStok = inventaris[i].kuantitas * inventaris[i].hargaBeli;
            totalNilaiInventaris += nilaiStok;

            cout << fixed << setprecision(0);
            cout << i + 1 << ". | ";
            cout.width(18); cout << left << inventaris[i].nama;
            cout << " | ";
            cout.width(9); cout << right << inventaris[i].kuantitas;
            cout << " | Rp ";
            cout.width(14); cout << right << inventaris[i].hargaBeli;
            cout << " | Rp ";
            cout.width(8); cout << right << nilaiStok << "\n";
        }
        cout << "--------------------------------------------------------\n";
        cout << "               TOTAL NILAI STOK INVENTARIS : Rp " << totalNilaiInventaris << "\n";
        cout << "--------------------------------------------------------\n";
    }

    cout << "\n======================================================\n";
    cout << "  LAPORAN RIWAYAT PENJUALAN DAN LABA KOTOR\n";
    cout << "======================================================\n";

    if (riwayat.empty()) {
        cout << "\nBelum ada transaksi penjualan yang tercatat.\n";
        return;
    }

    double totalPenjualan = 0.0;
    double totalHPP = 0.0;

    cout << "----------------------------------------------------------------------------------\n";
    cout << "No | Nama Barang        | Jml | H. Beli/Sat | H. Jual/Sat | Subtotal Jual | Subtotal Beli \n";
    cout << "----------------------------------------------------------------------------------\n";
    for (size_t i = 0; i < riwayat.size(); ++i) {
        totalPenjualan += riwayat[i].subtotalJual;
        totalHPP += riwayat[i].subtotalBeli;

        cout << fixed << setprecision(0);
        cout << i + 1 << ". | ";
        cout.width(18); cout << left << riwayat[i].namaBarang;
        cout << " | ";
        cout.width(3); cout << right << riwayat[i].jumlahJual;
        cout << " | Rp ";
        cout.width(8); cout << right << riwayat[i].hargaBeliSatuan;
        cout << " | Rp ";
        cout.width(8); cout << right << riwayat[i].hargaJualSatuan;
        cout << " | Rp ";
        cout.width(10); cout << right << riwayat[i].subtotalJual;
        cout << " | Rp ";
        cout.width(10); cout << right << riwayat[i].subtotalBeli << "\n";
    }
    cout << "----------------------------------------------------------------------------------\n";

    double labaKotor = totalPenjualan - totalHPP;

    cout << "TOTAL PENDAPATAN (PENJUALAN) : Rp " << totalPenjualan << "\n";
    cout << "TOTAL HPP (HARGA POKOK PENJUALAN) : Rp " << totalHPP << "\n";
    cout << "----------------------------------------------------------------------------------\n";

    if (labaKotor >= 0) {
        cout << "LABA KOTOR TOTAL : Rp " << labaKotor << "\n";
    }
    else {
        cout << "RUGI KOTOR TOTAL : Rp " << labaKotor << "\n";
    }
    cout << "----------------------------------------------------------------------------------\n";
}

int main() {
    vector<Barang> inventaris;
    vector<Transaksi> riwayatTransaksi;
    int pilihan;

    do {
        cout << "\n======================================\n";
        cout << "  SISTEM KASIR TOKO (UAS C++)\n";
        cout << "======================================\n";
        cout << "1. Tambah Barang ke Inventaris (Barang Masuk)\n";
        cout << "2. Proses Penjualan (Barang Keluar)\n";
        cout << "3. Tampilkan Laporan Keuangan (Stok & Laba/Rugi)\n";
        cout << "4. Keluar\n";
        cout << "--------------------------------------\n";
        cout << "Pilih menu (1-4): ";

        if (!(cin >> pilihan)) {
            cout << "\nInput tidak valid. Mohon masukkan angka!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            pilihan = 0;
            continue;
        }

        switch (pilihan) {
        case 1:
            tambahBarang(inventaris);
            break;
        case 2:
            prosesPenjualan(inventaris, riwayatTransaksi);
            break;
        case 3:
            tampilkanLaporan(inventaris, riwayatTransaksi);
            break;
        case 4:
            cout << "\nTerima kasih! Sistem kasir dimatikan.\n";
            break;
        default:
            cout << "\nPilihan tidak valid! Mohon masukkan angka 1 sampai 4.\n";
        }

    } while (pilihan != 4);

    return 0;
}