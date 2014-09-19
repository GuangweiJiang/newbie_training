//项目十二 –互动彩灯
int redPin = 9;                // R – digital 9    
int greenPin = 10;             // G – digital 10
int bluePin = 11;              // B – digital 11
int potRedPin = 0;             // 电位器1 – analog 0
int potGreenPin = 1;           // 电位器2 – analog 1
int potBluePin = 2;            // 电位器3 – analog 2

void setup(){
   pinMode(redPin,OUTPUT);
   pinMode(greenPin,OUTPUT);
   pinMode(bluePin,OUTPUT);
   Serial.begin(9600);           // 初始化串口
}

void loop(){
   int potRed = analogRead(potRedPin);     // potRed存储模拟口0读到的值
   int potGreen = analogRead(potGreenPin); // potGreen存储模拟口1读到的值
   int potBlue = analogRead(potBluePin);  // potBlue存储模拟口2读到的值
 
   int val1 = map(potRed,0,1023,0,255);     //通过map函数转换为0~255的值
   int val2 = map(potGreen,0,1023,0,255);
   int val3 = map(potBlue,0,1023,0,255);
   
   //串口依次输出Red，Green，Blue对应值
   Serial.print("Red:");                  
   Serial.print(val1);
   Serial.print("Green:");
   Serial.print(val2);
   Serial.print("Blue:");
   Serial.println(val3);
   
   colorRGB(val1,val2,val3);      // 让RGB LED 呈现对应颜色
}

//该函数用于显示颜色
void colorRGB(int red, int green, int blue){     
   analogWrite(redPin,constrain(red,0,255));
   analogWrite(greenPin,constrain(green,0,255));
   analogWrite(bluePin,constrain(blue,0,255));
}

