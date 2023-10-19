// Actividad 4.1 Implementación Intersección y proximidad aplicando geometría computacional.
// Andrea San Martin Vital - A00833676

#include <iostream>
#include <cmath>
#include <limits>
#include <vector>
#include <iterator>
#include <sstream>
#include <cstring>
using namespace std;

struct Point {
    double x;
    double y;
};

struct Line {
    Point start;
    Point end;
};

bool sonParalelas(const Line& linea1, const Line& linea2) {
    double pendiente1 = (linea1.end.y - linea1.start.y) / (linea1.end.x - linea1.start.x);
    double pendiente2 = (linea2.end.y - linea2.start.y) / (linea2.end.x - linea2.start.x);

    return pendiente1 == pendiente2;
}

Point encontrarInterseccion(const Line& linea1, const Line& linea2) {
    double pendiente1 = (linea1.end.y - linea1.start.y) / (linea1.end.x - linea1.start.x);
    double pendiente2 = (linea2.end.y - linea2.start.y) / (linea2.end.x - linea2.start.x);

    double x = (pendiente1 * linea1.start.x - pendiente2 * linea2.start.x + linea2.start.y - linea1.start.y) / (pendiente1 - pendiente2);
    double y = pendiente1 * (x - linea1.start.x) + linea1.start.y;

    if (x >= min(linea1.start.x, linea1.end.x) &&
        x <= max(linea1.start.x, linea1.end.x) &&
        x >= min(linea2.start.x, linea2.end.x) &&
        x <= max(linea2.start.x, linea2.end.x) &&
        y >= min(linea1.start.y, linea1.end.y) &&
        y <= max(linea1.start.y, linea1.end.y) &&
        y >= min(linea2.start.y, linea2.end.y) &&
        y <= max(linea2.start.y, linea2.end.y)) {
        Point puntoInterseccion;
        puntoInterseccion.x = x;
        puntoInterseccion.y = y;
        return puntoInterseccion;
    }

    Point puntoInvalido;
    puntoInvalido.x = numeric_limits<double>::quiet_NaN();
    puntoInvalido.y = numeric_limits<double>::quiet_NaN();
    return puntoInvalido;
}

int main() {
    int n;
    cout << "Ingresa el número de conjuntos (n): ";
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<string> resultado;

    cout << "\nIngresa, en cada línea, cuatro puntos (x1,y1 x2,y2 x3,y3 x4,y4): " << endl;

    for (int i = 0; i < n; i++) {
        Point punto1, punto2, punto3, punto4;

        string entradaLinea;
        getline(cin, entradaLinea);

        istringstream iss(entradaLinea);
        vector<string> puntos((istream_iterator<string>(iss)), istream_iterator<string>());

        if (puntos.size() != 4) {
            cout << "\nError" << endl;
            i--;
            continue;
        }

        int leido1 = sscanf(puntos[0].c_str(), "%lf,%lf", &punto1.x, &punto1.y);
        int leido2 = sscanf(puntos[1].c_str(), "%lf,%lf", &punto2.x, &punto2.y);
        int leido3 = sscanf(puntos[2].c_str(), "%lf,%lf", &punto3.x, &punto3.y);
        int leido4 = sscanf(puntos[3].c_str(), "%lf,%lf", &punto4.x, &punto4.y);

        if (leido1 != 2 || leido2 != 2 || leido3 != 2 || leido4 != 2) {
            cout << "\nFormato inválido." << endl;
            i--;
            continue;
        }

        Line linea1 = {punto1, punto2};
        Line linea2 = {punto3, punto4};

        if (sonParalelas(linea1, linea2)) {
            resultado.push_back("False");
        } else {
            Point interseccion = encontrarInterseccion(linea1, linea2);
            if (!isnan(interseccion.x) && !isnan(interseccion.y)) {
                resultado.push_back("True");
            } else {
                resultado.push_back("False");
            }
        }
    }

    cout << "\nResultado: " << endl;

    for (const string& res : resultado) {
        cout << res << endl;
    }

    return 0;
}

/*CASOS DE PRUEBA: 

CASO 1: 
Ingresa el número de conjuntos (n): 3

Ingresa, en cada línea, cuatro puntos (x1,y1 x2,y2 x3,y3 x4,y4): 
1,5 7,1 1,4 10,9
10,2 1,12 3,3 0,15
-6,-6 3,4 2,2 1,1

Resultado: 
True
False
False

CASO 2: 
Ingresa el número de conjuntos (n): 3

Ingresa, en cada línea, cuatro puntos (x1,y1 x2,y2 x3,y3 x4,y4): 
1,1 4,4 1,4 4,1
1,2 3,4 1,4 3,2
2,3 4,5 2,5 4,3

Resultado: 
True
True
True

CASO 3:
Ingresa el número de conjuntos (n): 3

Ingresa, en cada línea, cuatro puntos (x1,y1 x2,y2 x3,y3 x4,y4): 
1,5 7,1 1,4 10,9
10,2 1,12 3,3 0,15
-6,-6 3,4 2,21,1

Error
-6,-6 3,4 2,2 1,1

Resultado: 
True
False
False

CASO 4:
Ingresa el número de conjuntos (n): 2

Ingresa, en cada línea, cuatro puntos (x1,y1 x2,y2 x3,y3 x4,y4): 
1,1 2,2 3,3 4,4
1,1 2,2 3,3 4,4

Resultado: 
False
False*/