#include <msp430.h>

unsigned char tableau[500];  // déclaration d'un tableau de variables de taille 500



int main( void )
{
  // Stop watchdog timer to prevent time out reset

    int compteur;

  WDTCTL = WDTPW + WDTHOLD;

for (compteur=0; compteur<500; compteur++)
{
  tableau[compteur] = compteur;
}


  while(1);
}
