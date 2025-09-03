int led = 2; // led ยาว+ สั้น gnd
void setup()
{
 pinMode(led, OUTPUT); //ใช้ pinMode(2, OUTPUT); แบบนี้ก็ได้ ดูตัวอย่างข้อ 2
}
void loop()
{
 digitalWrite(led, HIGH); 
 delay(1000); // 
 digitalWrite(led, LOW); 
 delay(1000); 
}