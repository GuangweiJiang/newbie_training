#define LED_GREEN 9//定义与绿灯连接的引脚
#define LED_YELLOW 10//定义与黄灯连接的引脚
#define LED_RED 11//定义与红灯连接的引脚
void setup()
{
  unsigned char j;
  for(j=9;j<=11;j++)//设置与红绿黄灯连接的引脚为输出模式
  {
    pinMode(j,OUTPUT);
  }
}
void loop()
{
  int i;
  while(1)
  {
    i=analogRead(0);//读取温度传感器电压值
    if(i>41&&i<61)//温度在20~30度之间
    {
      digitalWrite(LED_GREEN,HIGH);//绿灯亮
      digitalWrite(LED_YELLOW,LOW);//黄灯灭
      digitalWrite(LED_RED,LOW);//红灯灭
    }
    else if(i>=61&&i<81)//温度在30~40度之间
    {
      digitalWrite(LED_YELLOW,HIGH);//黄灯亮
      digitalWrite(LED_GREEN,LOW);//绿灯灭
      digitalWrite(LED_RED,LOW);//红灯灭
    }
    else//温度在20度以下和40度以上
    {
      digitalWrite(LED_RED,HIGH);//红灯亮
      digitalWrite(LED_YELLOW,LOW);//黄灯灭
      digitalWrite(LED_GREEN,LOW);//绿灯灭
    }
  }
}

