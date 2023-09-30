
#define compCarro 30
void varrerLinha(){
PegarBola();//Posiciona pá para pegar bola; 
Frente(velTur); //o carrinho inicia seus motores para frente;
      distAntiga = leDistancia('f');
      val = 0;
      delay(TAndar);  
   while (val<=3){// ver se emperrou   
      distAtual = leDistancia('f'); //Leitura da distancia do ultrafrente até a parede
       Serial.print("distAtual : ");
   Serial.println(digitalRead(distAtual));
      delay(1);
      difDist = pow((distAntiga-distAtual),2); //tornando a diferença entre as distâncias positiva para comparar com a dif max
      if(difDist<=difMAX)val ++; //Se a leitura passada permanecer próxima ou igual a atual (menor que a difmax), significa que o robô não foi pra frente, ou seja, está sendo barrado
      distAntiga=distAtual;
      delay (TAndar);
   Serial.print("val : ");
   Serial.println(digitalRead(val));
   Serial.print("distAntiga : ");
   Serial.println(digitalRead(distAntiga));
   Serial.print("difDist : ");
   Serial.println(digitalRead(difDist));
    }
      Re(velTur);
      Serial.print("Dar re");
      val=1;
    while (val){// Dar espaço para conseguir levantar a pá
      distAtual = leDistancia('f');
   Serial.print("distAtual : ");
   Serial.println(digitalRead(distAtual));
      delay(1);
      if(distAtual>=distRePa)val = 0;//Se a distAtual for igual ou maior a dist min necessária para conseguir levantar a pá, então acaba a ré
    }
 Parar(); //parar
 GuardaBola();//levantar a pá para a bola cair
 delay(3000);//Dar tempo para a bolinha cair
 PegarBola(); // voltar ao estado 
  }
