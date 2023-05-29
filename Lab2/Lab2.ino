#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {10, 9, 8, 7}; 
byte colPins[COLS] = {6, 5, 4, 3};

Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

const int Trigger = 12;
const int Echo = 13;
const int LED = 2;

const String pass = "AB12#";
String password = "";
bool close;

const char reset = '*';

void setup() {
  Serial.begin(9600);
  pinMode(Trigger, OUTPUT);
  pinMode(Echo, INPUT); 
  digitalWrite(Trigger, LOW);
}

void loop() {
  long time;
  long dist;
  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trigger, LOW);
  
  time = pulseIn(Echo, HIGH); 
  dist = time/59;
  if (dist > 50) close = false;
  else close = true;

  char customKey = customKeypad.getKey();

  if (customKey && close) {
    if (customKey==reset) {
      password="";
      digitalWrite(LED, LOW);
    } else {
      password += customKey;
      Serial.println(password);
      if (password == pass) {
        digitalWrite(LED, HIGH);
      }
    }
  }

  if (!close) {
    digitalWrite(LED, LOW);
    password = "";
  }
  delay(100);        
}