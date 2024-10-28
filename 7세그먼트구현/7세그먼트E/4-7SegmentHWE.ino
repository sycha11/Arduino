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

int pos_pins[] = {9, 10, 11, 12}; // 몇번째 세그먼트
int num_of_pos = 4;
int pins[] = {2,3,4,5,6,7,8}; // 세그먼트 a, b, c, d, e, f, g, dp
int num_of_pins = 7;
int delaytime = 5;
int cnt =0;
byte number [10][7] = {
//{ a,b, c, d, e , f , g}
{ 1,1,1,1,1,1,0}, // 0
{ 0,1,1,0,0,0,0}, // 1
{ 1,1,0,1,1,0,1}, // 2
{ 1,1,1,1,0,0,1}, // 3
{ 0,1,1,0,0,1,1}, // 4
{ 1,0,1,1,0,1,1}, // 5
{ 1,0,1,1,1,1,1}, // 6
{ 1,1,1,0,0,0,0}, // 7
{ 1,1,1,1,1,1,1}, // 8
{ 1,1,1,1,0,1,1}, // 9
};

void setup() {
  for(int i=0; i<num_of_pos; i++) {
 pinMode(pos_pins[i], OUTPUT);
 }
 for(int i=0; i<num_of_pins; i++) {
 pinMode(pins[i], OUTPUT);
 }
 pinMode(13,INPUT);
 Serial.begin(115200);
}

void loop() {
  if(!digitalRead(13)){
    cnt= cnt+1;
    if(cnt ==10000){
      cnt =0;
    }
     delay(200);
  }
  digits_4_seven_segment(cnt);
}


// 원하는 위치에 표시되도록 set
void set_position(int pos){
  for(int i = 0; i < 4; i++) {
    if(i + 1 == pos){
      digitalWrite(pos_pins[i], LOW);
      }
    else {
      digitalWrite(pos_pins[i], HIGH);
        }
      }
}

// 함수 정의 : 원하는 숫자 표시
void set_number(int seg_num){
  for(int i=0;i<num_of_pins;++i){
    number[seg_num][i] ? digitalWrite(pins[i], HIGH) :digitalWrite(pins[i], LOW);
    }
}
// 함수 정의 : 원하는 위치, 원하는 숫자를 표시
void set_seven_segment(int pos, int seg_num){
 set_position(pos);
 set_number(seg_num);
}
// 함수 정의 : 입력된 4자리 숫자를 세그먼트에 표시
void digits_4_seven_segment(int num){
 for(int i=num_of_pos;i>0;--i){ // d4부터 d1
 set_seven_segment(i,num%10);
 delay(delaytime);
 num = num/10;
 }
}
