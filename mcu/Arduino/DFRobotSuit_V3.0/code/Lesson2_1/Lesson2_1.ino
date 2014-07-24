int ledPin = 10;
void setup() {
        pinMode(ledPin, OUTPUT);
}
void loop() {
             // 三个快闪烁来表示字母“S”
        digitalWrite(ledPin,HIGH);
        delay(150);
        digitalWrite(ledPin,LOW);
        delay(100);
        
        digitalWrite(ledPin,HIGH);
        delay(150);
        digitalWrite(ledPin,LOW);
        delay(100);

        digitalWrite(ledPin,HIGH);
        delay(150);
        digitalWrite(ledPin,LOW);
        delay(100);

        //三个短闪烁来表示字母“O”
        digitalWrite(ledPin,HIGH);
        delay(400);
        digitalWrite(ledPin,LOW);
        delay(100);

        digitalWrite(ledPin,HIGH);
        delay(400);
        digitalWrite(ledPin,LOW);
        delay(100);

        digitalWrite(ledPin,HIGH);
        delay(400);
        digitalWrite(ledPin,LOW);
        delay(100);

        //再用三个快闪烁来表示字母“S”
        digitalWrite(ledPin,HIGH);
        delay(150);
        digitalWrite(ledPin,LOW);
        delay(100);
        
        digitalWrite(ledPin,HIGH);
        delay(150);
        digitalWrite(ledPin,LOW);
        delay(100);

        digitalWrite(ledPin,HIGH);
        delay(150);
        digitalWrite(ledPin,LOW);
        delay(100);
}

