
//*****************************************************************************************************************************************************************************
int esqTemVerde(){
  int Volta;
  
digitalWrite(S_Cor_E_Red, HIGH); digitalWrite( S_Cor_E_Green, HIGH);  digitalWrite( S_Cor_E_Blue, HIGH);
delay(200);
 Volta = analogRead(S_Cor_E_Le);

return((Volta>= Verde_E[Min]) && (Volta <= Verde_E[Max]));
}
//*****************************************************************************************************************************************************************************
int dirTemVerde(){
  int Volta;
  
digitalWrite(S_Cor_D_Red, HIGH); digitalWrite( S_Cor_D_Green, HIGH);  digitalWrite( S_Cor_D_Blue, HIGH);
delay(200);
Volta = analogRead(S_Cor_D_Le);

return((Volta>= Verde_D[Min]) && (Volta <= Verde_D[Max]));
}
