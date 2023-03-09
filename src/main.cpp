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

  while(1) {
      for (int i = 0; i < 0x100; i++) {
          cmd[0] = i;
          i2c.write(adresse_i2c_8bits, cmd, 1);
          printf("Envoi de %d a l'adresse 0x%02X sur 8 bits (ou 0x%02X en 7 bits).\r\n", cmd[0], adresse_i2c_8bits, adresse_i2c_7bits);
          ThisThread::sleep_for(200ms);

          //i2c.read(adresse_i2c_8bits, message, sizeof(message));
          printf("Reception du message %s de l'adresse 0x%02X sur 8 bits (ou 0x%02X en 7 bits).\r\n", message, adresse_i2c_8bits, adresse_i2c_7bits);
          ThisThread::sleep_for(200ms);
      }
  }


  while(1) {
    for (int i = 0; i < 0x100; i++) {
      cmd[0] = i;
      
      i2c.write(0, cmd, 1);
      printf("Envoi de %d à l'adresse 0x00.\r\n", i);
      ThisThread::sleep_for(500ms);

      i2c.write(i, cmd, 1);
      printf("Envoi de %d à l'adresse 0x%2X.\r\n", i, i);
      ThisThread::sleep_for(500ms);

      i2c.read(i, message, sizeof(message));
      printf("Message reçu: %s", message);
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