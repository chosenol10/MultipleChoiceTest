#include "lop_sv.h"

// ========== HÀM XỬ LÝ CHUỖI ==========
void trimAllSpace(char* s) {
    int start = 0;
    while (isspace(s[start])) start++;
    int end = strlen(s) - 1;
    while (end >= start && isspace(s[end])) end--;
    int len = end - start + 1;
    memmove(s, s + start, len);
    s[len] = '\0';
}

// ========== NHẬP LỚP ==========
void nhapLop(DS_Lop &ds) {
    if (ds.n >= MAX_LOP) {
        cout << "Danh sach lop da day!\n";
        return;
    }

    Lop *lop = new Lop;
    cout << "Nhap ma lop: ";
    cin.ignore();
    cin.getline(lop->malop, 16);
    trimAllSpace(lop->malop);

    // Kiểm tra trùng mã lớp
    for (int i = 0; i < ds.n; i++) {
        if (strcmp(ds.nodes[i]->malop, lop->malop) == 0) {
            cout << "Ma lop da ton tai! Nhap lai.\n";
            delete lop;
            return;
        }
    }

    cout << "Nhap ten lop: ";
    cin.getline(lop->tenlop, 51);
    trimAllSpace(lop->tenlop);

    lop->FirstSV = NULL;
    ds.nodes[ds.n++] = lop;
    cout << "Them lop thanh cong!\n";
}

// ========== IN DANH SÁCH LỚP ==========
void inDanhSachLop(const DS_Lop &ds) {
    cout << "\n===== DANH SACH LOP =====\n";
    if (ds.n == 0) {
        cout << "Danh sach rong!\n";
        return;
    }

    for (int i = 0; i < ds.n; i++) {
        cout << i + 1 << ". " << ds.nodes[i]->malop
             << " - " << ds.nodes[i]->tenlop << endl;
    }
}

// ========== GHI FILE ==========
void ghiFileLop(const DS_Lop &ds) {
    ofstream file("lop.txt");
    if (!file.is_open()) {
        cout << "Khong the mo file lop.txt de ghi!\n";
        return;
    }

    for (int i = 0; i < ds.n; i++) {
        file << ds.nodes[i]->malop << "," << ds.nodes[i]->tenlop << endl;
    }

    file.close();
    cout << "Da luu danh sach lop vao file lop.txt!\n";
}

// ========== ĐỌC FILE ==========
void docFileLop(DS_Lop &ds) {
    ifstream file("lop.txt");
    if (!file.is_open()) {
        cout << "Khong tim thay file lop.txt!\n";
        return;
    }

    ds.n = 0;
    char line[100];
    while (file.getline(line, 100)) {
        if (strlen(line) == 0) continue;
        Lop *lop = new Lop;
        char *token = strtok(line, ",");
        if (token) {
            strcpy(lop->malop, token);
            trimAllSpace(lop->malop);
        }

        token = strtok(NULL, ",");
        if (token) {
            strcpy(lop->tenlop, token);
            trimAllSpace(lop->tenlop);
        }

        lop->FirstSV = NULL;
        ds.nodes[ds.n++] = lop;
    }

    file.close();
    cout << "Da doc danh sach lop tu file lop.txt!\n";
}
