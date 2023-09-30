 
 int estouNaRampa(){
  float YAtual,AngRampa;
  MedeAnguloVertical.update();
  YAtual = MedeAnguloVertical.getAngleY();
  AngRampa = abs(YAtual - YBase);
  Serial.print("\tangleY : ");
  Serial.println(AngRampa);
  return(AngRampa >= RampaMinima);
 }

 //*****************************************************************************************************************************************************************************
int Portal(){
  int Volta;
  int Volta1;
  
digitalWrite(S_Cor_E_Red, HIGH); digitalWrite( S_Cor_E_Green, HIGH);  digitalWrite( S_Cor_E_Blue, HIGH);
digitalWrite(S_Cor_D_Red, HIGH); digitalWrite( S_Cor_D_Green, HIGH);  digitalWrite( S_Cor_D_Blue, HIGH);
delay(200);
 Volta = analogRead(S_Cor_E_Le);
 Volta1 = analogRead(S_Cor_D_Le);
 return(((Volta>= Prata_E[Min]) && (Volta <= Prata_E[Max])) && ((Volta1>= Prata_D[Min]) && (Volta1 <= Prata_D[Max]))) ;
}

 
/*
 int andarDeCima(){
  float YAtual,AngCima;
  MedeAnguloVertical.update();
  YAtual = MedeAnguloVertical.getAngleY();
  AngCima = abs(YAtual - YBase);
  Serial.print("\tangleY : ");
  Serial.println(AngCima);
  return(AngCima <= (RampaMinima/2));
 }   */
