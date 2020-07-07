unsigned char c;  // variable to store the received character
int leftPin1 = 13;
int leftPin2 = 12;

int rightPin1= 10;
int rightPin2= 11;
int i=255;
int q=1;
void setup() {
 // Serial.begin(9600);   // setup serial
  //Serial.begin(19200);   // setup serial
  //Serial.begin(38400);   // setup serial
   //Serial.begin(57600);   // setup serial
  Serial.begin(115200);   // setup serial
  pinMode(leftPin1, OUTPUT);
  pinMode(leftPin2, OUTPUT);
  pinMode(rightPin1, OUTPUT);
  pinMode(rightPin2, OUTPUT);
}
    
void loop() {
//Serial.write(0x31);
//delay(1000);
//Serial.write(0x30);
//delay(1000);
//while(Serial.available())
//Serial.write(Serial.read());
delay(10);
  if(Serial.available() > 0){
      c = Serial.read();   // read the character
  
      if(c == 0x31){  // 전진
        analogWrite(leftPin1,i);
        analogWrite(leftPin2,0);
        analogWrite(rightPin1,i);
        analogWrite(rightPin2,0);
        Serial.println("전진");
        q=1;
      }else if(c == 0x32){ //후진
        analogWrite(leftPin1,0);
        analogWrite(leftPin2,i);
        analogWrite(rightPin1,0);
        analogWrite(rightPin2,i);
        Serial.println("후진");
        q=0;
      }
        else if(c == 0x33){ //좌회전
       if(q==1){
        analogWrite(leftPin1,20);
        analogWrite(leftPin2,i);
        analogWrite(rightPin1,i);
        analogWrite(rightPin2,20);}
        else if(q==0){
        analogWrite(leftPin1,i);
        analogWrite(leftPin2,20);
        analogWrite(rightPin1,20);
        analogWrite(rightPin2,i);}
        Serial.println("좌회전");
      }
      else if(c == 0x34){ //우회전
        if(q==1){
        analogWrite(leftPin1,i);
        analogWrite(leftPin2,20);
        analogWrite(rightPin1,20);
        analogWrite(rightPin2,i);}
        else if(q==0){
        analogWrite(leftPin1,20);
        analogWrite(leftPin2,i);
        analogWrite(rightPin1,i);
        analogWrite(rightPin2,20);}
        Serial.println("우회전");
      }
      else if(c == 0x30){ //정지
        analogWrite(leftPin1,0);
        analogWrite(leftPin2,0);
        analogWrite(rightPin1,0);
        analogWrite(rightPin2,0);
        Serial.println("정지");
      }
      else if(c == 0x35){ //정지
        analogWrite(leftPin1,0);
        analogWrite(leftPin2,0);
        analogWrite(rightPin1,0);
        analogWrite(rightPin2,0);
        Serial.println("정지");
      }
        else if(c == 0x36){ //속도 1단계
        i=190;
        Serial.println("속도 1단계");
      }
      else if(c == 0x37){ //속도 2단계
        i=255;
        Serial.println("속도 2단계");
      }
    }
}