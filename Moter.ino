#include <Stepper.h> 

// --- ค่าคงที่ที่ต้องตั้งค่า --- ส่วนที่ 1: วงจรเซ็นเซอร์ LDR (ต่อที่ขา A0) 5V -> ขาข้างหนึ่งของตัวต้านทาน 10KΩ ขาอีกข้างของตัวต้านทาน 10KΩ -> ต่อเข้ากับขา A0 และต่อไปยังขาข้างหนึ่งของ LDRขาอีกข้างของ LDR -> ต่อเข้ากับ GND

// 1. ตั้งค่า Stepper Motor
const int STEPS_PER_REV = 2048; // จำนวนสเต็ปที่มอเตอร์ 28BYJ-48 ต้องหมุนเพื่อให้ครบ 1 รอบ
// ขาที่ต่อกับไดรเวอร์ ULN2003 (IN1, IN3, IN2, IN4)
Stepper myStepper(STEPS_PER_REV, 8, 10, 9, 11);

// 2. ตั้งค่า LDR
const int LDR_PIN = A0; // ขา Analog ที่ต่อกับ LDR
// *** ค่าแสงมาตรฐาน (Threshold) ***
// คุณต้องหาค่านี้ด้วยตัวเอง (ดูวิธีหาค่าด้านล่าง)
// สมมติว่าถ้าค่าแสงมากกว่า 500 คือสว่าง
const int LIGHT_THRESHOLD = 500;

// --- ตัวแปรสำหรับจำสถานะ ---
bool isRackOut = false; // ตัวแปรสำหรับจำว่า "ราวตากผ้าถูกยืดออกไปแล้วหรือยัง"
                        // false = ราวถูกเก็บอยู่, true = ราวยืดออกไปแล้ว

void setup() {
  Serial.begin(9600); // เริ่มการสื่อสารเพื่อดูค่าแสง
  // ไม่ต้องกำหนดความเร็วมอเตอร์ตรงนี้ เพราะโจทย์ต้องการให้เร็วที่สุด
}

void loop() {
  // 1. อ่านค่าจากเซ็นเซอร์ LDR (ค่าที่ได้จะอยู่ระหว่าง 0-1023)
  int lightValue = analogRead(LDR_PIN);

  // แสดงค่าแสงที่อ่านได้ทาง Serial Monitor ตลอดเวลาเพื่อช่วยในการดีบัก
  Serial.print("Light Value: ");
  Serial.println(lightValue);

  // 2. ตรวจสอบเงื่อนไขตามโจทย์
  
  // --- เงื่อนไขที่ 1: แสงมาก และ ราวยังไม่ถูกยืดออกไป ---
  if (lightValue > LIGHT_THRESHOLD && !isRackOut) {
    Serial.println("Bright light detected! Extending the rack...");
    
    // ตั้งความเร็วสูงสุด (ค่า RPM สูงสุดของมอเตอร์รุ่นนี้ประมาณ 15)
    myStepper.setSpeed(15); 
    
    // คำนวณจำนวนสเต็ปที่ต้องหมุน (3 รอบ ตามเข็มนาฬิกา)
    int stepsToMove = STEPS_PER_REV * 3;
    
    // สั่งให้มอเตอร์หมุน
    myStepper.step(stepsToMove);
    
    // อัปเดตสถานะว่า "ราวยืดออกไปแล้ว" เพื่อไม่ให้ทำงานซ้ำ
    isRackOut = true; 
    Serial.println("Rack extended.");
  }
  
  // --- เงื่อนไขที่ 2: แสงน้อย และ ราวกำลังยืดอยู่ ---
  else if (lightValue < LIGHT_THRESHOLD && isRackOut) {
    Serial.println("Dim light detected! Retracting the rack...");
    
    // ตั้งความเร็ว (ในโจทย์ไม่ได้บอก แต่ตั้งให้เท่ากันได้)
    myStepper.setSpeed(15);
    
    // คำนวณจำนวนสเต็ปที่ต้องหมุน (4 รอบ ทวนเข็มนาฬิกา)
    // การใส่เครื่องหมายลบ จะทำให้มอเตอร์หมุนกลับด้าน
    int stepsToMove = -STEPS_PER_REV * 4;
    
    // สั่งให้มอเตอร์หมุน
    myStepper.step(stepsToMove);
    
    // อัปเดตสถานะว่า "ราวถูกเก็บแล้ว"
    isRackOut = false; 
    Serial.println("Rack retracted.");
  }

  // หน่วงเวลาเล็กน้อยเพื่อไม่ให้โปรแกรมทำงานเร็วเกินไป
  delay(500); 
}