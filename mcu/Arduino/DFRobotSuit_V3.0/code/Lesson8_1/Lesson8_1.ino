//项目八 – 震动传感器
int SensorLED = 13;       //定义LED为数字引脚13
int SensorINPUT = 3;      //连接震动开关到中断1，也就是数字引脚3 
unsigned char state = 0;

void setup() { 
  pinMode(SensorLED, OUTPUT);         //LED为输出模式
  pinMode(SensorINPUT, INPUT);        //震动开关为输入模式

  //低电平变高电平的过程中，触发中断1，调用blink函数
  attachInterrupt(1, blink, RISING);   
 }

void loop(){
      if(state!=0){              // 如果state不是0时
        state = 0;               // state值赋为0
        digitalWrite(SensorLED,HIGH);   // 亮灯
        delay(500);          //延时500ms
      }  
      else 
        digitalWrite(SensorLED,LOW);     // 否则，关灯
} 

void blink(){                //中断函数blink()
state++;             //一旦中断触发，state就不断自加
}

