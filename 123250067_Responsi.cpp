// Keifa Aditya Kurniawan
// 123250067

#include <iostream>
#include <string>
using namespace std;

struct ListNode {
    int kode;
    string nama;
    ListNode* next;
};
struct TreeNode {
    int kode;
    string nama;
    TreeNode* left;
    TreeNode* right;
};

ListNode* frontQueue = nullptr;
ListNode* rearQueue = nullptr;
ListNode* topHistory = nullptr;
TreeNode* rootOrgan = nullptr;

bool isQueueEmpty() {
    return frontQueue == nullptr;
}
bool isHistoryEmpty() {
    return topHistory == nullptr;
}
bool isOrganEmpty() {
    return rootOrgan == nullptr;
}

void enqueue(int kode, const string& nama) {
    ListNode* newNode = new ListNode;
    newNode->kode = kode;
    newNode->nama = nama;
    newNode->next = nullptr;

    if (isQueueEmpty()) {
        frontQueue = rearQueue = newNode;
    } else {
        rearQueue->next = newNode;
        rearQueue = newNode;
    }
}

bool dequeue(int& kode, string& nama) {
    if (isQueueEmpty()) {
        return false;
    }

    ListNode* temp = frontQueue;
    kode = temp->kode;
    nama = temp->nama;

    frontQueue = frontQueue->next;
    if (frontQueue == nullptr) {
        rearQueue = nullptr;
    }

    delete temp;
    return true;
}
void pushHistory(int kode, const string& nama) {
    ListNode* newNode = new ListNode;
    newNode->kode = kode;
    newNode->nama = nama;
    newNode->next = topHistory;
    topHistory = newNode;
}

bool popHistory(int& kode, string& nama) {
    if (isHistoryEmpty()) {
        return false;
    }

    ListNode* temp = topHistory;
    kode = temp->kode;
    nama = temp->nama;

    topHistory = topHistory->next;
    delete temp;
    return true;
}

TreeNode* insert(TreeNode* root, int kode, const string& nama) {
    if (root == nullptr) {
        TreeNode* newNode = new TreeNode;
        newNode->kode = kode;
        newNode->nama = nama;
        newNode->left = newNode->right = nullptr;
        return newNode;
    }

    if (kode < root->kode) {
        root->left = insert(root->left, kode, nama);
    } else if (kode > root->kode) {
        root->right = insert(root->right, kode, nama);
    }

    return root;
}

TreeNode* search(TreeNode* root, int kode) {
    if (root == nullptr || root->kode == kode) {
        return root;
    }

    if (kode < root->kode) {
        return search(root->left, kode);
    } else {
        return search(root->right, kode);
    }
}

TreeNode* findMin(TreeNode* root) {
    while (root->left != nullptr) {
        root = root->left;
    }
    return root;
}

TreeNode* deleteNode(TreeNode* root, int kode) {
    if (root == nullptr) {
        return root;
    }

    if (kode < root->kode) {
        root->left = deleteNode(root->left, kode);
    } else if (kode > root->kode) {
        root->right = deleteNode(root->right, kode);
    } else {
        if (root->left == nullptr) {
            TreeNode* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            TreeNode* temp = root->left;
            delete root;
            return temp;
        }

        // Node Tanpa anak
        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            return nullptr;
        }

        else if (root->left == nullptr) {
            TreeNode* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            TreeNode* temp = root->left;
            delete root;
            return temp;
        }

        // Node 2 Anak
        TreeNode* temp = findMin(root->right);
        root->kode = temp->kode;
        root->nama = temp->nama;
        root->right = deleteNode(root->right, temp->kode);
    }
    return root;
}

    void preOrder(TreeNode* root, int& nomor) {
        if (root != nullptr) {
            cout << nomor << ". " << root->kode << " - " << root->nama << endl;
            nomor++;
            preOrder(root->left, nomor);
            preOrder(root->right, nomor);
        }
    }

void inOrder(TreeNode* root, int& nomor) {
    if (root != nullptr) {
        inOrder(root->left, nomor);
        cout << nomor << ". " << root->kode << " - " << root->nama << endl;
        nomor++;
        inOrder(root->right, nomor);
    }
}

void postOrder(TreeNode* root, int& nomor) {
    if (root != nullptr) {
        postOrder(root->left, nomor);
        postOrder(root->right, nomor);
        cout << nomor << ". " << root->kode << " - " << root->nama << endl;
        nomor++;
    }
}

bool isKodeExist(TreeNode* root, int kode) {
    if (root == nullptr) {
        return false;
    }
    if (root->kode == kode) {
        return true;
    }
    return isKodeExist(root->left, kode) || isKodeExist(root->right, kode);
}

// 1. Tambahh energi
void tambahEnergi(){
    char lanjut;
    do {
        int kode;
        string nama;

        while (true){
            cout << "Masukkan Kode Organ: ";
            cin >> kode;
            if (kode <= 0) {
                cout << "Kode organ harus lebih dari nol" << endl;
                continue;
            }
            if (isKodeExist(rootOrgan, kode)) {
                cout << "Kode organ sudah ada. Silakan masukkan kode lain." << endl;
                continue;
            }
            break;
        }
        
        while (true){
            cout << "Masukkan Nama Organ: ";
            cin.ignore();
            getline(cin, nama);
            if (nama.empty()) {
                cout << "Nama organ tidak boleh kosong" << endl;
                continue;
            }
            break;
        }

        enqueue(kode, nama);
        cout << "Berhasil memasukkan energi wkwk" << endl;

        while (true) {
            cout << "Apakah ingin menambahkan energi lagi? (y/n): ";
            cin >> lanjut;
            if (lanjut == 'y' || lanjut == 'Y' || lanjut == 'n' || lanjut == 'N') {
                break;
            } else {
                cout << "Input tidak valid. Silakan masukkan 'y' atau 'n'." << endl;
            }

        }

        
    } while (lanjut == 'y' || lanjut == 'Y');
}

//2. Lihat energi dalam antreAN 
void lihatEnergi() {
    if (isQueueEmpty()) {
        cout << "Tidak ada energi dalam antrean." << endl;
        return;
    }

    ListNode* current = frontQueue;
    int nomor = 1;
    cout << "=== Energi dalam Antrean ===" << endl;
    while (current != nullptr) {
        cout << nomor << ". " << current->kode << " - " << current->nama << endl;
        current = current->next;
        nomor++;
    }
}

//3. Prosesss Energi
void prosesEnergi() {
    if (isQueueEmpty()) {
        cout << "Tidak ada energi dalam antrean." << endl;
        return;
    }

    int kode;
    string nama;
    if (dequeue(kode, nama)) {
        rootOrgan = insert(rootOrgan, kode, nama);
        pushHistory(kode, nama);
        cout << "Energi dengan kode " << kode << " dan nama " << nama << " telah diproses yeay." << endl;
    }
}

//4. Lihat energi
void lihatEnergiDiserap() {
    if (isOrganEmpty()) {
        cout << "Tidak ada energi yang sudah terserap." << endl;
        return;
    }

    int nomor = 1;
    cout << "=== Energi yang Telah Diproses ===" << endl;
    preOrder(rootOrgan, nomor);
}

//5. Hapus Riwayat Energi Teratas
 void hapusRiwayatTeratas(){
    if (isOrganEmpty()) {
        cout << "Tidak ada energi yang sudah terserap." << endl;
        return;
    }
    int kode;
    string nama;
    popHistory(kode, nama);
    cout << "Riwayat energi "<< nama << " dihapus";
}

//6. Cari energi
void cariEnergi(){
    if (isOrganEmpty()) {
        cout << "Tidak ada energi yang sudah terserap." << endl;
        return;
    }

    int kode;
    cout << "Masukkan kode energi yang ingin dicari: ";
    if (!(cin >> kode)) {
        cout << "Kode harus berupa angka." << endl;
        cin.clear();
        cin.ignore(1000, '\n');
        return;
    }
    cin.ignore(1000, '\n');

    TreeNode* hasil = search(rootOrgan, kode);
    if (hasil == nullptr) {
        cout << "Energi dengan kode " << kode << " tidak ditemukan." << endl;
    } else {
        cout << "Energi ditemukan: " << hasil->kode << " - " << hasil->nama << endl;
    }
}

//7. Lihat isi Organ
void lihatIsiOrgan() {
    if (rootOrgan == nullptr) {
        cout << "Error: Organ kosong! Belum ada kristal energi di dalam organ.\n";
        return;
    }

    int pilihan;
    cout << "=== Isi Kristal Organ ===\n";
    cout << "1. Pre-order\n";
    cout << "2. In-order\n";
    cout << "3. Post-order\n";
    cout << "Masukkan pilihan: ";

    if (!(cin >> pilihan)) {
        cout << "Error: Pilihan harus berupa angka!\n";
        return;
    }

    int nomor = 1;
    switch (pilihan) {
        case 1:
            preOrder(rootOrgan, nomor);
            break;
        case 2:
            inOrder(rootOrgan, nomor);
            break;
        case 3:
            postOrder(rootOrgan, nomor);
            break;
        default:
            cout << "Error: Pilihan traversal tidak valid!\n";
            break;
    }
}

//8. Gunakan Energi
void gunakanEnergi() {
    if (isOrganEmpty()) {
        cout << "Tidak ada energi yang sudah terserap." << endl;
        return;
    }

    int kode;
    cout << "Masukkan kode energi: ";
    if (!(cin >> kode)) {
        cout << "Kode harus berupa angka." << endl;
        cin.clear();
        cin.ignore(1000, '\n');
        return;
    }
    cin.ignore(1000, '\n');

    TreeNode* hasil = search(rootOrgan, kode);
    if (hasil == nullptr) {
        cout << "Energi dengan kode " << kode << " tidak ditemukan." << endl;
    } else {
        rootOrgan = deleteNode(rootOrgan, kode);
        cout << "Energi dengan kode " << kode << " telah digunakan dan dihapus dari organ." << endl;
    }
}

int main() {
    int pilihan;
    do {
        cout << "\n=== MANAJEMEN ENERGI ORGAN ===" << endl;
        cout << "1. Tambah energi ke antrean" << endl;
        cout << "2. Lihat antrean energi" << endl;
        cout << "3. Proses energi" << endl;
        cout << "4. Lihat energi yang terserap" << endl;
        cout << "5. Hapus riwayat teratas" << endl;
        cout << "6. Cari energi" << endl;
        cout << "7. Lihat isi organ" << endl;
        cout << "8. Gunakan energi" << endl;
        cout << "0. Keluar" << endl;
        cout << "Pilihan: ";

        if (!(cin >> pilihan)) {
            cout << "Pilihan harus berupa angka." << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }
        cin.ignore(1000, '\n');

        switch (pilihan) {
            case 1:
                tambahEnergi();
                break;
            case 2:
                lihatEnergi();
                break;
            case 3:
                prosesEnergi();
                break;
            case 4:
                lihatEnergiDiserap();
                break;
            case 5:
                hapusRiwayatTeratas();
                break;
            case 6:
                cariEnergi();
                break;
            case 7:
                lihatIsiOrgan();
                break;
            case 8:
                gunakanEnergi();
                break;
            case 0:
                cout << "Program selesai." << endl;
                break;
            default:
                cout << "Pilihan tidak tersedia." << endl;
                break;
        }
    } while (pilihan != 0);

    return 0;
}
