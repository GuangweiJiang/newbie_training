int g;//定义变量g

void buzzer()//蜂鸣器发出“嘀”声音子程序
{
        for(g=0;g<80;g++)    
        {
        digitalWrite(8,HIGH);//发声音
        delay(1);//延时1ms
        digitalWrite(8,LOW);//不发声音
        delay(1);//延时ms
        }
}
void setup()
{
    pinMode(8,OUTPUT);//设置数字8引脚为输出方式
}
void loop()
{
    char i,j,k;//定义变量
    i=analogRead(5);//读取没有火焰时模拟口的电压值
    while(1)
    {
      j=analogRead(5);//不断的读取模拟口的电压值，时时监测
      k=j-i;//做差值
      if(k>123)//如果差值大于0.6（0.6为模拟值，123为对应的数字二进制值）说明有火焰
      {
          buzzer();//蜂鸣器发出声音
      }
      else
      {
          digitalWrite(8,LOW);//设置数字8口为低电平，蜂鸣器不响
      }
    } 
}
