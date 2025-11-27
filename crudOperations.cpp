// crudOperations.cpp
// Implementasi operasi CRUD dengan vector

#include "inventory.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <algorithm>

using namespace std;

void inventory::tambahdata(vector<inventory> &data){
    string kode, nama, kat;
    int stokMasuk;

    cout << "Kode Barang  : ";
    getline(cin, kode);
    cout << "Nama Barang  : ";
    getline(cin, nama);
    cout << "Kategori     : ";
    getline(cin, kat);
    cout << "Stok Masuk   : ";
    cin >> stokMasuk;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Cek apakah barang sudah ada
    for (auto &item : data){
        if (item.getKode() == kode || item.getNama() == nama){
            cout << "\nBarang sudah ada. Menambahkan stok...\n";
            item.setStok(item.getStok() + stokMasuk);
            return;
        }
    }

    // Barang baru
    int newId = data.empty() ? 1 : data.back().getId() + 1;
    data.push_back(inventory(newId, kode, nama, kat, stokMasuk));
    cout << "\nBarang baru berhasil ditambahkan!\n";
}

void inventory::keluarbarang(vector<inventory> &data){
    int itemId, jumlahKeluar;

    cout << "ID Barang    : ";
    cin >> itemId;
    cout << "Stok Keluar  : ";
    cin >> jumlahKeluar;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Cari barang berdasarkan ID
    auto it = find_if(data.begin(), data.end(), 
                      [itemId](const inventory &item){ return item.getId() == itemId; });

    if (it == data.end()){
        cout << "ID tidak valid. Barang tidak ditemukan.\n";
        return;
    }

    if (it->getStok() < jumlahKeluar){
        cout << "GAGAL: Stok tidak mencukupi. Stok saat ini: " << it->getStok() << "\n";
        return;
    }

    it->setStok(it->getStok() - jumlahKeluar);
    cout << "\nStok berhasil dikurangi! Sisa stok: " << it->getStok() << "\n";
}

void inventory::TampilData(const vector<inventory> &data){
    if (data.empty()){
        cout << "(Tidak ada data inventory)\n";
        return;
    }

    cout << left << setw(5) << "NO"
         << setw(5) << "ID"
         << setw(10) << "KODE"
         << setw(20) << "NAMA"
         << setw(15) << "KATEGORI"
         << setw(6) << "STOK" << right << "\n";
    cout << string(61, '-') << "\n";

    int no = 1;
    for (const auto &item : data){
        cout << left << setw(5) << no++
             << setw(5) << item.getId()
             << setw(10) << item.getKode()
             << setw(20) << item.getNama()
             << setw(15) << item.getKategori()
             << setw(6) << item.getStok() << right << "\n";
    }
}

void inventory::UbahData(vector<inventory> &data){
    int id;
    cout << "Ubah data ID : ";
    cin >> id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    auto it = find_if(data.begin(), data.end(), 
                      [id](const inventory &item){ return item.getId() == id; });

    if (it == data.end()){
        cout << "ID tidak valid.\n";
        return;
    }

    string kode, nama, kat;
    int stok;

    cout << "Kode Barang  : ";
    getline(cin, kode);
    cout << "Nama Barang  : ";
    getline(cin, nama);
    cout << "Kategori     : ";
    getline(cin, kat);
    cout << "Stok         : ";
    cin >> stok;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    *it = inventory(id, kode, nama, kat, stok);
    cout << "\nData berhasil diubah!\n";
}

void inventory::HapusData(vector<inventory> &data){
    int id;
    cout << "Pilih data ID yang dihapus : ";
    cin >> id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    auto it = find_if(data.begin(), data.end(), 
                      [id](const inventory &item){ return item.getId() == id; });

    if (it == data.end()){
        cout << "ID tidak valid.\n";
        return;
    }

    data.erase(it);
    
    // Re-assign ID secara berurutan
    int newId = 1;
    for (auto &item : data){
        item.setId(newId++);
    }

    cout << "\nData berhasil dihapus!\n";
}