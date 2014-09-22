//项目三 -- 互动交通信号灯
int carRed = 12; //设置汽车灯
int carYellow = 11;
int carGreen = 10;
int button = 9; //按钮引脚
int pedRed = 8; //设置行人灯
int pedGreen = 7;
int crossTime =5000;//允许行人通过的时间
unsigned long changeTime;//按钮按下后的时间

void setup() {
        //所有LED设置为输出模式
  	pinMode(carRed, OUTPUT);
  	pinMode(carYellow, OUTPUT);
  	pinMode(carGreen, OUTPUT);
  	pinMode(pedRed, OUTPUT);
        pinMode(pedGreen, OUTPUT);
        pinMode(button, INPUT); //按钮设置为输入模式
        digitalWrite(carGreen, HIGH); //车行
	digitalWrite(pedRed, LOW);  //人停
}

void loop() {
	int state = digitalRead(button);
        //检测按钮是否被按下，并且是否距上次按下后有5秒的等待时间
        if(state == HIGH && (millis() - changeTime)> 5000){
               //调用变灯函数
               changeLights();
        }
}

void changeLights() {
	digitalWrite(carGreen, LOW); //汽车绿灯灭
	digitalWrite(carYellow, HIGH); //汽车黄灯亮
	delay(2000); //等待2秒
		
	digitalWrite(carYellow, LOW); //汽车黄灯灭
	digitalWrite(carRed, HIGH); //汽车红灯亮
        delay(1000); //为安全考虑等待1秒
		
	digitalWrite(pedRed, LOW); //行人红灯灭
	digitalWrite(pedGreen, HIGH); //行人绿灯亮

	delay(crossTime); //等待一个通过时间
		
	//闪烁行人灯绿灯，提示可过马路时间快到
        for (int x=0; x<10; x++) {
	        digitalWrite(pedGreen, HIGH);
		delay(250);
		digitalWrite(pedGreen, LOW);
		delay(250);
         }
 				
        digitalWrite(pedRed, HIGH);//行人红灯亮
	delay(500);

	digitalWrite(carRed, LOW); //汽车红灯灭
	digitalWrite(carYellow, HIGH); //汽车黄灯亮	
	delay(1000);
	digitalWrite(carYellow, LOW); //汽车黄灯灭
        digitalWrite(carGreen, HIGH); //汽车绿灯亮

	changeTime = millis(); //记录自上一次灯变化的时间
	//返回到主函数循环中
}

