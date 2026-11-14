#ifndef TEMPORISATION_H
#define TEMPORISATION_H

/* Initialise le Timer_A0 */
void temporisation_init(void);

/* Renvoie le temps ecoule depuis l'initialisation, en ms */
unsigned long temporisation_get_ms(void);

/* Renvoie 1 si la duree est ecoulee depuis "debut", sinon revoie 0 */
int temporisation_ecoulee(unsigned long debut, unsigned long duree);

#endif