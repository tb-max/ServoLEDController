#include <Arduino.h>
#include <EnableInterrupt.h>

#define BUTTON_PIN 5
#define DEBOUNCE_DELAY 100 // in ms

uint32_t last_interrupt_time = 0;
uint8_t led_status = 0;


void isr_handler() {
  uint32_t interrupt_time = millis();

  if (interrupt_time - last_interrupt_time > DEBOUNCE_DELAY) {
    led_status = !led_status;
    digitalWrite(LED_BUILTIN, led_status);
  }

  last_interrupt_time = interrupt_time;
}

void setup() {
  pinMode(BUTTON_PIN, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  enableInterrupt(BUTTON_PIN, isr_handler, RISING);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}

