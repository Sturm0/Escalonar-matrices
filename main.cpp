#include <iostream>
#include <Eigen/Dense>
using Eigen::MatrixXd;
//~ void cambiar_pivote(MatrixXd* matriz, n_columna) {
	//~ //se encarga de asegurarse que aquello que va a usarse como pivote sea diferente de 0, si llega a ser igual a 0 intercambia
	//~ //filas para asegurarse que sea diferente y si no no hace nada. Probablemente "pivote" no es el término correcto para lo que
	//~ //quiero expresar, revisar después cual sería.
	//~ //lleva "para arriba" a la fila con un elemento no nulo en la columna argumento
//~ }
int main()
{
	int tamaño_y;
	std::cout << "Este programa sirve para escalonar matrices de 3 filas y n columnas" << std::endl;
	std::cout << "Ingrese la cantidad de columnas de la matriz: " << std::endl;
	std::cin >> tamaño_y;
	std::cout << "Cuando se le pida que ingrese las filas debe ingresar los elementos de dicha separados por un espacio, ejemplo: 1 2 3" << std::endl;
	MatrixXd m(3,tamaño_y);
	for (int i = 0; i < 3; i++)
	{
		std::cout << "Ingrese la fila " << i+1 << " de su matriz:" << std::endl;
		for (int j = 0; j < tamaño_y; j++)
		{
			std::cin >> m(i,j);
		}
	}
	for (int i = 0; i < 20; i++) std::cout << '-';
	std::cout << std::endl;
	if (!m(0,0)) {
		for (int i = 1; i < tamaño_y; i++)
		{
			MatrixXd temporal(1,tamaño_y);
			if (m(i)) {
				//esto solo es requerido porque no tengo idea cual sería la función swap que sirve para eigen
				std::cout << "esto es m(i): " << m(i) << std::endl;
				temporal = m.row(0);
				m.row(0) = m.row(i);
				m.row(i) = temporal;
				break;
			}
		}
	}
	if (m(1,0)) m.row(1) = m(0,0)*m.row(1)-m(1,0)*m.row(0);
	if (m(2,0)) m.row(2) = m(0,0)*m.row(2)-m(2,0)*m.row(0);
	if (m(2,1)) m.row(2) = m(1,1)*m.row(2)-m(2,1)*m.row(1);
	std::cout << m << std::endl;
	
	
}
