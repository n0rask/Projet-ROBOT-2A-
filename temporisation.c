#include <msp430.h>
#include "temporisation.h"

/* Compteur de temps en millisecondes */
static volatile unsigned long compteur_ms = 0;


/*
 * Initialisation du Timer_A0
 * Une interruption toutes les 1 ms.
 */
void temporisation_init(void)
{
    /* Arret du timer pendant sa configuration */
    TA0CTL = MC_0;

    /* Desactivation de l'interruption du timer */
    TA0CCTL0 = 0;

    /* Remise a zero du compteur logiciel */
    compteur_ms = 0;

    /* Valeur de comparaison : 999 */
    TA0CCR0 = 999;

    /* Autorisation de l'interruption CCR0 */
    TA0CCTL0 = CCIE;

    /* SMCLK, mode UP, remise a zero du timer */
    TA0CTL = TASSEL_2 | MC_1 | TACLR;
}


/*
 * Routine d'interruption du Timer_A0
 * Appelee toutes les millisecondes
 */
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A0_CCR0_ISR(void)
{
    compteur_ms++;
}


unsigned long temporisation_get_ms(void)
{
    unsigned long temps;
    unsigned int interruptions_actives;

    /* Memorisation de l'etat des interruptions */
    interruptions_actives = __get_SR_register() & GIE;

    /* Protection pendant la lecture */
    __disable_interrupt();

    temps = compteur_ms;

    /* Retablissement de l'etat precedent */
    if (interruptions_actives)
    {
        __enable_interrupt();
    }

    return temps;
}


/*
 * Verifie si une duree est ecoulee depuis un instant donne.
 */
int temporisation_ecoulee(unsigned long debut, unsigned long duree)
{
    unsigned long maintenant;

    maintenant = temporisation_get_ms();

    if ((maintenant - debut) >= duree)
    {
        return 1;
    }

    return 0;
}