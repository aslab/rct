/*
  Programa que lee el valor del inclin�metro
 max 746      min 55
 420 = 0� approx
 */

// ****************************************

//#include <ServoTimeTimer1.h> //linea para servo con la placa diecimila
#include <Servo.h> /// linea para servo con la arduino mega

// ****************************************

#define servoPin 13 // linea para servo
#define digpininf 22
#define digpinsup 23
#define digpinbrujula 25





int ledPin = 13;   // select the pin for the LED
int ang_v = 0;     // variable to store the value coming from the sensor
int ang = 0;       // variable to store the value coming from the sensor translate to degrees
int entrada1=0;    // lo que lee del ordenador
int angulo;
int giro;
int v_ant=0;//medida anterior
int v_act;//medida actual//

int valor_pin[12] = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

int angulo_max=0;
int angulo_max_ant=0;
int angulo_min=0;
int angulo_min_ant=0;

int referencia;
int servo_enabled=0;

int error_sup=0;
int error_inf=0;

unsigned int valor_pind22=0;
unsigned int valor_pind23=0;
unsigned int valor_pind24=0;
unsigned int valor_pind25=0;
unsigned int valor_pind26=0;
unsigned int valor_pind27=0;

int pin=0;

int tope_inf=0;
int tope_sup=0;
int salida1=0;
int init_val=0;


// ****************************

Servo servo;  // linea para el servo si se usa la placa arduino mega

// ****************************

int contador=0;
int salida=0;
int ref_anterior;

// variables para el PID

int u,e,v; // la y es la entrada del inclin�metro? -> la variable "valor" y la referencia es "referencia"
double K=0.5;
double Ti=60;
double Td=0.7;
double Beta=1;
double Tr=10;
double N=5;
double h=0.1;
//double ad=Td/(Td+N*h);
//double bd=K*ad*N;
double D,I;
int e1=0;
int e2=0;
double T=1;
double q0=K*(1+T/Ti+Td/T);
double q1=K*(-1-2*Td/T);
double q2=K*Td/T;

void setup() {
  servo.attach(servoPin); // adivina... servo
  pinMode(ledPin, OUTPUT);  // declare the ledPin as an OUTPUT
  Serial.begin(9600);

  pinMode(digpininf, INPUT);
  pinMode(digpinsup, INPUT);
  pinMode(digpinbrujula,INPUT);

  pinMode(24,OUTPUT);
  pinMode(26,OUTPUT);
  pinMode(27,OUTPUT);

  for (int i = 31; i <= 39; i++)
  {
    digitalWrite(i,HIGH);
    pinMode(i,OUTPUT);
    digitalWrite(i,HIGH);
  }

}

void loop() {

  if(init_val==0){ // esto es una funcion de iniciacion para dar una calibracion inicial al potenciometro.

     //puesta_cero(); // encontramos el limite inferior del potenciometro   

    init_val=1;
  }

  //hago las lecturas de todos los pines


  refresh_an_pin();
  refresh_dig_pin();
  refresh_compass();

  entrada1 = Serial.read();

  switch(entrada1){
  case 0:
    { // peticion de info, asi que le envio los datos que tengo: referencia actual, inclinometro y enable del servo

      enviar_info();

    }
    break;
  case 1:
  case 2:
  case 3:
    {// cambio de referencia del PID

      enviar_ceros();

      //referencia = 255*(entrada1-1)+Serial.read();
      // como siempre, tengo que cerrar la comunicacion enviando algo, porque lo primero que haremos en el siguiente ciclo sera leer desde 
      // la placa

      int new_value = Serial.read();
      if (new_value <= 0) new_value = 0;
      if (new_value >= 180) new_value = 180;
      servo.write(new_value);

      enviar_ceros();

    }//case 1,2 y 3
    break;
  case 4:
    {// enable del servo
      if (servo_enabled==0) servo_enabled=1; 
      else servo_enabled=0;

      enviar_ceros();

    }//case 4
    break;
  case 5:
    {// puesta a cero

      enviar_ceros();
      //puesta_cero();

    }//case 5
    break;
  case 6:
    {// poner a nivel alto una salida digital

      enviar_ceros();

      pin=Serial.read();
      referencia=pin;
      digitalWrite(pin,HIGH);
      switch(pin){
      case 24: 
        valor_pind24=1;
        break;
      case 26: 
        valor_pind26=1;
        break;
      case 27: 
        valor_pind27=1;
        break;
      default:;
      }//switch


      // como siempre, tengo que cerrar la comunicacion enviando algo, porque lo primero que haremos en el siguiente ciclo sera leer desde 
      //a placa

      enviar_ceros();

    }//case 6
    break;
  case 7:
    {// poner a nivel bajo una salida digital

      enviar_ceros();

      pin=Serial.read();
      digitalWrite(pin,LOW);

      switch(pin){
      case 24: 
        valor_pind24=0;
        break;
      case 26: 
        valor_pind26=0;
        break;
      case 27: 
        valor_pind27=0;
        break;
      default:

        ;
      }//switch
      // como siempre, tengo que cerrar la comunicacion enviando algo, porque lo primero que haremos en el siguiente ciclo sera leer desde 
      //a placa

      enviar_ceros();

    }//case 7
    break;
  default:
    {
      // envio informacion

      enviar_info();
    }
  }//fin del case de la orden

  //************************************************ de momento esta deshabilitado el servo  
  //servo.detach();
  //servo.write(1050);

  servo_enabled = 0;

  if(servo_enabled==1){
    if(referencia!=valor_pin[5]){
      if (!servo.attached())
      { 
        servo.attach(servoPin);
        if (salida==0) servo.write(1484);
      }
      else {
        if(contador>10)
        { // el retraso es para que le de tiempo al potenciometro a dar su medida
          //salida=(int)(servo.read()+(referencia-valor)/*abs(referencia-valor)*/);
          salida=(int)(servo.read()+calcular_salida(referencia,valor_pin[5],v_ant,ref_anterior));
          //1800 como maximo, INCLUYENDO EL LASER
          //1080 como minimo
          if (salida>1800) salida=1800; // debo de incluir el minimo hallado por el potenciometro
          if (salida<1050) salida=1050; // en la puesta a cero, debo de hacer que busque el maximo tambien, para que la ref no pase de este valor
          // o debo de verificar aqui si toca o no?... mejor eso... para que no dependa de la puesta a cero...
          //u=salida;
          contador=0;
        }
        else contador++;
        //updateState(u,valor);
        servo.write(salida);

      }
    }
    else servo.detach();
  }
  else {
    //servo.write(1484);
    //servo.detach();
  }
  v_ant=valor_pin[5];
  ref_anterior=referencia;

} // loop

int calcular_salida(int ref, int y,int yant,int ref_ant){
  D=N/(N*h+Td)*(Td/N*D+K*Td*((ref-ref_ant)-(y-yant)));  
  u=K*(Beta*ref-y)+I+D;

  //v=v+q0*(ref-y)+q1*e1+q2*e2;
  //e2=e1;
  //e1=(ref-y);

  if ((abs(u)>250)) v=250*(u/abs(u));
  else v=u;

  I=I+(K*h/Ti)*(ref-y)+(h/Tr)*(v-u);
  if(abs(ref-y)<5) 
  {
    v=v/abs(v);
    return v;
  }
  if(abs(v)<1){
    return v/abs(v);
  }
  return (int)v;
}

/*void updateState(int u,int y){
 I=I+(K*h/Ti)*e+(h/Tr)*(u-v);
 yOld=y;
 }*/


void puesta_cero(){

  // tope_inf
  salida1=0;
  int i=90;
  while(salida1==0)
  {
    servo.write(i);
    delay(100);

    refresh_an_pin();
    refresh_dig_pin();

    if (valor_pind22 == 1)
      i++;
    else
    {
      salida1 = 1;
      //tope_inf=valor_pin[5];
      tope_inf=i;
    }
    if(i>180)
    {
      error_inf=1;
      return;
    }
  }

  // tope_sup
  salida1=0;
  i=90;
  while(salida1==0)
  {
    servo.write(i);
    delay(100);

    refresh_an_pin();
    refresh_dig_pin();

    if (valor_pind23 == 1)
      i--;
    else
    {
      salida1 = 1;
      //tope_inf=valor_pin[5];
      tope_sup=i;
    }
    if(i>180)
    {
      error_sup=1;
      return;
    }
  }
}



// Applies a low pass filter when refreshing the value of an analogical pin.
void refresh_an_pin(){
  // With i = 5: Aqui debe de ir el potenci�metro, pq si filtro RC no
  // tien condensador para aumentar la velocidad de respuesta
  static int valor_ant_pin[12] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0              };
  for (int i = 0; i < 12; i++)
  {
    valor_pin[i]=analogRead(i);
    valor_pin[i]=0.8*valor_ant_pin[i]+0.2*valor_pin[i];
    valor_ant_pin[i]=valor_pin[i];
  }
}

void refresh_dig_pin(){
  valor_pind22=digitalRead(digpininf);

  valor_pind23=digitalRead(digpinsup);
}

void refresh_compass()
{
  static int i = 0;
  if (++i == 10)
  {
    valor_pind25=pulseIn(digpinbrujula,HIGH,120000);
    valor_pind25 -= 1000;
    valor_pind25 /= 100;
    valor_pind25 = 540 - valor_pind25;
    while (valor_pind25 >= 360)
      valor_pind25 -= 360;
    i = 0;
  }
}

void enviar_ceros(){
  //primero envio los datos de los pines anal�gicos
  Serial.print(2);// 0 
  Serial.print(",");
  /*
      Serial.print(0);// 0 
   Serial.print(",");
   Serial.print(0);// 1
   Serial.print(",");
   Serial.print(0);// 2
   Serial.print(",");
   Serial.print(0);// 3
   Serial.print(",");
   Serial.print(0);// 4
   Serial.print(",");
   Serial.print(0);// 5
   Serial.print(",");
   Serial.print(0);// 6
   Serial.print(",");
   Serial.print(0);// 7
   Serial.print(",");
   Serial.print(0);// 8
   Serial.print(",");
   Serial.print(0);// 9
   Serial.print(",");
   Serial.print(0);// 10
   Serial.print(",");
   Serial.print(0);// 11
   Serial.print(",");
   
   //luego, envio los valores de los pines digitales
   
   Serial.print(0);// 12
   Serial.print(",");
   Serial.print(0);// 13
   Serial.print(",");
   Serial.print(0);// 14
   Serial.print(",");
   Serial.print(0);// 15
   Serial.print(",");
   Serial.print(0);// 16
   Serial.print(",");
   Serial.print(0);// 17
   Serial.print(",");
   
   // ahora la referencia y el servo      
   
   Serial.print(0);// 18
   Serial.print(",");
   Serial.print(2);// 19 
   Serial.print(",");
   
   //ahora el valor inferior del potenciomero y si hubo error en la puesta a cero o no
   
   Serial.print(0);// 20
   Serial.print(",");
   Serial.print(0);// 21
   Serial.print(",");   
   
   //finalmente los parametros del regulador
   
   Serial.print(0);// 22
   Serial.print(",");
   Serial.print(0);// 23
   Serial.print(",");
   Serial.print(0);// 24
   Serial.print(",");
   Serial.print(0);// 25
   Serial.print(",");
   Serial.print(0);// 26
   Serial.print(",");
   Serial.print(0);// 27
   Serial.print(",");
   Serial.print(0);// 28
   Serial.print(",");
   */
  // finalmente, el caracter que indica final de envio

  Serial.println("|"); 
}

void enviar_info(){
  Serial.print(servo_enabled);    // esta dira si el servo esta habilitado o no... 
  Serial.print(",");

  for (int i = 0; i < 12; i++)
  {
    Serial.print(valor_pin[i]);
    Serial.print(",");
  }

  //luego, envio los valores de los pines digitales

  Serial.print(valor_pind22);//valor del pin digital 22
  Serial.print(",");
  Serial.print(valor_pind23);//valor del pin digital 23
  Serial.print(",");
  Serial.print(valor_pind24);//valor del pin digital 24
  Serial.print(",");
  Serial.print(valor_pind25);//valor del pin digital 25
  Serial.print(",");
  Serial.print(valor_pind26);//valor del pin digital 26
  Serial.print(",");
  Serial.print(valor_pind27);//valor del pin digital 27
  Serial.print(",");

  // ahora la referencia y el servo      

  Serial.print(referencia);    // referencia que viene para el pid 
  Serial.print(",");


  //ahora el valor inferior del potenciomero y si hubo error en la puesta a cero o no

  Serial.print(tope_inf);    // valor del potenciometro en la menor inclinacion segun fin de carrera
  Serial.print(",");
  Serial.print(tope_sup);
  Serial.print(",");   

  //finalmente los parametros del regulador

  Serial.print(K);
  Serial.print(",");
  Serial.print((int)(Ti));
  Serial.print(",");
  Serial.print(Td);
  Serial.print(",");
  Serial.print(Beta);
  Serial.print(",");
  Serial.print(Tr);
  Serial.print(",");
  Serial.print(N);
  Serial.print(",");
  Serial.print(h);
  Serial.print(",");

  // finalmente, el caracter que indica final de envio

  Serial.println("|"); 

}

// vim:filetype=c








