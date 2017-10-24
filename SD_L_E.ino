/* LISTE DE COURSES
 *  Exercice du cours "Perfectionnez-vous dans la programmation Arduino" des Jean-Noël Rousseau
 *  sur Open Classroom
 *  Ce travail est libre de droit
 *  Commencé le 24/10/2017 - Terminé le ...
 */

#include <SPI.h>
#include <SD.h> 
File monFichier;
boolean messageOK = 1;

void setup() {
  Serial.begin(9600);
  message("Initialisation");
  if(!SD.begin(4)) {
    message("Communication impossible");
    return;
  }
  message("Communication etablie");
}

void loop() {
  
}

void message(String s) {
  if (messageOK) {
    Serial.println(s);
  }
}

