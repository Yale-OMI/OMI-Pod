
void light_loop()
{

    Serial.print("/light ");   //Write the value of the photoresistor to the serial monitor.

    Serial.println(analogRead(1));

 // Depending on value of resistor you have  to divide the value. for example, 
 // with a 10k resistor divide the value by 2, for 100k resistor divide by 4.
 // delay(10); //short delay for faster response to light.
}
