/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Blink
*/
int cnt =0;
byte number[10][7] = {//{a,b,c,d,e,f,g} 
 {1,1,1,1,1,1,0}, //0 
{0,1,1,0,0,0,0}, //1 
{1,1,0,1,1,0,1}, //2 
{1,1,1,1,0,0,1}, //3 
{0,1,1,0,0,1,1}, //4 
{1,0,1,1,0,1,1}, //5 
{1,0,1,1,1,1,1}, //6 
{1,1,1,0,0,0,0}, //7 
{1,1,1,1,1,1,1}, //8 
{1,1,1,1,0,1,1}, //9 
}; 


// the setup function runs once when you press reset or power the board
void setup() {
  for(int i=2; i<13; i++){
    pinMode(i,OUTPUT);
  }
}

// the loop function runs over and over again forever
void loop() {

  for(int i=0; i<10;i++){
   for(int k=0;k<7;k++){
      digitalWrite(k+2 , number[i][k]);
    }
    display();
    cnt++;   
    delay(1000);
  }

}

void display(){
   if(cnt%4 == 0){
       digitalWrite(9,LOW);
      digitalWrite(10,HIGH);
      digitalWrite(11,HIGH);
      digitalWrite(12,HIGH);
    }else if( cnt%4 ==1){
      digitalWrite(9,HIGH);
      digitalWrite(10,LOW);
      digitalWrite(11,HIGH);
      digitalWrite(12,HIGH);
    }else if( cnt%4 ==2){
      digitalWrite(9,HIGH);
      digitalWrite(10,HIGH);
      digitalWrite(11,LOW);
      digitalWrite(12,HIGH);
    }else if( cnt%4 ==3){
      digitalWrite(9,HIGH);
      digitalWrite(10,HIGH);
      digitalWrite(11,HIGH);
      digitalWrite(12,LOW);
    }
}
