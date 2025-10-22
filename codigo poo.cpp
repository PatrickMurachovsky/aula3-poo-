#include <Arduino.h>

class Led {
  int pin;
public:
  Led(int p) : pin(p) {}
  void begin() { pinMode(pin, OUTPUT); off(); }
  void on()  { digitalWrite(pin, HIGH); }
  void off() { digitalWrite(pin, LOW); }
};

class Semaforo {
  Led &vermelho;
  Led &amarelo;
  Led &verde;
public:
  Semaforo(Led &v, Led &a, Led &g) : vermelho(v), amarelo(a), verde(g) {}
  void begin() { vermelho.begin(); amarelo.begin(); verde.begin(); apagarTudo(); }
  void apagarTudo() { vermelho.off(); amarelo.off(); verde.off(); }
  void ligarVerde()   { apagarTudo(); verde.on(); }
  void ligarAmarelo() { apagarTudo(); amarelo.on(); }
  void ligarVermelho(){ apagarTudo(); vermelho.on(); }
};

Led ledVerm(8);
Led ledAmar(7);
Led ledVerd(6);
Semaforo sem(ledVerm, ledAmar, ledVerd);

void setup() {
  Serial.begin(9600);
  Serial.println("Digite V (verde), A (amarela) ou R (vermelha).");
  sem.begin();
}

void loop() {
  if (Serial.available()) {
    String comando = Serial.readStringUntil('\n');
    comando.trim();
    if (comando.equalsIgnoreCase("V")) sem.ligarVerde();
    else if (comando.equalsIgnoreCase("A")) sem.ligarAmarelo();
    else if (comando.equalsIgnoreCase("R")) sem.ligarVermelho();
    else Serial.println("Comando inválido. Use V, A ou R.");
  }
}
