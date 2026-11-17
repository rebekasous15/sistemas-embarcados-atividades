const int vermelho = 8;
const int verde = 9;
const int amarelo = 10;
const int botao = 2;

enum Estado {
  VERMELHO,
  VERDE,
  AMARELO
};

Estado estadoAtual = VERMELHO;

int leituraBotao = HIGH;
int ultimoEstadoBotao = HIGH;

unsigned long tempoDebounce = 0;
const unsigned long debounce = 50;

void setup() {
  pinMode(vermelho, OUTPUT);
  pinMode(verde, OUTPUT);
  pinMode(amarelo, OUTPUT);

  pinMode(botao, INPUT_PULLUP);

  Serial.begin(9600);

  atualizarSemaforo();
}

void loop() {
  int leitura = digitalRead(botao);

  if (leitura != ultimoEstadoBotao) {
    tempoDebounce = millis();
  }

  if (millis() - tempoDebounce > debounce) {

    if (leitura != leituraBotao) {
      leituraBotao = leitura;

      if (leituraBotao == LOW) {
        avancarEstado();
      }
    }
  }

  ultimoEstadoBotao = leitura;
}

void avancarEstado() {

  if (estadoAtual == VERMELHO) {
    estadoAtual = VERDE;
  }
  else if (estadoAtual == VERDE) {
    estadoAtual = AMARELO;
  }
  else if (estadoAtual == AMARELO) {
    estadoAtual = VERMELHO;
  }

  atualizarSemaforo();
}

void atualizarSemaforo() {

  digitalWrite(vermelho, LOW);
  digitalWrite(verde, LOW);
  digitalWrite(amarelo, LOW);

  switch (estadoAtual) {

    case VERMELHO:
      digitalWrite(vermelho, HIGH);
      Serial.println("Estado atual: VERMELHO");
      break;

    case VERDE:
      digitalWrite(verde, HIGH);
      Serial.println("Estado atual: VERDE");
      break;

    case AMARELO:
      digitalWrite(amarelo, HIGH);
      Serial.println("Estado atual: AMARELO");
      break;
  }
}
