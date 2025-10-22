class Led {
  int pin;
public:
  Led(int p) : pin(p) {}

  void begin() {
    pinMode(pin, OUTPUT);
    off();
  }
  void on()  { digitalWrite(pin, HIGH); }
  void off() { digitalWrite(pin, LOW);  }
  void blink(unsigned long tempo = 200) {
    on();
    delay(tempo);
    off();
    delay(tempo);
  }
};
class Semaforo {
  Led &vermelho;
  Led &amarelo;
  Led &verde;
  bool aberto = false; 
public:
  Semaforo(Led &v, Led &a, Led &g)
    : vermelho(v), amarelo(a), verde(g) {}

  void begin() {
    vermelho.begin();
    amarelo.begin();
    verde.begin();
    mostrarEstado();
  }
  void executar() {
  }

  void abrir() {
    if (!aberto) {
      amarelo.blink(100);
      aberto = true;
      mostrarEstado();
      Serial.println("Semáforo ABERTO (verde).");
    }
  }

  void fechar() {
    if (aberto) {
      amarelo.blink(100);
      aberto = false;
      mostrarEstado();
      Serial.println("Semáforo FECHADO (vermelho).");
    }
  }
private:
  void mostrarEstado() {
    vermelho.off();
    amarelo.off();
    verde.off();

    if (aberto) verde.on();
    else        vermelho.on();
  }
};

Led ledVerm(8);
Led ledAmar(7);
Led ledVerd(6);
Semaforo sem(ledVerm, ledAmar, ledVerd);
void setup() {
  Serial.begin(9600);
  Serial.println("Digite F para fechar e A para abrir.");

  sem.begin();
}
void loop() {
  sem.executar();
  if (Serial.available()) {
    String comando = Serial.readStringUntil('\n'); 
    comando.trim(); 

    Serial.print("Comando recebido: ");
    Serial.println(comando);

    if (comando == "F" || comando == "f") {
      sem.fechar();
    }
    else if (comando == "A" || comando == "a") {
      sem.abrir();
    }
  }
}
