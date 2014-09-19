#define BUZZER 10//蜂鸣器
#define LED_RED 11//红灯
#define IR_IN  8  //红外接收

int Pulse_Width=0;//存储脉宽 
int  ir_code=0x00;//命令值

void timer1_init(void)//定时器初始化函数
{
  TCCR1A = 0X00; 
  TCCR1B = 0X05;//给定时器时钟源  
  TCCR1C = 0X00;
  TCNT1 = 0X00;
  TIMSK1 = 0X00;	//禁止定时器溢出中断
}
void remote_deal(void)//执行译码结果函数
{ 
  switch(ir_code)
  {
  case 0xff00://停止
    digitalWrite(LED_RED,LOW);//红灯不亮
    digitalWrite(BUZZER,LOW);//蜂鸣器不响
    break;
  case 0xfe01://VOL+
    digitalWrite(LED_RED,HIGH);//红灯亮
    break;
  case 0xf609://VOL-
    digitalWrite(BUZZER,HIGH);//蜂鸣器响
    break;
  }
}
char logic_value()//判断逻辑值“0”和“1”子函数
{
  while(!(digitalRead(8))); //低等待
  Pulse_Width=TCNT1;
  TCNT1=0;
  if(Pulse_Width>=7&&Pulse_Width<=10)//低电平560us
  {
    while(digitalRead(8));//是高就等待
    Pulse_Width=TCNT1;
    TCNT1=0;
    if(Pulse_Width>=7&&Pulse_Width<=10)//接着高电平560us
      return 0;
    else if(Pulse_Width>=25&&Pulse_Width<=27) //接着高电平1.7ms
      return 1;
  }
  return -1;
}
void pulse_deal()//接收地址码和命令码脉冲函数
{
  int i;
  //执行8个0
  for(i=0; i<8; i++)
  {
    if(logic_value() != 0) //不是0
        return;
  }
  //执行6个1
  for(i=0; i<6; i++)
  {
    if(logic_value()!= 1) //不是1
        return;
  }
  //执行1个0
  if(logic_value()!= 0) //不是0
      return;
  //执行1个1
  if(logic_value()!= 1) //不是1
      return;


  //解析遥控器编码中的command指令
  ir_code=0x00;//清零
  for(i=0; i<16;i++ )
  {
    if(logic_value() == 1)
    {
      ir_code |=(1<<i);
    }
  }
}
void remote_decode(void)//译码函数
{
  TCNT1=0X00;       
  while(digitalRead(8))//是高就等待
  {
    if(TCNT1>=1563)  //当高电平持续时间超过100ms，表明此时没有按键按下
    {
      ir_code = 0xff00;
      return;
    }  
  }

  //如果高电平持续时间不超过100ms
  TCNT1=0X00;

  while(!(digitalRead(8))); //低等待
  Pulse_Width=TCNT1;
  TCNT1=0;
  if(Pulse_Width>=140&&Pulse_Width<=141)//9ms
  {

    while(digitalRead(8));//是高就等待
    Pulse_Width=TCNT1;
    TCNT1=0;
    if(Pulse_Width>=68&&Pulse_Width<=72)//4.5ms
    {
      pulse_deal();
      return;
    }
    else if(Pulse_Width>=34&&Pulse_Width<=36)//2.25ms
    {
      while(!(digitalRead(8)));//低等待
      Pulse_Width=TCNT1;
      TCNT1=0;
      if(Pulse_Width>=7&&Pulse_Width<=10)//560us
      {
        return; 
      }
    }
  }
}
void setup()
{
  unsigned char i;
  pinMode(LED_RED,OUTPUT);//设置与红灯连接的引脚为输出模式
  pinMode(BUZZER,OUTPUT);//设置与蜂鸣器连接的引脚为输出模式
  pinMode(IR_IN,INPUT);//设置红外接收引脚为输入
}
void loop()
{  
  timer1_init();//定时器初始化
  while(1)
  {
    remote_decode();  //译码
    remote_deal();   //执行译码结果
  }  
}



