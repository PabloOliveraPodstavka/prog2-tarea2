/* 
        TEST DE USO_CADENA 
        
        Ho hace falta hacer un delete de los new, ya que estos duran en la vida de este test.
        Una vez que finalizan, se mueren solos.
        
        
 */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../../include/utils.hpp"
#include "../../include/texto.hpp"
#include "../../include/info.hpp"
#include "../../include/cadena.hpp"
#include "../../include/uso_cadena.hpp"


int main() {
    
    /* Se construye cadena generica de n nodos para pruebas
    */
    // int largo_cadena = 10;
    
    //ESTRUCTURA CADENA -> REP_CADENA
    cadena cad = crear_cadena();

    info_t info = crear_info(3, array_a_texto("t"));
    
    // localizador loc = inicio_cadena(cad);
    // insertar_antes(info, loc, cad);
    // punt_nodo nodo_anterior = NULL; //nodo auxiliar, el anterior
    
    // for(int i=0;i<largo_cadena;i++){
        
    //     //ESTRUCTURA NODO
    //     punt_nodo nuevo_nodo = new nodo; 
        
    //     //ESTRUCTURA INFO_T -> REP_INFO
    //     info_t nuevo_info = new rep_info;
    //     nuevo_info->numero = i; //este numero se usa en prueba 1, por ejemplo
    //     //nuevo_info->texto = todo!! no lo uso de momento
        
    //     nuevo_nodo->dato = nuevo_info;
      
    //     if(i==0){   /*Inicio*/
    //       cadena_prueba->inicio = nuevo_nodo;
    //     }else if( i == largo_cadena){   /*Fin*/
    //       cadena_prueba->fin = nuevo_nodo; 
    //       nuevo_nodo->siguiente = null; //es el ultimo, no hay siguiente
    //     }
        
    //     //armo el doble enlace
    //     nuevo_nodo->anterior = nodo_anterior;
    //     if(nodo_anterior!=null){
    //       nodo_anterior->siguiente = nuevo_nodo;
    //     }
        
    //     //Guardo el nodo, para referenciarlo en el siguiente
    //     nodo_anterior = nuevo_nodo;
        
    // }
    // puts("Construccion de la estructura de pruebas satisfactoria!");
    
    // s
    // /* TEST 1  (pertenece)
    // */
    // puts("Inicio Test 1 (pertenece)");
    // //prueba 1
    // int test1_int_p1 = 0; 
    // bool res_pertenece = pertenece(test1_int_p1, cadena_prueba);
    // assert(res_pertenece); //debe dar true
    // //prueba 2
    // int test1_int_p2 = 5; 
    // bool res_pertenece = pertenece(test1_int_p2, cadena_prueba);
    // assert(res_pertenece); //debe dar true
    // //prueba 3
    // int test1_int_p3 = 9; 
    // bool res_pertenece = pertenece(test1_int_p3, cadena_prueba);
    // assert(res_pertenece); //debe dar true
    // //prueba 4
    // int test1_int_p4 = 15; 
    // bool res_pertenece = pertenece(test1_int_p4, cadena_prueba);
    // assert(!res_pertenece); //debe dar false
    // puts("Fin Test 1 (pertenece)");
    

    
    // puts("Fin Test uso_cadena !!");
    return 0;
}
