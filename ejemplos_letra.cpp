/*
  Módulo principal ejemplos_letra.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
*/

#include "include/utils.hpp"
#include "include/texto.hpp"
#include "include/info.hpp"
#include "include/cadena.hpp"
#include "include/uso_cadena.hpp"

#include <stddef.h>
#include <stdio.h>

int main() {
  cadena cad, cad2, sgm;
  info_t info;
  localizador loc, loc2;

  // insertar-antes
  printf("insertar_antes. \n");
  // primer ejemplo
  printf("1:");
  cad = crear_cadena();

  info = crear_info(3, array_a_texto("t"));
  loc = inicio_cadena(cad);
  insertar_antes(info, loc, cad);

  imprimir_cadena(cad);
  liberar_cadena(cad);

  // segundo ejemplo
  printf("2:");
  cad = crear_cadena();
  info = crear_info(1, array_a_texto("u"));
  insertar_despues(info, final_cadena(cad), cad);
  info = crear_info(5, array_a_texto("c"));
  insertar_despues(info, final_cadena(cad), cad);
  info = crear_info(2, array_a_texto("d"));
  insertar_despues(info, final_cadena(cad), cad);
  info = crear_info(8, array_a_texto("o"));
  insertar_despues(info, final_cadena(cad), cad);

  info = crear_info(3, array_a_texto("t"));
  loc = inicio_cadena(cad);
  insertar_antes(info, loc, cad);

  imprimir_cadena(cad);
  liberar_cadena(cad);

  // tercer ejemplo
  printf("3:");
  cad = crear_cadena();
  info = crear_info(1, array_a_texto("u"));
  insertar_despues(info, final_cadena(cad), cad);
  info = crear_info(5, array_a_texto("c"));
  insertar_despues(info, final_cadena(cad), cad);
  info = crear_info(2, array_a_texto("d"));
  insertar_despues(info, final_cadena(cad), cad);
  info = crear_info(8, array_a_texto("o"));
  insertar_despues(info, final_cadena(cad), cad);

  info = crear_info(3, array_a_texto("t"));
  loc = anterior(final_cadena(cad), cad);
  insertar_antes(info, loc, cad);

  imprimir_cadena(cad);
  liberar_cadena(cad);

  // remover_de_cadena
  printf("remover_de_cadena. \n");
  // primer ejemplo
  printf("1:");
  cad = crear_cadena();

  loc = inicio_cadena(cad);
  remover_de_cadena(loc, cad);

  imprimir_cadena(cad);
  liberar_cadena(cad);

  // segundo ejemplo
  printf("2:");
  cad = crear_cadena();
  info = crear_info(1, array_a_texto("u"));
  insertar_despues(info, final_cadena(cad), cad);
  info = crear_info(5, array_a_texto("c"));
  insertar_despues(info, final_cadena(cad), cad);
  info = crear_info(2, array_a_texto("d"));
  insertar_despues(info, final_cadena(cad), cad);
  info = crear_info(8, array_a_texto("o"));
  insertar_despues(info, final_cadena(cad), cad);

  loc = inicio_cadena(cad);
  remover_de_cadena(loc, cad);

  imprimir_cadena(cad);
  liberar_cadena(cad);

  // tercer ejemplo
  printf("3:");
  cad = crear_cadena();
  info = crear_info(1, array_a_texto("u"));
  insertar_despues(info, final_cadena(cad), cad);
  info = crear_info(5, array_a_texto("c"));
  insertar_despues(info, final_cadena(cad), cad);
  info = crear_info(2, array_a_texto("d"));
  insertar_despues(info, final_cadena(cad), cad);
  info = crear_info(8, array_a_texto("o"));
  insertar_despues(info, final_cadena(cad), cad);

  loc = final_cadena(cad);
  remover_de_cadena(loc, cad);

  imprimir_cadena(cad);
  liberar_cadena(cad);

  // cuarto ejemplo
  printf("4:");
  cad = crear_cadena();
  info = crear_info(1, array_a_texto("u"));
  insertar_despues(info, final_cadena(cad), cad);
  info = crear_info(5, array_a_texto("c"));
  insertar_despues(info, final_cadena(cad), cad);
  info = crear_info(2, array_a_texto("d"));
  insertar_despues(info, final_cadena(cad), cad);
  info = crear_info(8, array_a_texto("o"));
  insertar_despues(info, final_cadena(cad), cad);

  loc = anterior(final_cadena(cad), cad);
  remover_de_cadena(loc, cad);

  imprimir_cadena(cad);
  liberar_cadena(cad);

  // intercambiar
  printf("intercambiar. \n");
  // primer ejemplo
  printf("1:");
  cad = crear_cadena();
  info = crear_info(1, array_a_texto("u"));
  insertar_despues(info, final_cadena(cad), cad);
  info = crear_info(3, array_a_texto("t"));
  insertar_despues(info, final_cadena(cad), cad);
  info = crear_info(5, array_a_texto("c"));
  insertar_despues(info, final_cadena(cad), cad);
  info = crear_info(9, array_a_texto("n"));
  insertar_despues(info, final_cadena(cad), cad);
  info = crear_info(6, array_a_texto("s"));
  insertar_despues(info, final_cadena(cad), cad);

  loc = siguiente(inicio_cadena(cad), cad);
  loc2 = anterior(final_cadena(cad), cad);
  intercambiar(loc, loc2, cad);

  imprimir_cadena(cad);
  liberar_cadena(cad);

  // siguiente_clave
  printf("siguiente_clave. \n");
  // primer ejemplo
  printf("1:");
  cad = crear_cadena();
  loc = inicio_cadena(cad);
  loc = siguiente_clave(8, loc, cad);
  if (es_localizador_cadena(loc)) {
    texto_t t = info_a_texto(info_cadena(loc, cad));
    escribir_texto(t);
    liberar_texto(t);
  }
  escribir_nueva_linea();
  liberar_cadena(cad);

  // segundo ejemplo
  printf("2:");
  cad = crear_cadena();
  info = crear_info(1, array_a_texto("u"));
  insertar_despues(info, final_cadena(cad), cad);
  info = crear_info(4, array_a_texto("c"));
  insertar_despues(info, final_cadena(cad), cad);
  info = crear_info(2, array_a_texto("d"));
  insertar_despues(info, final_cadena(cad), cad);

  loc = siguiente(inicio_cadena(cad), cad);
  loc = siguiente_clave(3, loc, cad);
  if (es_localizador_cadena(loc)) {
    texto_t t = info_a_texto(info_cadena(loc, cad));
    escribir_texto(t);
    liberar_texto(t);
  }
  escribir_nueva_linea();
  liberar_cadena(cad);

  // tercer ejemplo
  printf("3:");
  cad = crear_cadena();
  info = crear_info(1, array_a_texto("u"));
  insertar_despues(info, final_cadena(cad), cad);
  info = crear_info(4, array_a_texto("c"));
  insertar_despues(info, final_cadena(cad), cad);
  info = crear_info(2, array_a_texto("d"));
  insertar_despues(info, final_cadena(cad), cad);
  info = crear_info(11, array_a_texto("o"));
  insertar_despues(info, final_cadena(cad), cad);
  info = crear_info(9, array_a_texto("n"));
  insertar_despues(info, final_cadena(cad), cad);

  loc = siguiente(inicio_cadena(cad), cad);
  loc = siguiente_clave(11, loc, cad);
  if (es_localizador_cadena(loc)) {
    texto_t t = info_a_texto(info_cadena(loc, cad));
    escribir_texto(t);
    liberar_texto(t);
  }
  escribir_nueva_linea();
  liberar_cadena(cad);

  // separar_segmento
  printf("separar_segmento. \n");
  // primer ejemplo
  printf("1:");
  cad = crear_cadena();
  info = crear_info(1, array_a_texto("u"));
  insertar_despues(info, final_cadena(cad), cad);
  info = crear_info(3, array_a_texto("t"));
  insertar_despues(info, final_cadena(cad), cad);
  info = crear_info(5, array_a_texto("c"));
  insertar_despues(info, final_cadena(cad), cad);
  info = crear_info(9, array_a_texto("n"));
  insertar_despues(info, final_cadena(cad), cad);
  info = crear_info(6, array_a_texto("s"));
  insertar_despues(info, final_cadena(cad), cad);

  loc = inicio_cadena(cad);
  loc2 = anterior(final_cadena(cad), cad);
  sgm = separar_segmento(loc, loc2, cad);

  imprimir_cadena(sgm);
  imprimir_cadena(cad);
  liberar_cadena(cad);
  liberar_cadena(sgm);

  // segundo ejemplo
  printf("2:");
  cad = crear_cadena();
  info = crear_info(1, array_a_texto("u"));
  insertar_despues(info, final_cadena(cad), cad);
  info = crear_info(3, array_a_texto("t"));
  insertar_despues(info, final_cadena(cad), cad);
  info = crear_info(5, array_a_texto("c"));
  insertar_despues(info, final_cadena(cad), cad);
  info = crear_info(9, array_a_texto("n"));
  insertar_despues(info, final_cadena(cad), cad);
  info = crear_info(6, array_a_texto("s"));
  insertar_despues(info, final_cadena(cad), cad);

  loc = siguiente(siguiente(inicio_cadena(cad), cad), cad);
  loc2 = final_cadena(cad);
  sgm = separar_segmento(loc, loc2, cad);

  imprimir_cadena(sgm);
  imprimir_cadena(cad);
  liberar_cadena(cad);
  liberar_cadena(sgm);

  // tercer ejemplo
  printf("3:");
  cad = crear_cadena();
  info = crear_info(1, array_a_texto("u"));
  insertar_despues(info, final_cadena(cad), cad);
  info = crear_info(3, array_a_texto("t"));
  insertar_despues(info, final_cadena(cad), cad);
  info = crear_info(5, array_a_texto("c"));
  insertar_despues(info, final_cadena(cad), cad);
  info = crear_info(9, array_a_texto("n"));
  insertar_despues(info, final_cadena(cad), cad);
  info = crear_info(6, array_a_texto("s"));
  insertar_despues(info, final_cadena(cad), cad);

  loc = siguiente(inicio_cadena(cad), cad);
  loc2 = anterior(final_cadena(cad), cad);
  sgm = separar_segmento(loc, loc2, cad);

  imprimir_cadena(sgm);
  imprimir_cadena(cad);
  liberar_cadena(cad);
  liberar_cadena(sgm);

  // reversa
  printf("reversa. \n");
  // primer ejemplo
  printf("1:");
  cad = crear_cadena();

  sgm = reversa(cad);

  imprimir_cadena(sgm);
  liberar_cadena(cad);
  liberar_cadena(sgm);

  // segundo ejemplo
  printf("2:");
  cad = crear_cadena();
  info = crear_info(1, array_a_texto("u"));
  insertar_despues(info, final_cadena(cad), cad);
  info = crear_info(3, array_a_texto("t"));
  insertar_despues(info, final_cadena(cad), cad);
  info = crear_info(5, array_a_texto("c"));
  insertar_despues(info, final_cadena(cad), cad);
  info = crear_info(9, array_a_texto("n"));
  insertar_despues(info, final_cadena(cad), cad);
  info = crear_info(6, array_a_texto("s"));
  insertar_despues(info, final_cadena(cad), cad);

  sgm = reversa(cad);

  imprimir_cadena(sgm);
  liberar_cadena(cad);
  liberar_cadena(sgm);

  // retroceder
  printf("retroceder. \n");
  // primer ejemplo
  printf("1:");
  cad = crear_cadena();
  info = crear_info(1, array_a_texto("u"));
  insertar_despues(info, final_cadena(cad), cad);
  info = crear_info(3, array_a_texto("t"));
  insertar_despues(info, final_cadena(cad), cad);
  info = crear_info(5, array_a_texto("c"));
  insertar_despues(info, final_cadena(cad), cad);
  info = crear_info(9, array_a_texto("n"));
  insertar_despues(info, final_cadena(cad), cad);
  info = crear_info(6, array_a_texto("s"));
  insertar_despues(info, final_cadena(cad), cad);

  loc = inicio_cadena(cad);
  retroceder(loc, cad);

  imprimir_cadena(cad);
  liberar_cadena(cad);

  // segundo ejemplo
  printf("2:");
  cad = crear_cadena();
  info = crear_info(1, array_a_texto("u"));
  insertar_despues(info, final_cadena(cad), cad);
  info = crear_info(3, array_a_texto("t"));
  insertar_despues(info, final_cadena(cad), cad);
  info = crear_info(5, array_a_texto("c"));
  insertar_despues(info, final_cadena(cad), cad);
  info = crear_info(9, array_a_texto("n"));
  insertar_despues(info, final_cadena(cad), cad);
  info = crear_info(6, array_a_texto("s"));
  insertar_despues(info, final_cadena(cad), cad);

  loc = final_cadena(cad);
  retroceder(loc, cad);

  imprimir_cadena(cad);
  liberar_cadena(cad);

  // tercer ejemplo
  printf("3:");
  cad = crear_cadena();
  info = crear_info(3, array_a_texto("t"));
  insertar_despues(info, final_cadena(cad), cad);
  info = crear_info(5, array_a_texto("c"));
  insertar_despues(info, final_cadena(cad), cad);
  info = crear_info(9, array_a_texto("n"));
  insertar_despues(info, final_cadena(cad), cad);
  info = crear_info(1, array_a_texto("u"));
  insertar_despues(info, final_cadena(cad), cad);
  info = crear_info(6, array_a_texto("s"));
  insertar_despues(info, final_cadena(cad), cad);

  loc = anterior(final_cadena(cad), cad);
  retroceder(loc, cad);

  imprimir_cadena(cad);
  liberar_cadena(cad);

  // unificar
  printf("unificar. \n");
  // primer ejemplo
  printf("1:");
  cad = crear_cadena();
  info = crear_info(1, array_a_texto("u"));
  insertar_despues(info, final_cadena(cad), cad);
  info = crear_info(3, array_a_texto("t"));
  insertar_despues(info, final_cadena(cad), cad);
  info = crear_info(5, array_a_texto("c"));
  insertar_despues(info, final_cadena(cad), cad);
  info = crear_info(6, array_a_texto("s"));
  insertar_despues(info, final_cadena(cad), cad);

  unificar(cad);

  imprimir_cadena(cad);
  liberar_cadena(cad);

  // segundo ejemplo
  printf("2:");
  cad = crear_cadena();
  info = crear_info(1, array_a_texto("u"));
  insertar_despues(info, final_cadena(cad), cad);
  info = crear_info(3, array_a_texto("t"));
  insertar_despues(info, final_cadena(cad), cad);
  info = crear_info(5, array_a_texto("c"));
  insertar_despues(info, final_cadena(cad), cad);
  info = crear_info(5, array_a_texto("b"));
  insertar_despues(info, final_cadena(cad), cad);
  info = crear_info(6, array_a_texto("s"));
  insertar_despues(info, final_cadena(cad), cad);

  unificar(cad);

  imprimir_cadena(cad);
  liberar_cadena(cad);

  // tercer ejemplo
  printf("3:");
  cad = crear_cadena();
  info = crear_info(1, array_a_texto("e"));
  insertar_despues(info, final_cadena(cad), cad);
  info = crear_info(1, array_a_texto("b"));
  insertar_despues(info, final_cadena(cad), cad);
  info = crear_info(1, array_a_texto("c"));
  insertar_despues(info, final_cadena(cad), cad);
  info = crear_info(1, array_a_texto("d"));
  insertar_despues(info, final_cadena(cad), cad);
  info = crear_info(1, array_a_texto("a"));
  insertar_despues(info, final_cadena(cad), cad);

  unificar(cad);

  imprimir_cadena(cad);
  liberar_cadena(cad);

  // mezcla
  printf("mezcla. \n");
  // primer ejemplo
  printf("1:");
  cad = crear_cadena();
  cad2 = crear_cadena();

  sgm = mezcla(cad, cad2);

  imprimir_cadena(sgm);
  liberar_cadena(cad);
  liberar_cadena(cad2);
  liberar_cadena(sgm);

  // segundo ejemplo
  printf("2:");
  cad = crear_cadena();
  cad2 = crear_cadena();
  info = crear_info(1, array_a_texto("d"));
  insertar_despues(info, final_cadena(cad2), cad2);
  info = crear_info(2, array_a_texto("b"));
  insertar_despues(info, final_cadena(cad2), cad2);
  info = crear_info(7, array_a_texto("c"));
  insertar_despues(info, final_cadena(cad2), cad2);

  sgm = mezcla(cad, cad2);

  imprimir_cadena(sgm);
  liberar_cadena(cad);
  liberar_cadena(cad2);
  liberar_cadena(sgm);

  // tercer ejemplo
  printf("3:");
  cad = crear_cadena();
  info = crear_info(1, array_a_texto("a"));
  insertar_despues(info, final_cadena(cad), cad);
  info = crear_info(2, array_a_texto("j"));
  insertar_despues(info, final_cadena(cad), cad);
  info = crear_info(3, array_a_texto("r"));
  insertar_despues(info, final_cadena(cad), cad);
  cad2 = crear_cadena();
  info = crear_info(1, array_a_texto("d"));
  insertar_despues(info, final_cadena(cad2), cad2);
  info = crear_info(2, array_a_texto("b"));
  insertar_despues(info, final_cadena(cad2), cad2);
  info = crear_info(7, array_a_texto("c"));
  insertar_despues(info, final_cadena(cad2), cad2);

  sgm = mezcla(cad, cad2);

  imprimir_cadena(sgm);
  liberar_cadena(cad);
  liberar_cadena(cad2);
  liberar_cadena(sgm);

  // filtrado
  printf("filtrado. \n");
  // primer ejemplo
  printf("1:");
  cad = crear_cadena();
  info = crear_info(7, array_a_texto("c"));
  insertar_despues(info, final_cadena(cad), cad);
  info = crear_info(1, array_a_texto("a"));
  insertar_despues(info, final_cadena(cad), cad);
  info = crear_info(2, array_a_texto("b"));
  insertar_despues(info, final_cadena(cad), cad);

  sgm = filtrado(2, menor, cad);

  imprimir_cadena(sgm);
  liberar_cadena(cad);
  liberar_cadena(sgm);

  // segundo ejemplo
  printf("2:");
  cad = crear_cadena();
  info = crear_info(7, array_a_texto("c"));
  insertar_despues(info, final_cadena(cad), cad);
  info = crear_info(1, array_a_texto("a"));
  insertar_despues(info, final_cadena(cad), cad);
  info = crear_info(2, array_a_texto("b"));
  insertar_despues(info, final_cadena(cad), cad);

  sgm = filtrado(8, igual, cad);

  imprimir_cadena(sgm);
  liberar_cadena(cad);
  liberar_cadena(sgm);

  // tercer ejemplo
  printf("3:");
  cad = crear_cadena();
  info = crear_info(7, array_a_texto("c"));
  insertar_despues(info, final_cadena(cad), cad);
  info = crear_info(1, array_a_texto("a"));
  insertar_despues(info, final_cadena(cad), cad);
  info = crear_info(2, array_a_texto("b"));
  insertar_despues(info, final_cadena(cad), cad);

  sgm = filtrado(1, mayor, cad);

  imprimir_cadena(sgm);
  liberar_cadena(cad);
  liberar_cadena(sgm);

  // subcadena
  printf("subcadena. \n");
  // primer ejemplo
  printf("1:");
  cad = crear_cadena();
  info = crear_info(1, array_a_texto("a"));
  insertar_despues(info, final_cadena(cad), cad);
  info = crear_info(2, array_a_texto("b"));
  insertar_despues(info, final_cadena(cad), cad);
  info = crear_info(7, array_a_texto("c"));
  insertar_despues(info, final_cadena(cad), cad);

  sgm = subcadena(1, 2, cad);

  imprimir_cadena(sgm);
  liberar_cadena(cad);
  liberar_cadena(sgm);

  // segundo ejemplo
  printf("2:");
  cad = crear_cadena();
  info = crear_info(1, array_a_texto("a"));
  insertar_despues(info, final_cadena(cad), cad);
  info = crear_info(2, array_a_texto("b"));
  insertar_despues(info, final_cadena(cad), cad);
  info = crear_info(3, array_a_texto("a"));
  insertar_despues(info, final_cadena(cad), cad);
  info = crear_info(3, array_a_texto("c"));
  insertar_despues(info, final_cadena(cad), cad);
  info = crear_info(3, array_a_texto("b"));
  insertar_despues(info, final_cadena(cad), cad);
  info = crear_info(7, array_a_texto("c"));
  insertar_despues(info, final_cadena(cad), cad);

  sgm = subcadena(3, 7, cad);

  imprimir_cadena(sgm);
  liberar_cadena(cad);
  liberar_cadena(sgm);

  return 0;
}
