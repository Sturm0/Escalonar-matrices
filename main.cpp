#include <iostream>
#include <Eigen/Dense>
#include <vector>
/*
 * Para hacer este programa me basé en esto (https://en.wikipedia.org/wiki/Gaussian_elimination la sección que dice "echelon form"):
 * For each row in a matrix, if the row does not consist of only zeros, then the leftmost nonzero entry is called the leading coefficient (or pivot) of that row. 
 * So if two leading coefficients are in the same column, then a row operation of type 3 could be used to make one of those coefficients zero.
 *  Then by using the row swapping operation, one can always order the rows so that for every non-zero row, the leading coefficient is to the right of the leading coefficient of the row above.
*/
using Eigen::MatrixXd;
int cant_filas;
int cantidad_columnas;
struct coordenadas_pivote{
	int fila, columna;
	bool vacio = true;
};
coordenadas_pivote encontrar_pivote(MatrixXd matriz,int fila) {
	//encuentra el pivote de la fila y devuelve sus coordenadas
	coordenadas_pivote coordenadas;
	for (int i = 0; i < cantidad_columnas; i++)
	{
		if (matriz(fila,i)) {
			coordenadas.fila = fila;
			coordenadas.columna = i;
			coordenadas.vacio = false;
			break;
		}
	}
	return coordenadas;
}

void reordenar_filas(MatrixXd* p_matriz) {
	//reordena las filas en la matriz para que el pivote de una fila dada este a la derecha del de la fila anterior
	MatrixXd& matriz = *p_matriz;
	MatrixXd temporal(1,matriz.cols());
	for (int i = 0; i < matriz.rows()-1; i++)
	{
		if (encontrar_pivote(matriz,i).columna > encontrar_pivote(matriz,i+1).columna || encontrar_pivote(matriz,i).vacio || encontrar_pivote(matriz,i+1).vacio)
		{
			temporal = matriz.row(i);
			matriz.row(i) = matriz.row(i+1);
			matriz.row(i+1) = temporal;
		}
	}
	
}
bool matriz_escalonada(MatrixXd m) {
	//devuelve true si la matriz argumento se encuentra escalonada, para funcionar correctamente requiere que la matriz este bien ordenada
		
	int cant_ceros[cant_filas]; //guarda cuantos ceros hay a la izquierda de cada pivote en cada fila
	for (int i = 0; i < cant_filas; i++) cant_ceros[i]=0;
	
	for (int i = 0; i < cant_filas; i++)
	{
		for (int j = 0; j < cantidad_columnas; j++)
		{
			if (m(i,j)) break;
			cant_ceros[i]++;
		}
	}
	int asdf_asdf = 0; //guarda cuantas veces se dió que una fila tuviera menos ceros que su siguiente, cambiar el nombre a algo más significativo
	for (int i = 0; i < cant_filas-1; i++)
	{
		if (cant_ceros[i] < cant_ceros[i+1] || (cant_ceros[i] == cantidad_columnas && cant_ceros[i+1] == cantidad_columnas)) asdf_asdf++;
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
	std::cin >> cantidad_columnas;
	std::cout << "Cuando se le pida que ingrese las filas debe ingresar los elementos de dicha separados por un espacio, ejemplo: 1 2 3" << std::endl;
	MatrixXd m(cant_filas,cantidad_columnas);
	for (int i = 0; i < cant_filas; i++)
	{
		std::cout << "Ingrese la fila " << i+1 << " de su matriz:" << std::endl;
		for (int j = 0; j < cantidad_columnas; j++)
		{
			std::cin >> m(i,j);
		}
	}
	for (int i = 0; i < 30; i++) std::cout << '-';
	std::cout << std::endl;
	coordenadas_pivote pivotes[cant_filas];
	for (;;)
	{
		reordenar_filas(&m);
		std::cout << m << std::endl;
		for (int i = 0; i < 40; i++) std::cout << "-";
		std::cout << std::endl;
		
		for (int i = 0; i < cant_filas; i++) pivotes[i] = encontrar_pivote(m,i);
		std::vector<coordenadas_pivote> lista_coincidencias[cantidad_columnas];
		for (int i = 0; i < cant_filas; i++)
		{
			if (pivotes[i].vacio) continue;
			lista_coincidencias[pivotes[i].columna].push_back(pivotes[i]);
		}
		if (matriz_escalonada(m)) break;
		
		for (int i = 0; i < cantidad_columnas; i++)
		{
			if (lista_coincidencias[i].size() > 1) {
				coordenadas_pivote elemento_referencia = lista_coincidencias[i].front();
				lista_coincidencias[i].erase(lista_coincidencias[i].begin());
				//y acá van las operaciones entre filas pertinentes
				for (unsigned int j = 0; j < lista_coincidencias[i].size(); j++)
				{
					double valor = m(lista_coincidencias[i][j].fila,lista_coincidencias[i][j].columna); //mejorar el nombre de esta variable a algo más significativo
					m.row(lista_coincidencias[i][j].fila) *= m(elemento_referencia.fila,elemento_referencia.columna);
					m.row(lista_coincidencias[i][j].fila) -= valor*m.row(elemento_referencia.fila);
				}
				lista_coincidencias[i].clear();
			}
		}
	}
	
	std::cout << m << std::endl;
	std::cout << "Presione ENTER para cerrar el programa" << std::endl;
	char cont;
	std::cin.get(cont);
	std::cin.get(cont);
	
}
