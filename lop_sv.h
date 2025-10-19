#ifndef LOP_SV_H
#define LOP_SV_H
#include "structs.h"
#include <fstream>
#include <iostream>
#include <cstring>
using namespace std;

// Hàm tiện ích
void trimAllSpace(char* s);

// Quản lý lớp
void nhapLop(DS_Lop &ds);
void inDanhSachLop(const DS_Lop &ds);
void ghiFileLop(const DS_Lop &ds);
void docFileLop(DS_Lop &ds);

#endif
