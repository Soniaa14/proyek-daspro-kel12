#include <stdio.h>
#include <string.h>

// Struct untuk menyimpan data rute, jadwal, dan harga tiket
typedef struct {
    char asal[50];
    char tujuan[50];
    char jadwal[50];
    float harga;
} Rute;

// Struct untuk menyimpan data pelanggan dan transaksi
typedef struct {
    char nama[50];
    char id[20];
    char no_telepon[15];
    int nomor_kursi;
    Rute rute_dipilih;
} Pelanggan;

// Deklarasi data rute bus
Rute rute_bus[3] = {
    {"Kediri", "Malang", "10:00 WIB", 150000},
    {"Blitar", "Magelang", "08:00 WIB", 285000},
    {"Bandung", "Surabaya", "06:00 WIB", 325000}
};

// Fungsi untuk menampilkan semua rute dan jadwal
void tampilkanRute() {
    printf("Daftar Rute dan Jadwal:\n");
    for (int i = 0; i < 3; i++) {
        printf("%d. %s ke %s - %s - Rp %.2f\n", i + 1, rute_bus[i].asal, rute_bus[i].tujuan, rute_bus[i].jadwal, rute_bus[i].harga);
    }
}

// Fungsi untuk melihat kursi tersedia
void lihatKursi(int kursi_terpesan[], int total_kursi) {
    printf("Kursi yang tersedia: ");
    for (int i = 1; i <= total_kursi; i++) {
        if (kursi_terpesan[i] == 0) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

// Fungsi untuk menyimpan laporan ke file txt
void tambahLaporan(Pelanggan pelanggan) {
    FILE *file = fopen("laporan_transaksi.txt", "a");
    if (file == NULL) {
        printf("Gagal membuka file untuk menambahkan laporan!\n");
        return;
    }
    fprintf(file, "Nama: %s\nID: %s\nNo Telepon: %s\nRute: %s ke %s\nJadwal: %s\nNomor Kursi: %d\nHarga: Rp %.2f\n\n",
            pelanggan.nama, pelanggan.id, pelanggan.no_telepon,
            pelanggan.rute_dipilih.asal, pelanggan.rute_dipilih.tujuan,
            pelanggan.rute_dipilih.jadwal, pelanggan.nomor_kursi,
            pelanggan.rute_dipilih.harga);
    fclose(file);
    printf("Data transaksi berhasil disimpan ke laporan_transaksi.txt\n");
}

int main() {
    int kursi_terpesan[21] = {0};
    Pelanggan pelanggan[20];
    int jumlah_pelanggan = 0;
    int pilihan, nomor_rute, nomor_kursi;
    
    do {
        printf("\n=== Sistem Pemesanan Tiket Bus ===\n");
        printf("1. Lihat Rute dan Jadwal\n");
        printf("2. Pesan Tiket\n");
        printf("3. Lihat Kursi Tersedia\n");
        printf("4. Keluar\n");
        printf("Pilih menu: ");
        scanf("%d", &pilihan);
        getchar();

        switch (pilihan) {
            case 1:
                tampilkanRute();
                break;
            case 2:
                if (jumlah_pelanggan >= 20) {
                    printf("Kursi sudah penuh!\n");
                    break;
                }
                printf("Masukkan nama: ");
                fgets(pelanggan[jumlah_pelanggan].nama, 50, stdin);
                pelanggan[jumlah_pelanggan].nama[strcspn(pelanggan[jumlah_pelanggan].nama, "\n")] = 0; 
                printf("Masukkan ID pelanggan: ");
                scanf("%s", pelanggan[jumlah_pelanggan].id);
                printf("Masukkan nomor telepon: ");
                scanf("%s", pelanggan[jumlah_pelanggan].no_telepon);
                tampilkanRute();
                printf("Pilih nomor rute: ");
                scanf("%d", &nomor_rute);
                if (nomor_rute < 1 || nomor_rute > 3) {
                    printf("Pilihan rute tidak valid!\n");
                    break;
                }
                pelanggan[jumlah_pelanggan].rute_dipilih = rute_bus[nomor_rute - 1];
                lihatKursi(kursi_terpesan, 20);
                printf("Pilih nomor kursi: ");
                scanf("%d", &nomor_kursi);
                if (nomor_kursi < 1 || nomor_kursi > 20 || kursi_terpesan[nomor_kursi] == 1) {
                    printf("Nomor kursi tidak valid atau sudah dipesan!\n");
                    break;
                }
                pelanggan[jumlah_pelanggan].nomor_kursi = nomor_kursi;
                kursi_terpesan[nomor_kursi] = 1;
                tambahLaporan(pelanggan[jumlah_pelanggan]);
                jumlah_pelanggan++;
                printf("Tiket berhasil dipesan dan laporan disimpan!\n");
                break;
            case 3:
                lihatKursi(kursi_terpesan, 20);
                break;
            case 4:
                printf("Terima kasih telah menggunakan sistem ini.\n");
                break;
            default:
                printf("Pilihan tidak valid!\n");
        }
    } while (pilihan != 4);

    return 0;
}
