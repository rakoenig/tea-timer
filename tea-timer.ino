char version[ ] ="V2 (2021-02-25)";

#include <Arduino.h>

#include <Servo.h>
Servo myservo;

// Ein paar Variablen für die Hardware
const int pot1 = A0;
int pot1_wert = 0;
const int taster=12;
int tasterstatus=0;
const int LEDgruen=11;
const int LEDrot=10;
const int Buzzer=9;

// Ein paar Winkeleinstellungen für den Arm
const int Beuteloben=92; 
const int Beutelunten=35;
const int Beutelmitte=80;

// Variablen für die Zeitmessung
unsigned long startMillis = 0;
unsigned long endMillis = 0;
unsigned long zeit;

// Status fürs Programm
int programmstatus=0;
int armstellung = 0;

void setup() {
  pinMode(taster, INPUT);
  pinMode(LEDgruen, OUTPUT);
  digitalWrite(LEDgruen, HIGH);
  pinMode(LEDrot, OUTPUT);
  digitalWrite(LEDrot, LOW);
  pinMode(Buzzer, OUTPUT);
  digitalWrite(Buzzer,LOW);
  Serial.begin(9600);
  myservo.attach(3);
  Serial.println(version);
  Serial.println("Start - Warte auf Taster");
  armstellung=Beuteloben;
  myservo.write(armstellung);
}

void endbeep(){
  int i;
  for (i=0;i<3;i++) {
    digitalWrite(Buzzer, HIGH);
    delay(500);
    digitalWrite(Buzzer, LOW);
    delay(500);
  }
}

void servobewegung(int zielwinkel){
  int diff;
  int schritt = 1;
  int warten=25;
  diff = zielwinkel - armstellung;
  if (diff < 0)
  {
    schritt = -1;
    warten=50;
  }
  while (armstellung != zielwinkel)
  {
    armstellung = armstellung + schritt;
    myservo.write(armstellung);
    delay(warten);
  }
}

// taucht den Beutel 5 mal raus und rein,
void aufab(){
  int i;
  for (i=0;i<5;i++){
    servobewegung(Beutelmitte);
    delay(500);
    servobewegung(Beutelunten);
    delay(500);  
  }
}

void loop() {
  pot1_wert = analogRead(pot1);
  pot1_wert = map(pot1_wert, 0 ,1023, 0, 100);
  // Abhängig vom Programmstatus die LED schalten, grün ist fertig, rot=läuft. 
  if (programmstatus == 0)
  {
    digitalWrite(LEDgruen, HIGH);
    digitalWrite(LEDrot, LOW);
  }
  else
  {
    digitalWrite(LEDgruen, LOW);
    digitalWrite(LEDrot, HIGH);
  }

  if (programmstatus == 3) // warten dass die Zeit abläuft
  {
    Serial.print("P1 = ");
    Serial.println(pot1_wert);
    endMillis = startMillis + (unsigned long) 6000*pot1_wert; 
//    Serial.println(startMillis);
    zeit = millis();
//    Serial.println(zeit);
//    Serial.println(endMillis);
    if (zeit > endMillis) // Programm fertig;
    {
      programmstatus=0;
      servobewegung(Beuteloben);
      endbeep();
    }
  }
  
  if (programmstatus == 2) // aufab machen
  {
    programmstatus=3; 
    Serial.println("Teebeutel auf- und ab bewegen");
    aufab();
    startMillis = millis(); // Startzeit ermitteln
  }
  if (programmstatus == 1) // Start, Beutel eintauchen und 5 Sekunden warten)
  {
    Serial.println("Teebeutel 5 Sec eintauchen");
    programmstatus = 2;
    servobewegung(Beutelunten);
    delay(5000);
  }
  
  tasterstatus=digitalRead(taster);
  if (tasterstatus == HIGH)
  { if (programmstatus == 0)
  {
     programmstatus=1; // start das Programm
     Serial.println("Taster gedrückt");
  } 
  } 
  delay(100);
}
