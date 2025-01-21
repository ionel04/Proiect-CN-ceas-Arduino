#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 10
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal_I2C lcd(0x27, 16, 2);

int o = 0;
int m = 59;
int s = 0;
int oA = 0;
int mA = 0;
int buton2 = 2;
int buton3 = 3;
int buton4 = 4;
const int buzzer = 5;

void setup() {
  lcd.begin(16, 2);
  lcd.init();
  lcd.backlight();

  pinMode(buton2, INPUT);
  pinMode(buton3, INPUT);
  pinMode(buton4, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(buzzer, OUTPUT);

  Serial.begin(9600);
  dht.begin();

  Serial.println(F("DHTxx Unified Sensor Example"));
}

void loop() {
  int state_A = digitalRead(buton4);

  if (state_A == LOW) { 
    while (o == oA && m == mA && s == 0) {

      int state_M1 = digitalRead(buton2); 
      if (state_M1 == HIGH) {
      digitalWrite(LED_BUILTIN, HIGH);
      m = m + 1;
      s = 0;
      delay(1000);
      digitalWrite(LED_BUILTIN, LOW);
    }
      tone(buzzer, 1000); 
      delay(1000);
      noTone(buzzer); 
      
    }

    lcd.setCursor(0, 0);
    lcd.print("O:");
    if (o < 10) lcd.print("0");
    lcd.print(o);
    lcd.print(":");
    if (m < 10) lcd.print("0");
    lcd.print(m);
    lcd.print(":");
    if (s < 10) lcd.print("0");
    lcd.print(s);

    lcd.setCursor(0, 1);

    int h = dht.readHumidity();
    int t = dht.readTemperature();

    lcd.print("T:");
    lcd.print(t);
    lcd.print("C' ");

    lcd.print("H:");
    lcd.print(h);
    lcd.print("%");

    delay(1000);
    s = s + 1;
    if (s == 60) {
      m = m + 1;
      s = 0;
    }

    if (m == 60) {
      o = o + 1;
      m = 0;
    }

    if (o == 24) {
      o = 0;
    }

    int state_O = digitalRead(buton3);
    int state_M = digitalRead(buton2);

    if (state_O == HIGH) {
      digitalWrite(LED_BUILTIN, HIGH);
      o = o + 1;
      delay(1000);
      digitalWrite(LED_BUILTIN, LOW);
    }

    if (state_M == HIGH) {
      digitalWrite(LED_BUILTIN, HIGH);
      m = m + 1;
      s = 0;
      delay(1000);
      digitalWrite(LED_BUILTIN, LOW);
    }
  } 
  else 
  {
    lcd.setCursor(0, 0);
    lcd.print("A:");
    if (oA < 10) lcd.print("0");
    lcd.print(oA);
    lcd.print(":");
    if (mA < 10) lcd.print("0");
    lcd.print(mA);
    lcd.print(":00");

    int state_O = digitalRead(buton3);
    int state_M = digitalRead(buton2);

    if (state_O == HIGH) {
      digitalWrite(LED_BUILTIN, HIGH);
      oA = oA + 1;
      delay(1000);
      digitalWrite(LED_BUILTIN, LOW);
    }

    if (state_M == HIGH) {
      digitalWrite(LED_BUILTIN, HIGH);
      mA = mA + 1;
      delay(1000);
      digitalWrite(LED_BUILTIN, LOW);
    }
  }
}


