/* LISTE DE COURSES
 *  Exercice du cours "Perfectionnez-vous dans la programmation Arduino" des Jean-Noël Rousseau
 *  sur Open Classroom
 *  Licence : GNU General public V3
 *  Commencé le 24/10/2017 - Terminé le ...
 */

#include <SPI.h>
#include <SD.h> 
File monFichier;
boolean messageOK = 1;

void setup() {
  Serial.begin(9600);
  message("Initialisation");
  if(!SD.begin(4)) { //teste la communication avec la carte(pin 4)
    message("Communication impossible");
    return;
  }
  message("Communication etablie");
}

void loop() {
  // Lire depuis le moniteur serie
  char c;
  while (Serial.available()) {
    c = Serial.read();
    Serial.print(c);
    delay(10);
    tri(c); // Envoyer chaque caractère vers une fonction de tri et de mise en forme
  }
  ecriture(); // Mettre à jour le fichier
}

void message(String s) { // affichage des message de debogage
  if (messageOK) {
    Serial.println(s);
  }
}

void tri(char c) { // fonction de tri et de mise en forme des entrees
  if (char(c) == 47) { // pour l'execution d'une commande
    commandes(); // demande l'execution de la commande
  } 
}

void ecriture() { // fonction d'ecriture dans le fichier liste.ard
  
}

void lecture() { // fonction de lectrure du fichier liste.ard
  
}

void commandes() { // Execution des commandes
  char c;
  while (Serial.available()) {
  c = Serial.read();
  Serial.println("Commande "); Serial.print(c);
  delay(10);
  }
}

