/*
   Proyecto hiper simple para mandar un tweet a trav√s de la Arduino Yun

   Jorge Gomez / Sindormir.net 
    jorge@sindormir.net 2014
     
    Una vez enviado el tweet el programa se mantendra parpadeando.

    Licencia GPLv3

*/


#include <Bridge.h>
#include <Temboo.h>

#include "secrets.h"    //Fichero que contiene los tokens secretos de Temboo y de Twitter

void setup() {
  pinMode(13, OUTPUT);
  Bridge.begin();
}

void loop() {
  unsigned int tiempo;
  
  String tweetText("Saludos desde Medialab Madrid - Cantina");

  TembooChoreo StatusesUpdateChoreo;  // Instancia para mandar unTWEET

  StatusesUpdateChoreo.begin(); // Llamamos al cliente de Temboo

  // Establecemos credenciales de Temboo
  StatusesUpdateChoreo.setAccountName(TEMBOO_ACCOUNT);
  StatusesUpdateChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
  StatusesUpdateChoreo.setAppKey(TEMBOO_APP_KEY);

  // Twitter API library
  StatusesUpdateChoreo.setChoreo("/Library/Twitter/Tweets/StatusesUpdate");

  // Credenciales de Twitter
  StatusesUpdateChoreo.addInput("AccessToken", TWITTER_ACCESS_TOKEN);
  StatusesUpdateChoreo.addInput("AccessTokenSecret", TWITTER_ACCESS_TOKEN_SECRET);
  StatusesUpdateChoreo.addInput("ConsumerKey", TWITTER_CONSUMER_KEY);
  StatusesUpdateChoreo.addInput("ConsumerSecret", TWITTER_CONSUMER_SECRET);

  // Mensaje a enviar
  StatusesUpdateChoreo.addInput("StatusUpdate", tweetText);

  //Ejecutamos y comprobamos salida
  if (!StatusesUpdateChoreo.run()) tiempo=500;
  else tiempo=50;
  
  //Cerramos conexion
  StatusesUpdateChoreo.close();

  //Indicamos con el led si ha ido bien o no y no hacemos nada mas
  while (1) {
    digitalWrite(13, HIGH);
    delay(tiempo);
    digitalWrite(13, LOW);
    delay(tiempo);
  }

}











