# Escalonar-matrices
Programa para escalonar matrices, por ahora solo de 3xn.
## Cómo usarlo
El programa en sí es el main.exe y el main.out. Usar el main.exe si se está en Windows o el main.out si se esta utilizando un sistema GNU/Linux. Si se esta utilizando otra plataforma más abajo hay instrucciones para compilar manualmente el programa.

Para ejecutarlo:

(en ambos casos suponiendo que se está en una terminal en el directorio donde se encuentra el programa)

En GNU/Linux:

`./main.out`

En Windows:

`main.exe`

## Compilarlo manualmente
Aclaración: Esto solo es requerido en caso que no se hayan provisto los binarios correspondientes a la plataforma que esta utilizando o en caso que haya hecho cambios en el código fuente.

Usando gcc sería:

`g++ -I eigen main.cpp`

El archivo main.cpp y la carpeta "eigen" solo son relevantes si se planea compilar manualmente el programa, en caso que ello no le sea relevante sientase libre de eliminarlos (no afectará el funcionamiento del programa).
