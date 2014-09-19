//项目二 -- S.O.S信号
int ledPin = 10;
void setup() {
        pinMode(ledPin, OUTPUT);
}
void loop() {
       // 三个快闪烁来表示字母“S”
       for(int x=0;x<3;x++){
        digitalWrite(ledPin,HIGH);            //设置LED 为开
        delay(150);                           //延时150毫秒
        digitalWrite(ledPin,LOW);             //设置LED 为关
        delay(100);                           //延时100毫秒
        }
       
        //100毫秒延时产生字母之间的间隙
        delay(100);

        //三个短闪烁来表示字母“O”
       for(int x=0;x<3;x++){
        digitalWrite(ledPin,HIGH);            //设置LED 为开
        delay(400);                           //延时400毫秒
        digitalWrite(ledPin,LOW);             //设置LED 为关
        delay(100);                           //延时100毫秒
        }

        //100毫秒延时产生字母之间的间隙
        delay(100);

       // 再用三个快闪烁来表示字母“S”
       for(int x=0;x<3;x++){
        digitalWrite(ledPin,HIGH);            //设置LED 为开
        delay(150);                           //延时150毫秒
        digitalWrite(ledPin,LOW);             //设置LED 为关
        delay(100);                           //延时100毫秒
        }

        // 在重复S.0.S信号前等待5秒
        delay(5000);
}

