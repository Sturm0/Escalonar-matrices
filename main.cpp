#include <iostream>
#include <vector>
#include <iomanip>
#include <cstring>
/*
 * Para hacer este programa me basé en esto (https://en.wikipedia.org/wiki/Gaussian_elimination la sección que dice "echelon form"):
 * For each row in a matrix, if the row does not consist of only zeros, then the leftmost nonzero entry is called the leading coefficient (or pivot) of that row. 
 * So if two leading coefficients are in the same column, then a row operation of type 3 could be used to make one of those coefficients zero.
 *  Then by using the row swapping operation, one can always order the rows so that for every non-zero row, the leading coefficient is to the right of the leading coefficient of the row above.
*/
int cant_filas;
int cant_columnas;
struct coordenadas_pivote{
	int fila, columna;
	bool vacio = true;
};

void mostrar(double* matriz) {
    for (int i = 0; i < cant_filas; i++) {
        for (int j = 0; j < cant_columnas; j++) {
            std::cout << std::setw(4)<< matriz[i * cant_columnas + j];
        }
        std::cout << std::endl;
    }
}

void intercambiar_filas(double* m,const int filaA,const int filaB) {
	double temporal[cant_columnas];
	std::memcpy(temporal,m+filaA*cant_columnas,sizeof(double[cant_columnas]));
	std::memcpy(m+filaA*cant_columnas,m+filaB*cant_columnas,sizeof(double[cant_columnas]));
	std::memcpy(m+filaB*cant_columnas,temporal,sizeof(double[cant_columnas]));
}

void sumar_multiplo(double* m,const double escalar1 ,const int filaA,const double escalar2 = 0,const int filaB = 0) {
	//suma a una fila un múltiplo de otra, también se puede usar para multiplicar una fila por un escalar
	for (int j = 0; j < cant_columnas; j++)
	{
		m[filaA * cant_columnas + j] = (escalar1*m[filaA * cant_columnas + j]); //fijarse bien como funcionaria esta expresión teniendo en cuenta que el orden de evaluación no está garantizado
	}
	
	for (int j = 0; j < cant_columnas; j++)
	{
		m[filaA * cant_columnas + j] += escalar2*m[filaB * cant_columnas + j];
	}
}


//~ coordenadas_pivote encontrar_pivote(MatrixXd matriz,int fila) {
coordenadas_pivote encontrar_pivote(double* matriz,int fila) {
	//encuentra el pivote de la fila y devuelve sus coordenadas
	coordenadas_pivote coordenadas;
	for (int i = 0; i < cant_columnas; i++)
	{
		//~ if (matriz(fila,i)) {
		if (matriz[fila * cant_columnas + i]) {
			coordenadas.fila = fila;
			coordenadas.columna = i;
			coordenadas.vacio = false;
			break;
		}
	}
	return coordenadas;
}

void reordenar_filas(double* p_matriz) {
	//reordena las filas en la matriz para que el pivote de una fila dada este a la derecha del de la fila anterior
	for (int i = 0; i < cant_filas-1; i++)
	{
		if (encontrar_pivote(p_matriz,i).columna > encontrar_pivote(p_matriz,i+1).columna || encontrar_pivote(p_matriz,i).vacio || encontrar_pivote(p_matriz,i+1).vacio)
		{
			intercambiar_filas(p_matriz,i,i+1);
		}
	}
	
}
bool matriz_escalonada(double* m) {
	//devuelve true si la matriz argumento se encuentra escalonada, para funcionar correctamente requiere que la matriz este bien ordenada
		
	int cant_ceros[cant_filas]; //guarda cuantos ceros hay a la izquierda de cada pivote en cada fila
	for (int i = 0; i < cant_filas; i++) cant_ceros[i]=0;
	
	for (int i = 0; i < cant_filas; i++)
	{
		for (int j = 0; j < cant_columnas; j++)
		{
			if (m[i * cant_columnas + j]) break;
			cant_ceros[i]++;
		}
	}
	int asdf_asdf = 0; //guarda cuantas veces se dió que una fila tuviera menos ceros que su siguiente, cambiar el nombre a algo más significativo
	for (int i = 0; i < cant_filas-1; i++)
	{
		if (cant_ceros[i] < cant_ceros[i+1] || (cant_ceros[i] == cant_columnas && cant_ceros[i+1] == cant_columnas)) asdf_asdf++;
	}
	if (asdf_asdf == cant_filas-1) return true;
	return false;
}
int main()
{
	std::cout << "Este programa sirve para escalonar matrices de m filas y n columnas" << std::endl;
	std::cout << "Ingrese la cantidad de filas de la matriz: " << std::endl;
	std::cin >> cant_filas;
	std::cout << "Ingrese la cantidad de columnas de la matriz: " << std::endl;
	std::cin >> cant_columnas;
	std::cout << "Cuando se le pida que ingrese las filas debe ingresar los elementos de dicha separados por un espacio, ejemplo: 1 2 3" << std::endl;
	int cant_elementos = cant_filas*cant_columnas;
	double m[cant_elementos];
	for (int i = 0; i < cant_filas; i++)
	{
		std::cout << "Ingrese la fila " << i+1 << " de su matriz:" << std::endl;
		for (int j = 0; j < cant_columnas; j++)
		{
			//~ std::cin >> m(i,j);
			std::cin >> m[i * cant_columnas + j];
		}
	}
	for (int i = 0; i < 30; i++) std::cout << '-';
	std::cout << std::endl;
	coordenadas_pivote pivotes[cant_filas];
	for (;;)
	{
		reordenar_filas(m);
		//~ std::cout << m << std::endl;
		//~ std::cout << "-------------------------------------------------------------------------------------------------------" << std::endl;
		for (int i = 0; i < cant_filas; i++) pivotes[i] = encontrar_pivote(m,i);
		coordenadas_pivote lista_coincidencias[cant_columnas][cant_filas];
		unsigned int cant_piv_coincidentes[cant_columnas];
		for (int i = 0; i < cant_columnas; i++) cant_piv_coincidentes[i] = 0;
		
		for (int i = 0; i < cant_filas; i++)
		{
			if (pivotes[i].vacio) continue;
			lista_coincidencias[pivotes[i].columna][i] = pivotes[i];
			cant_piv_coincidentes[pivotes[i].columna]++;
			
		}
		if (matriz_escalonada(m)) break;
		
		for (int i = 0; i < cant_columnas; i++)
		{
			if (cant_piv_coincidentes[i] > 1) {
				coordenadas_pivote elemento_referencia = lista_coincidencias[i][0];
				
				//y acá van las operaciones entre filas pertinentes
				for (unsigned int j = 1; j < cant_piv_coincidentes[i]; j++)
				{
					double valor = m[lista_coincidencias[i][j].fila * cant_columnas + lista_coincidencias[i][j].columna]; //mejorar el nombre a algo más representativo
					sumar_multiplo(m, m[elemento_referencia.fila * cant_columnas + elemento_referencia.columna] ,lista_coincidencias[i][j].fila,-valor,elemento_referencia.fila);
				}
				cant_piv_coincidentes[i] = 0;
			}
		}
	}
	mostrar(m);
	std::cout << "Presione ENTER para cerrar el programa" << std::endl;
	char cont;
	std::cin.get(cont);
	std::cin.get(cont);
	
}
