#include <Arduino.h>
#include <EnableInterrupt.h>


#define RC_CH1  2

uint32_t last_interrupt_time = 0;
uint16_t value = 1500;
uint8_t led_value = 0;

void isr_handler() {
  if (digitalRead(RC_CH1) == HIGH) {
    last_interrupt_time = micros();
  } else {
    uint16_t rc_compare = (uint16_t)(micros() - last_interrupt_time);
    value = rc_compare;
    
    led_value = map(value, 1000, 2000, 0, 255); 
    analogWrite(LED_BUILTIN, led_value);
  }
}

void setup() {
  Serial.begin(57600);
  pinMode(RC_CH1, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  enableInterrupt(RC_CH1, isr_handler, CHANGE);
}

// the loop function runs over and over again forever
void loop() {
  Serial.print("rc value: ");
  Serial.println(value);
  Serial.print("led value: ");
  Serial.println(led_value);
  delay(1000);                       // wait for a second

}

