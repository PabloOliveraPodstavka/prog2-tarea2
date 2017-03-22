/* 4424601 - 5015357
  Módulo de implementación de `texto'.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#include "../include/utils.hpp"
#include "../include/texto.hpp"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*
  Aquí se define la representación de `rep_texto'.
  Por lo tanto, `texto_t', por ser un puntero a un elemento de tipo `rep_texto',
  es un puntero a un registro con un array de caracteres y un natural que
  representa la longitud del texto representado.
 */
struct rep_texto {
  char caracteres[TXT_MAX_LNG + 1];
  nat longitud;
};

comp_t texto_a_comp(texto_t txt) {
  // el texto tiene longitud 1
  assert(txt->caracteres[1] == '\0');
  // el único símbolo es un operador de comparación
  assert((txt->caracteres[0] == '<') || (txt->caracteres[0] == '=') ||
         (txt->caracteres[0] == '>'));

  comp_t res;
  if (strcmp(txt->caracteres, "<") == 0)
    res = menor;
  else if (strcmp(txt->caracteres, ">") == 0)
    res = mayor;
  else
    res = igual;
  return res;
}

texto_t texto_nulo() {
  /* El resultado es de tipo `texto_t' que es un puntero a un elemento de tipo
     `rep_texto'. Por lo tanto se necesita pedir memoria. */
  texto_t res = new rep_texto;
  res->caracteres[0] = '\0';
  res->longitud = 0;
  return res;
}

texto_t char_a_texto(char simbolo) {
  texto_t res = new rep_texto;

  /* El índice del array donde está el primer elemento es el 0. */
  res->caracteres[0] = simbolo;
  /* El fin de un string se representa con el símbolo '\0'. Las funciones de la
     biblioteca string.h buecan este símbolo para determinar donde termina un
     string. */
  res->caracteres[1] = '\0';
  res->longitud = 1;
  return res;
}

texto_t array_a_texto(const char *array) {
  texto_t res = new rep_texto;
  strncpy(res->caracteres, array, TXT_MAX_LNG);
  res->longitud = strlen(res->caracteres);
  assert(res->longitud == strlen(array));
  assert(res->longitud <= TXT_MAX_LNG);
  return res;
}

texto_t leer_palabra() {
  texto_t res = new rep_texto;
  scanf("%s", res->caracteres);
  res->longitud = strlen(res->caracteres);
  assert(res->longitud <= TXT_MAX_LNG);
  return res;
}

texto_t leer_resto_linea() {
  texto_t res = new rep_texto;

  /* stdin es la entrada estándar.
     fgets lee `max - 1' caracteres o hasta enconrtrar el fin de línea (o fin
     de archivo) y los almacena en `res->caracteres'.
     Ver http://www.cplusplus.com/reference/cstdio/fgets/ */
  fgets(res->caracteres, TXT_MAX_LNG, stdin);

  /* Se sustituye el carácter de fin de linea ('\n') por el de fin de cadena. */
  res->caracteres[strlen(res->caracteres) - 1] = '\0';
  res->longitud = strlen(res->caracteres);
  assert(res->longitud <= TXT_MAX_LNG);
  return res;
}

void escribir_texto(texto_t t) { fputs(t->caracteres, stdout); }

void escribir_nueva_linea() { fputs("\n", stdout); }

texto_t concatenar_texto(texto_t t1, texto_t t2) {
  texto_t res = copiar_texto(t1);
  strncat(res->caracteres, t2->caracteres, TXT_MAX_LNG - res->longitud);
  res->longitud = strlen(res->caracteres);
  assert(res->longitud <= TXT_MAX_LNG);
  return res;
}

texto_t copiar_texto(texto_t t) {
  texto_t res = new rep_texto;
  strcpy(res->caracteres, t->caracteres);
  res->longitud = strlen(res->caracteres);
  assert(res->longitud == strlen(t->caracteres));
  assert(res->longitud <= TXT_MAX_LNG);
  return res;
}

bool es_texto_nulo(texto_t t) { return t->longitud == 0; }

nat longitud_texto(texto_t t) { return t->longitud; }

comp_t comparar_texto(texto_t t1, texto_t t2) {
  comp_t res;
  int rint = strcmp(t1->caracteres, t2->caracteres);
  if (rint < 0) {
    res = menor;
  } else if (rint == 0) {
    res = igual;
  } else {
    res = mayor;
  }
  return res;
}

int texto_a_int(texto_t t) { return (nat)atoi(t->caracteres); }

texto_t int_a_texto(int i) {
  texto_t res = new rep_texto;
  /* Se "imprime" `i' en el array `res->caracteres'. */
  res->longitud = sprintf(res->caracteres, "%d", i);
  /*  Un elemento de tipo int requiere un máximo de 11 caracteres cuando se lo
     representa en notación decimal, por lo que un array de tamaño
     `TXT_MAX_LNG + 1' es suficiente. */
  assert((res->longitud > 0) && (res->longitud < TXT_MAX_LNG));
  assert(res->caracteres[res->longitud] == '\0');
  return res;
}

void liberar_texto(texto_t &t) {
  /* Se libera la memoria pedida para `t', por ejemplo
     texto_t res = new rep_texto;  */
  delete t;
}
