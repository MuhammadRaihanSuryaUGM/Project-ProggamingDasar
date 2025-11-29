#ifndef INVENTORYMANAGER_H
#define INVENTORYMANAGER_H

#include <vector>
#include "Barang.h"
#include "FileManager.h"
using namespace std;

class InventoryManager {
private:
    vector<Barang> data;
    FileManager filemgr;
    int lastId;
    
    int getNextId();

public:
    vector<Barang>& getData() {
        return data;
    }
    
    void setLastId(int id) {
        lastId = id;
    }

    void tampilData();

    void tambahBarang();
    void keluarkanBarang();
    void ubahBarang();
    void hapusBarang();
};

#endif
