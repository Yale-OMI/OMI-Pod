void setup() {

  //required by accelrometer
  Serial.begin(115200);

  accel_setup();
  pc_setup();
  distance_setup();
  color_setup();
  
}

void loop() {

  accel_loop();
  pc_loop();
  distance_loop();
  color_loop();
  sound_loop();

}
