//Furkan ZEKİRİ

#include <Servo.h>


int ch1=2;
int ch2=3;
int ch3=4;
int ch4=5;
int ch5=6;
int ch6=7;

const int esc_pin = 45;
const int kanat_sag_pin = 47;
const int kanat_sol_pin = 49;
const int kuyruk_sag_pin = 51;
const int kuyruk_sol_pin = 53;

Servo motor;  
Servo kanat_sag;  
Servo kanat_sol;
Servo kuyruk_sag;
Servo kuyruk_sol; 

int ch1_map, ch2_map, ch3_map, ch4_map, ch5_map;
   
void setup() {
   Serial.begin(9600);
   pinMode(ch1, INPUT);
   pinMode(ch2, INPUT);
   pinMode(ch3, INPUT);
   pinMode(ch4, INPUT);
   pinMode(ch5, INPUT);
   pinMode(ch6, INPUT);

   motor.attach(esc_pin);  
   kanat_sag.attach(kanat_sag_pin);
   kanat_sol.attach(kanat_sol_pin);  
   kuyruk_sag.attach(kuyruk_sag_pin);
   kuyruk_sol.attach(kuyruk_sol_pin); 

}

void loop() {
  int ch1_val = pulseIn(ch1,HIGH);
  ch1_map = map(ch1_val, 1000, 2000, 0, 180);
  int ch2_val = pulseIn(ch2,HIGH); 
  ch2_map = map(ch2_val, 1000, 2000, 0, 180); 
  int ch3_val = pulseIn(ch3,HIGH);
  ch3_map = map(ch3_val, 1000, 2000, 0, 180);
  int ch4_val = pulseIn(ch4,HIGH);
  ch4_map = map(ch4_val, 1000, 2000, 0, 180);
  int ch5_val = pulseIn(ch5,HIGH);
  ch5_map = map(ch5_val, 1000, 2000, 0, 180);
  bool ch6_val = digitalRead(ch6);

  Serial.print("\nch1: ");
  Serial.print(ch1_map);
  Serial.print("\nch2: ");
  Serial.print(ch2_map);
  Serial.print("\nch3: ");
  Serial.print(ch3_map);
  Serial.print("\nch4: ");
  Serial.print(ch4_map);
  Serial.print("\nch5: ");
  Serial.print(ch5_map);
  Serial.print("\nch6: ");
  Serial.print(ch6_val);
  Serial.print("\n------------------------------------------------------------");

  
  algorithm_roll(ch1_map, ch2_map);
  algorithm_pitch(ch1_map, ch2_map);
  algorithm_yaw(ch4_map);
  motor.write(ch3_map);

}

void algorithm_roll(int ch1_m, int ch2_m) {

  if (ch1_m < 70){
    kanat_sag.write(180 - ch2_m);
    kanat_sol.write(90 - (ch1_m - 90));
   
  }
  else if (ch1_m >110){
    kanat_sag.write(90 - (ch1_m - 90));
    kanat_sol.write(180 - ch2_m);
  }
  else {
    kanat_sag.write(90);
    kanat_sol.write(90);
  }
}

void algorithm_pitch(int ch1_m, int ch2_m){
  
  // Aşağı doğru eğilmek için
  if (ch2_m > 110) {
    kanat_sag.write(ch2_m);
    kanat_sol.write(180 - ch2_m);
  }
  
  // Yukarı doğru eğilmek için
  else if (ch2_m < 70) {
    kanat_sag.write(ch2_m);
    kanat_sol.write(180 - ch2_m);
  }
}

void algorithm_yaw(int ch4_m){

  
  if (ch4_m < 85 || ch4_m >95){
    kuyruk_sag.write(ch4_m);
    kuyruk_sol.write(ch4_m);
  }
  else {
    kuyruk_sag.write(90);
    kuyruk_sol.write(90);
  }
  delay(20);
}
