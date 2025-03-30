#include <Keyboard.h>

// Structure to hold pin-key mappings
struct KeyMapping {
  int pin;
  uint8_t modifier; // Modifier key (AltGr for German layout)
  char key;
  int prevState;
  unsigned long lastDebounceTime;
};

// German keyboard uses AltGr (Right Alt) for certain keys
#define ALTGR 0x40  // AltGr modifier

KeyMapping keyMappings[] = {
  {2, ALTGR, '8', HIGH, 0}, // AltGr + 8 = [
  {3, ALTGR, '9', HIGH, 0}  // AltGr + 9 = ]
};

// Number of keys
constexpr int numKeys = sizeof(keyMappings) / sizeof(keyMappings[0]);
constexpr int debounceDelay = 5; // Debounce delay in milliseconds

void setup() {
  for (int i = 0; i < numKeys; i++) {
    pinMode(keyMappings[i].pin, INPUT_PULLUP);
    keyMappings[i].prevState = digitalRead(keyMappings[i].pin);
  }
  Keyboard.begin();
}

void loop() {
  for (int i = 0; i < numKeys; i++) {
    handleMorseKey(keyMappings[i]);
  }
}

void handleMorseKey(KeyMapping &keyMapping) {
  int keyState = digitalRead(keyMapping.pin);

  if (keyState != keyMapping.prevState) {
    unsigned long currentTime = millis();
    if ((currentTime - keyMapping.lastDebounceTime) > debounceDelay) {
      keyMapping.lastDebounceTime = currentTime;

      if (keyState == LOW) {
        Keyboard.press(KEY_RIGHT_ALT); // AltGr
        Keyboard.press(keyMapping.key);
      } else {
        Keyboard.release(keyMapping.key);
        Keyboard.release(KEY_RIGHT_ALT); // Release AltGr
      }

      keyMapping.prevState = keyState;
    }
  }
}
