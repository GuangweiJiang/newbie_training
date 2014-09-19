int ledPin=8; //设定控制LED的数字IO脚
void setup()
{
    pinMode(ledPin,OUTPUT);//设定数字IO口的模式，OUTPUT 为输出
}
void loop()
{  
    digitalWrite(ledPin,HIGH); //设定PIN8脚为HIGH = 5V左右
    delay(1000); //设定延时时间，1000 = 1秒
    digitalWrite(ledPin,LOW); //设定PIN8脚为LOW = 0V
    delay(1000); //设定延时时间，1000 = 1秒
} 
