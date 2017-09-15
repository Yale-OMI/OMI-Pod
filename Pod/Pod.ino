void setup() {

  //required by accelrometer
  Serial.begin(115200);

  accel_setup();
  pc_setup();
  distance_setup();
  
  
}

void loop() {

  accel_loop();
  pc_loop();
  distance_loop();

}
