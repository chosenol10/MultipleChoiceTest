#ifndef STRUCTS_H
#define STRUCTS_H
#include <iostream>
#include <cstring>
using namespace std;

const int MAX_LOP = 10000;  // Giới hạn số lớp

// =================== CÂU HỎI THI ===================
struct CauHoi {
    int id;             // ID câu hỏi
    char noidung[501];  // Nội dung câu hỏi
    char A[201];
    char B[201];
    char C[201];
    char D[201];
    char dapan;         // Đáp án đúng (A/B/C/D)
};

// Node cho danh sách liên kết câu hỏi
struct NodeCH {
    CauHoi data;
    NodeCH* next;
};
typedef NodeCH* PTRCH;

// =================== MÔN HỌC ===================
struct MonHoc {
    char mamh[16];       // Mã môn học (C15)
    char tenmh[51];      // Tên môn học
    PTRCH FirstCHT = NULL; // Danh sách câu hỏi thi của môn
    int height;          // Chiều cao (phục vụ AVL)
};

// Node cho cây AVL
struct NodeMH {
    MonHoc data;
    NodeMH* left;
    NodeMH* right;
};
typedef NodeMH* PTRMH;

// =================== ĐIỂM THI ===================
struct DiemThi {
    char mamh[16];  // Mã môn học
    float diem;     // Điểm (làm tròn 1 số sau dấu chấm)
};

// Node cho danh sách liên kết điểm thi
struct NodeDiem {
    DiemThi data;
    NodeDiem* next;
};
typedef NodeDiem* PTRDiemThi;

// =================== SINH VIÊN ===================
struct SinhVien {
    char masv[16];       // Mã sinh viên
    char ho[51];         // Họ
    char ten[16];        // Tên
    char phai[4];        // Giới tính
    char password[21];   // Mật khẩu
    PTRDiemThi ds_diemthi = NULL; // Danh sách điểm thi
};

// Node cho danh sách liên kết sinh viên
struct NodeSV {
    SinhVien data;
    NodeSV* next;
};
typedef NodeSV* PTRSV;

// =================== LỚP HỌC ===================
struct Lop {
    char malop[16];      // Mã lớp
    char tenlop[51];     // Tên lớp
    PTRSV FirstSV = NULL;  // Danh sách sinh viên
};

// Danh sách lớp học (mảng con trỏ)
struct DS_Lop {
    int n = 0;
    Lop* nodes[MAX_LOP];
};

#endif
