//******************************************************************************************************************************************************************************************
int pulsosParaDist(int d){
  return(d*ppVolta/dpVolta); 
}

//******************************************************************************************************************************************************************************************
void Frente(int vel){  
  analogWrite(pinMotorDireitaFrente, vel-correcao(vel));  
  analogWrite(pinMotorDireitaTras, 0);
  analogWrite(pinMotorEsquerdaFrente, vel);
  analogWrite(pinMotorEsquerdaTras, 0);  
}
//******************************************************************************************************************************************************************************************
void Re(int vel){
  analogWrite(pinMotorDireitaFrente, 0);
  analogWrite(pinMotorDireitaTras, vel );
  analogWrite(pinMotorEsquerdaFrente, 0);
  analogWrite(pinMotorEsquerdaTras, vel);  
}
//******************************************************************************************************************************************************************************************
void corrigeReDir(int vel){
  analogWrite(pinMotorEsquerdaFrente, vel);
  analogWrite(pinMotorEsquerdaTras, 0); 
  analogWrite(pinMotorDireitaFrente, 0);
  analogWrite(pinMotorDireitaTras, vel - correcao(vel)); 
}
//******************************************************************************************************************************************************************************************
void corrigeReEsq(int vel){
  analogWrite(pinMotorEsquerdaFrente, 0);
  analogWrite(pinMotorEsquerdaTras, vel); 
  analogWrite(pinMotorDireitaFrente, vel - correcao(vel));
  analogWrite(pinMotorDireitaTras, 0);  
}
//******************************************************************************************************************************************************************************************
void ReNavega(int vel){ 
  //ré seguindo linha... a lógica aqui é que quando o sensor de um lado fica preto, corrige-se para o lado oposto. 
  //EX: sensor esquerdo de dentro fica preto, então devemos acelerar o motor direito para trás e o esquerdo para frente!
  if(!digitalRead(pinSensorEsq) && digitalRead(pinSensorCentral) && !digitalRead(pinSensorDir))
  { //o sensor do centro esta seguido; os dois motores devem estar ativos.
    Re(vel);
  }
  if(!digitalRead(pinSensorEsq)&& !digitalRead(pinSensorCentral)&& digitalRead(pinSensorDir))
  { //o sensor da esquerda de dentro está pegando, entao o motor direita tem que acelerar para trás
    corrigeReDir(vel);
  } 
  if(digitalRead(pinSensorEsq) && !digitalRead(pinSensorCentral) && !digitalRead(pinSensorDir))
  { //o sensor da direita de dentro está pegando, entao o motor direito tem que acelerar para trás
    corrigeReEsq(vel);
  } 
 }
//******************************************************************************************************************************************************************************************
void corrigeDir(int vel){  
  analogWrite(pinMotorDireitaFrente, 0);
  analogWrite(pinMotorDireitaTras, 0);
  analogWrite(pinMotorEsquerdaFrente, vel);
  analogWrite(pinMotorEsquerdaTras, 0);  
}
//******************************************************************************************************************************************************************************************
void corrigeEsq(int vel){  
  analogWrite(pinMotorDireitaFrente, (vel - correcao(vel)));
  analogWrite(pinMotorDireitaTras, 0);
  analogWrite(pinMotorEsquerdaFrente, 0);
  analogWrite(pinMotorEsquerdaTras, 0);  
}
//******************************************************************************************************************************************************************************************
void corrigeDirRap(int vel){  
  analogWrite(pinMotorDireitaFrente, 0);
  analogWrite(pinMotorDireitaTras, (vel-correcao(vel)));
  analogWrite(pinMotorEsquerdaFrente, vel);
  analogWrite(pinMotorEsquerdaTras, 0);  
}
//******************************************************************************************************************************************************************************************
void corrigeEsqRap(int vel){  
  analogWrite(pinMotorDireitaFrente, (vel - correcao(vel)));
  analogWrite(pinMotorDireitaTras, 0);
  analogWrite(pinMotorEsquerdaFrente, 0);
  analogWrite(pinMotorEsquerdaTras, vel);  
}
//******************************************************************************************************************************************************************************************
void Parar(){  
  analogWrite(pinMotorDireitaFrente, 0);
  analogWrite(pinMotorDireitaTras, 0);
  analogWrite(pinMotorEsquerdaFrente,0);
  analogWrite(pinMotorEsquerdaTras, 0);  
}

//******************************************************************************************************************************************************************************************
int temObstaculoPerto(){  //leitura do ultrasom
  float Tempo;
  digitalWrite(trigFrente, LOW);
  delayMicroseconds(2);
  digitalWrite(trigFrente, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigFrente, LOW);
  delayMicroseconds(2);
  Tempo = pulseIn(echoFrente, HIGH);
  Dist = (Tempo/2) / 29.1;  
  return ((Dist <= dMin)?1:0);  // como if 
}
//***************************************************************************************************************************************************************************************
void direitaVolver(){
   int pulsosDesejados = pulsosParaDist(dpVoltaCarro/4);
   Serial.print("Pulsos Desejados: ");
   Serial.println(pulsosDesejados);
   delay(2000);
   contaPulso = 0;  
   analogWrite(pinMotorDireitaFrente, 0);
   analogWrite(pinMotorDireitaTras, (velGiro-correcao(velAjuste)));
   analogWrite(pinMotorEsquerdaFrente, velGiro);
   analogWrite(pinMotorEsquerdaTras, 0);
  while(contaPulso < (pulsosDesejados-46)){ 
     delayMicroseconds (1);
   Serial.println(contaPulso);
 //delayMicroseconds (10);
 
 
                                        }
  Parar();
}
//***************************************************************************************************************************************************************************************
void esquerdaVolver(){
  int pulsosDesejados = pulsosParaDist(dpVoltaCarro/4);
  contaPulso = 0;  
   analogWrite(pinMotorDireitaFrente, velGiro- correcao(velAjuste));
   analogWrite(pinMotorDireitaTras, 0);
   analogWrite(pinMotorEsquerdaFrente, 0);
   analogWrite(pinMotorEsquerdaTras, velGiro);
  while(contaPulso < (pulsosDesejados-46)){     
    delayMicroseconds (1);
    Serial.println(contaPulso);
 //delayMicroseconds (10);
  
  
  }
  Parar();
}

//***************************************************************************************************************************************************************************************
void meiaEsquerdaVolver(){
  int pulsosDesejados = pulsosParaDist(dpVoltaCarro/8);
  contaPulso = 0;  
   analogWrite(pinMotorDireitaFrente, velGiro- correcao(velAjuste));
   analogWrite(pinMotorDireitaTras, 0);
   analogWrite(pinMotorEsquerdaFrente, 0);
   analogWrite(pinMotorEsquerdaTras, velGiro);
  while(contaPulso < (pulsosDesejados)){ 
    delayMicroseconds (1);
    Serial.println(contaPulso);
    //delayMicroseconds (10);

    }
  Parar();
}


//***************************************************************************************************************************************************************************************
void meiaDireitaVolver(){
   int pulsosDesejados = pulsosParaDist(dpVoltaCarro/8);
   Serial.print("Pulsos Desejados: ");
   Serial.println(pulsosDesejados);
   delay(2000);
   contaPulso = 0;  
   analogWrite(pinMotorDireitaFrente, 0);
   analogWrite(pinMotorDireitaTras, (velGiro-correcao(velAjuste)));
   analogWrite(pinMotorEsquerdaFrente, velGiro);
   analogWrite(pinMotorEsquerdaTras, 0);
  while(contaPulso < pulsosDesejados){     delayMicroseconds (1);
    Serial.println(contaPulso);
    delayMicroseconds (10);

                                        }
  Parar();
}



//***************************************************************************************************************************************************************************************
void meiaVoltaVolver(){
  int pulsosDesejados = pulsosParaDist(dpVoltaCarro/2);
  contaPulso = 0;  
   analogWrite(pinMotorDireitaFrente, velGiro- correcao(velAjuste));
   analogWrite(pinMotorDireitaTras, 0);
   analogWrite(pinMotorEsquerdaFrente, 0);
   analogWrite(pinMotorEsquerdaTras, velGiro);

  while(contaPulso < (pulsosDesejados-46)){ 
    delayMicroseconds (1);
  Serial.println(contaPulso);
//delayMicroseconds (10);
  }

  Parar();
}
//***************************************************************************************************************************************************************************************

void alinharPelaTesta(){      // esta e para trabalhar somente com os dois sensores de dentro
while(!(digitalRead(pinSensorEsq) && digitalRead(pinSensorDir))){
  Re(velAjuste);  // marcha a Ré para tentar acertar perpendicularmente com a linha que está sendo seguida.
  while( (digitalRead(pinSensorEsq)) &&  (digitalRead(pinSensorDir))){
    delayMicroseconds(1); 
  }
  delayMicroseconds(1);
  Parar();
  while((!digitalRead(pinSensorEsq))&& (digitalRead(pinSensorDir)))  
     {
         corrigeDirRap(velAjuste);
     }
  while((digitalRead(pinSensorDir)==0)&&(digitalRead(pinSensorEsq)))
        {
            corrigeEsqRap(velAjuste);
        }
}
Parar();
}
//***************************************************************************************************************************************************************************************
 float leDistancia(char lado){
  float Tempo, dist;
  switch(lado){
    case 'e': digitalWrite(trigEsq, LOW);
              delayMicroseconds(2);
              digitalWrite(trigEsq, HIGH);
              delayMicroseconds(10);
              digitalWrite(trigEsq, LOW);
              delayMicroseconds(2);
              Tempo = pulseIn(echoEsq, HIGH);
              dist = (Tempo/2) / 29.1;
              break;
    case 't': digitalWrite(trigTras, LOW);
              delayMicroseconds(2);
              digitalWrite(trigTras, HIGH);
              delayMicroseconds(10);
              digitalWrite(trigTras, LOW);
              delayMicroseconds(2);
              Tempo = pulseIn(echoTras, HIGH);
              dist = (Tempo/2) / 29.1;
              break;
   case 'f':  digitalWrite(trigFrente, LOW);
              delayMicroseconds(2);
              digitalWrite(trigFrente, HIGH);
              delayMicroseconds(10);
              digitalWrite(trigFrente, LOW);
              delayMicroseconds(2);
              Tempo = pulseIn(echoFrente, HIGH);
              dist = (Tempo/2) / 29.1;
              break;
  }
  return(dist);             
}

//***************************************************************************************************************************************************************************************
void avancarDesvio(){  
  float Tempo;
  float distLimSup = distEsperada;
  Dist = leDistancia('e');
  if(Dist >= distLimSup){   // ainda não ve o obstáculo do lado
        Frente(velAjuste);
        while(Dist > distLimSup){
            Dist = leDistancia('e');
        }
        Parar();    // sensor começa a ver o obstaculo.
        }
        contaPulso = 0;   // zera o contaPulso para ver o tamanho da frente do obstáculo
        Frente(velAjuste-15);
        while(Dist <= distLimSup){
            Dist = leDistancia('e');
            Serial.println(Dist);
            delayMicroseconds(1);
        } 
        Parar();
        
        largObstaculo = contaPulso*dpVolta/ppVolta;   // para segurança no retorno à linha.
        contaPulso = 0; // zerando para calcular quanto avanço mais por segurança  
        Frente(velAjuste);
        while(contaPulso < pulsosParaDist(distFolga)+150){
        delayMicroseconds(1);
        Serial.println(contaPulso);
        }
        Parar();
        }
//***************************************************************************************************************************************************************************************
void Ultrapassar(){
  float Tempo;
  float distLimSup = distLateral + distFolga;
  Dist = leDistancia('e');
  if(Dist > distLimSup){   // ainda não ve o obstáculo do lado
        Frente(velAjuste);
        while(Dist > distLimSup){
            Dist = leDistancia('e');
        }
        Parar();    // sensor começa a ver o obstaculo.
        }
        contaPulso = 0;   // zera o contaPulso para ver o tamanho da frente do obstáculo
        Frente(velAjuste);
        while(Dist <= distLimSup){
            Dist = leDistancia('e');
        } 
        Parar();
        contaPulso = 0; // zerando para calcular quanto avanço mais por segurança  
        Frente(velAjuste);
        while(contaPulso < pulsosParaDist(distFolga)+150){
        delayMicroseconds(1);
        Serial.println(contaPulso);
        }
        Parar();
    }
    
/***************************************************************************************************************************************************************************************/
void recuarDesvio(){ 
while(!((digitalRead(pinSensorEsq)==0) && (digitalRead(pinSensorDir)==0))){
  Frente(velAjuste);
  while((digitalRead(pinSensorEsq)) && (digitalRead(pinSensorDir)))
 {delayMicroseconds(1);}
  Parar(); 
   while((digitalRead(pinSensorEsq)==0)&& (digitalRead(pinSensorDir)))  
     {
         corrigeEsqRap(velAjuste);
     }
  while((digitalRead(pinSensorDir)==0)&&(digitalRead(pinSensorEsq)))
        {
            corrigeDirRap(velAjuste);
        }
 }
Parar();
}
//***************************************************************************************************************************************************************************************
void direitaVolverSegueLinha(){
  delayMicroseconds(1);
    Frente(velGiro);
  delay(300);
    Parar();
   meiaDireitaVolver();
   analogWrite(pinMotorDireitaFrente, 0);
   analogWrite(pinMotorDireitaTras, (velGiro-correcao(velAjuste)));
   analogWrite(pinMotorEsquerdaFrente, velGiro);
   analogWrite(pinMotorEsquerdaTras, 0);
   while(!digitalRead(pinSensorCentral)){ 
              }
  Frente(velTur);
  delay(100);            
  Parar();
}
//***************************************************************************************************************************************************************************************
void esquerdaVolverSegueLinha(){
   delayMicroseconds(1);
      Frente(velGiro);
  delay(300);
    Parar();
   meiaEsquerdaVolver();
   analogWrite(pinMotorDireitaFrente, velGiro- correcao(velAjuste));
   analogWrite(pinMotorDireitaTras, 0);
   analogWrite(pinMotorEsquerdaFrente, 0);
   analogWrite(pinMotorEsquerdaTras, velGiro);
   while(!digitalRead(pinSensorCentral)){     
  }
  Frente(velTur);
  delay(100);
  Parar();
}
void meiaVoltaVolverSegueLinha(){
   delayMicroseconds(1);
   Frente(velGiro);
   delay(100);
   Parar();
   meiaEsquerdaVolver();
   meiaEsquerdaVolver();
  analogWrite(pinMotorDireitaFrente, velTur - correcao(velTur));
   analogWrite(pinMotorDireitaTras, 0);
   analogWrite(pinMotorEsquerdaFrente, 0);
   analogWrite(pinMotorEsquerdaTras, velTur);
   while(!digitalRead(pinSensorCentral)){ 
              }
  Frente(velTur);
  delay(100);            
  Parar();
}
