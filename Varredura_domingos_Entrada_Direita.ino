#define tempoBolaCair 2000 // tempo para a bola cair
#define distRedil ((sqrt(largCarro*largCarro/4) + sqrt(compCarro*compCarro/4)) - compCarro/2) //distância que o robô deve retornar para girar sobre seu eixo quando está colado no Redil
#define largCarro 16  //--------------------
#define alinhaGirosDireita 0 //Angulo pedido para a  função que alinha o robô com determinado ângulo do giroscópio, no caso, 0 alinha para a direita 
#define alinhaGirosEsquerda 180 //Angulo pedido para a  função que alinha o robô com determinado ângulo do giroscópio, no caso, 180 alinha para a esquerda 
#define TAndar 100 // tempo para robô  andar ou parar para diferenciar as distâncias em uma função de contagem
#define calibragem 0.5 // distância que será somada a outras para elas acontecerem exatamente no momento esperado, não muito depois
#define quantMin 5 // quantidade mínima para uma contagem
#define Perto 10 // A variável verifica a distância do carrinho em relação a pared
int compCarro = 30;  //--------------------Comprimento como inteiro para exatificar a divisão 
float largResgate,distAtual,distAntiga, difDist;
int val, varridas;// val = variavel de contagem , varridas = quantidade de varridas
int girosInicial, girosAtual;// leituras do giroscópio

void areaResgate () {

   Serial.println("Esquerda");
  esquerdaVolver();// Identificar  a largura da área de resgate
  PegarBola();
   Serial.println("Frente");
  Frente(velTur);
  delay(2000);
  Parar();
  delay(TAndar);
     Serial.println("Direita");
  direitaVolver();
  largResgate = compCarro + leDistancia('f')+ leDistancia('t');//Largura total da área de resgate-
  Serial.print("largura do resgate: ");
  Serial.println(largResgate);
  delay(TAndar);
  Modelo_1Varredura();
}

//---------------------------------------------MODELO DE VARREDURA
void Modelo_1Varredura (){//Prosseguir a distância de uma largura do carro a cada for, sempre voltar na mesma reta varrendo a linha duas vezes.
  //moveIr e moveVoltar  são as direções que o carro vai seguir quando se chamar as funções, Essa função sempre começa com o robô apontando para o comprimento oposto da pista, 
  //O moveIr é a primeira direção que ele precisa seguir (Direita ou Esquerda), então ele varre a linha. 
  //Para fazer a segunda varredura e voltar a apontar para o comprimento oposto na posição inicial, ele utiliza o moveVoltar(Esquerda ou Direita)
  //Nesse tipo de varredura, cada redil será encontrada após certo tipo de movimento, MAS qual movimento a ser feito depende da pista :
  // Primeira varrida (IDA) = Redil"C" ___ Subida para outra varrida em linha reta = Redil "B" ____ Segunda Varrida "A" (VOLTA)
  
  for(varridas = 0; varridas<=( (largResgate-compCarro)/compCarro)*2 ;varridas++){//divisão por inteiros (varridas = largura total dividido por largura do carro), se sobrar restos ele pegará isso depois do "for"
  Serial.print("Inicio da varredura");
  esquerdaVolver();
  girosInicial = leGiroscopio('y'); // leitura do eixo y antiga
  
  varrerLinha(); //Fazer uma leitura a cada movimento que ele fizer para verificar se achou o redil, Se o Redil for achado nesse movimento é o caso C
  girosAtual = leGiroscopio('y');
  
  if(!(girosAtual = girosInicial)){//Verificação de mudança na angulação do giroscopio
  Caso_C();
  return;
  }//Como não houve alteração na angulação do giroscopio, o redil não está na posição C e o robô continuará a varredura
  
  direitaVolver();//Já verreu uma linha, agora o robô virará, subirá uma distancia e virará de novo para varrer a outra linha
  
  distAntiga = leDistancia('f');
  girosInicial = leGiroscopio('x');  //Fazer uma leitura a cada movimento que ele fizer para verificar se achou o redil, Se o Redil for achado nesse movimento é o caso B, leitura do eixo X
  Frente(velTur);
  val = 1;
  while(val){//tempo para ele andar a metade do seu comprimento
   distAtual = leDistancia('f');
   if(distAntiga - distAtual  >= compCarro/2)val = 0;//Se a  distinicial(antes de se mover) menos a distAtual for igual ou maior a dist da largura do carro, então ele para
   delay (TAndar);
   girosAtual = leGiroscopio('x');
   if(!(girosAtual = girosInicial)){
    Caso_B();
    return;
   }
  }
  Parar();
  delay(TAndar);
  
  direitaVolver();//Giro do robô para varrer a outra linha
  
  girosInicial = leGiroscopio('y'); // leitura do eixo y antiga
  varrerLinha();  //Fazer uma leitura a cada movimento que ele fizer para verificar se achou o redil, Se o Redil for achado nesse movimento é o caso A
  girosAtual = leGiroscopio('y');
  if(!(girosAtual = girosInicial)){
  Caso_A();
  return;
  }
  
  esquerdaVolver();//Deixa o robô denovo na mesma posição inicial, porém com a distância de uma largura do robô a frente
  }
  //--------------------------------------------RESTA VARRER UM ÚLTIMO COMPRIMENTO DO CARRO NA PISTA, PORÉM, ELE NÃO PODERÁ SUBIR MAIS.
  //Se sobraram restos na divisão para o número de varridas, agora ele varrerá esse resto
  girosInicial = leGiroscopio('y'); // leitura do eixo y antiga
  varrerLinha();
  girosAtual = leGiroscopio('y');
  if(!(girosAtual = girosInicial)){
  Caso_A();
  return;
  }
  
  esquerdaVolver();
  girosInicial = leGiroscopio('y'); // leitura do eixo y antiga
  varrerLinha();
  girosAtual = leGiroscopio('y');
  if(!(girosAtual = girosInicial)){
    Caso_B();
    return;
   }
  
  Re(velTur);// Voltar para a posição final do for para facilitar as funções
  distAntiga = leDistancia('t');
  delay(TAndar);
  val = 0;
  while (val<=3){// ver se parou na parede   
   distAtual = leDistancia('t'); //Leitura da distancia do ultrassônico da frente até a parede
   delay(1);
   difDist= pow((distAntiga-distAtual),2); //tornando a diferença entre as distâncias positiva para comparar com a dif max
   if(difDist<=difMAX)val ++; //Se a leitura passada permanecer próxima ou igual a atual (menor que a difmax), significa que o robô não foi pra frente, ou seja, está sendo barrado
   distAntiga=distAtual;
   delay (TAndar);
  }
  
  Parar();
  delay(TAndar); 
  direitaVolver();//Se o robô não achar nenhum Redil(impossível), ele terminaria aqui.------Fase de testes------
  }
  
 //-------Função para jogar as bolas no Redil
 void jogarBolasRedil(){
    meiaVoltaVolver();//Jogou as bolas para dentro, agora ele dará meia volta
    
    Re(velTur); //Para não ficar nenhuma distancia entre o Redil e o Carro e uma bola possivelmente cair, o robô dará uma ré
    val = 0;
    while (val<= quantMin){// Forçar o carro contra o Redil    
     distAtual = leDistancia('t'); //Leitura da distancia do ultrassônico de trás até o Redil
     delay(1);
     difDist= pow((distAntiga-distAtual),2); //tornando a diferença entre as distâncias positiva para comparar com a dif max
     if(difDist<=difMAX)val ++; //Se a leitura passada permanecer próxima ou igual a atual (menor que a difmax), significa que o robô não foi pra frente, ou seja, está sendo barrado
     distAntiga=distAtual;
     delay (TAndar);
    }
    
    Parar();
    delay(TAndar);//Programação Defensiva, tempo discutível.
    
    SubirCancela();//Deixar as bolas cairem no redil
    delay(tempoBolaCair);// tempo para as bolas cairem no Redil, a ser definido
    
    distAtual = leDistancia('t');// Agora o robô está colado no Redil
    Frente(velTur); //Dar espaço para o robô girar
    while(distAtual <= distRedil){
      distAtual = leDistancia('t');
      delay(1);
    }
    
    Parar();
    delay(TAndar);
 }
 //-----------------------------------------------------------CASO C
  void Caso_C(){//Achou o Redil

    jogarBolasRedil();
    
    alinhaGiroscopio(alinhaGirosDireita);// Função que permite o robô corrigir sua angulação utilizando o giroscópio
    
    varrerLinha();
    
    esquerdaVolver();//Se a Entrada da pista for na direita, o robô girará para a esquerda no final da linha

    Frente(velTur);//O robô andará essa largura para, quando chamarmos a função, ele não cair no mesmo loop de achar o Redil de novo
    val = 1;
    distAntiga = leDistancia('f');
    while(val){//tempo para ele andar o sua largura
     distAtual = leDistancia('f');
     if(distAntiga - distAtual  >= largCarro)val = 0;//Se a  distinicial(antes de se mover) menos a distAtual for igual ou maior a dist da largura do carro, então ele para
     delay (TAndar);
    }
    
    Parar();
    delay(TAndar);
    
     Modelo_1Varredura(); // como a entrada da pista é na direita, o primeiro movimento tem que ser para a esquerda
     Re(velTur);// Após a feição das varreduras o robô dará ré até a entrada para chegar no redil novamente
     val = 0;
     while (!(val >= quantMin)){// Voltar à entrada para entregar as bolinhas     
      distAtual = leDistancia('f');
      if(distAtual + calibragem >= (largResgate-largCarro))val = val+1; //Se a leitura passada permanecer próxima ou igual a atual, significa que o robô não foi pra frente, está sendo barrado
      delay (TAndar);
    }
    
    esquerdaVolver();
    varrerLinha();
    Caso_C(); //O robô entrará em um loop de varridas
}

  //-----------------------------------------------------------CASO B
   void Caso_B(){//Achou o Redil
     varrerLinha();// No Caso "B" forçar a pá contra o Redil é necessário, pois não se tem certeza que isso foi feito
     
     jogarBolasRedil();
     
    alinhaGiroscopio(alinhaGirosDireita);// Função que permite o robô corrigir sua angulação utilizando o giroscópio
    
    varrerLinha();// Agora o robô fará duas últimas varreduras, na linha que do Redil que ele não varrreu e a linha limite da Área de Resgate
     
    esquerdaVolver();
    varrerLinha();
     
    esquerdaVolver ();//Pista com a entrada na direita
    varrerLinha();//Varreu até o Redil
    
    jogarBolasRedil();
     
    alinhaGiroscopio(alinhaGirosDireita);
     //Somente deu uma varrida completa na pista toda
     }
  //------------------------------------------------------CASO A   
     void Caso_A(){//Achou o Redil
     
     jogarBolasRedil();

     alinhaGiroscopio(alinhaGirosEsquerda);// Função que permite o robô corrigir sua angulação utilizando o giroscópio
     varrerLinha();
     
     direitaVolver();
     varrerLinha();
     
     direitaVolver();
     varrerLinha();// Agora o robô fará duas últimas varreduras, na linha que do Redil que ele não varrreu e a linha limite da Área de Resgate
     
     jogarBolasRedil();

    alinhaGiroscopio(alinhaGirosDireita);
     //Somente dá um varrida completa na Pista
     }
