/* 4424601 - 5015357
  Módulo de implementación de 'cadena'.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#include "../include/cadena.hpp"
#include "../include/texto.hpp"
#include "../include/info.hpp"

#include <stddef.h>
#include <stdio.h>

// nodo con punteros al anterior y al siguiente
struct nodo {
  info_t dato;
  nodo *anterior;
  nodo *siguiente;
};

// cadena implementada con cabecera con punteros al incio y al final
struct rep_cadena {
  nodo *inicio;
  nodo *final;
};

/*  Devuelve la cadena vacía (sin elementos). */
cadena crear_cadena()
{
  // se obtiene espacio para la cabecera
  // la cadena vacía no es NULL
  cadena res = new rep_cadena;
  res->inicio = res->final = NULL;
  return res;
}

/*
  Devuelve el localizador con el que se accede al inicio de `cad`.
  Si es_vacia_cadena(cad) devuelve un localizador no válido.
 */
localizador inicio_cadena(cadena cad)
{
  // Devuelvo la direccion del puntero al nodo inicial, si cad es vacia cad->inicio es NULL por definición de cad
  return cad->inicio;
} // fin inicio_cadena
/*
  Devuelve el localizador con el que se accede al final de `cad'.
  Si es_vacia_cadena(cad) devuelve un localizador no válido.
 */
localizador final_cadena(cadena cad)
{
  // Devuelvo la direccion del puntero al nodo final
 return cad->final;
} // fin final_cadena

/* Devuelve `true' si y sólo si `cad' es vacía (no tiene elementos). */
bool es_vacia_cadena(cadena cad)
{
  /* Si el inicio de la cadena es null es porque no tiene elementos,
  por lo tanto la cadena es vacía */
  return cad->inicio == NULL;
} // fin es_vacia_cadena*/

/*
  Devuelve `true' si y sólo si con `loc' se accede al primer elemento de `cad'.
  Precondición: ! es_vacia_cadena (cad).
 */
bool es_inicio_cadena(localizador loc, cadena cad)
{
  if (!es_vacia_cadena(cad))
  {
    /*Evalúa si el puntero loc apunta a la misma ubicacion de memoria que el puntero de inicio de cadena*/
    return loc == cad->inicio;
  }
  else
  {
    return false;
  }
} // fin es_inicio_cadena

/*
  Devuelve `true' si y sólo si con `loc' se accede al último elemento de `cad'.
  Precondición: ! es_vacia_cadena (cad).
 */
bool es_final_cadena(localizador loc, cadena cad)
{
  if (!es_vacia_cadena(cad))
  {
    /*Evalúa si el puntero loc apunta a la misma ubicacion de memoria que el puntero de final de cadena*/
    return loc == cad->final;
  }
  else
  {
    return false;
  }
} // fin es_final_cadena

/*
  Devuelve el localizador con el que se accede al elemento de `cad'
  inmediatamente  siguiente a `loc'.
  Si es_final_cadena(loc, cad), devuelve un localizador no válido.
  Precondición: ! es_vacia_cadena(l) y localizador_pertenece_a_cadena(loc, cad).
 */
localizador siguiente(localizador loc, cadena cad)
{
  if (!es_vacia_cadena(cad) && localizador_pertenece_a_cadena(loc, cad))
  {
    if (es_final_cadena(loc, cad))
    {
      return NULL;
    }
    else
    {
      return loc->siguiente;
    }
  }
  else
  {
    return NULL;
  }
} // fin siguiente

/*
  Devuelve el localizador con el que se accede al elemento de `cad'
  inmediatamente  anterior a `loc'.
  Si es_inicio_cadena(loc, cad), devuelve un localizador no válido.
  Precondición: ! es_vacia_cadena(l) y localizador_pertenece_a_cadena(loc, cad).
 */
localizador anterior(localizador loc, cadena cad)
{
  if (!es_vacia_cadena(cad) and localizador_pertenece_a_cadena(loc, cad))
  {
    if (es_inicio_cadena(loc, cad))
    {
      return NULL;
    }
    else
    {
      return loc->anterior;
    }
  }
  else
  {
    return NULL;
  }
} // fin anterior

/*
  Devuelve `true' si y sólo si `loc' es un localizador válido.
  En cadenas enlazadas un localizador no es válido si es `NULL'.
*/
bool es_localizador_cadena(localizador loc) 
{
  return loc != NULL;
}/*fin es_localizador_cadena*/

/*
  Devuelve `true' si y sólo si con `loc' se accede a  un elemento de `cad'.
  Precondición: ! es_vacia_cadena(cad).
 */
bool localizador_pertenece_a_cadena(localizador loc, cadena cad)
{
  bool res = false;
  localizador cursor = inicio_cadena(cad);
  while ((!res) && (es_localizador_cadena(cursor))) {
    if (cursor == loc)
      res = true;
    else
      cursor = siguiente(cursor, cad);
  }
  return res;
} // fin localizador_pertenece_a_cadena

/*
  Devuelve `true' si y sólo si `loc1' es igual o precede a `loc2` en `cad`.
  Precondición: localizador_pertenece_a_cadena(loc1, cad) y
    localizador_pertenece_a_cadena(loc2, cad).
 */
bool precede_en_cadena(localizador l1, localizador l2, cadena cad)
{
  bool precede = false;
  // Evaluacion de la precondicion, pertenencia de l1 y l2 a cad
  if (localizador_pertenece_a_cadena(l1, cad) && localizador_pertenece_a_cadena(l2, cad))
  {
    // Recorro la cadena desde l1 hasta encontrar l2, si llego al final y no la encuentro, no precede ni es igual
    localizador cursor = l1;
    while ((!precede) && (es_localizador_cadena(cursor)))
    {
      if (cursor == l2)
      {
        precede = true;
      }
      cursor = siguiente(cursor, cad);
    }
  }
  return precede;
} // fin precede_en_cadena

/*
  Se inserta `i' como un nuevo elemento inmediatamente antes de `loc'.
  Si es_vacia_cadena (cad), entonces `loc' es ignorado e `i' se inserta como
  unico elemento de `cad'.
  Precondición: es_vacia_cadena(cad) o localizador_pertenece_a_cadena(loc, cad).
 */
void insertar_antes(info_t i, localizador loc, cadena &cad)
{
  nodo *nuevo = new nodo;
  nuevo->dato = i;
  if (es_vacia_cadena(cad))
  {
    // nuevo es el único nodo, por lo que es el inicio y el final
    cad->inicio = cad->final = nuevo;
    nuevo->anterior = nuevo->siguiente = NULL;
  }
  else
  {
    nuevo->siguiente = loc;
    nuevo->anterior = anterior(loc, cad);
    loc->anterior = nuevo;

    if (loc == inicio_cadena(cad))
      cad->inicio = nuevo;
    else
      nuevo->anterior->siguiente = nuevo;
  }
} // fin insertar_antes

/*
  Se inserta `i' como un nuevo elemento inmediatamente después de `loc'.
  Si es_vacia_cadena(cad), entonces `loc' es ignorado e `i' se inserta como
  unico elemento de `cad'.
  Precondición: es_vacia_cadena(cad) o localizador_pertenece_a_cadena(loc, cad).
 */
void insertar_despues(info_t i, localizador loc, cadena &cad)
{
  nodo *nuevo = new nodo;
  nuevo->dato = i;
  if (es_vacia_cadena(cad))
  {
    cad->inicio = cad->final = nuevo;
    nuevo->anterior = nuevo->siguiente = NULL;
  }
  else
  {
    nuevo->siguiente = siguiente(loc, cad);
    nuevo->anterior = loc;
    loc->siguiente = nuevo;
    
    if (loc == final_cadena(cad))
      cad->final = nuevo;
    else
      nuevo->anterior->siguiente = nuevo;
  }
} // fin insertar_despues

/*
  Se quita el elemento referenciado en `loc' y se libera la memoria asignada
  al mismo y al nodo apuntado por el localizador.
  Si es_vacia_cadena(cad), `loc' es ignorado y no se hace nada.
  El valor de `loc' queda indeterminado.
  Precondición: es_vacia_cadena(cad) o localizador_pertenece_a_cadena(loc, cad).
 */
void remover_de_cadena(localizador &loc, cadena &cad)
{
  if (!es_vacia_cadena(cad))
  {
		// Evaluo si loc apunta al nodo que se encuetra al inicio o final de cadena
		if (es_inicio_cadena(loc, cad) || es_final_cadena(loc, cad))
		{
			if (es_inicio_cadena(loc, cad))
			{
				// Se apunta el inicio de cadena al siguiente nodo
				cad->inicio = siguiente(loc,cad);
				// Libero la memoria del nodo que apunta loc
				delete loc;
			}
			else //Es final cadena
			{
				// Se apunta el final de cadena al nodo anterior al que voy a eliminar
				cad->final = anterior(loc, cad);
				// Libero la memoria del nodo que apunta loc
				delete loc;
			}
		}
		else // Loc se encuentra en un nodo que no es inicio ni final
		{
			// Apunto siguiente del nodo anterior al siguiente de loc
			loc->anterior->siguiente = siguiente(loc, cad);
			// Apunto anterior del nodo siguiente al anterior de loc
			loc->siguiente->anterior = anterior(loc, cad);
			// Libero la memoria del nodo que apunta loc
			delete loc;
		}
  }
} // fin remover_de_cadena

/*  Libera la memoria asignada a `cad' y la de todos sus elementos. */
void liberar_cadena(cadena &cad)
{
	if (!es_vacia_cadena(cad))
	{
		// Defino cursor como el inicio de la cadena
		localizador cursor = inicio_cadena(cad);
		// Recorro la cadena mientras cursor != NULL (Final cadena)
		while (cursor != NULL)
		{
			// asigno en cursorAux el nodo a eliminar
			localizador cursorAux = cursor;
			// asigno el nodo siguiente en cursor
			cursor = siguiente(cursor, cad);
			// libero la memoria de nodo (cursorAux)
			delete cursorAux;
		}
		// Libero la memoria de cad
		delete cad;
	}
	else // cad es vacia
	{
		// Libero cad
		delete cad;
	}	
} // fin liberar_cadena

/*
  Devuelve una cadena con los elementos de `cad' que se encuentran entre
  `desde' y `hasta', inclusive.
  La cadena resultado no comparte memoria con `cad'.
  Si es_vacia_cadena(cad) devuelve la cadena vacia.
  Precondición: es_vacia_cadena(cad) o precede_cadena(desde, hasta, cad).
 */
cadena segmento_cadena(localizador desde, localizador hasta, cadena cad)
{
	cadena res = crear_cadena();
	if (!es_vacia_cadena(cad))
	{
	localizador loc = desde;
    while (loc != siguiente(hasta, cad)) {
      // ERROR: compartiría memoria
      // info_t info = loc->dato;
	  
      // ERROR: compartiría memoria
      // info_t info = crear_info(numero_info(loc->dato),
      // texto_info(loc->dato));
      info_t info = crear_info(numero_info(loc->dato), copiar_texto(texto_info(loc->dato)));
      insertar_despues(info, final_cadena(res), res);
      loc = siguiente(loc, cad);
    }
  }
  return res;
} // fin segmento_cadena

/*
  Se inserta la cadena `sgm' inmediatamente después de `loc' en `cad',
  manteniendo los elementos originales y el orden relativo entre ellos.
  No se debe obtener memoria (los nodos de `sgm' pasan a ser parte de `cad').
  Al terminar, `sgm' queda vacía.
  Si es_vacia_cadena(cad), `loc' es ignorado y el segmento queda insertado.
  Precondición: es_vacia_cadena(cad) o localizador_pertenece_a_cadena(loc, cad).
 */
void insertar_segmento_despues(cadena &sgm, localizador loc, cadena &cad)
{
	// evaluo si cad es vacia
	if (!es_vacia_cadena(cad))
	{
		// asigno como anterior del primer elemente de sgm, el nodo al que apunta cad
		sgm->inicio->anterior = loc;
		// asigno al nodo final de sgm, el siguiente de loc
		sgm->final->siguiente = loc->siguiente;
		// asigno como siguiente de loc, el primero de sgm
		loc->siguiente = sgm->inicio;
	} // cadena es vacia
	else
	{
		cad->inicio = sgm->inicio;
		cad->final = sgm->final;
	}
	// dejo sgm vacio
	sgm->inicio = sgm->final = NULL;
} // fin insertar_segmento_despues

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
cadena separar_segmento(localizador desde, localizador hasta, cadena &cad)
{
	// Obtengo memoria crando nueva cadena
	cadena cadNueva = crear_cadena();
	if (!es_vacia_cadena(cad))
	{
		/* (!!) ver donde controlar su desde, hasta precede */
		// asigno inicio y final de cadNueva
		cadNueva->inicio = desde;
		cadNueva->final = hasta;
		// Enlazo los nodos de cad "saltando" desde y hasta
		desde->anterior->siguiente = hasta->siguiente;
		hasta->siguiente->anterior = desde->anterior;
	}
	return cadNueva;
} // fin separar_segmento

/*
  Devuelve el primer localizador con el que se accede a un elemento cuyo dato
  numérico es igual a `clave', buscando desde `loc' (inclusive) hacia el final
  de `cad'.
  Si no se encuentra o `cad' es vacía, devuelve un localizador no válido.
  Precondición: es_vacia_cadena(cad) o localizador_pertenece_a_cadena(loc, cad).
 */
localizador siguiente_clave(int clave, localizador loc, cadena cad)
{
  if (es_vacia_cadena(cad))
    return NULL;
  else
  {
    while (es_localizador_cadena(loc) && numero_info(loc->dato) != clave)
      loc = siguiente(loc, cad);
    return loc;
  }
} // fin siguiente_clave

/*
  Devuelve el primer localizador con el que se accede a un elemento cuyo dato
  numérico es igual a `clave', buscando desde `loc' (inclusive) hacia el inicio
  de `cad'.
  Si no se encuentra o `cad' es vacia, devuelve un localizador no válido.
  Precondición: es_vacia_cadena(cad) o localizador_pertenece_a_cadena(loc, cad).
 */
localizador anterior_clave(int clave, localizador loc, cadena cad)
{
  if (!es_vacia_cadena(cad))
  {
    while (localizador_pertenece_a_cadena(loc,cad) && numero_info(loc->dato) != clave)
      loc = anterior(loc, cad);
    return loc;
  }
  else
  {
    return NULL;
  }
  
} // fin anterior_clave

/*
  Devuelve el localizador con el que se accede al elemento cuyo dato numérico
  es el menor en el segmento que va desde `loc' hasta el final_cadena(cad).
  Si hay más de un elemento cuyo valor es el menor, el resultado accede al que
  precede a los otros.
  Precondición: ! es_vacia_cadena(cad) y localizador_pertenece_a_cadena(loc,
  cad).
 */
localizador menor_en_cadena(localizador loc, cadena cad)
{
  if (!es_vacia_cadena(cad) && localizador_pertenece_a_cadena(loc, cad))
  {
    int menor = numero_info(loc->dato);
    localizador res;
    while (localizador_pertenece_a_cadena(loc, cad))
    {
      if (numero_info(loc->dato) < menor)
        menor = numero_info(loc->dato);
        res = loc;
      loc = siguiente(loc, cad);
    };
    return res;
  }
  else
  {
    return NULL;
  }
} // fin menor_en_cadena

/*
  Devuelve el elemento de `cad' al que se accede con `loc'.
  Precondición: ! es_vacia_cadena(cad) y localizador_pertenece_a_cadena(loc,
  cad).
 */
info_t info_cadena(localizador loc, cadena cad)
{
  if (!es_vacia_cadena(cad) && localizador_pertenece_a_cadena(loc, cad))
  {
    return loc->dato;
  }
  else
  {
    return NULL;
  }
} // info_cadena

/*
  Sustituye con `i' el elemento de `cad' al que se accede con `loc'.
xo  No destruye el elemento al que antes se accedía con `loc'.
  Precondición: ! es_vacia_cadena(cad) y localizador_pertenece_a_cadena(loc,
  cad).
 */
void cambiar_en_cadena(info_t i, localizador loc, cadena &cad)
{
  if (!es_vacia_cadena(cad) && localizador_pertenece_a_cadena(loc, cad))
  {
    loc->dato = i;
  }
} // fin cambiar_en_cadena

/*
  Intercambia los elementos a los que se accede con `loc1' y `loc2'.
  `loc1' y `loc2' mantienen su relación de precedencia.
  Precondición: ! es_vacia_cadena (cad)
  y localizador_pertenece_a_cadena (loc1, cad)
  y localizador_pertenece_a_cadena (loc2, cad).
 */
void intercambiar(localizador loc1, localizador loc2, cadena &cad)
{
  if (!es_vacia_cadena(cad) && localizador_pertenece_a_cadena(loc1, cad) && localizador_pertenece_a_cadena(loc2, cad))
  {
    info_t aux;
    aux = loc1->dato;
    loc1->dato = loc2->dato;
    loc2->dato = aux;
  }
} // fin intercambiar

/*
  Mueve el elemento al que se accede con `loc2' dejándolo inmediatamente antes
  de `loc1'.
  Los valores de `loc1' y `loc2' quedan indeterminados.
  Si loc1 == loc2 no hace nada.
  Precondición: ! es_vacia_cadena (cad)
  y localizador_pertenece_a_cadena (loc1, cad)
  y localizador_pertenece_a_cadena (loc2, cad).
 */
void mover_antes(localizador loc1, localizador loc2, cadena &cad)
{
  // En esta versión no se solicita memoria para crear nodos, sino que
  // se mueve todo el nodo que es accedido con `loc2`.
  if (loc1 != loc2) {
    // La creación de una cadena requiere espacio para la cabecera que habrá
    // que liberar al final.
    cadena sgm = separar_segmento(loc2, loc2, cad);

    // El segemento (de un elemento) se inserta antes de `loc1`.
    // Es lo que se haría si existiera la funcióm insertar_segmento_antes
    // excepto en que acá no es necesario contemplar el caso en que la cadena
    // es vacía ya que se sabe que loc1 != loc2
    sgm->inicio->anterior = anterior(loc1, cad);
    sgm->final->siguiente = loc1;
    if (es_inicio_cadena(loc1, cad)) {
      cad->inicio = inicio_cadena(sgm);
    } else {
      loc1->anterior->siguiente = inicio_cadena(sgm);
    }
    loc1->anterior = final_cadena(sgm);

    // Se libera la memoria de la cabecera de la cadena, ya vacía.
    delete sgm;
  }
} // fin mover_antes

/*
  Imprime los elementos de `cad` de la siguiente forma:
  (dn de pos1,dt de pos1)(dn de pos2,dt de pos2)(dn de pos3,dt de pos3) ...
  donce `dn` es el dato numérico y `dt` es el dato de texto.
  Antes de terminar, se debe imprimir un fin de linea.
  Si es_vacia_cadena(cad) solo se imprime el fin de línea.
 */
void imprimir_cadena(cadena cad)
{
  if (!es_vacia_cadena(cad))
  {
    localizador cursor = inicio_cadena(cad);
    while (localizador_pertenece_a_cadena(cursor, cad))
    {
      printf("(%d", numero_info(cursor->dato));
      escribir_texto(texto_info(cursor->dato));
      printf(")");
      cursor = siguiente(cursor, cad);
    };
    escribir_nueva_linea();
  }
  else
  {
    escribir_nueva_linea();
  }
} // fin imprimir_cadena