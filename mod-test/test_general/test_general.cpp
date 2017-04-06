/* 
        TEST GENERAL
 */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <time.h>

#include "../../include/utils.hpp"
#include "../../include/texto.hpp"
#include "../../include/info.hpp"
#include "../../include/cadena.hpp"
#include "../../include/uso_cadena.hpp"

//EL INICIO DE LOS TEST ESTA EN LA FUNCION MAIN


/* 
  ## Funciones Auxiliares
*/
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

void imp_nodo(localizador cursor, cadena cad)
{
  if(cursor != NULL)
  {
    printf("(%d", numero_info(info_cadena(cursor, cad)));
    escribir_texto(texto_info(info_cadena(cursor, cad)));
    puts(")");
  }
  else
  {
    puts("(NULO)");
  }
}
//cadena aleatoria
cadena cad_aleatoria(int cant_nodos, int num1, int num2)
{
  cadena cad = crear_cadena();
  srand(time(NULL));
  for(int i = 1; i <= cant_nodos; i++)
  {
    int num = rand() % num2 + num1;
    char texto[] = "texto ";
    texto_t nuevo_texto = array_a_texto(texto);
    info_t info = crear_info(num, concatenar_texto(nuevo_texto, int_a_texto(i)));
    localizador final = final_cadena(cad);
    insertar_despues(info, final, cad);
  }
  return cad;
}
//localizador segun posicion
localizador loc_segun_posicion(int posicion, cadena cad)
{
  int i = 1;
  localizador cursor = inicio_cadena(cad);
  while(cursor != NULL && i < posicion)
  {
    cursor = siguiente(cursor, cad);
    i++;
  };
  return cursor;
}

void agregar_a_cadena(int num, const char *array, cadena &cad){
    if(cad!=NULL){
	info_t info = crear_info(num, array_a_texto(array));
    localizador ultimo = final_cadena(cad);
    insertar_despues(info, ultimo, cad);
    }
}


void test_info(){
    
    //TST DE INFO.CPP
    puts("INICIO DE TEST PARA INFO.CPP!");
  
     //variables globales al test
    int num = 10;
    char texto[] = "prueba";
    info_t info_1;
    
    //1) test crear_info
        puts("1) test crear_info");
        info_1 = crear_info(num, array_a_texto(texto));
        assert(numero_info(info_1) == num);
        assert(comparar_texto(texto_info(info_1), array_a_texto(texto)) == igual);
        puts("1) ok!");
        
    /*2) test liberar_info
         (borro el que cree en 1)*/
        puts("2) test liberar_info");
        liberar_info(info_1);
        assert(info_1 == NULL);
        puts("2) ok!");  
    
     /*3) test numero_info
          creo un info_t nuevo */
        puts("3) test numero_info");
        info_1 = crear_info(num, array_a_texto(texto));
        assert(numero_info(info_1) == num);
        puts("3) ok!");    
        
    /*4) test texto_info */
        puts("4) test texto_info");
        assert(comparar_texto(texto_info(info_1), array_a_texto(texto)) == igual);
        puts("4) ok!");  
        
    /*5) test es_valida_info 
        Se crea info invalida!!
        */
        puts("5) test es_valida_info");
        assert(es_valida_info(info_1)); //deberia ser true
        info_t info_invalida = crear_info(INT_MAX, array_a_texto(texto));
        assert(!es_valida_info(info_invalida)); //deberia ser false
        puts("5) ok!");  
        
     /*6) test info_a_texto 
          Se prueba que:
          a) No comparta memoria
          b) Que el nuevo texto sea el esperado
        */
        puts("6) test info_a_texto");
        texto_t nuevo_texto = info_a_texto(info_1);
        //a)
        assert(comparar_texto(texto_info(info_1), array_a_texto(texto)) == igual);
        
        char texto_concat[20] = "";
        char int_to_char[20] = "";
        strcat(texto_concat, "(");
        sprintf(int_to_char, "%d", num);
        strcat(texto_concat, int_to_char);
        strcat(texto_concat, ",");
        strcat(texto_concat,texto);
        strcat(texto_concat,")");
        
        texto_t texto_t_texto_concat = array_a_texto(texto_concat);
        
        assert(comparar_texto(nuevo_texto, texto_t_texto_concat) == igual);
        puts("6) ok!");   
        
        
    /*7) test leer_info --- TEST ok ! se comenta, para que no tranque la automatizacion
        */
        puts("7) test leer_info OK !! (de momento esta comentado)");
       // info_t info_desde_lectura = leer_info(longitud_texto(nuevo_texto));
       // assert(comparar_texto(texto_info(info_desde_lectura), texto_info(info_1)) == igual);
     
    
    puts("FIN DE TEST PARA INFO.CPP!");
    puts("");
}

void test_cadena(){
    
          //TST DE CADENA.CPP
    puts("INICIO DE TEST PARA CADENA.CPP!");
    
    
    //variables globales a los test
    cadena cad = NULL;
    int num_1 = 1;
    int num_2 = 2;
    int num_3 = 3;
    int num_4 = 4;
    int num_5 = 5;
    
    char texto_1[] = "texto 1";
    char texto_2[] = "texto 2";
    char texto_3[] = "texto 3";
    char texto_4[] = "texto 4";
    char texto_5[] = "texto 5";
    
    info_t info_cad_1;
    info_t info_cad_2;
    info_t info_cad_3;
    info_t info_cad_4;
    info_t info_cad_5;
    
        //1) test crear_cadena
        puts("1) test crear_cadena");
        cad = crear_cadena();
        assert(cad!=NULL);
        puts("1) ok!");
        
        /*2) test multiple insertar_antes | inicio_cadena | final_cadena | info_cadena
        
          Se crean 5 elementos y se prueba que el ultimo en agregar, es el primero en cadena,
          y el primero es el ultimo.
        */
        puts("2) test MULTIPLE  insertar_antes | inicio_cadena | final_cadena | info_cadena");
        cad = crear_cadena();
        info_cad_1 = crear_info(num_1, array_a_texto(texto_1));
        info_cad_2 = crear_info(num_2, array_a_texto(texto_2));
        info_cad_3 = crear_info(num_3, array_a_texto(texto_3));
        info_cad_4 = crear_info(num_4, array_a_texto(texto_4));
        info_cad_5 = crear_info(num_5, array_a_texto(texto_5));
        
        //Primer elemento
        insertar_antes(info_cad_1, NULL, cad);
        localizador primero = inicio_cadena(cad);
        
        insertar_antes(info_cad_2, primero, cad);
        primero = inicio_cadena(cad);
        
        insertar_antes(info_cad_3, primero, cad);
        primero = inicio_cadena(cad);
        
        insertar_antes(info_cad_4, primero, cad);
        primero = inicio_cadena(cad);
        
        insertar_antes(info_cad_5, primero, cad);
        primero = inicio_cadena(cad);
        
        //El ultimo en agregar es el primero? se compara texto y numero
        primero = inicio_cadena(cad);
        info_t info_primero = info_cadena(primero, cad);
        assert(comparar_texto(texto_info(info_primero), texto_info(info_cad_5)) == igual);
        assert(numero_info(info_primero) == numero_info(info_cad_5));
        
        //El primero en agregar es el ultimo?
        localizador ultimo = final_cadena(cad);
        info_t info_ultimo = info_cadena(ultimo, cad);
        assert(comparar_texto(texto_info(info_ultimo), texto_info(info_cad_1)) == igual);
        assert(numero_info(info_ultimo) == numero_info(info_cad_1));
        puts("2) ok!");
        
        
        /*3) test multiple insertar_despues | inicio_cadena | final_cadena | info_cadena
        
          Se crean 5 elementos y se prueba que el primero en agregar, es el primero en cadena,
          y el ultimo es el ultimo.
        */
        puts("3) test MULTIPLE  insertar_despues | inicio_cadena | final_cadena | info_cadena");
        cad = crear_cadena();
        info_cad_1 = crear_info(num_1, array_a_texto(texto_1));
        info_cad_2 = crear_info(num_2, array_a_texto(texto_2));
        info_cad_3 = crear_info(num_3, array_a_texto(texto_3));
        info_cad_4 = crear_info(num_4, array_a_texto(texto_4));
        info_cad_5 = crear_info(num_5, array_a_texto(texto_5));
        
        //Primer elemento
        insertar_despues(info_cad_1, NULL, cad);
        ultimo = final_cadena(cad);
        
        insertar_despues(info_cad_2, ultimo, cad);
        ultimo = final_cadena(cad);
        
        insertar_despues(info_cad_3, ultimo, cad);
        ultimo = final_cadena(cad);
        
        insertar_despues(info_cad_4, ultimo, cad);
        ultimo = final_cadena(cad);
        
        insertar_despues(info_cad_5, ultimo, cad);
        ultimo = final_cadena(cad);
        
        //El primero en agregar es el primero? se compara texto y numero
        primero = inicio_cadena(cad);
        info_primero = info_cadena(primero, cad);
        assert(comparar_texto(texto_info(info_primero), texto_info(info_cad_1)) == igual);
        assert(numero_info(info_primero) == numero_info(info_cad_1));
        
        //El ultimo en agregar es el ultimo?
        ultimo = final_cadena(cad);
        info_ultimo = info_cadena(ultimo, cad);
        assert(comparar_texto(texto_info(info_ultimo), texto_info(info_cad_5)) == igual);
        assert(numero_info(info_ultimo) == numero_info(info_cad_5));
        puts("3) ok!");
    
    
         /*4) test MULTIPLE segmento_cadena | es_vacia_cadena | siguiente | anterior
         
            (Uso la cadena creada en 3)
          */
        puts("4) test MULTIPLE segmento_cadena | es_vacia_cadena | siguiente | anterior");
        
        //Prueba cadena vacia
        cadena cadena_vacia = crear_cadena();
        cadena segmento = segmento_cadena(NULL, NULL, cadena_vacia);
        assert(es_vacia_cadena(segmento));
        
        /*  Prueba segmento completo (todos los elementos originales)
            Chequeo el texto y valor del primero y ultimo
        */
        primero = inicio_cadena(cad);
        ultimo = final_cadena(cad);
        info_primero = info_cadena(primero, cad);
        info_ultimo = info_cadena(ultimo, cad);
        
        segmento = segmento_cadena(primero, ultimo, cad);
        localizador primero_seg = inicio_cadena(segmento);
        localizador ultimo_seg = final_cadena(segmento);
        info_t info_primero_seg = info_cadena(primero_seg, segmento);
        info_t info_ultimo_seg = info_cadena(ultimo_seg, segmento);
        
        assert(comparar_texto(texto_info(info_primero), texto_info(info_primero_seg)) == igual);
        assert(comparar_texto(texto_info(info_ultimo), texto_info(info_ultimo_seg)) == igual);
        assert(numero_info(info_primero) == numero_info(info_primero_seg));  
        assert(numero_info(info_ultimo) == numero_info(info_ultimo_seg));  
        
        
        //Prueba segmento (del 3 al 4)
        localizador tercero = siguiente(siguiente(inicio_cadena(cad), cad), cad);
        localizador cuarto = anterior(final_cadena(cad), cad);
        info_t info_tercero = info_cadena(tercero, cad);
        info_t info_cuarto = info_cadena(cuarto, cad);
        
        segmento = segmento_cadena(tercero, cuarto, cad);
        primero_seg = inicio_cadena(segmento);
        ultimo_seg = final_cadena(segmento);
        info_primero_seg = info_cadena(primero_seg, segmento);
        info_ultimo_seg = info_cadena(ultimo_seg, segmento);
        
        assert(comparar_texto(texto_info(info_tercero), texto_info(info_primero_seg)) == igual);
        assert(comparar_texto(texto_info(info_cuarto), texto_info(info_ultimo_seg)) == igual);
        assert(numero_info(info_tercero) == numero_info(info_primero_seg));  
        assert(numero_info(info_cuarto) == numero_info(info_ultimo_seg));  
        
        puts("4) ok!");
        
        /*5) test MULTIPLE insertar_segmento_despues | es_vacia_cadena | siguiente | anterior
         
            (Uso la cadena creada en 3)
          */
        puts("5) test MULTIPLE insertar_segmento_despues | imprimir_cadena");
        puts("Se inserta la sub cadena 2-3-4 en cadena 1-2-3-4-5 en el lugar 3 y se imprime en pantalla para chequear");
        localizador segundo = siguiente(inicio_cadena(cad), cad);
        cuarto = anterior(final_cadena(cad), cad);
        segmento = segmento_cadena(segundo, cuarto, cad);
        puts("Se imprime segmento:");
        imprimir_cadena(segmento);
        puts("Se imprime cadena:");
        imprimir_cadena(cad);
        insertar_segmento_despues(segmento, tercero, cad);
        puts("Se imprime la conjuncion:");
        imprimir_cadena(cad);
        puts("5) ESTA OK !");
        
        
        /*6 
            test MULTIPLE separar_segmento | imprimir_cadena
          */
        escribir_nueva_linea();
        escribir_nueva_linea();
        cadena cad_test_6 = cad_aleatoria(9, 1, 20);
        puts("6) test MULTIPLE separar_segmento | imprimir_cadena");
        puts("Separa segmento: ");
        localizador desde_sep_seg = loc_segun_posicion(3, cad_test_6);
        localizador hasta_sep_seg = loc_segun_posicion(5, cad_test_6);
        
        puts("Cadena: ");
        imprimir_cadena(cad_test_6);
        printf("Desde: ");
        imp_nodo(desde_sep_seg, cad_test_6);
        printf("Hasta: ");
        imp_nodo(hasta_sep_seg, cad_test_6);
        puts("Se imprime segmento separado:");
        cadena segmento_separado = separar_segmento(desde_sep_seg, hasta_sep_seg, cad_test_6);
        imprimir_cadena(segmento_separado);
        escribir_nueva_linea();
        
        puts("Se imprime cadena inicial con la separación del segmento:");
        imprimir_cadena(cad_test_6);
        escribir_nueva_linea();
        
        puts("Anterior Inicio (cad_ini): ");
        imp_nodo(anterior(inicio_cadena(cad_test_6),cad_test_6), cad_test_6);
        escribir_nueva_linea();
        
        puts("Siguiente Final (cad_ini):");
        imp_nodo(siguiente(final_cadena(cad_test_6),cad_test_6), cad_test_6);
        escribir_nueva_linea();
        
        puts("Anterior Inicio (sgm): ");
        imp_nodo(anterior(inicio_cadena(segmento_separado),segmento_separado), cad_test_6);
        escribir_nueva_linea();
        
        puts("Siguiente Final (sgm):");
        imp_nodo(siguiente(final_cadena(segmento_separado),segmento_separado), cad_test_6);
        escribir_nueva_linea();
        
        puts("6) Esta Bien :) ");
        
        
        
        
        //Para la destruccion se prueba creando otras cadenas
        
        /* 8
          Se quita el elemento referenciado en `loc' y se libera la memoria asignada
          al mismo y al nodo apuntado por el localizador.
          Si es_vacia_cadena(cad), `loc' es ignorado y no se hace nada.
          El valor de `loc' queda indeterminado.
          Precondición: es_vacia_cadena(cad) o localizador_pertenece_a_cadena(loc, cad).
         */
    	puts("\n##########################################");
    	puts("8) - TEST REMOVER DE CADENA");
    	puts("void remover_de_cadena(localizador &loc, cadena &cad)");
    	puts("------------------------------------------");
    	// Cadena aleatoria
    	cadena cad_test_8_cad = cad_aleatoria(10,1,10);
    	puts("Cadena: ");
    	imprimir_cadena(cad_test_8_cad);
    	
    	puts("## Se remueve de cadena pos 1: ");
    	localizador loc_test_8 = loc_segun_posicion(1,cad_test_8_cad);
    	puts("Nodo: ");
    	imp_nodo(loc_test_8,cad_test_8_cad);
    	remover_de_cadena(loc_test_8,cad_test_8_cad);
    	puts("Cadena resultante: ");
    	imprimir_cadena(cad_test_8_cad);
    	escribir_nueva_linea();
    	
    	puts("## Se remueve de cadena pos 2: ");
    	loc_test_8 = loc_segun_posicion(2,cad_test_8_cad);
    	puts("Nodo: ");
    	imp_nodo(loc_test_8,cad_test_8_cad);
    	remover_de_cadena(loc_test_8,cad_test_8_cad);
    	puts("Cadena resultante: ");
    	imprimir_cadena(cad_test_8_cad);
    	escribir_nueva_linea();
    	
    	puts("## Se remueve de cadena pos 3: ");
    	loc_test_8 = loc_segun_posicion(3,cad_test_8_cad);
    	puts("Nodo: ");
    	imp_nodo(loc_test_8,cad_test_8_cad);
    	remover_de_cadena(loc_test_8,cad_test_8_cad);
    	puts("Cadena resultante: ");
    	imprimir_cadena(cad_test_8_cad);
    	escribir_nueva_linea();
    	
    	puts("## Se remueve de cadena pos 7: ");
    	loc_test_8 = loc_segun_posicion(7,cad_test_8_cad);
    	puts("Nodo: ");
    	imp_nodo(loc_test_8,cad_test_8_cad);
    	remover_de_cadena(loc_test_8,cad_test_8_cad);
    	puts("Cadena resultante: ");
    	imprimir_cadena(cad_test_8_cad);
    	puts("------------------------------------------");
    	puts("FIN TEST REMOVER DE CADENA");
    	puts("##########################################\n");
        
        /*8)
            usar valgrind
          */
        puts("8) test liberar_cadena, se prueba con valgrind");
        
        
         /*9)
               TEST es_vacia_cadena
          */
        puts("8) test es_vacia_cadena");
        cadena_vacia = crear_cadena();
        assert(es_vacia_cadena(cadena_vacia));
        assert(!es_vacia_cadena(cad));
        puts("8) ESTA OK !");
        
          /*10)
               TEST es_localizador_cadena
          */
        puts("10) test es_localizador_cadena");
        assert(es_localizador_cadena(ultimo));
        assert(!es_localizador_cadena(NULL));
        puts("10) ESTA OK !");
        
        /*11)
               TEST localizador_pertenece_a_cadena
          */
        puts("11) test localizador_pertenece_a_cadena");
        
        cadena cad_2 = crear_cadena();
        info_t info_cad_2_1 = crear_info(num_1, array_a_texto(texto_1));
        info_t info_cad_2_2 = crear_info(num_2, array_a_texto(texto_2));
        info_t info_cad_2_3 = crear_info(num_3, array_a_texto(texto_3));
        
        //Primer elemento
        insertar_despues(info_cad_2_1, NULL, cad_2);
        localizador ultimo_2 = final_cadena(cad_2);
        insertar_despues(info_cad_2_2, ultimo_2, cad_2);
        ultimo_2 = final_cadena(cad_2);
        insertar_despues(info_cad_2_3, ultimo_2, cad_2);
        ultimo_2 = final_cadena(cad_2);
        
        ultimo = final_cadena(cad);
        
        
        assert(localizador_pertenece_a_cadena(ultimo_2, cad_2));
        assert(!localizador_pertenece_a_cadena(ultimo, cad_2));
        puts("11) ESTA OK !");
        
        
        /*12)
               TEST precede_en_cadena (se usa cadena de 11))
          */
        puts("12) test precede_en_cadena");
        assert(precede_en_cadena(inicio_cadena(cad_2), final_cadena(cad_2), cad_2));
        assert(!precede_en_cadena(final_cadena(cad_2), inicio_cadena(cad_2), cad_2));
        puts("12) ESTA OK !");
        
        /*13)
               TEST es_inicio_cadena (se usa cadena de 11))
          */
        puts("13) test es_inicio_cadena");
        assert(es_inicio_cadena(inicio_cadena(cad_2), cad_2));
        assert(!es_inicio_cadena(final_cadena(cad_2), cad_2));
        puts("13) ESTA OK !");
        
        /*14)
              TEST es_final_cadena (se usa cadena de 11))
          */
        puts("13) test es_inicio_cadena");
        assert(!es_final_cadena(inicio_cadena(cad_2), cad_2));
        assert(es_final_cadena(final_cadena(cad_2), cad_2));
        puts("13) ESTA OK !");
        
        
         /*15 y 16) 17) 18) OK!! inicio_cadena, final_cadena, siguiente, anterior
            
            testeado previamente
          */



        /*19) y 20)
              TEST MULTIPLE siguiente_clave | anterior_clave (se usa cadena de 11))
          */
        puts("19 y 20) test siguiente_clave anterior_clave");
        assert(es_final_cadena(siguiente_clave(num_3, inicio_cadena(cad_2), cad_2), cad_2));
        assert(!es_final_cadena(siguiente_clave(100, inicio_cadena(cad_2), cad_2), cad_2));
        assert(es_inicio_cadena(anterior_clave(num_1, final_cadena(cad_2), cad_2), cad_2));
        assert(!es_inicio_cadena(anterior_clave(200, final_cadena(cad_2), cad_2), cad_2));
        puts("19 y 20) ESTA OK !");
        
        
        /*21)
              TEST MULTIPLE menor_en_cadena (se usa nueva cadena cad))
          */
        puts("21) test menor_en_cadena");
        cad = crear_cadena();
        info_cad_1 = crear_info(num_1, array_a_texto(texto_1));
        info_cad_2 = crear_info(num_2, array_a_texto(texto_2));
        info_cad_3 = crear_info(num_3, array_a_texto(texto_3));
        info_cad_4 = crear_info(num_4, array_a_texto(texto_4));
        info_cad_5 = crear_info(num_5, array_a_texto(texto_5));
        info_t info_cad_6 = crear_info(0, array_a_texto(texto_5));
        
        //Primer elemento
        insertar_despues(info_cad_1, NULL, cad);
        ultimo = final_cadena(cad);
        insertar_despues(info_cad_2, ultimo, cad);
        ultimo = final_cadena(cad);
        insertar_despues(info_cad_3, ultimo, cad);
        ultimo = final_cadena(cad);
        insertar_despues(info_cad_4, ultimo, cad);
        ultimo = final_cadena(cad);
        insertar_despues(info_cad_5, ultimo, cad);
        ultimo = final_cadena(cad);
        insertar_despues(info_cad_6, ultimo, cad);
        
        imprimir_cadena(cad);
        assert(es_final_cadena(menor_en_cadena(siguiente(inicio_cadena(cad),cad),cad), cad));
        puts("21) ESTA OK !");
      
        /*22)
              TEST info_cadena se usa cadena creada en 21)
          */
        puts("22) test info_cadena");
        assert(numero_info(info_cadena(final_cadena(cad),cad)) == numero_info(info_cad_6));
        puts("22) OK!!");
        
         /*23)
              TEST cambiar_en_cadena se usa cadena creada en 21)
          */
        puts("23) test info_cadena");
        puts("se imprime la cadena antes");
        imprimir_cadena(cad);
        cambiar_en_cadena(info_cad_3, final_cadena(cad), cad);
        puts("se imprime la cadena despues");
        imprimir_cadena(cad);
        assert(numero_info(info_cadena(final_cadena(cad), cad)) == numero_info(info_cad_3));
        puts("23) OK!!");
        
         /*24)
              TEST cambiar_en_cadena se usa cadena creada en 21)
              
              Intercambio elemento 2 por elemento 5
              
              Intercambio elemento 1 por elemento 4
              
              Chequeo los valores
          */
        puts("24) test cambiar_en_cadena");
        puts("se imprime la cadena antes");
        imprimir_cadena(cad);
        intercambiar(siguiente(inicio_cadena(cad), cad), anterior(final_cadena(cad),cad), cad);
        puts("se imprime primer cambio (2 x 5)");
        imprimir_cadena(cad);
        intercambiar(inicio_cadena(cad), anterior(anterior(final_cadena(cad), cad), cad), cad);
        puts("se imprime segundo cambio (1 x 4)");
        imprimir_cadena(cad);
        assert(numero_info(info_cadena(inicio_cadena(cad), cad)) == numero_info(info_cad_4));
        puts("24) OK!!");
        
    
    /* 25 OK
      Mueve el elemento al que se accede con `loc2' dejándolo inmediatamente antes
      de `loc1'.
      Los valores de `loc1' y `loc2' quedan indeterminados.
      Si loc1 == loc2 no hace nada.
      Precondición: ! es_vacia_cadena (cad)
      y localizador_pertenece_a_cadena (loc1, cad)
      y localizador_pertenece_a_cadena (loc2, cad).
     */
    puts("\n##########################################");
	puts("25) - TEST MOVER ANTES ");
	puts("void mover_antes(localizador loc1, localizador loc2, cadena &cad)");
	puts("------------------------------------------");
	// Creo cadenas aleatorias
	cadena cad_test_25_1 = cad_aleatoria(5,1,10);
	cadena cad_test_25_2 = cad_aleatoria(8,1,10);
	cadena cad_test_25_3 = cad_aleatoria(3,1,10);
	puts("## Mover desde posicion 4 antes que 2: ");
	puts("-- Cadena Inicial: ");
	imprimir_cadena(cad_test_25_1);
	// Proceso mover antes
	mover_antes(loc_segun_posicion(1, cad_test_25_1), loc_segun_posicion(4, cad_test_25_1), cad_test_25_1);
	puts("-- Cadena luego de mover antes: ");
	imprimir_cadena(cad_test_25_1);
	escribir_nueva_linea();
	
	puts("## Mover desde posicion 7 antes que 2: ");
	puts("-- Cadena Inicial: ");
	imprimir_cadena(cad_test_25_2);
	// Proceso mover antes
	mover_antes(loc_segun_posicion(2, cad_test_25_2), loc_segun_posicion(7, cad_test_25_2), cad_test_25_2);
	puts("-- Cadena luego de mover antes: ");
	imprimir_cadena(cad_test_25_2);
	escribir_nueva_linea();
	
	puts("## Mover desde posicion 3 antes que 2: ");
	puts("-- Cadena Inicial: ");
	imprimir_cadena(cad_test_25_3);
	// Proceso mover antes
	mover_antes(loc_segun_posicion(2, cad_test_25_3), loc_segun_posicion(3, cad_test_25_3), cad_test_25_3);
	puts("-- Cadena luego de mover antes: ");
	imprimir_cadena(cad_test_25_3);
	escribir_nueva_linea();
	
	puts("------------------------------------------");
	puts("FIN TEST MOVER ANTES");
	puts("##########################################\n");
	
	
	
	
	puts("\n##########################################");
	puts("##) - TEST SIGUIENTE ANTERIOR ");
	puts("void mover_antes(localizador loc1, localizador loc2, cadena &cad)");
	//Creo cadena aleatoria
	cadena cad_test_26 = cad_aleatoria(8,1,10);
	puts("## Cadena");
	imprimir_cadena(cad_test_26);
	escribir_nueva_linea();
	// Testeos
	puts("Nodo pos 1: ");
	imp_nodo(loc_segun_posicion(1,cad_test_26),cad_test_26);
	puts("Anterior posicion 1: ");
	imp_nodo(anterior(loc_segun_posicion(1,cad_test_26),cad_test_26),cad_test_26);
	puts("Siguiente posicion 1: ");
	imp_nodo(siguiente(loc_segun_posicion(1,cad_test_26),cad_test_26),cad_test_26);
	escribir_nueva_linea();
	
	puts("## Cadena");
	imprimir_cadena(cad_test_26);
	escribir_nueva_linea();
	puts("Nodo pos 8: ");
	imp_nodo(loc_segun_posicion(8,cad_test_26),cad_test_26);
	puts("Anterior posicion 8: ");
	imp_nodo(anterior(loc_segun_posicion(8,cad_test_26),cad_test_26),cad_test_26);
	puts("Siguiente posicion 8: ");
	imp_nodo(siguiente(loc_segun_posicion(8,cad_test_26),cad_test_26),cad_test_26);
	escribir_nueva_linea();
	
	puts("## Cadena");
	imprimir_cadena(cad_test_26);
	escribir_nueva_linea();
	puts("Nodo pos 7: ");
	imp_nodo(loc_segun_posicion(7,cad_test_26),cad_test_26);
	puts("Anterior posicion 7: ");
	imp_nodo(anterior(loc_segun_posicion(7,cad_test_26),cad_test_26),cad_test_26);
	puts("Siguiente posicion 7: ");
	imp_nodo(siguiente(loc_segun_posicion(7,cad_test_26),cad_test_26),cad_test_26);
	escribir_nueva_linea();
	
	puts("## Cadena");
	imprimir_cadena(cad_test_26);
	escribir_nueva_linea();
	puts("Nodo pos 2: ");
	imp_nodo(loc_segun_posicion(2,cad_test_26),cad_test_26);
	puts("Anterior posicion 2: ");
	imp_nodo(anterior(loc_segun_posicion(2,cad_test_26),cad_test_26),cad_test_26);
	puts("Siguiente posicion 2: ");
	imp_nodo(siguiente(loc_segun_posicion(2,cad_test_26),cad_test_26),cad_test_26);
	escribir_nueva_linea();
	
	puts("## Cadena");
	imprimir_cadena(cad_test_26);
	escribir_nueva_linea();
	puts("Nodo pos 5: ");
	imp_nodo(loc_segun_posicion(5,cad_test_26),cad_test_26);
	puts("Anterior posicion 5: ");
	imp_nodo(anterior(loc_segun_posicion(5,cad_test_26),cad_test_26),cad_test_26);
	puts("Siguiente posicion 5: ");
	imp_nodo(siguiente(loc_segun_posicion(5,cad_test_26),cad_test_26),cad_test_26);
	escribir_nueva_linea();
	
	
	puts("------------------------------------------");
	puts("FIN TEST SIGUIENTE ANTERIOR");
	puts("##########################################\n");
	
	/*
	    Testeo insertar antes y despues
	*/
	puts("\n##########################################");
	puts("##) - TEST Insertar antes y Despues");
	puts("---------------------------------------------------");
	// Creo cadenas vacia
	cadena cad_29 = crear_cadena();
	cadena cad_29_1 = cad_aleatoria(1,1,5);
	cadena cad_29_2 = cad_aleatoria(2,1,5);
	cadena cad_29_3 = cad_aleatoria(3,1,5);
	cadena cad_29_4 = cad_aleatoria(4,1,5);
	cadena cad_29_5 = cad_aleatoria(5,1,5);
	// creo la info
	
	// Defino los textos
	char texto_29_1[] = "Enero";
	char texto_29_2[] = "Febrero";
	char texto_29_3[] = "Marzo";
	char texto_29_4[] = "Abril";
	char texto_29_5[] = "Mayo";
	char texto_29_6[] = "Junio";
	
	//Creo la info
	info_t info_29 = crear_info(8, array_a_texto(texto_29_1));
	info_t info_29_1 = crear_info(5, array_a_texto(texto_29_2));
	info_t info_29_2 = crear_info(9, array_a_texto(texto_29_3));
	info_t info_29_3 = crear_info(3, array_a_texto(texto_29_4));
	info_t info_29_4 = crear_info(7, array_a_texto(texto_29_5));
	info_t info_29_5 = crear_info(10, array_a_texto(texto_29_6));
	
	//Corro los test
	puts("# Cadena Vacia: ");
	puts("-- Insertar antes: (8,enero)");
	imprimir_cadena(cad_29);
	puts("->");
	insertar_antes(info_29,loc_segun_posicion(1,cad_29),cad_29);
	imprimir_cadena(cad_29);
	escribir_nueva_linea();
	escribir_nueva_linea();
	
	
	puts("# Cadena #1: ");
	puts("-- Insertar antes: (5,febrero)");
	imprimir_cadena(cad_29_1);
	puts("->");
	insertar_antes(info_29_1,loc_segun_posicion(1,cad_29_1),cad_29_1);
	imprimir_cadena(cad_29_1);
	escribir_nueva_linea();
	escribir_nueva_linea();
	
	puts("# Cadena #2: ");
	puts("-- Insertar antes pos 2: (9,marzo)");
	imprimir_cadena(cad_29_2);
	puts("->");
	insertar_antes(info_29_2,loc_segun_posicion(2,cad_29_2),cad_29_2);
	imprimir_cadena(cad_29_2);
	escribir_nueva_linea();
	escribir_nueva_linea();
	
	puts("# Cadena #3: ");
	puts("-- Insertar antes pos3: (3,abril)");
	imprimir_cadena(cad_29_3);
	puts("->");
	insertar_antes(info_29_3,loc_segun_posicion(3,cad_29_3),cad_29_3);
	imprimir_cadena(cad_29_3);
	escribir_nueva_linea();
	escribir_nueva_linea();
	
	
	puts("# Cadena #4: ");
	puts("-- Insertar antes pos 4: (7,mayo)");
	imprimir_cadena(cad_29_4);
	puts("->");
	insertar_antes(info_29_4,loc_segun_posicion(4,cad_29_4),cad_29_4);
	imprimir_cadena(cad_29_4);
	escribir_nueva_linea();
	escribir_nueva_linea();
	
	puts("# Cadena #5: ");
	puts("-- Insertar antes pos 5: (10,junio)");
	imprimir_cadena(cad_29_5);
	puts("->");
	insertar_antes(info_29_5,loc_segun_posicion(5,cad_29_5),cad_29_5);
	imprimir_cadena(cad_29_5);
	escribir_nueva_linea();
	escribir_nueva_linea();
	
	//#######################################
	//#######################################
	puts("# Cadena #1: ");
	puts("-- Insertar despues: (5,febrero)");
	imprimir_cadena(cad_29_1);
	puts("->");
	insertar_despues(info_29_1,loc_segun_posicion(2,cad_29_1),cad_29_1);
	imprimir_cadena(cad_29_1);
	escribir_nueva_linea();
	escribir_nueva_linea();
	
	puts("# Cadena #2: ");
	puts("-- Insertar despues pos 2: (9,marzo)");
	imprimir_cadena(cad_29_2);
	puts("->");
	insertar_despues(info_29_2,loc_segun_posicion(3,cad_29_2),cad_29_2);
	imprimir_cadena(cad_29_2);
	escribir_nueva_linea();
	escribir_nueva_linea();
	
	puts("# Cadena #3: ");
	puts("-- Insertar despues pos3: (3,abril)");
	imprimir_cadena(cad_29_3);
	puts("->");
	insertar_despues(info_29_3,loc_segun_posicion(4,cad_29_3),cad_29_3);
	imprimir_cadena(cad_29_3);
	escribir_nueva_linea();
	escribir_nueva_linea();
	
	
	puts("# Cadena #4: ");
	puts("-- Insertar despues pos 4: (7,mayo)");
	imprimir_cadena(cad_29_4);
	puts("->");
	insertar_despues(info_29_4,loc_segun_posicion(5,cad_29_4),cad_29_4);
	imprimir_cadena(cad_29_4);
	escribir_nueva_linea();
	escribir_nueva_linea();
	
	puts("# Cadena #5: ");
	puts("-- Insertar despues pos 5: (10,junio)");
	imprimir_cadena(cad_29_5);
	puts("->");
	insertar_despues(info_29_5,loc_segun_posicion(6,cad_29_5),cad_29_5);
	imprimir_cadena(cad_29_5);
	escribir_nueva_linea();
	escribir_nueva_linea();
	
	
	puts("------------------------------------------");
	puts("FIN TEST INSERTAR ANTES Y DESPUES");
	puts("##########################################\n");
	
	
	/*
	    Testeo anterior siguiente clave
	*/
	puts("\n##########################################");
	puts("##) - TEST ANTERIOR SIGUIENTE CLAVE");
	puts("---------------------------------------------------");
	// Creo cadena
	cadena cad_test_27 = cad_aleatoria(6,1,20);
	puts("## ANTERIOR CLAVE");
	imprimir_cadena(cad_test_27);
	escribir_nueva_linea();
	puts("- Loc 6, Clave 3: ");
	imp_nodo(anterior_clave(3,loc_segun_posicion(6,cad_test_27),cad_test_27),cad_test_27);
	puts("- Loc 5, Clave 5: ");
	imp_nodo(anterior_clave(5,loc_segun_posicion(5,cad_test_27),cad_test_27),cad_test_27);
	puts("- Loc 2, Clave 2: ");
	imp_nodo(anterior_clave(2,loc_segun_posicion(2,cad_test_27),cad_test_27),cad_test_27);
	puts("- Loc 1, Clave 5: ");
	imp_nodo(anterior_clave(5,loc_segun_posicion(1,cad_test_27),cad_test_27),cad_test_27);
	escribir_nueva_linea();
	
	puts("## SIGUIENTE CLAVE");
	imprimir_cadena(cad_test_27);
	escribir_nueva_linea();
	puts("- Loc 6, Clave 3: ");
	imp_nodo(siguiente_clave(3,loc_segun_posicion(6,cad_test_27),cad_test_27),cad_test_27);
	puts("- Loc 5, Clave 5: ");
	imp_nodo(siguiente_clave(5,loc_segun_posicion(5,cad_test_27),cad_test_27),cad_test_27);
	puts("- Loc 2, Clave 2: ");
	imp_nodo(siguiente_clave(2,loc_segun_posicion(2,cad_test_27),cad_test_27),cad_test_27);
	puts("- Loc 1, Clave 5: ");
	imp_nodo(siguiente_clave(5,loc_segun_posicion(1,cad_test_27),cad_test_27),cad_test_27);
	
	
	puts("------------------------------------------");
	puts("FIN TEST ANTERIOR SIGUIENTE CLAVE");
	puts("##########################################\n");
	
	
	
	/*
	    Testeo precede en cadena
	*/
	puts("\n##########################################");
	puts("##) - TEST PRECEDE EN CADENA");
	puts("---------------------------------------------------");
	// Creo cadena
	cadena cad_test_28 = cad_aleatoria(9,1,20);
	localizador loc1_28;
	localizador loc1_29;
	//Casos
	puts("# Caso 1: 1 precede 2?: ");
	loc1_28 = loc_segun_posicion(1,cad_test_28);
	loc1_29 = loc_segun_posicion(2,cad_test_28);
	if (precede_en_cadena(loc1_28,loc1_29,cad_test_28))
	{
	    puts("Precede");
	}
	else
	{
	    puts("No precede");
	}
	escribir_nueva_linea();
	
	puts("# Caso 1.1: 2 precede 1?: ");
	loc1_28 = loc_segun_posicion(2,cad_test_28);
	loc1_29 = loc_segun_posicion(1,cad_test_28);
	if (precede_en_cadena(loc1_28,loc1_29,cad_test_28))
	{
	    puts("Precede");
	}
	else
	{
	    puts("No precede");
	}
	escribir_nueva_linea();
	
	puts("# Caso 2: 2 precede 3?: ");
	loc1_28 = loc_segun_posicion(2,cad_test_28);
	loc1_29 = loc_segun_posicion(3,cad_test_28);
	if (precede_en_cadena(loc1_28,loc1_29,cad_test_28))
	{
	    puts("Precede");
	}
	else
	{
	    puts("No precede");
	}
	escribir_nueva_linea();
	
	puts("# Caso 3: 5 precede 7?: ");
	loc1_28 = loc_segun_posicion(5,cad_test_28);
	loc1_29 = loc_segun_posicion(7,cad_test_28);
	if (precede_en_cadena(loc1_28,loc1_29,cad_test_28))
	{
	    puts("Precede");
	}
	else
	{
	    puts("No precede");
	}
	escribir_nueva_linea();
	
	puts("# Caso 4: 7 precede 5?: ");
	loc1_28 = loc_segun_posicion(7,cad_test_28);
	loc1_29 = loc_segun_posicion(5,cad_test_28);
	if (precede_en_cadena(loc1_28,loc1_29,cad_test_28))
	{
	    puts("Precede");
	}
	else
	{
	    puts("No precede");
	}
	escribir_nueva_linea();
	
	puts("# Caso 5: 9 precede 8?: ");
	loc1_28 = loc_segun_posicion(9,cad_test_28);
	loc1_29 = loc_segun_posicion(8,cad_test_28);
	if (precede_en_cadena(loc1_28,loc1_29,cad_test_28))
	{
	    puts("Precede");
	}
	else
	{
	    puts("No precede");
	}
	escribir_nueva_linea();
	
	puts("# Caso 6: 8 precede 9?: ");
	loc1_28 = loc_segun_posicion(8,cad_test_28);
	loc1_29 = loc_segun_posicion(9,cad_test_28);
	if (precede_en_cadena(loc1_28,loc1_29,cad_test_28))
	{
	    puts("Precede");
	}
	else
	{
	    puts("No precede");
	}
	escribir_nueva_linea();
	
	
	puts("------------------------------------------");
	puts("FIN TEST PRECEDE EN CADENA");
	puts("##########################################\n");
}

void test_uso_cadena(){
    
    
// 	/* ANDA OK!!!!
// 	  1) 
// 	  Devuelve `true' si en `cad' hay un elemento cuyo dato numérico es `i',
// 	  o `false` en otro caso.
// 	 */
// 	puts("\n##########################################");
// 	puts("1) - TEST PERTENECE ");
// 	puts("bool pertenece(int i, cadena cad)");
// 	puts("------------------------------------------");
// 	// Creo cadena para trabajar el ejemplo
// 	cadena cad = cad_aleatoria(6,1,10);
// 	puts("imprimo la cadena:");
// 	imprimir_cadena(cad);
// 	int casos[3];
// 	casos[0] = 5;
// 	casos[1] = 7;
// 	casos[2] = 3;
// 	for (int i = 0; i <= 3; i++){
// 		if(pertenece(casos[i], cad))
// 		{
// 			printf("%d pertenece a cadena\n", casos[i]);
// 		}
// 		else
// 		{
// 			printf("%d no pertenece a cadena\n", casos[i]);
// 		}
// 	}
// 	puts("------------------------------------------");
// 	puts("FIN TEST PERTENECE");
// 	puts("##########################################\n");
	
// 	/* 2) ANDA OK!!!!
// 	  Devuelve la cantidad de elementos de `cad'. 
// 	*/
// 	puts("\n##########################################");
// 	puts("2) - TEST LONGITUD");
// 	puts("nat longitud(cadena cad)");
// 	puts("------------------------------------------");
// 	// Creo cadenas para trabajar el ejemplo
// 	cadena cad1 = cad_aleatoria(5,1,10);
// 	cadena cad2 = cad_aleatoria(0,1,10);
// 	cadena cad3 = cad_aleatoria(1,1,10);
	
// 	// Imprimo resultados
// 	imprimir_cadena(cad1);
// 	printf("%d es la longitud de cad1\n", longitud(cad1));
// 	imprimir_cadena(cad2);
// 	printf("%d es la longitud de cad2\n", longitud(cad2));
// 	imprimir_cadena(cad3);
// 	printf("%d es la longitud de cad3\n", longitud(cad3));
	
// 	puts("------------------------------------------");
// 	puts("FIN TEST LONGITUD");
// 	puts("##########################################\n");
	
	
// 	/* 3) ANDA OK!!!!
// 		Devuelve la cantidad de elementos de `cad' cuyo dato numérico es `i'. 
// 	*/
// 	puts("\n##########################################");
// 	puts("3) - TEST CANTIDAD");
// 	puts("nat cantidad(int i, cadena cad)");
// 	puts("------------------------------------------");
// 	int casos_3[5];
// 	casos_3[0] = 5;
// 	casos_3[1] = 7;
// 	casos_3[2] = 11;
// 	casos_3[3] = 15;
// 	casos_3[4] = 10;
// 	cadena cad_t_3 = cad_aleatoria(10,1,15);
// 	imprimir_cadena(cad_t_3);	
// 	for (int i = 0; i < 5; i++){
// 		printf("%d se encuentra %d veces en cadena\n", casos_3[i], cantidad(casos_3[i],cad_t_3));
// 	}
	
// 	puts("------------------------------------------");
// 	puts("FIN TEST CANTIDAD");
// 	puts("##########################################\n");
	
// 	/*
// 	  4) ANDA OK !!!!!!!!!!!!!!!
// 	  Devuelve `true' si y sólo si los datos numéricos de los elementos de `l1'
// 	  son iguales uno a uno con los de los elementos de `l2' (es decir, son los
// 	  mismos números y en el mismo orden).
// 	  Si es_vacia_cadena(l1) y es_vacia_cadena(l2) devuelve `true'.
// 	 */
// 	puts("\n##########################################");
// 	puts("4) - TEST SON NUMEROS IGUALES");
// 	puts("bool son_numeros_iguales(cadena l1, cadena l2)");
// 	puts("------------------------------------------");
// 	// Creo 2 cadenas aleatorias
// 	cadena cad_test_4_1 = cad_aleatoria(3,1,5);
// 	cadena cad_test_4_2 = cad_aleatoria(3,1,5);
// 	// Creo 2 cadenas definidas manualmente iguales
// 	cadena cad_test_4_3 = crear_cadena();
// 	cadena cad_test_4_4 = crear_cadena();
// 	// Creo los nodos de cad_test_4_3 y los agrego
// 	char texto_1[] = "texto 1";
// 	char texto_2[] = "texto 2";
// 	char texto_3[] = "texto 3";
// 	// Creacion de los nodos con la info
// 	info_t info_cad_1 = crear_info(1, array_a_texto(texto_1));
// 	info_t info_cad_2 = crear_info(2, array_a_texto(texto_2));
// 	info_t info_cad_3 = crear_info(3, array_a_texto(texto_3));
// 	// - Primer elemento
//     insertar_despues(info_cad_1, NULL, cad_test_4_3);
//     localizador ultimo = final_cadena(cad_test_4_3);
// 	// - Segundo elemento
//     insertar_despues(info_cad_2, ultimo, cad_test_4_3);
//     ultimo = final_cadena(cad_test_4_3);
// 	// - Tercer elemento
//     insertar_despues(info_cad_3, ultimo, cad_test_4_3);
//     ultimo = final_cadena(cad_test_4_3);
// 	// -------
// 	// Creo los nodos de cad_test_4_4 y los agrego
// 	char texto_4[] = "texto 1";
// 	char texto_5[] = "texto 2";
// 	char texto_6[] = "texto 3";
// 	// Creacion de los nodos con la info
// 	info_t info_cad_4 = crear_info(1, array_a_texto(texto_4));
// 	info_t info_cad_5 = crear_info(2, array_a_texto(texto_5));
// 	info_t info_cad_6 = crear_info(3, array_a_texto(texto_6));
// 	// - Primer elemento
//     insertar_despues(info_cad_4, NULL, cad_test_4_4);
//     ultimo = final_cadena(cad_test_4_4);
// 	// - Segundo elemento
//     insertar_despues(info_cad_5, ultimo, cad_test_4_4);
//     ultimo = final_cadena(cad_test_4_4);
// 	// - Tercer elemento
//     insertar_despues(info_cad_6, ultimo, cad_test_4_4);
//     ultimo = final_cadena(cad_test_4_4);
// 	// -----
// 	// Comienza el test
// 	puts("\n## Se imprimen las cadenas ##:\n ");
// 	puts("Cadena 1: ");
// 	imprimir_cadena(cad_test_4_1);
// 	puts("Cadena 2: ");
// 	imprimir_cadena(cad_test_4_2);
// 	puts("Cadena 3: ");
// 	imprimir_cadena(cad_test_4_3);
// 	puts("Cadena 4: ");
// 	imprimir_cadena(cad_test_4_4);
// 	// Comparacion de cadena 1 con cadena 2
// 	puts("Comparación de cadena 1 con cadena 2");
// 	if (son_numeros_iguales(cad_test_4_1, cad_test_4_2))
// 	{
// 		puts("Cadena 1 y Cadena 2 son iguales");
// 	}
// 	else
// 	{
// 	puts("Cadena 1 y Cadena 2 no son iguales");
// 	}
// 	// Comparacion de cadena 3 con cadena 4
// 	puts("Comparación de cadena 3 con cadena 4");
// 	if (son_numeros_iguales(cad_test_4_3, cad_test_4_4))
// 	{
// 		puts("Cadena 3 y Cadena 4 son iguales");
// 	}
// 	else
// 	{
// 		puts("Cadena 3 y Cadena 4 no son iguales");
// 	}
// 		// Comparacion de cadena 1 con cadena 4
// 	puts("Comparación de cadena 1 con cadena 4");
// 	if (son_numeros_iguales(cad_test_4_1, cad_test_4_4))
// 	{
// 		puts("Cadena 1 y Cadena 4 son iguales");
// 	}
// 	else
// 	{
// 		puts("Cadena 1 y Cadena 4 no son iguales");
// 	}
// 	puts("------------------------------------------");
// 	puts("FIN TEST SON NUMEROS IGUALES");
// 	puts("##########################################\n");
	
	
//     /*
//       5) ANDA OK !!!!!
//       Devuelve `true' si y sólo si `cad' está ordenada de forma no decreciente
//       (= creciente de manera no estricta) según  los datos numéricos de sus
//       elementos.
//       Si es_vacia_cadena (cad), devuelve `true'.
//     */
// 	puts("\n##########################################");
// 	puts("5) - TEST ESTA ORDENADA CADENA");
// 	puts("bool esta_ordenada(cadena cad)");
// 	puts("------------------------------------------");
// 	// Cadena test 5
// 	cadena cad_test_5 = cad_aleatoria(6,1,10);
// 	puts("Cadena: ");
// 	imprimir_cadena(cad_test_5);
// 	if (esta_ordenada(cad_test_5))
// 	{
// 	    puts("Cadena Test 5 esta ordenada");
// 	}
// 	else
// 	{
// 	    puts("Cadena Test 5 no esta ordenada");
// 	}
	
// 	cadena cad_func_5 = crear_cadena();
//  	for(int i=0; i<10; i++){
//  	  char texto[] = "texto";
//  	  agregar_a_cadena(i, texto, cad_func_5);
//  	}
//  	puts("Cadena 2:");
//  	imprimir_cadena(cad_func_5);
//  	if (esta_ordenada(cad_func_5))
// 	{
// 	    puts("Cadena 2 Test 5 esta ordenada");
// 	}
// 	else
// 	{
// 	    puts("Cadena 2 Test 5 no esta ordenada");
// 	}
	
// 	puts("------------------------------------------");
// 	puts("FIN TEST ESTA ORDENADA CADENA");
// 	puts("##########################################\n");
	
	
	
//     /*
//       6)  ANDA OK!!!!
//       Devuelve el resultado de concatenar `l2' después de `l1'.
//       La cadena resultado no comparte memoria ni con `l1' ni con `l2'.
//     */
// 	puts("\n##########################################");
// 	puts("6) - TEST CONCATENAR");
// 	puts("cadena concatenar(cadena l1, cadena l2)");
// 	puts("------------------------------------------");
// 	// Primera cadena test 6
// 	cadena cad_test_6_1 = cad_aleatoria(3,1,5);
// 	// Segunda cadena test 6
// 	cadena cad_test_6_2 = cad_aleatoria(5,6,10);
// 	// Tercera cadena test 6
// 	cadena cad_test_6_3 = cad_aleatoria(1,11,20);
// 	// Impresión de cadenas
// 	puts("Cadena 1: ");
// 	imprimir_cadena(cad_test_6_1);
// 	puts("Cadena 2: ");
// 	imprimir_cadena(cad_test_6_2);
// 	puts("Cadena 3: ");
// 	imprimir_cadena(cad_test_6_3);
// 	// Concatenación de cadenas
// 	cadena concat1 = concatenar(cad_test_6_1, cad_test_6_2);
// 	puts("Concatenación de cadena 1 con cadena 2: ");
// 	imprimir_cadena(concat1);
// 	cadena concat2 = concatenar(concat1, cad_test_6_3);
// 	puts("Cadena resultante de concatenar las cadenas 1 y 2, concatenada con cadena 3: ");
// 	imprimir_cadena(concat2);
	
// 	cadena cad_vacia_1 = crear_cadena();
// 	cadena cad_vacia_2 = crear_cadena();
// 	puts("Cadena resultante de concatenar dos cadenas vacias ");
// 	cadena concat3 = concatenar(cad_vacia_1, cad_vacia_2);
// 	imprimir_cadena(concat3);
// 	puts("------------------------------------------");
// 	puts("FIN TEST CONCATENAR");
// 	puts("##########################################\n");
	
	
//     /* 7) ANDA Ok!!
//       Devuelve la cadena que tiene todos los elementos de `cad' pero en orden
//       inverso.
//       La cadena resultado no comparte memoria con `cad'.
//      */
// 	puts("\n##########################################");
// 	puts("7) - TEST REVERSA");
// 	puts("cadena reversa(cadena cad)");
// 	puts("------------------------------------------");
// 	// Cadena test 7
// 	cadena cad_test_7_1 = cad_aleatoria(6,1,10);
// 	cadena cad_test_7_2 = cad_aleatoria(5,11,17);
// 	cadena cad_test_7_3 = cad_aleatoria(1,20,25);
// 	cadena cad_test_7_4 = cad_aleatoria(2,1,5);
// 	// Impresion de cadenas junto con sus reversas
// 	puts("# Cadena 1 y luego su reversa: ");
// 	imprimir_cadena(cad_test_7_1);
// 	imprimir_cadena(reversa(cad_test_7_1));
// 	puts("# Cadena 2 y luego su reversa: ");
// 	imprimir_cadena(cad_test_7_2);
// 	imprimir_cadena(reversa(cad_test_7_2));
// 	puts("# Cadena 3 y luego su reversa: ");
// 	imprimir_cadena(cad_test_7_3);
// 	imprimir_cadena(reversa(cad_test_7_3));
// 	puts("# Cadena 4 y luego su reversa: ");
// 	imprimir_cadena(cad_test_7_4);
// 	imprimir_cadena(reversa(cad_test_7_4));
// 	puts("------------------------------------------");
// 	puts("FIN TEST REVERSA");
// 	puts("##########################################\n");
	
	
	
	
//     /* ANDA OK !!
//       8)
//       Devuelve el localizador que accede al primer elemento, empezando desde el
//       inicio de `cad' y anterior a `loc', cuyo dato numérico es mayor que el del
//       elemento que se accede desde `loc'.
//       Si ninguno de los elementos anteriores es mayor devuelve `loc'.
//       Precondición: ! es_vacia_cadena (cad), pertenece_localizador_cadena (loc, cad)
//       y `cad' está ordenada de manera creciente (no estricta) según su dato
//       numérico desde el inicio hasta el anterior a `loc'.
//      */
// 	puts("\n##########################################");
// 	puts("8) - TEST PRIMER VALOR");
// 	puts("localizador primer_mayor(localizador loc, cadena cad)");
// 	puts("------------------------------------------");
// 	// Creación de cadenas aleatorias
//     cadena cad_test_8_1 = cad_aleatoria(1,1,10);
//     cadena cad_test_8_2 = cad_aleatoria(4,1,10);
//     cadena cad_test_8_3 = cad_aleatoria(6,1,10);
//     cadena cad_test_8_4 = cad_aleatoria(8,1,10);
//     cadena cad_test_8_5 = cad_aleatoria(11,1,10);
    
//     // Impresión de localizadores
//     puts("Localizar -> Pos 1 - Cad 1: ");
//     imprimir_cadena(cad_test_8_1);
//     puts("Nodo Pos 1:");
//     localizador nodo_seg_pos = loc_segun_posicion(1,cad_test_8_1);
//     imp_nodo(nodo_seg_pos, cad_test_8_1);
//     puts("Primer mayor:");
//     localizador prim_mayor = primer_mayor(nodo_seg_pos, cad_test_8_1);
//     imp_nodo(prim_mayor, cad_test_8_1);
//     puts("");
  
//     puts("Localizar -> Pos 2 - Cad 2: ");
//     imprimir_cadena(cad_test_8_2);
//     puts("Nodo Pos 2:");
//     localizador nodo_seg_pos_2 = loc_segun_posicion(2, cad_test_8_2);
//     imp_nodo(nodo_seg_pos_2, cad_test_8_2);
//     puts("Primer mayor:");
//     localizador prim_mayor_2 = primer_mayor(nodo_seg_pos_2, cad_test_8_2);
//     imp_nodo(prim_mayor_2, cad_test_8_2);
//     puts("");
    
//     puts("Localizar -> Pos 3 - Cad 3: ");
//     imprimir_cadena(cad_test_8_3);
//     puts("Nodo Pos 3:");
//     localizador nodo_seg_pos_3 = loc_segun_posicion(3, cad_test_8_3);
//     imp_nodo(nodo_seg_pos_3, cad_test_8_3);
//     puts("Primer mayor:");
//     localizador prim_mayor_3 = primer_mayor(nodo_seg_pos_3, cad_test_8_3);
//     imp_nodo(prim_mayor_3, cad_test_8_3);
//     puts("");
    
//     puts("Localizar -> Pos 4 - Cad 4: ");
//     imprimir_cadena(cad_test_8_4);
//     puts("Nodo Pos 4:");
//     localizador nodo_seg_pos_4 = loc_segun_posicion(4, cad_test_8_4);
//     imp_nodo(nodo_seg_pos_4, cad_test_8_4);
//     puts("Primer mayor:");
//     localizador prim_mayor_4 = primer_mayor(nodo_seg_pos_4, cad_test_8_4);
//     imp_nodo(prim_mayor_4, cad_test_8_4);
//     puts("");
    
//     puts("Localizar -> Pos 5 - Cad 5: ");
//     imprimir_cadena(cad_test_8_5);
//     puts("Nodo Pos 5:");
//     localizador nodo_seg_pos_5 = loc_segun_posicion(5, cad_test_8_5);
//     imp_nodo(nodo_seg_pos_5, cad_test_8_5);
//     puts("Primer mayor:");
//     localizador prim_mayor_5 = primer_mayor(nodo_seg_pos_5, cad_test_8_5);
//     imp_nodo(prim_mayor_5, cad_test_8_5);
//     puts("");
    

// 	puts("------------------------------------------");
// 	puts("FIN TEST PRIMER VALOR");
// 	puts("##########################################\n");
	
	
    /* 
      9) ANDA OK!!
      Mueve el elemento al que se accede con `loc' dejéndolo inmediatamente antes
      de los elementos cuyos datos numéricos son mayores que dicho elemento.
      El valor de `loc' queda ideterminado.
      Si el dato numérico de `loc' es mayor o igual que el los de los que lo
      preceden no hace nada.
      Precondición: ! es_vacia_cadena (cad), pertenece_localizador_cadena (loc, cad)
      y `cad' está ordenada de manera creciente (no estricta) según su dato
      numérico desde el inicio hasta el anterior a `loc'.
    */
    puts("\n##########################################");
	puts("9) - TEST RETROCEDER");
	puts("void retroceder(localizador loc, cadena &cad)");
	puts("------------------------------------------");
	// Creación de cadenas aleatorias
    cadena cad_test_9_1 = cad_aleatoria(1,1,10);
    cadena cad_test_9_2 = cad_aleatoria(2,1,10);
    cadena cad_test_9_3 = cad_aleatoria(3,1,10);
    cadena cad_test_9_4 = cad_aleatoria(4,1,10);
    cadena cad_test_9_5 = cad_aleatoria(5,1,10);
    // Aplicacion de retroceder e impresion de cadena en cada caso
    // ## CADENA 1
    puts("### CADENA 1: ");
    imprimir_cadena(cad_test_9_1);
    puts("Loc -> posicion 1: ");
    localizador loc1 = loc_segun_posicion(1,cad_test_9_1);
    imp_nodo(loc1,cad_test_9_1);
    // Aplico retroceder
    retroceder(loc1,cad_test_9_1);
    puts("Cadena luego de retroceder: ");
    imprimir_cadena(cad_test_9_1);
    escribir_nueva_linea();
    // ## CADENA 2
    puts("### CADENA 2: ");
    imprimir_cadena(cad_test_9_2);
    puts("Loc -> posicion 2: ");
    localizador loc2 = loc_segun_posicion(2,cad_test_9_2);
    imp_nodo(loc2,cad_test_9_2);
    // Aplico retroceder
    retroceder(loc2,cad_test_9_2);
    puts("Cadena luego de retroceder: ");
    imprimir_cadena(cad_test_9_2);
    // ## CADENA 3
    escribir_nueva_linea();
    
    puts("### CADENA 3: ");
    imprimir_cadena(cad_test_9_3);
    puts("Loc -> posicion 3: ");
    localizador loc3 = loc_segun_posicion(3,cad_test_9_3);
    imp_nodo(loc3,cad_test_9_3);
    // Aplico retroceder
    retroceder(loc3,cad_test_9_3);
    puts("Cadena luego de retroceder: ");
    imprimir_cadena(cad_test_9_3);
    // ## CADENA 2
    puts("");
    
    puts("### CADENA 4: ");
    imprimir_cadena(cad_test_9_4);
    puts("Loc -> posicion 4: ");
    localizador loc4 = loc_segun_posicion(4,cad_test_9_4);
    imp_nodo(loc4,cad_test_9_4);
    // Aplico retroceder
    retroceder(loc4,cad_test_9_4);
    puts("Cadena luego de retroceder: ");
    imprimir_cadena(cad_test_9_4);
    escribir_nueva_linea();
    // ## CADENA 5
    puts("### CADENA 5: ");
    imprimir_cadena(cad_test_9_5);
    puts("Loc -> posicion 5: ");
    localizador loc5 = loc_segun_posicion(5,cad_test_9_5);
    imp_nodo(loc5,cad_test_9_5);
    // Aplico retroceder
    retroceder(loc5,cad_test_9_5);
    puts("Cadena luego de retroceder: ");
    imprimir_cadena(cad_test_9_5);
    escribir_nueva_linea();
    
    // ## CADENA 5 POS 3
    puts("### CADENA 5 - Pos 3: ");
    imprimir_cadena(cad_test_9_5);
    puts("Loc -> posicion 3: ");
    localizador loc6 = loc_segun_posicion(3,cad_test_9_5);
    imp_nodo(loc6,cad_test_9_5);
    // Aplico retroceder
    retroceder(loc6,cad_test_9_5);
    puts("Cadena luego de retroceder: ");
    imprimir_cadena(cad_test_9_5);
    escribir_nueva_linea();
	
	// ## CADENA 5 POS 1
    puts("### CADENA 5 - Pos 1: ");
    imprimir_cadena(cad_test_9_5);
    puts("Loc -> posicion 1: ");
    localizador loc7 = loc_segun_posicion(1,cad_test_9_5);
    imp_nodo(loc7,cad_test_9_5);
    // Aplico retroceder
    retroceder(loc7,cad_test_9_5);
    puts("Cadena luego de retroceder: ");
    imprimir_cadena(cad_test_9_5);
	puts("------------------------------------------");
	puts("FIN TEST RETROCEDER");
	puts("##########################################\n");
	
	
    /* ANDA IMPECABLE!!!
      10)
      Se ordena `cad' de manera creciente según los datos numéricos de sus
      elementos.
      Si los datos numéricos de dos elementos son iguales, se mantiene el orden
      relativo que tenían dichos elementos inicialmente.
      No se debe obtener ni devolver memoria de manera dinámica.
      Si es_vacia_cadena (cad) no hace nada.
     */
//     puts("\n##########################################");
// 	puts("10) - TEST ordenar");
// 	puts("void ordenar(cadena &cad)");
// 	puts("------------------------------------------");
// 	// Cadena test 10
// 	cadena cad_test_10_1 = cad_aleatoria(6,1,15);
// 	cadena cad_test_10_2 = cad_aleatoria(5,11,20);
// 	cadena cad_test_10_3 = cad_aleatoria(1,1,10);
// 	cadena cad_test_10_4 = cad_aleatoria(3,25,40);
// 	cadena cad_test_10_5 = cad_aleatoria(4,1,20);
// 	puts("## Cadena 1: ");
//     imprimir_cadena(cad_test_10_1);
//     puts("");
//     ordenar(cad_test_10_1);
//     puts("Cadena 1 Ordenada: ");
//     imprimir_cadena(cad_test_10_1);
//     escribir_nueva_linea();
    
//     puts("## Cadena 2: ");
//     imprimir_cadena(cad_test_10_2);
//     ordenar(cad_test_10_2);
//     puts("Cadena 2 Ordenada: ");
//     imprimir_cadena(cad_test_10_2);
//     escribir_nueva_linea();
    
//     puts("## Cadena 3: ");
//     imprimir_cadena(cad_test_10_3);
//     ordenar(cad_test_10_3);
//     puts("Cadena 3 Ordenada: ");
//     imprimir_cadena(cad_test_10_3);
//     escribir_nueva_linea();
    
//     puts("## Cadena 4: ");
//     imprimir_cadena(cad_test_10_4);
//     ordenar(cad_test_10_4);
//     puts("Cadena 4 Ordenada: ");
//     imprimir_cadena(cad_test_10_4);
//     escribir_nueva_linea();
    
//     puts("## Cadena 5: ");
//     imprimir_cadena(cad_test_10_5);
//     ordenar(cad_test_10_5);
//     puts("Cadena 5 Ordenada: ");
//     imprimir_cadena(cad_test_10_5);
//     escribir_nueva_linea();
// 	puts("------------------------------------------");
// 	puts("FIN TEST ORDENAR");
// 	puts("##########################################\n");
	
//     /*
//       11)
//       Elimina los elementos con datos numéricos repetidos, conservando el primero
//       de ellos.
//       Libera la memoria de los elementos que elimina.
//       Precondición: esta_ordenada (cad).
//     */
//     puts("11) - TEST UNIFICAR");
// 	puts("void unificar(cadena &cad)");
// 	puts("------------------------------------------");
// 	// Creacion de cadenas
// 	cadena cad_test_11_1 = cad_aleatoria(1,1,5);
// 	cadena cad_test_11_2 = cad_aleatoria(2,1,5);
// 	cadena cad_test_11_3 = cad_aleatoria(3,1,5);
// 	cadena cad_test_11_4 = cad_aleatoria(4,1,5);
// 	cadena cad_test_11_5 = cad_aleatoria(10,1,5);
// 	// Ordenar cadenas
// 	ordenar(cad_test_11_1);
// 	ordenar(cad_test_11_2);
// 	ordenar(cad_test_11_3);
// 	ordenar(cad_test_11_4);
// 	ordenar(cad_test_11_5);
//     // Unificando datos
//     puts("## Cadena 1: ");
//     imprimir_cadena(cad_test_11_1);
//     unificar(cad_test_11_1);
//     puts("- Cadena unificada: ");
//     imprimir_cadena(cad_test_11_1);
//     escribir_nueva_linea();
    
//     puts("## Cadena 2: ");
//     imprimir_cadena(cad_test_11_2);
//     unificar(cad_test_11_2);
//     puts("- Cadena unificada: ");
//     imprimir_cadena(cad_test_11_2);
//     escribir_nueva_linea();
    
//     puts("## Cadena 3: ");
//     imprimir_cadena(cad_test_11_3);
//     unificar(cad_test_11_3);
//     puts("- Cadena unificada: ");
//     imprimir_cadena(cad_test_11_3);
//     escribir_nueva_linea();
    
//     puts("## Cadena 4: ");
//     imprimir_cadena(cad_test_11_4);
//     unificar(cad_test_11_4);
//     puts("- Cadena unificada: ");
//     imprimir_cadena(cad_test_11_4);
//     escribir_nueva_linea();
    
//     puts("## Cadena 5: ");
//     imprimir_cadena(cad_test_11_5);
//     unificar(cad_test_11_5);
//     puts("- Cadena unificada: ");
//     imprimir_cadena(cad_test_11_5);
//     escribir_nueva_linea();

// 	puts("------------------------------------------");
// 	puts("FIN TEST UNIFICAR");
// 	puts("##########################################\n");
    
    /*
      12)
      Devuelve una cadena con todos los elementos de `l1' y `l2' ordenada de manera
      creciente segun sus datos numéricos.
      Si hay elementos cuyos datos numéricos son iguales, los elementos de `l1'
      quedan antes de los de `l2'.
      La cadena resultado no comparte memoria ni con `l1' ni con `l2'.
      Precondición: esta_ordenada (l1) y esta_ordenada (l2).
     */
    
//     puts("\n##########################################");
// 	puts("12) - TEST MEZCLA");
// 	puts("cadena mezcla(cadena l1, cadena l2)");
// 	puts("------------------------------------------");
// 	// Creacion de cadenas
// 	cadena cad_test_12_1 = cad_aleatoria(9,1,15);
// 	cadena cad_test_12_2 = cad_aleatoria(7,3,20);
// 	cadena cad_test_12_3 = cad_aleatoria(5,2,10);
// 	cadena cad_test_12_4 = cad_aleatoria(2,4,40);
// 	cadena cad_test_12_5 = cad_aleatoria(1,5,20);
// 	cadena cad_test_12_6 = cad_aleatoria(3,6,10);
// 	//Ordenar cadenas
// 	ordenar(cad_test_12_1);
// 	ordenar(cad_test_12_2);
// 	ordenar(cad_test_12_3);
// 	ordenar(cad_test_12_4);
// 	ordenar(cad_test_12_5);
// 	ordenar(cad_test_12_6);
// 	// Mezcla de elementos
// 	cadena cad_mez_1 = mezcla(cad_test_12_1, cad_test_12_2);
// 	cadena cad_mez_2 = mezcla(cad_test_12_3, cad_test_12_4);
// 	cadena cad_mez_3 = mezcla(cad_test_12_5, cad_test_12_6);
// 	// Impresión de cadenas
// 	puts("## Cadena 1 y 2: ");
// 	imprimir_cadena(cad_test_12_1);
// 	imprimir_cadena(cad_test_12_2);
//     puts("-- Mezcla: ");
//     imprimir_cadena(cad_mez_1);
//     escribir_nueva_linea();
//     puts("## Cadena 3 y 4: ");
// 	imprimir_cadena(cad_test_12_3);
// 	imprimir_cadena(cad_test_12_4);
//     puts("-- Mezcla: ");
//     imprimir_cadena(cad_mez_2);
//     escribir_nueva_linea();
//     puts("## Cadena 5 y 6: ");
// 	imprimir_cadena(cad_test_12_5);
// 	imprimir_cadena(cad_test_12_6);
//     puts("-- Mezcla: ");
//     imprimir_cadena(cad_mez_3);
// 	puts("------------------------------------------");
// 	puts("FIN TEST MEZCLA");
// 	puts("##########################################\n");
    
    
//     /*
//       13)
//       Cambia todas las ocurrencias de `original' por `nuevo' en los elementos
//       de `cad'. No debe quedar memoria inaccesible.
//     */
//     puts("\n##########################################");
// 	puts("14) - TEST CAMBIAR TODOS");
// 	puts("void cambiar_todos(int original, int nuevo, cadena &cad)");
// 	puts("------------------------------------------");
// 	// Creacion de cadenas
// 	cadena cad_test_13_1 = cad_aleatoria(9,1,15);
// 	cadena cad_test_13_2 = cad_aleatoria(7,1,10);
// 	cadena cad_test_13_3 = cad_aleatoria(5,1,10);
// 	cadena cad_test_13_4 = cad_aleatoria(2,1,10);
// 	cadena cad_test_13_5 = cad_aleatoria(1,1,10);
// 	cadena cad_test_13_6 = cad_aleatoria(3,1,10);
// 	// Impresión de cadenas y procesamiento del procedimiento
// 	puts("## Cadena 1: ");
// 	imprimir_cadena(cad_test_13_1);
// 	cambiar_todos(5,8,cad_test_13_1);
// 	puts("- Cadena con cambios (5 -> 8): ");
// 	imprimir_cadena(cad_test_13_1);
// 	escribir_nueva_linea();
	
// 	puts("## Cadena 2: ");
// 	imprimir_cadena(cad_test_13_2);
// 	cambiar_todos(3,6,cad_test_13_2);
// 	puts("- Cadena con cambios (3 -> 6): ");
// 	imprimir_cadena(cad_test_13_2);
// 	escribir_nueva_linea();
	
// 	puts("## Cadena 3: ");
// 	imprimir_cadena(cad_test_13_3);
// 	cambiar_todos(1,2,cad_test_13_3);
// 	puts("- Cadena con cambios (1 -> 2): ");
// 	imprimir_cadena(cad_test_13_3);
// 	escribir_nueva_linea();
	
// 	puts("## Cadena 4: ");
// 	imprimir_cadena(cad_test_13_4);
// 	cambiar_todos(9,10,cad_test_13_4);
// 	puts("- Cadena con cambios (9 -> 10): ");
// 	imprimir_cadena(cad_test_13_4);
// 	escribir_nueva_linea();
	
// 	puts("## Cadena 5: ");
// 	imprimir_cadena(cad_test_13_5);
// 	cambiar_todos(4,8,cad_test_13_5);
// 	puts("- Cadena con cambios (4 -> 8): ");
// 	imprimir_cadena(cad_test_13_5);
// 	escribir_nueva_linea();
	
// 	puts("## Cadena 6: ");
// 	imprimir_cadena(cad_test_13_6);
// 	cambiar_todos(1,7,cad_test_13_6);
// 	puts("- Cadena con cambios (1 -> 7): ");
// 	imprimir_cadena(cad_test_13_6);
// 	puts("------------------------------------------");
// 	puts("FIN TEST CAMBIAR TODOS");
// 	puts("##########################################\n");
    
    
    
    
//     puts("\n##########################################");
// 	puts("14) - TEST FILTRADO");
// 	puts("cadena filtrado(int clave, comp_t criterio, cadena cad)");
// 	puts("------------------------------------------");
// 	/*
//           14)
//           Devuelve una cadena con los elementos que cumplen
//           "numero_info (elemento) criterio clave".
//           El orden relativo de los elementos en la cadena resultado debe ser el mismo
//           que en `cad`.
//           Si es_vacia_cadena (cad), `clave` y `criterio` son ignorados, y se devuelve la
//           cadena vacía.
//           La cadena resultado no comparte memoria con `cad`.
//      */
     
//     cad = cad_aleatoria(20, 1, 20);
//     agregar_a_cadena(5, "texto-5", cad); //agrego el 5 para probar el igual
    
//     puts("imprimo cadena original");
//  	imprimir_cadena(cad);
 	
//  	cadena filtrado_1 = filtrado(10, menor, cad);
//  	puts("menor a 10");
//  	imprimir_cadena(filtrado_1);
 	
//  	cadena filtrado_2 = filtrado(0, menor, cad);
//  	puts("menor a 0");
//  	imprimir_cadena(filtrado_2);
 	
//  	cadena filtrado_3 = filtrado(12, mayor, cad);
//  	puts("mayor a 12");
//  	imprimir_cadena(filtrado_3);
 	
//  	cadena filtrado_4 = filtrado(5, igual, cad);
//  	puts("igual a 5");
//  	imprimir_cadena(filtrado_4);
 	
//  	cadena filtrado_5 = filtrado(20, mayor, cad);
//  	puts("mayor a 20");
//  	imprimir_cadena(filtrado_5);
 	
//  	puts("------------------------------------------");
// 	puts("FIN TEST FILTRADO");
// 	puts("##########################################\n");
    
	
    
   
// 	puts("\n##########################################");
// 	puts("15) - TEST SUBCADENA - ESTÁ BIEN!!");
// 	puts("cadena subcadena(nat menor, nat mayor, cadena cad)");
// 	puts("------------------------------------------");
// 	/*
//          15)
//           Devuelve la cadena de elementos de `cad' que cumplen
//           "menor <= numero_info (elemento) <= mayor".
//           El orden relativo de los elementos en la cadena resultado debe ser el mismo
//           que en `cad'.
//           La cadena resultado no comparte memoria con `cad'.
//           Precondición: esta_ordenada (cad), `menor' <= `mayor',
//           pertenece (menor, cad), pertenece (mayor, cad).
//  */
 
//  	cadena cad_104 = crear_cadena();
//  	for(int i=0; i<10; i++){
//  	  char texto[] = "texto";
//  	  agregar_a_cadena(i, texto, cad_104);
//  	}
//  	puts("Imprimo cadena original");
//  	imprimir_cadena(cad_104);
 	
//  	cadena sub_cadena_1 = subcadena(0, 9, cad_104); //largo 10
//  	cadena sub_cadena_2 = subcadena(0, 4, cad_104); //largo 5
//  	cadena sub_cadena_3 = subcadena(5, 8, cad_104); //largo 4
//  	cadena sub_cadena_4 = subcadena(6, 6, cad_104); //largo 1
 	
//  	puts("Imprimo las 4 subcadenas");
//  	imprimir_cadena(sub_cadena_1);
//  	imprimir_cadena(sub_cadena_2);
//  	imprimir_cadena(sub_cadena_3);
//  	imprimir_cadena(sub_cadena_4);
 	
//  	assert(longitud(sub_cadena_1) == 10);
//  	assert(longitud(sub_cadena_2) == 5);
//  	assert(longitud(sub_cadena_3) == 4);
//  	assert(longitud(sub_cadena_4) == 1);
 	
//  	puts("------------------------------------------");
// 	puts("FIN TEST SUBCADENA");
// 	puts("##########################################\n");
 	

}


int main() {
    
   
    // Test info está OK!!
    //test_info();
    
    // Test cadena está OK!!
    //test_cadena();
    
    test_uso_cadena();
    
    puts("");
  
    return 0;
}
