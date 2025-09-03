// กำหนด Pin ที่ใช้ด้วย #define
#define led1Pin 2
#define led2Pin 3
#define switchPin 7

// unsigned long เหมือน int แต่เก็บได้มากกว่า 
unsigned long previousMillis1 = 0, previousMillis2 = 0;

// สถานะการเปิด/ปิดของ LED 
int led1State = LOW, led2State = LOW;

void setup() { // ถูกเปลี่ยนค่าแล้ว
  pinMode(led1Pin, OUTPUT); //  pinMode(2, OUTPUT);  
  pinMode(led2Pin, OUTPUT); //  pinMode(3, OUTPUT); 
  pinMode(switchPin, INPUT_PULLUP); //pinMode(7, INPUT_PULLUP);
}

void loop() {
  unsigned long currentMillis = millis(); // อ่านเวลาปัจจุบัน

  // --- ส่วนควบคุม LED 1 และสวิตช์ ---
  // คอมไพเลอร์จะเห็นโค้ดส่วนนี้เป็น if (digitalRead(7) == LOW) { ... }
  if (digitalRead(switchPin) == LOW) { // ถ้าปุ่มกดอยู่
    digitalWrite(led1Pin, HIGH);       // ไฟติด
    led1State = HIGH;               
  } else { // ถ้าปุ่มถูกปล่อย (ให้กระพริบ)
    if (currentMillis - previousMillis1 >= 1000) {
      previousMillis1 = currentMillis;    // บันทึกเวลาใหม่
      led1State = !led1State;           // สลับสถานะ (ถ้าติดให้ดับ, ถ้าดับให้ติด)
      digitalWrite(led1Pin, led1State); // สั่งงาน LED
    }
  }

  // --- ส่วนควบคุม LED 2 (กระพริบตลอดเวลา) ---
  if (currentMillis - previousMillis2 >= 3000) {
    previousMillis2 = currentMillis;      // บันทึกเวลาใหม่
    led2State = !led2State;             // สลับสถานะ
    digitalWrite(led2Pin, led2State);   // สั่งงาน LED
  }
}