/* ESP32-S3 + ST7735S (Adafruit GFX/ST7735) + ADC read on AN1 (GPIO1)
   Libraries (Library Manager):
     Adafruit GFX Library
     Adafruit ST7735 and ST7789 Library
*/

#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

// -------- Pin mapping (adjust if your board differs) --------
#define TFT_CS    10    // LCD_VSPICS
#define TFT_DC     7    // LCD_VSPIDC (D/C)
#define TFT_RST    4    // LCD_RESET
#define TFT_MOSI  11    // LCD_VSPID
#define TFT_SCLK  12    // LCD_VSPICLK
#define TFT_BL    13    // LCD_BRIGHTNESS (backlight), optional

#define ADC_PIN    1    // AN1 on the diagram (GPIO1)

// -------- Display object (hardware SPI with chosen pins) --------
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

// ADC reference assumption (ESP32 ADC is not precision-calibrated).
// If you have a known reference, adjust VREF.
constexpr float VREF = 3.30f;   // volts
constexpr int   ADC_MAX = 4095; // 12-bit ADC

void setup() {
  // USB CDC Serial (enable "USB CDC On Boot" in board settings)
  Serial.begin(115200);

  while (!Serial) { delay(10); }
  Serial.println("USB-CDC ready");

  // Set up SPI pins for this bus, then init display
  SPI.begin(TFT_SCLK, -1, TFT_MOSI, TFT_CS);
  // For ST7735S, pick your init sequence:
  // If your panel is 128x160, INITR_BLACKTAB is commonly right.
  tft.initR(INITR_GREENTAB);
  tft.setRotation(3);
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextWrap(false);

  // Backlight
  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH);   // full brightness; use PWM if you want dimming

  // ADC pin
  pinMode(ADC_PIN, INPUT);

  // Title
  tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
  tft.setCursor(0, 0);
  tft.setTextSize(2);
  tft.println("Input 1");

  // Small hint line
  tft.setTextSize(1);
  tft.println("Raw + Volts to LCD & USB");
}

void drawReading(uint16_t raw, float volts) {
  // Clear reading area
  tft.fillRect(0, 30, 160, 60, ST77XX_BLACK);

  tft.setCursor(0, 30);
  tft.setTextSize(2);
  tft.setTextColor(ST77XX_CYAN, ST77XX_BLACK);
  tft.print("RAW: ");
  tft.println(raw);

  tft.setTextColor(ST77XX_YELLOW, ST77XX_BLACK);
  tft.print("V: ");
  tft.println(volts, 3);  // 3 decimal places
}

void loop() {
  // Read ADC (average a few samples to reduce noise)
  const int N = 8;
  uint32_t sum = 0;
  for (int i = 0; i < N; ++i) {
    sum += analogRead(ADC_PIN);
    delay(2);
  }
  uint16_t raw = sum / N;
  float volts = (raw * VREF) / ADC_MAX;

  // To LCD
  drawReading(raw, volts);

  // To CDC Serial
  Serial.print("AN1 raw=");
  Serial.print(raw);
  Serial.print("  volts=");
  Serial.println(volts, 4);

  delay(200); // update ~5 times/sec
}
