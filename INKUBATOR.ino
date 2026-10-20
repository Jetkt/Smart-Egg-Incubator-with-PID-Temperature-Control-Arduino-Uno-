#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// --- Konfigurasi LCD I2C ---
LiquidCrystal_I2C lcd(0x27, 16, 2);

// --- Konfigurasi DHT ---
#define DHTPIN 2
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// --- Konfigurasi Output ---
#define RELAY_LAMP 7
#define FAN_PIN 9

// --- Set Point dan Histeresis ---
const float setPoint = 37.5;
const float hysteresis = 0.5;

// --- Kalibrasi ---
const float kalibrasiSuhu = -2.0;        // Sensor lebih tinggi 2 °C
const float kalibrasiKelembapan = -5.0;  // Sensor lebih tinggi 5%

// --- PWM Kipas ---
int pwmOutput = 0;
int fanMinPWM = 50;
int fanMaxPWM = 180;
float error = 0;

// Status
bool lampuNyala = false;
bool kipasNyala = false;

// Timing
unsigned long lastReadTime = 0;
const unsigned long readInterval = 2000;

float suhu = NAN;
float kelembapan = NAN;

void setup() {
  Serial.begin(9600);
  dht.begin();
  lcd.init();
  lcd.backlight();

  pinMode(RELAY_LAMP, OUTPUT);
  pinMode(FAN_PIN, OUTPUT);

  digitalWrite(RELAY_LAMP, HIGH); // Lampu OFF
  analogWrite(FAN_PIN, 0);        // Kipas OFF

  lcd.setCursor(0, 0);
  lcd.print("Inkubator Ayam");
  delay(2000);
  lcd.clear();
}

void loop() {
  unsigned long currentTime = millis();

  if (currentTime - lastReadTime >= readInterval) {
    float rawSuhu = dht.readTemperature();
    float rawKelembapan = dht.readHumidity();
    lastReadTime = currentTime;

    // Terapkan kalibrasi
    suhu = rawSuhu + kalibrasiSuhu;
    kelembapan = rawKelembapan + kalibrasiKelembapan;

    // Serial plotter suhu dan kelembapan
    Serial.print("Suhu:"); Serial.print(suhu);
    Serial.print(", Kelembapan:"); Serial.println(kelembapan);

    // Serial monitor PWM
    Serial.print("PWM kipas: ");
    Serial.println(pwmOutput);
  }

  if (isnan(suhu) || isnan(kelembapan)) {
    lcd.setCursor(0, 0);
    lcd.print("Err Sensor      ");
    lcd.setCursor(0, 1);
    lcd.print("Cek Koneksi     ");
    delay(500);
    return;
  }

  // Logika lampu
  if (suhu <= setPoint - hysteresis) {
    digitalWrite(RELAY_LAMP, LOW); // Lampu ON
    lampuNyala = true;
  } else if (suhu >= setPoint + hysteresis) {
    digitalWrite(RELAY_LAMP, HIGH); // Lampu OFF
    lampuNyala = false;
  }

  // Logika PWM kipas
  error = suhu - setPoint;
  if (error > 0) {
    pwmOutput = map(error * 100, 0, 200, fanMinPWM, fanMaxPWM);
    pwmOutput = constrain(pwmOutput, fanMinPWM, fanMaxPWM);
    analogWrite(FAN_PIN, pwmOutput);
    kipasNyala = true;
  } else {
    analogWrite(FAN_PIN, 0);
    pwmOutput = 0;
    kipasNyala = false;
  }

  // LCD baris 1
  lcd.setCursor(0, 0);
  lcd.print("S= ");
  lcd.print(suhu, 1);
  lcd.print((char)223);
  lcd.print("C ");
  lcd.print("H= ");
  lcd.print(kelembapan, 0);
  lcd.print("% ");

  // LCD baris 2
  lcd.setCursor(0, 1);
  if (lampuNyala && kipasNyala) {
    lcd.print("Lamp ON Fan ON ");
  } else if (lampuNyala && !kipasNyala) {
    lcd.print("Lamp ON Fan OFF ");
  } else if (!lampuNyala && kipasNyala) {
    lcd.print("Lamp OFF Fan ON ");
  } else {
    lcd.print("Lamp OFF Fan OFF ");
  }

  delay(200);
}
