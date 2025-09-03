// กำหนดขา Pin ที่ใช้งาน
const int led1Pin = 2;      // Pin สำหรับ LED ดวงที่ 1
const int led2Pin = 3;      // Pin สำหรับ LED ดวงที่ 2
const int switchPin = 7;    // Pin สำหรับสวิตช์

// ตัวแปรสำหรับจับเวลาของ LED 1
unsigned long previousMillis1 = 0;
const long intervalOn1 = 1000;   // เวลาที่ LED 1 ติด (1 วินาที)
const long intervalOff1 = 1000;  // เวลาที่ LED 1 ดับ (1 วินาที)
int led1State = LOW;             // สถานะปัจจุบันของ LED 1

// ตัวแปรสำหรับจับเวลาของ LED 2
unsigned long previousMillis2 = 0;
const long intervalOn2 = 3000;   // เวลาที่ LED 2 ติด (3 วินาที)
const long intervalOff2 = 3000;  // เวลาที่ LED 2 ดับ (3 วินาที)
int led2State = LOW;             // สถานะปัจจุบันของ LED 2

void setup() {
  // ตั้งค่า Pin Mode
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  // ตั้งค่า Pin ของสวิตช์เป็น INPUT_PULLUP เพื่อใช้ตัวต้านทานภายในบอร์ด
  // เมื่อไม่กด สวิตช์จะมีสถานะเป็น HIGH, เมื่อกดจะเป็น LOW
  pinMode(switchPin, INPUT_PULLUP);
}

void loop() {
  // อ่านค่าเวลาปัจจุบันในทุกๆ รอบของ loop
  unsigned long currentMillis = millis();
  
  // อ่านสถานะของสวิตช์
  int switchState = digitalRead(switchPin);

  // --- ส่วนควบคุม LED ดวงที่ 1 ---
  if (switchState == LOW) { // ถ้าสวิตช์ถูกกด (LOW เพราะใช้ PULLUP)
    digitalWrite(led1Pin, HIGH); // ให้ LED 1 ติดค้าง
  } else { // ถ้าสวิตช์ไม่ได้ถูกกด
    // ทำงานกระพริบตามปกติ
    if (led1State == HIGH && currentMillis - previousMillis1 >= intervalOn1) {
      // ถ้า LED กำลังติด และครบเวลาที่กำหนดแล้ว
      led1State = LOW;  // เปลี่ยนสถานะเป็นดับ
      previousMillis1 = currentMillis; // บันทึกเวลาที่เปลี่ยนสถานะ
    } else if (led1State == LOW && currentMillis - previousMillis1 >= intervalOff1) {
      // ถ้า LED กำลังดับ และครบเวลาที่กำหนดแล้ว
      led1State = HIGH; // เปลี่ยนสถานะเป็นติด
      previousMillis1 = currentMillis; // บันทึกเวลาที่เปลี่ยนสถานะ
    }
    digitalWrite(led1Pin, led1State); // สั่งให้ LED แสดงผลตามสถานะ
  }

  // --- ส่วนควบคุม LED ดวงที่ 2 (ทำงานอิสระ) ---
  if (led2State == HIGH && currentMillis - previousMillis2 >= intervalOn2) {
    // ถ้า LED กำลังติด และครบเวลาที่กำหนดแล้ว
    led2State = LOW;  // เปลี่ยนสถานะเป็นดับ
    previousMillis2 = currentMillis; // บันทึกเวลาที่เปลี่ยนสถานะ
  } else if (led2State == LOW && currentMillis - previousMillis2 >= intervalOff2) {
    // ถ้า LED กำลังดับ และครบเวลาที่กำหนดแล้ว
    led2State = HIGH; // เปลี่ยนสถานะเป็นติด
    previousMillis2 = currentMillis; // บันทึกเวลาที่เปลี่ยนสถานะ
  }
  digitalWrite(led2Pin, led2State); // สั่งให้ LED แสดงผลตามสถานะ
}