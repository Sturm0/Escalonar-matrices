#include <iostream>
#include <Eigen/Dense>
using Eigen::MatrixXd;

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
	m.row(1) = m(0,0)*m.row(1)-m(1,0)*m.row(0);
	m.row(2) = m(0,0)*m.row(2)-m(2,0)*m.row(0);
	m.row(2) = (m(0,0)*m(1,1)-m(1,0)*m(0,1))*m.row(2)-(m(0,0)*m(2,1)-m(2,0)*m(0,1))*m.row(1);
	std::cout << m << std::endl;
}
