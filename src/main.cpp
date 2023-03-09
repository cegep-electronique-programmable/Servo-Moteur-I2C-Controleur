#include <mbed.h>

#define ADDRESSE_I2C_PAR_DEFAUT 0x23

I2C i2c(I2C_SDA, I2C_SCL);

int main() {
  printf("Début du programme\r\n");
  const int addr8bit = ADDRESSE_I2C_PAR_DEFAUT << 1;

  char cmd[1];
  char message[10];

  while(1) {
    for (int i = 0; i < 0x100; i++) {
      cmd[0] = i;
      i2c.write(addr8bit, cmd, 1);
      printf("Envoi de %d à l'adresse %d.\r\n", i, addr8bit);
      ThisThread::sleep_for(500ms);
    }

    //cmd[0] = 45; // Envoyer le moteur à la position 45°
    //i2c.write(addr8bit, cmd, 1);

    //ThisThread::sleep_for(1000);

    //i2c.read(addr8bit, message, sizeof(message));
    //printf("Message reçu: %s", message);

    //ThisThread::sleep_for(1000);
  }
}