#include <LiquidCrystal.h>
#include <DHT.h>

// LCD PINS
#define LCD_RS 2
#define LCD_EN 3
#define LCD_D4 4
#define LCD_D5 5
#define LCD_D6 6
#define LCD_D7 7

LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

// SENSOR PINS
#define SMOKE_PIN 8
#define ACTIVITY_PIN 9
#define WATER_PIN 10
#define BUZZER_PIN 11

// DHT SENSOR
#define DHTPIN 12
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// VARIABLES
int RH = 0;
int TEMP = 0;

int smokeState = 0;
int activityState = 0;
int envState = 0;


// -------- FUNCTIONS --------

void SMK() {
  Serial.println("+254796264192");
  Serial.println("smoke detected");
  delay(2000);
}

void SND() {
  Serial.println("+254796264192");
  Serial.println("no activity detected");
  delay(2000);
}

void ENQ() {

  Serial.println("+254796264192");
  Serial.println("Adverse conditions");

  Serial.print("Humidity: ");
  Serial.println(RH);

  Serial.print("Temperature: ");
  Serial.println(TEMP);

  delay(1000);
}


// -------- SETUP --------

void setup() {

  Serial.begin(9600);

  pinMode(SMOKE_PIN, INPUT);
  pinMode(ACTIVITY_PIN, INPUT);
  pinMode(WATER_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  lcd.begin(16,2);

  lcd.setCursor(0,0);
  lcd.print("BEE FARMING");

  lcd.setCursor(0,1);
  lcd.print("REAL TIME MON");

  delay(3000);
  lcd.clear();

  dht.begin();
}


// -------- LOOP --------

void loop() {

  RH = dht.readHumidity();
  TEMP = dht.readTemperature();

  lcd.setCursor(0,1);
  lcd.print("H:");
  lcd.print(RH);

  lcd.setCursor(8,1);
  lcd.print("T:");
  lcd.print(TEMP);

  // HUMIDITY CONDITION
  if(RH < 50) {

    if(envState == 0) {
      envState = 1;
      ENQ();
    }

  }

  // TEMPERATURE CONDITION
  if(TEMP > 34) {

    if(envState == 0) {
      envState = 1;
      ENQ();
    }

  }

  // WATER SENSOR
  if(digitalRead(WATER_PIN) == HIGH) {

    lcd.setCursor(0,0);
    lcd.print("WT");

    digitalWrite(BUZZER_PIN, HIGH);

  }
  else {

    lcd.setCursor(0,0);
    lcd.print("  ");

    digitalWrite(BUZZER_PIN, LOW);

  }

  // SMOKE SENSOR
  if(digitalRead(SMOKE_PIN) == HIGH) {

    lcd.setCursor(4,0);
    lcd.print("SM");

    if(smokeState == 0) {

      smokeState = 1;
      SMK();

    }

  }
  else {

    lcd.setCursor(4,0);
    lcd.print("  ");
    smokeState = 0;

  }

  // ACTIVITY SENSOR
  if(digitalRead(ACTIVITY_PIN) == LOW) {

    lcd.setCursor(7,0);
    lcd.print("   ");

    if(activityState == 0) {

      activityState = 1;
      SND();

    }

  }
  else {

    lcd.setCursor(7,0);
    lcd.print("SND");
    activityState = 0;

  }

  delay(1000);

}
