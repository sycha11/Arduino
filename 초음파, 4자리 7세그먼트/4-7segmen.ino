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

#define TP 13
#define EP A0 
#define NOTE_C4 261 // 도

int pos_pins[] = {9, 10, 11, 12}; // 몇번째 세그먼트
int num_of_pos = 4;
int pins[] = {2,3,4,5,6,7,8}; // 세그먼트 a, b, c, d, e, f, g, dp
int num_of_pins = 7;
int delaytime = 5;
int AN5 = 0;

// 세그먼트에 표시 할 숫자
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
{ 1,1,1,1,0,1,1} // 9
};

//멜로디 배열 선언
int melody[] = {NOTE_C4};
// 각 음 시간 설정
int noteDurations[] = { 4};


// the setup function runs once when you press reset or power the board
void setup() {
   pinMode(TP,OUTPUT); 
 pinMode(EP,INPUT); 
 for(int i=0; i<num_of_pos; i++) {
    pinMode(pos_pins[i], OUTPUT);
    }
    for(int i=0; i<num_of_pins; i++) {
      pinMode(pins[i], OUTPUT);
      }
     
  Serial.begin(115200); 
}

// the loop function runs over and over again forever
void loop() {
int num_dd[4];
long microseconds = TP_init();
 long distance_cm = Distance(microseconds); 
 int v = int(distance_cm);
  Serial.println(v); 
                     
  for(int u=0; u < 4; u++){
    num_dd[u] = v % 10; // 10으로 나눠서 나머지를 num_dd[u]에 입력
    v = v /10; //맨 뒤에 자리수를 없앤다
  }
  int num[] = {num_dd[3], num_dd[2], num_dd[1], num_dd[0]};
  digits_4_seven_segment(num);

/*
if(distance_cm >=50){
  sound();
  delay(2000);
}
else if(distance_cm >=40){
  sound();
  delay(1000);
}
else if(distance_cm >=30){
  sound();
  delay(500);
}
else if(distance_cm >=20){
  sound();
  delay(250);
}
else if(distance_cm >=10){
  sound();
  delay(125);
}
else if(distance_cm >0){
  sound();
}
*/
 Serial.print("Distacne_CM = "); 
 Serial.println(distance_cm); 
                    
}

// 원하는 위치에 표시되도록 set
void set_position(int pos){
for(int i = 0; i < 4; i++) {
if(i + 1 == pos){
digitalWrite(pos_pins[i], LOW);
} else {
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
void digits_4_seven_segment(int num[]){
  for(int i=0;i<num_of_pos;++i){
    set_seven_segment(i+1,num[i]);
    delay(delaytime);
    }
}

void sound(){
  for (int thisNote = 0; thisNote < 1; thisNote++) {
  int noteDuration = 1000 / noteDurations[thisNote]; //음길이 계산
  tone(3, melody[thisNote], noteDuration); //PWM 파형 출력

 int pauseBetweenNotes = noteDuration * 1.3; //각 음간 지연시간 설정
 delay(pauseBetweenNotes); //지연
// Serial.println(pauseBetweenNotes);
 // stop the tone playing:
 noTone(3); //PWM 파형 출력 중단
 }
}

long Distance(long time)
{
 long distance; 
 distance = time /29 / 2; 
 return distance; 
}

long TP_init()
{
 digitalWrite(TP, HIGH); //TP 핀에 HIGH 출력
 delayMicroseconds(10); //10 us 대기
 digitalWrite(TP, LOW);
  long microseconds = pulseIn(EP,HIGH); //EP핀에 HIGH 입력되는 시갂을 변수에 저장
 return microseconds; //변수 반환
}
