/* LISTE DE COURSES
 *  Exercice du cours "Perfectionnez-vous dans la programmation Arduino" des Jean-Noël Rousseau
 *  sur Open Classroom
 *  Licence : GNU General public V3
 *  Commencé le 24/10/2017 - Terminé le ...
 */

#include <SPI.h>
#include <SD.h> 
File monFichier;            // Variable pour le nom du fichier
boolean messageOK = 0;      // Switch pour le message de debogage

void setup() {
  Serial.begin(9600);
  message("Initialisation");
  if(!SD.begin(4)) {        //teste la communication avec la carte (pin 4)
    message("Communication impossible");
    return;
  }
  message("Communication etablie");
}

void loop() {
  // Lire depuis le moniteur serie
  while (!Serial.available()) {}
  char c;                       // Vairable pour lire le caractere en cour
  char mot[30] = {0};           // table pour stocker les mots
  byte cpt = 0;                 // Compteur
  while (Serial.available()) {  // Tan qu'il y a des caractère en attente
    c = Serial.read();
    mot[cpt] = c;
    delay(10);
    cpt++;
  }
  tri(mot);                     // Envoie vers une fonction de tri
}

void tri(char mot[30]) {        // Fonction de tri
  if (mot[0] == '/') {          // Si le mot commence par /, c'est une commande
    commandes(mot);
    return;
  }
  ecriture(mot);                // Sinon, c'est un item à ajouter à la liste
}

void commandes(char mot[30]) {  // Execution des commandes
  message("Commande...");
  String commande = mot;
  message(commande);
  if (commande == "/liste") { // Afficher la liste
    lecture();
    return;
  }
  if (commande == "/efface") {  // Effacer le fichier
    effacer();
    return;
  }
  if (commande == "/compte") {  // Compter le nombre d'item (de ligne).
    compter();
    return;
  }
  Serial.println("Commande inconnue !");
}

void ecriture(char mot[30]) {   // fonction d'ecriture dans le fichier liste.ard
  if (!(monFichier = SD.open("liste.ard", FILE_WRITE))) { // test et touverture du fichier
    message("Erreur fichier");
    return;
  }
  message("Ecriture dans le fichier");
  for (int i = 0; i < 30; i++) {
    if (mot[i] == '\0') {   // Si on atteint la fin de chaine de caractere
      monFichier.print('\n'); // ON remplce le caractere NULL par uen sauf de ligne
      monFichier.close();     // ON ferme le fichier
      message("Fichier clos");
      Serial.println();     // Ajoout de saut de ligne sur le moniteur
      return;
    }
    monFichier.print(mot[i]); // Sinon, on écrit le mot caractere par caractere
    Serial.print(mot[i]);     // et on l'affiche sur la moniteur
  }
}

void lecture() {            // fonction de lectrure du fichier liste.ard
  message("Commande Lecture");
  if (!(monFichier = SD.open("liste.ard", FILE_READ))) { // test et touverture du fichier
    message("Erreur fichier");
    return;
  }
  message("Ouverture du fichier");
  char c = 0;
  while (c != -1) {         // Tant qu'on a pas atteint la fin du fichier
    c = monFichier.read();  // on lit les caractere
    Serial.print(c);        // et on les affiche sur le moniteur
  }
  monFichier.close();       // Sinon, on ferme le fichier
  message("Fichier clos");
}

void effacer() {            // Fonction d'effacement du fichier
  message("commande effacer");
  if (SD.exists("liste.ard")) { // si le fichier existe
    SD.remove("liste.ard");     // on l'efface
    Serial.println("Liste effacee");
    return;
  }
  Serial.print("Fichier inexistant"); // sinon on signale une erreur
}

void compter() {            // Fcontion de comptage des items
  message("Commande compter");
    if (!(monFichier = SD.open("liste.ard", FILE_READ))) { // test et touverture du fichier
    message("Erreur fichier");
    return;
  }
  message("Ouverture du fichier");
  char c = 0;
  int cpt = 0;
  while (c != -1) {         // tant qu'on a pas attaint la fin du fichier
    c = monFichier.read();  // ON lit les caractère un à un
    if (c == '\n') cpt++;   // Si on rencontre un saut de ligne, on compte un item
  }
  Serial.print("Il y a "); Serial.print(cpt); Serial.println(" articles dans la liste.");
  monFichier.close();
  message("Fichier clos");
}

void message(String s) {  // affichage des message de debogage
  if (messageOK) {
    Serial.println(s);
  }
}


