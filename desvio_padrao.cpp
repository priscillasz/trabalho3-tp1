#include <stdio.h>
#include <math.h>

// le o vetor de inteiros
void le_vetor(int v[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("v[%d]: ", i);
        scanf("%d", &v[i]);
    }
}

// imprime o vetor de inteiros
void imprime_vetor(int v[], int n)
{
    putchar('\n');
    printf("v1 = [ ");
    for (int i = 0; i < n; i++)
        printf("%d ", v[i]);
    printf("]");
}

// calcula o desvio padrao de um grupo k de elementos
float desvio_padrao(int v1[], int k, float soma, int inicio, int fim)
{
    // obtem a media do bloco
    float media = soma / k;

    // soma de cada elemento - media elevada a 2
    float soma2 = 0;
    for (inicio; inicio < fim; inicio++)
        soma2 += pow(v1[inicio] - media, 2);
    
    // divide a soma por k - 1
    float divsoma = soma2 / (k-1);

    // tira a raiz quadrada de divsoma
    float desvio_pad = sqrt(divsoma);

    return desvio_pad;
}

// percorre o vetor v1 de k em k elementos e preenche o vetor v2 com os desvios-padrão
void calcula_dp(int v1[], int n, int k)
{
    int j = 0;
    float v2[n/k];
    float soma = 0;
    int inicio = 0;
    int fim = k;

    for (int i = 0; i < n; i++)
    {
        soma = soma + v1[i];
        if(i > 0 && ((i+1) % k == 0))
        {
            v2[j] = desvio_padrao(v1, k, soma, inicio, fim);
            soma = 0;
            inicio += k;
            fim += k;
            j++;
        }
    }
    putchar('\n');

    // imprime o vetor v2 com os desvios-padrao
    printf("v2 = [ ");
    for (int i = 0; i < n/k; i++)
    {
        printf("%.2f ", v2[i]);
    }
    printf("]");
}

// le n, k e chama as funcoes acima
int main()
{
    int n, k;

    // Le N
    do
    {
        printf("N: ");
        scanf("%d", &n);

        if (n <= 2)
            puts("Valor de N invalido");
    } while (n <= 2);
    
    // Cria o vetor v1
    int v1[n];

    // Le K
    do
    {
        printf("K: ");
        scanf("%d", &k);
        if (k < 2 || k > n || n % k != 0)
            puts("Valor de K invalido");
    } while (k < 2 || k > n || n % k != 0);
    
    // chama as funcoes criadas
    le_vetor(v1, n);        // Le o vetor

    imprime_vetor(v1, n);   // Imprime v1

    calcula_dp(v1, n, k);   
}