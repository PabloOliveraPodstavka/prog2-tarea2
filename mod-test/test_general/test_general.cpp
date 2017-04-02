/* 
        TEST GENERAL
 */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>

#include "../../include/utils.hpp"
#include "../../include/texto.hpp"
#include "../../include/info.hpp"
#include "../../include/cadena.hpp"
#include "../../include/uso_cadena.hpp"


int main() {
    
    //variables globales a los test
    int num = 10;
    
    char texto[] = "prueba";
    info_t info_1;

    //TST DE INFO.CPP
    puts("INICIO DE TEST PARA INFO.CPP!");
  
    
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
    
    
    
    
    
    puts("TODOS LOS TEST ESTAN BIEN :)");
    puts("");
    return 0;
}
