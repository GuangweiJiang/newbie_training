//设置控制各段的数字IO脚
int a=7;
int b=6;
int c=5;
int d=11;
int e=10;
int f=8;
int g=9;
int dp=4;

//显示数字1
void digital_1(void)
{
  unsigned char j;
  digitalWrite(c,LOW);//给数字5引脚低电平，点亮c段
  digitalWrite(b,LOW);//点亮b段
  for(j=7;j<=11;j++)//熄灭其余段
    digitalWrite(j,HIGH);
  digitalWrite(dp,HIGH);//熄灭小数点DP段
}
//显示数字2
void digital_2(void)
{
  unsigned char j;
  digitalWrite(b,LOW);
  digitalWrite(a,LOW);
  for(j=9;j<=11;j++)
    digitalWrite(j,LOW);
  digitalWrite(dp,HIGH);
  digitalWrite(c,HIGH);
  digitalWrite(f,HIGH);
}
//显示数字3
void digital_3(void)
{
  unsigned char j;
  digitalWrite(g,LOW);
  digitalWrite(d,LOW);
  for(j=5;j<=7;j++)
    digitalWrite(j,LOW);
  digitalWrite(dp,HIGH);
  digitalWrite(f,HIGH);
  digitalWrite(e,HIGH);
}
//显示数字4
void digital_4(void)
{
  digitalWrite(c,LOW);
  digitalWrite(b,LOW);
  digitalWrite(f,LOW);
  digitalWrite(g,LOW);
  digitalWrite(dp,HIGH);
  digitalWrite(a,HIGH);
  digitalWrite(e,HIGH);
  digitalWrite(d,HIGH);   
}
//显示数字5
void digital_5(void)
{
  unsigned char j;
  for(j=7;j<=9;j++)
    digitalWrite(j,LOW);
  digitalWrite(c,LOW);
  digitalWrite(d,LOW);
  digitalWrite(dp,HIGH);
  digitalWrite(b,HIGH);
  digitalWrite(e,HIGH); 
}
//显示数字6
void digital_6(void)
{
  unsigned char j;
  for(j=7;j<=11;j++)
    digitalWrite(j,LOW);
  digitalWrite(c,LOW);
  digitalWrite(dp,HIGH);
  digitalWrite(b,HIGH);   
}
//显示数字7
void digital_7(void)
{
  unsigned char j;
  for(j=5;j<=7;j++)
    digitalWrite(j,LOW);
  digitalWrite(dp,HIGH);
  for(j=8;j<=11;j++)
    digitalWrite(j,HIGH);
}
//显示数字8
void digital_8(void)
{
  unsigned char j;
  for(j=5;j<=11;j++)
    digitalWrite(j,LOW);
  digitalWrite(dp,HIGH);
}
void setup()
{
    int i;
    for(i=4;i<=11;i++)
    {
    pinMode(i,OUTPUT);//设置4~11口味输出模式
    }
}
void loop()
{  
   while(1)
   {
       digital_1();//显示数字1
       while(analogRead(0)>512);//如果读到模拟0口的值为0则说明有按键按下
       delay(200);//延时200ms
        digital_2();
        while(analogRead(0)>512);
       delay(200);
        digital_3();
        while(analogRead(0)>512);
       delay(200);
        digital_4();
        while(analogRead(0)>512);
       delay(200);
        digital_5();
        while(analogRead(0)>512);
       delay(200);
        digital_6();
        while(analogRead(0)>512);
       delay(200);
        digital_7();
        while(analogRead(0)>512);
       delay(200);
        digital_8();
        while(analogRead(0)>512);
       delay(200); 
   }
}
