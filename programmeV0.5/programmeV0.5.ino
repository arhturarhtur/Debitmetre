//V0 programme de base pour detecter les pulse du débitmètre
const byte debitmetre=D5;                           // broche utilisée pour déclencher l'interruption 
volatile long nbPulse = 0;                     // compteur d'impulsions
long NombreDimpulsions = 0;
float debit;
unsigned long tempsAncien = 0;
const int NbImpulsionsDebitmetre = 1000;

void ICACHE_RAM_ATTR comptage() {
  nbPulse++;
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
if((millis() - tempsAncien) > 1000) // Calcule le débit toutes les 1 secondes environ
  {
    byte pulses;
    unsigned long time;
    // Désactive les interruptions
    noInterrupts();
    // Récupère les valeurs pour le calcul
    pulses = nbPulse;
    nbPulse = 0;
    time = millis();
    // Réactive les interruptions
    interrupts();
        
    // 1 pulse = 1L
    // L/min
    debit = 60000.0 / (time - tempsAncien) * pulses / NbImpulsionsDebitmetre;

    tempsAncien = time;
    Serial.print("débit : ");
    Serial.println(debit);
  }
}
