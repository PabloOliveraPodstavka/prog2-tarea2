/*
  Módulo de definición de `uso_cadenas'.

  Se definen funciones sobre cadenas.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#ifndef _USO_LISTAS_H
#define _USO_LISTAS_H

#include "utils.hpp"
#include "texto.hpp"
#include "info.hpp"
#include "cadena.hpp"

/*
  Devuelve `true' si en `cad' hay un elemento cuyo dato numérico es `i',
  o `false` en otro caso.
 */
bool pertenece(int i, cadena cad);

/*  Devuelve la cantidad de elementos de `cad'. */
nat longitud(cadena cad);

/*  Devuelve la cantidad de elementos de `cad' cuyo dato numérico es `i'. */
nat cantidad(int i, cadena cad);


/*
  Devuelve `true' si y sólo si los datos numéricos de los elementos de `l1'
  son iguales uno a uno con los de los elementos de `l2' (es decir, son los
  mismos números y en el mismo orden).
  Si es_vacia_cadena(l1) y es_vacia_cadena(l2) devuelve `true'.
 */
bool son_numeros_iguales(cadena l1, cadena l2);

/*
  Devuelve `true' si y sólo si `cad' está ordenada de forma no decreciente
  (= creciente de manera no estricta) según  los datos numéricos de sus
  elementos.
  Si es_vacia_cadena (cad), devuelve `true'.
 */
bool esta_ordenada(cadena cad);

/*
  Devuelve el resultado de concatenar `l2' después de `l1'.
  La cadena resultado no comparte memoria ni con `l1' ni con `l2'.
 */
cadena concatenar(cadena l1, cadena l2);

/*
  Devuelve la cadena que tiene todos los elementos de `cad' pero en orden
  inverso.
  La cadena resultado no comparte memoria con `cad'.
 */
cadena reversa(cadena cad);

/*
  Devuelve el localizador que accede al primer elemento, empezando desde el
  inicio de `cad' y anterior a `loc', cuyo dato numérico es mayor que el del
  elemento que se accede desde `loc'.
  Si ninguno de los elementos anteriores es mayor devuelve `loc'.
  Precondición: ! es_vacia_cadena (cad), pertenece_localizador_cadena (loc, cad)
  y `cad' está ordenada de manera creciente (no estricta) según su dato
  numérico desde el inicio hasta el anterior a `loc'.
 */
localizador primer_mayor(localizador loc, cadena cad);

/*
  Mueve el elemento al que se accede con `loc' dejéndolo inmediatamente antes
  de los elementos cuyos datos numéricos son mayores que dicho elemento.
  El valor de `loc' queda ideterminado.
  Si el dato numérico de `loc' es mayor o igual que el los de los que lo
  preceden no hace nada.
  Precondición: ! es_vacia_cadena (cad), pertenece_localizador_cadena (loc, cad)
  y `cad' está ordenada de manera creciente (no estricta) según su dato
  numérico desde el inicio hasta el anterior a `loc'.
 */
void retroceder(localizador loc, cadena &cad);

/*
  Se ordena `cad' de manera creciente según los datos numéricos de sus
  elementos.
  Si los datos numéricos de dos elementos son iguales, se mantiene el orden
  relativo que tenían dichos elementos inicialmente.
  No se debe obtener ni devolver memoria de manera dinámica.
  Si es_vacia_cadena (cad) no hace nada.
 */
void ordenar(cadena &cad);

/*
  Elimina los elementos con datos numéricos repetidos, conservando el primero
  de ellos.
  Libera la memoria de los elementos que elimina.
  Precondición: esta_ordenada (cad).
 */
void unificar(cadena &cad);

/*
  Devuelve una cadena con todos los elementos de `l1' y `l2' ordenada de manera
  creciente segun sus datos numéricos.
  Si hay elementos cuyos datos numéricos son iguales, los elementos de `l1'
  quedan antes de los de `l2'.
  La cadena resultado no comparte memoria ni con `l1' ni con `l2'.
  Precondición: esta_ordenada (l1) y esta_ordenada (l2).
 */
cadena mezcla(cadena l1, cadena l2);

/*
  Cambia todas las ocurrencias de `original' por `nuevo' en los elementos
   de `cad'. No debe quedar memoria inaccesible.
 */
void cambiar_todos(int original, int nuevo, cadena &cad);

/*
  Devuelve una cadena con los elementos que cumplen
  "numero_info (elemento) criterio clave".
  El orden relativo de los elementos en la cadena resultado debe ser el mismo
  que en `cad`.
  Si es_vacia_cadena (cad), `clave` y `criterio` son ignorados, y se devuelve la
  cadena vacía.
  La cadena resultado no comparte memoria con `cad`.
 */
cadena filtrado(int clave, comp_t criterio, cadena cad);

/*
  Devuelve la cadena de elementos de `cad' que cumplen
  "menor <= numero_info (elemento) <= mayor".
  El orden relativo de los elementos en la cadena resultado debe ser el mismo
  que en `cad'.
  La cadena resultado no comparte memoria con `cad'.
  Precondición: esta_ordenada (cad), `menor' <= `mayor',
  pertenece (menor, cad), pertenece (mayor, cad).
 */
cadena subcadena(nat menor, nat mayor, cadena cad);

#endif
