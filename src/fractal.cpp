#include <iostream>
#include <complex.h>
#include <math.h>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char** argv) {
    
    // Variáveis para cálculo do fractal
    int max_iter;     // Número máximo de iterações
    int width, height;// Dimensões da imagem
    int i, j, k;      // Contadores de loops
    complex<double> center; // Centro do fractal no plano complexo
    complex<double> extent; // Tamanho da área visualizada
    complex<double> c, z;   // Números complexos para os cálculos
    double scale;     // Fator de escala
    
    // Configura parâmetros via argumentos de linha de comando
    if (argc == 8) {
        max_iter = atoi(argv[1]);
        width = atoi(argv[2]);
        height = atoi(argv[3]);
        center = complex<double>(atof(argv[4]), atof(argv[5]));
        extent = complex<double>(atof(argv[6]), atof(argv[7]));
    }
    // Valores padrão caso não haja argumentos suficientes
    else {
        max_iter = 256;
        width = 256;
        height = 256;
        center = complex<double>(-0.8, 0.0);
        extent = complex<double>(3.0, 3.0);
    }
    scale = max((extent / static_cast<double>(width)).real(), 
               (extent / static_cast<double>(height)).imag());

    // Salva parâmetros para comunicação com Python
    ofstream parameters("Parameter.txt");
    if (!parameters) {
        cerr << "Error Opening File";
        return 2;
    }
    parameters << max_iter << ";" << width << ";" << height << ";" 
              << center.real() << "+" << center.imag() << ";" 
              << extent.real() << '+' << extent.imag() << ";"
              << scale;
    parameters.close();

    // Arquivo de saída para os dados do fractal
    ofstream outfile("MandelMatrix.txt");
    if (!outfile) {
        cerr << "Error Opening File";
        return 1;
    }

    // Gera o conjunto de Mandelbrot
    for (j = 0; j < height; j++) {
        for (i = 0; i < width; i++) {
            // Mapeia pixel para ponto no plano complexo
            c = center + complex<double>(i - width/2, j - height/2) * scale;
            z = 0;
            
            // Verifica se o ponto pertence ao conjunto
            for (k = 0; k < max_iter; k++) {
                z = pow(z, 2) + c;
                if (norm(z) > 4.0) break; // norm(z) = z * conj(z)
            }
            
            outfile << k;
            if (i < width - 1) outfile << " ";
        }
        outfile << endl;
    }
    
    outfile.close();
    return 0;
}
