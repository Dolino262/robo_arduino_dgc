/*MODIFICAÇÕES:
  Páginas Adicionadas:
  -"VarrerLinha" (onde se encontra a função varrer linha)
  -"Posição_PA_e_CANCELADomingos", onde se encontra as funções que determinam a posição da pá e da cancela.
  Atualização da página: "SPINA_SENSORSENIRIO" retirou-se a função: "DescobreIntervalo" e foi adicionada as funções: "DescobreIntervaloE" e "DescobreIntervaloD"
*/
/******* DEFINIÇÕES GERAIS *******/


//  ESTA VERSÃO ESTÁ PREPARADA PARA O SEGUIDOR CONJUNTO COM 3 SENSORES AGRUPADOS EM UMA SÓ PLACA ONDE SE LÊ 5V PARA BRANCO E 0 VOLTS PARA PRETO.
// BIBLIOTECAS
#include <Math.h>
#include <LiquidCrystal.h> //Inclui biblioteca do LCD
#include <Wire.h>
#include <MPU6050_tockn.h>   //GIROSCÓPIO
#include <Servo.h>
// LCD DESAFIO
#define NCol 16
#define NLin 2

// BOTÕES PARA CALIBRAGEM DO SENSOR DE COR
#define seguranca 4 // Constante que dita quantas vezes deve ser apertado o botão para que a função seja executada.

// SENSORES SEGUE LINHA   // fios preto = sinal; marrom = VCC ; azul = GND   ( E18 - D80 NK - SENSOR DE PROXIMIDADE )
#define pinSensorEsq 33
#define pinSensorCentral 45
#define pinSensorDir 34

// ENCODER RODA E DEFINIÇÕES
#define encoderEsq 2  // interrupt 0
#define encoderDir 3  // interrupt 1
#define dCarro 24   // cm  diametro da volta do carro sobre seu eixo  // ATENCAO ==> A SER MUDADO
#define dpVoltaCarro 75.36 // cm  distancia percorrida por volta sobre o eixo do carro | 2 * pi * raio do centro do carro ao meio da roda
#define dRoda 6.5  // cm     diametro da roda      
#define ppVolta 238         // pulsos por volta     // ATENCAO ==>  PODE SER MUDADO
#define dpVolta  20.41    // cm  .. distancia percorrida por volta// interrupt 1     // ATENCAO ==> PODE  SER MUDADO
#define qtPulsosPrevista  238  // quantidade de pulsos que se espera sejam dados em um décimo de segundo na velocidade velTur. Usada para verificar se o carro está parado num redutor
// se emitiu menos que esse nr de passos, é porque ou está parado no redutor ou está patinando no redutor. De qq maneira tem que ser acertado.

// SENSOR INDUTIVO
#define sensorIndutivo 50

// SENSOR ULTRASOM
// FRENTE
#define trigFrente 26
#define echoFrente 28
// ESQUERDA
#define trigEsq 35
#define echoEsq 36

// TRAS
#define trigTras 52
#define echoTras 53

//Constantes auxiliares do SENSOR ULTRASSÔNICO
#define TAndar 100 //tempo em que o Robô estará andando 
#define difMAX 0.25 //caso a distAtual e a distAntiga se diferenciem mais do que isso, então o robô ainda está andando
#define distRePa 20 //distância de ré necessária para conseguir levantar a pá sem problemas MUDAR VALOR

// DEFINIÇÃO DE VALORES AUXILIARES     // ATENCAO ==> A SEREM MUDADOS
#define distParada 13  // ditancia mínima antes do obstáculo
#define distSeguranca 5 // eh o que pode variar a distancia Esperada enquanto avancaDesvio
#define distEsperada (distParada + distSeguranca + 5)  // esperando que ao fazer direita volver, a distancia aumente em "distSeguranca"  + 5 cm  os 5 cm devem ser conferidos no direita volver.
#define distLateral 10  // espera-se passar a 10 cm pelo lado direito do obstaculo
#define distFolga 5    // eh o tanto que se avança apos ultrapassar o obstaculo, para folga na hora de voltar à linha. (direita volver final)

// SERVOS MOTORES

#define Servo01 12   // fio laranja => ServoPa
#define Servo02 13  // fio laranja => ServoCancela    NOS três SERVOS, O FIO MARROM VAI PARA O GND E O FIO VERMELHO NO VCC
//#define Servo03 14  // fio laranja => ServoPa1 NÂO SERÁ USADO

#define tempo90_60 2000 // tempo que leva para o robô posicionar sua garra     --teste
#define tempo180_60 20   00 // tempo de descida (mais devagar(defeito do servo motor))   --teste
#define CancelaFechada 45
#define CancelaAberta 145

// SENSOR DE COR
// ESQUERDO       //AQUI HAVERÁ GRANDE MUDANÇA POIS USAREMOS O SENSOR DESENVOLVIDO POR NÓS.
#define S_Cor_E_Red 23  // fio vermelho
#define S_Cor_E_Green 25  // fio verde
#define S_Cor_E_Blue 27    //fio Azul   
#define S_Cor_E_Le A15  //    leitura analógica branco     temos que ligar o cinza no GND e violeta no VCC

// DIREITO
#define S_Cor_D_Red 49   // Vermelho
#define S_Cor_D_Green 50  // Verde
#define S_Cor_D_Blue 51   // Azul
#define S_Cor_D_Le  A14   // leitura analógica     branco    temos que ligar o cinza no GND e violeta no VCC

// DEFINIÇÃO DOS VALORES AUXILIARES     // VERIFICAR SE DEVEMOS MUDAR PARA EEPROM
//Vetores que determinam os intervalos de determinada cor
int Prata_E[2], Verde_E[2], Branco_E[2], Prata_D[2], Verde_D[2], Branco_D[2]; // o número na posição 0 é o valor mínimo do intervalo e o da posição 1 é o valor máximo
#define RLegal 255//82//163
#define GLegal 255//84//168
#define BLegal 255//80//160
#define PrecisaoIntervalo 5 // quanto maior o número, maior será  a precisão do intervalo -> TEMPO EM SEGUNDOS DA CALIBRAGEM EM FUNÇÃO DESSA CONSTANTE: T(x)= 38 + (1,5)x
#define Min 0
#define Max 1
#define TempoEspera 5000
#define dMin 20   // ???????????????????????????????????????????????????????????????

// MOTOR
// DIREITA
#define pinMotorDireitaFrente 11
#define pinMotorDireitaTras 10
// ESQUERDA
#define pinMotorEsquerdaFrente 6
#define pinMotorEsquerdaTras 5

#define S_Cor_E_EFINIÇÕES DOS VALORES AUXILIARES //?????????????????????????????????????

#define velTur 55
#define velGiro 95
#define velAjuste 80
#define velTurbo 200
#define distFugaRedutor 12

// GIROSCOPIO
#define RampaMinima 10 //valor mínimo que se espera para a rampa

// FIM DE CURSO SENSOR
#define FimCursoc 15 //fim de curso de cima     -teste
#define FimCursob 14 //fim de curso de baixo   --teste
//*******************************************************************************************************************************************************************

// VARIAVEIS
MPU6050 MedeAnguloVertical(Wire);
LiquidCrystal MENSAGEIRO(41, 42, 46, 47, 48, 40); // (RS,EN,D4,D5,D6,D7)  O RW DEVE SER COLOCADO EM GND.
Servo ServoPa;  // criando um objeto servo motor para ACIONAR A PA
Servo ServoCancela;//CRIANDO UM OBJETO SERVO MOTOR PARA ACIONAR A CANCELA
Servo ServoPa1; // criando segundo objeto servo motor para ACIONAR A PA
int habCalibra = 1; // Variável de estado que se associa com o estado do robo: estar em função de calibrar ou em função de realizar a prova.
//Quando esta variável vale 1, significa que o robô está esperando para calibrar. Caso contrário, a variável vale 0 e o carro está em caminho
int calibrando = 0;
float largObstaculo;
int cont = 0;
float Dist;
int contaPulso;
int emBaixo = 1;  // em Baixo passa a ser zero (0), quando estiver na rampa E PERMANECE ASSIM em cima.
int emCima = 0;   // quando subir totalmente, emCima passa a ser 1
float YBase;
int contaPulsoD = 0,contaPulsoE = 0;//--------------------------ALTERAÇÃO
//********************************************************CÓDIGO DO SETUP  *****************************************************************************************************************
//***************************************************************************************************************************************************************************************
void incremPulso() {
  contaPulso++;
}
//*****************************************************************************************************************************************************
void MudaEstRobo() { //Função que muda o estado do robo.
  static int cont = 1;
  delay(500);
  if ((cont % seguranca) == 0) {
    habCalibra = !habCalibra;
    if (habCalibra)Serial.println("HABILITADA");
    else Serial.println("DESABILITADA");
    cont = 0;
  }
  cont++;
}
//************************************************************************************************************************************************************************************
void CalibraSensor() { //Inicia o processo de calibragem
  static int cont1 = 1;
  delay(300);
  if (habCalibra) {
    if ((cont1 % seguranca) == 0) {
      Serial.println("CALIBRANDOOOOOOO");
      calibrando = 1;
      // chamar ou colocar aqui o programa de calibragem.
    }
    cont1++;
  }
}
void incremPulsoD() {//-------------------ALTERAÇÃO
  contaPulsoD++;
}
void incremPulsoE() {//-------------------ALTERAÇÃO
  contaPulsoE++;
}
//**************************************SETUP*************************************SETUP*******************************************SETUP ***************************************************
void setup() {
  Serial.begin(9600);
  // INICIALIZANDO TUDO QUE PRECISA PARA O GIROSCÓPIO
  Wire.begin();
  MedeAnguloVertical.begin();
  MedeAnguloVertical.calcGyroOffsets(true);
  MedeAnguloVertical.update();
  YBase = MedeAnguloVertical.getAngleY();

  // DETALHES DO  DISPLAY
  MENSAGEIRO.begin(NCol, NLin);
  MENSAGEIRO.setCursor(0, 0);
  MENSAGEIRO.print("  EQUIPO UAISÔ  ");
  MENSAGEIRO.setCursor(0, 1);
  MENSAGEIRO.print(" ABRAZA A TODAS ");

  // SENSOR SEGUE LINHA
  pinMode(pinSensorDir, INPUT);
  pinMode(pinSensorEsq, INPUT);
  pinMode(pinSensorCentral, INPUT);

  // ULTRASOM
  // FRENTE
  pinMode(trigFrente, OUTPUT);
  pinMode(echoFrente, INPUT);
  // ESQUERDO
  pinMode(trigEsq, OUTPUT);
  pinMode(echoEsq, INPUT);

  // TRASEIRO
  pinMode(trigTras, OUTPUT);
  pinMode(echoTras, INPUT);

  // ENCODER
  attachInterrupt(0, incremPulso, FALLING); // PARA CONTAR OS PULSOS DO ENCODER ; interrupt zero - 0
  attachInterrupt(1, incremPulsoE, FALLING); // PARA CONTAR OS PULSOS DO ENCODER ; interrupt zero - 1---------------ALTERAÇÃO

  // SENSOR INDUTIVO DE IDENTIFICAÇAO DE NAVE RESGATAVEL
  //  pinMode(sensorIndutivo,INPUT);

  // SENSOR DE COR
  // ESQUERDO
  pinMode(S_Cor_E_Red, OUTPUT);
  pinMode(S_Cor_E_Green, OUTPUT);
  pinMode(S_Cor_E_Blue, OUTPUT);
  // DIREITO
  pinMode(S_Cor_D_Red, OUTPUT);
  pinMode(S_Cor_D_Green, OUTPUT);
  pinMode(S_Cor_D_Blue, OUTPUT);
  //LIMPANDO DADOS DOS VETORES-INTERVALOS
  Prata_E[Min] = 1023, Verde_E[Min] = 1023, Branco_E[Min] = 1023;
  Prata_E[Max] = 0, Verde_E[Max] = 0, Branco_E[Max] = 0;
  Prata_D[Min] = 1023, Verde_D[Min] = 1023, Branco_D[Min] = 1023;
  Prata_D[Max] = 0, Verde_D[Max] = 0, Branco_D[Max] = 0;

  // BOTÕES PARA CALIBRAGEM DO LEITOR DE COR
  attachInterrupt(5, MudaEstRobo, FALLING); // PINO 18
  attachInterrupt(4, CalibraSensor, FALLING); // PINO 19
  Serial.begin(9600);

  //**********************************************************************************************************************************************************************************
  //  INICIALIZAÇÕES DOS SERVOS MOTORES:
  ServoPa.attach(Servo01);           // Associando cada servo a seu pino de acionamento
  ServoCancela.attach(Servo02);
  //ServoPa1.attach(Servo03);
  // FIM DE CURSO SENSOR
  pinMode(FimCursoc, INPUT);
  pinMode(FimCursob, INPUT);
  

}  // final do SETUP
   //***************************************************************************************************************************************************************************************
 //CONTA PARA A CORREÇÃO DO MOTOR DIREITO E ESQUERDO
 int correcao(int veloc){
int correcao;
correcao = veloc - 77*veloc/100;
return(correcao);}
//***********************************************************  CODIGO PRINCIPAL DO LOOP  ***************************************************************************************************
void loop() {
  int contaPulsoA, contaPulsoN;  //variaveis para verificar se, apesar de mandar andar, está preso no redutor ou outro lugar.

  if (habCalibra) {
    if (calibrando) {
      Serial.println("ativando a funcao de calibragem");
      delay(1000);
      Serial.println("FIQUE ATENTO");
      delay(1000);
      Serial.println("VOCEh TERAh 10 SEGUNDOS PARA EXECUTAR CADA ORDEM:");
      delay(3000);

      Serial.println("COLOQUE O SENSOR ESQUERDO E DIREITO NO VERDE "); // SENSOR ESQUERDO EH AQUELE QUE USA O PINO A15 E SENSOR DIREITO EH AQUELE QUE USA O PINO A14
      delay(TempoEspera);
      Serial.println("DEIXE OS SENSORES QUIETOS POR:");
      Serial.print((PrecisaoIntervalo * 0.8));
      Serial.print("SEGUNDOS");
      DescobreIntervaloE(Verde_E);//descobriu o intervalo verde esquerdo
      DescobreIntervaloD(Verde_D);//descobriu o intervalo verde direito
      Serial.println("INTERVALO DO VERDE PARA O LADO ESQUERDO -> VAL MIN:");
      Serial.print(Verde_E[Min]);
      Serial.print(" VAL MAX:");
      Serial.print(Verde_E[Max]);
      Serial.println("INTERVALO DO VERDE PARA O LADO DIREITO -> VAL MIN:");
      Serial.print(Verde_D[Min]);
      Serial.print(" VAL MAX:");
      Serial.print(Verde_D[Max]);
      delay(1000);

      Serial.println("COLOQUE O SENSOR ESQUERDO E DIREITO NO BRANCO");
      delay(TempoEspera);
      Serial.println("DEIXE O SENSOR QUIETO POR:");
      Serial.print((PrecisaoIntervalo * 0.8));
      Serial.print("SEGUNDOS");
      DescobreIntervaloE(Branco_E);//descobriu o intervalo branco esquerdo
      DescobreIntervaloD(Branco_D);//descobriu o intervalo branco direito
      Serial.println("INTERVALO DO BRANCO PARA O LADO ESQUERDO -> VAL MIN:");
      Serial.print(Branco_E[Min]);
      Serial.print(" VAL MAX:");
      Serial.print(Branco_E[Max]);
      Serial.println("INTERVALO DO BRANCO PARA O LADO DIREITO -> VAL MIN:");
      Serial.print(Branco_D[Min]);
      Serial.print(" VAL MAX:");
      Serial.print(Branco_D[Max]);
      delay(1000);

      Serial.println("COLOQUE O SENSOR ESQUERDO E DIREIRTO NO PRATA");
      delay(TempoEspera);
      Serial.println("DEIXE O SENSOR QUIETO POR:");
      Serial.print((PrecisaoIntervalo * 0.8));
      Serial.print("SEGUNDOS");
      DescobreIntervaloE(Prata_E);//descobriu o intervalo prata esquerdo
      DescobreIntervaloD(Prata_D);//descobriu o intervalo prata direito
      Serial.println("INTERVALO DO PRATA PARA O LADO ESQUERDO -> VAL MIN:");
      Serial.print(Prata_E[Min]);
      Serial.print(" VAL MAX:");
      Serial.print(Prata_E[Max]);
      Serial.println("INTERVALO DO PRATA PARA O LADO DIREITO -> VAL MIN:");
      Serial.print(Prata_D[Min]);
      Serial.print(" VAL MAX:");
      Serial.print(Prata_D[Max]);
      delay(1000);
      Serial.println("FEITA A CALIBRAGEM");
      calibrando = 0;
    }
    else Serial.println("ESTADO DE ESPERA PARA MANDAR CALIBRAR OU SEGUIR VIDA NORMAL");
  }
  else { // INICIO DO TRABALHO DO ROBO.
    areaResgate();
    
  }
}
  /*  if (emBaixo) { // AINDA NÃO ENTREI NA RAMPA
      if ((!digitalRead(pinSensorEsq)) && (!digitalRead(pinSensorDir)))
      { //SOMENTE O SENSOR CENTRAL ESTÁ SEGUINDO LINHA OU  ESTÁ EM GAP
        if (temObstaculoPerto()) {
          Parar();
          delay(100);
          direitaVolver();
          delay(200);
          alinharPelaTesta();
          delay(300);
          avancarDesvio();
          delay(300);
          esquerdaVolver();
          delay(300);
          Ultrapassar();    // dentro de ultrapassar jah anda um pouco mais após ultrapassar para não correr risco de bater no obstaculo ao fazer direitaVolver para voltar à linha.
          delay(300);
          esquerdaVolver();
          delay(300);
          recuarDesvio();  // dentro do recuarDesvio jah faço o ajustarFrente de deixa de ser necessário.
          delay(300);
          direitaVolver();
          delay(300);
          Frente(velTur);
        }
        if (estouNaRampa())
          emBaixo = 0;   //****************************  PASSEI PARA A RAMPA.  ********************************
        Frente(velTur);

        /*   if(estaParadoNoRedutor())
             tentarSairDoRedutor();     
      }
      if (digitalRead(pinSensorEsq) && !digitalRead(pinSensorCentral) && !digitalRead(pinSensorDir)) // desviado para a direita
      {
        corrigeEsqRap(velGiro);
      }
      if (!digitalRead(pinSensorEsq) && !digitalRead(pinSensorCentral) && digitalRead(pinSensorDir))   // desviado para a esquerda
      {
        corrigeDirRap(velGiro);
      }

      //TRATANDO TODOS OS CASOS DE CRUZAMENTO SEM OTIMIZAÇÃO  ....  SE NECESSÁRIO E POSSIVEL, VAMOS OTIMIZAR
      if (digitalRead(pinSensorEsq) && digitalRead(pinSensorCentral) && !digitalRead(pinSensorDir)) { // Cruzamento Frente ou Esquerda
        Parar();
        if (esqTemVerde())  esquerdaVolver();
        Frente(velTur);
      }
      if (!digitalRead(pinSensorEsq) && digitalRead(pinSensorCentral) && digitalRead(pinSensorDir)) { // Cruzamento Frente ou Direita
        Parar();
        if (dirTemVerde())  direitaVolver();
        Frente(velTur);
      }
      if (digitalRead(pinSensorEsq) && !digitalRead(pinSensorCentral) && digitalRead(pinSensorDir)) { // Cruzamento Esquerda, direita ou Retorno
        Parar();
        if (esqTemVerde()) {
          if (dirTemVerde()) meiaVoltaVolver();
          else esquerdaVolver();
          Frente(velTur);
        }
        else {
          if (dirTemVerde()) {
            direitaVolver();
            Frente(velTur);
          }
        }
        //FICA PARADO NO CRUZAMENTO POR ERRO DA ARBITRAGEM, POIS INCORREU NUM CASO IMPOSSÍVEL
        // NESSE CASO, VALE MANDAR UMA MENSAGEM PARA O DISPLAY.....  TRAJETO IMPOSSÍVEL.
      }

      if (digitalRead(pinSensorEsq) && digitalRead(pinSensorCentral) && digitalRead(pinSensorDir)) { // Cruzamento Frente, esquerda, direita ou retorno
        Parar();
        if (esqTemVerde()) {
          if (dirTemVerde())meiaVoltaVolver();
          else esquerdaVolver();
        }
        else if (dirTemVerde())direitaVolver();
        Frente(velTur);        // caso não haja verde de nenhum lado e ao final dos outros casos, sempre se vai para frente.
      }
      //  FINAL DO TRATAMENTO DOS CRUZAMENTOS....

    }  // final do if(emBaixo)...
    else { //  está na rampa ou em cima
      if (emCima) {


        //   transito em cima e pegar feridos.
        /*(O robô está na posição inicial)ele vá à FRENTE até econtrar a parede ou triângulo. Se encontrar o triângulo ou a parede recolhe garra e joga na caçamba.
          Após encontrar um ou outro, volta de ré e fique x cm do portal(se verifica isso com a distância que o sensor ultra verificou em relação a parede)
          em seguida vira para a direita e vá à frente. Quando encontrar a parede ou o triângulo recolhe a garra e jogue na caçamba. Após isso volta para a frente do  portal e
          dê um esquerda volver. Dessa forma o robô estará na posição inicial. Isso garantirá que as bolinhas não estejam perto do portal. Se ele encontrou o triângulo esse triângulo está a frente
          ou atrás da posição inicial. Caso contrário estará na diagonal da posição inicial. Assim sabe-se onde está o triângulo em relação à posição inicial. Próximo passo será retirar as bolinhas
          do centro. Para isso o robô irá da posição inicial para o centro varrendo as laterais do quadrado central, de tal forma que as bolinhas, se escaparem, não possam sair da área de salvamento.
          após essa etapa, as bolinhas estão nas paredes, basta retornar o robô para a posição inicial e e varrer os cantos. Depois jogar tudo na área de resgate e repetir o processo 2 vezes. 
        //Valores de distância--------------------
        //os valores do lados são aproximadamente 120 e 90,

      }
      else {     // ESTAH NA RAMPA
        while (!Portal()) {
          if (!digitalRead(pinSensorEsq) && !digitalRead(pinSensorDir) )
          {
            Frente(velTur);
          }
          if (digitalRead(pinSensorEsq) && !digitalRead(pinSensorCentral) && !digitalRead(pinSensorDir))
          {
            corrigeEsqRap(velGiro);
          }
          if (!digitalRead(pinSensorEsq) && !digitalRead(pinSensorCentral) && digitalRead(pinSensorDir))
          {
            corrigeDirRap(velGiro);
          }

          /* while(estaParadoNoRedutor())
                         tentarSair();   
        }
        emCima = 1;   // ANDAR
        while (Portal())
          Frente(velAjuste);
        Parar();                // Parando logo após passar o sensor da fita cinza.
        //       NavegarCima();
      }
    }
  }
}// final do loop.*/
