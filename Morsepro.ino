#include <Keyboard.h>

// Structure to hold pin-key mappings
struct KeyMapping {
  int pin;
  char key;
  int prevState;
};

// Define an array of key mappings
KeyMapping keyMappings[] = {
  {2, '[', LOW}, // Pin 2, key '[', initial previous state LOW
  {3, ']', LOW}  // Pin 3, key ']', initial previous state LOW
};

// Number of keys
const int numKeys = sizeof(keyMappings) / sizeof(keyMappings[0]);

const int debounceDelay = 25; // Debounce delay in milliseconds

void setup() {
  for (int i = 0; i < numKeys; i++) {
    pinMode(keyMappings[i].pin, INPUT_PULLUP); // Set each key pin as input with internal pull-up resistor
  }
  Keyboard.begin(); // Initialize keyboard
}

void loop() {
  for (int i = 0; i < numKeys; i++) {
    handleMorseKey(keyMappings[i]);
  }
}

void handleMorseKey(KeyMapping &keyMapping) {
  int keyState = digitalRead(keyMapping.pin);
  if (keyState != keyMapping.prevState) {
    if (keyState == LOW) {
      Keyboard.press(keyMapping.key); // Press the key
    } else {
      Keyboard.release(keyMapping.key); // Release the key
    }
    keyMapping.prevState = keyState;
    delay(debounceDelay); // Debounce delay
  }
}
