#include <mbed.h>

#define ADDRESSE_I2C_PAR_DEFAUT 0x23
#define COMMANDE_ALLUMER_MOTEUR 126
#define COMMANDE_ETEINDRE_MOTEUR 127
#define COMMANDE_LIRE_POSITION_MOTEUR 125

I2C i2c(I2C_SDA, I2C_SCL);

DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);
DigitalOut led4(LED4);

void sequence_led_demarrage()
{
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
}

int main()
{

    printf("\r\n\r\n=== Debut du programme Servo-Moteur-I2C (Controleur) ===\r\n");

    sequence_led_demarrage();

    const int adresse_i2c_7bits = ADDRESSE_I2C_PAR_DEFAUT;
    const int adresse_i2c_8bits = adresse_i2c_7bits << 1; // Nécessairement pair

    char cmd[1];
    char message[10];

    // On utilise la valeur 125 pour faire une lecture I2C
    int8_t sequence_moteur[] = {
        COMMANDE_ETEINDRE_MOTEUR,
        COMMANDE_LIRE_POSITION_MOTEUR,
        COMMANDE_ALLUMER_MOTEUR,
        COMMANDE_LIRE_POSITION_MOTEUR,
        -90,
        COMMANDE_LIRE_POSITION_MOTEUR,
        -45,
        0,
        COMMANDE_LIRE_POSITION_MOTEUR,
        45,
        90,
        45,
        COMMANDE_LIRE_POSITION_MOTEUR,
        0,
        -45,
        -90};

    while (1)
    {
        // Pour chaque position du moteur
        for (uint8_t i = 0; i < sizeof(sequence_moteur); i++)
        {
            switch (sequence_moteur[i])
            {
            case COMMANDE_ALLUMER_MOTEUR:
                // Demande demarrage moteur
                cmd[0] = sequence_moteur[i];
                // Envoyer le premier octet du tableau à l'adresse I2C
                if (i2c.write(adresse_i2c_8bits, cmd, 1))
                {
                    printf("=  Erreur d'ecriture I2C !\r\n");
                }
                else
                {
                    printf("=> Demande demarrage moteur.\r\n");
                }
                break;

            case COMMANDE_ETEINDRE_MOTEUR:
                // Demande arret moteur
                cmd[0] = sequence_moteur[i];
                // Envoyer le premier octet du tableau à l'adresse I2C
                if (i2c.write(adresse_i2c_8bits, cmd, 1))
                {
                    printf("=  Erreur d'ecriture I2C !\r\n");
                }
                else
                {
                    printf("=> Demande arret moteur.\r\n");
                }
                break;

            case COMMANDE_LIRE_POSITION_MOTEUR:
                // On lit la position du moteur (utiliser la meme taille pour le buffer du peripherique)
                if (i2c.read(adresse_i2c_8bits, message, sizeof(message)))
                {
                    printf("=  Erreur de lecture I2C !\r\n");
                }
                else
                {
                    printf("=> Demande etat moteur\r\n");
                    printf("<= %s.\r\n", message);
                }

                // On vide le tableau
                for (uint8_t j = 0; j < sizeof(message); j++)
                {
                    message[j] = 0;
                }
                break;

            default:
                // Écrire la position dans un tableau
                cmd[0] = sequence_moteur[i];
                // Envoyer le premier octet du tableau à l'adresse I2C
                if (i2c.write(adresse_i2c_8bits, cmd, 1))
                {
                    printf("Erreur d'ecriture I2C.\r\n");
                }
                else
                {
                    printf("=> Moteur en position %d°.\r\n", (int8_t)cmd[0]);
                }
                break;
            }

            ThisThread::sleep_for(1000ms);
            printf("\r\n");
        }
    }
}