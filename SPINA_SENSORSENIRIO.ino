
void CorRGB(int r, int g, int b){//DETERMINA A COR QUE SERÁ LANÇADA PELO LED RGB DOS DOIS LEDS
  analogWrite(S_Cor_E_Red, r);
  analogWrite(S_Cor_E_Green, g);
  analogWrite(S_Cor_E_Blue, b);
  analogWrite(S_Cor_D_Red, r);
  analogWrite(S_Cor_D_Green, g);
  analogWrite(S_Cor_D_Blue, b);
  //A COR BRANCA EH A MAIS INTERESSANTE;
}
void DescobreIntervaloE (int* Cor){//Descobre do sensor de cor esquerdo o intervalo do  de determinada cor 
    int Volta;
    int i; 
    CorRGB(RLegal,GLegal,BLegal); //Acende o led;
for(i = 1; i <= PrecisaoIntervalo; i++){   
    delay(200); 
    Volta = analogRead(S_Cor_E_Le); //recebeu o valor 
    Serial.print("Leitura: ");
    Serial.println(Volta);
    Cor[Min] = (Volta < Cor[Min])?Volta:Cor[Min];    
    Cor[Max] = (Volta > Cor[Max])?Volta:Cor[Max];       
 }}
 void DescobreIntervaloD (int* Cor){//Descobre do sensor de cor direito o intervalo de determinada cor 
    int Volta;
    int i; 
    CorRGB(RLegal,GLegal,BLegal); //Acende o led;
for(i = 1; i <= PrecisaoIntervalo; i++){   
    delay(200); 
    Volta = analogRead(S_Cor_D_Le); //recebeu o valor 
    Serial.print("Leitura: ");
    Serial.println(Volta);
    Cor[Min] = (Volta < Cor[Min])?Volta:Cor[Min];    
    Cor[Max] = (Volta > Cor[Max])?Volta:Cor[Max];       
 }
}
//------------------------------------

void alinhaGiroscopio(int angulo){

}

int leGiroscopio(char a){
 return(0); 
}
