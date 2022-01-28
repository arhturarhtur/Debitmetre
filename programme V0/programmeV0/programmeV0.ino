//V0 programme de base pour detecter les pulse du débitmètre
const byte debitmetre=D5;                           // broche utilisée pour déclencher l'interruption 
volatile long nbPulse = 0;                     // compteur d'impulsions
long NombreDimpulsions = 0;

void ICACHE_RAM_ATTR comptage() {
  nbPulse++;
  Serial.println("pulse");
}

void setup() {
  // Serial port for debugging purposes
  Serial.begin(115200);
  
  // Broche du débitmètre en INPUT_PULLUP
  pinMode(debitmetre, INPUT_PULLUP);
  // Mettre la broche du débimetre en interrupt, assignation de la fonction comptage et réglage en FALLING (NPN)
  attachInterrupt(digitalPinToInterrupt(debitmetre), comptage, FALLING);
}

void loop() {
NombreDimpulsions=nbPulse;    // utilisation du compteur
  Serial.print("Nombre d'impulsions : ");
  Serial.println(NombreDimpulsions);
}
