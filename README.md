# PROYEK-2 - Pengembangan Aplikasi Berbasis Library

## Teknik Komputer dan Informatika - D3 Teknik Informatika 
## Manager Proyek: Djoko Cahyo Utomo Lieharyani, S.Kom., M.MT
## Nama Kelompok: C3-*Space Invaders*
### Anggota Kelompok:

| Nama | NIM |
| ---- | --- |
| Alda Pujama | 241511066 |
| Fairuz Sheva Muhammad | 241511073 |
| Gema Adzan Firdaus | 241511075 |
| Muhammad Ihsan Ramadhan | 241511083 |
| Rahma Attaya Tamimah | 241511088 |

# Deskripsi
Space Invaders adalah game di mana pemain mengendalikan pesawat luar angkasa dan bertugas menghancurkan musuh yang datang berdasarkan wave. Terdapat dua jenis musuh dalam permainan ini: musuh biasa dengan HP rendah dan musuh kuat dengan HP lebih tinggi, yang bergerak dari kanan ke kiri layar. Untuk membantu pemain bertahan lebih lama, permainan ini menyediakan power-up yang dapat menambah nyawa dan amunisi. Dalam permainan ini, pesawat dikendalikan langsung melalui keyboard. Pemain dapat menembak dengan sistem yang memiliki jeda (cooldown) dan harus melakukan reload jika amunisi habis. Musuh muncul secara acak dengan variasi posisi dan kecepatan, sehingga masing-masing memiliki pola pergerakan yang berbeda. Setelah satu gelombang musuh dikalahkan, jumlah musuh akan bertambah dan tingkat kesulitannya meningkat. Sistem collision detection akan mendeteksi benturan antara peluru dan musuh atau antara pesawat dan musuh, yang akan mempengaruhi jumlah nyawa dan skor pemain.

# Struktur File Proyek
```
Proyek2-C3/
├── assets/
│   ├── audio/
│   ├── gambar/
├── bin/
├── include/
│   ├── SDL3/
│   ├── alda.h
│   ├── config.h
│   ├── fairuz.h
│   ├── gema.h
│   ├── ihsan.h
│   ├── rahma.h
├── lib/
│   ├── cmake/
│   ├── pkgconfig/
│   ├── libSDL3_test.a
│   ├── libSDL3.dll.a
│   ├── SDL3_mixer.lib
├── share/
│   ├── license/
├── src/
│   ├── audio.c
│   ├── background.c
│   ├── highskor.dat
│   ├── main.c
│   ├── menu.c
│   ├── musuh.c
│   ├── peluru_player.c
│   ├── pesawat.c
│   ├── skor.c
│   ├── star.c
│   ├── suplai.c
│   ├── wave.c
├── makefile
└── README.md
```


# Deskripsi File-File Utama dalam Game
## **main.c**
- Program utama (game loop)
- Insisialisasi window utama
- Logika utama permainan
- Penanganan input dari pemain
- Perpindahan antar state (menu, game, about dan tutorial)

## **config.h**
- Deklarasi ukuran window utama
- Deklarasi state dalam game (menu, game, about dan tutorial)

## **alda.h**
- Deklarasi dan inisialisasi audio(SDL_Mixer)
- Sistem skor pemain
- Tampilan saat game over

## **fairuz.h**
- Deklarasi jumlah maksimal musuh dan wave
- Sistem wave musuh dalam game
- Sistem pengurangan skor
- Sistem bonus wave

## **gema.h**
- Deklarasi jumlah maksimal bintang
- Deklarasi bagian menu
- Deklarasi background saat memulai permainan

## **ihsan.h**
- Deklarasi jumlah maksimal peluru, suplai dan berapa jenis suplai yang ada
- Sistem pesawat pemain
- Sistem peluru(tembakan pesawat)
- Sistem suplai di dalam game

## **rahma.h**
- Deklarasi berapa jenis musuh
- Sistem musuh dan jenis musuh
- Sistem collision pesawat dengan musuh
- Sistem suplai di dalam game

**Kompilasi**
Menggunakan Makefile:

```
make
```
pada terminal git bash

**Syarat**
-Compiler C(MinGW/GCC)

**Kontrol Pemain**
| Tombol | Fungsi |
| ---- | --- |
| W | Bergerak ke arah atas |
| S | Bergerak ke arah bawah |
| A | Bergerak ke arah kiri |
| D | Bergerak ke arah kanan |
| Spasi | Menembak |
| R | Mengisi ulang amnunisi(reload) |

# Fitur Game dan Pembagian Tugas:
### 1. Alda Pujama - Bertanggung jawab dalam pembuatan skor dan highskor, gameover, audio.
    A. Skor
        Membuat sistem skor bagi player dimana jika musuh berhasil mati terkena peluru player maka skor bertamabah dan menampilkannya.
    B. Highskor
        Mencatat skor tertinggi yang didapat selama bermain, highskor ini berubah hanya jika skor yang didapat lebih besar dari highskor dan bisa menampilkan highskor yang didapat sebelumnya.
    C. Gameover
        Membuat tampilan saat pemain sudah kehabisan nyawa atau game over disertai catatan skor dan highskor yang didapatkan. Kemudian mengembalikan ke state menu lagi setelah waktu tertentu.
    D. Audio dengan SDL_Mixer
        Mengintegrasikan audio menggunakan sdl mixer sehingga game bisa menggeluarkan suara atau audio. Audio dikeluarkan saat : 
            - Menu game ditampilkan
            - Button di tekan
            - Mulainya game
            - Player mengeluarkan peluru
            - Musuh mati
            - nyawa player beekurang
            - Tampilan game over

### 2. Fairuz Sheva Muhammad - Bertanggung jawab dalam pengembangan gameplay seperti wave dan pengurangan skor.
    A. Membuat Sistem Wave
        a). Membuat sistem wave untuk memberikan tantangan kepada player, dengan sistem ketika semua musuh mati dalam wave tersebut, maka akan lanjut ke wave selanjutnya.
        b). Menampilkan juga wave yang sedang dihadapi.
    B. Membuat Sistem Pengurangan Skor
        a). Ketika musuh melewati batas/pemain, maka hal tersebut akan menyebabkan pengurangan skor.
        b). Pengurangan skor dibagi menjadi dua, untuk musuh biasa dan musuh besar.

### 3. Gema Adzan F - Bertanggung jawab dalam pembuatan menu utama, background, dan game state.
    A. Background
        Membuat background bintang agar ambience luar angkasa dari game Space Invaders terasa.
    B. Menu Utama
        Menu utama dari game Space Invaders yang terdiri dari 4 tombol, yaitu:
        a). Play: Untuk memulai permainan.
        b). About: Untuk menampilkan profil Kelompok C3.
        c). Tutorial: Untuk menampilkan cara memainkan permainan.
        d). Quit: Untuk keluar dari game.
    C. Game State
        Game state yang berguna untuk memungkinkan user berada di menu utama, dalam game, dan lainnya.

### 4.  M. Ihsan Ramadhan - Bertanggung jawab dalam pengembangan sistem pesawat pemain, peluru, dan power-up (buff), yaitu:
    A. Sistem Pesawat Pemain
        1. Gerakan Pesawat
            a). Mengatur pergerakan pesawat menggunakan input pemain (WASD).
            b). Menentukan batas gerakan agar pesawat tidak keluar dari layar.
        2. Penanganan Tabrakan dengan Musuh
            a). Memeriksa apakah pesawat menyentuh musuh.    
            b). Pengurangan nyawa saat bertabrakan dengan musuh
        3. Efek Visual Pesawat
            a). Membuat tampilan pesawat dengan SDL_Renderer.
            b). Membuat efek api beranimasi di bagian belakang pesawat. jika pesawat diam, apinya kecil, dan jika bergerak, apinya membesar.
    B. Sistem Peluru
        1. Membuat Visualisasi Peluru
            a). Mengatur ukuran dan warna peluru beserta trail (ekor).
        2. Menembakkan Peluru, Mengatur Kecepatan dan Jalurnya
            a). Membuat fungsi nembak() agar pesawat bisa menembakkan peluru.
            b). Mengatur kecepatan peluru menggunakan dx dan dy, memastikan peluru menghilang saat keluar dari layar.
        3. Menambah Amunisi dan Menampilkan Amunisi
            a). Menambahkan pembatasan amunisi awal (30 peluru).
            b).Menampilkan jumlah peluru yang tersisa dalam magasin menggunakan fungsi tampilAmunisi().
        4. Mekanisme Reload Peluru
            a). Jika amunisi habis, pemain harus menunggu reload selesai sebelum bisa menembak lagi.
            b). Menampilkan teks “RELOADING...” di layar saat reload berlangsung.
    C. Sistem Power-Ups
        1. Spawn suplai (nyawa dan amunisi)
            a). Mengatur power-ups muncul secara acak di layar.
            b). Menentukan jenis power-ups yang muncul (nyawa atau amunisi).
        2. Visualisasi Power-Ups
            a). Merender dan menggambar Power-Ups sesuai jenisnya menggunakan SDL_Texture.
        3. Deteksi tabrakan suplai dengan pesawat
            a). Memeriksa apakah pesawat menyentuh Power-Ups.
            b). Jika terkena, Power-Ups akan memberikan efek sesuai jenisnya. Jika nyawa maka menambah nyawa, dan jika amunisi maka menambah amunisi.

### 5. Rahma Attaya Tamimah - Bertanggung jawab untuk merancang dan mengimplementasikan yang berkaitan dengan musuh, yaitu:
    A. Struktur dan Atribut Musuh
        a). Mendefinisikan 2 jenis musuh, yaitu Musuh Biasa (tipe 0) dengan HP rendah dan Musuh Kuat (tipe 1) dengan HP lebih tinggi. 
        b). Menyimpan atribut HP, lebar, dan tinggi di dalam variabel global musuhAtribut.
    B. Inisialisasi Musuh
        a). Mengatur posisi awal setiap musuh secara acak, menetapkan kecepatan horizontal (dx) dalam rentang 2–3 piksel.
        b). Mengatur tipe musuh kuat sesuai kebutuhan wave.
    C. Pergerakan Musuh
        Menggerakkan musuh dengan menambahkan nilai dx ke posisi X, lalu me-reset posisi musuh yang keluar layar ke sisi kanan yang belum terkena peluru.
    D. Collision & Efek Tabrakan
        Menangani tabrakan antara peluru dan musuh lalu menonaktifkan musuh serta peluru.
    E. Tampilan Visual Musuh
        a). Menggambar tubuh, mata, antena, tangan, dan tentakel.
        b). Mmembedakan warna untuk musuh biasa dan kuat.
        c). Menampilkan HP bar di atas musuh kuat untuk memperlihatkan sisa HP.
