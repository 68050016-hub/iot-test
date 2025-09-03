// 5v 10k  220 GND A0 Mid
 * โค้ดสำหรับทำเครื่องวัดความต้านทาน (Ohmmeter)
 * หลักการ: วงจรแบ่งแรงดัน (Voltage Divider)
 * วงจร: 5V --- [R_known] --- A0 --- [R_unknown] --- GND
 */

// กำหนดค่าตัวต้านทานอ้างอิง (R_known) ที่เราใช้ในวงจร
// เราเลือกใช้ 10k Ohm หรือ 10000 Ohm
const float R_KNOWN = 10000.0;

// ขา Analog ที่เราใช้วัดแรงดัน
const int ANALOG_PIN = A0;

void setup() {
  // เริ่มต้นการสื่อสารผ่าน Serial ที่ความเร็ว 9600 bps
  Serial.begin(9600);
}

void loop() {
  // 1. อ่านค่าจากขา Analog (จะได้ค่าระหว่าง 0 - 1023)
  int adc_value = analogRead(ANALOG_PIN);

  // 2. คำนวณหาค่าความต้านทานที่ไม่รู้จัก (R_unknown)
  // เราจะตรวจสอบก่อนว่า adc_value ไม่ใช่ 0 เพื่อป้องกันการหารด้วยศูนย์
  if (adc_value != 0) {
    float r_unknown = R_KNOWN * (1023.0 / adc_value - 1.0);

    // 3. แสดงผลลัพธ์ออกทาง Serial Monitor
    Serial.print("ADC Value: ");
    Serial.print(adc_value);
    Serial.print(", Calculated Resistance: ");
    
    // แสดงผลเป็น KΩ ถ้าค่ามากกว่า 1000
    if (r_unknown >= 30000) {
      Serial.print(r_unknown / 30000.0);
      Serial.println(" KOhms");
    } else {
      Serial.print(r_unknown);
      Serial.println(" Ohms");
    }

  } else {
    // ถ้า adc_value เป็น 0 แสดงว่าอาจไม่มีตัวต้านทานต่ออยู่ (Open circuit)
    Serial.println("Resistance: Infinite (Open Circuit)");
  }

  // หน่วงเวลา 1 วินาทีก่อนวัดค่าครั้งต่อไป
  delay(1000);
}