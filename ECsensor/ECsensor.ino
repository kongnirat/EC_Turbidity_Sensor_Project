#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int sensorPin = A1; // กำหนดพินที่เชื่อมต่อกับเซนเซอร์
float volt;         // ตัวแปรเก็บค่าแรงดันไฟฟ้า (Voltage)
float ntu;          // ตัวแปรเก็บค่า NTU (ค่าความขุ่น)

void setup() {
  Serial.begin(9600);  // เริ่มการสื่อสารผ่าน Serial Monitor
  lcd.begin();         // เริ่มการทำงานของ LCD
  lcd.backlight();     // เปิดไฟพื้นหลังของ LCD
}

void loop() {
  volt = 0; // รีเซ็ตค่าแรงดันไฟฟ้า

  // อ่านค่าแรงดันจากเซนเซอร์ 800 ครั้งและหาค่าเฉลี่ย
  for (int i = 0; i < 800; i++) {
    // แปลงค่า analog เป็นแรงดันไฟฟ้า (0-5V)
    volt += (analogRead(sensorPin) / 1023.0) * 5.0;
  }
  volt /= 800.0;                       // หาค่าเฉลี่ยของแรงดัน
  volt = roundf(volt * 100) / 100.0;   // ปัดค่าแรงดันเป็นทศนิยม 2 ตำแหน่ง

  // คำนวณค่า NTU ตามสูตรที่กำหนด
  if (volt < 2.5) {
    ntu = 3000; // กรณีแรงดันต่ำกว่า 2.5V ให้ค่า NTU เป็น 3000
  } else {
    // ใช้สมการเพื่อคำนวณค่า NTU จากแรงดัน
    ntu = -1120.4 * (volt * volt) + 5742.3 * volt - 4353.8;
  }

  // แสดงผลแรงดันไฟฟ้าและค่า NTU บน LCD
  lcd.clear();               // ล้างหน้าจอ LCD
  lcd.setCursor(0, 0);       // กำหนดตำแหน่งเริ่มต้นที่แถวแรก
  lcd.print(volt);           // แสดงค่าแรงดัน
  lcd.print(" V");

  lcd.setCursor(0, 1);       // กำหนดตำแหน่งที่แถวที่สอง
  lcd.print(ntu);            // แสดงค่า NTU
  lcd.print(" NTU");

  delay(10);                 // หน่วงเวลา 10 ms ก่อนวนลูปใหม่
}
