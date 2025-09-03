void setup()
{
pinMode(2, OUTPUT);
pinMode(3, OUTPUT);
}
void loop()
{
 digitalWrite(2, HIGH); // แบบนี้หรือ 1   0 ก็ได้
 delay(1000);  // 1000milli = 1 วิ 250milli = 0.25 วิ  
 digitalWrite(2, LOW); 
 delay(1000); // 1 Hz
digitalWrite(3, HIGH); 
 delay(500); // 2Hz  
 digitalWrite(3, LOW); 
 delay(500); 
}