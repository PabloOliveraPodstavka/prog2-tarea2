/*
  Módulo de implementación de 'cadena'.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#include "../include/cadena.hpp"
#include "../include/texto.hpp"
#include "../include/info.hpp"

#include <stddef.h>

// nodo con punteros al anterior y al siguiente
struct nodo {
  info_t dato;
  nodo *anterior;
  nodo *siguiente;
};

// cadena implementada con cabecera con punteros al incio y al final
struct rep_cadena {
  nodo *inicio;
  nodo *final;
};

cadena crear_cadena() {
  // se obtiene espacio para la cabecera
  // la cadena vacía no es NULL
  cadena res = new rep_cadena;
  res->inicio = res->final = NULL;
  return res;
}
/*
localizador inicio_cadena(cadena cad) {}

localizador final_cadena(cadena cad) {}

bool es_vacia_cadena(cadena cad) {}

bool es_inicio_cadena(localizador loc, cadena cad) {}

bool es_final_cadena(localizador loc, cadena cad) {}

localizador siguiente(localizador loc, cadena cad) {}

localizador anterior(localizador loc, cadena cad) {}*/

bool es_localizador_cadena(localizador loc) { return loc != NULL; }

bool localizador_pertenece_a_cadena(localizador loc, cadena cad) {
  bool res = false;
  localizador cursor = inicio_cadena(cad);
  while ((!res) && (es_localizador_cadena(cursor))) {
    if (cursor == loc)
      res = true;
    else
      cursor = siguiente(cursor, cad);
  }
  return res;
}

//bool precede_en_cadena(localizador l1, localizador l2, cadena cad) {}

void insertar_antes(info_t i, localizador loc, cadena &cad) {
  nodo *nuevo = new nodo;
  nuevo->dato = i;
  if (es_vacia_cadena(cad)) {
    // nuevo es el único nodo, por lo que es el inicio y el final
    cad->inicio = cad->final = nuevo;
    nuevo->anterior = nuevo->siguiente = NULL;
  } else {
    nuevo->siguiente = loc;
    nuevo->anterior = anterior(loc, cad);
    loc->anterior = nuevo;

    if (loc == inicio_cadena(cad))
      cad->inicio = nuevo;
    else
      nuevo->anterior->siguiente = nuevo;
  }
}

/*void insertar_despues(info_t i, localizador loc, cadena &cad) {}

void remover_de_cadena(localizador &loc, cadena &cad) {}

void liberar_cadena(cadena &cad) {}*/

cadena segmento_cadena(localizador desde, localizador hasta, cadena cad) {
  cadena res = crear_cadena();
  if (!es_vacia_cadena(cad)) {
    localizador loc = desde;
    while (loc != siguiente(hasta, cad)) {
      // ERROR: compartiría memoria
      // info_t info = loc->dato;

      // ERROR: compartiría memoria
      // info_t info = crear_info(numero_info(loc->dato),
      // texto_info(loc->dato));

      info_t info = crear_info(numero_info(loc->dato),
                               copiar_texto(texto_info(loc->dato)));
      insertar_despues(info, final_cadena(res), res);
      loc = siguiente(loc, cad);
    }
  }
  return res;
}

/*void insertar_segmento_despues(cadena &sgm, localizador loc, cadena &cad) {}

cadena separar_segmento(localizador desde, localizador hasta, cadena &cad) {}*/

localizador siguiente_clave(int clave, localizador loc, cadena cad) {
  if (es_vacia_cadena(cad))
    return NULL;
  else {
    while (es_localizador_cadena(loc) && numero_info(loc->dato) != clave)
      loc = siguiente(loc, cad);

    return loc;
  }
}

/*localizador anterior_clave(int clave, localizador loc, cadena cad) {}

localizador menor_en_cadena(localizador loc, cadena cad) {}

info_t info_cadena(localizador loc, cadena cad) {}

void cambiar_en_cadena(info_t i, localizador loc, cadena &cad) {}

void intercambiar(localizador loc1, localizador loc2, cadena &cad) {}*/

void mover_antes(localizador loc1, localizador loc2, cadena &cad) {
  // En esta versión no se solicita memoria para crear nodos, sino que
  // se mueve todo el nodo que es accedido con `loc2`.
  if (loc1 != loc2) {
    // La creación de una cadena requiere espacio para la cabecera que habrá
    // que liberar al final.
    cadena sgm = separar_segmento(loc2, loc2, cad);

    // El segemento (de un elemento) se inserta antes de `loc1`.
    // Es lo que se haría si existiera la funcióm insertar_segmento_antes
    // excepto en que acá no es necesario contemplar el caso en que la cadena
    // es vacía ya que se sabe que loc1 != loc2
    sgm->inicio->anterior = anterior(loc1, cad);
    sgm->final->siguiente = loc1;
    if (es_inicio_cadena(loc1, cad)) {
      cad->inicio = inicio_cadena(sgm);
    } else {
      loc1->anterior->siguiente = inicio_cadena(sgm);
    }
    loc1->anterior = final_cadena(sgm);

    // Se libera la memoria de la cabecera de la cadena, ya vacía.
    delete sgm;
  }
}

/*void imprimir_cadena(cadena cad) {}*/
