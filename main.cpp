#include <LiquidCrystal.h>


const int trigPin = 9;
const int echoPin = 10;
const int dcPin = 11;
const float totalHeight = 103; // total height of bottle in cm

const int rsPin = 13;
const int enablePin = 6;
const int d4 = 5;
const int d5 = 4;
const int d6 = 3;
const int d7 = 2;

LiquidCrystal my_lcd(rsPin, enablePin, d4, d5, d6, d7);

float duration, distance, nivel_atual;
float margem = 3.00; // margem do erro do sensor em cm

int motorLigado = 0;

void setup() {
    // setando pinos

    pinMode(echoPin, INPUT);
    pinMode(trigPin, OUTPUT);
    pinMode(dcPin, INPUT);

    my_lcd.begin(16, 2);

    meu_lcd.print("Status: ");

    Serial.begin(9600);
}

void loop() {
    // distance = (duracao*velocidade) / 2
    //essa é a distancia do sensor ao obstáculo

    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH);
    distance = (duration * 0.0343) / 2;

    distance -= margem;

    if (distance < 0) {
        distance = 0;
    }

    nivel_atual = (1 - distance/totalHeight) * 100;

    if (nivel_atual < 0) {
        nivel_atual = 0;
    }

    // configuracao do motor

    if (motorLigado) {
        if (nivel_atual >= 60 && nivel_atual < 75) {
            analogWrite(dcPin, 64);
        }
        else if (nivel_atual >= 75) {
            analogWrite(dcPin, 10);
        }
        if (nivel_atual >= 90) {
            analogWrite(dcPin, 0);
            motorLigado = 0;
        }
    }
    else {
        if (nivel_atual <= 10) {
            analogWrite(dcPin, 102);
            motorLigado = 1;
        }
    }

    // config do LCD
    int nivel_formatado = (int)nivel_atual;
    meu_lcd.setCursor(0, 1);
    meu_lcd.print(nivel_formatado);
    meu_lcd.print("% cheio");

    Serial.print("Volume: ");
    Serial.print(nivel_formatado);
    Serial.println("% cheio");

    delay(1000);
}




