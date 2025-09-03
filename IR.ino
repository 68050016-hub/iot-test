// --- กำหนดขาที่ใช้งาน ---
const int SENSOR_PIN = 2;
const int LED_PIN = 12;

// กำหนดขาสำหรับ 7-Segment แต่ละส่วน (a, b, c, d, e, f, g)
const int segmentPins[] = {3, 4, 5, 6, 7, 8, 9};

// --- Pattern การเปิด/ปิด LED ของ 7-Segment เพื่อสร้างตัวเลข 0-9 ---
// 1 = HIGH (เปิดไฟ), 0 = LOW (ปิดไฟ) สำหรับ Common Cathode
// ตำแหน่งใน Array ตรงกับ (a, b, c, d, e, f, g)
byte numbers[10][7] = {
  { 1, 1, 1, 1, 1, 1, 0 },  // เลข 0
  { 0, 1, 1, 0, 0, 0, 0 },  // เลข 1
  { 1, 1, 0, 1, 1, 0, 1 },  // เลข 2
  { 1, 1, 1, 1, 0, 0, 1 },  // เลข 3
  { 0, 1, 1, 0, 0, 1, 1 },  // เลข 4
  { 1, 0, 1, 1, 0, 1, 1 },  // เลข 5
  { 1, 0, 1, 1, 1, 1, 1 },  // เลข 6
  { 1, 1, 1, 0, 0, 0, 0 },  // เลข 7
  { 1, 1, 1, 1, 1, 1, 1 },  // เลข 8
  { 1, 1, 1, 1, 0, 1, 1 }   // เลข 9
};

// --- ตัวแปรที่ใช้ในการทำงาน ---
int count = 0;              // ตัวแปรนับค่า
int sensorState = HIGH;     // สถานะปัจจุบันของเซ็นเซอร์ (HIGH = ไม่เจอวัตถุ)
int lastSensorState = HIGH; // สถานะก่อนหน้าของเซ็นเซอร์ (สำหรับตรวจจับการเปลี่ยนแปลง)


void setup() {
  Serial.begin(9600); // สำหรับดีบัก

  // กำหนดโหมดของ Pin
  pinMode(SENSOR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  for (int i = 0; i < 7; i++) {
    pinMode(segmentPins[i], OUTPUT);
  }
  
  // แสดงเลข 0 ตอนเริ่มต้น
  displayNumber(0); 
}

void loop() {
  // อ่านค่าจากเซ็นเซอร์ (ปกติเป็น HIGH, ถ้าเจอวัตถุจะเป็น LOW)
  sensorState = digitalRead(SENSOR_PIN);

  // ตรวจจับ "จังหวะ" ที่สถานะเปลี่ยนจาก "ไม่เจอ" เป็น "เจอ"
  if (sensorState != lastSensorState) {
    if (sensorState == LOW) { // LOW หมายถึงเจอวัตถุ
      count++; // นับเพิ่ม 1
      Serial.print("Object detected! Count is now: ");
      Serial.println(count);

      // ถ้านับเกิน 9 ให้วนกลับไปที่ 0
      if (count > 9) {
        count = 0;
      }
      
      // อัปเดตการแสดงผลบน 7-Segment
      displayNumber(count);
      
      // --- ตรวจสอบเงื่อนไขพิเศษ ---
      if (count == 8) {
        Serial.println("Count is 8! Blinking LED...");
        blinkLED(); // เรียกฟังก์ชันให้ LED กระพริบ
      }
    }
    delay(50); // Delay เล็กน้อยเพื่อป้องกันการสั่นของสัญญาณ (Debounce)
  }
  
  // อัปเดตสถานะล่าสุดของเซ็นเซอร์
  lastSensorState = sensorState;
}

// --- ฟังก์ชันสำหรับแสดงตัวเลขบน 7-Segment ---
void displayNumber(int number) {
  for (int i = 0; i < 7; i++) {
    digitalWrite(segmentPins[i], numbers[number][i]);
  }
}

// --- ฟังก์ชันสำหรับสั่งให้ LED กระพริบ 2 ครั้ง ---
void blinkLED() {
  digitalWrite(LED_PIN, HIGH);
  delay(200);
  digitalWrite(LED_PIN, LOW);
  delay(200);
  digitalWrite(LED_PIN, HIGH);
  delay(200);
  digitalWrite(LED_PIN, LOW);
}

//ส่วนที่ 1: โมดูลเซ็นเซอร์ IR (ต่อที่ขา 2) ขา VCC ของโมดูล -> ขา 5V ของ Arduino ขา GND ของโมดูล -> ขา GND ของ Arduino ขา OUT (หรือ D0) ของโมดูล -> ขา Digital 2 ของ Arduino

//ส่วนที่ 2: LED กระพริบ (ต่อที่ขา 12) ขา Digital 12 ของ Arduino -> ตัวต้านทาน 220Ω -> ขาบวก (ยาว) ของ LED ขาลบ (สั้น) ของ LED -> ขา GND ของ Arduino

//ส่วนที่ 3: 7-Segment Display (ต่อที่ขา 3 ถึง 9)

//ขา a ของ 7-Segment -> ผ่าน R 220Ω -> ขา Digital 3

//ขา b ของ 7-Segment -> ผ่าน R 220Ω -> ขา Digital 4

//ขา c ของ 7-Segment -> ผ่าน R 220Ω -> ขา Digital 5

//ขา d ของ 7-Segment -> ผ่าน R 220Ω -> ขา Digital 6

//ขา e ของ 7-Segment -> ผ่าน R 220Ω -> ขา Digital 7

//ขา f ของ 7-Segment -> ผ่าน R 220Ω -> ขา Digital 8

//ขา g ของ 7-Segment -> ผ่าน R 220Ω -> ขา Digital 9

//ขา COM (ขากลาง) ของ 7-Segment -> ขา GND ของ Arduino