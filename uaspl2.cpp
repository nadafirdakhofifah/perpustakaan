#include <iostream>
#include <string>

using namespace std;

struct Buku {
    string kode_buku;
    string judul;
    string penulis;
    string penerbit;
    int jumlah_stok;
    Buku* next;
};

Buku* head = nullptr;
Buku* tail = nullptr;

bool cariBuku(string kode, Buku*& bukuDitemukan) {
    Buku* current = head;
    while (current != nullptr) {
        if (current->kode_buku == kode) {
            bukuDitemukan = current;
            return true;
        }
        current = current->next;
    }
    return false;
}

void tambahBuku() {
    Buku* buku_baru = new Buku;
    cout << "Masukkan Kode Buku: "; cin >> buku_baru->kode_buku;
    Buku* temp;

    if (cariBuku(buku_baru->kode_buku, temp)) {
        cout << "\nKode buku sudah ada. Gagal menambahkan buku." << endl;
        delete buku_baru;
        return;
    }

    cin.ignore();
    // Validasi judul buku
    do {
        cout << "Masukkan Judul Buku: "; getline(cin, buku_baru->judul);
        if (buku_baru->judul.length() < 4) {
            cout << "Judul buku harus terdiri dari minimal 4 karakter. Silakan coba lagi." << endl;
        }
    } while (buku_baru->judul.length() < 4);

    cout << "Masukkan Penulis Buku: "; getline(cin, buku_baru->penulis);
    cout << "Masukkan Penerbit Buku: "; getline(cin, buku_baru->penerbit);
    cout << "Masukkan Jumlah Stok Buku: "; cin >> buku_baru->jumlah_stok;

    buku_baru->next = head; // Menyisipkan buku baru di depan
    head = buku_baru; // Buku baru menjadi head
    if (tail == nullptr) { // Jika ini buku pertama, tail juga harus menunjuk ke buku tersebut
        tail = buku_baru;
    }

    cout << "\nBuku '" << buku_baru->judul << "' berhasil ditambahkan." << endl;
}

void ubahBuku() {
    string kode;
    cout << "Masukkan kode buku yang ingin diubah: "; cin >> kode;

    Buku* bukuDitemukan;
    if (!cariBuku(kode, bukuDitemukan)) {
        cout << "Buku dengan kode tersebut tidak ditemukan." << endl;
        return;
    }

    cin.ignore();
    cout << "Masukkan Judul Buku Baru: "; getline(cin, bukuDitemukan->judul);
    cout << "Masukkan Penulis Buku Baru: "; getline(cin, bukuDitemukan->penulis);
    cout << "Masukkan Penerbit Buku Baru: "; getline(cin, bukuDitemukan->penerbit);
    cout << "Masukkan Jumlah Stok Buku Baru: "; cin >> bukuDitemukan->jumlah_stok;
    cout << "\nData buku berhasil diubah." << endl;
}

void hapusBuku() {
    string kode;
    cout << "Masukkan kode buku yang ingin dihapus: "; cin >> kode;

    Buku* current = head;
    Buku* previous = nullptr;

    while (current != nullptr && current->kode_buku != kode) {
        previous = current;
        current = current->next;
    }

    if (current == nullptr) {
        cout << "Buku dengan kode tersebut tidak ditemukan." << endl;
        return;
    }

    if (current == head) {
        head = head->next;
        if (head == nullptr) {
            tail = nullptr;
        }
    } else {
        previous->next = current->next;
        if (current == tail) {
            tail = previous;
        }
    }

    cout << "\nBuku '" << current->judul << "' berhasil dihapus." << endl;
    delete current;
}

void peminjamanBuku() {
    string kode;
    cout << "Masukkan kode buku yang ingin dipinjam: "; cin >> kode;

    Buku* bukuDitemukan;
    if (!cariBuku(kode, bukuDitemukan)) {
        cout << "Buku dengan kode tersebut tidak ditemukan." << endl;
        return;
    }

    if (bukuDitemukan->jumlah_stok > 0) {
        bukuDitemukan->jumlah_stok--;
        cout << "\nBuku '" << bukuDitemukan->judul << "' berhasil dipinjam." << endl;
    } else {
        cout << "\nStok buku habis. Tidak dapat meminjam buku ini." << endl;
    }
}

void pengembalianBuku() {
    string kode;
    cout << "Masukkan kode buku yang ingin dikembalikan: "; cin >> kode;

    Buku* bukuDitemukan;
    if (!cariBuku(kode, bukuDitemukan)) {
        cout << "Buku dengan kode tersebut tidak ditemukan." << endl;
        return;
    }

    bukuDitemukan->jumlah_stok++;
    cout << "\nBuku '" << bukuDitemukan->judul << "' berhasil dikembalikan." << endl;
}

void cariBukuJudul() {
    string keyword;
    cout << "Masukkan sebagian judul buku yang ingin dicari: ";
    cin.ignore();
    getline(cin, keyword);

    Buku* current = head;
    int count = 0;

    while (current != nullptr) {
        if (current->judul.find(keyword) != string::npos) {
            count++;
            cout << "\nBuku ditemukan:\n";
            cout << "+-------------------------------------------+\n";
            cout << "Kode Buku   : " << current->kode_buku << endl;
            cout << "Judul       : " << current->judul << endl;
            cout << "Penulis     : " << current->penulis << endl;
            cout << "Penerbit    : " << current->penerbit << endl;
            cout << "Jumlah Stok : " << current->jumlah_stok << endl;
            cout << "+-------------------------------------------+\n";
        }
        current = current->next;
    }

    if (count == 0) {
        cout << "\nTidak ada buku yang ditemukan dengan kata kunci '" << keyword << "'." << endl;
    } else {
        cout << "\nJumlah buku ditemukan: " << count << endl;
    }
}

void tampilkanHeader() {
    cout << "\n===============================================================================\n";
    cout << "                    Selamat Datang di Perpustakaan Naa 2024!\n";
    cout << "                          \"Mari utamakan membaca!\"\n";
    cout << "                   Siap untuk mendapatkan ilmu baru hari ini?\n";
    cout << "===============================================================================\n";
}

void tampilkanBuku(Buku* current) {
    if (current == nullptr) {
        return;
    }

    static int indeks = 1;
    cout << "\nBuku " << indeks++ << ":\n";
    cout << "+-------------------------------------------+\n";
    cout << "Kode Buku   : " << current->kode_buku << endl;
    cout << "Judul       : " << current->judul << endl;
    cout << "Penulis     : " << current->penulis << endl;
    cout << "Penerbit    : " << current->penerbit << endl;
    cout << "Jumlah Stok : " << current->jumlah_stok << endl;
    cout << "+-------------------------------------------+\n";

    tampilkanBuku(current->next);
}

int main() {
    int pilihan;

    tampilkanHeader();

    do {
        cout << "\n+-----------------------------------------------------------------------------+\n";
        cout << "|                          === Menu Perpustakaan ===                          |"<< endl;
        cout << "+-----------------------------------------------------------------------------+\n";
        cout << "|  1. Tambah Buku                                                             |" << endl;
        cout << "|  2. Ubah Buku                                                               |" << endl;
        cout << "|  3. Hapus Buku                                                              |" << endl;
        cout << "|  4. Tampilkan Buku                                                          |" << endl;
        cout << "|  5. Pinjam Buku                                                             |" << endl;
        cout << "|  6. Kembalikan Buku                                                         |" << endl;
        cout << "|  7. Cari Buku Berdasarkan Judul                                             |" << endl;
        cout << "|  8. Keluar                                                                  |" << endl;
        cout << "+-----------------------------------------------------------------------------+\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tambahBuku();
                break;
            case 2:
                ubahBuku();
                break;
            case 3:
                hapusBuku();
                break;
            case 4:
                if (head == nullptr) {
                    cout << "\nBelum ada buku dalam perpustakaan." << endl;
                } else {
                    tampilkanBuku(head);
                }
                break;
            case 5:
                peminjamanBuku();
                break;
            case 6:
                pengembalianBuku();
                break;
            case 7:
                cariBukuJudul();
                break;
            case 8:
                cout << "\nTerima kasih telah menggunakan sistem perpustakaan." << endl;
                break;
            default:
                cout << "\nPilihan tidak valid!" << endl;
                break;
        }
    } while (pilihan != 8);

    return 0;
}

