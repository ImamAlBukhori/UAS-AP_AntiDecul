#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct Pemain {
    string nama;
    int skor = 0;
    int selisih = 0;
    int skorTieBreak = 0;
    bool pemenangTieBreak = false;
};

bool compareSkor(const Pemain& a, const Pemain& b) {
    if (a.selisih == b.selisih) return a.skorTieBreak > b.skorTieBreak;
    return a.selisih < b.selisih;
}

int lemparDadu() {
    return rand() % 6 + 1;
}

int main() {
    srand(time(0));
    int jumlahPemain;
    int targetSkor;
    vector<Pemain> pemain;

    cout << "===============================================\n";
    cout << "  Selamat Datang di Game Dadu Kelompok Anti Decul!!!\n";
    cout << "===============================================\n";
    cout << "NOTE: Pemain maksimal berjumlah 5 orang\n\n";

    do {
        cout << "Masukkan jumlah pemain: ";
        cin >> jumlahPemain;
    } while (jumlahPemain < 2 || jumlahPemain > 5);

    do {
        cout << "Masukkan skor target: ";
        cin >> targetSkor;
    } while (targetSkor < 3 || targetSkor > 18);

    cin.ignore();

    for (int i = 0; i < jumlahPemain; i++) {
        Pemain p;
        cout << "Nama pemain ke-" << i + 1 << " : ";
        getline(cin, p.nama);
        pemain.push_back(p);
    }


    for (int putaran = 1; putaran <= 3; putaran++) {
        cout << "\nPutaran ke-" << putaran << "\n";
        for (int i = 0; i < jumlahPemain; i++) {
            int nilaiDadu = lemparDadu();
            pemain[i].skor += nilaiDadu;
            cout << "Pemain ke-" << i + 1 << " atau " << pemain[i].nama << endl;
            cout << "Dadu anda bernilai " << nilaiDadu << endl;
            cout << "Skor anda saat ini: " << pemain[i].skor << endl << endl;
        }
    }


    for (auto& p : pemain) {
        p.selisih = abs(targetSkor - p.skor);
    }


    sort(pemain.begin(), pemain.end(), compareSkor);

    int selisihTop = pemain[0].selisih;
    int skorTop = pemain[0].skor;
    vector<int> tieIndex;

    for (int i = 0; i < pemain.size(); i++) {
        if (pemain[i].selisih == selisihTop && pemain[i].skor == skorTop) {
            tieIndex.push_back(i);
        }
    }


    if (tieIndex.size() > 1) {
        cout << "\n===============================================\n";
        cout << "     Tie Breaker untuk Menentukan Pemenang\n";
        cout << "===============================================\n";

        bool selesai = false;
        while (!selesai) {
            cout << "\nPeserta tie breaker:\n";
            for (int i : tieIndex) {
                cout << "- " << pemain[i].nama << endl;
            }

            cout << "Tekan ENTER untuk lempar dadu...";
            cin.ignore();

            int maxTieBreak = 0;
            for (int i : tieIndex) {
                int hasil = lemparDadu();
                pemain[i].skorTieBreak = hasil;
                cout << pemain[i].nama << " mendapatkan nilai dadu: " << hasil << endl;
                if (hasil > maxTieBreak) maxTieBreak = hasil;
            }

            vector<int> nextTie;
            for (int i : tieIndex) {
                if (pemain[i].skorTieBreak == maxTieBreak) {
                    nextTie.push_back(i);
                }
            }

            if (nextTie.size() == 1) {
                pemain[nextTie[0]].pemenangTieBreak = true;
                selesai = true;
                cout << "\nPemenang Tie Break adalah: " << pemain[nextTie[0]].nama << endl;
            } else {
                cout << "\nMasih Seri! Pemain yang lanjut tie break:\n";
                tieIndex = nextTie;
                
            }
        }
    }


    sort(pemain.begin(), pemain.end(), compareSkor);


    cout << "\n================== HASIL AKHIR ==================\n";
    cout << "Skor Target : " << targetSkor << "\n";
    cout << "========================================================\n";
    cout << "Ranking | Nama     | Skor | Selisih Skor | Skor Tie Break\n";
    cout << "========================================================\n";

    int peringkat = 1;
    for (int i = 0; i < pemain.size(); i++) {
        cout << peringkat << "       | "
             << pemain[i].nama
             << string(9 - pemain[i].nama.length(), ' ') << "| "
             << pemain[i].skor << "    | "
             << pemain[i].selisih << "            | "
             << pemain[i].skorTieBreak << endl;
        peringkat++;
    }


    cout << "\n🏆 Pemenang Game Ini: ";
    bool pemenangDariTieBreak = false;
    for (const auto& p : pemain) {
        if (p.pemenangTieBreak) {
            cout << p.nama << " (melalui Tie Break)\n";
            pemenangDariTieBreak = true;
            break;
        }
    }
    if (!pemenangDariTieBreak) {
        cout << pemain[0].nama << endl;
    }

    cout << "\nTerima kasih sudah bermain!\n";

    return 0;
}