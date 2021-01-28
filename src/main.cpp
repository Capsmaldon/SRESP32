#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

unsigned long counter = 0;
bool flip = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  display.display();
  delay(2000); // Pause for 2 seconds
  display.clearDisplay();
  display.display();

  display.setTextSize(2);
  display.setTextColor(WHITE);
}

const int SC_ENTER = 0;
const int SC_BACKSPACE = 1;
const int SC_ARROW_UP = 2;
const int SC_ARROW_DOWN = 3;
const int SC_ARROW_LEFT = 4;
const int SC_ARROW_RIGHT = 5;

int characterIndex = 0;
char passwordBuffer[64];

void processSpecialCharacter(int specialCharacter)
{
  if(specialCharacter == SC_BACKSPACE)
  {
    if(characterIndex > 0) characterIndex--;
    passwordBuffer[characterIndex] = '\0';
    display.clearDisplay();
    display.setCursor(0,0);
    display.println(passwordBuffer);
    display.display();
  }
}

void processCharacter(char character)
{
  passwordBuffer[characterIndex] = character;
  
  if(characterIndex < 62)
  {
    characterIndex++;
    passwordBuffer[characterIndex] = '\0';
  }

  display.clearDisplay();
  display.setCursor(0,0);
  display.println(passwordBuffer);
  display.display();
}

void processSerialInput()
{
  int availableBytes = 0;

  while(availableBytes = Serial.available())
  {
    int bufferSize = availableBytes;
    char buffer[bufferSize];

    int readBytes = Serial.readBytes(buffer, bufferSize);

    for(int c = 0; c < readBytes; c++)
    {
      char character = buffer[c];
      if(character == 0x1b)
      {
        if(buffer[c+1] == 0x5b)
        {
          if(buffer[c+2] == 0x41) { Serial.printf("<Up>"); c += 2; processSpecialCharacter(SC_ARROW_UP);}
          else if(buffer[c+2] == 0x42) { Serial.printf("<Down>"); c += 2; processSpecialCharacter(SC_ARROW_DOWN);}
          else if(buffer[c+2] == 0x43) { Serial.printf("<Right>"); c += 2; processSpecialCharacter(SC_ARROW_RIGHT);}
          else if(buffer[c+2] == 0x44) { Serial.printf("<Left>"); c += 2; processSpecialCharacter(SC_ARROW_LEFT);}
        }
      }
      else if(character == 0xd && buffer[c+1] == 0xa)
      {
        c += 1;
        Serial.printf("\n");
        processSpecialCharacter(SC_ENTER);
      }
      else if(character == 0x8)
      {
        Serial.printf("<Backspace>");
        processSpecialCharacter(SC_BACKSPACE);
      }
      else
      {
        Serial.printf("%c", character);
        processCharacter(character);
      }
      
      
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  processSerialInput();
  
  if(counter == 40)
  {
    digitalWrite(LED_BUILTIN, flip);
    flip = !flip;
    counter = 0;
  }

  counter++;
  delay(10);
}