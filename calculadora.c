/*******************************************************
* Autor: [Ricardo Almeida de Oliveira]
* Email: [ricardo.almeidaoliveira@upe.br]
* Github: https://github.com/Ricardo191005/Calculadora.git

********************************************************

* Descrição: Calculadora Programadora Didática

********************************************************
* Atualizações:
* Versão Inicial - Data 20/09/2024 - 16h20
********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h> // Inclua a biblioteca para usar SetConsoleOutputCP

void decimalParaBinario(int n) {
    int binario[32], i = 0;
    printf("Convertendo %d para binário:\n", n);
    while (n > 0) {
        binario[i] = n % 2;
        printf("%d %% 2 = %d (resto)\n", n, binario[i]);
        n = n / 2;
        printf("%d / 2 = %d (próximo valor)\n", n * 2, n);
        i++;
    }
    printf("Resultado em binário: ");
    for (int j = i - 1; j >= 0; j--)
        printf("%d", binario[j]);
    printf("\n\n");
}

void decimalParaOctal(int n) {
    int octal[32], i = 0;
    printf("Convertendo %d para octal:\n", n);
    while (n > 0) {
        octal[i] = n % 8;
        printf("%d %% 8 = %d (resto)\n", n, octal[i]);
        n = n / 8;
        printf("%d / 8 = %d (próximo valor)\n", n * 8, n);
        i++;
    }
    printf("Resultado em octal: ");
    for (int j = i - 1; j >= 0; j--)
        printf("%d", octal[j]);
    printf("\n\n");
}

void decimalParaHexadecimal(int n) {
    char hexa[32];
    int i = 0;
    printf("Convertendo %d para hexadecimal:\n", n);
    while (n > 0) {
        int temp = n % 16;
        if (temp < 10)
            hexa[i] = temp + 48; // ASCII de 0 a 9
        else
            hexa[i] = temp + 55; // ASCII de A a F
        printf("%d %% 16 = %d (resto)\n", n, temp);
        n = n / 16;
        printf("%d / 16 = %d (próximo valor)\n", n * 16, n);
        i++;
    }
    printf("Resultado em hexadecimal: ");
    for (int j = i - 1; j >= 0; j--)
        printf("%c", hexa[j]);
    printf("\n\n");
}

void decimalParaBCD(int n) {
    int bcd[32], i = 0;
    printf("Convertendo %d para BCD (Binary Coded Decimal):\n", n);
    while (n > 0) {
        int digito = n % 10;
        printf("Dígito: %d\n", digito);
        for (int j = 3; j >= 0; j--) {
            bcd[i + j] = digito % 2;
            digito /= 2;
        }
        for (int j = 0; j < 4; j++)
            printf("%d", bcd[i + j]);
        printf(" (dígito em BCD)\n");
        n = n / 10;
        printf("%d / 10 = %d (próximo valor)\n", n * 10, n);
        i += 4;
    }
    printf("Resultado em BCD: ");
    for (int j = 0; j < i; j++)
        printf("%d", bcd[j]);
    printf("\n\n");
}

int main() {
    // Configurar o terminal para UTF-8
    SetConsoleOutputCP(CP_UTF8);

    int numero, escolha;

    printf("Calculadora de conversão de bases\n");
    printf("Digite um número na base 10: ");
    scanf("%d", &numero);

    printf("\nEscolha a conversão:\n");
    printf("1 - Converter para Binário\n");
    printf("2 - Converter para Octal\n");
    printf("3 - Converter para Hexadecimal\n");
    printf("4 - Converter para BCD\n");
    printf("Sua escolha: ");
    scanf("%d", &escolha);

    switch (escolha) {
        case 1:
            decimalParaBinario(numero);
            break;
        case 2:
            decimalParaOctal(numero);
            break;
        case 3:
            decimalParaHexadecimal(numero);
            break;
        case 4:
            decimalParaBCD(numero);
            break;
        default:
            printf("Escolha inválida.\n");
            break;
    }

    // Linha para evitar que o programa feche imediatamente
    printf("\nPressione Enter para sair...");
    getchar();  // Pega o '\n' deixado pelo último scanf
    getchar();  // Espera pelo próximo Enter

    return 0;
}


