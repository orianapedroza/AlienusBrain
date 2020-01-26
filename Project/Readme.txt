Para compilar ingresar a la carpeta build-unix, y modificar el fichero: Makefile.config

linea 38: modificar bandera SYSTEMC_HOME a la direccion de instalacion de systemC
linea 41: modificar bandera TARGET_ARCH: colocar linux64 para X86_64 y AMD64, linux para i386 X86

luego compilar desde /MICRO/main/ usando make, o gmake.


Nota: Si compila con versiones desactualizadas de g++ o clang es recomendable remover las banderas:
      -pedantic -Werror esto debido a que trataran los warnings como errores ademas de ser muy 
      estricto con las conversiones de tipo.

LARGA VIDA A SYSTEMC!!
