#include <stdio.h>
#include <ctype.h>

// le o vetor de caracteres e retorna o vetor preenchido
void le_caracteres(char vet[], int n)
{
    int i;
    // Le cada caractere do vetor
    for (i = 0; i < n; i++)
    {
        getchar();
        printf("Caractere %d: ", i+1);
        vet[i] = getchar();
    }   
    vet[i] = 0;
    putchar('\n');
}

// imprime o vetor lido
void imprime_vet_original(char vet[], int n)
{
    puts("Vetor original:");
    puts(vet); 

    putchar('\n');
}

// recebe o vetor lido na função anterior e retorna o vetor convertido e a quantidade de conversões
char converte_caracteres(char vet[], int n)
{
    char letra;
    int conv_1 = 0;
    int conv_2 = 0; // conta as conversoes

    for (int i = 0; i < n; i++)
    {
        letra = vet[i];
        if ((letra >= 97) && (letra <= 122))
        {
            vet[i] = toupper(vet[i]);       // converte minusculas para maiusculas
            conv_1++;
        }
        else if ((letra >= 65) && (letra <= 90))
        {
            vet[i] = tolower(vet[i]);       // converte maiusculas para minusculas
            conv_2++;
        }
    }
    
    // soma as conversoes e retorna
    int conv = conv_1 + conv_2;
    return conv;
}

//recebe o vetor de caracteres e imprime seu conteúdo em uma única linha.
void imprime_caracteres(char vet[], int n)
{
    putchar('\n');
    puts("Vetor convertido:");
    puts(vet);
}

//  ler o valor n, chamar as funções definidas acima e imprimir a quantidade de conversões
int main()
{
    int n; 
    // le o valor de N -> Se n < 3, o valor e pedido novamente  
    do
    {
        printf("N: ");
        scanf("%d", &n);

        if (n < 3)
            puts("Valor de N invalido");
    } while (n < 3);

    // cria o vetor
    char vet[n];

    // chama cada uma das funcoes criadas acima
    le_caracteres(vet, n);

    imprime_vet_original(vet, n);

    char c = converte_caracteres(vet, n);
    printf("Conversoes: %d\n", c);

    imprime_caracteres(vet, n);
}