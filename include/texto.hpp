/*
  Módulo de definición de `texto'.

  `texto_t' es un puntero a una estructura (opaca, que debe definirse en
  texto.cpp) cuyo contenido es un texto (arreglo de elementos de tipo char).

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#ifndef _TEXTO_H
#define _TEXTO_H

#include "utils.hpp"

/* Longitud máxima de los textos. */
const nat TXT_MAX_LNG = 80;

/* representación de `texto', definida en texto.cpp */
struct rep_texto;

/* El tipo `texto_t' es un puntero a elementos de tipo `rep_texto'. */
typedef rep_texto *texto_t;

/* **************  NUEVO  ************** */

/*
  Devuelve el resultado de convertir el contenido de `t` en comp_t.
  Precondición: el contenido de `t` es `<`, `=` o `>`.
 */
comp_t texto_a_comp(texto_t txt);

/*  Devuelve un `texto' cuyo contenido es nulo (de longitud 0). */
texto_t texto_nulo();

/*  Devuelve un `texto' cuyo contenido es `simbolo'. */
texto_t char_a_texto(char simbolo);

/* **************************  NOMBRE CAMBIADO  **************************
 **************  En la tarea 1 se llamaba cadena_a_texto  ************** */
/*
  Devuelve un `texto' cuyo contenido es una copia de `array'.
  Precondición: la longitud de `array' no es mayor a TXT_MAX_LNG.
 */
texto_t array_a_texto(const char *array);

/*
  Devuelve un `texto' leído desde la entrada estándar luego de ignorar los
  espacios en blanco iniciales.
  Lee hasta encontrar un espacio en blanco.
  Precondición: la longitud de la palabra no es mayor a TXT_MAX_LNG.
 */
texto_t leer_palabra();

/*
  Devuelve un `texto' leído desde la entrada estándar.
  Lee hasta encontrar el carácter de `fin de línea' o de `fin de archivo'.
  Ese carácter es leído pero no se incluye en el `texto' devuelto.
  Precondición: la longitud del resto de la línea no es mayor a TXT_MAX_LNG.
 */
texto_t leer_resto_linea();

/*  Escribe en la salida estándar el contenido de `t'. */
void escribir_texto(texto_t t);

/*
  Inserta en la salida estándar `nueva línea' (inserta una línea y mueve el
  cursor a la primera columna de la línea insertada).
 */
void escribir_nueva_linea();

/*
  Devuelve un `texto' cuyo contenido es la concatenación de las copias de
  los de `t1' y `t2'.
  Si la suma de las longitudes de `t1' y `t2' es mayor a TXT_MAX_LNG
  se concatenan los primeros caracteres de `t2' hasta completar TXT_MAX_LNG.
 */
texto_t concatenar_texto(texto_t t1, texto_t t2);

/*  Devuelve un `texto' cuyo contenido es una copia del de `t'. */
texto_t copiar_texto(texto_t t);

/*  Devuelve `true' si y sólo si `t' es nulo. */
bool es_texto_nulo(texto_t t);

/*  Devuelve la longitud del contenido de `t'. */
nat longitud_texto(texto_t t);

/*
  Devuelve el resultado de la comparación lexicográfica de los contenidos de
  `t1' y `t2'.
 */
comp_t comparar_texto(texto_t t1, texto_t t2);

/*  Devuelve el resultado de convertir el contenido de `t' en un entero. */
int texto_a_int(texto_t t);

/* Devuelve el resultado de convertir `i' a texto_t. */
texto_t int_a_texto(int i);

/*  Libera la memoria asignada a `t'. */
void liberar_texto(texto_t &t);

#endif
