#include <mbed.h>

#define ADDRESSE_I2C_PAR_DEFAUT 0x23

I2C i2c(I2C_SDA, I2C_SCL);

int main() {

  const int addr8bit = ADDRESSE_I2C_PAR_DEFAUT << 1;

  char cmd[1];
  char message[10];

  while(1) {
    cmd[0] = 127; // Démarrer le moteur
    i2c.write(addr8bit, cmd, 1);

    cmd[0] = 45; // Envoyer le moteur à la position 45°
    i2c.write(addr8bit, cmd, 1);

    ThisThread::sleep_for(1000);

    i2c.read(addr8bit, message, sizeof(message));
    printf("Message reçu: %s", message);

    ThisThread::sleep_for(1000);
  }
}