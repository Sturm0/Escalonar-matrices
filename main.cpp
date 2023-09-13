#include <iostream>
#include <Eigen/Dense>
#include <vector>
using Eigen::MatrixXd;
int cant_filas;
int tamaño_y;
extern int* encontrar_pivote(MatrixXd matriz,int fila);

void reordenar_filas(MatrixXd* p_matriz) {
	//reordena las filas en la matriz final para que el pivote de una fila dada este a la derecha del de la fila anterior
	MatrixXd& matriz = *p_matriz;
	MatrixXd temporal(1,matriz.cols());
	for (int i = 0; i < matriz.rows()-1; i++)
	{
		if (encontrar_pivote(matriz,i) != nullptr && encontrar_pivote(matriz,i+1) != nullptr && encontrar_pivote(matriz,i)[1] > encontrar_pivote(matriz,i+1)[1])
		{
			temporal = matriz.row(i);
			matriz.row(i) = matriz.row(i+1);
			matriz.row(i+1) = temporal;
		}
	}
	
}
int* encontrar_pivote(MatrixXd matriz,int fila) {
	//encuentra el pivote de la fila y devuelve sus coordenadas, si no encuentra nada devuelve el puntero nulo
	int* coordenadas = new int[2];
	for (int i = 0; i < tamaño_y; i++)
	{
		if (matriz(fila,i)) {
			coordenadas[0] = fila;
			coordenadas[1] = i;
			return coordenadas;
		}
	}
	return nullptr;
}
int main()
{
	std::cout << "Este programa sirve para escalonar matrices de m filas y n columnas" << std::endl;
	std::cout << "Ingrese la cantidad de filas de la matriz: " << std::endl;
	std::cin >> cant_filas;
	std::cout << "Ingrese la cantidad de columnas de la matriz: " << std::endl;
	std::cin >> tamaño_y;
	std::cout << "Cuando se le pida que ingrese las filas debe ingresar los elementos de dicha separados por un espacio, ejemplo: 1 2 3" << std::endl;
	MatrixXd m(cant_filas,tamaño_y);
	for (int i = 0; i < cant_filas; i++)
	{
		std::cout << "Ingrese la fila " << i+1 << " de su matriz:" << std::endl;
		for (int j = 0; j < tamaño_y; j++)
		{
			std::cin >> m(i,j);
		}
	}
	for (int i = 0; i < 30; i++) std::cout << '-';
	std::cout << std::endl;
	int* pivotes[cant_filas];
	for (;;)
	{
		for (int i = 0; i < cant_filas; i++) pivotes[i] = encontrar_pivote(m,i);
		std::vector<int*> lista_coincidencias[tamaño_y];
		for (int i = 0; i < cant_filas; i++)
		{
			if (pivotes[i] == nullptr) continue;
			lista_coincidencias[pivotes[i][1]].push_back(pivotes[i]);
		}
		//esto sirve para saber si terminar
		int contador = 0;
		for (int i = 0; i < tamaño_y; i++)
		{
			if (lista_coincidencias[i].size() <= 1) contador++; //continuar por acá
		}
		if (contador == cant_filas) break;
		
		for (int i = 0; i < tamaño_y; i++)
		{
			if (lista_coincidencias[i].size() > 1) {
				int* elemento_referencia = lista_coincidencias[i].front();
				lista_coincidencias[i].erase(lista_coincidencias[i].begin());
				//y acá van las operaciones entre filas pertinentes
				for (unsigned int j = 0; j < lista_coincidencias[i].size(); j++)
				{
					double valor = m(lista_coincidencias[i][j][0],lista_coincidencias[i][j][1]); //mejorar el nombre de esta variable a algo más significativo
					m.row(lista_coincidencias[i][j][0]) *= m(elemento_referencia[0],elemento_referencia[1]);
					m.row(lista_coincidencias[i][j][0]) -= valor*m.row(elemento_referencia[0]);
				}
				lista_coincidencias[i].clear();
			}
		}
	}
	reordenar_filas(&m);
	std::cout << m << std::endl;
}
