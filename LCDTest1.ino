
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library
#include <TouchScreen.h>


// The control pins for the LCD can be assigned to any digital or
// analog pins...but we'll use the analog pins as this allows us to
// double up the pins with the touch screen (see the TFT paint example).
#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0

#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

#define YP A3  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 9   // can be a digital pin
#define XP 8   // can be a digital pin

//colors
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define ORANGE  0xFD20
#define WHITE   0xFFFF
#define GRAY    0x2222

//touch values
#define TS_MINX 130
#define TS_MAXX 900

#define TS_MINY 80
#define TS_MAXY 900

#define MINPRESSURE 10
#define MAXPRESSURE 1000

#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;

//float array to keep track of measured voltage of the batteries
float voltage[16];
//int array to check if the Energy States have changed
int lastEnergyState[16];
//int to check which module is selected and which screen you are on
//(-1 for first screen, 0-15 for the modules selected screens)
int selectedModule = -1;
//boolean to check if the baselines where already drawn to save time
boolean baseDrawn = false;
//touchscreen variable
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
// Adafruit_TFTLCD tft;
//text data
tft.setTextColor(BLACK);

//funktion to get the length of the string for centered positioning
uint16_t stringLength(String stringL, int x, int y)
{
  int16_t x1, y1;
  uint16_t wc, hc;
  tft.getTextBounds(stringL, x, y, &x1, &y1, &wc, &hc); //calc width of new string
  return wc;
}

//first Screen
void firstScreen(TSPoint p)
{
  //Text data set up  
  tft.setTextSize(1);
  //loops to refer to all areas of a 4x4 repetitive layout
  for(int i = 0;i < 4;i++)
  {
    for(int j = 0;j < 4;j++)
    {
      //initial base lines
      if(baseDrawn == false)
      {
        if(j == 0 && i == 0)
        {
          tft.fillScreen(WHITE);
        }
        tft.drawLine(1+j*60,1+i*80,58+j*60,1+i*80,BLACK);
        tft.drawLine(58+j*60,1+i*80,58+j*60,78+i*80,BLACK);
        tft.drawLine(58+j*60,78+i*80,1+j*60,78+i*80,BLACK);
        tft.drawLine(1+j*60,78+i*80,1+j*60,1+i*80,BLACK);
        String moduleText = "Modul ";
        moduleText += String(1+j+i*4);
        tft.setCursor(31+j*60 - stringLength(moduleText,31,4) / 2, 4+i*80);
        tft.println(moduleText);


        //tft.setCursor(31+j*60,4+i*80);
        //tft.println(a);
        //drawCentreString(a,31+j*60,4+i*80);
  
        tft.drawRect(16+j*60,22+i*80,28,2,BLACK);
        tft.drawRect(16+j*60,22+i*80,2,50,BLACK);
        tft.drawRect(42+j*60,22+i*80,2,50,BLACK);
        tft.drawRect(16+j*60,70+i*80,28,2,BLACK);
        tft.fillRect(26+j*60,18+i*80,8,4,BLACK);

        lastEnergyState[j+i*4] = -2;

        if(j == 3 && i == 3)
        {
          //track that the baselines are drawn so they dont get repeated
          baseDrawn = true;
        }
      }
        /*
      voltage[j+i*4]=4.11-(0.01*(j+i*4)*3); //test voltages//
      if(j == 3 && i == 3)                  //
        {
          voltage[j+i*4]=2; //
        }
*/
      //display the different batterie status
      //100%
      if(voltage[j+i*4] > 4.10 && lastEnergyState[j+i*4] != 10)
      {
        lastEnergyState[j+i*4] = 10;
        tft.fillRect(18+j*60,24+i*80,24,46,WHITE);
        tft.fillRect(11+j*60,65+i*80,5,11,WHITE);
        tft.fillRect(44+j*60,19+i*80,5,11,WHITE);
        tft.fillRect(18+j*60,24+i*80,24,46,GREEN);
      }
      //90%
      else if(voltage[j+i*4] > 4.06 && voltage[j+i*4] <= 4.10 && lastEnergyState[j+i*4] != 9)
      {
        lastEnergyState[j+i*4] = 9;
        tft.fillRect(18+j*60,24+i*80,24,46,WHITE);
        tft.fillRect(11+j*60,65+i*80,5,11,WHITE);
        tft.fillRect(44+j*60,19+i*80,5,11,WHITE);
        tft.fillRect(18+j*60,29+i*80,24,41,GREEN);
      }
      //80%
      else if(voltage[j+i*4] > 3.95 && voltage[j+i*4] <= 4.06 && lastEnergyState[j+i*4] != 8)
      {
        lastEnergyState[j+i*4] = 8;
        tft.fillRect(18+j*60,24+i*80,24,46,WHITE);
        tft.fillRect(11+j*60,65+i*80,5,11,WHITE);
        tft.fillRect(44+j*60,19+i*80,5,11,WHITE);
        tft.fillRect(18+j*60,33+i*80,24,37,GREEN);
      }
      //70%
      else if(voltage[j+i*4] > 3.90 && voltage[j+i*4] <= 3.95 && lastEnergyState[j+i*4] != 7)
      {
        lastEnergyState[j+i*4] = 7;
        tft.fillRect(18+j*60,24+i*80,24,46,WHITE);
        tft.fillRect(11+j*60,65+i*80,5,11,WHITE);
        tft.fillRect(44+j*60,19+i*80,5,11,WHITE);
        tft.fillRect(18+j*60,38+i*80,24,32,GREEN);
      }
      //60%
      else if(voltage[j+i*4] > 3.88 && voltage[j+i*4] <= 3.90 && lastEnergyState[j+i*4] != 6)
      {
        lastEnergyState[j+i*4] = 6;
        tft.fillRect(18+j*60,24+i*80,24,46,WHITE);
        tft.fillRect(11+j*60,65+i*80,5,11,WHITE);
        tft.fillRect(44+j*60,19+i*80,5,11,WHITE);
        tft.fillRect(18+j*60,42+i*80,24,28,GREEN);
      }
      //50%
      else if(voltage[j+i*4] > 3.84 && voltage[j+i*4] <= 3.88 && lastEnergyState[j+i*4] != 5)
      {
        lastEnergyState[j+i*4] = 5;
        tft.fillRect(18+j*60,24+i*80,24,46,WHITE);
        tft.fillRect(11+j*60,65+i*80,5,11,WHITE);
        tft.fillRect(44+j*60,19+i*80,5,11,WHITE);
        tft.fillRect(18+j*60,47+i*80,24,23,YELLOW);
      }
      //40%
      else if(voltage[j+i*4] > 3.82 && voltage[j+i*4] <= 3.84 && lastEnergyState[j+i*4] != 4)
      {
        lastEnergyState[j+i*4] = 4;
        tft.fillRect(18+j*60,24+i*80,24,46,WHITE);
        tft.fillRect(11+j*60,65+i*80,5,11,WHITE);
        tft.fillRect(44+j*60,19+i*80,5,11,WHITE);
        tft.fillRect(18+j*60,52+i*80,24,18,YELLOW);
      }
      //30%
      else if(voltage[j+i*4] > 3.80 && voltage[j+i*4] <= 3.82 && lastEnergyState[j+i*4] != 3)
      {
        lastEnergyState[j+i*4] = 3;
        tft.fillRect(18+j*60,24+i*80,24,46,WHITE);
        tft.fillRect(11+j*60,65+i*80,5,11,WHITE);
        tft.fillRect(44+j*60,19+i*80,5,11,WHITE);
        tft.fillRect(18+j*60,56+i*80,24,14,ORANGE);
      }
      //20%
      else if(voltage[j+i*4] > 3.76 && voltage[j+i*4] <= 3.80 && lastEnergyState[j+i*4] != 2)
      {
        lastEnergyState[j+i*4] = 2;
        tft.fillRect(18+j*60,24+i*80,24,46,WHITE);
        tft.fillRect(11+j*60,65+i*80,5,11,WHITE);
        tft.fillRect(44+j*60,19+i*80,5,11,WHITE);
        tft.fillRect(18+j*60,61+i*80,24,9,ORANGE);
      }
      //10%
      else if(voltage[j+i*4] > 3.71 && voltage[j+i*4] <= 3.76 && lastEnergyState[j+i*4] != 1)
      {
        lastEnergyState[j+i*4] = 1;
        tft.fillRect(18+j*60,24+i*80,24,46,WHITE);
        tft.fillRect(11+j*60,65+i*80,5,11,WHITE);
        tft.fillRect(44+j*60,19+i*80,5,11,WHITE);
        tft.fillRect(18+j*60,65+i*80,24,5,RED);
      }
      //0%
      else if(voltage[j+i*4] > 3.50 && voltage[j+i*4] <= 3.71 && lastEnergyState[j+i*4] != 0)
      {
        lastEnergyState[j+i*4] = 0;
        tft.fillRect(18+j*60,24+i*80,24,46,WHITE);
        tft.fillRect(11+j*60,65+i*80,5,11,WHITE);
        tft.fillRect(44+j*60,19+i*80,5,11,WHITE);
        tft.fillRect(18+j*60,69+i*80,24,1,RED);
        tft.fillRect(29+j*60,40+i*80,2,11,BLACK);
        tft.fillRect(29+j*60,53+i*80,2,2,BLACK);
      }
      //No connection
      else if(voltage[j+i*4] <= 3.50 && lastEnergyState[j+i*4] != -1)
      {
        lastEnergyState[j+i*4] = -1;
        tft.fillRect(18+j*60,24+i*80,24,46,WHITE);
        tft.drawLine(11+j*60,76+i*80,48+j*60,19+i*80,BLACK);
        //tft.fillRect(2+j*60,2+i*80,56,76,GRAY);
      }

      //Touch
      if(p.x>0+j*60 && p.x<59+j*60 && p.y>0+i*80 && p.y<79+i*80 && selectedModule == -1)// The user has pressed inside the red rectangle
      {
        selectedModule = j+i*4;
        Serial.print(selectedModule+1);
        delay(100);
      }
      if(j == 3 && i == 3 && selectedModule != -1)
      {
        //set the boolean to false for the new Screen
        baseDrawn = false;
      }
    }  
  }
}

void secondScreen(TSPoint p)
{
  //Text data set up
  tft.setTextSize(3);
  //initial base lines
  if(baseDrawn == false)
  {
    Serial.print("SECONDSTREAM BASE");
    Serial.print("fillscreenwhite");
    tft.fillScreen(WHITE);
    tft.setTextColor(BLACK);  
    String moduleText = "Modul ";
    moduleText += String(selectedModule+1);
    tft.setCursor(121 - stringLength(moduleText,31,4) / 2, 16);
    tft.println(moduleText);

    tft.fillRect(104,56,32,16,BLACK);
    tft.fillRect(64,72,112,4,BLACK);
    tft.fillRect(64,72,4,216,BLACK);
    tft.fillRect(172,72,4,216,BLACK);
    tft.fillRect(64,284,112,4,BLACK);

    //reset the last energy state so it gets drawn on the new screen even if it didnt change
    lastEnergyState[selectedModule] = -2;

    //display the batterie status of the selected module
      //100%
      if(voltage[selectedModule] > 4.10 && lastEnergyState[selectedModule] != 10)
      {
        lastEnergyState[selectedModule] = 10;
        tft.fillRect(68,76,104,208,WHITE);
        tft.fillRect(176,56,16,24,WHITE);
        tft.fillRect(48,280,16,24,WHITE);
        tft.fillRect(68,76,104,208,GREEN);
        moduleText = "100%";
        tft.setCursor(121 - stringLength(moduleText,31,4) / 2, 166);
        tft.println(moduleText);
      }
      //95%
      else if(voltage[selectedModule] > 4.08 && voltage[selectedModule] <= 4.10 && lastEnergyState[selectedModule] != 20)
      {
        lastEnergyState[selectedModule] = 20;
        tft.fillRect(68,76,104,208,WHITE);
        tft.fillRect(176,56,16,24,WHITE);
        tft.fillRect(48,280,16,24,WHITE);
        tft.fillRect(68,87,104,197,GREEN);
        moduleText = "95%";
        tft.setCursor(121 - stringLength(moduleText,31,4) / 2, 166);
        tft.println(moduleText);
      }
      //90%
      else if(voltage[selectedModule] > 4.06 && voltage[selectedModule] <= 4.08 && lastEnergyState[selectedModule] != 9)
      {
        lastEnergyState[selectedModule] = 9;
        tft.fillRect(68,76,104,208,WHITE);
        tft.fillRect(176,56,16,24,WHITE);
        tft.fillRect(48,280,16,24,WHITE);
        tft.fillRect(68,97,104,187,GREEN);
        moduleText = "90%";
        tft.setCursor(121 - stringLength(moduleText,31,4) / 2, 166);
        tft.println(moduleText);
      }
      //85%
      else if(voltage[selectedModule] > 4.00 && voltage[selectedModule] <= 4.06 && lastEnergyState[selectedModule] != 19)
      {
        lastEnergyState[selectedModule] = 19;
        tft.fillRect(68,76,104,208,WHITE);
        tft.fillRect(176,56,16,24,WHITE);
        tft.fillRect(48,280,16,24,WHITE);
        tft.fillRect(68,108,104,176,GREEN);
        moduleText = "85%";
        tft.setCursor(121 - stringLength(moduleText,31,4) / 2, 166);
        tft.println(moduleText);
      }
      //80%
      else if(voltage[selectedModule] > 3.95 && voltage[selectedModule] <= 4.00 && lastEnergyState[selectedModule] != 8)
      {
        lastEnergyState[selectedModule] = 8;
        tft.fillRect(68,76,104,208,WHITE);
        tft.fillRect(176,56,16,24,WHITE);
        tft.fillRect(48,280,16,24,WHITE);
        tft.fillRect(68,118,104,166,GREEN);
        moduleText = "80%";
        tft.setCursor(121 - stringLength(moduleText,31,4) / 2, 166);
        tft.println(moduleText);
      }
      //75%
      else if(voltage[selectedModule] > 3.92 && voltage[selectedModule] <= 3.95 && lastEnergyState[selectedModule] != 18)
      {
        lastEnergyState[selectedModule] = 18;
        tft.fillRect(68,76,104,208,WHITE);
        tft.fillRect(176,56,16,24,WHITE);
        tft.fillRect(48,280,16,24,WHITE);
        tft.fillRect(68,129,104,155,GREEN);
        moduleText = "75%";
        tft.setCursor(121 - stringLength(moduleText,31,4) / 2, 166);
        tft.println(moduleText);
      }
      //70%
      else if(voltage[selectedModule] > 3.90 && voltage[selectedModule] <= 3.92 && lastEnergyState[selectedModule] != 7)
      {
        lastEnergyState[selectedModule] = 7;
        tft.fillRect(68,76,104,208,WHITE);
        tft.fillRect(176,56,16,24,WHITE);
        tft.fillRect(48,280,16,24,WHITE);
        tft.fillRect(68,139,104,145,GREEN);
        moduleText = "70%";
        tft.setCursor(121 - stringLength(moduleText,31,4) / 2, 166);
        tft.println(moduleText);
      }
      //65%
      else if(voltage[selectedModule] > 3.89 && voltage[selectedModule] <= 3.90 && lastEnergyState[selectedModule] != 17)
      {
        lastEnergyState[selectedModule] = 17;
        tft.fillRect(68,76,104,208,WHITE);
        tft.fillRect(176,56,16,24,WHITE);
        tft.fillRect(48,280,16,24,WHITE);
        tft.fillRect(68,150,104,134,GREEN);
        moduleText = "65%";
        tft.setCursor(121 - stringLength(moduleText,31,4) / 2, 166);
        tft.println(moduleText);
      }
      //60%
      else if(voltage[selectedModule] > 3.88 && voltage[selectedModule] <= 3.89 && lastEnergyState[selectedModule] != 6)
      {
        lastEnergyState[selectedModule] = 6;
        tft.fillRect(68,76,104,208,WHITE);
        tft.fillRect(176,56,16,24,WHITE);
        tft.fillRect(48,280,16,24,WHITE);
        tft.fillRect(68,160,104,124,GREEN);
        moduleText = "60%";
        tft.setCursor(121 - stringLength(moduleText,31,4) / 2, 166);
        tft.println(moduleText);
      }
      //55%
      else if(voltage[selectedModule] > 3.86 && voltage[selectedModule] <= 3.88 && lastEnergyState[selectedModule] != 16)
      {
        lastEnergyState[selectedModule] = 16;
        tft.fillRect(68,76,104,208,WHITE);
        tft.fillRect(176,56,16,24,WHITE);
        tft.fillRect(48,280,16,24,WHITE);
        tft.fillRect(68,171,104,113,GREEN);
        moduleText = "55%";
        tft.setCursor(121 - stringLength(moduleText,31,4) / 2, 166);
        tft.println(moduleText);
      }
      //50%
      else if(voltage[selectedModule] > 3.84 && voltage[selectedModule] <= 3.86 && lastEnergyState[selectedModule] != 5)
      {
        lastEnergyState[selectedModule] = 5;
        tft.fillRect(68,76,104,208,WHITE);
        tft.fillRect(176,56,16,24,WHITE);
        tft.fillRect(48,280,16,24,WHITE);
        tft.fillRect(68,180,104,104,YELLOW);
        moduleText = "50%";
        tft.setCursor(121 - stringLength(moduleText,31,4) / 2, 166);
        tft.println(moduleText);
      }
      //45%
      else if(voltage[selectedModule] > 3.83 && voltage[selectedModule] <= 3.84 && lastEnergyState[selectedModule] != 15)
      {
        lastEnergyState[selectedModule] = 15;
        tft.fillRect(68,76,104,208,WHITE);
        tft.fillRect(176,56,16,24,WHITE);
        tft.fillRect(48,280,16,24,WHITE);
        tft.fillRect(68,191,104,93,YELLOW);
        moduleText = "45%";
        tft.setCursor(121 - stringLength(moduleText,31,4) / 2, 166);
        tft.println(moduleText);
      }
      //40%
      else if(voltage[selectedModule] > 3.82 && voltage[selectedModule] <= 3.83 && lastEnergyState[selectedModule] != 4)
      {
        lastEnergyState[selectedModule] = 4;
        tft.fillRect(68,76,104,208,WHITE);
        tft.fillRect(176,56,16,24,WHITE);
        tft.fillRect(48,280,16,24,WHITE);
        tft.fillRect(68,201,104,83,YELLOW);
        moduleText = "40%";
        tft.setCursor(121 - stringLength(moduleText,31,4) / 2, 166);
        tft.println(moduleText);
      }
      //35%
      else if(voltage[selectedModule] > 3.81 && voltage[selectedModule] <= 3.82 && lastEnergyState[selectedModule] != 14)
      {
        lastEnergyState[selectedModule] = 14;
        tft.fillRect(68,76,104,208,WHITE);
        tft.fillRect(176,56,16,24,WHITE);
        tft.fillRect(48,280,16,24,WHITE);
        tft.fillRect(68,212,104,72,YELLOW);
        moduleText = "35%";
        tft.setCursor(121 - stringLength(moduleText,31,4) / 2, 166);
        tft.println(moduleText);
      }
      //30%
      else if(voltage[selectedModule] > 3.80 && voltage[selectedModule] <= 3.81 && lastEnergyState[selectedModule] != 3)
      {
        lastEnergyState[selectedModule] = 3;
        tft.fillRect(68,76,104,208,WHITE);
        tft.fillRect(176,56,16,24,WHITE);
        tft.fillRect(48,280,16,24,WHITE);
        tft.fillRect(68,222,104,62,ORANGE);
        moduleText = "30%";
        tft.setCursor(121 - stringLength(moduleText,31,4) / 2, 166);
        tft.println(moduleText);
      }
      //25%
      else if(voltage[selectedModule] > 3.78 && voltage[selectedModule] <= 3.80 && lastEnergyState[selectedModule] != 13)
      {
        lastEnergyState[selectedModule] = 13;
        tft.fillRect(68,76,104,208,WHITE);
        tft.fillRect(176,56,16,24,WHITE);
        tft.fillRect(48,280,16,24,WHITE);
        tft.fillRect(68,233,104,51,ORANGE);
        moduleText = "25%";
        tft.setCursor(121 - stringLength(moduleText,31,4) / 2, 166);
        tft.println(moduleText);
      }
      //20%
      else if(voltage[selectedModule] > 3.76 && voltage[selectedModule] <= 3.78 && lastEnergyState[selectedModule] != 2)
      {
        lastEnergyState[selectedModule] = 2;
        tft.fillRect(68,76,104,208,WHITE);
        tft.fillRect(176,56,16,24,WHITE);
        tft.fillRect(48,280,16,24,WHITE);
        tft.fillRect(68,243,104,41,ORANGE);
        moduleText = "20%";
        tft.setCursor(121 - stringLength(moduleText,31,4) / 2, 166);
        tft.println(moduleText);
      }
      //15%
      else if(voltage[selectedModule] > 3.74 && voltage[selectedModule] <= 3.76 && lastEnergyState[selectedModule] != 12)
      {
        lastEnergyState[selectedModule] = 12;
        tft.fillRect(68,76,104,208,WHITE);
        tft.fillRect(176,56,16,24,WHITE);
        tft.fillRect(48,280,16,24,WHITE);
        tft.fillRect(68,254,104,30,RED);
        moduleText = "15%";
        tft.setCursor(121 - stringLength(moduleText,31,4) / 2, 166);
        tft.println(moduleText);
      }
      //10%
      else if(voltage[selectedModule] > 3.71 && voltage[selectedModule] <= 3.74 && lastEnergyState[selectedModule] != 1)
      {
        lastEnergyState[selectedModule] = 1;
        tft.fillRect(68,76,104,208,WHITE);
        tft.fillRect(176,56,16,24,WHITE);
        tft.fillRect(48,280,16,24,WHITE);
        tft.fillRect(68,264,104,20,RED);
        moduleText = "10%";
        tft.setCursor(121 - stringLength(moduleText,31,4) / 2, 166);
        tft.println(moduleText);
      }
      //5%
      else if(voltage[selectedModule] > 3.705 && voltage[selectedModule] <= 3.71 && lastEnergyState[selectedModule] != 11)
      {
        lastEnergyState[selectedModule] = 11;
        tft.fillRect(68,76,104,208,WHITE);
        tft.fillRect(176,56,16,24,WHITE);
        tft.fillRect(48,280,16,24,WHITE);
        tft.fillRect(68,275,104,9,RED);
        moduleText = "5%";
        tft.setCursor(121 - stringLength(moduleText,31,4) / 2, 166);
        tft.println(moduleText);
      }
      //0%
      else if(voltage[selectedModule] > 3.50 && voltage[selectedModule] <= 3.705 && lastEnergyState[selectedModule] != 0)
      {
        lastEnergyState[selectedModule] = 0;
        tft.fillRect(68,76,104,208,WHITE);
        tft.fillRect(176,56,16,24,WHITE);
        tft.fillRect(48,280,16,24,WHITE);
        tft.fillRect(68,283,104,1,RED);
        moduleText = "0%";
        tft.setCursor(121 - stringLength(moduleText,31,4) / 2, 166);
        tft.println(moduleText);
      }
      //No connection
      else if(voltage[selectedModule] <= 3.50 && lastEnergyState[selectedModule] != -1)
      {
        lastEnergyState[selectedModule] = -1;
        tft.fillRect(68,76,104,208,WHITE);
        //tft.drawLine(56,288,192,56,BLACK);
        tft.setTextSize(2);
        moduleText = "No Connection";
        tft.setCursor(121 - stringLength(moduleText,31,4) / 2, 296);
        tft.println(moduleText);
        //tft.fillRect(2+j*60,2+i*80,56,76,GRAY);
      }
    
    //track that the baselines are drawn so they dont get repeated
    baseDrawn = true;
  }

  //Touch
  if(p.x>10 && p.x<230 && p.y>10 && p.y<310 && selectedModule != -1)// The user has pressed inside the red rectangle
  {
    //No Module selected anymore
    selectedModule = -1;
    Serial.print(selectedModule+1);
    //set the boolean to false for the new Screen
    baseDrawn = false;
    delay(100);
  }
}

void setup() {
  Serial.begin(9600);
  Serial.println(F("TFT LCD test"));
  tft.reset();

  //get the right driver version for the LCD
  uint16_t identifier = tft.readID();
  if(identifier == 0x9325) {
    Serial.println(F("Found ILI9325 LCD driver"));
  } else if(identifier == 0x9328) {
    Serial.println(F("Found ILI9328 LCD driver"));
  } else if(identifier == 0x4535) {
    Serial.println(F("Found LGDP4535 LCD driver"));
  }else if(identifier == 0x7575) {
    Serial.println(F("Found HX8347G LCD driver"));
  } else if(identifier == 0x9341) {
    Serial.println(F("Found ILI9341 LCD driver"));
  }else if(identifier == 0x7783) {
    Serial.println(F("Found ST7781 LCD driver"));
  }else if(identifier == 0x8230) {
    Serial.println(F("Found UC8230 LCD driver"));  
  }
  else if(identifier == 0x8357) {
    Serial.println(F("Found HX8357D LCD driver"));
  } else if(identifier==0x0101)
  {     
      identifier=0x9341;
       Serial.println(F("Found 0x9341 LCD driver"));
  }else {
    Serial.print(F("Unknown LCD driver chip: "));
    Serial.println(identifier, HEX);
    Serial.println(F("If using the Adafruit 2.8\" TFT Arduino shield, the line:"));
    Serial.println(F("  #define USE_ADAFRUIT_SHIELD_PINOUT"));
    Serial.println(F("should appear in the library header (Adafruit_TFT.h)."));
    Serial.println(F("If using the breakout board, it should NOT be #defined!"));
    Serial.println(F("Also if using the breakout, double-check that all wiring"));
    Serial.println(F("matches the tutorial."));
    identifier=0x9341;
   
  }

  tft.begin(identifier);

  Serial.println(F("Benchmark                Time (microseconds)"));

  //Set up the orientation of the display
  tft.setRotation(0);

  //Touchscreen variables
  int x1, y1, x2, y2 ,xAdd ,yAdd,
  w = tft.width(),
  h = tft.height();
  
  tft.fillScreen(WHITE);
  delay(500);

  for(int i = 0;i < 16;i++)
  {
      lastEnergyState[i] = -1;
  }

}

void loop() {

  //measure the voltage of the batterie
  int sensor = analogRead(A15);
  voltage[0] = sensor * (5 / 1023.00);

  //create variable to track the point and pressure of a touch
  TSPoint p = ts.getPoint();  //Get touch point
  //This is important, because the libraries are sharing pins
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);

  //When the screen is touched
  if (p.z > ts.pressureThreshhold) {

   Serial.print("\n");

   //map the voltage of the pins to the pixels of the screen
   p.x = map(p.x, TS_MAXX, TS_MINX, 0, 240);
   p.y = map(p.y, TS_MAXY, TS_MINY, 320, 0); //changing the oriantation to get x=0 and y=0 in one corner of the display

   Serial.print("X = "); Serial.print(p.x);
   Serial.print("\tY = "); Serial.print(p.y);
   Serial.print("\n");  
  }

  //call the selected screen
  if(selectedModule == -1)
  {
    firstScreen(p);
  }
  else
  {
    secondScreen(p);
  }
  Serial.print(selectedModule+1);
  Serial.print("\n"); 
  //framerate of the funktion
  delay(10);  
}
