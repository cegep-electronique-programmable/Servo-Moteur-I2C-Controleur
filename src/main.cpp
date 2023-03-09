#include <mbed.h>

#define ADDRESSE_I2C_PAR_DEFAUT 0x23

I2C i2c(I2C_SDA, I2C_SCL);

DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);
DigitalOut led4(LED4);

int main() {
  printf("Debut du programme\r\n");

  led1 = 1;
  led2 = 0;
  led3 = 0;
  led4 = 0;
  ThisThread::sleep_for(200ms);

  led1 = 0;
  led2 = 1;
  led3 = 0;
  led4 = 0;
  ThisThread::sleep_for(200ms);

  led1 = 0;
  led2 = 0;
  led3 = 1;
  led4 = 0;
  ThisThread::sleep_for(200ms);

  led1 = 0;
  led2 = 0;
  led3 = 0;
  led4 = 1;
  ThisThread::sleep_for(200ms);

  led1 = 0;
  led2 = 0;
  led3 = 0;
  led4 = 0;

  const int adresse_i2c_7bits = 0x23;
  const int adresse_i2c_8bits = adresse_i2c_7bits << 1; // Nécessairement pair

  char cmd[1];
  char message[10];

  // On utilise la valeur 125 pour faire une lecture I2C
  int8_t sequence_moteur[] = {127, 126, -90, 125, -45, 45, 0, 125, 90, 120, 125, 0, 127, 125};

  while(1) {

      // Pour chaque position du moteur
      for (uint8_t i = 0; i < sizeof(sequence_moteur); i++) {
          if (sequence_moteur[i] == 125) {
              // On lit la position du moteur
              //i2c.read(adresse_i2c_8bits, message, sizeof(message)); // TODO: Bug in slave when reading
              printf("Etat moteur %s.\r\n", message);
          } else {
            // Écrire la position dans un tableau
            cmd[0] = sequence_moteur[i];
            // Envoyer le premier octet du tableau à l'adresse I2C
            i2c.write(adresse_i2c_8bits, cmd, 1);
            printf("Moteur en position %d° a l'adresse 0x%02X sur 8 bits (ou 0x%02X en 7 bits).\r\n", cmd[0], adresse_i2c_8bits, adresse_i2c_7bits);
            ThisThread::sleep_for(1000ms);
          }
      }

  }

  
}