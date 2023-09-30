/*int pi = 0; 
int pf = 180;
int val;    // variavel para ler o valor da posição inicial do servo
int estado,i;
void NovaPos(int orig, int dest){

   if(orig <= dest)
            for(i = orig; i < dest; i++)
               {
                 myservo.write(i);
                 delay(10);
                 }
         else for(i = orig; i > dest; i--)
                 {
                 myservo.write(i);
                 delay(10);
                 }
       }
void setup()
{
  ServoPa.attach(Servo01);  // Liga oficialmente o servo motor ao pino registrado no ligservo.
  Serial.begin(9600);
  val  = myservo.read();
  NovaPos(val,pi);
  delay(3000);
  NovaPos(pi,pf);
  delay(3000);  
  
}



void loop() 
{ 

  NovaPos(pf,pi);
  delay(3000);
  NovaPos(pi,pf);
  delay(3000);

} 

void Avancar(int dist){
        contaPulso = 0;  
        Frente(velAjuste);
        while(contaPulso < pulsosParaDist(dist)){
            delayMicroseconds(1);
        }
        Parar();
        }






//*******************************NavegarCima() *****************************************************************************************************************
void NavegarCima(){
float DistFrPI;   // distancia para frente a partir da Posicao Inicial.
float DistEsqEntrado;  // distancia para a esquerda a partir da Posicao Inicial.
DistFrPI = leDistancia('f');
Avancar(20);
DistEsqEntrado =  leDistancia('e');
if(DistEsqEntrado < ){  // está no canto da esquerda.      /// posso trabalhar com o meiaDireitaVolver ou meiaEsquerdaVolver  ...
  
}
}
else {    // está no canto da direita  */
