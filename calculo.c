#include <stdio.h>
#include <stdlib.h>
#include <math.h> 

typedef struct {
    double x;
    double y;
} Ponto;

double areaTriangulo(Ponto a, Ponto b, Ponto c) {
    double det = a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y);
    return fabs(det / 2.0);
}

double areaPoligono(Ponto pontos[], int n) {
    double areaTotal = 0.0;
    for (int i = 1; i < n - 1; i++) {
        areaTotal += areaTriangulo(pontos[0], pontos[i], pontos[i + 1]);
    }
    return areaTotal;
}


int main() {

    FILE *file = fopen("areaPoligono.txt", "r");
    if (file == NULL) {
        return 1;
    }

    int n;
    if (fscanf(file, "%d", &n) != 1) {
        fclose(file);
        return 1;
    }

    Ponto *pontos = malloc(n * sizeof(Ponto));
    if (pontos == NULL) {
        fclose(file);
        return 1;
    }

    for (int i = 0; i < n; i++) {
        if (fscanf(file, "%lf %lf", &pontos[i].x, &pontos[i].y) != 2) {
            free(pontos);
            fclose(file);
            return 1;
        }
    }

    double area = areaPoligono(pontos, n);
    printf("Area do poligono: %.2lf\n", area);

    free(pontos);
    fclose(file);

    return  0;
}