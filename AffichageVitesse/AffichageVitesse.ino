/*-----( Import needed libraries )-----*/
#include <Wire.h>  // Comes with Arduino IDE
// Get the LCD I2C Library here: 
// https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads
// Move any other LCD libraries to another folder or delete them
// See Library "Docs" folder for possible commands etc.
#include <LiquidCrystal_I2C.h>
 
/*-----( Declare Constants )-----*/
/*-----( Declare objects )-----*/
// set the LCD address to 0x27 for a 20 chars 4 line display
// Set the pins on the I2C chip used for LCD connections:
//                    addr, en,rw,rs,d4,d5,d6,d7,bl,blpol
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address
 
#include <NMEAGPS.h>
#include <GPSport.h>

NMEAGPS  gps; // This parses the GPS characters
gps_fix  fix; // This holds on to the latest values

void setup()
{
  // initialize library
  lcd.begin(16,2);
  Serial.begin(9600);
  gpsPort.begin(9600);
}

//--------------------------

void loop()
{
  while (gps.available( gpsPort )) {
    fix = gps.read();

  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Sat:");
  lcd.setCursor(5,0);
  lcd.print( fix.satellites );
  lcd.setCursor(0,1);
  lcd.print("Vitesse:");
  lcd.setCursor(9,1);
  lcd.print( fix.speed_kph() );
  Serial.print("<");
  Serial.print("?");
  Serial.print( fix.speed_kph() );
  Serial.print("?");
  Serial.print( fix.satellites );
  Serial.print("?");
  Serial.print( fix.latitude(), 6 );
  Serial.print("?");
  Serial.print( fix.longitude(), 6 );
  Serial.print("?");
  Serial.print(">");
  Serial.println();
}
}
