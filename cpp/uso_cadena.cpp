/* 4424601 - 5015357
  Módulo de implementación de 'uso_cadenas'.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#include "../include/utils.hpp"
#include "../include/texto.hpp"
#include "../include/info.hpp"
#include "../include/cadena.hpp"
#include "../include/uso_cadena.hpp"


/*
  1) 
  Devuelve `true' si en `cad' hay un elemento cuyo dato numérico es `i',
  o `false` en otro caso.
 */
bool pertenece(int i, cadena cad) {
  
  //recorro la cadena hasta encontrar un elemento que tenga el dato numerico i
  bool encontrado = false;
  localizador loc = inicio_cadena(cad); //parto desde el inicio de la cadena
  
  while(!encontrado && es_localizador_cadena(loc)){
    int dato_num = numero_info(info_cadena(loc , cad));
    if(dato_num == i){
      encontrado = true;
    }else{
      loc = siguiente(loc, cad);
    }
  }
  return encontrado;
}


/* 2)
  Devuelve la cantidad de elementos de `cad'. */
nat longitud(cadena cad) {
  
  nat cant = 0;
  
  localizador loc = inicio_cadena(cad); //parto desde el inicio de la cadena
  
  while(es_localizador_cadena(loc)){
    cant++;
    loc = siguiente(loc, cad);
  }
  
  return cant;
}

/* 3)
Devuelve la cantidad de elementos de `cad' cuyo dato numérico es `i'. */
nat cantidad(int i, cadena cad) {
  nat cant = 0;
    
  //recorro la cadena contando los elementos que tienen a i
  localizador loc = inicio_cadena(cad); //parto desde el inicio de la cadena
  
  while(es_localizador_cadena(loc)){
    int dato_num = numero_info(info_cadena(loc , cad));
    if(dato_num == i){
      cant++;
    }
    loc = siguiente(loc, cad);
  }
  return cant;
  
}



/*
  4)
  Devuelve `true' si y sólo si los datos numéricos de los elementos de `l1'
  son iguales uno a uno con los de los elementos de `l2' (es decir, son los
  mismos números y en el mismo orden).
  Si es_vacia_cadena(l1) y es_vacia_cadena(l2) devuelve `true'.
 */
bool son_numeros_iguales(cadena l1, cadena l2) {
  
  bool son_iguales = true;
  
  if(es_vacia_cadena(l1) && es_vacia_cadena(l2)){
    return true;
  }
  
  //Si tienen distinto tamanio, no son iguales
  if(longitud(l1) != longitud(l2)){
    return false;
  }
  
  //recorro las cadenas uno a uno comparando, hasta que encuentre un desigual, o termine de comparar
  localizador loc_1 = inicio_cadena(l1); //parto desde el inicio de l1
  localizador loc_2 = inicio_cadena(l2); //parto desde el inicio de l2
  
  while(son_iguales && es_localizador_cadena(loc_1) && es_localizador_cadena(loc_2)){
    if(numero_info(info_cadena(loc_1 , l1)) != numero_info(info_cadena(loc_2 , l2))){
     son_iguales = false;
    }
    loc_1 = siguiente(loc_1, l1);
    loc_2 = siguiente(loc_2, l2);
  }
  return son_iguales;
}

/*
  5)
  Devuelve `true' si y sólo si `cad' está ordenada de forma no decreciente
  (= creciente de manera no estricta) según  los datos numéricos de sus
  elementos.
  Si es_vacia_cadena (cad), devuelve `true'.
 */
bool esta_ordenada(cadena cad) {
  bool res = true;
  if (!es_vacia_cadena(cad)) {
    localizador loc = inicio_cadena(cad);
    while (res && es_localizador_cadena(siguiente(loc, cad))) {
      localizador sig_loc = siguiente(loc, cad);
      if (numero_info(info_cadena(loc, cad)) >
          numero_info(info_cadena(sig_loc, cad)))
        res = false;
      else
        loc = siguiente(loc, cad);
    }
  }
  return res;
}

/*
  6) 
  Devuelve el resultado de concatenar `l2' después de `l1'.
  La cadena resultado no comparte memoria ni con `l1' ni con `l2'.
 */
cadena concatenar(cadena l1, cadena l2) {
  
  //Como no comparten memoria, se crea una nueva cadena.
  cadena nueva_cadena = crear_cadena();

  //Primero se copian los elementos de l1
  localizador loc_l1 = inicio_cadena(l1);
  while(es_localizador_cadena(loc_l1)){
     localizador ultimo_nueva_cadena = final_cadena(nueva_cadena);
     
     info_t info_cad1 = crear_info(numero_info(info_cadena(loc_l1,l1)), copiar_texto(texto_info(info_cadena(loc_l1,l1))));
     
     insertar_despues(info_cad1, ultimo_nueva_cadena, nueva_cadena);
     
     loc_l1 = siguiente(loc_l1, l1);
  }
  
  // Luego se copian los elementos de l2
  localizador loc_l2 = inicio_cadena(l2);
  while(es_localizador_cadena(loc_l2)){
     localizador ultimo_nueva_cadena = final_cadena(nueva_cadena);
     
     info_t info_cad2 = crear_info(numero_info(info_cadena(loc_l2,l2)), copiar_texto(texto_info(info_cadena(loc_l2,l2))));
     
     insertar_despues(info_cad2, ultimo_nueva_cadena, nueva_cadena);
     
     loc_l2 = siguiente(loc_l2, l2);
  }
  
  return nueva_cadena;
}

 /* 7)
  Devuelve la cadena que tiene todos los elementos de `cad' pero en orden
  inverso.
  La cadena resultado no comparte memoria con `cad'.
 */
cadena reversa(cadena cad) {
  
  //Como no comparten memoria, se crea una nueva cadena.
  cadena nueva_cadena = crear_cadena();
  
    
  //Al ser una lista doblemente enlazada, arranco por el final
  localizador loc = final_cadena(cad);
  
  while(es_localizador_cadena(loc)){
   localizador ultimo_nueva_cadena = final_cadena(nueva_cadena);
   
   //Se obtiene la info nueva
   info_t info = crear_info(numero_info(info_cadena(loc,cad)), copiar_texto(texto_info(info_cadena(loc,cad))));
   
   insertar_despues(info, ultimo_nueva_cadena, nueva_cadena);
   loc = anterior(loc, cad);
  }
  
  return nueva_cadena;
}

/*
  8)
  Devuelve el localizador que accede al primer elemento, empezando desde el
  inicio de `cad' y anterior a `loc', cuyo dato numérico es mayor que el del
  elemento que se accede desde `loc'.
  Si ninguno de los elementos anteriores es mayor devuelve `loc'.
  Precondición: ! es_vacia_cadena (cad), pertenece_localizador_cadena (loc, cad)
  y `cad' está ordenada de manera creciente (no estricta) según su dato
  numérico desde el inicio hasta el anterior a `loc'.
 */
localizador primer_mayor(localizador loc, cadena cad) {
    
  localizador loc_cad = inicio_cadena(cad); //localizador a comparar
  int dato_num_loc = numero_info(info_cadena(loc, cad));
  bool encontrado = false;
  
  // Se le agrega que loc_cad sea diferente a loc porque sino sigue evaluando el resto de la cadena
  while(es_localizador_cadena(loc_cad) && (loc_cad != loc) && !encontrado)
  {
    // Dato numerico al que estoy accediendo para luego comparar
    int dato_num = numero_info(info_cadena(loc_cad, cad));
    // Evalúo si es mayor al dato numerico de loc
    if(dato_num > dato_num_loc)
    {
      encontrado = true;
    }
    else
    {
      loc_cad = siguiente(loc_cad, cad);
    }
  }
  
  if(encontrado){
    return loc_cad;
  }else{
    return loc;
  }
}

/*
  9)
  Mueve el elemento al que se accede con `loc' dejéndolo inmediatamente antes
  de los elementos cuyos datos numéricos son mayores que dicho elemento.
  El valor de `loc' queda ideterminado.
  Si el dato numérico de `loc' es mayor o igual que el los de los que lo
  preceden no hace nada.
  Precondición: ! es_vacia_cadena (cad), pertenece_localizador_cadena (loc, cad)
  y `cad' está ordenada de manera creciente (no estricta) según su dato
  numérico desde el inicio hasta el anterior a `loc'.
 */
void retroceder(localizador loc, cadena &cad) {
  localizador pto_ins = primer_mayor(loc, cad);
  mover_antes(pto_ins, loc, cad);
}

/*
  10)
  Se ordena `cad' de manera creciente según los datos numéricos de sus
  elementos.
  Si los datos numéricos de dos elementos son iguales, se mantiene el orden
  relativo que tenían dichos elementos inicialmente.
  No se debe obtener ni devolver memoria de manera dinámica.
  Si es_vacia_cadena (cad) no hace nada.
 */

void ordenar(cadena &cad) {

  if(!es_vacia_cadena(cad)){// si es vacia, no hace nada
    
    localizador cad_ord = inicio_cadena(cad);  // ultimo puntero a fin sub-lista ordenada
    
    // Recorro la cedena original de izquierda a derecha    
    while(es_localizador_cadena(cad_ord)){
     
      //localizador cad_ord_aux = cad_ord;
      localizador ant = anterior(cad_ord, cad); //navego hacia la izquierda hasta encontrar un ordenado
  
	bool ordenado = false;
	while(es_localizador_cadena(ant) && !ordenado){
		//si el anterior es mayor a cad_ord los swapeo
		if(numero_info(info_cadena(ant, cad)) > numero_info(info_cadena(cad_ord, cad))){
			intercambiar(ant, cad_ord, cad);	
			cad_ord = ant;		
		}else{
			ordenado = true;
		}
		ant = anterior(ant, cad);
	}      
      cad_ord = siguiente(cad_ord, cad); // avanzo un lugar     
    }
  }
}

/*
  11)
  Elimina los elementos con datos numéricos repetidos, conservando el primero
  de ellos.
  Libera la memoria de los elementos que elimina.
  Precondición: esta_ordenada (cad).
 */
void unificar(cadena &cad) {
  if (!es_vacia_cadena(cad)) {
    localizador loc = inicio_cadena(cad);
    // se cumplen las precondiciones de `siguiente`
    localizador sig_loc = siguiente(loc, cad);

    while (es_localizador_cadena(sig_loc)) {
      if (numero_info(info_cadena(loc, cad)) == numero_info(info_cadena(sig_loc, cad))){
        remover_de_cadena(sig_loc, cad);
      }
      else{
         loc = sig_loc;
      }
      sig_loc = siguiente(loc, cad);
    }
  }
}

/*
  Funcion privada, se usa en (mezcla, filtrar, subcadena)
  
  Recibe como parametro un localizador, una cadena, y una nueva cadena.
  Agrega un nuevo localizador, (siguiente) en la nueva cadena.
  
*/
void agregar_en_nueva_cadena(localizador loc, cadena cad, cadena &nueva_cadena) {
  
  info_t info = crear_info(numero_info(info_cadena(loc, cad)), copiar_texto(texto_info(info_cadena(loc, cad))));
  
  localizador final = final_cadena(nueva_cadena); //obtengo el ultimo localizador de la nueva_cadena
  
  insertar_despues(info, final, nueva_cadena);
}

/*
  12)
  Devuelve una cadena con todos los elementos de `l1' y `l2' ordenada de manera
  creciente segun sus datos numéricos.
  Si hay elementos cuyos datos numéricos son iguales, los elementos de `l1'
  quedan antes de los de `l2'.
  La cadena resultado no comparte memoria ni con `l1' ni con `l2'.
  Precondición: esta_ordenada (l1) y esta_ordenada (l2).
 */
cadena mezcla(cadena l1, cadena l2) {
  
  /* Al estar ambas cadenas ordenadas, voy recorriendo una a una y comparando
     La que es menor la agrego a la nueva lista, y avanzo un lugar en esa cadena.
  */
  
   cadena nueva_cadena = crear_cadena();
  
   localizador loc_1 = inicio_cadena(l1);
   localizador loc_2 = inicio_cadena(l2);
   
   while(es_localizador_cadena(loc_1) || es_localizador_cadena(loc_2)){ //mientras haya al menos un elemento en ambas cadenas
   
     // A)  Si no hay mas en l1, relleno la nueva cadena con l2, avanzo un lugar
     if(!es_localizador_cadena(loc_1) && es_localizador_cadena(loc_2)){
       agregar_en_nueva_cadena(loc_2, l2, nueva_cadena);
       loc_2 = siguiente(loc_2, l2);
     }
     
      // B)  Si no hay mas en l2, relleno la nueva cadena con l1, avanzo un lugar
     if(!es_localizador_cadena(loc_2) && es_localizador_cadena(loc_1)){
       agregar_en_nueva_cadena(loc_1, l1, nueva_cadena);
       loc_1 = siguiente(loc_1, l1);
     }
     
     /* C)  Si hay elementos tanto en l1 como en l2, obtengo el menor y avanzo un lugar,
            si son iguales, agrego primero loc_1*/
     if(es_localizador_cadena(loc_1) && es_localizador_cadena(loc_2)){
       
       if(numero_info(info_cadena(loc_2, l2)) < numero_info(info_cadena(loc_1, l1))){
         agregar_en_nueva_cadena(loc_2, l2, nueva_cadena);
         loc_2 = siguiente(loc_2, l2);
       }else{
         agregar_en_nueva_cadena(loc_1, l1, nueva_cadena);
         loc_1 = siguiente(loc_1, l1);
       }
       
     }
     
   }
  return nueva_cadena;
}

/*
  13)
  Cambia todas las ocurrencias de `original' por `nuevo' en los elementos
   de `cad'. No debe quedar memoria inaccesible.
 */
void cambiar_todos(int original, int nuevo, cadena &cad) {
  localizador loc = inicio_cadena(cad);
  while (es_localizador_cadena(loc)) {
    if (numero_info(info_cadena(loc, cad)) == original) {
      info_t info = info_cadena(loc, cad);
      info_t nueva_info = crear_info(nuevo, copiar_texto(texto_info(info)));
      cambiar_en_cadena(nueva_info, loc, cad);
      // libera la info que no libera cambiar_en_cadena
      liberar_info(info);
    }
    loc = siguiente(loc, cad);
  }
}


/*
  14)
  Devuelve una cadena con los elementos que cumplen
  "numero_info (elemento) criterio clave".
  El orden relativo de los elementos en la cadena resultado debe ser el mismo
  que en `cad`.
  Si es_vacia_cadena (cad), `clave` y `criterio` son ignorados, y se devuelve la
  cadena vacía.
  La cadena resultado no comparte memoria con `cad`.
 */
cadena filtrado(int clave, comp_t criterio, cadena cad) {
  
  
  if(!es_vacia_cadena(cad)){
    
    cadena nueva_cadena = crear_cadena();
    
    localizador loc = inicio_cadena(cad);
    
    //Como no es una precondicion que la cadena esté ordenada, la recorro toda para comparar todos los elementos
    while(es_localizador_cadena(loc)){
      
     int num = numero_info(info_cadena(loc, cad));
      
     switch (criterio) {
        case menor: {
          if(num < clave){
            agregar_en_nueva_cadena(loc, cad, nueva_cadena);
          }
          break;
        }
        case igual: {
          if(num == clave){
            agregar_en_nueva_cadena(loc, cad, nueva_cadena);  
          }
          break;
        }
        case mayor: {
          if(num > clave){
            agregar_en_nueva_cadena(loc, cad, nueva_cadena);
          }
          break;
        }
      }
     
      loc = siguiente(loc, cad);
    }
    
    return nueva_cadena;
    
  }else{
    return cad;
  }
}

/*
  15)
  Devuelve la cadena de elementos de `cad' que cumplen
  "menor <= numero_info (elemento) <= mayor".
  El orden relativo de los elementos en la cadena resultado debe ser el mismo
  que en `cad'.
  La cadena resultado no comparte memoria con `cad'.
  Precondición: esta_ordenada (cad), `menor' <= `mayor',
  pertenece (menor, cad), pertenece (mayor, cad).
 */
cadena subcadena(nat menor, nat mayor, cadena cad) {
  
  cadena sub_cadena = crear_cadena();
  localizador loc = inicio_cadena(cad);
  bool terminar = false;
  
  while(es_localizador_cadena(loc) && !terminar){
    nat num = numero_info(info_cadena(loc, cad));
    
    if(num <= mayor){
      if(menor <= num){
        agregar_en_nueva_cadena(loc, cad, sub_cadena);  
      }
    }else{ //si el numero supera la cota superior, termino el while
      terminar = true;
    }

    loc = siguiente(loc, cad);
  }
  
  return sub_cadena;
}


