# 🥚 Smart Egg Incubator with PID Temperature Control (Arduino Uno)

Sistem kontrol otomatis suhu ruang inkubator telur ayam berbasis mikrokontroler **Arduino Uno** menggunakan algoritma **PID (Proportional-Integral-Derivative)**. Sistem ini dirancang untuk menjaga kestabilan suhu ruang penetasan secara presisi pada titik ideal **37.5°C** guna mengoptimalkan tingkat keberhasilan penetasan telur.

---

## 📌 Deskripsi Proyek

Keberhasilan penetasan telur sangat bergantung pada kestabilan suhu lingkungan dalam inkubator. Kenaikan atau penurunan suhu yang drastis dapat menggagalkan proses embrio telur. 

Proyek ini mengimplementasikan metode **kendali PID** untuk mengatur daya pemanas (**lampu bohlam**) dan sistem pendingin pembuang panas (**exhaust blower**) secara otomatis. Ketika suhu berada di bawah setpoint (37.5°C), lampu bohlam diatur untuk menaikkan suhu. Jika terjadi kenaikan suhu berlebih (*overshoot*), *blower* akan otomatis menyala untuk membuang hawa panas berlebih keluar dari inkubator.

---

## ⚙️ Fitur Utama

- **Kontrol Suhu Presisi Berbasis PID:** Menghitung nilai *error* secara *real-time* untuk menstabilkan suhu pada titik setpoint 37.5°C.
- **Aktuator Pemanas (Heater):** Lampu bohlam sebagai sumber pemanas utama ruang inkubator.
- **Aktuator Pembuang Panas (Exhaust Blower):** Kipas/blower aktif otomatis untuk membuang hawa panas jika suhu melebihi ambang batas toleransi.
- **Pemantauan Real-Time:** Pembacaan data sensor suhu secara terus-menerus untuk umpan balik (*feedback control*).

---

## 🛠️ Perangkat Keras & Komponen (Hardware)

- **Mikrokontroler:** Arduino Uno
- **Sensor Suhu:** Sensor Suhu Presisi (DS18B20 / DHT22)
- **Aktuator Pemanas:** Lampu Bohlam (Incandescent Lamp)
- **Aktuator Pembuang Panas:** DC Blower / Exhaust Fan
- **Driver Aktuator:** Modul Relay / AC Dimmer Module
- **Catu Daya:** Power Supply 12V / 5V

---

## 📐 Prinsip Kerja & Algoritma PID

1. **Pembacaan Sensor:** Sensor membaca kondisi suhu riil (*Process Value* / PV) di dalam inkubator.
2. **Kalkulasi Error:** Arduino menghitung nilai selisih (*Error*):
   `Error = Setpoint (37.5°C) - Suhu Riil`
3. **Aksi Kontrol PID:**
   - **Proportional (P):** Merespons besarnya nilai *error* saat ini.
   - **Integral (I):** Mengakumulasi *error* dari waktu ke waktu untuk menghilangkan *steady-state error*.
   - **Derivative (D):** Memprediksi laju perubahan *error* untuk mencegah *overshoot*.
4. **Respon Aktuator:**
   - Jika Suhu < 37.5°C: Lampu bohlam menyala/redup-terang sesuai kalkulasi daya PID.
   - Jika Suhu > 37.5°C: Exhaust blower menyala untuk membuang hawa panas hingga suhu kembali normal.

---

## 📁 Struktur Repositori

```text
├── INKUBATOR.ino    # Kode program utama Arduino Uno (PID & Kontrol Sensor)
└── README.md        # Dokumentasi resmi proyek
