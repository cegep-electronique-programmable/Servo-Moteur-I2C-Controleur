#include <mbed.h>

#define ADDRESSE_I2C_PAR_DEFAUT 0x23

I2C i2c(I2C_SDA, I2C_SCL);

DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);
DigitalOut led4(LED4);


int main() {
  printf("Début du programme\r\n");

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