//项目十一 - 可控舵机
#include <Servo.h>           // 声明调用Servo.h库
Servo myservo;               // 创建一个舵机对象
 
int potpin = 0;              // 连接到模拟口0               
int val;                     //变量val用来存储从模拟口0读到的值
 
void setup() { 
  myservo.attach(9);          // 将引脚9上的舵机与声明的舵机对象连接起来
} 
 
void loop() { 
  val = analogRead(potpin);         //从模拟口0读值，并通过val记录          
  val = map(val, 0, 1023, 0, 179);  //通过map函数进行数值转换    
  myservo.write(val);               // 给舵机写入角度  
  delay(15);                        // 延时15ms让舵机转到指定位置  
}

