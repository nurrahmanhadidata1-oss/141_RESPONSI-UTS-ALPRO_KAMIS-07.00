#include <iostream>
#include <fstream>
using namespace std;

struct Mahasiswa {
    string nim;
    string nama;
    float tugas, uts, uas;
    float nilaiAkhir;
    char grade;
};

float hitungNilai(float arr[], int n) {
    if (n == 1)
        return arr[0];
    else
        return arr[n-1] + hitungNilai(arr, n-1);
}

char tentukanGrade(float nilai) {
    if (nilai >= 85)
        return 'A';
    else if (nilai >= 70)
        return 'B';
    else if (nilai >= 60)
        return 'C';
    else if (nilai >= 50)
        return 'D';
    else
        return 'E';
}

int cariNIM(Mahasiswa mhs[], int n, string nim) {
    for (int i = 0; i < n; i++) {
        if (mhs[i].nim == nim)
            return i;
    }
    return -1;
}

int cariTerendah(Mahasiswa mhs[], int n) {
    int idx = 0;
    for (int i = 1; i < n; i++) {
        if (mhs[i].nilaiAkhir < mhs[idx].nilaiAkhir)
            idx = i;
    }
    return idx;
}

float rataRata(Mahasiswa mhs[], int n) {
    float total = 0;
    for (int i = 0; i < n; i++) {
        total += mhs[i].nilaiAkhir;
    }
    return total / n;
}

int main() {
    Mahasiswa mhs[100];
    int n = 0;

    ifstream file("data.txt");

    if (!file) {
        cout << "File tidak ditemukan!\n";
        return 0;
    }

    while (file >> mhs[n].nim >> mhs[n].nama 
                >> mhs[n].tugas >> mhs[n].uts >> mhs[n].uas) {
        
        float nilai[3] = {
            0.3 * mhs[n].tugas,
            0.3 * mhs[n].uts,
            0.4 * mhs[n].uas
        };

        mhs[n].nilaiAkhir = hitungNilai(nilai, 3);
        mhs[n].grade = tentukanGrade(mhs[n].nilaiAkhir);
        n++;
    }

    file.close();

    string cari;
    cout << "Masukkan NIM yang dicari: ";
    cin >> cari;

    int idx = cariNIM(mhs, n, cari);

    if (idx != -1) {
        cout << "\nData ditemukan:\n";
        cout << mhs[idx].nim << " "
             << mhs[idx].nama << " "
             << mhs[idx].nilaiAkhir << " "
             << mhs[idx].grade << endl;
    } else {
        cout << "Data tidak ditemukan\n";
    }

    int rendah = cariTerendah(mhs, n);
    cout << "\nNilai terendah: "
         << mhs[rendah].nama << " = "
         << mhs[rendah].nilaiAkhir << " ("
         << mhs[rendah].grade << ")" << endl;


    float rata = rataRata(mhs, n);
    cout << "Rata-rata nilai: " << rata << endl;

    ofstream out("hasil_analisis.txt");

    out << "HASIL ANALISIS\n\n";

    for (int i = 0; i < n; i++) {
        out << mhs[i].nim << " "
            << mhs[i].nama << " "
            << mhs[i].nilaiAkhir << " "
            << mhs[i].grade << endl;
    }

    out << "\nRata-rata: " << rata << endl;
    out << "Nilai terendah: "
        << mhs[rendah].nama << " "
        << mhs[rendah].nilaiAkhir << " "
        << mhs[rendah].grade << endl;

    out.close();

    cout << "\nData berhasil disimpan ke file!\n";

    return 0;
}
