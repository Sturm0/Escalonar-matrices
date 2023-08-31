#include <iostream>
int main()
{
	int a,b,c,d,e,f,g,h,i;
	std::cout << "Este programa sirve para escalonar matrices de 3x3" << std::endl;
	std::cout << "Ingrese la primera fila de su matriz separando cada elemento con un espacio: " << std::endl;
	std::cin >> a;
	std::cin >> b;
	std::cin >> c;
	std::cout << "Ahora la segunda fila: " << std::endl;
	std::cin >> d;
	std::cin >> e;
	std::cin >> f;
	std::cout << "Ahora la tercera fila: " << std::endl;
	std::cin >> g;
	std::cin >> h;
	std::cin >> i;
	std::cout << "Resultado:" << std::endl;
	std::cout << a << " " << b << " " << c << std::endl;
	std::cout << 0 << " " << a*e-d*b << " " << a*f-d*c << std::endl;
	std::cout << 0 << " " << 0 << " " << (a*e-d*b)*(a*i-g*c)-(a*h-g*b)*(a*f-d*c) << std::endl;
	return 0;
}
