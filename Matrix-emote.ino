#include "Arduino_LED_Matrix.h" // Include the LED_Matrix Library

ArduinoLEDMatrix matrix; // Create an instance of the ArduinoLEDMatrix class

// 2D Array สำหรับเก็บรูปแบบรูปหัวใจ
uint8_t heartFrame[8][12] = {
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0 },
  { 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0 },
  { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
  { 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0 },
  { 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0 },
  { 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0 }
};

void setup() {
  matrix.begin(); // เริ่มต้นการทำงานของ LED matrix
}

void loop() {
  // แสดงรูปหัวใจบน LED matrix
  matrix.renderBitmap(heartFrame, 8, 12);
  delay(1000); // หน่วงเวลา 1 วินาที

  // ล้างหน้าจอ (ทำให้ LED ทุกดวงดับ)
  matrix.clear();
  delay(1000); // หน่วงเวลา 1 วินาที
}