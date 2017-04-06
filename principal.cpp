/*
  Módulo principal de la tarea 2.

Intérprete de comandos para probar los módulos.

Está definida una cadena `cad'.

Cada comando tiene un nombre y una cadena (posiblemente vacía) de parámetros.
Se asume que los comandos están bien formados. Esto implica que:
- el nombre es uno de los descritos más abajo;
- la cantidad y tipo de los parámetros cumplen con lo requerido;
- se cumplen las precondiciones de las operaciones invocadas.

Si un parámetro debe ser de tipo info_t su formato cumple con lo descrito en
`info_a_texto' del módulo `info', con el agregado de que no puede incluir el
 símbolo ')'.
Una secuencia de elementos de un tipo es terminada por un espacio en blanco
seguido de un punto.

Descripción de los comandos:

Fin
   Termina el programa
# comentario
   Imprime nueva línea.
insertar_cadena secuencia_info_t .
   Inserta en `cad' cada elemento de la secuencia leída.
insertar_antes clave1 info_t2 .
  Inserta en `cad' el elemento info_t2 antes del primer elemento (buscado desde
el comienzo)
  cuya clave sea igual a clave1.
  Ejemplo:
    Construída la cadena: (16,marzo) (27,abril) (13,abril)
    Ejecutar 'insertar_antes 27 (20,julio) .'
    generará la cadena (16,marzo) (20,julio) (27,abril) (13,abril)
insertar_despues clave1 info_t2 .
  Inserta en `cad' el elemento info_t2 luego del primer elemento (buscado desde
el comienzo)
  cuya clave sea igual a clave1.
  Ejemplo:
    Construída la cadena: (16,marzo) (27,abril) (13,abril)
    Ejecutar 'insertar_despues 27 (20,julio) .'
    generará la cadena (16,marzo) (27,abril) (20,julio) (13,abril)
insertar_comienzo info_t1 .
  Inserta en `cad' el elemento info_t1 antes del elemento inicial.
  Ejemplo:
    Construída la cadena: (16,marzo) (27,abril) (13,abril)
    Ejecutar 'insertar_comienzo (20,julio) .'
    generará la cadena (20,julio) (16,marzo) (27,abril) (13,abril)
insertar_final info_t1 .
  Inserta en `cad' el elemento info_t1 después del elemento final.
  Ejemplo:
    Construída la cadena: (16,marzo) (27,abril) (13,abril)
    Ejecutar 'insertar_final (20,julio) .'
    generará la cadena (16,marzo) (27,abril) (13,abril) (20,julio)
recorrido
   recorre `cad' imprimiendo sus elementos.
segmentos clave1 clave2
   manipula la subcadena de `cad` desde la primera aparición de `clave1` hasta
   la última aparición de `clave2`, donde `clave1` y `clave2` son enteros.
modificar_cadena clave1 clave2
   modifica `cad', utilizando las apariciones de los enteros `clave1' y
   `clave2'.
intercambiar clave1 clave2
  Intercambia los elementos info_t que correspondan con las claves clave1 y
clave2.
  Los elementos a intercambiar serán la primera aparición en la cadena que
correspondan con las claves,
  desde el comienzo de la cadena.
  Ejemplo:
    Construída la cadena: (16,marzo) (27,abril) (13,abril) (27,agosto)
    Ejecutar 'intercambiar 27 13'
    generará la cadena (16,marzo) (13,abril) (27,abril) (27,agosto)
retroceder clave1
  Retrocede el elemento de clave 'clave1' que corresponde con la primera
aparición en la cadena buscando
  desde el comienzo.
  Ejemplo:
    Construída la cadena: (16,marzo) (27,abril) (13,abril) (27,agosto)
    Ejecutar 'retroceder 13'
    generará la cadena (13,abril) (16,marzo) (27,abril) (27,agosto)
concatenar secuencia_info_t.
  Concatena `cad' con la cadena formada por secuencia_info_t. El resultado no
comparte memoria con cad.
subcadena clave1 clave2.
  Genera una cadena nueva con los valores de `cad' que se encuentran entre
`clave1' y `clave2' inclusive.
  `cad' debe estar ordenada, `clave1' y `clave2' deben pertenecer a `cad' y
`clave1' debe ser menor a `clave2'.
ordenar_cadena
   realiza algunas operaciones sobre `cad'.
filtrado_cadena clave criterio
   realiza algunas operaciones sobre `cad' con el entero `clave' y `criterio'.
reversa_cadena dato1 dato2
   realiza algunas operaciones sobre `cad' con los enteros `dato1' y `dato2'.
liberar_cadena
   libera la memoria asignada a `cad' y la vuelve a crear.
test_memoria iteraciones memoria
   hace `iteraciones' llamadas a funciones que deben liberar memoria.
   El parámetro `memoria' es el límite superior de la memoria que debe ser
   usada.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
*/

#include "include/utils.hpp"
#include "include/texto.hpp"
#include "include/info.hpp"
#include "include/cadena.hpp"
#include "include/uso_cadena.hpp"

#define MAX_RESTO_LINEA 200
#define MAX_LARGO_PALABRA 83

// mensajes
const texto_t msg_fin = array_a_texto("Fin.");
const texto_t msg_cmd_no_reconocido = array_a_texto("Comando no reconocido.");
const texto_t msg_elemento_no_encontrado =
    array_a_texto("Elemento no encontrado.");

const texto_t prompt = char_a_texto('>');

/* Estructura para identificar el nombre de comando */
enum enum_cmd_t {
  cmd_fin,
  cmd_comentario,
  cmd_ins_cadena_antes,
  cmd_ins_cadena_despues,
  cmd_ins_cadena_comienzo,
  cmd_ins_cadena_final,
  cmd_intercambiar,
  cmd_retroceder,
  cmd_concatenar,
  cmd_subcadena,
  cmd_ins_cadena,
  cmd_recorrido_cadena,
  cmd_segmentos_cadena,
  cmd_modificar_cadena,
  cmd_ordenar_cadena,
  cmd_filtrado_cadena,
  cmd_reversa_cadena,
  cmd_liberar_cadena,
  cmd_test_memoria,
  no_reconocido
};
const nat cant_com = no_reconocido;

struct enum_nombre_cmd {
  const enum_cmd_t enum_cmd;
  const char *nombre_cmd;
};

/* Asociación entre nombre de comando y enumerado. */
const enum_nombre_cmd cmds[] = {{cmd_fin, "Fin"},
                                {cmd_comentario, "#"},
                                {cmd_ins_cadena_antes, "insertar_antes"},
                                {cmd_ins_cadena_despues, "insertar_despues"},
                                {cmd_ins_cadena_comienzo, "insertar_comienzo"},
                                {cmd_ins_cadena_final, "insertar_final"},
                                {cmd_intercambiar, "intercambiar"},
                                {cmd_retroceder, "retroceder"},
                                {cmd_concatenar, "concatenar"},
                                {cmd_subcadena, "subcadena"},
                                {cmd_ins_cadena, "insertar_cadena"},
                                {cmd_recorrido_cadena, "recorrido"},
                                {cmd_segmentos_cadena, "segmentos"},
                                {cmd_modificar_cadena, "modificar_cadena"},
                                {cmd_ordenar_cadena, "ordenar_cadena"},
                                {cmd_filtrado_cadena, "filtrado_cadena"},
                                {cmd_reversa_cadena, "reversa_cadena"},
                                {cmd_liberar_cadena, "liberar_cadena"},
                                {cmd_test_memoria, "test_memoria"}};

/* Devuelve el identificador de comando leido desde la entrada estándar. */
enum_cmd_t identificador_comando() {
  enum_cmd_t res = no_reconocido;
  texto_t nom_com = leer_palabra();

  bool encontrado = false;
  nat i = cmd_fin; // = 0
  while ((!encontrado) && (i < cant_com)) {
    texto_t nom_item = array_a_texto(cmds[i].nombre_cmd);
    if (igual == comparar_texto(nom_com, nom_item)) {
      res = cmds[i].enum_cmd;
      encontrado = true;
    } else {
      i++;
    }
    liberar_texto(nom_item);
  }
  liberar_texto(nom_com);
  return res;
} // identificador_comando

/* Incrementa el contador de comandos y muestra el prompt. */
void mostrar_prompt(nat &cont_comandos) {
  cont_comandos++;
  texto_t cont_com_txt = int_a_texto(cont_comandos);
  escribir_texto(cont_com_txt);
  escribir_texto(prompt);
  liberar_texto(cont_com_txt);
} // mostrar_prompt

/*
  Lee desde la entrada estándar un texto y devuelve su conversión a entero.
 */
int leer_int() {
  texto_t txt_int = leer_palabra();
  int res = texto_a_int(txt_int);
  liberar_texto(txt_int);
  return res;
} // leer_int

/* Imprime `txt' seguido de nueva línea. */
void imprimir_con_nl(texto_t txt) {
  escribir_texto(txt);
  escribir_nueva_linea();
} // imprimir_con_nl

/* Imprime `n' seguido de nueva línea. */
void imprimir_int(int n) {
  texto_t txt_int = int_a_texto(n);
  imprimir_con_nl(txt_int);
  liberar_texto(txt_int);
} // imprimir_int

void imprimir_info(info_t i) {
  texto_t txt = info_a_texto(i);
  escribir_texto(txt);
  liberar_texto(txt);
} // imprimir_info

/*
  Lee una cadena de info_t desde la entrada estándar. Después de cada elemento
  hay un espacio en blanco. Termina con un punto.
 */
cadena leer_cadena() {
  cadena res = crear_cadena();
  info_t info = leer_info(MAX_LARGO_PALABRA);
  while (es_valida_info(info)) {
    insertar_despues(info, final_cadena(res), res);
    info = leer_info(MAX_LARGO_PALABRA);
  }
  liberar_info(info);
  return res;
} // leer_cadena

void test_memoria(int iteraciones) {
  for (int i = 0; i < iteraciones; i++) {
    cadena cad1 = crear_cadena(), cad2 = crear_cadena(), cad3;
    insertar_antes(crear_info(2, array_a_texto("b")), inicio_cadena(cad1),
                   cad1);
    insertar_antes(crear_info(3, array_a_texto("a")), inicio_cadena(cad1),
                   cad1);
    insertar_despues(crear_info(1, array_a_texto("c")), final_cadena(cad1),
                     cad1);
    imprimir_cadena(cad1);
    mover_antes(inicio_cadena(cad1), final_cadena(cad1), cad1);
    localizador loc = inicio_cadena(cad1);
    remover_de_cadena(loc, cad1);
    cambiar_todos(2, 4, cad1);
    insertar_antes(crear_info(9, array_a_texto("z")), inicio_cadena(cad2),
                   cad2);
    cad3 = concatenar(cad1, cad2);
    liberar_cadena(cad1);
    liberar_cadena(cad2);
    liberar_cadena(cad3);
  }
} // test_memoria

int main() {
  cadena cad = crear_cadena();

  nat cont_comandos = 0;
  bool salir = false;
  while (!salir) {

    mostrar_prompt(cont_comandos);
    enum_cmd_t enum_com = identificador_comando();

    // procesar el comando
    switch (enum_com) {
    case cmd_fin:
      salir = true;
      imprimir_con_nl(msg_fin);
      break;
    case cmd_comentario:
      escribir_nueva_linea();
      break;
    case cmd_ins_cadena: {
      info_t info = leer_info(MAX_LARGO_PALABRA);
      while (es_valida_info(info)) {
        insertar_despues(info, final_cadena(cad), cad);
        info = leer_info(MAX_LARGO_PALABRA);
      }
      liberar_info(info);
      imprimir_cadena(cad);
      break;
    }
    case cmd_ins_cadena_antes: {
      int clave1 = leer_int();
      info_t info_insertar;
      bool existe = pertenece(clave1, cad);
      if (existe) {
        info_insertar = leer_info(MAX_LARGO_PALABRA);
        insertar_antes(info_insertar,
                       siguiente_clave(clave1, inicio_cadena(cad), cad), cad);
        imprimir_cadena(cad);
      } else {
        imprimir_con_nl(msg_elemento_no_encontrado);
      }

      break;
    }
    case cmd_ins_cadena_despues: {
      int clave1 = leer_int();
      bool existe = pertenece(clave1, cad);
      if (existe) {
        info_t info_insertar = leer_info(MAX_LARGO_PALABRA);
        insertar_despues(info_insertar,
                         siguiente_clave(clave1, inicio_cadena(cad), cad), cad);
        imprimir_cadena(cad);
      } else {
        imprimir_con_nl(msg_elemento_no_encontrado);
      }
      break;
    }
    case cmd_ins_cadena_comienzo: {
      info_t info_insertar = leer_info(MAX_LARGO_PALABRA);
      insertar_antes(info_insertar, inicio_cadena(cad), cad);
      imprimir_cadena(cad);
      break;
    }
    case cmd_ins_cadena_final: {
      info_t info_insertar = leer_info(MAX_LARGO_PALABRA);
      insertar_despues(info_insertar, final_cadena(cad), cad);
      imprimir_cadena(cad);
      break;
    }
    case cmd_recorrido_cadena: {
      if (!es_vacia_cadena(cad)) {
        localizador loc = inicio_cadena(cad);
        while (es_localizador_cadena(loc)) {
          imprimir_info(info_cadena(loc, cad));
          loc = siguiente(loc, cad);
        }
        loc = final_cadena(cad);
        while (es_localizador_cadena(loc)) {
          imprimir_info(info_cadena(loc, cad));
          loc = anterior(loc, cad);
        }
        escribir_nueva_linea();
      }
      break;
    }
    case cmd_segmentos_cadena: {
      
      int clave1 = leer_int();
      
      int clave2 = leer_int();
      
      localizador desde = siguiente_clave(clave1, inicio_cadena(cad), cad);
      
      localizador hasta = anterior_clave(clave2, final_cadena(cad), cad);
      
      if (es_localizador_cadena(desde) && es_localizador_cadena(hasta) &&
      
          precede_en_cadena(desde, hasta, cad)) {
      
        cadena sgm = separar_segmento(desde, hasta, cad);
      
        cadena copia = segmento_cadena(inicio_cadena(sgm), final_cadena(sgm), sgm);
      
        imprimir_cadena(sgm);
        
        liberar_cadena(sgm);
        
        insertar_segmento_despues(copia, final_cadena(cad), cad);
        
        liberar_cadena(copia);
        
        imprimir_cadena(cad);
      }
      break;
    }
    case cmd_modificar_cadena: {
      int clave1 = leer_int();
      int clave2 = leer_int();
      localizador loc1 = siguiente_clave(clave1, inicio_cadena(cad), cad);
      localizador loc2 = anterior_clave(clave2, final_cadena(cad), cad);
      if (es_localizador_cadena(loc1) && es_localizador_cadena(loc2)) {
        intercambiar(loc1, loc2, cad);
        imprimir_cadena(cad);
        if (!es_inicio_cadena(loc2, cad)) {
          localizador ant = anterior(loc2, cad);
          cadena prefijo = segmento_cadena(inicio_cadena(cad), ant, cad);
          if (esta_ordenada(prefijo))
            retroceder(loc2, cad);
          liberar_cadena(prefijo);
        }
        imprimir_cadena(cad);
      }
      break;
    }
    case cmd_retroceder: {
      int clave1 = leer_int();
      localizador loc1 = siguiente_clave(clave1, inicio_cadena(cad), cad);
      if (es_localizador_cadena(loc1)) {
        retroceder(loc1, cad);
      }
      imprimir_cadena(cad);
      break;
    }
    case cmd_intercambiar: {
      int clave1 = leer_int();
      int clave2 = leer_int();
      localizador loc1 = siguiente_clave(clave1, inicio_cadena(cad), cad);
      localizador loc2 = siguiente_clave(clave2, inicio_cadena(cad), cad);
      if (es_localizador_cadena(loc1) && es_localizador_cadena(loc2)) {
        intercambiar(loc1, loc2, cad);
        imprimir_cadena(cad);
      }
      break;
    }
    case cmd_ordenar_cadena: {
      nat len_cad = longitud(cad);
      imprimir_int(len_cad);
      localizador loc = inicio_cadena(cad);
      for (nat i = 0; i < len_cad / 2 - 1; i++)
        loc = siguiente(loc, cad);
      cadena primera = segmento_cadena(inicio_cadena(cad), loc, cad);
      cadena segunda =
          segmento_cadena(siguiente(loc, cad), final_cadena(cad), cad);

      cadena concat = concatenar(primera, segunda);
      imprimir_cadena(concat);
      liberar_cadena(concat);

      if (son_numeros_iguales(primera, segunda)) {
        imprimir_cadena(primera);
      }

      if (!esta_ordenada(primera))
        ordenar(primera);
      if (!esta_ordenada(segunda))
        ordenar(segunda);

       cadena mzc = mezcla(primera, segunda);
       imprimir_cadena(mzc);

       unificar(mzc);
       imprimir_cadena(mzc);
       liberar_cadena(mzc);
       liberar_cadena(primera);
      // liberar_cadena(segunda);
      break;
    }
    case cmd_concatenar: {
      info_t info = leer_info(MAX_LARGO_PALABRA);
      cadena cad2 = crear_cadena();
      while (es_valida_info(info)) {
        insertar_despues(info, final_cadena(cad2), cad2);
        info = leer_info(MAX_LARGO_PALABRA);
      }
      liberar_info(info);
      cadena concat = concatenar(cad, cad2);
      imprimir_cadena(concat);
      break;
    }
    case cmd_filtrado_cadena: {
      int clave = leer_int();
      texto_t palabra = leer_palabra();
      comp_t criterio = texto_a_comp(palabra);
      liberar_texto(palabra);
      if (pertenece(clave, cad)) {
        imprimir_int(cantidad(clave, cad));
      }
      cadena flt = filtrado(clave, criterio, cad);
      imprimir_cadena(flt);
      liberar_cadena(flt);
      break;
    }
    case cmd_reversa_cadena: {
      int dato1 = leer_int();
      int dato2 = leer_int();
      if (esta_ordenada(cad) && pertenece(dato1, cad) &&
          pertenece(dato2, cad) && dato1 < dato2) {
        cadena sub = subcadena(dato1, dato2, cad);
        imprimir_cadena(sub);
        cadena rev = reversa(sub);
        imprimir_cadena(rev);
        cambiar_todos(dato1, dato2, rev);
        imprimir_cadena(rev);
        liberar_cadena(sub);
        liberar_cadena(rev);
      }
      break;
    }
    case cmd_subcadena: {
      int dato1 = leer_int();
      int dato2 = leer_int();
      if (esta_ordenada(cad) && pertenece(dato1, cad) &&
          pertenece(dato2, cad) && dato1 <= dato2) {
        cadena sub = subcadena(dato1, dato2, cad);
        imprimir_cadena(sub);
      }
      break;
    }
    case cmd_liberar_cadena: {
      liberar_cadena(cad);
      cad = crear_cadena();
      break;
    }
    case cmd_test_memoria: {
      test_memoria(leer_int());
      break;
    }
    default:
      imprimir_con_nl(msg_cmd_no_reconocido);
      break;
    } // switch
    texto_t resto_linea = leer_resto_linea();
    liberar_texto(resto_linea);
  } // while
  liberar_cadena(cad);
  return 0;
}
