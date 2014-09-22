//项目六 报警器
float sinVal;
int toneVal;

void setup(){
     pinMode(8, OUTPUT);
}

void loop(){
     for(int x=0; x<180; x++){
            sinVal = (sin(x*(3.1412/180)));
            toneVal = 2000+(int(sinVal*1000));
            tone(8, toneVal);
            delay(2); 
     }   
}
