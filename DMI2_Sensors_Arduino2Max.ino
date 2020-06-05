#include <math.h>

#define trigPin 4
#define echoPin 5

double Thermistor(int RawADC) {
 double Temp;
 Temp = log(10000.0*((1024.0/RawADC-1))); 
 Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp ))* Temp );
 Temp = Temp - 273.15;          
 return Temp;
}
const int PIEZO_PIN = A0; // Piezo output


void setup() {
  Serial.begin (115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(2, OUTPUT);
  pinMode(3, INPUT);
}

void loop() {
  int val;                
  double temp;            
  val=analogRead(0);      
  temp=Thermistor(val);

  float duration, distance;
  float duration2, distance2;
  int piezoADC = analogRead(PIEZO_PIN);
  float spdSnd;
 
  digitalWrite(2, LOW); 
  delayMicroseconds(2);
 
  digitalWrite(2, HIGH);
  delayMicroseconds(10);
  
  digitalWrite(2, LOW);
  duration = pulseIn(3, HIGH);

  
 
  digitalWrite(4, LOW);
  delayMicroseconds(2);

  digitalWrite(4, HIGH);
  delayMicroseconds(10);
  

  digitalWrite(4, LOW);
  duration2 = pulseIn(5, HIGH);
 
  spdSnd = 331.4 + (0.606 * temp) + 0.62;
  distance = (duration / 2) * (spdSnd / 10000);
  distance2 = (duration2 / 2) * (spdSnd / 10000); 
  float piezoV = piezoADC / 1023.0 * 5;

  
  
  Serial.print(distance); //Prints Horizontal distance
  Serial.print(" ");
  Serial.print(distance2); //Prints Vertical distance
  Serial.print(" ");
  Serial.print(piezoV); //Prints piezo voltage
  Serial.println();
  
  delay(20);
}

