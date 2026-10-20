# 🥚 Smart Egg Incubator with PID Fan Speed Control (Arduino Uno)

Sistem kontrol otomatis suhu ruang inkubator telur ayam berbasis mikrokontroler **Arduino Uno** menggunakan algoritma **PID (Proportional-Integral-Derivative)**. PID digunakan untuk mengatur kecepatan **DC Fan (Blower)** secara dinamis via sinyal **PWM** guna menstabilkan suhu ruang penetasan secara presisi pada titik ideal **37.5°C**.

---

## 📌 Deskripsi Proyek

Kestabilan suhu di dalam ruang inkubator sangat menentukan tingkat keberhasilan penetasan telur. Kenaikan suhu di atas ambang ideal dapat merusak embrio.

Proyek ini mengimplementasikan algoritma **PID** pada kontroler untuk mengatur laju pembuangan/sirkulasi hawa panas melalui **DC Fan (Exhaust Blower)**. **Lampu bohlam** difungsikan sebagai sumber pemanas utama (*heater*). Ketika suhu mulai mendekati atau melebihi titik *setpoint* (37.5°C), algoritma PID akan menghitung dan menyesuaikan kecepatan putar *DC Fan* secara presisi (via PWM) sehingga suhu tetap konstan tanpa terjadi fluktuasi berlebih (*overshoot*).

---

## ⚙️ Fitur Utama

- **Kontrol Kecepatan Kipas Berbasis PID (PWM):** Menyesuaikan daya putar *DC Fan* secara *real-time* berdasarkan kalkulasi PID untuk meregulasi suhu.
- **Pemanas Terstruktur:** Lampu bohlam sebagai sumber panas utama inkubator.
- **Respon Dinamis & Presisi:** Meminimalkan lonjakan suhu (*overshoot*) dengan sirkulasi udara yang terkontrol secara otomatis.
- **Monitoring Suhu Real-Time:** Pembacaan data sensor secara berkelanjutan sebagai masukan *feedback loop* PID.

---

## 🛠️ Perangkat Keras & Komponen (Hardware)

- **Mikrokontroler:** Arduino Uno
- **Sensor Suhu:** Sensor Suhu Presisi DHT22
- **Aktuator Utama PID:** 12 V DC Fan (Kecepatan Diatur PWM)
- **Aktuator Pemanas:** Lampu Bohlam 
- **Driver Aktuator:** Transistor Driver (PWM Fan) & Modul Relay (Lampu)
- **Catu Daya:** Power Supply 12V 

---

## 📐 Prinsip Kerja & Algoritma PID

1. **Pembacaan Sensor:** Sensor membaca kondisi suhu riil (*Process Value* / PV) dalam ruang inkubator.
2. **Kalkulasi Error:** Arduino menghitung selisih antara suhu riil dengan target suhu (*Setpoint* = 37.5°C):
   `Error = Suhu Riil - Setpoint (37.5°C)`
3. **Kalkulasi Sinyal PID:**
   - **Proportional (P):** Merespons besarnya *error* suhu saat ini secara langsung ke kecepatan kipas.
   - **Integral (I):** Mengakumulasi *error* dari waktu ke waktu untuk menghilangkan *steady-state error*.
   - **Derivative (D):** Meredam laju perubahan kenaikan suhu cepat untuk mencegah lonjakan berlebih.
4. **Respon Aktuator:**
   - **DC Fan (Blower):** Menerima keluaran nilai PID dalam bentuk sinyal **PWM (0–255)** untuk mengatur kecepatan putaran kipas pembuang panas secara linier dan halus.
   - **Lampu Bohlam:** Mempertahankan kehangatan ruang inkubator sebagai sumber panas utama.

---

## 📁 Struktur Repositori

```text
├── INKUBATOR.ino    # Kode program utama Arduino Uno (Algoritma PID, PWM Fan & Sensor)
└── README.md        # Dokumentasi resmi proyek
