#include <Adafruit_GFX.h> 
#include <Adafruit_SSD1306.h>


#define OLED_RESET LED_BUILTIN
Adafruit_SSD1306 display(OLED_RESET);

#if (SSD1306_LCDHEIGHT != 64)
#error("Altura incorrecta, cambie en la libreria de Adafruit_SSD1306.h!");
#endif

void read_temp() {
display.clearDisplay();
display.setTextSize(2);
display.setTextColor(WHITE);
display.setCursor(0,10);
display.println("termopar 1");
display.setCursor(0,32);
display.println("xx C");
display.display();
delay(2000);
}
void setup() {
display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
display.clearDisplay();
//display.drawBitmap(0,0,logo,128,64,1);
display.display();
delay(5000);
}
void loop() {
read_temp();
display.clearDisplay();
display.setTextSize(3);
display.setCursor(0,10);
display.println("Almexa");
display.display();
delay(2000);
}
