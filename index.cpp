#include <iostream>
#include <cstring>
#
using namespace std;

// ======== CẤU TRÚC GỐC (KHÔNG ĐƯỢC THAY ĐỔI) ========
const int MAX_LOP = 10000;

struct CauHoi {
    int id;
    char noidung[501];
    char A[201], B[201], C[201], D[201];
    char dapan;
};
struct NodeCH {
    CauHoi data;
    NodeCH* next;
};
typedef NodeCH* PTRCH;

struct MonHoc {
    char mamh[16];
    char tenmh[51];
    PTRCH FirstCHT = NULL;
    int height;
};
struct NodeMH {
    MonHoc data;
    NodeMH* left;
    NodeMH* right;
};
typedef NodeMH* PTRMH;

struct DiemThi {
    char mamh[16];
    float diem;
};
struct NodeDiem {
    DiemThi data;
    NodeDiem* next;
};
typedef NodeDiem* PTRDiemThi;

struct SinhVien {
    char masv[16];
    char ho[51];
    char ten[16];
    char phai[4];
    char password[21];
    PTRDiemThi ds_diemthi = NULL;
};
struct NodeSV {
    SinhVien data;
    NodeSV* next;
};
typedef NodeSV* PTRSV;

struct Lop {
    char malop[16];
    char tenlop[51];
    PTRSV FirstSV = NULL;
};
struct DS_Lop {
    int n = 0;
    Lop* nodes[MAX_LOP];
};

// ========== TIỆN ÍCH CHUỖI ==========
void trim(char* s) {
    int n = strlen(s), i = 0, j = n - 1;
    while (i < n && (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')) i++;
    while (j >= i && (s[j] == ' ' || s[j] == '\t' || s[j] == '\n')) j--;
    if (i > j) { s[0] = '\0'; return; }
    int k = 0; while (i <= j) s[k++] = s[i++]; s[k] = '\0';
}
void read_line(const char* prompt, char* buf, int cap) {
    cout << prompt;
    cin.getline(buf, cap);
    trim(buf);
}
int cmp_str(const char* a, const char* b) {
    int i = 0; while (a[i] && b[i] && a[i] == b[i]) i++;
    return a[i] - b[i];
}

// ======== TÌM SINH VIÊN TRONG DANH SÁCH ========
SinhVien* findSV(DS_Lop& ds, const char* masv) {
    for (int i = 0; i < ds.n; i++) {
        for (PTRSV p = ds.nodes[i]->FirstSV; p; p = p->next) {
            if (cmp_str(p->data.masv, masv) == 0)
                return &p->data;
        }
    }
    return NULL;
}

// ======== HÀM NHẬP THÔNG TIN LỚP (CHO GV) ========
void nhapLop(DS_Lop& ds) {
    while (true) {
        char malop[16];
        read_line("\nNhap MA LOP (hoac nhap '0' de dung): ", malop, 16);
        if (strcmp(malop, "0") == 0) {
            cout << "=> Da dung nhap lop.\n";
            break;
        }
        char tenlop[51];
        read_line("Nhap TEN LOP: ", tenlop, 51);

        if (ds.n >= MAX_LOP) {
            cout << "=> Vuot gioi han lop toi da!\n";
            return;
        }

        Lop* l = new Lop;
        strcpy(l->malop, malop);
        strcpy(l->tenlop, tenlop);
        l->FirstSV = NULL;
        ds.nodes[ds.n++] = l;

        cout << "=> Da them lop: " << malop << " - " << tenlop << endl;
    }
}

// ======== CÂU A: ĐĂNG NHẬP PHÂN TÁCH GV / SV ========
void dangNhap(DS_Lop& ds, bool& isGV, char masvOut[16]) {
    cout << "\n===== DANG NHAP HE THONG =====\n";
    cout << "1) Dang nhap GIAO VIEN\n";
    cout << "2) Dang nhap SINH VIEN\n";
    cout << "Chon (1/2): ";

    char chon[4];
    cin.getline(chon, 4);

    // ==== ĐĂNG NHẬP GIÁO VIÊN ====
    if (strcmp(chon, "1") == 0) {
        char user[16], pass[21];
        read_line("\nNhap ma GV: ", user, 16);
        read_line("Nhap mat khau: ", pass, 21);

        if (strcmp(user, "GV") == 0 && strcmp(pass, "GV") == 0) {
            isGV = true;
            masvOut[0] = '\0';
            cout << "\n==> Dang nhap thanh cong voi quyen GIAO VIEN!\n";
            cout << "Ban co the nhap thong tin lop duoi day:\n";
            nhapLop(ds);
        } else {
            cout << "==> Sai thong tin GIAO VIEN!\n";
            isGV = false;
            masvOut[0] = '\0';
        }
        return;
    }

    // ==== ĐĂNG NHẬP SINH VIÊN ====
    else if (strcmp(chon, "2") == 0) {
        char ma[16], pass[21];
        read_line("\nNhap ma sinh vien: ", ma, 16);
        read_line("Nhap mat khau: ", pass, 21);

        SinhVien* sv = findSV(ds, ma);
        if (sv && strcmp(sv->password, pass) == 0) {
            isGV = false;
            strcpy(masvOut, ma);
            cout << "==> Dang nhap thanh cong (Sinh vien: " << ma << ")\n";
        } else {
            cout << "==> Sai thong tin dang nhap!\n";
            isGV = false;
            masvOut[0] = '\0';
        }
        return;
    }

    // ==== LỰA CHỌN SAI ====
    else {
        cout << "Lua chon khong hop le!\n";
        isGV = false;
        masvOut[0] = '\0';
    }
}

// ======== MAIN TEST ========
int main() {
    PTRMH treeMH = NULL;
    DS_Lop dslop;

    bool isGV = false;
    char masv[16];

    // Vòng lặp cho phép đăng nhập nhiều lần
    while (true) {
        dangNhap(dslop, isGV, masv);

        char tieptuc[4];
        read_line("\nNhap 'y' de dang nhap lai hoac phim khac de thoat: ", tieptuc, 4);
        if (tieptuc[0] != 'y' && tieptuc[0] != 'Y') {
            cout << "\n==> Ket thuc chuong trinh.\n";
            break;
        }
    }

    return 0;
}
