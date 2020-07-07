#include <ESP8266WiFi.h>
const char* ssid = "mapoo2995";
const char* password = "alsdn1995";

//const char *ssid = "U+NetF2D9";
//const char *password = "1C59001101";
int IR_sensor = A0;
int val ;
long IR_value;
long IR_range;
//#include <ESP8266WiFi.h>
//const char *ssid = "U+NetF2D9";
//const char *password = "1C59001101";
WiFiServer server(80);
int led = 14 ;
int j =1;
int t =0;
const char* host = "192.168.43.1";
//char* host = "192.168.43.49";
 WiFiClient client;
void setup() {
  Serial.begin(115200);
  delay(10);
  pinMode(led, OUTPUT);
  // We start by connecting to a WiFi network
  pinMode (IR_sensor, INPUT);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);


  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    val = analogRead(IR_sensor);
   //IR_value = map(val,0,1023,0,645);
   IR_value = val;
   IR_range = gp2y0a21yk(IR_value);

  //Serial.println (IR_value);
  //Serial.print (IR_range);
  //Serial.println (" cm");
  //Serial.println ();
  //delay (1000);
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  digitalWrite(led,HIGH);
  delay(1000);
  digitalWrite(led,LOW);
  Serial.print("connecting to ");
  Serial.println(host);
  Serial.println();
  Serial.println("closing connection");
  client.write("모듈 접속");
  client.println("모듈 접속");
/*
    if(t==0){
       char* host = "192.168.43.49";
       t=1;
       client.connect(host, 7000);
      }
      else if(t==1){
       char* host = "192.168.43.1";
         t=0;
         client.connect(host, 7000);
        }
        */
}
//WiFiClient client;
int value = 0;
long gp2y0a21yk (long IR_value)
{
  if (IR_value < 10) IR_value = 10;
  
  return ((67870.0 / (IR_value - 3.0)) - 40.0)/10;
} 
void loop() {
  delay(500);
  ++value;
 val = analogRead(IR_sensor);
 IR_value = val;
 IR_range = gp2y0a21yk(IR_value);

  
  // Use WiFiClient class to create TCP connections
 // WiFiClient client;
  const int httpPort = 7000;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  } 
  // This will send the request to the server
 //client.print("신호 줄래?");
  int timeout = millis() + 5000;
  while (client.available() == 0) {
    if (timeout - millis() < 0) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
  
  // Read all the lines of the reply from server and print them to Serial
 // while(client.available()){
    //String line = client.readStringUntil('\r');
 //   Serial.print(line);
  // Serial.print("신호 받았다.");
  
 // Serial.println();
 // Serial.println("closing connection");
 client.print(IR_range);
 while(!client.available()){
  client.println("");
 client.print(IR_range);
 client.print(" cm");
 delay(300);
  }
  
//while(1){
 
//while(client.available()){
  char ch=client.read();
 // Serial.write(ch);

   if(ch==0x30)
   {
   Serial.write("0");
   client.write("YES, 0 Sign\n");
   
   }
  else if(ch==0x31)
   {
   
   Serial.write("1");
   client.write("YES, 1 Sign\n");
  // analogWrite(led, 127);
   }
     else if(ch==0x32)
   {
   Serial.write("2");
   client.write("YES, 2 Sign\n");
  // analogWrite(led, 100);
   }
     else if(ch==0x33)
   {
   Serial.write("3");
   client.write("YES, 3 Sign\n");
   //analogWrite(led, 300);
   }
    else if(ch==0x34)
   {
   Serial.write("4");
   client.write("YES, 4 Sign\n");
  // analogWrite(led, 654);
   }
     else if(ch==0x35)
   {
   Serial.write("5");
   client.write("YES, 5 Sign\n");
   }
     else if(ch==0x36)
   {
   Serial.write("6");
   client.write("YES, 6 Sign\n");
   }
     else if(ch==0x37)
   {
   Serial.write("7");
   client.write("YES, 7 Sign\n");
   }  else if(ch==0x38)
   {
     //센서 무시하기
     j=0;
   }
   else if(ch==0x39)
   {
    //센서 키기
    j=1;
   }
   
   else{
    while(Serial.available()){
      Serial.println("무엇인가 rx를 통해 받았다.");
      }
   }

  //}
  
  
//}
 client.print(IR_range);
 client.print(" cm\n");
 if(IR_range<20&&j==1){
  Serial.write("5");
  client.print("부딪칠 수 있어요, 속도를 줄입니다.");
  }
}