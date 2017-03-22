/* 4424601 - 5015357
  Módulo de implementación de 'uso_cadenas'.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#include "../include/utils.hpp"
#include "../include/texto.hpp"
#include "../include/info.hpp"
#include "../include/cadena.hpp"
#include "../include/uso_cadena.hpp"

bool esta_ordenada(cadena cad) {
  bool res = true;
  if (!es_vacia_cadena(cad)) {
    localizador loc = inicio_cadena(cad);
    while (res && es_localizador_cadena(siguiente(loc, cad))) {
      localizador sig_loc = siguiente(loc, cad);
      if (numero_info(info_cadena(loc, cad)) >
          numero_info(info_cadena(sig_loc, cad)))
        res = false;
      else
        loc = siguiente(loc, cad);
    }
  }
  return res;
}

void retroceder(localizador loc, cadena &cad) {
  localizador pto_ins = primer_mayor(loc, cad);
  mover_antes(pto_ins, loc, cad);
}

void unificar(cadena &cad) {
  if (!es_vacia_cadena(cad)) {
    localizador loc = inicio_cadena(cad);
    // se cumplen las precondiciones de `siguiente`
    localizador sig_loc = siguiente(loc, cad);

    while (es_localizador_cadena(sig_loc)) {
      if (numero_info(info_cadena(loc, cad)) ==
          numero_info(info_cadena(sig_loc, cad)))
        remover_de_cadena(sig_loc, cad);
      else
        loc = sig_loc;
      sig_loc = siguiente(loc, cad);
    }
  }
}

void cambiar_todos(int original, int nuevo, cadena &cad) {
  localizador loc = inicio_cadena(cad);
  while (es_localizador_cadena(loc)) {
    if (numero_info(info_cadena(loc, cad)) == original) {
      info_t info = info_cadena(loc, cad);
      info_t nueva_info = crear_info(nuevo, copiar_texto(texto_info(info)));
      cambiar_en_cadena(nueva_info, loc, cad);
      // libera la info que no libera cambiar_en_cadena
      liberar_info(info);
    }
    loc = siguiente(loc, cad);
  }
}

/*
bool pertenece(int i, cadena cad) {
}

nat longitud(cadena cad) {
}

nat cantidad(int i, cadena cad) {
}

bool son_numeros_iguales(cadena l1, cadena l2) {
}

cadena concatenar(cadena l1, cadena l2) {
}

cadena reversa(cadena cad) {
}

localizador primer_mayor(localizador loc, cadena cad) {
}

void ordenar(cadena &cad) {
}

cadena mezcla(cadena l1, cadena l2) {
}

cadena filtrado(int clave, comp_t criterio, cadena cad) {
}

cadena subcadena(nat menor, nat mayor, cadena cad) {
}

*/
