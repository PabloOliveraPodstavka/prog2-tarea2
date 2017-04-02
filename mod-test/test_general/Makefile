
# --------------------------------------------------------------------
#  Makefile uso_cadena 

 # DE MOMENTO SOLO SE COMPILA, el testing esta por verse..  :)


# Objetivos que no son archivos.
.PHONY: all principal clean_bin


# Objetivo predeterminado (no se necesita especificarlo al invocar `make').
all: principal

# compilador
CC = g++
# opciones de compilación
CCFLAGS = -Wall -Werror -Iinclude -g
# -DNDEBUG
# se agrega esta opción para que las llamadas a assert no hagan nada.


# borra binarios
clean_bin:
	@rm -f test_general ../../obj/*.o
	
	# principal
principal: clean_bin test_general



# La construccion de todos los modulos
utils.o: ../../cpp/utils.cpp ../../include/utils.hpp
	$(CC) $(CCFLAGS) -c ../../cpp/utils.cpp -o ../../obj/utils.o

texto.o: ../../cpp/texto.cpp ../../include/texto.hpp utils.o
	$(CC) $(CCFLAGS) -c ../../cpp/texto.cpp -o ../../obj/texto.o

info.o: ../../cpp/info.cpp ../../include/info.hpp texto.o
	$(CC) $(CCFLAGS) -c ../../cpp/info.cpp -o ../../obj/info.o
	
# NICO desarrollando
cadena.o: ../../cpp/cadena.cpp ../../include/cadena.hpp texto.o info.o
	$(CC) $(CCFLAGS) -c ../../cpp/cadena.cpp -o ../../obj/cadena.o
	
uso_cadena.o: ../../cpp/uso_cadena.cpp ../../include/uso_cadena.hpp cadena.o info.o texto.o utils.o
	$(CC) $(CCFLAGS) -c ../../cpp/uso_cadena.cpp -o ../../obj/uso_cadena.o

test_general.o: utils.o texto.o info.o cadena.o uso_cadena.o 
	$(CC) $(CCFLAGS) -c test_general.cpp -o test_general.o


#Principal
test_general: utils.o texto.o info.o cadena.o uso_cadena.o test_general.o
	$(CC) $(CCFLAGS) ../../obj/uso_cadena.o  ../../obj/cadena.o ../../obj/texto.o ../../obj/info.o test_general.o -o test_general



