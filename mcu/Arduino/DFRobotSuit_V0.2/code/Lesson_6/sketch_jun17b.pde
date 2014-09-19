void setup()
{
    pinMode(6,OUTPUT);
}
void loop()
{
    while(1)
    {
        char i,j;
     while(1)
     {
       for(i=0;i<80;i++)    //输出一个频率的声音
        {
        digitalWrite(6,HIGH);
        delay(1);
        digitalWrite(6,LOW);
        delay(1);
        }
        for(i=0;i<100;i++)   //输出另一个频率的声音
        {
        digitalWrite(6,HIGH);
        delay(2);
        digitalWrite(6,LOW);
        delay(2);
        }
     }
    }
}
