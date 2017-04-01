/*
  Módulo de definición de `cadena'.

  Lista doblemente enlazada de elementos de tipo `info_t', con cabezal con
  punteros al inicio y al final.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#ifndef _LISTA_H
#define _LISTA_H

#include "info.hpp"

/*
  Las variables de tipo localizador permiten acceder a los elementos en las
  estructuras que los contienen. En el caso de una cadena enlazada esas
  variables son punteros a los nodos.
 */
struct nodo; // representación de `localizador', definida en `cadena.cpp'.
typedef nodo *localizador;

struct rep_cadena; // representación de `cadena', definida en `cadena.cpp'.
typedef rep_cadena *cadena;

/* Constructoras */

/*  Devuelve la cadena vacía (sin elementos). */
cadena crear_cadena();

/*
  Se inserta `i' como un nuevo elemento inmediatamente antes de `loc'.
  Si es_vacia_cadena (cad), entonces `loc' es ignorado e `i' se inserta como
  unico elemento de `cad'.
  Precondición: es_vacia_cadena(cad) o localizador_pertenece_a_cadena(loc, cad).
 */
void insertar_antes(info_t i, localizador loc, cadena &cad);

/*
  Se inserta `i' como un nuevo elemento inmediatamente después de `loc'.
  Si es_vacia_cadena(cad), entonces `loc' es ignorado e `i' se inserta como
  unico elemento de `cad'.
  Precondición: es_vacia_cadena(cad) o localizador_pertenece_a_cadena(loc, cad).
 */
void insertar_despues(info_t i, localizador loc, cadena &cad);

/*
  Devuelve una cadena con los elementos de `cad' que se encuentran entre
  `desde' y `hasta', inclusive.
  La cadena resultado no comparte memoria con `cad'.
  Si es_vacia_cadena(cad) devuelve la cadena vacia.
  Precondición: es_vacia_cadena(cad) o precede_cadena(desde, hasta, cad).
 */
cadena segmento_cadena(localizador desde, localizador hasta, cadena cad);

/*
  Se inserta la cadena `sgm' inmediatamente después de `loc' en `cad',
  manteniendo los elementos originales y el orden relativo entre ellos.
  No se debe obtener memoria (los nodos de `sgm' pasan a ser parte de `cad').
  Al terminar, `sgm' queda vacía.
  Si es_vacia_cadena(cad), `loc' es ignorado y el segmento queda insertado.
  Precondición: es_vacia_cadena(cad) o localizador_pertenece_a_cadena(loc, cad).
 */
void insertar_segmento_despues(cadena &sgm, localizador loc, cadena &cad);

/*
  Devuelve una cadena con los elementos de `cad' que se encuentran
  entre `desde' y `hasta', inclusive. Ademas, quita de `cad' dichos elementos,
  manteniendo el orden de los restantes.
  Si es_vacia_cadena(cad), devuelve la cadena vacía.
  No se debe obtener ni devolver memoria de nodos ni de elementos.
  La cadena resultado no comparte memoria con `l'.
  Los valores de `desde' y `hasta' quedan indeterminados.
  Precondición: es_vacia_cadena(cad) o precede_cadena(desde, hasta, cad).
 */
cadena separar_segmento(localizador desde, localizador hasta, cadena &cad);

/* Destructoras */

/*
  Se quita el elemento referenciado en `loc' y se libera la memoria asignada
  al mismo y al nodo apuntado por el localizador.
  Si es_vacia_cadena(cad), `loc' es ignorado y no se hace nada.
  El valor de `loc' queda indeterminado.
  Precondición: es_vacia_cadena(cad) o localizador_pertenece_a_cadena(loc, cad).
 */
void remover_de_cadena(localizador &loc, cadena &cad);

/*  Libera la memoria asignada a `cad' y la de todos sus elementos. */
void liberar_cadena(cadena &cad);

/* Predicados */

/* Devuelve `true' si y sólo si `cad' es vacía (no tiene elementos). */
bool es_vacia_cadena(cadena cad);

/*
  Devuelve `true' si y sólo si `loc' es un localizador válido.
  En cadenas enlazadas un localizador no es válido si es `NULL'.
*/
bool es_localizador_cadena(localizador loc);

/*
  Devuelve `true' si y sólo si con `loc' se accede a  un elemento de `cad'.
  Precondición: ! es_vacia_cadena(cad).
 */
bool localizador_pertenece_a_cadena(localizador loc, cadena cad);

/*
  Devuelve `true' si y sólo si `loc1' es igual o precede a `loc2` en `cad`.
  Precondición: localizador_pertenece_a_cadena(loc1, cad) y
    localizador_pertenece_a_cadena(loc2, cad).
 */
bool precede_en_cadena(localizador loc1, localizador loc2, cadena cad);

/*
  Devuelve `true' si y sólo si con `loc' se accede al primer elemento de `cad'.
  Precondición: ! es_vacia_cadena (cad).
 */
bool es_inicio_cadena(localizador loc, cadena cad);

/*
  Devuelve `true' si y sólo si con `loc' se accede al último elemento de `cad'.
  Precondición: ! es_vacia_cadena (cad).
 */
bool es_final_cadena(localizador loc, cadena cad);

/* Posicionamiento */

/*
  Devuelve el localizador con el que se accede al inicio de `cad`.
  Si es_vacia_cadena(cad) devuelve un localizador no válido.
 */
localizador inicio_cadena(cadena cad);

/*
  Devuelve el localizador con el que se accede al final de `cad'.
  Si es_vacia_cadena(cad) devuelve un localizador no válido.
 */
localizador final_cadena(cadena cad);

/*
  Devuelve el localizador con el que se accede al elemento de `cad'
  inmediatamente  siguiente a `loc'.
  Si es_final_cadena(loc, cad), devuelve un localizador no válido.
  Precondición: ! es_vacia_cadena(l) y localizador_pertenece_a_cadena(loc, cad).
 */
localizador siguiente(localizador loc, cadena cad);

/*
  Devuelve el localizador con el que se accede al elemento de `cad'
  inmediatamente  anterior a `loc'.
  Si es_inicio_cadena(loc, cad), devuelve un localizador no válido.
  Precondición: ! es_vacia_cadena(l) y localizador_pertenece_a_cadena(loc, cad).
 */
localizador anterior(localizador loc, cadena cad);

/*
  Devuelve el primer localizador con el que se accede a un elemento cuyo dato
  numérico es igual a `clave', buscando desde `loc' (inclusive) hacia el final
  de `cad'.
  Si no se encuentra o `cad' es vacía, devuelve un localizador no válido.
  Precondición: es_vacia_cadena(cad) o localizador_pertenece_a_cadena(loc, cad).
 */
localizador siguiente_clave(int clave, localizador loc, cadena cad);

/*
  Devuelve el primer localizador con el que se accede a un elemento cuyo dato
  numérico es igual a `clave', buscando desde `loc' (inclusive) hacia el inicio
  de `cad'.
  Si no se encuentra o `cad' es vacia, devuelve un localizador no válido.
  Precondición: es_vacia_cadena(cad) o localizador_pertenece_a_cadena(loc, cad).
 */
localizador anterior_clave(int clave, localizador loc, cadena cad);

/*
  Devuelve el localizador con el que se accede al elemento cuyo dato numérico
  es el menor en el segmento que va desde `loc' hasta el final_cadena(cad).
  Si hay más de un elemento cuyo valor es el menor, el resultado accede al que
  precede a los otros.
  Precondición: ! es_vacia_cadena(cad) y localizador_pertenece_a_cadena(loc,
  cad).
 */
localizador menor_en_cadena(localizador loc, cadena cad);

/* Selectoras */

/*
  Devuelve el elemento de `cad' al que se accede con `loc'.
  Precondición: ! es_vacia_cadena(cad) y localizador_pertenece_a_cadena(loc,
  cad).
 */
info_t info_cadena(localizador loc, cadena cad);

/* Modificadoras */

/*
  Sustituye con `i' el elemento de `cad' al que se accede con `loc'.
  No destruye el elemento al que antes se accedía con `loc'.
  Precondición: ! es_vacia_cadena(cad) y localizador_pertenece_a_cadena(loc,
  cad).
 */
void cambiar_en_cadena(info_t i, localizador loc, cadena &cad);

/*
  Intercambia los elementos a los que se accede con `loc1' y `loc2'.
  `loc1' y `loc2' mantienen su relación de precedencia.
  Precondición: ! es_vacia_cadena (cad)
  y localizador_pertenece_a_cadena (loc1, cad)
  y localizador_pertenece_a_cadena (loc2, cad).
 */
void intercambiar(localizador loc1, localizador loc2, cadena &cad);

/*
  Mueve el elemento al que se accede con `loc2' dejándolo inmediatamente antes
  de `loc1'.
  Los valores de `loc1' y `loc2' quedan indeterminados.
  Si loc1 == loc2 no hace nada.
  Precondición: ! es_vacia_cadena (cad)
  y localizador_pertenece_a_cadena (loc1, cad)
  y localizador_pertenece_a_cadena (loc2, cad).
 */
void mover_antes(localizador loc1, localizador loc2, cadena &cad);

/* Salida */
/*
  Imprime los elementos de `cad` de la siguiente forma:
  (dn de pos1,dt de pos1)(dn de pos2,dt de pos2)(dn de pos3,dt de pos3) ...
  donce `dn` es el dato numérico y `dt` es el dato de texto.
  Antes de terminar, se debe imprimir un fin de linea.
  Si es_vacia_cadena(cad) solo se imprime el fin de línea.
 */
void imprimir_cadena(cadena cad);

#endif
