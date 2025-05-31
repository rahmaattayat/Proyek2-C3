# PROYEK-2 - Pengembangan Aplikasi Berbasis Library

## Teknik Komputer dan Informatika - D3 Teknik Informatika 
## Manager Proyek: Djoko Cahyo Utomo Lieharyani, S.Kom., M.MT
## Nama Kelompok: C3-*Space Invaders*
### Anggota Kelompok:

| Nama | NIM | ID GitHub |
| ---- | --- | --- |
| Alda Pujama | 241511066 | Arud4Alda |
| Fairuz Sheva Muhammad | 241511073 | pairus-portofolio |
| Gema Adzan Firdaus | 241511075 | Gema1407 |
| Muhammad Ihsan Ramadhan | 241511083 | ihsan-ramadhan |
| Rahma Attaya Tamimah | 241511088 | rahmaattayat |

# Deskripsi
Space Invaders adalah game arcade 2D di mana pemain mengendalikan pesawat luar angkasa untuk menghancurkan gelombang musuh yang datang. Pemain harus mengelola amunisi, menghindari tabrakan, dan memanfaatkan power-up untuk bertahan selama mungkin.

# Aturan Game
## **1. Tipe Musuh**
- Terdapat dua tipe musuh: Musuh Biasa dan Musuh Kuat.
- Musuh Biasa memiliki 1 HP, sedangkan Musuh Kuat memiliki 3 HP.
- Musuh Kuat mulai muncul pada wave 5, dengan jumlah yang meningkat seiring kenaikan wave (maksimal sepertiga dari jumlah musuh).

## **2. Skor**
- Membunuh Musuh Biasa menambah skor sebanyak 10 poin (dikalikan dengan bonus wave, jika aktif).
- Membunuh Musuh Kuat menambah skor sebanyak 30 poin (dikalikan dengan bonus wave, jika aktif).
- Jika musuh (biasa atau kuat) keluar dari layar tanpa terbunuh, skor akan berkurang: -10 poin untuk Musuh Biasa dan -30 poin untuk Musuh Kuat.
- Skor tertinggi (high score) disimpan dalam file highskor.dat dan diperbarui jika skor saat ini melebihi high score sebelumnya.

## **3. Wave dan Bonus**
- Permainan terdiri dari beberapa wave, dimulai dari Wave 1, dengan jumlah musuh bertambah setiap wave (maksimal 20 musuh).
- Setiap kelipatan 5 wave (misalnya Wave 5, 10, dst.), merupakan Bonus Wave, di mana semua poin yang diperoleh digandakan (bonus = 2).
- Jumlah musuh pada setiap wave bertambah sesuai nomor wave, namun dibatasi hingga maksimal 20 musuh.

## **4. Kontrol Pesawat**
- Gunakan tombol W untuk bergerak ke atas, S untuk ke bawah, A untuk ke kiri, dan D untuk ke kanan.
- Tekan Spasi untuk menembak peluru (dengan jeda antar tembakan).
- Tekan R untuk reload amunisi jika peluru habis (memerlukan waktu reload 60 frame).
- Pesawat memiliki 3 nyawa di awal permainan dan 30 amunisi per magasin.

## **5. Amunisi dan Reload**
- Pesawat dapat menembak hingga 30 peluru per magasin.
- Jika amunisi habis, tekan R untuk reload, yang akan mengisi ulang magasin tetapi membutuhkan waktu.
- Selama reload, status "RELOADING..." akan ditampilkan di layar.

## **6. Power-Ups (Suplai)**
- Terdapat dua jenis power-up: Nyawa dan Amunisi.
- Power-up muncul secara acak setiap 30–45 detik di sisi kanan layar dan bergerak ke kiri.
- Menabrak power-up Nyawa akan menambah 1 nyawa (maksimal 3 nyawa).
- Menabrak power-up Amunisi akan menambah kapasitas magasin sebanyak 5 peluru dan langsung mengisi ulang amunisi.

## **7. Tabrakan dengan Musuh**
- Jika pesawat menabrak Musuh Biasa, nyawa berkurang 1 poin.
- Jika menabrak Musuh Kuat, nyawa berkurang 2 poin.
- Jika nyawa habis (0), permainan berakhir (Game Over), dan skor disimpan. Permainan akan kembali ke menu utama setelah 4 detik.

## **8. Menu dan Navigasi**
- Pada menu utama, pilih opsi PLAY untuk memulai permainan, ABOUT untuk melihat informasi pengembang, TUTORIAL untuk panduan permainan, atau EXIT untuk keluar.
- Tekan ESC pada layar About atau Tutorial untuk kembali ke menu utama.
- Klik tombol di menu menggunakan mouse, dengan efek suara saat tombol diklik.

## **9. Game Over**
- Saat Game Over, layar akan menampilkan skor akhir dan high score.
- Permainan akan menunda selama 4 detik sebelum kembali ke menu utama, dengan musik Game Over diputar.
- Jumlah musuh direset ke 5, wave direset ke 1, dan skor direset ke 0 untuk permainan berikutnya.

## **10. Audio**
- Permainan memiliki musik latar untuk menu, permainan, dan Game Over.
- Efek suara diputar saat menembak, musuh mati, pemain tertabrak, dan pesawat player menyentuh suplai.

# Struktur File Proyek:
```
Proyek2-C3/
├── assets/
│   ├── audio/
│   ├── fonts/
│   ├── gambar/
├── bin/
├── build/
├── include/
│   ├── SDL3/
│   ├── SDL3_ttf/
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
│   ├── libSDL3_ttf.dll.a
│   ├── libSDL3.dll.a
│   ├── SDL3_mixer.lib
├── share/
│   ├── license/
├── src/
│   ├── audio.c
│   ├── background.c
│   ├── leaderboard.c
│   ├── leaderboard.dat
│   ├── main.c
│   ├── menu.c
│   ├── musuh.c
│   ├── peluru_player.c
│   ├── pesawat.c
│   ├── skor.c
│   ├── suplai.c
│   ├── ttf.c
│   ├── wave.c
├── makefile
└── README.md
```


# Deskripsi File-File Utama dalam Game:
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

# Keterangan Teknis:
## **Langkah-Langkah Setup dan Kontrol Pemain**
### **1. Tools yang digunakan**
- Visual Studio Code
- GitHub Dekstop
- MSYS2 (Compiler)
- Scoop

### **2. Langkah Instalasi**
- Install VSCode, Git, MSYS2GitHub Dekstop
- Pastikan PATH environment sudah berisi: MinGw\bin
- Install Extension C/C++ di VSCode
- Buka Git Bash lalu jalankan:  
```
scoop install make
```

### **3. Menjalankan Game**
- Download repository dari GitHub (ZIP atau Clone)
- Buka folder project di VSCode
- Buka terminal di VSCode, ubah terminal ke Git Bash
- Compile dan jalankan program menggunakan Make:
```
make
```

### **4. Kontrol Pemain**
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
        Membuat sistem skor bagi player, jika musuh mati terkena peluru player maka skor bertamabah dan membuat tampilan realtimenya. Mencatat skor tertinggi yang didapat selama bermain, sebagai highskor highskor ini berubah hanya jika skor yang didapat lebih besar dari highskor dan bisa menampilkan highskor yang didapat sebelumnya.
    B. Gameover
        Membuat tampilan game over jika pemain sudah kehabisan nyawa dan mati lalu kembali ke menu awal.
    C. Audio dengan SDL_Mixer
        Mengintegrasikan audio menggunakan sdl mixer sehingga game bisa menggeluarkan background musik dan sound effect ke dalam game agar lebih menarik. Audio dikeluarkan saat menu game ditampilkan, button di tekan, mulainya game, player mengeluarkan peluru, musuh mati, nyawa player beekurang, tampilan game over.
    D. Leaderboard
        Membuat sistem leaderboard untuk mencatat dan menampilkan daftar pemain dengan skor tertinggi. Fungsi utamanya untuk menyimpan data banyak pemain, termasuk username, skor terakhir, dan high score-nya. Lalu akan menampilkan urutan pemain berdasarkan high score dari yang tertinggi. Dan menyimpan data ke file agar bisa digunakan kembali saat game dibuka kembali. Fitur ini menerapkan pemograman dengan struktur data dinamis yaitu double linked list. 

### 2. Fairuz Sheva Muhammad - Bertanggung jawab dalam pengembangan gameplay seperti wave dan pengurangan skor.
    A. Membuat Sistem Wave
        a). sistem wave mengatur gelombang musuh secara bertahap. Sistem ini menggunakan linked list untuk menyimpan dan melacak nomor wave secara dinamis. Setiap kali pemain menyelesaikan satu wave, node baru ditambahkan, menandakan gelombang berikutnya.
        b). Selain itu, terdapat bonus wave, di mana setiap beberapa wave (misalnya kelipatan 5), skor yang diperoleh saat menghancurkan musuh akan digandakan.
    B. Membuat Sistem Pengurangan Skor
        a). Ketika musuh melewati batas/pemain, maka hal tersebut akan menyebabkan pengurangan skor.
        b). Pengurangan skor dibagi menjadi dua, untuk musuh biasa dan musuh besar.

### 3. Gema Adzan F - Bertanggung jawab dalam pembuatan menu utama, background, dan game state.
    A. Menu Utama
        Main menu yang menampilakan judul game dan beberapa tombol di tampilannya untuk memasuki konten-konten yang ada di dalam game. Tombol-tombol tersebut adalah : 
        a). Play: Untuk memulai permainan.
        b). About: Untuk menampilkan profil Kelompok C3.
        c). Tutorial: Untuk menampilkan cara memainkan permainan.
        d). Leaderboard : Tombol untuk menunjukan peringkat poin dalam game space invader
        e). Quit: Untuk keluar dari game.
    B. Tampilan
        a). Tampilan Background: Membuat tampilan untuk background dengan visual bintang yang bergerak kearah yang sebaliknya dari pesawat untuk menciptakan efek seolah pesawat bergerak maju secara terus menerus. Visual di background ini dibuat agar suasana luar angkasa di game terasa.
        b). Tampilan Leaderboard: Membuat tampilan leaderboard yaitu tampilan peringkat untuk 10 player dengan perolehan poin tertinggi/highscore yang diurutkan secara descending.
    C. Implementasi SDL_ttf
       SDL_ttf digunakan untuk merender teks ke layar dan juga untuk memuat font yang telah didownload dan dimasukan ke proyek. Penggunaan ttf ini digunakan pada teks dalam proyek seperti judul, teks dalam about, teks dalam tutorial, dan lain lain
                
### 4.  M. Ihsan Ramadhan - Bertanggung jawab dalam pengembangan sistem pesawat pemain, peluru, dan power-up (buff), yaitu:
    A. Sistem Pesawat Pemain
        a). Mengatur pergerakan pesawat lewat gerakinPesawat() dan membatasi agar tetap di layar dengan updatePesawat(). 
        b). Visual pesawat digambar melalui bikinGambarPesawat(), dan nyawa ditampilkan dengan tampilNyawa().
    B. Sistem Peluru
        1. Menerapkan Struktur Double Linked List pada Peluru
            Mengatur proses Insert, dan Delete pada penerapan Double Linked List di sistem Peluru. Proses Insert diatur di fungsi PeluruNode* buatPeluruNode() dan tambahPeluruNode(), serta Proses Delete diatur di fungsi hapusPeluruNode() dan freePeluruList().
        2. Membuat Visualisasi Peluru
            Mengatur ukuran dan warna peluru beserta trail (ekor) lewat bikinGambarPeluru().
        3. Menembakkan Peluru, Mengatur Kecepatan dan Jalurnya
            a). Membuat fungsi nembak() agar pesawat bisa menembakkan peluru.
            b). Mengatur kecepatan peluru menggunakan dx dan dy, memastikan peluru menghilang saat keluar dari layar.
        4. Menambah Amunisi dan Menampilkan Amunisi
            a). Menambahkan pembatasan amunisi awal (30 peluru).
            b). Menampilkan jumlah peluru yang tersisa dalam magasin menggunakan fungsi tampilAmunisi().
        5. Mekanisme Reload Peluru
            a). Jika amunisi habis, pemain harus menunggu reload selesai sebelum bisa menembak lagi.
            b). Menampilkan teks “RELOADING...” di layar saat reload berlangsung.
        6. Mengatur Collisions antara Peluru dengan Musuh
            a). Menghapus Node Peluru jika menyentuh Musuh melalui hapusPeluruNode()
            b). Mengatur logika Collisions melalui pengecekan posisi x dan y, serta besar w dan h dari current (peluru) dan musuh.
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
    A. Membuat Struktur Data Musuh dengan Double Linked List    
        Fungsi yang digunakan antara lain tambahNodeMusuh() untuk menambah musuh, hapusNodeMusuh() untuk menghapus musuh, dan freeMusuh() untuk menghapus semua musuh saat game diulang. Cara ini membuat pengaturan musuh jadi lebih fleksibel dan efisien.
    B. Mengelola Atribut Musuh
        Atribut musuh seperti HP, ukuran, dan kecepatan diatur berdasarkan tipe musuh, yaitu musuh biasa dan musuh kuat. Fungsi aturAtributMusuh() dan buatMusuh() dibuat untuk mengatur posisi, ukuran, dan kecepatan awal setiap musuh saat muncul di layar.
    C. Spawning Musuh
        Spawning musuh dilakukan lewat bikinMusuh() sesuai level wave. Musuh lama dihapus, lalu musuh baru ditambahkan dengan jumlah dan tipe yang disesuaikan.
    D. Pergerakan dan Interaksi Musuh
        Pergerakan musuh dibuat dengan fungsi gerakinMusuh() agar semua musuh bergerak ke kiri layar. Jika ada musuh yang keluar layar, musuhKeluarLayar() akan mendeteksinya dan mengurangi skor pemain. Selain itu, nabrakMusuh() digunakan untuk mendeteksi tabrakan dengan pemain dan mengurangi nyawa sesuai tipe musuh.
    E. Tampilan Visual Musuh
        Tampilan musuh didesain menggunakan SDL_FRect untuk membentuk bagian seperti kepala, mata, antena, tangan, tentakel, mulut, dan alis. Warna musuh dibedakan berdasarkan tipe, yaitu musuh biasa dan musuh kuat. Untuk musuh kuat, ditambahkan bar HP agar pemain bisa melihat sisa nyawanya.
