/* 4424601 - 5015357
  Módulo de implementación de 'utils'.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#include "../include/utils.hpp"

#include <stdio.h>

void imprimir_comp(comp_t comp) {
  switch (comp) {
  case menor: {
    printf("<");
    /* En general, debe usarse break para evitar que siga procesando los otros
       casos. */
    break;
  }
  case igual: {
    printf("=");
    break;
  }
  case mayor: {
    printf(">");
    break;
  }
  }
} // imprimir_comp
