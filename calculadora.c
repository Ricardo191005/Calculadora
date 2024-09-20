/*******************************************************
* Autor: [Ricardo Almeida de Oliveira]
* Email: [ricardo.almeidaoliveira@upe.br]
* Github: https://github.com/Ricardo191005/Calculadora.git

********************************************************

* Descrição: Calculadora Programadora Didática

********************************************************
* Atualizações:
* Versão Inicial - calculadora de conversão (binário, octal, hexadecimal e BCD) - Data 20/09/2024 - 16h20
* Adição da conversão de real em decimal para float e double                    - Data 20/09/2024 - 17h10
********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <windows.h> // Inclua a biblioteca para usar SetConsoleOutputCP

// Estruturas de união para facilitar a manipulação de bits
union FloatUnion {
    float f;
    uint32_t bits;
};

union DoubleUnion {
    double d;
    uint64_t bits;
};

// Função para converter um inteiro para binário e imprimir com 32 bits
void imprimirBits32(uint32_t n) {
    for (int i = 31; i >= 0; i--) {
        printf("%d", (n >> i) & 1);
    }
    printf("\n");
}

// Função para converter um inteiro para binário e imprimir com 64 bits
void imprimirBits64(uint64_t n) {
    for (int i = 63; i >= 0; i--) {
        printf("%d", (n >> i) & 1);
    }
    printf("\n");
}

// Função para exibir os componentes de um número float em ponto flutuante (32 bits)
void decomporFloat(float num) {
    union FloatUnion u;
    u.f = num;

    uint32_t sinal = (u.bits >> 31) & 1;
    uint32_t expoente = (u.bits >> 23) & 0xFF;
    uint32_t fracao = u.bits & 0x7FFFFF;  // 23 bits de fração

    printf("Número (float): %f\n", num);
    printf("Bits: ");
    imprimirBits32(u.bits);

    printf("Sinal: %u\n", sinal);
    printf("Expoente: %u (sem viés)\n", expoente);
    printf("Expoente com viés: %d\n", expoente - 127);  // O viés do expoente em float é 127
    printf("Fracao: %u\n\n", fracao);
}

// Função para exibir os componentes de um número double em ponto flutuante (64 bits)
void decomporDouble(double num) {
    union DoubleUnion u;
    u.d = num;

    uint64_t sinal = (u.bits >> 63) & 1;
    uint64_t expoente = (u.bits >> 52) & 0x7FF;
    uint64_t fracao = u.bits & 0xFFFFFFFFFFFFF;  // 52 bits de fração

    printf("Número (double): %lf\n", num);
    printf("Bits: ");
    imprimirBits64(u.bits);

    printf("Sinal: %llu\n", sinal);
    printf("Expoente: %llu (sem viés)\n", expoente);
    printf("Expoente com viés: %lld\n", expoente - 1023);  // O viés do expoente em double é 1023
    printf("Fracao: %llu\n\n", fracao);
}

// Função para converter decimal para binário
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

// Função para converter decimal para octal
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

// Função para converter decimal para hexadecimal
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

// Função para converter decimal para BCD (Binary Coded Decimal)
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
    float numeroFloat;
    double numeroDouble;

    printf("Calculadora de conversão de bases e decomposição de ponto flutuante\n");
    printf("Escolha uma opção:\n");
    printf("1 - Converter número decimal para outras bases\n");
    printf("2 - Decompor número real (float e double)\n");
    printf("Sua escolha: ");
    scanf("%d", &escolha);

    if (escolha == 1) {
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
    } else if (escolha == 2) {
        printf("Digite um número real (float): ");
        scanf("%f", &numeroFloat);
        printf("Digite um número real (double): ");
        scanf("%lf", &numeroDouble);

        printf("\nEscolha a decomposição:\n");
        printf("1 - Decompor float\n");
        printf("2 - Decompor double\n");
        printf("Sua escolha: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                decomporFloat(numeroFloat);
                break;
            case 2:
                decomporDouble(numeroDouble);
                break;
            default:
                printf("Escolha inválida.\n");
                break;
        }
    } else {
        printf("Escolha inválida.\n");
    }

    // Linha para evitar que o programa feche imediatamente
    printf("\nPressione Enter para sair...");
    getchar();  // Pega o '\n' deixado pelo último scanf
    getchar();  // Espera pelo próximo Enter

    return 0;
}


