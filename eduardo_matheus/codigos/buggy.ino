#include "Motores.h"
#include "Ultrassom.h"
#include "Linha.h"  // Inclui a Biblioteca

//Variáveis Globais
char dado_recebido;
char buffer;
float aux;  // Variável usada para controle de velocidade
/* Tarefas básicas do exemplo */
void tarefa_1();  //movimetação pelo Celular
void tarefa_2();  //seguidor de linha
void tarefa_3();  //ler serial

/* Instâncias das classe dos sensores/atuadores */
Motores motores;
Linha seguidor_linha;
Ultrassom ultrassom_1(Ultrassom::ECHO1, Ultrassom::TRIG1);
/* Configuração e mensagem inicial */
void setup() {

  Serial.begin(9600);
  buffer = 0;
  aux = 0.0;
  while (!Serial)
    ;

  Serial.println("Teste buggy 4x4");
  Serial.println("Mande a velocidade");
  Serial.println("0: Velocidade igual a 0%");
  Serial.println("1: Velocidade igual a 10%");
  Serial.println("2: Velocidade igual a 20%");
  Serial.println("3: Velocidade igual a 30%");
  Serial.println("4: Velocidade igual a 40%");
  Serial.println("5: Velocidade igual a 50%");
  Serial.println("6: Velocidade igual a 60%");
  Serial.println("7: Velocidade igual a 70%");
  Serial.println("8: Velocidade igual a 80%");
  Serial.println("9: Velocidade igual a 90%");
  Serial.println("q: Velocidade igual a 100%");
  Serial.println("F: mover para frente");
  Serial.println("B: mover para tras");
  Serial.println("L: mover para esquerda");
  Serial.println("R: mover para direita");
  Serial.println("I: mover para Frente e Direita");
  Serial.println("G: mover para Frente e Esquerda");
  Serial.println("H: mover para Tras e Esquerda");
  Serial.println("J: mover para Tras e Direita");
  Serial.println("s: exibir estado dos sensores a cada 1s");
  Serial.println("i: exibir descrição das dos estados");

  delay(5000);
}

/* Loop de atualização do sensores e das tarefas */
void loop() {

  ultrassom_1.atualizar();
  tarefa_1();
  tarefa_2();
  tarefa_3();
}

void tarefa_1() {
  //Código para seleção de velocidade

  if (buffer == 1) {

    if (dado_recebido == '0') {
      aux = 0;
      buffer = 0;
    } else if (dado_recebido == '1') {
      aux = 0.1;
      buffer = 0;
    } else if (dado_recebido == '2') {
      aux = 0.2;
      buffer = 0;
    } else if (dado_recebido == '3') {
      aux = 0.3;
      buffer = 0;
    } else if (dado_recebido == '4') {
      aux = 0.4;
      buffer = 0;
    } else if (dado_recebido == '5') {
      aux = 0.5;
      buffer = 0;
    } else if (dado_recebido == '6') {
      aux = 0.6;
      buffer = 0;
    } else if (dado_recebido == '7') {
      aux = 0.7;
      buffer = 0;
    } else if (dado_recebido == '8') {
      aux = 0.8;
      buffer = 0;
    } else if (dado_recebido == '9') {
      aux = 0.9;
      buffer = 0;
    } else if (dado_recebido == 'q') {
      aux = 1.0;
      buffer = 0;
    }
    if (dado_recebido == 'S') {
      motores.parar();
      buffer = 0;
    }  //Código para seleção de direção
    else if (dado_recebido == 'F') {
      motores.frente(255 * aux);
      buffer = 0;
    } else if (dado_recebido == 'B') {
      motores.tras(255 * aux);
      buffer = 0;
    } else if (dado_recebido == 'L') {
      motores.esquerda(255 * aux);
      buffer = 0;
    } else if (dado_recebido == 'R') {
      motores.direita(255 * aux);
      buffer = 0;
    } else if (dado_recebido == 'I') {
      motores.fd(255 * aux);
      buffer = 0;
    } else if (dado_recebido == 'G') {
      motores.fe(255 * aux);
      buffer = 0;
    } else if (dado_recebido == 'H') {
      motores.te(255 * aux);
      buffer = 0;
    } else if (dado_recebido == 'J') {
      motores.td(255 * aux);
      buffer = 0;
    }
  }
}

void tarefa_2() {

  buffer = 0;

  if (dado_recebido == 'V') {
    Serial.println(ultrassom_1.obter_distancia());

    if (ultrassom_1.obter_distancia() > 400) {

      Serial.println("entrou no if");
      if (seguidor_linha.obter_esquerda() == 0 && seguidor_linha.obter_direita() == 0) {
        motores.frente(80);
        Serial.println("teste2");
      }

      else if (seguidor_linha.obter_esquerda() == 0 && seguidor_linha.obter_direita() == 1) {
        motores.direita(100);
        Serial.println("teste3");
      }

      else if (seguidor_linha.obter_direita() == 0 && seguidor_linha.obter_esquerda() == 1) {
        motores.esquerda(100);
        Serial.println("teste4");
      }

      else if (seguidor_linha.obter_direita() == 1 && seguidor_linha.obter_esquerda() == 1) {
        motores.parar();
        Serial.println("teste5");
        dado_recebido = 0;
      }
    } else if (ultrassom_1.obter_distancia() <= 400) {
      motores.parar();
     // dado_recebido = 0;
    }
  }
}

void tarefa_3() {

  if ((Serial.available()) && (buffer == 0)) {
    dado_recebido = Serial.read();
    while (Serial.read() != -1) {
      Serial.read();
    }

    // Serial.println(Serial.available());
    // Serial.println(dado_recebido);
    buffer = 1;
  }
}