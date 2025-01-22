#include "SSD1306.h"

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void oledBegin()
{
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    Serial.println(F("SSD1306 allocation failed"));
    return;
  }
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1); // 6x8
  display.setCursor(0, 0);

  // Uncomment the following line if you have a logo to display
  // display.drawBitmap(0, 0, logo_dst, SCREEN_WIDTH, SCREEN_HEIGHT, SSD1306_WHITE);
  
  display.display();
  delay(1000);
  return;
}

void clearScreen()
{
  display.setCursor(0, 0);
  display.clearDisplay();
  display.display();
}

void print(String message)
{
  Serial.print(message);
  if (display.getCursorX() + message.length() > display.width())
  {
    display.println(message);
  }
  else
  {
    display.print(message);
  }
  display.display();
}

void println(String message)
{
  Serial.println(message);

  if (display.getCursorY() == display.height() - 1)
  {
    clearScreen();
    display.println(message);
  }
  else
  {
    display.println(message);
  }

  display.display();
}

void header(String topic, bool gps)
{
  display.drawRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BLACK);
  String text = "DST Tracker";
  int width = display.width();
  int box_height = 15;
  display.drawRect(0, 0, width, box_height, SSD1306_WHITE);
  
  if (gps)
  {
    display.fillCircle(display.width() - 14 - (topic.length() * 6), 7, 4, WHITE);
  }
  else
  {
    display.fillCircle(display.width() - 14 - (topic.length() * 6), 7, 4, BLACK);
    display.drawCircle(display.width() - 14 - (topic.length() * 6), 7, 4, INVERSE);
  }
  
  display.setCursor(3, 4);
  display.print(text);
  display.setCursor(display.width() - 3 - (topic.length() * 6), 3);
  display.println(topic);

  // gps data
  display.setCursor(0, box_height + 3);
  display.print("Latitude");
  display.setCursor(SCREEN_WIDTH / 2, box_height + 3);
  display.print("Longitude");

  // dht data
  display.setCursor(0, 47);
  display.println("Temp");
  display.println("Humidity");

  display.display();
}

// After initialization only
void gpsDisplay(String latitude, String longitude)
{
  int cursorHeight = 26;

  display.fillRect(0, cursorHeight, SCREEN_WIDTH, 10, BLACK);

  display.setCursor(1, cursorHeight);
  display.print(latitude);
  display.setCursor((SCREEN_WIDTH / 2) + 1, cursorHeight);
  display.print(longitude);
  display.display();
}

void dhtDisplay(String temperature, String humidity)
{
  int cursorWidth = SCREEN_WIDTH / 2;
  int cursorHeight = 47;

  display.fillRect(cursorWidth, cursorHeight, SCREEN_WIDTH / 2, SCREEN_HEIGHT, BLACK);

  display.setCursor(cursorWidth, cursorHeight);
  display.print(temperature + " C");
  display.setCursor(cursorWidth, cursorHeight + 8);
  display.print(humidity + " %");

  display.display();
}

// Fungsi untuk menampilkan data MPU6050 di layar OLED
// Fungsi untuk menampilkan data MPU6050 di layar OLED
void mpuDisplay(String gyroX, String gyroY, String gyroZ)
{
  // Menghapus area di mana data gyroscope ditampilkan
  display.fillRect(0, 35, SCREEN_WIDTH, 10, BLACK); // Bersihkan area tampilan

  display.setCursor(1, 36); // Set posisi kursor di layar OLED
  display.print("Acl:"); // Tambahkan label jika diinginkan
  display.print(gyroX); display.print("|");
  display.print(gyroY); display.print("|");
  display.print(gyroZ);
  
  display.display(); // Tampilkan informasi di OLED
}



