 //项目15 – 数码管数字显示 
int number[10][8] = 
{
  {0,0,0,1,0,0,0,1},   //显示0
  {0,1,1,1,1,1,0,1},   //显示1
  {0,0,1,0,0,0,1,1},   //显示2
  {0,0,1,0,1,0,0,1},   //显示3
  {0,1,0,0,1,1,0,1},   //显示4
  {1,0,0,0,1,0,0,1},   //显示5
  {1,0,0,0,0,0,0,1},   //显示6
  {0,0,1,1,1,1,0,1},   //显示7
  {0,0,0,0,0,0,0,1},   //显示8
  {0,0,0,0,1,1,0,1}    //显示9
};

void numberShow(int i){         //该该函数用来显示数字
    for(int pin = 2; pin <= 9 ; pin++){
       digitalWrite(pin, number[i][pin - 2]);
    }
}

void setup(){
  for(int pin = 2 ; pin <= 9 ; pin++){      // 设置数字引脚2~9为输出模式
      pinMode(pin, OUTPUT);
      digitalWrite(pin, HIGH);
  }
}

void loop() {      
    for(int j = 0; j <= 9 ; j++){  
          numberShow(j);       //调用numberShow()函数，显示0~9
          delay(500);
    }
}


