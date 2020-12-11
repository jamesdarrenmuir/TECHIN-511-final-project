// James Muir
// 12-8-2020
// TECHIN 511

// Globe Lamp code
// goal: toggle lamp on or off when any of the buttons is pressed

// TODOS:
// add support for NeoPixel ring (done)
// add support for external buttons

// using both libraries because Adafruit CircuitPlayground lacks a fill command
// but I want to use the CircuitPlayground button functions
#include <Adafruit_NeoPixel.h>
#include <Adafruit_CircuitPlayground.h>

// which pins are the buttons on?
#define BUTTON_PIN_1 2
#define BUTTON_PIN_2 10
#define BUTTON_PIN_3 12 

// Which pin on the Arduino is connected to the NeoPixels?
#define LED_PIN_BOARD 17 // the NeoPixels on the CircuitPlayground board itself
#define LED_PIN_RING 0  // the NeoPixel ring

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT_BOARD 10
#define LED_COUNT_RING 24

Adafruit_NeoPixel board(LED_COUNT_BOARD, LED_PIN_BOARD);
Adafruit_NeoPixel ring(LED_COUNT_RING, LED_PIN_RING);

void pxl_init(Adafruit_NeoPixel& strip) {
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  // TODO: set this to a good value for the lamp
  // currently set low so it doesn't blind me when testing
  strip.setBrightness(255); // Set BRIGHTNESS (max = 255, default = 255)
}

void pxl_on(Adafruit_NeoPixel& strip) {
  // set the whole strip to white
  strip.fill(strip.Color(255, 255, 255));
}

void pxl_off(Adafruit_NeoPixel& strip) {
  // set the whole strip to off
  strip.clear();
}

void setup() {
  // put your setup code here, to run once:
  // I think uncommenting this initializes the CircuitPlayground board NeoPixels twice, compiler does not like it
//  CircuitPlayground.begin();
  Serial.begin(9600);
  Serial.println("Globe Lamp");
  
  pxl_init(board);
  pxl_init(ring);

  // set up the buttons
  pinMode(BUTTON_PIN_1, INPUT_PULLUP);
  pinMode(BUTTON_PIN_2, INPUT_PULLUP);
  pinMode(BUTTON_PIN_3, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  static bool on = false;
  if (CircuitPlayground.leftButton() || CircuitPlayground.rightButton() || !digitalRead(BUTTON_PIN_1) || !digitalRead(BUTTON_PIN_2) || !digitalRead(BUTTON_PIN_3)) {
    on = !on; // toggle
    if (on) {
      Serial.println("Lamp On");
      pxl_on(board);
      pxl_on(ring);
    } else {
      Serial.println("Lamp Off");
      pxl_off(board);
      pxl_off(ring);
    }
    // push colors to NeoPixels
    board.show();
    ring.show();
    delay(500); // so the buttons work decently
  }
}
