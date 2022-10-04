#include <Arduino.h>
#include <KarakuriMotors.h>
#include <KarakuriBluetooth.h>
#include <Actions.h>

Actions Acciones;
KarakuriMotors motors1;
KarakuriBluetooth BTS;

String strT = "";
const char separatorT = ',';
const int dataLengthT = 3;
int datoT[dataLengthT];

int ledState = LOW; 
int ledPin = 2 ;
long max_lenght;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  BTS.Start();
  Acciones.init();
  motors1.setSpeed(0);

  pinMode(ledPin, OUTPUT);
  ledState == LOW;
}

////////////////////////////////////////////////////////////////

void loop()
{
  // put your main code here, to run repeatedly:
  //
  strT = "";
  if (Serial.available())
  {
    strT = Serial.readStringUntil('\n');
    Serial.println(strT);
    for (int i = 0; i < dataLengthT; i++)
    {
      int index = strT.indexOf(separatorT);
      datoT[i] = strT.substring(0, index).toInt();
      strT = strT.substring(index + 1);
    }
    for (int i = 0; i < dataLengthT; i++)
    {
      Serial.printf("Dato %d = %d  ", i, datoT[i]);
    }
    Serial.println(" ");
  }
  switch ((int)datoT[0])
  {
  case 0:
    // El sistema se detiene completamente
    // Serial.println("   ////////////////   STOP ////////////////    ");
    // frenar(1);
    datoT[0] = 0;
    break;
  case 1:
    //Serial.println("Sistema bloques DATOS:   ");
    // Recibe();
    //  Aquí se pone la funcione de movimientos en la cual dependiendo de cual sea selecciona que realiza el carrito
    // act.movimientos((int)dato[1], (int)dato[2]);
    // frenar(10);
    motors1.setSpeed(0);
    datoT[0] = 0;
    break;

  case 2:
    //Serial.println("Sistema bloques DATOS:   ");
    // Recibe();
    //  Aquí se pone la funcione de movimientos en la cual dependiendo de cual sea selecciona que realiza el carrito
    // act.movimientos((int)dato[1], (int)dato[2]);
    // frenar(10);
    Serial.println(datoT[1]);
    motors1.setSpeed(datoT[1]);

    if(datoT[1]>0){motors1.directionM=true;}
    if(datoT[1]<0){motors1.directionM=false;}


    datoT[0] = 0;
    break;

    case 3:
    //Serial.println("Sistema bloques DATOS:   ");
    //bool Status_St=digitalRead(Switch);
    Acciones.home();
    datoT[0] = 0;

    break;


    case 4:
    //Serial.println("Sistema bloques DATOS:   ");
    //bool Status_St=digitalRead(Switch);
    datoT[0] = 0;
    break;

    case 8:
    ledState=LOW;
    digitalWrite(ledPin, ledState);
     datoT[0] = 0;
    break;
    
    case 9:
    max_lenght=datoT[1];
    Serial.print("Longitud Maxima: ");
    Serial.println(max_lenght);

     datoT[0] = 0;
    break;

    case 10:
    Serial.print("Longitud motors1.directionM: ");
    Serial.println(motors1.directionM);
     datoT[0] = 0;
    break;

    default:
    // colocar movimientos pero en cada instante
    Serial.println("Sistema tele operado");
    // act.tele((int)dato[1]);
    datoT[0] = 0;

  }
}