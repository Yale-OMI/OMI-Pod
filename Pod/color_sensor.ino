/*     Arduino Color Sensing Tutorial
 *      
 *  by Dejan Nedelkovski, www.HowToMechatronics.com
 *  
 */

 // defines changed to match our testing circuit
 
#define S0 2
#define S1 3
#define S2 4
#define S3 5
#define SLED 8
#define sensorOut 6

int frequency = 0;

void color_setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(SLED, INPUT);
  pinMode(sensorOut, INPUT);
  
  // Setting frequency-scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  digitalWrite(SLED, HIGH);
}

void color_loop() {
  Serial.print("/color ");
  // Setting red filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  //Remaping the value of the frequency to the RGB Model of 0 to 255
  frequency = map(frequency, 240,600,255,0);
  // Printing the value on the serial monitor
  Serial.print(frequency);//printing RED color frequency
  Serial.print(" ");
  delay(100);

  // Setting Green filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  //Remaping the value of the frequency to the RGB Model of 0 to 255
  frequency = map(frequency, 300,805,255,0);
  // Printing the value on the serial monitor
  Serial.print(frequency);//printing RED color frequency
  Serial.print(" ");
  delay(100);

  // Setting Blue filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  //Remaping the value of the frequency to the RGB Model of 0 to 255
  frequency = map(frequency, 260,720,255,0);
  // Printing the value on the serial monitor
  Serial.print(frequency);//printing RED color frequency
  Serial.println("");
  delay(100);
}
