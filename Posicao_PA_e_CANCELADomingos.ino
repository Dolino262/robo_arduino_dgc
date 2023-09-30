//PARA A PÁ
int parar = 90; //velocidade nula do giro do servopa 
int baixo =120; //velocidade média sentido horário do giro do servopa -- sentido descer
int cima = 60; //velocidade média sentido anti-horário do giro do servopa -- sentido subir
int estadopa = 180; // estado da pá: Varia entre 180, 60 e 90. Sendo 180 a pá guardada, 60 a pá lançando bolinhas para o armazém e 90 a pá buscando bolinhas.
//___________________________________________________________________________________
void GuardaBola(){//angulo de 60 em relação ao chão / ir até a posição de guardar bolinha
   ServoPa.write(cima); // giro anti-horario
   delay(tempo90_60);
   ServoPa.write(parar); // depois de derminado tempo ele já guarda as bolinhas;
   estadopa = 60;
  }
  
//___________________________________________________________________________________
void Descanco(){ //angulo de 180 em relação ao chão / ir até a posição de descanço 
   ServoPa.write(cima); // giro anti-horario
   while(digitalRead(FimCursoc));//Quando o Fim de Curso é apertado ele dá 0 
   ServoPa.write(parar); 
   estadopa = 180;
   Serial.print("cima : ");
   Serial.println(digitalRead(FimCursoc));
}

//___________________________________________________________________________________
void PegarBola(){//angulo de 90 em relação ao chão // ir até a posição pegar bolinhas
   ServoPa.write(baixo); // giro horario
   while(digitalRead(FimCursob));
   ServoPa.write(parar); 
   estadopa = 90;
   Serial.print("baixo : ");
   Serial.println(digitalRead(FimCursob));
}

//PARA A CANCELA
int ang; //ângulo que se apresenta a cancela -> 45 está fechada e 145 está aberta
void SubirCancela(){
  for(ang=CancelaFechada;ang<=CancelaAberta;ang+=5){
  ServoCancela.write(ang);
  delay(1);
  }
}
void DescerCancela(){
   for(ang=CancelaAberta;ang>=CancelaFechada;ang-=5){
  ServoCancela.write(ang);
  delay(1);
   }
}
