# Queens Puzzle Solver
> Tugas Kecil 1 IF2211 Strategi Algoritma

## Deskripsi Program
Program ini adalah solver untuk Queens Puzzle, sebuah permainan papan yang bertujuan menempatkan N buah queen pada papan berukuran N×N dengan ketentuan:
- Setiap baris dan kolom hanya boleh memiliki tepat satu queen
- Tidak ada dua queen yang saling bertetangga/adjacent
- Setiap area warna yang berbeda hanya boleh memiliki tepat satu queen

Program ini mengimplementasikan dua pendekatan algoritma:
1. **Pure Brute Force** - Menghasilkan semua permutasi penempatan queen lalu memvalidasi setiap konfigurasi
2. **Backtracking Optimization** - Memvalidasi constraint secara incremental dan melakukan pruning untuk efisiensi yang lebih baik

## Requirements
- **Compiler**: g++ (MinGW untuk Windows, GCC untuk Linux/Mac)
- **C++ Standard**: C++17 atau setelahnya
- **OS**: Windows, Linux, atau macOS
- **Make**: GNU Make (opsional, untuk kompilasi via Makefile)

## Cara Mengkompilasi Program

### Menggunakan Makefile (Recommended)
```bash
make
```

### Manual Compilation
**Windows:**
```bash
mkdir bin
g++ src/main.cpp -o bin/main.exe
```

**Linux/Mac:**
```bash
mkdir -p bin
g++ src/main.cpp -o bin/main
```

## Cara Menjalankan Program

### Setelah Kompilasi dengan Make
Program akan otomatis berjalan setelah kompilasi dengan `make`.

### Manual Execution
**Windows:**
```bash
bin\main.exe
```

**Linux/Mac:**
```bash
./bin/main
```

## Cara Menggunakan Program

1. **Input Test Case**
   - Siapkan file test case dalam format `.txt` di folder `test/`
   - Format file: Grid N×N dengan karakter yang berbeda untuk setiap area warna
   - Contoh file `test/input.txt`:
     ```
     ABCD
     BADC
     CDAB
     DCBA
     ```

2. **Menjalankan Program**
   ```
   Input your test case filename in .txt (e.g. input.txt):
   >> input.txt
   ```

3. **Memilih Algoritma**
   ```
   Choose one of the two algorithms:
   1. Pure Brute-force
   2. Backtrack optimization
   >> 2
   ```

4. **Melihat Hasil**
   - Program akan menampilkan solusi dengan tanda `*` untuk posisi queen
   - Informasi waktu eksekusi dan jumlah iterasi akan ditampilkan
   - Contoh output:
     ```
     AB*D
     *ADC
     CD*B
     DC*A
     ----------
     Program elapsed in 15ms
     A total of 248 cases were checked
     ```

5. **Menyimpan Hasil (Opsional)**
   ```
   Do you want to save the result?
   1. Yes
   2. No
   >> 1
   
   Input your target filename in .txt (e.g. output.txt):
   >> output.txt
   ```
   - File akan disimpan di folder `result/`

## Struktur Folder
```
Tucil1_13524031/
├── src/
│   └── main.cpp          # Source code program
├── test/                 # Folder untuk menyimpan output ketujuh testcase di laporan
│   └── sol1.txt
│   └── sol2.txt
│   └── sol3.txt
│   └── sol4.txt
│   └── sol5.txt
│   └── sol6.txt
│   └── sol7.txt
├── testcase/             # Folder lokal untuk menyimpan testcase
├── result/               # Folder untuk menyimpan jawaban asli testcase
├── bin/                  # Folder hasil kompilasi (dibuat otomatis)
│   └── main.exe
├── doc/                  # Folder dokumentasi laporan
├── Makefile              # Build script
└── README.md             # Dokumentasi ini
```

## Cleaning Build Files
Untuk menghapus file hasil kompilasi:
```bash
make clean
```

## Author
**Nama**: Vincent Rionarlie  
**NIM**: 13524031  
**Program Studi**: Teknik Informatika  
**Institusi**: Institut Teknologi Bandung  
**Mata Kuliah**: IF2211 Strategi Algoritma  
**Tahun**: 2025

## Catatan Tambahan
- Program akan memberikan error jika format file tidak sesuai
- Test case diharapkan menggunakan format non-CRLF, agar asisten Linux tidak kewalahan saat mengecek