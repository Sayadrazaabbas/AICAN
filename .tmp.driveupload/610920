#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>
#include <Fonts/FreeSansBold9pt7b.h>
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSans12pt7b.h>
#include <Fonts/FreeMonoBold9pt7b.h>
#include <Fonts/Picopixel.h>

Adafruit_SH1106 display(21, 22);


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels



void displays() {
  display.clearDisplay();
  display.drawLine(0, 15, display.width() - 3, 15, WHITE);
  display.drawLine(85, 15, 85, 0, WHITE);
  display.drawLine(35, 15, 35, 0, WHITE);
  //display.fillRect(1, 21, 126, 42, BLACK);

  display.setFont();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 5);
  char str8[10];
  sprintf(str8, "%d", y);
  display.print(str8);
  display.print(" %");

  display.setCursor(40, 5);
  char str2[10];
  if (vals > 100 || vals < 0)  {
    display.setCursor(45, 5);
    display.print("NA");
  }
  else {
    sprintf(str2, "%.1f", vals);
    display.print(str2);
    display.print(" C");
  }

  display.setFont();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(90, 5);
  int z = mVx;
  char str3[10];
  sprintf(str3, "%d", z);
  display.print(str3);
  display.print("mV");

  display.setFont();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(50, 20);
  display.print("pH:");
  display.setCursor(110, 20);
  if (hodl == 1) display.print("ST");

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setFont(&FreeSans9pt7b);
  display.setCursor(5, 55);
  char str[10];
  sprintf(str, "%.2f", x);
  display.print(str);
  Serial.print("display_ph:");


  Serial.print(str);
  display.display();
}

void display_init() {
  display.begin(SH1106_SWITCHCAPVCC, 0x3C);
  Serial.print("Initializing OLED ");
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(30, 15);
  display.print("VENUS");
  display.setCursor(35, 45);
  display.print("LABS");
  display.display();

}

void cal_disp(int d) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(14, 30);
  display.print("Calibrating");
  display.setCursor(14, 60);
  if (d == 1){ display.print("B_1:-");display.print(bufferValue[0]);}
  else if (d == 2) {display.print("B_2:-");display.print(bufferValue[1]);}
  else if (d == 3) {display.print("B_3:-");display.print(bufferValue[2]);}
  else if (d == 4){ display.print("B_4:-");display.print(bufferValue[3]);}
  else if (d == 5){ display.print("B_5:-");display.print(bufferValue[4]);}
  display.display();
}

void battery_warning() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(14, 30);
  display.print("BATTERY");
  display.setCursor(28, 60);
  display.print("LOW");
  display.display();
}

void cal_home() {
  display.clearDisplay();
  display.setFont();
  display.setTextSize(1);
  display.setCursor(30, 5);
  display.print("CALIBRATION");
  display.setCursor(50, 15);
  display.print("MODE");
  display.setCursor(12, 40);
  display.print("Press OK : Start");
  display.setCursor(0, 50);
  display.print("Press down key : Back");
  display.display();
}

void display_cal_timer(int y) {
  display.clearDisplay();
  display.drawLine(0, 20, display.width() - 3, 20, WHITE);
  display.setFont();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("Keep pH probe dipped");
  display.setCursor(0, 9);
  display.print("till timer ends");
  display.setCursor(5, 22);
  display.print("Seconds Remaining:");
  display.setFont(&FreeSans9pt7b);
  display.setTextSize(2);
  char string[10];
  y = 45 - (y / 1000);
  if (y > 0) sprintf(string, "%d", y);
  display.setCursor(15, 60);
  display.print(string);
  display.display();
}

void buf_run(int c, float y) {
  display.clearDisplay();
  display.drawLine(0, 20, display.width() - 3, 20, WHITE);
  display.setFont();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("Press OK to change");
  display.setCursor(0, 9);
  display.print("buffer value");
  display.setCursor(15, 25);
  display.print("SELECT BUFFER");
  display.print(c);
  display.print(":");
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setFont(&FreeSans9pt7b);
  display.setCursor(15, 60);
  float xyz = y;
  char string[10];
  sprintf(string, "%.2f", xyz);
  display.print(string);
  display.display();
}

void runner_val(int c, float y) {
  display.clearDisplay();
  display.drawLine(0, 20, display.width() - 3, 20, WHITE);
  display.setFont();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("Press arrow keys to");
  display.setCursor(0, 9);
  display.print("move value");
  display.setCursor(15, 25);
  display.print("SELECT BUFFER");
  display.print(c);
  display.print(":");
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setFont(&FreeSans9pt7b);
  display.setCursor(15, 60);
  float xyz = y;
  char string[10];
  sprintf(string, "%.2f", xyz);
  display.print(string);
  display.display();
}

void log_mode_disp() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(5, 15);
  display.print("BUTTON LOG");
  display.setCursor(20, 45);
  display.print("MODE ON");
  display.display();
}

void logman_disp() {
  display.clearDisplay();
  display.setFont();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(30, 15);
  display.print("MEMORY");
  display.setCursor(35, 30);
  display.print("FULL");
  display.setCursor(10, 50);
  display.print("Do you want to continue?");
  display.display();

}

void probe_display() {
  display.clearDisplay();
  display.setFont();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(25, 0);
  display.print("PROBE HEALTH");
  display.setCursor(0, 20);
  display.print("Average Slope: ");
  char stringA[10], slopeA[10], slopeB[10], slopeC[10], slopeD[10];
  sprintf(stringA, "%.1f", slope_total);
  sprintf(slopeA, "%.1f", buf_slope[0]);
  sprintf(slopeB, "%.1f", buf_slope[1]);
  sprintf(slopeC, "%.1f", buf_slope[2]);
  sprintf(slopeD, "%.1f", buf_slope[3]);
  display.print(stringA);
  display.setCursor(0, 30);
  display.print("S1: ");
  display.print(buf_slope[0]);
  display.setCursor(60, 30);
  display.print("S2: ");
  display.print(buf_slope[1]);
  display.setCursor(0, 40);
  display.print("S3: ");
  display.print(buf_slope[2]);
  display.setCursor(60, 40);
  display.print("S4: ");
  display.print(buf_slope[3]);
  display.setCursor(0, 50);
  display.print("Offset: ");
  char stringB[10];
  sprintf(stringB, "%.2f", x3);
  display.print(stringB);
  display.display();

}
