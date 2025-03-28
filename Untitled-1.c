#include <stdio.h>
#include <math.h>

int main() {
    // Parte 1: Calcolo delle aree
    float D;
    printf("Inserisci un numero reale D: ");
    scanf("%f", &D);
    
    // Calcolo aree
    float area_quadrato = D * D;
    float area_cerchio = M_PI * (D/2) * (D/2); // raggio = D/2
    float area_triangolo = (sqrt(3)/4) * D * D;
    
    // Parte 2: Calcolo della media di 3 numeri
    float num1, num2, num3;
    printf("\nInserisci 3 numeri per calcolare la media:\n");
    printf("Numero 1: ");
    scanf("%f", &num1);
    printf("Numero 2: ");
    scanf("%f", &num2);
    printf("Numero 3: ");
    scanf("%f", &num3);
    
    float media = (num1 + num2 + num3) / 3;
    
    // Stampa risultati
    printf("\nRisultati:\n");
    printf("1. Area del quadrato di lato %.2f:\n", D);
    printf("   - Valore decimale: %.2f\n", area_quadrato);
    printf("   - Valore arrotondato: %d\n", (int)(area_quadrato + 0.5));
    
    printf("\n2. Area del cerchio di diametro %.2f:\n", D);
    printf("   - Valore decimale: %.2f\n", area_cerchio);
    printf("   - Valore arrotondato: %d\n", (int)(area_cerchio + 0.5));
    
    printf("\n3. Area del triangolo equilatero di lato %.2f:\n", D);
    printf("   - Valore decimale: %.2f\n", area_triangolo);
    printf("   - Valore arrotondato: %d\n", (int)(area_triangolo + 0.5));
    
    printf("\n4. Media dei 3 numeri inseriti:\n");
    printf("   - Valore decimale: %.2f\n", media);
    printf("   - Valore arrotondato: %d\n", (int)(media + 0.5));
    
    return 0;
}