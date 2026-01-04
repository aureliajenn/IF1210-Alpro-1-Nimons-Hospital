# Rumah Sakit Nimons K01-N
Sistem informasi rumah sakit untuk tugas besar mata kuliah IF1210 Algoritma dan Pemrograman 1 yang dapat digunakan oleh tiga peran utama, yaitu pasien, dokter, dan manajer, dengan fitur autentikasi, manajemen pasien, pengelolaan antrian, serta diagnosis dan pengobatan penyakit.

---

## Daftar Isi
- [Deskripsi](#deskripsi)
- [Struktur Folder](#-struktur-folder)
- [Fitur Utama](#-fitur-utama)
- [Prerequisites & Cara Menjalankan Program](#-prerequisites-dan-cara-menjalankan-program)
- [Kontributor](#-kontributor)

---

## Deskripsi
Sistem informasi rumah sakit digital yang dapat digunakan oleh tiga peran utama, yaitu pasien, dokter, dan manajer. Sistem ini dirancang untuk menangani permasalahan administratif dan medis, mulai dari pendaftaran pasien, pengelolaan antrian, diagnosis otomatis, hingga manajemen data pengguna dan ruangan. Selain itu, sistem juga mampu menyimpan dan memuat data dari file eksternal agar informasi tidak hilang saat program ditutup. Sistem ini mengimplementasikan berbagai konsep dalam Algoritma dan Pemrograman, seperti:

- konsep validasi input, searching, sorting, filtering, dan modularisasi
- struktur data dan ADT (ADT Sederhana, List, Linked List, Set, Queue, Stack, Matrix, dan Map), dan
- manajemen data (file eksternal, dan struktur data dinamis)

---

## Struktur Folder

```
IF1210---ALPRO-1-Nimons-Hospital/
│
├── data/
├── doc/
├── src/
│   ├── Auth/
│   │   ├── auth.c
│   │   └── auth.h
│   ├── DataParser/
│   │   ├── dataParser.c
│   │   └── dataParser.h
│   ├── Label/
│   │   ├── label.c
│   │   └── label.h
│   ├── Laman/
│   │   ├── AntrianSaya/
│   │   │   ├── antriansaya.c
│   │   │   └── antriansaya.h
│   │   ├── CariUser/
│   │   │   ├── cariuser.c
│   │   │   └── cariuser.h
│   │   ├── daftarcheckup/
│   │   │   ├── daftar_checkup.c
│   │   │   └── daftar_checkup.h
│   │   ├── Denah/
│   │   │   ├── denah.c
│   │   │   └── denah.h
│   │   ├── Diagnosis/
│   │   │   ├── diagnosis.c
│   │   │   └── diagnosis.h
│   │   ├── LihatUser/
│   │   │   ├── lihatuser.c
│   │   │   └── lihatuser.h
│   │   ├── MinumObat/
│   │   │   ├── minumobat.c
│   │   │   └── minumobat.h
│   │   ├── Ngobatin/
│   │   │   ├── ngobatin.c
│   │   │   └── ngobatin.h
│   │   ├── PulangDok/
│   │   │   ├── pulangdok.c
│   │   │   └── pulangdok.h
│   │   ├── TambahDokter/
│   │   │   ├── tambahdokter.c
│   │   │   └── tambahdokter.h
│   │   ├── dokter.c
│   │   ├── dokter.h
│   │   ├── manager.c
│   │   ├── manager.h
│   │   ├── pasien.c
│   │   └── pasien.h
│   ├── Model/
│   │   └── model.h
│   └── Utils/
│   │   ├── ADT/
│   │   │   ├── map.c
│   │   │   ├── map.h
│   │   │   ├── queue.c
│   │   │   ├── queue.h
│   │   │   ├── stack.c
│   │   │   └── stack.h
│   │   ├── Boolean.h
│   │   ├── help.c
│   │   ├── help.h
│   │   ├── load.c
│   │   ├── load.h
│   │   ├── save.c
│   │   ├── save.h
│   │   ├── utils.c
│   │   └── utils.h
├── main.c
├── main.h
├── makefile
└── README.md

```

---

## Fitur Utama

| ID | Fitur | Status |
|:--:|:------|:------:|
| F00 | Rencana Implementasi | ✅ |
| F01 | Login | ✅ |
| F02 | Register Pasien | ✅ |
| F03 | Logout | ✅ |
| F04 | Lupa Password | ✅ |
| F05 | Menu & Help | ✅ |
| F06 | Denah Rumah Sakit | ✅ |
| F07 | Lihat User | ✅ |
| F08 | Cari User | ✅ |
| F09 | Lihat Antrian | ✅ |
| F10 | Tambah Dokter | ✅ |
| F11 | Diagnosis | ✅ |
| F12 | Ngobatin | ✅ |
| F13 | Aku boleh pulang ga dok? | ✅ |
| F14 | Dokter Check-Up | ✅ |
| F15 | Antrian Sayai | ✅ |
| F16 | Minum Obat | ✅ |
| F17 | Minum Penawar | ✅ |
| F18 | Exit | ✅ |
| D01 | Denah Rumah Sakit | ✅ |
| D02 | Lihat Antrian | ✅ |
| D03 | Load Data | ✅ |
| D04 | Save Data | ✅ |

---

## Prerequisites dan Cara Menjalankan Program

### Prerequisites
- **Compiler**: GCC (GNU C Compiler)
- **Build Tool**: Make
- **OS**: Linux/Unix/MacOS/Windows (with MinGW/WSL for Windows)

Untuk Windows, Anda bisa menggunakan:
- **MinGW**: https://www.mingw-w64.org/
- **WSL (Windows Subsystem for Linux)**: Recommended untuk pengalaman Linux di Windows

### Cara Menjalankan

#### 1. **Compile menggunakan Make**

Buka terminal/command prompt di folder project root, kemudian jalankan:

```bash
make clean
make
```

**Penjelasan:**
- `make clean` → Menghapus build sebelumnya
- `make` → Mengcompile semua file C menjadi executable

#### 2. **Menjalankan Program**

Setelah compile berhasil, jalankan program dengan:

**Linux/MacOS:**
```bash
./build/final_program
```

**Windows (Command Prompt):**
```bash
.\build\final_program
```

**Windows (PowerShell):**
```powershell
./build/final_program
```

#### 3. **Membersihkan Build (Opsional)**

Untuk menghapus file hasil compile:

```bash
make clean
```

## 👥Kontributor
**Anggota Tim:**
| NIM | Nama |
|:--:|:------|
| 13524007 | Muhammad Ashkar |
| 13524053 | Muhammad Haris Putra S. |
| 13524089 | Aurelia Jennifer Gunawan |
| 13524119 | Nathanael Shane Bennet |
| 13524123 | Yuhan Fanzuri Nizar |
| 13524127 | Fazri Arrashyi Putra |