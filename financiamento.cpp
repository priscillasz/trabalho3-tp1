#include <stdio.h>
#include <time.h>
#include <math.h>

// Funcoes que checam se a data e valida
bool eh_bissexto(int ano)
{
    return (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
}

int numero_dias_mes(int mes, int ano)
{
    if (mes < 1 || mes > 12 || ano <= 0)
        return -1;

    if (mes == 1 || mes == 3 || mes == 5 || mes == 7 ||
        mes == 8 || mes == 10 || mes == 12)
            return 31;
    else if (mes == 4 || mes == 6 || mes == 9 || mes == 11)
        return 30;
    else if (eh_bissexto(ano))
        return 29;
    else
        return 28;
}

bool eh_data_valida(int dia, int mes, int ano)
{
    int numero_dias = numero_dias_mes(mes, ano);

    return numero_dias != -1 && dia >= 1 && dia <= numero_dias;
}

// calcula a mensalidade e a taxa de juros mensais
void calcula_juros_mensalidade(float &emprestimo, float &parcelas, float &fator)
{
    float juros_mensais, juros, tempo, mensalidade, mensalidade_final;

    juros_mensais = 1.8 + (fator * 0.2);
    juros = juros_mensais / 100;
    printf("Juros mensais: %.2f%c\n", juros_mensais, '%');

    tempo = parcelas / 12;
    mensalidade = (emprestimo * pow(1 + juros, tempo)) / parcelas;
    mensalidade_final = mensalidade / 100;
    printf("Mensalidade: R$ %.2f\n", mensalidade);
}

// calcula fator de risco com base no patrimonio e na idade da pessoa
void fator_de_risco(float &patrimonio, int &idade, float &fator)
{
    int d, m, a;

    if (idade >= 18 && idade <= 30)
        fator = 3;
    else if (idade >= 31 && idade <= 50)
        fator = 6;
    else if (idade >= 51 && idade <= 60)
        fator = 9;
    else
        fator = 12;
    
    /*-------------------------*/

    if (patrimonio <= 50000)
        fator += 2;
    else if (patrimonio > 50000 && patrimonio <= 200000)
        fator += 1;
    else if (patrimonio > 200000 && patrimonio <= 1000000)
        fator -= 1;
    else
        fator -= 2;
    
    printf("Fator de risco: %.f\n", fator);
}

int calcula_idade(int &d, int &m, int &a, int &anos)
{
    int ano, mes, dia;

    time_t t = time(NULL);
    struct tm lt = *localtime(&t);
    ano = lt.tm_year + 1900;
    mes = lt.tm_mon + 1;
    dia = lt.tm_mday;

    if (m > mes)
    {
        ano = ano - 1;
        mes = mes + 12;
    }
    
    anos = ano - a;
    int meses = mes - m;
    int dias = dia - d;    

    return anos;
}

void le_dados(int &d, int &m, int &a, float &patrimonio, float &emprestimo, float &parcelas)
{
    // le a data de nascimento. se a data for invalida, pede novamente.
    puts("Informe a data de nascimento abaixo:");
    do
    {
        printf("Dia: ");
        scanf("%d", &d);

        printf("Mes: ");
        scanf("%d", &m);

        printf("Ano: ");
        scanf("%d", &a);

        if (eh_data_valida(d, m, a) == false)
        {
            puts("A data inserida e invalida");
        }

    } while (eh_data_valida(d, m, a) == false);
    
    // le o valor do patrimonio
    do
        {
            printf("Valor do patrimonio: ");
            scanf("%f", &patrimonio);

            if (patrimonio < 0)
                puts("Valor de patrimonio invalido.");
            
        } while (patrimonio < 0);

    // Le o valor do emprestimo
    do
    {
        printf("Valor do emprestimo: ");
        scanf("%f", &emprestimo);

        if (emprestimo < 1000)
            puts("Valor de emprestimo invalido");
    } while (emprestimo < 1000);

    // Le a quantidade de parcelas
    printf("Parcelas: ");
    scanf("%f", &parcelas);

    while (parcelas < 2)
    {
        puts("Valor de parcelas invalido.");
        printf("Parcelas: ");
        scanf("%f", &parcelas);
    }
}

int main()
{
    int d, m, a, anos;
    float patrimonio, emprestimo;
    float parcelas;
    float fator;

    le_dados(d, m, a, patrimonio, emprestimo, parcelas);

    if (calcula_idade(d, m, a, anos) < 18)
        puts("Menores de 18 anos nao podem pedir emprestimos.");

    else
    {
        putchar('\n');
        puts("DADOS DO EMPRESTIMO:");   
        fator_de_risco(patrimonio, anos, fator);
        calcula_juros_mensalidade(emprestimo, parcelas, fator);
    }
}