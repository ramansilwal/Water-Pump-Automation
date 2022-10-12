#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
bool go_to_home=false;
bool run_pump=false;
bool go_to_tank_full=false;
bool go_to_stop_screen=false;
bool go_to_overload_screen=false;
const int buttonPinAuto = 8;
const int sensorPinAuto = 7;
const int buttonPinTimer = 10;
int buttonStateTimer = 0;
int sensorStateAuto = 0;
int buttonStateAuto = 0;
const int relay =  6;   
long int start_time=0;

int up_time=0;
String up_sec="";
String up_mins="";
String run_time="";


void home_screen(){
  lcd.clear();
  lcd.setCursor(0, 0);
lcd.print("Turn off or");
lcd.setCursor(1, 1);
lcd.print("Press Start");

}

void run_pump_timed(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Pump is running");
while (true){
  buttonStateAuto = digitalRead(buttonPinAuto);
    delay(100);
    buttonStateTimer = digitalRead(buttonPinTimer);
    
  if (buttonStateAuto == 1) {
    digitalWrite(relay, HIGH);
    lcd.clear();
    lcd.setCursor(0, 0);
  lcd.print("Pump Force Quit!!");
    go_to_home=true;
    delay(5000);
    break;}
    
  if (buttonStateTimer == 1) {
    start_time=start_time+60;
  }
  up_time=start_time-millis()/1000;
  if (up_time<=0){
    digitalWrite(relay, HIGH);
    go_to_stop_screen=true;
    break;}
    
  if (up_time/60>=10){up_mins=String(up_time/60);}
  else{up_mins="0"+String(up_time/60);}
  
  if (up_time%60>=10){up_sec=String(up_time%60);}
  else{up_sec="0"+String(up_time%60);}

  run_time="run time "+String(up_mins)+":"+String(up_sec);
 lcd.setCursor(1, 1);
lcd.print(run_time);
delay(800);
}
}
void run_pump_func(){
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Pump is running");
  delay(2500);
while (true){
 buttonStateAuto = digitalRead(buttonPinAuto);
   if (buttonStateAuto == 1) {
    digitalWrite(relay, HIGH);
    lcd.clear();
    lcd.setCursor(0, 0);
  lcd.print("Pump Force Quit!!");
    go_to_home=true;
    delay(5000);
    break;}
    
  lcd.setCursor(1, 1);
  sensorStateAuto=0;
  up_time=(millis()-start_time)/1000;
  for(int i=0;i<20;i++){
    sensorStateAuto += digitalRead(sensorPinAuto);
    delay(10);
    }

   if (sensorStateAuto<5){
    digitalWrite(relay, HIGH);
    go_to_tank_full=true;
    break;}
    
  if (up_time/60>=25){
    digitalWrite(relay, HIGH);
    go_to_overload_screen=true;
    break;}
  
  if (up_time/60>=10){up_mins=String(up_time/60);}
  else{up_mins="0"+String(up_time/60);}
  
  if (up_time%60>=10){up_sec=String(up_time%60);}
  else{up_sec="0"+String(up_time%60);}

  run_time="Up time "+String(up_mins)+":"+String(up_sec);
lcd.print(run_time);
delay(800);
}

}


void overload_screen(){
  lcd.clear();
  lcd.setCursor(0, 0);
lcd.print("Over load !!!");
lcd.setCursor(0, 1);
lcd.print("Restart or Off");}
void tank_full_screen(){
  lcd.clear();
  lcd.setCursor(0, 0);
lcd.print("Tank Full!!");
lcd.setCursor(0, 1);
lcd.print("Restart or Off");}

void stop_screen(){
  lcd.clear();
  lcd.setCursor(0, 0);
lcd.print("Time Finished !!!");
lcd.setCursor(0, 1);
lcd.print("Restart or Off");}


void setup() {
  lcd.begin(16, 2);
  go_to_home=true;
  digitalWrite(relay, HIGH);
  pinMode(relay, OUTPUT);
  
}

void loop() {

    if (go_to_overload_screen==true) {
    overload_screen();
    go_to_overload_screen=false;}
    if(go_to_tank_full==true){
      tank_full_screen();
      go_to_tank_full=false;
      }
  if (go_to_home==true){
  home_screen();
  go_to_home=false;
}

if (go_to_stop_screen==true){
  stop_screen();
    go_to_stop_screen=false;}
    
    buttonStateAuto = digitalRead(buttonPinAuto);
    delay(100);
    buttonStateTimer = digitalRead(buttonPinTimer);
    
  if (buttonStateAuto == 1) {
    digitalWrite(relay, LOW);
    start_time=millis();
    run_pump_func();}
    
  if (buttonStateTimer == 1) {
    digitalWrite(relay, LOW);
    start_time=millis()/1000+10;
    run_pump_timed();
}

}
