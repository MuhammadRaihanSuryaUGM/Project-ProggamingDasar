#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "MenuUI.h"
using namespace std;

void MenuUI::tampilMenu() {
    cout << "\n=== MENU INVENTORY ===\n";
    cout << "1. Tampilkan Data\n";
    cout << "2. Tambah Barang\n";
    cout << "3. Barang Keluar\n";
    cout << "4. Ubah Barang\n";
    cout << "5. Hapus Barang\n";
    cout << "6. Import Data\n";
    cout << "7. Exit\n";
    cout << "Pilih: ";
}

void MenuUI::tampilImportFile(string file) {
    ifstream in(file);
    if (!in) {
        cout << "\nError: File tidak ditemukan: " << file << "\n";
        return;
    }

    cout << "\n=== ISI FILE IMPORT ===\n";
    cout << left << setw(5) << "ID" << setw(10) << "KODE" << setw(20) << "NAMA" 
         << setw(15) << "KATEGORI" << setw(10) << "STOK" << endl;
    cout << string(60, '-') << endl;

    string line;
    getline(in, line);  // Skip header
    
    while (getline(in, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string idStr, kode, nama, kategori, stokStr;

        try {
            getline(ss, idStr, '|');
            getline(ss, kode, '|');
            getline(ss, nama, '|');
            getline(ss, kategori, '|');
            getline(ss, stokStr);

            cout << left << setw(5) << idStr 
                 << setw(10) << kode 
                 << setw(20) << nama 
                 << setw(15) << kategori
                 << setw(10) << stokStr << endl;
        } catch (...) {
            cout << "Warning: Baris tidak valid: " << line << "\n";
        }
    }
    cout << endl;
    in.close();
}

void MenuUI::jalankan() {
    int pilih;
    filemgr.loadData("data/inventory.txt", manager.getData());
    manager.setLastId(filemgr.loadLastId());

    while (true) {
        tampilMenu();
        cin >> pilih;
        cin.ignore();  // Bersihkan newline dari buffer input

        switch (pilih) {
        case 1: manager.tampilData(); break;
        case 2: manager.tambahBarang(); break;
        case 3: manager.keluarkanBarang(); break;
        case 4: manager.ubahBarang(); break;
        case 5: manager.hapusBarang(); break;
        case 6: 
            tampilImportFile("data/import.txt");
            filemgr.importData("data/import.txt", manager.getData()); 
            break;
        case 7: return;
        }
    }
}
