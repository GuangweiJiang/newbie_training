
//设置控制Led的数字IO脚
int Led1 = 1;
int Led2 = 2;
int Led3 = 3;
int Led4 = 4;
int Led5 = 5;
int Led6 = 6;
//led灯花样显示样式1子程序
void style_1(void)
{
  unsigned char j;
  for(j=1;j<=6;j++)//每隔200ms依次点亮1~6引脚相连的led灯
  {
    digitalWrite(j,HIGH);//点亮j引脚相连的led灯
    delay(200);//延时200ms
  }
  for(j=6;j>=1;j--)//每隔200ms依次熄灭6~1引脚相连的led灯
  {
    digitalWrite(j,LOW);//熄灭j引脚相连的led灯
    delay(200);//延时200ms
  } 
}
//灯闪烁子程序
void flash(void)
{   
  unsigned char j,k;
  for(k=0;k<=1;k++)//闪烁两次
  {
    for(j=1;j<=6;j++)//点亮1~6引脚相连的led灯
      digitalWrite(j,HIGH);//点亮与j引脚相连的led灯
    delay(200);//延时200ms
    for(j=1;j<=6;j++)//熄灭1~6引脚相连的led灯
      digitalWrite(j,LOW);//熄灭与j引脚相连的led灯
    delay(200);//延时200ms
  }
}
//led灯花样显示样式2子程序
void style_2(void)
{
  unsigned char j,k;
  k=1;//设置k的初值为1
  for(j=3;j>=1;j--)
  {   
    digitalWrite(j,HIGH);//点亮灯
    digitalWrite(j+k,HIGH);//点亮灯
    delay(400);//延时400ms
    k +=2;//k值加2
  }
  k=5;//设置k值为5
  for(j=1;j<=3;j++)
  {
    digitalWrite(j,LOW);//熄灭灯
    digitalWrite(j+k,LOW);//熄灭灯
    delay(400);//延时400ms
    k -=2;//k值减2
  }
}
//led灯花样显示样式3子程序
void style_3(void)
{
  unsigned char j,k;//led灯花样显示样式3子程序
  k=5;//设置k值为5
  for(j=1;j<=3;j++)
  {
    digitalWrite(j,HIGH);//点亮灯
    digitalWrite(j+k,HIGH);//点亮灯
    delay(400);//延时400ms
    digitalWrite(j,LOW);//熄灭灯
    digitalWrite(j+k,LOW);//熄灭灯
    k -=2;//k值减2
  }
  k=3;//设置k值为3
  for(j=2;j>=1;j--)
  {   
    digitalWrite(j,HIGH);//点亮灯
    digitalWrite(j+k,HIGH);//点亮灯
    delay(400);//延时400ms
    digitalWrite(j,LOW);//熄灭灯
    digitalWrite(j+k,LOW);//熄灭灯
    k +=2;//k值加2
  } 
}
void setup()
{ 
  unsigned char i;
  for(i=1;i<=6;i++)//依次设置1~6个数字引脚为输出模式
    pinMode(i,OUTPUT);//设置第i个引脚为输出模式
}
void loop()
{   
  style_1();//样式1
  flash();//闪烁
  style_2();//样式2
  flash();//闪烁
  style_3();//样式3
  flash();//闪烁
}



