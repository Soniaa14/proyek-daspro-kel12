#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RUTE 10
#define MAX_KURSI 40
#define MAX_TRANSAKSI 100

typedef struct {
    char asal[30];
    char tujuan[30];
    char tanggal[15];
    char waktu[10];
    int harga;
} Rute;

typedef struct {
    char nama[50];
    char id[15];
    char telepon[15];
    int rute_index;
    int kursi;
    int total_harga;
} Transaksi;

Rute rutes[MAX_RUTE];
int total_rute = 0;
int kursi_terpesan[MAX_RUTE][MAX_KURSI] = {0};
Transaksi transaksi[MAX_TRANSAKSI];
int total_transaksi = 0;

int bersihkanBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    return 1; 
}

int tambahRute() {
    if (total_rute >= MAX_RUTE) {
        printf("Kapasitas rute penuh.\n");
        return 0; 
    }

    Rute r;
    printf("Masukkan kota asal: ");
    fgets(r.asal, sizeof(r.asal), stdin);
    r.asal[strcspn(r.asal, "\n")] = '\0';

    printf("Masukkan kota tujuan: ");
    fgets(r.tujuan, sizeof(r.tujuan), stdin);
    r.tujuan[strcspn(r.tujuan, "\n")] = '\0';

    printf("Masukkan tanggal (DD-MM-YYYY): ");
    fgets(r.tanggal, sizeof(r.tanggal), stdin);
    r.tanggal[strcspn(r.tanggal, "\n")] = '\0';

    printf("Masukkan waktu (HH:MM): ");
    fgets(r.waktu, sizeof(r.waktu), stdin);
    r.waktu[strcspn(r.waktu, "\n")] = '\0';

    printf("Masukkan harga tiket: ");
    if (scanf("%d", &r.harga) != 1) {
        printf("Input harga tidak valid.\n");
        bersihkanBuffer();
        return 0; 
    }
    bersihkanBuffer();

    rutes[total_rute++] = r;
    printf("Rute berhasil ditambahkan.\n");
    return 1; 
}

int tampilkanRute() {
    if (total_rute == 0) {
        printf("Belum ada rute yang tersedia.\n");
        return 0; 
    }

    printf("Daftar Rute:\n");
    for (int i = 0; i < total_rute; i++) {
        printf("%d. %s ke %s - %s %s - Rp%d\n", i + 1,
               rutes[i].asal, rutes[i].tujuan, rutes[i].tanggal,
               rutes[i].waktu, rutes[i].harga);
    }
    return 1; 
}

int pesanTiket() {
    if (!tampilkanRute()) return 0;

    int rute_index, kursi;
    Transaksi t;

    printf("Pilih nomor rute: ");
    if (scanf("%d", &rute_index) != 1 || rute_index < 1 || rute_index > total_rute) {
        printf("Nomor rute tidak valid.\n");
        bersihkanBuffer();
        return 0; 
    }
    bersihkanBuffer();

    rute_index; 

    printf("Masukkan nomor kursi (1-%d): ", MAX_KURSI);
    if (scanf("%d", &kursi) != 1 || kursi < 1 || kursi > MAX_KURSI || kursi_terpesan[rute_index][kursi - 1]) {
        printf("Kursi tidak valid atau sudah dipesan.\n");
        bersihkanBuffer();
        return 0; 
    }
    bersihkanBuffer();

    printf("Masukkan nama Anda: ");
    fgets(t.nama, sizeof(t.nama), stdin);
    t.nama[strcspn(t.nama, "\n")] = '\0';

    printf("Masukkan ID Anda: ");
    fgets(t.id, sizeof(t.id), stdin);
    t.id[strcspn(t.id, "\n")] = '\0';

    printf("Masukkan nomor telepon: ");
    fgets(t.telepon, sizeof(t.telepon), stdin);
    t.telepon[strcspn(t.telepon, "\n")] = '\0';

    t.rute_index = rute_index;
    t.kursi = kursi;
    t.total_harga = rutes[rute_index].harga;

    transaksi[total_transaksi++] = t;
    kursi_terpesan[rute_index][kursi - 1] = 1;

    printf("Tiket berhasil dipesan.\n");
    return 1; 
}

int simpanLaporanKeFile() {
    FILE *file = fopen("laporan_transaksi.txt", "w");
    if (!file) {
        printf("Gagal membuka file untuk menulis laporan.\n");
        return 0; 
    }

    fprintf(file, "Laporan Transaksi:\n");
    for (int i = 0; i < total_transaksi; i++) {
        fprintf(file, "%d. %s (ID: %s) - Rute: %s ke %s - Kursi: %d - Total: Rp%d\n",
                i + 1, transaksi[i].nama, transaksi[i].id,
                rutes[transaksi[i].rute_index].asal, rutes[transaksi[i].rute_index].tujuan,
                transaksi[i].kursi, transaksi[i].total_harga);
    }

    fclose(file);
    printf("Laporan transaksi berhasil disimpan ke 'laporan_transaksi.txt'.\n");
    return 1; 
}

int laporanTransaksi() {
    if (total_transaksi == 0) {
        printf("Belum ada transaksi.\n");
        return 0; 
    }

    printf("Laporan Transaksi:\n");
    for (int i = 0; i < total_transaksi; i++) {
        printf("%d. %s (ID: %s) - Rute: %s ke %s - Kursi: %d - Total: Rp%d\n",
               i + 1, transaksi[i].nama, transaksi[i].id,
               rutes[transaksi[i].rute_index].asal, rutes[transaksi[i].rute_index].tujuan,
               transaksi[i].kursi, transaksi[i].total_harga);
    }

    simpanLaporanKeFile();

    return 1;
}

int main() {
    int pilihan;
    do {
        printf("\nMenu Pemesanan Tiket:\n");
        printf("1. Tambah Rute\n");
        printf("2. Pesan Tiket\n");
        printf("3. Laporan Transaksi\n");
        printf("4. Keluar\n");
        printf("Pilihan: ");
        
        if (scanf("%d", &pilihan) != 1) {
            printf("Input tidak valid. Masukkan angka.\n");
            bersihkanBuffer();
            continue;
        }
        bersihkanBuffer();

        if (pilihan == 1) tambahRute();
        else if (pilihan == 2) pesanTiket();
        else if (pilihan == 3) laporanTransaksi();
        else if (pilihan == 4) printf("Terima kasih telah menggunakan sistem.\n");
        else printf("Pilihan tidak valid.\n");
    } while (pilihan != 4);

    return 0;
}
