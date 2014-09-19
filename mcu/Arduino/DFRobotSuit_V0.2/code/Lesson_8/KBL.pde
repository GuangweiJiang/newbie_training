int RedLed=8;//定义第八引脚连接红灯
int GreenLed=7;//定义第七引脚连接绿灯
int i;//定义变量i
int j=0;//定义变量j

void buzzer()//蜂鸣器发出“嘀”声音子程序
{
        for(i=0;i<80;i++)    
        {
        digitalWrite(5,HIGH);//发声音
        delay(1);//延时1ms
        digitalWrite(5,LOW);//不发声音
        delay(1);//延时ms
        }
}
void key_scan()//按键扫描子程序
{
      int key_1,key_2,key_3;//定义变量
      
      key_1=analogRead(1);//读取模拟第一引脚的电压值
      key_2=analogRead(2);//读取模拟第二引脚的电压值
      key_3=analogRead(3);//读取模拟第三引脚的电压值
      
      if(key_1<204&&key_2<204&&key_3<204)//如果各按键电压值都小于204（即模拟值的1V），可以判断没有按键按下
      {
         return;//跳出本子函数
      }
      if(key_1>818)//如果按键1的电压值都大于818（即模拟值的4V），则可以判断按键1被按下
      {
         delay(10);//由于有抖动，所以延时100ms再一次判断
         if(key_1>818)//如果按键1的电压值都大于818（即模拟值的4V），则可以判断按键1确实被按下
         {
             buzzer();//蜂鸣器发出声音
             digitalWrite(RedLed,HIGH);//红灯亮
             digitalWrite(GreenLed,LOW);//绿灯灭
         }
         else //否则认为是抖动干扰，不做任何动作
         {
            return;//跳出本子函数
         }
      }
      if(key_2>818)//如果按键2的电压值都大于818（即模拟值的4V），则可以判断按键2被按下
      {
         delay(10);//由于有抖动，所以延时100ms再一次判断
         if(key_2>818)//如果按键2的电压值都大于818（即模拟值的4V），则可以判断按键2确实被按下
         {
             buzzer();//蜂鸣器发出声音
             digitalWrite(RedLed,LOW);//红灯灭
             digitalWrite(GreenLed,HIGH);//绿灯亮
         }
         else //否则认为是抖动干扰，不做任何动作
         {
            return;//跳出本子函数
         }
      }
      if(key_3>818)//如果按键3的电压值都大于818（即模拟值的4V），则可以判断按键3被按下
      {
         delay(10);//由于有抖动，所以延时100ms再一次判断
         if(key_3>818)//如果按键3的电压值都大于818（即模拟值的4V），则可以判断按键3确实被按下
         {
             buzzer();//蜂鸣器发出声音
             digitalWrite(RedLed,LOW);//红灯灭
             digitalWrite(GreenLed,LOW);//绿灯灭
         }
         else  //否则认为是抖动干扰，不做任何动作
         {
            return;//跳出本子函数
         }
      }
      
}
void setup()
{
   for(i=5;i<=8;i++)
  {
       pinMode(i,OUTPUT);//将5~8引脚设置为输出模式
  }  
}
void loop()
{
     while(1)
     {
        key_scan();//循环扫描按键
     }
}
