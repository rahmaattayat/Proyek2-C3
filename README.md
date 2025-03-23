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

# Fitur Game dan Pembagian Tugas:
### 1. Alda Pujama - Bertanggung jawab dalam pembuatan skor dan highskor, gameover, audio.
    A. SKOR
        Membuat sistem skor bagi pemain, di mana jika musuh berhasil ditaklukkan oleh peluru pemain, skor akan bertambah dan ditampilkan di layar.

    B. HIGHSKOR
        Mencatat skor tertinggi yang diperoleh selama permainan. Jika skor baru melebihi highskor sebelumnya, maka highskor akan diperbarui secara otomatis.

    C. GAMEOVER
        Membuat tampilan saat pemain kehabisan nyawa atau mengalami game over, menampilkan skor serta highskor yang telah dicapai. Setelah itu, pemain dikembalikan ke menu utama setelah jeda tertentu.

    D. AUDIO DENGAN SDL MIXER
        Mengintegrasikan audio menggunakan SDL Mixer, sehingga game dapat mengeluarkan suara atau efek audio di berbagai momen, seperti:
        a). Saat menu game ditampilkan
        b). Ketika tombol ditekan
        c). Saat permainan dimulai
        d). Ketika pemain menembakkan peluru
        e). Ketika musuh mati
        f). Saat nyawa pemain berkurang
        g). Ketika game over muncul

### 2. Fairuz Sheva Muhammad - Bertanggung jawab dalam pengembangan gameplay seperti wave dan pengurangan skor.
    A. Membuat Sistem Wave
        a). Membuat sistem wave untuk memberikan tantangan kepada player, dengan sistem ketika semua musuh mati dalam wave tersebut, maka akan lanjut ke wave selanjutnya.
        b). Menampilkan juga wave yang sedang dihadapi.
        c). Membuat wavebonus dimana pada wave tersebut poin yang didapatkan digandakan 2.
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
        2. Penanganan Tabrakan dengan Suplai
            a). Memeriksa apakah pesawat menabrak power-up (buff).
            b). Menambahkan efek ketika suplai diambil, seperti menambah nyawa atau amunisi.
        3. Efek Visual Pesawat
            a). Membuat tampilan pesawat dengan SDL_Renderer.
            b). Membuat efek api beranimasi di bagian belakang pesawat; jika pesawat diam, apinya kecil, dan jika bergerak, apinya membesar.
    B. Sistem Peluru
        1. Membuat Visualisasi Peluru
            a). Mengatur ukuran dan warna peluru beserta trail (ekor).
        2. Menembakkan Peluru, Mengatur Kecepatan dan Jalurnya
            a). Membuat fungsi nembak() agar pesawat bisa menembakkan peluru.
            b). Mengatur kecepatan peluru menggunakan dx dan dy, memastikan peluru menghilang saat keluar dari layar.
        3. Menambah Amunisi dan Menampilkan Amunisi
            a). Menambahkan pembatasan amunisi awal (30 peluru).
            b).Menampilkan jumlah peluru yang tersisa dalam magasin menggunakan fungsi         tampilAmunisi().
        4. Mekanisme Reload Peluru
            a). Jika amunisi habis, pemain harus menunggu reload selesai sebelum bisa menembak lagi.
            b). Menampilkan teks “RELOADING...” di layar saat reload berlangsung.

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
