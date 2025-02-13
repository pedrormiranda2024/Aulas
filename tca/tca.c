#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>        
#include <windows.h>
#define VERMELHO 	printf("\33[31m");
#define BRANCO 		printf("\33[37m");

typedef struct
{
    int dia;
    int mes;
    int ano;
} TData;

typedef struct
{
    int hora;
    int minuto;
} THora;

typedef struct
{
    char *nome;
    char *apelido;
    char *email;
    TData data_nas;
    char *telefone;
} TAmigo;

typedef struct
{
    char *logradouro;
    int numero;
    char *bairro;
    char *cidade;
    char *estado;
} TEndereco;

typedef struct
{
    char *nome_encontro;
    TEndereco endereco;
} TLocal;


typedef struct
{
    char *nome;
} TCategoria;

typedef struct
{
    TAmigo *amigos;
    int numAmigoEnc;
    TCategoria *categoria;
    int numCategoriaEnc;
    TData data;
    THora horario;
    TLocal local;
    int indLoc;
    char *desc;
    int *indiceAmigo;
} TEncontro;

void lerMenu();
void manterAmigo();
void manterLocal();
void manterCategoria();
void manterEncontro();
void Relatorios();
void listarAmigos();
void PrintaTodosAmigos();
void PrintaUmAmigo(int amg);
void listarLocais();
void PrintaTodosLocais();
void PrintaUmLocal(int loc);
void listarCategorias();
void listarEncontros();
void PrintaTodosEncontros();
void PrintaUmEncontro(int enc);
void RelatorioPorCategoria();
void PrintaEncontrosDaCategoria(int cat);
void adicionarAmigo();
void adicionarLocal();
void adicionarCategoria();
void adicionarEncontro();
int ValidarAmigoEnc(int amg, int ind);
int ValidarCategoriaEnc(int cat, int ind);
int selecionarAmigo(int ind);
int selecionarLocal();
int selecionarCategoria(int ind);
int selecionarEncontro();
void alterarAmigo(int amg);
void alterarLocal(int loc);
void alterarCategoria(int cat);
void alterarEncontro(int enc);
void alterarAmigoEnc(int enc);
void alterarCategoriaEnc(int enc);
int selecionarAmigoEnc(int enc);
int selecionarCategoriaEnc(int enc);
void excluirAmigo(int amg);
int ValidarExcluirAmigo(int amg);
void excluirLocal(int loc);
int ValidarExcluirLocal(int loc);
void excluirCategoria(int cat);
int ValidarExcluirCategoria(int cat);
void excluirEncontro(int enc);
void salvarAmigo();
void salvarLocal();
void salvarCategoria();
void salvarEncontro();
void recuperarAmigo();
void recuperarLocal();
void recuperarCategoria();
void recuperarEncontro();
void salvarDados();
void recuperarDados();
int valide_data(int dias, int mes, int ano);
int validarValor(int num, int param1, int param2);
int validarHora(int hora, int minuto);
int validarAmigo(char amg[100]);
int validarCategoria(char cat[100]); 
void ERRO(int id);
void liberarPonteiros();

TAmigo *amigos;
TLocal *locais;
TCategoria *categorias;
TEncontro *encontros;

int numAmigo = 0;
int numLocal = 0;
int numCategoria = 0;
int numEncontro = 0;

int main()
{
    SetConsoleOutputCP(65001);
    recuperarDados();
    lerMenu();
    salvarDados();
    liberarPonteiros();
}

void lerMenu()
{
    int op1 = 1;
    while (op1 != 0)
    {
        printf("Bem vindo!!\n");
        printf("Selecione a opção desejada: \n");
        printf("1) Manter amigo\n");
        printf("2) Manter local\n");
        printf("3) Manter categoria\n");
        printf("4) Manter encontro\n");
        printf("5) Relatorios\n");
        printf("0) Sair\n");
        scanf("%d", &op1);

        switch (op1)
        {
        case 1:
            system("cls");
            manterAmigo();
            break;
        case 2:
            system("cls");
            manterLocal();
            break;
        case 3:
            system("cls");
            manterCategoria();
            break;
        case 4:
            system("cls");
            manterEncontro();
            break;
        case 5:
            system("cls");
            Relatorios();
            break;
        case 0:
            system("cls");
            break;
        default:
            system("cls");
            ERRO(1);
            lerMenu();
            return;
        }
    }
    system("cls");
}

void manterAmigo()
{
    int opAmigo = 1, amg;
    while(opAmigo != 0)
    {
        printf("1) Adicionar amigo\n");
        printf("2) Alterar amigo\n");
        printf("3) Excluir amigo\n");
        printf("0) Voltar\n");
        scanf("%d", &opAmigo);

        switch(opAmigo)
        {
            case 1:
                adicionarAmigo();
                break;
            case 2:
                amg = selecionarAmigo(-1);
                alterarAmigo(amg);
                break;
            case 3:
                amg = selecionarAmigo(-1);
                excluirAmigo(amg);
                break;
            case 0:
                system("cls");
                return;
            default:
                system("cls");
                ERRO(1);
                manterAmigo();
                return;
        }
    }
}

void adicionarAmigo()
{
    char strAux[100];
    int auxDat = 0;
    if(numAmigo == 0)
    {
        amigos = (TAmigo *)malloc(1 * sizeof(TAmigo));
    }
    else
    {
        amigos = (TAmigo *)realloc(amigos, (numAmigo + 1) * sizeof(TAmigo));
    }

    while (1)
    {
        printf("Qual o nome do amigo?\n");
        fflush(stdin);
        gets(strAux);
        fflush(stdin);
        if (validarAmigo(strAux) == 1)
        {
            amigos[numAmigo].nome = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
            strcpy(amigos[numAmigo].nome, strAux);
            break;
        }
        else
        {
            ERRO(11);
        }
    }

    printf("Qual o apelido do amigo?\n");
    fflush(stdin);
    gets(strAux);
    fflush(stdin);
    amigos[numAmigo].apelido = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
    strcpy(amigos[numAmigo].apelido, strAux);

    printf("Qual o email do amigo?\n");
    fflush(stdin);
    gets(strAux);
    fflush(stdin);
    amigos[numAmigo].email = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
    strcpy(amigos[numAmigo].email, strAux);

    while(auxDat == 0)
    {
        printf("Digite sua data de nascimento: (DD MM AAAA, sem barras)\n");
        scanf("%d%d%d", &amigos[numAmigo].data_nas.dia, &amigos[numAmigo].data_nas.mes, &amigos[numAmigo].data_nas.ano);
        auxDat = valide_data(amigos[numAmigo].data_nas.dia, amigos[numAmigo].data_nas.mes, amigos[numAmigo].data_nas.ano);
        if (auxDat == 0)
        {
            ERRO(2);
        }
    }

    printf("Qual o seu telefone?\n");
    fflush(stdin);
    gets(strAux);
    fflush(stdin);
    amigos[numAmigo].telefone = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
    strcpy(amigos[numAmigo].telefone, strAux);
    
    numAmigo++;
    system("cls");
}

int selecionarAmigo(int ind)
{
    int i, j, aux = 0, opAmigo;
    printf("Você deseja selecionar qual amigo?\n");
    if (ind == -1)
    {
        for (i = 0; i < numAmigo; i++)
        {
            printf("%d) ", i + 1);
            puts(amigos[i].nome);
        }
    }
    else
    {
        for (i = 0; i < numAmigo && encontros[ind].numAmigoEnc < numAmigo; i++)
        {
            for (j = 0; j < encontros[ind].numAmigoEnc; j++)
            {
                if (strcmp(amigos[i].nome, encontros[ind].amigos[j].nome) == 0)
                {
                    aux++;
                }
            }
            if (aux == 0)
            {
                printf("%d) ", i + 1);
                puts(amigos[i].nome);
            }
            else
            {
                VERMELHO;
                printf("%d) ", i + 1);
                puts(amigos[i].nome);
                BRANCO;
                aux = 0;
            }
        }   
        if (encontros[ind].numAmigoEnc == numAmigo)
        {
            printf("Não há mais amigos disponíveis\n");
            return -10;
        }
    }
    scanf("%d", &opAmigo);

    while(validarValor(opAmigo, 1, numAmigo) == 0)
    {
        printf("Você deseja selecionar qual amigo?\n");
        for (i = 0; i < numAmigo; i++)
        {
            printf("%d) ", i + 1);
            puts(amigos[i].nome);
        }
        scanf("%d", &opAmigo);
    }

    return opAmigo - 1;
}

void alterarAmigo(int amg)
{
    int opAlt, auxDat = 0;
    char strAux[100];
    if (ValidarExcluirAmigo(amg) == 0)
    {
        ERRO(4);
        system("pause");
        system("cls");
        return;
    }
    printf("Você deseja alterar:\n");
    printf("1) Nome (%s)\n", amigos[amg].nome);
    printf("2) Apelido (%s)\n", amigos[amg].apelido);
    printf("3) Email (%s)\n", amigos[amg].email); 
    printf("4) Alterar data (%d/%d/%d)\n", amigos[amg].data_nas.dia, amigos[amg].data_nas.mes, amigos[amg].data_nas.ano);
    printf("5) Telefone (%s)\n", amigos[amg].telefone); 
    printf("0) Voltar\n");
    scanf("%d", &opAlt);
    switch(opAlt)
    {
        case 1:
            printf("Digite o novo nome:\n");
            fflush(stdin);
            gets(strAux);
            fflush(stdin);
            amigos[amg].nome = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
            strcpy(amigos[amg].nome, strAux);
            break;
        case 2:
            printf("Digite o novo apelido:\n");
            fflush(stdin);
            gets(strAux);
            fflush(stdin);
            amigos[amg].apelido = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
            strcpy(amigos[amg].apelido, strAux);
            break;
        case 3:
            printf("Digite o novo email:\n");
            fflush(stdin);
            gets(strAux);
            fflush(stdin);
            amigos[amg].email= (char *)malloc((strlen(strAux) + 1) * sizeof(char));
            strcpy(amigos[amg].email, strAux);
            break;
        case 4:
            while(auxDat == 0)
            {
                printf("Digite sua data de nascimento: (DD MM AAAA, sem barras)\n");
                scanf("%d%d%d", &amigos[amg].data_nas.dia, &amigos[amg].data_nas.mes, &amigos[amg].data_nas.ano);
                auxDat = valide_data(amigos[amg].data_nas.dia, amigos[amg].data_nas.mes, amigos[amg].data_nas.ano);
                if (auxDat == 0)
                {
                    ERRO(2);
                }
            }
        case 5:
            printf("Digite o novo telefone:\n");
            fflush(stdin);
            gets(strAux);
            fflush(stdin);
            amigos[amg].telefone = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
            strcpy(amigos[amg].telefone, strAux);
            break;
        case 0:
            system("cls");
            manterAmigo();
            return;
        default:
            ERRO(1);
            alterarAmigo(amg);
            return;
        
    }
    system("cls");
}

void excluirAmigo(int amg)
{
    int i, aux, conf;
    if (ValidarExcluirAmigo(amg) == 0)
    {
        ERRO(4);
        system("pause");
        system("cls");
        return;
    }
    printf("Tem certeza que quer excluir o amigo?\n");
    printf("1) Sim\n2) Não\n");
    
    scanf("%d", &conf);
    if (conf == 1)
    {
        for(i = amg; i < numAmigo - 1; i++)
        {
            amigos[i] = amigos[i + 1];
        }
        numAmigo--;
        amigos = (TAmigo *)realloc(amigos, numAmigo * sizeof(TAmigo));
        system("cls");
    }
    else if (conf == 2)
    {
        system("cls");
        manterAmigo();
        return;
    }
    else
    {
        ERRO(1);
        excluirAmigo(amg);
        return;
    }
}

int ValidarExcluirAmigo(int amg)
{
    int i, j;
    for (i = 0; i < numEncontro; i++)
    {
        for (j = 0; j < encontros[i].numAmigoEnc; j++)
        {
            if (amg == encontros[i].indiceAmigo[j])
            {
                return 0;
            }
        }
    }
    return 1;
}

void salvarAmigo()
{
    int i;
    FILE *pArq;

    pArq = fopen("amigosBD.txt", "w");
    for (i = 0; i < numAmigo; i++)
    {
        fprintf(pArq, "%s;", amigos[i].nome);
        fprintf(pArq, "%s;", amigos[i].apelido);
        fprintf(pArq, "%s;", amigos[i].email);
        fprintf(pArq, "%d;", amigos[i].data_nas.dia);
        fprintf(pArq, "%d;", amigos[i].data_nas.mes);
        fprintf(pArq, "%d;", amigos[i].data_nas.ano);
        fprintf(pArq, "%s;", amigos[i].telefone);
        fprintf(pArq, "%c", '\n');
    }
    fclose(pArq);
}

void recuperarAmigo()
{
    int i = 0, sep = 0;
    char c, str[100];
    FILE *pArq;

    pArq = fopen("amigosBD.txt", "r");
    if (pArq)
    {
        while (!feof(pArq))
        {
            c = fgetc(pArq);

            if (c != ';' && c != '\n' && c != EOF)
            {
                str[i++] = c;
            }
            else if (c == ';' || c == '\n')
            {
                str[i] = '\0';
                i = 0;
                if (c == ';')
                {
                    if (sep == 0)
                    {
                        if (numAmigo == 0)
                        {
                            amigos = (TAmigo *)malloc(1 * sizeof(TAmigo));
                        }
                        else
                        {
                            amigos = (TAmigo *)realloc(amigos, (numAmigo + 1) * sizeof(TAmigo));
                        }
                        amigos[numAmigo].nome = (char *)malloc((strlen(str) + 1) * sizeof(char));
                        strcpy(amigos[numAmigo].nome, str);
                        sep++;
                    }
                    else if (sep == 1)
                    {
                        amigos[numAmigo].apelido = (char *)malloc((strlen(str) + 1) * sizeof(char));
                        strcpy(amigos[numAmigo].apelido, str);
                        sep++;
                    }
                    else if (sep == 2)
                    {
                        amigos[numAmigo].email = (char *)malloc((strlen(str) + 1) * sizeof(char));
                        strcpy(amigos[numAmigo].email, str);
                        sep++;
                    }
                    else if (sep == 3)
                    {
                        amigos[numAmigo].data_nas.dia = atoi(str);
                        sep++;
                    }
                    else if (sep == 4)
                    {
                        amigos[numAmigo].data_nas.mes = atoi(str);
                        sep++;
                    }
                    else if (sep == 5)
                    {
                        amigos[numAmigo].data_nas.ano = atoi(str);
                        sep++;
                    }
                    else if (sep == 6)
                    {
                        amigos[numAmigo].telefone = (char *)malloc((strlen(str) + 1) * sizeof(char));
                        strcpy(amigos[numAmigo].telefone, str);
                        sep++;
                    }
                }
                else
                {
                    numAmigo++;
                    sep = 0;
                }
            }
        }
    }
    fclose(pArq);
}


void manterLocal()
{
    int opLocal = 1, loc;
    while(opLocal != 0)
    {
        printf("1) Adicionar local\n");
        printf("2) Alterar local\n");
        printf("3) Excluir local\n");
        printf("0) Voltar\n");
        scanf("%d", &opLocal);

        switch(opLocal)
        {
            case 1:
                adicionarLocal();
                break;
            case 2:
                loc = selecionarLocal();
                alterarLocal(loc);
                break;
            case 3:
                loc = selecionarLocal();
                excluirLocal(loc);
                break;
            case 0:
                system("cls");
                return;
            default:
                ERRO(1);
                manterLocal();
                return;
        }
    }
}

void adicionarLocal()
{
    char strAux[100];
    if(numLocal == 0)
    {
        locais = (TLocal *)malloc(1 * sizeof(TLocal));
    }
    else
    {
        locais = (TLocal *)realloc(locais, (numLocal + 1) * sizeof(TLocal));
    }

    printf("Onde será o encontro?\n");
    fflush(stdin);
    gets(strAux);
    fflush(stdin);
    locais[numLocal].nome_encontro = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
    strcpy(locais[numLocal].nome_encontro, strAux);

    printf("Qual o logradouro?\n");
    fflush(stdin);
    gets(strAux);
    fflush(stdin);
    locais[numLocal].endereco.logradouro = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
    strcpy(locais[numLocal].endereco.logradouro, strAux);

    printf("Qual o numero do endereço?\n");
    scanf("%d", &locais[numLocal].endereco.numero);

    printf("Qual o bairro?\n");
    fflush(stdin);
    gets(strAux);
    fflush(stdin);
    locais[numLocal].endereco.bairro = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
    strcpy(locais[numLocal].endereco.bairro, strAux);

    printf("Qual a cidade?\n");
    fflush(stdin);
    gets(strAux);
    fflush(stdin);
    locais[numLocal].endereco.cidade = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
    strcpy(locais[numLocal].endereco.cidade, strAux);

    printf("Qual o estado?\n");
    fflush(stdin);
    gets(strAux);
    fflush(stdin);
    locais[numLocal].endereco.estado = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
    strcpy(locais[numLocal].endereco.estado, strAux);
    
    numLocal++;
    system("cls");
}

int selecionarLocal()
{
    int i, opLocal;
    printf("Você deseja selecionar qual local?\n");
    for (i = 0; i < numLocal; i++)
    {
        printf("%d) ", i + 1);
        puts(locais[i].nome_encontro);
    }
    scanf("%d", &opLocal);

    while(validarValor(opLocal, 1, numLocal) == 0)
    {
        printf("Você deseja selecionar qual local?\n");
        for (i = 0; i < numLocal; i++)
        {
            printf("%d) ", i + 1);
            puts(locais[i].nome_encontro);
        }
        scanf("%d", &opLocal);
    }

    return opLocal - 1;
}

void alterarLocal(int loc)
{
    int opAlt, auxDat = 0;
    char strAux[100];

    if (ValidarExcluirLocal(loc) == 0)
    {
        ERRO(5);
        system("pause");
        system("cls");
        return;
    }

    printf("Você deseja alterar:\n");
    printf("1) Local do encontro (%s)\n", locais[loc].nome_encontro);
    printf("2) Logradouro (%s)\n", locais[loc].endereco.logradouro);
    printf("3) Numero (%d)\n", locais[loc].endereco.numero); 
    printf("4) Bairro (%s)\n", locais[loc].endereco.bairro);
    printf("5) Cidade (%s)\n", locais[loc].endereco.cidade); 
    printf("6) Estado (%s)\n", locais[loc].endereco.estado); 
    printf("0) Voltar\n");
    scanf("%d", &opAlt);


    switch(opAlt)
    {
        case 1:
            printf("Digite o novo local:\n");
            fflush(stdin);
            gets(strAux);
            fflush(stdin);
            locais[loc].nome_encontro = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
            strcpy(locais[loc].nome_encontro, strAux);
            break;
        case 2:
            printf("Digite o novo logradouro:\n");
            fflush(stdin);
            gets(strAux);
            fflush(stdin);
            locais[loc].endereco.logradouro = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
            strcpy(locais[loc].endereco.logradouro, strAux);
            break;
        case 3:
            printf("Digite o novo numero:\n");
            scanf("%d", &locais[loc].endereco.numero);
            break;
        case 4:
            printf("Digite o novo bairro:\n");
            fflush(stdin);
            gets(strAux);
            fflush(stdin);
            locais[loc].endereco.bairro = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
            strcpy(locais[loc].endereco.bairro, strAux);
            break;
        case 5:
            printf("Digite a nova cidade:\n");
            fflush(stdin);
            gets(strAux);
            fflush(stdin);
            locais[loc].endereco.cidade = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
            strcpy(locais[loc].endereco.cidade, strAux);
            break;
        case 6:
            printf("Digite o novo estado:\n");
            fflush(stdin);
            gets(strAux);
            fflush(stdin);
            locais[loc].endereco.estado = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
            strcpy(locais[loc].endereco.estado, strAux);
            break;
        case 0:
            system("cls");
            manterLocal();
            return;
        default:
            ERRO(1);
            alterarLocal(loc);
            return;
    }
    system("cls");
}

void excluirLocal(int loc)
{
    int i, conf;
    if (ValidarExcluirLocal(loc) == 0)
    {
        ERRO(5);
        system("pause");
        system("cls");
        return;
    }

    printf("Tem certeza que quer excluir o local?\n");
    printf("1) Sim\n2) Não\n");
    
    scanf("%d", &conf);
    if (conf == 1)
    {
        for(i = loc; i < numLocal - 1; i++)
        {
            locais[i] = locais[i + 1];
        }
        numLocal--;
        locais = (TLocal *)realloc(locais, numLocal * sizeof(TLocal));
        system("cls");
    }
    else if (conf == 2)
    {
        system("cls");
        manterLocal();
        return;
    }
    else
    {
        ERRO(1);
        excluirLocal(loc);
        return;
    }
}

int ValidarExcluirLocal(int loc)
{
    int i, j;
    for (i = 0; i < numEncontro; i++)
    {
        if (loc == encontros[i].indLoc)
        {
            return 0;
        }
    }
    return 1;
}

void salvarLocal()
{
    int i;
    FILE *pArq;

    pArq = fopen("locaisBD.txt", "w");
    for (i = 0; i < numLocal; i++)
    {
        fprintf(pArq, "%s;", locais[i].nome_encontro);
        fprintf(pArq, "%s;", locais[i].endereco.logradouro);
        fprintf(pArq, "%i;", locais[i].endereco.numero);
        fprintf(pArq, "%s;", locais[i].endereco.bairro);
        fprintf(pArq, "%s;", locais[i].endereco.cidade);
        fprintf(pArq, "%s;", locais[i].endereco.estado);
        fprintf(pArq, "%c", '\n');
    }
    fclose(pArq);
}

void recuperarLocal()
{
    int i = 0, sep = 0;
    char c, str[100];
    FILE *pArq;

    pArq = fopen("locaisBD.txt", "r");
    if (pArq)
    {
        while (!feof(pArq))
        {
            c = fgetc(pArq);

            if (c != ';' && c != '\n' && c != EOF)
            {
                str[i++] = c;
            }
            else if (c == ';' || c == '\n')
            {
                str[i] = '\0';
                i = 0;
                if (c == ';')
                {
                    if (sep == 0)
                    {
                        if (numLocal == 0)
                        {
                            locais = (TLocal *)malloc(1 * sizeof(TLocal));
                        }
                        else
                        {
                            locais = (TLocal *)realloc(locais, (numLocal + 1) * sizeof(TLocal));
                        }
                        locais[numLocal].nome_encontro = (char *)malloc((strlen(str) + 1) * sizeof(char));
                        strcpy(locais[numLocal].nome_encontro, str);
                        sep++;
                    }
                    else if (sep == 1)
                    {
                        locais[numLocal].endereco.logradouro = (char *)malloc((strlen(str) + 1) * sizeof(char));
                        strcpy(locais[numLocal].endereco.logradouro, str);
                        sep++;
                    }
                    else if (sep == 2)
                    {
                        locais[numLocal].endereco.numero = atoi(str);
                        sep++;
                    }
                    else if (sep == 3)
                    {
                        locais[numLocal].endereco.bairro = (char *)malloc((strlen(str) + 1) * sizeof(char));
                        strcpy(locais[numLocal].endereco.bairro, str);
                        sep++;
                    }
                    else if (sep == 4)
                    {
                        locais[numLocal].endereco.cidade = (char *)malloc((strlen(str) + 1) * sizeof(char));
                        strcpy(locais[numLocal].endereco.cidade, str);
                        sep++;
                    }
                    else if (sep == 5)
                    {
                        locais[numLocal].endereco.estado = (char *)malloc((strlen(str) + 1) * sizeof(char));
                        strcpy(locais[numLocal].endereco.estado, str);
                        sep++;
                    }
                }
                else
                {
                    numLocal++;
                    sep = 0;
                }
            }
        }
    }
    fclose(pArq);
}

void manterCategoria()
{
    int opCategoria = 1, cat;
    while(opCategoria != 0)
    {
        printf("1) Adicionar categoria\n");
        printf("2) Alterar categoria\n");
        printf("3) Excluir categoria\n");
        printf("0) Voltar\n");
        scanf("%d", &opCategoria);

        switch(opCategoria)
        {
            case 1:
                adicionarCategoria();
                break;
            case 2:
                cat = selecionarCategoria(-1);
                alterarCategoria(cat);
                break;
            case 3:
                cat = selecionarCategoria(-1);
                excluirCategoria(cat);
                break;
            case 0:
                system("cls");
                return;
            default:
                ERRO(1);
                manterCategoria();
                return;
        }
    }
}

void adicionarCategoria()
{
    char strAux[100];
    if(numCategoria == 0)
    {
        categorias = (TCategoria *)malloc(1 * sizeof(TCategoria));
    }
    else
    {
        categorias = (TCategoria *)realloc(categorias, (numCategoria + 1) * sizeof(TCategoria));
    }

    while(1)
    {
        printf("Qual a categoria?\n");
        fflush(stdin);
        gets(strAux);
        fflush(stdin);
        if(validarCategoria(strAux) == 1)
        {
            categorias[numCategoria].nome = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
            strcpy(categorias[numCategoria].nome, strAux);
            break;
        }
        else
        {
            ERRO(12);
        }
    }

    numCategoria++;
    system("cls");
}

int selecionarCategoria(int ind)
{
    int i, j, aux = 0, opCategoria;
    printf("Você deseja selecionar qual categoria?\n");
    if (ind == -1)
    {
        for (i = 0; i < numCategoria; i++)
        {
            printf("%d) ", i + 1);
            puts(categorias[i].nome);
        }
    }
    else
    {
        for (i = 0; i < numCategoria && encontros[ind].numCategoriaEnc < numCategoria; i++)
        {
            for (j = 0; j < encontros[ind].numCategoriaEnc; j++)
            {
                if (strcmp(categorias[i].nome, encontros[ind].categoria[j].nome) == 0)
                {
                    aux++;
                }
            }
            if (aux == 0)
            {
                printf("%d) ", i + 1);
                puts(categorias[i].nome);
            }
            else
            {
                VERMELHO;
                printf("%d) ", i + 1);
                puts(categorias[i].nome);
                BRANCO;
                aux = 0;
            }
        }   
        if (encontros[ind].numCategoriaEnc == numCategoria)
        {
            printf("teste123\n");
            printf("Não há mais categorias disponíveis\n");
            return -10;
        }
    }
    scanf("%d", &opCategoria);

    while(validarValor(opCategoria, 1, numCategoria) == 0)
    {
        printf("Você deseja selecionar qual categoria?\n");
        for (i = 0; i < numCategoria; i++)
        {
            printf("%d) ", i + 1);
            puts(categorias[i].nome);
        }
        scanf("%d", &opCategoria);
    }


    return opCategoria - 1;
}

void alterarCategoria(int cat)
{
    char strAux[100];
    if(ValidarExcluirCategoria(cat) == 0)
    {
        ERRO(6);
        system("pause");
        manterCategoria();
        return;
    }
    printf("Qual o novo nome da categoria?\n");
    fflush(stdin);
    gets(strAux);
    fflush(stdin);
    categorias[cat].nome = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
    strcpy(categorias[cat].nome, strAux);  
    system("cls");
}

void excluirCategoria(int cat)
{
    int i, conf;
    if(ValidarExcluirCategoria(cat) == 0)
    {
        ERRO(6);
        system("pause");
        manterCategoria();
        return;
    }
    printf("Tem certeza que quer excluir a categoria?\n");
    printf("1) Sim\n2) Não\n");
    
    scanf("%d", &conf);
    if (conf == 1)
    {
        for(i = cat; i < numCategoria - 1; i++)
        {
            categorias[i] = categorias[i + 1];
        }
        numCategoria--;
        categorias = (TCategoria *)realloc(categorias, numCategoria * sizeof(TCategoria));
        system("cls");
    }
    else if (conf == 2)
    {
        system("cls");
        manterCategoria();
        return;
    }
    else
    {
        ERRO(1);
        excluirCategoria(cat);
        return;
    }
}

int ValidarExcluirCategoria(int cat)
{
    int i, j;
    for (i = 0; i < numEncontro; i++)
    {
        for (j = 0; j < encontros[i].numCategoriaEnc; j++)
        {
            if (strcmp(categorias[cat].nome, encontros[i].categoria[j].nome) == 0)
            {
                return 0;
            }
        }
    }
    return 1;
}

void salvarCategoria()
{
    int i;
    FILE *pArq;

    pArq = fopen("categoriasBD.txt", "w");
    for (i = 0; i < numCategoria; i++)
    {
        fprintf(pArq, "%s;", categorias[i].nome);
        fprintf(pArq, "%c", '\n');
    }
    fclose(pArq);
}

void recuperarCategoria()
{
    int i = 0;
    char c, str[100];
    FILE *pArq;

    pArq = fopen("categoriasBD.txt", "r");
    if (pArq)
    {
        while (!feof(pArq))
        {
            c = fgetc(pArq);

            if (c != ';' && c != '\n' && c != EOF)
            {
                str[i++] = c;
            }
            else if (c == ';' || c == '\n')
            {
                str[i] = '\0';
                i = 0;
                if (c == ';')
                {
                    if (numCategoria == 0)
                    {
                        categorias = (TCategoria *)malloc(1 * sizeof(TCategoria));
                    }
                    else
                    {
                        categorias = (TCategoria *)realloc(categorias, (numCategoria + 1) * sizeof(TCategoria));
                    }
                    categorias[numCategoria].nome = (char *)malloc((strlen(str) + 1) * sizeof(char));
                    strcpy(categorias[numCategoria].nome, str);
                }
                else
                {
                    numCategoria++;
                }
            }
        }
    }
    fclose(pArq);
}

void manterEncontro()
{
    int opEncontro = 1, enc;
    while(opEncontro != 0)
    {
        printf("1) Adicionar encontro\n");
        printf("2) Alterar encontro\n");
        printf("3) Excluir encontro\n");
        printf("0) Voltar\n");
        scanf("%d", &opEncontro);

        switch(opEncontro)
        {
            case 1:
                system("cls");
                adicionarEncontro();
                break;
            case 2:
                system("cls");
                enc = selecionarEncontro();
                alterarEncontro(enc);
                break;
            case 3:
                system("cls");
                enc = selecionarEncontro();
                excluirEncontro(enc);
                break;
            case 0:
                system("cls");
                return;
            default:
                ERRO(1);
                manterEncontro();
                return;
        }
    }
}

void adicionarEncontro()
{
    int aux, cont = 0, op = 0, auxDat = 0, auxHora = 0, auxIndice = 0;
    char strAux[200];

    if(numEncontro == 0)
    {
        encontros = (TEncontro*)malloc(1 * sizeof(TEncontro));
    }
    else
    {
        encontros = (TEncontro*)realloc(encontros, (numEncontro + 1) * sizeof(TEncontro));
    }

    encontros[numEncontro].numAmigoEnc = 1;
    encontros[numEncontro].numCategoriaEnc = 1;

    printf("Preencha os dados do encontro:\n");

    encontros[numEncontro].amigos = (TAmigo *)malloc(1 * sizeof(TAmigo));
    encontros[numEncontro].indiceAmigo = (int *)malloc(1 * sizeof(int));
    aux = selecionarAmigo(-1);
    encontros[numEncontro].indiceAmigo[auxIndice++] = aux;
    encontros[numEncontro].amigos[cont] = amigos[aux];
    while (1)
    {
        printf("Deseja selecionar mais um amigo?\n");
        printf("1) Sim\n");
        printf("2) Não\n");
        scanf("%d", &op);
        if (op == 1)
        {
            cont++;
            encontros[numEncontro].amigos = (TAmigo*)realloc(encontros[numEncontro].amigos, (cont + 1) * sizeof(TAmigo));
            encontros[numEncontro].indiceAmigo = (int *)realloc(encontros[numEncontro].indiceAmigo, (auxIndice + 1) * sizeof(int));
            aux = selecionarAmigo(numEncontro);
            if (aux != -10)
            {
                if (ValidarAmigoEnc(aux, -1) != 0)
                {
                    encontros[numEncontro].indiceAmigo[auxIndice++] = aux;
                    encontros[numEncontro].amigos[cont] = amigos[aux];
                    encontros[numEncontro].numAmigoEnc++;
                }
                else
                {
                    ERRO(7);
                }
            }
            else
            {
                break;
            }
        }
        else if (op == 2)
        {
            cont = 0;
            break;
        }
        else
        {
            ERRO(1);
        }
    }

    auxIndice = 0;
    encontros[numEncontro].categoria = (TCategoria*)malloc(1 * sizeof(TCategoria));
    aux = selecionarCategoria(-1);
    encontros[numEncontro].categoria[cont] = categorias[aux];
    while (1)
    {
        printf("Deseja selecionar mais uma categoria?\n");
        printf("1) Sim\n");
        printf("2) Não\n");
        scanf("%d", &op);
        if (op == 1)
        {
            cont++;
            encontros[numEncontro].categoria = (TCategoria*)realloc(encontros[numEncontro].categoria, (cont + 1) * sizeof(TCategoria));
            aux = selecionarCategoria(numEncontro);
            if (aux != -10)
            {
                if (ValidarCategoriaEnc(aux, -1) != 0)
                {
                    encontros[numEncontro].categoria[cont] = categorias[aux];
                    encontros[numEncontro].numCategoriaEnc++;
                }
                else
                {
                    ERRO(8);
                }
            }
            else
            {
                break;
            }
        }
        else if (op == 2)
        {
            cont = 0;
            break;
        }
        else
        {
            printf("Valor invalido!\n");
        }
    }

    aux = selecionarLocal(0);
    encontros[numEncontro].local = locais[aux];
    encontros[numEncontro].indLoc = aux;

    while(auxHora == 0)
    {
        printf("Qual o horário?(Sem sinal entre hora e minutos)");
        scanf("%d%d", &encontros[numEncontro].horario.hora, &encontros[numEncontro].horario.minuto);
        auxHora = validarHora(encontros[numEncontro].horario.hora, encontros[numEncontro].horario.minuto);
        if (auxHora == 0)
        {
            printf("Horario invalido\n");
        }
    }

    while(auxDat == 0)
    {
        printf("Qual a data do encontro? (DD MM AAAA, sem barras)\n");
        scanf("%d%d%d", &encontros[numEncontro].data.dia, &encontros[numEncontro].data.mes, &encontros[numEncontro].data.ano);
        auxDat = valide_data(encontros[numEncontro].data.dia, encontros[numEncontro].data.mes, encontros[numEncontro].data.ano);
        if (auxDat == 0)
        {
            printf("Valor invalido!\n");
        }
    }

    printf("O que acontecera no encontro?\n");
    fflush(stdin);
    gets(strAux);
    fflush(stdin);
    encontros[numEncontro].desc = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
    strcpy(encontros[numEncontro].desc, strAux);

    numEncontro++;
    system("cls");
}

int ValidarAmigoEnc(int amg, int ind)
{
    int i;
    if (ind == -1)
    {
        for (i = 0; i < encontros[numEncontro].numAmigoEnc; i++)
        {
            if (amg == encontros[numEncontro].indiceAmigo[i])
            {
                return 0;
            }
        }
        return 1;
    }
    else
    {
        for (i = 0; i < encontros[ind].numAmigoEnc; i++)
        {
            if (amg == encontros[ind].indiceAmigo[i])
            {
                return 0;
            }
        }
        return 1;
    }
}

int ValidarCategoriaEnc(int cat, int ind)
{
    int i;
    if (ind == -1)
    {
        for (i = 0; i < encontros[numEncontro].numCategoriaEnc; i++)
        {
            if (strcmp(categorias[cat].nome, encontros[numEncontro].categoria[i].nome) == 0)
            {
                return 0;
            }
        }
        return 1;
    }
    else
    {
        for (i = 0; i < encontros[ind].numCategoriaEnc; i++)
        {
            if (strcmp(categorias[cat].nome, encontros[ind].categoria[i].nome) == 0)
            {
                return 0;
            }
        }
        return 1;
    }
}

int selecionarEncontro()
{
    int i, opEncontro;
    printf("Você deseja selecionar qual encontro?\n");
    for (i = 0; i < numEncontro; i++)
    {
        printf("%d) ", i + 1);
        puts(encontros[i].desc);
    }
    scanf("%d", &opEncontro);

    while(validarValor(opEncontro, 1, numEncontro) == 0)
    {
        printf("Você deseja selecionar qual encontro?\n");
        for (i = 0; i < numEncontro; i++)
        {
            printf("%d) ", i + 1);
            puts(encontros[i].desc);
        }
        scanf("%d", &opEncontro);
    }

    return opEncontro - 1;
}

void alterarEncontro(int enc)
{
    int opAlt, auxDat = 0, auxHora = 0, i, aux;
    char strAux[100];
    printf("Você deseja alterar:\n");

    printf("1) Amigos (");
    for (i = 0; i < encontros[enc].numAmigoEnc; i++)
    {
        printf("%s", encontros[enc].amigos[i].nome);
        if (i != encontros[enc].numAmigoEnc - 1)
        {
            printf(", ");
        }
    }
    printf(")\n");

    printf("2) Categorias (");
    for (i = 0; i < encontros[enc].numCategoriaEnc; i++)
    {
        printf("%s", encontros[enc].categoria[i].nome);
        if (i != encontros[enc].numCategoriaEnc - 1)
        {
            printf(", ");
        }
    }
    printf(")\n");

    printf("3) Local (%s)\n", encontros[enc].local.nome_encontro); 
    printf("4) Horário (%d:%d)\n", encontros[enc].horario.hora, encontros[enc].horario.minuto);
    printf("5) Data (%d/%d/%d)\n", encontros[enc].data.dia, encontros[enc].data.mes, encontros[enc].data.ano); 
    printf("6) Descrição (%s)\n", encontros[enc].desc); 
    scanf("%d", &opAlt);

    if(validarValor(opAlt, 1, 6) == 0)
    {
        system("cls");
        alterarEncontro(enc);
    }

    switch(opAlt)
    {
        case 1:
            system("cls");
            alterarAmigoEnc(enc);
            break;
        case 2:
            system("cls");
            alterarCategoriaEnc(enc);
            break;
        case 3:
            printf("Qual o novo local?\n");
            aux = selecionarLocal(0);
            encontros[enc].local = locais[aux];
            encontros[enc].indLoc = aux;
            break;
        case 4:
            while(auxHora == 0)
            {
                printf("Qual o horário?(Sem sinal entre hora e minutos)");
                scanf("%d%d", &encontros[enc].horario.hora, &encontros[enc].horario.minuto);
                auxHora = validarHora(encontros[enc].horario.hora, encontros[enc].horario.minuto);
                if (auxHora == 0)
                {
                    printf("Horario invalido\n");
                }
            }
            break;
        case 5:
            while(auxDat == 0)
            {
                printf("Qual a nova data do encontro? (DD MM AAAA, sem barras)\n");
                scanf("%d%d%d", &encontros[enc].data.dia, &encontros[enc].data.mes, &encontros[enc].data.ano);
                auxDat = valide_data(encontros[enc].data.dia, encontros[enc].data.mes, encontros[enc].data.ano);
                if (auxDat == 0)
                {
                    printf("Valor invalido!\n");
                }
            }
            break;
        case 6:
            printf("Qual a nova descrição?\n");
            fflush(stdin);
            gets(strAux);
            fflush(stdin);
            encontros[enc].desc = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
            strcpy(encontros[enc].desc, strAux);
            break;
    }
    system("cls");
}

void alterarAmigoEnc(int enc)
{
    int i, op, aux, conf;
    printf("Você deseja: \n");
    printf("1) Adicionar mais amigos\n");
    printf("2) Excluir um amigo\n");
    printf("0) Sair\n");
    scanf("%d", &op);
    system("cls");
    switch(op)
    {
        case 1:
            encontros[enc].amigos = (TAmigo*)realloc(encontros[enc].amigos, (encontros[enc].numAmigoEnc + 1) * sizeof(TAmigo));
            encontros[enc].indiceAmigo = (int *)realloc(encontros[enc].indiceAmigo, (encontros[enc].numAmigoEnc + 1) * sizeof(int));
            aux = selecionarAmigo(enc);
            if (aux != -10)
            {
                if (ValidarAmigoEnc(aux, enc) != 0)
                {
                    encontros[enc].indiceAmigo[encontros[enc].numAmigoEnc] = aux;
                    encontros[enc].amigos[encontros[enc].numAmigoEnc] = amigos[aux];
                    encontros[enc].numAmigoEnc++;
                    break;
                }
                else
                {
                    ERRO(7);
                    system("pause");
                    break;
                }
            }
            else
            {
                system("pause");
                system("cls");
                break;
            }
        case 2:
            aux = selecionarAmigoEnc(enc);
            printf("Tem certeza que quer excluir o amigo?\n");
            printf("1) Sim\n2) Não\n");
            scanf("%d", &conf);

            if (conf == 1)
            {
                if (encontros[enc].numAmigoEnc == 1)
                {
                    ERRO(9);
                    system("pause");
                }
                else
                {
                    for(i = aux; i < encontros[enc].numAmigoEnc - 1; i++)
                    {
                        encontros[enc].amigos[i] = encontros[enc].amigos[i + 1];
                        encontros[enc].indiceAmigo[i] = encontros[enc].indiceAmigo[i + 1];
                    }
                    encontros[enc].numAmigoEnc--;
                    encontros[enc].amigos = (TAmigo *)realloc(encontros[enc].amigos, encontros[enc].numAmigoEnc * sizeof(TAmigo));
                    encontros[enc].indiceAmigo = (int *)realloc(encontros[enc].indiceAmigo, encontros[enc].numAmigoEnc * sizeof(int));
                    system("cls");
                }
            }
            else
            {
                system("cls");
                return;
            }
            break;
        case 0:
            system("cls");
            return;
    }
}

void alterarCategoriaEnc(int enc)
{
    int i, op, aux, conf;
    printf("Você deseja: \n");
    printf("1) Adicionar mais categorias\n");
    printf("2) Excluir uma categoria\n");
    printf("0) Sair\n");
    scanf("%d", &op);
    switch(op)
    {
        case 1:
            encontros[enc].categoria = (TCategoria *)realloc(encontros[enc].categoria, (encontros[enc].numCategoriaEnc + 1) * sizeof(TCategoria));
            aux = selecionarCategoria(enc);
            if (aux != -10)
            {
                if (ValidarCategoriaEnc(aux, enc) != 0)
                {
                    encontros[enc].categoria[encontros[enc].numCategoriaEnc].nome = categorias[aux].nome;
                    encontros[enc].numCategoriaEnc++;
                    break;
                }
                else
                {
                    ERRO(8);
                    system("pause");
                    break;
                }
            }
            else 
            {
                system("pause");
                system("cls");
                break;
            }
        case 2:
            aux = selecionarCategoriaEnc(enc);
            printf("Tem certeza que quer excluir a categoria?\n");
            printf("1) Sim\n2) Não\n");
            scanf("%d", &conf);

            if (conf == 1)
            {
                if (encontros[enc].numCategoriaEnc == 1)
                {
                    ERRO(10);
                    system("pause");
                }
                else
                {
                    for(i = aux; i < encontros[enc].numCategoriaEnc - 1; i++)
                    {
                        encontros[enc].categoria[i] = encontros[enc].categoria[i + 1];
                    }
                    encontros[enc].numCategoriaEnc--;
                    encontros[enc].categoria = (TCategoria *)realloc(encontros[enc].categoria, encontros[enc].numCategoriaEnc * sizeof(TCategoria));
                    system("cls");
                }

            }
            else
            {
                system("cls");
                return;
            }
            break;
    }
}

int selecionarAmigoEnc(int enc)
{
    int i, opAmigo;
    printf("Selecione o amigo desejado:\n");
    for (i = 0; i < encontros[enc].numAmigoEnc; i++)
    {
        printf("%d) %s\n", i + 1, encontros[enc].amigos[i].nome);
    }
    scanf("%d", &opAmigo);

    while(validarValor(opAmigo, 1, encontros[enc].numAmigoEnc) == 0)
    {
        printf("Selecione o amigo desejado:\n");
        for (i = 0; i < encontros[enc].numAmigoEnc; i++)
        {
            printf("%d) %s\n", i + 1, encontros[enc].amigos[i].nome);
        }
        scanf("%d", &opAmigo);
    }

    return opAmigo - 1;
}

int selecionarCategoriaEnc(int enc)
{
    int i, opCategoria;
    printf("Selecione a categoria desejada:\n");
    for (i = 0; i < encontros[enc].numCategoriaEnc; i++)
    {
        printf("%d) %s\n", i + 1, encontros[enc].categoria[i].nome);
    }
    scanf("%d", &opCategoria);

    while(validarValor(opCategoria, 1, encontros[enc].numCategoriaEnc) == 0)
    {
        printf("Selecione a categoria desejada:\n");
        for (i = 0; i < encontros[enc].numCategoriaEnc; i++)
        {
            printf("%d) %s\n", i + 1, encontros[enc].categoria[i].nome);
        }
        scanf("%d", &opCategoria);
    }

    return opCategoria - 1;
}

void excluirEncontro(int enc)
{
    int i, conf;
    printf("Tem certeza que quer excluir o encontro?\n");
    printf("1) Sim\n2) Não\n");
    
    scanf("%d", &conf);
    if (conf == 1)
    {
        for(i = enc; i < numEncontro - 1; i++)
        {
            encontros[i] = encontros[i + 1];
        }
        numEncontro--;
        encontros = (TEncontro *)realloc(encontros, numEncontro * sizeof(TEncontro));
        system("cls");
    }
    else
    {
        system("cls");
        return;
    }
}

void salvarEncontro()
{
    int i, j;
    FILE *pArq;

    pArq = fopen("encontrosBD.txt", "w");
    for (i = 0; i < numEncontro; i++)
    {
        fprintf(pArq, "%i;", encontros[i].numAmigoEnc);
        fprintf(pArq, "%i;", encontros[i].numCategoriaEnc);
        fprintf(pArq, "%i;", encontros[i].data.dia);
        fprintf(pArq, "%i;", encontros[i].data.mes);
        fprintf(pArq, "%i;", encontros[i].data.ano);
        fprintf(pArq, "%i;", encontros[i].horario.hora);
        fprintf(pArq, "%i;", encontros[i].horario.minuto);
        fprintf(pArq, "%d;", encontros[i].indLoc);
        fprintf(pArq, "%s;", encontros[i].desc);
        for (j = 0; j < encontros[i].numAmigoEnc; j++)
        {
            fprintf(pArq, "%d@", encontros[i].indiceAmigo[j]);
        }
        for (j = 0; j < encontros[i].numCategoriaEnc; j++)
        {
            fprintf(pArq, "%s#", encontros[i].categoria[j].nome);
        }
        fprintf(pArq, "%c", '\n');
    }
    fclose(pArq);
}

void recuperarEncontro()
{
    int i = 0, sep = 0, j = 0;
    char c, str[100];
    FILE *pArq;

    pArq = fopen("encontrosBD.txt", "r");
    if (pArq)
    {
        while (!feof(pArq))
        {
            c = fgetc(pArq);

            if (c != ';' && c != '#' && c != '@' && c != '\n' && c != EOF)
            {
                str[i++] = c;
            }
            else if (c == '@' || c == '#' || c == ';' || c == '\n')
            {
                str[i] = '\0';
                i = 0;
                
                if (c == ';')
                {
                    if (sep == 0)
                    {
                        if (numEncontro == 0)
                        {
                            encontros = (TEncontro *)malloc(1 * sizeof(TEncontro));
                        }
                        else
                        {
                            encontros = (TEncontro *)realloc(encontros, (numEncontro + 1) * sizeof(TEncontro));
                        }
                        encontros[numEncontro].numAmigoEnc = atoi(str);
                        sep++;
                    }
                    else if (sep == 1)
                    {
                        encontros[numEncontro].numCategoriaEnc = atoi(str);
                        sep++;
                    }
                    else if (sep == 2)
                    {
                        encontros[numEncontro].data.dia = atoi(str);
                        sep++;
                    }
                    else if (sep == 3)
                    {
                        encontros[numEncontro].data.mes = atoi(str);
                        sep++;
                    }
                    else if (sep == 4)
                    {
                        encontros[numEncontro].data.ano = atoi(str);
                        sep++;
                    }
                    else if (sep == 5)
                    {
                        encontros[numEncontro].horario.hora = atoi(str);
                        sep++;
                    }
                    else if (sep == 6)
                    {
                        encontros[numEncontro].horario.minuto = atoi(str);
                        sep++;
                    }
                    else if (sep == 7)
                    {
                        encontros[numEncontro].indLoc = atoi(str);
                        encontros[numEncontro].local = locais[encontros[numEncontro].indLoc];
                        sep++;
                    }
                    else if (sep == 8)
                    {
                        encontros[numEncontro].desc = (char *)malloc((strlen(str) + 1) * sizeof(char));
                        strcpy(encontros[numEncontro].desc, str);
                        sep = 0;
                    }
                }
                else if (c == '@')
                {
                    if (sep == 0)
                    {
                        encontros[numEncontro].amigos = (TAmigo *)malloc(1 * sizeof(TAmigo));
                        encontros[numEncontro].indiceAmigo = (int *)malloc(1 * sizeof(int));
                        encontros[numEncontro].indiceAmigo[j] = atoi(str);
                        encontros[numEncontro].amigos[j] = amigos[encontros[numEncontro].indiceAmigo[j]];
                        j++;
                    }
                    else
                    {
                        encontros[numEncontro].amigos = (TAmigo *)realloc(encontros[numEncontro].amigos, (j + 1) * sizeof(TAmigo));
                        encontros[numEncontro].indiceAmigo = (int *)realloc(encontros[numEncontro].indiceAmigo, (j + 1) * sizeof(int));
                        encontros[numEncontro].indiceAmigo[j] = atoi(str);
                        encontros[numEncontro].amigos[j] = amigos[encontros[numEncontro].indiceAmigo[j]];
                        j++;
                    }
                    sep = -1;
                }
                else if (c == '#')
                {
                    if(sep == -1)
                    {
                        j = 0;
                        encontros[numEncontro].categoria = (TCategoria *)malloc(1 * sizeof(TCategoria));
                        encontros[numEncontro].categoria[j].nome = (char *)malloc((strlen(str) + 1) * sizeof(char));
                        strcpy(encontros[numEncontro].categoria[j].nome, str);
                        j++;
                    }
                    else
                    {
                        encontros[numEncontro].categoria = (TCategoria *)realloc(encontros[numEncontro].categoria, (j + 1) * sizeof(TCategoria));
                        encontros[numEncontro].categoria[j].nome = (char *)malloc((strlen(str) + 1) * sizeof(char));
                        strcpy(encontros[numEncontro].categoria[j].nome, str);
                        j++;
                    }
                    sep = -2;
                }
                else
                {
                    numEncontro++;
                    sep = 0;
                    j = 0;
                }
            }
        }
    }
    fclose(pArq);
}

void Relatorios()
{
    int op;
    printf("Qual opção você deseja?\n");
    printf("1) Listar amigos\n");
    printf("2) Listar locais\n");
    printf("3) Listar categorias\n");
    printf("4) Listar encontros\n");
    printf("5) Relatório por categoria\n");
    printf("0) Sair\n");
    scanf("%d", &op);
    switch(op)
    {
        case 1:
            system("cls");
            listarAmigos();
            break;
        case 2:
            system("cls");
            listarLocais();
            break;
        case 3:
            system("cls");
            listarCategorias();
            break;
        case 4:
            system("cls");
            listarEncontros();
            break;
        case 5:
            system("cls");
            RelatorioPorCategoria();
            break;
        case 0:
            system("cls");
            return;
        default:
            printf("Valor invalido, tente novamente.\n");
            system("pause");
            system("cls");
            Relatorios();
            break;
    }
}

void listarAmigos()
{
    int op, aux;
    printf("Selecione a opção desejada:\n");
    printf("1) Exibir os dados de todos os amigos\n");
    printf("2) Exibir os dados de um amigo específico\n");
    printf("0) Voltar\n");
    scanf("%d", &op);
    switch(op)
    {
        case 1:
            system("cls");
            PrintaTodosAmigos();
            break;
        case 2:
            aux = selecionarAmigo(-1);
            system("cls");
            PrintaUmAmigo(aux);
            break;
        case 0:
            system("cls");
            Relatorios();
            break;
        default:
            printf("Valor invalido, tente novamente\n");
            system("pause");
            system("cls");
            listarAmigos();
            break;
    }
}

void PrintaTodosAmigos()
{
    int i;
    for(i = 0; i < numAmigo; i++)
    {
        printf("Amigo %d:\n", i + 1);
        printf("Nome: %s\n", amigos[i].nome);
        printf("Apelido: %s\n", amigos[i].apelido);
        printf("Data de nascimento: %d/%d/%d\n", amigos[i].data_nas.dia, amigos[i].data_nas.mes, amigos[i].data_nas.ano);
        printf("Email: %s\n", amigos[i].email);
        printf("Telefone: %s\n", amigos[i].telefone);
        printf("\n");
    }
    system("pause");
    system("cls");
}

void PrintaUmAmigo(int amg)
{
    printf("Nome: %s\n", amigos[amg].nome);
    printf("Apelido: %s\n", amigos[amg].apelido);
    printf("Data de nascimento: %d/%d/%d\n", amigos[amg].data_nas.dia, amigos[amg].data_nas.mes, amigos[amg].data_nas.ano);
    printf("Email: %s\n", amigos[amg].email);
    printf("Telefone: %s\n", amigos[amg].telefone);
    printf("\n");
    system("pause");
    system("cls");
}


void listarLocais()
{
    int op, aux;
    printf("Selecione a opção desejada:\n");
    printf("1) Exibir os dados de todos os locais\n");
    printf("2) Exibir os dados de um local específico\n");
    printf("0) Voltar\n");
    scanf("%d", &op);
    switch(op)
    {
        case 1:
            system("cls");
            PrintaTodosLocais();
            break;
        case 2:
            aux = selecionarLocal(0);
            system("cls");
            PrintaUmLocal(aux);
            break;
        case 0:
            system("cls");
            Relatorios();
            break;
        default:
            printf("Valor invalido, tente novamente\n");
            system("pause");
            system("cls");
            listarLocais();
            break;
    }
}

void PrintaTodosLocais()
{
    int i;
    for(i = 0; i < numLocal; i++)
    {
        printf("Local %d:\n", i + 1);
        printf("Nome: %s\n", locais[i].nome_encontro);
        printf("Logradouro: %s\n", locais[i].endereco.logradouro);
        printf("Numero: %d\n", locais[i].endereco.numero);
        printf("Bairro: %s\n", locais[i].endereco.bairro);
        printf("Cidade: %s\n", locais[i].endereco.cidade);
        printf("Estado: %s\n", locais[i].endereco.estado);
        printf("\n");
    }
    system("pause");
    system("cls");
}

void PrintaUmLocal(int loc)
{
    printf("Nome: %s\n", locais[loc].nome_encontro);
    printf("Logradouro: %s\n", locais[loc].endereco.logradouro);
    printf("Numero: %d\n", locais[loc].endereco.numero);
    printf("Bairro: %s\n", locais[loc].endereco.bairro);
    printf("Cidade: %s\n", locais[loc].endereco.cidade);
    printf("Estado: %s\n", locais[loc].endereco.estado);
    printf("\n");
    system("pause");
    system("cls");
}

void listarCategorias()
{
    int i;
    for(i = 0; i < numCategoria; i++)
    {
        printf("Categoria %d: %s\n", i + 1, categorias[i].nome);
        printf("\n");
    }
    system("pause");
    system("cls");
}

void listarEncontros()
{
    int op, aux;
    printf("Selecione a opção desejada:\n");
    printf("1) Exibir os dados de todos os encontros\n");
    printf("2) Exibir os dados de um encontro específico\n");
    printf("0) Voltar\n");
    scanf("%d", &op);
    switch(op)
    {
        case 1:
            system("cls");
            PrintaTodosEncontros();
            break;
        case 2:
            aux = selecionarEncontro(5);
            system("cls");
            PrintaUmEncontro(aux);
            break;
        case 0:
            system("cls");
            Relatorios();
            break;
        default:
            printf("Valor invalido, tente novamente\n");
            system("pause");
            system("cls");
            listarEncontros();
            break;
    }
}

void PrintaTodosEncontros()
{
    int i, j;
    for(i = 0; i < numEncontro; i++)
    {
        printf("Encontro %d:\n", i + 1);
        for (j = 0; j < encontros[i].numAmigoEnc; j++)
        {
            printf("Amigo %d: %s\n", j + 1, encontros[i].amigos[j].nome);
        }
        for (j = 0; j < encontros[i].numCategoriaEnc; j++)
        {
            printf("Categoria %d: %s\n", j + 1, encontros[i].categoria[j].nome);
        }
        printf("Local: %s\n", encontros[i].local.nome_encontro);
        printf("Data: %d/%d/%d\n", encontros[i].data.dia, encontros[i].data.mes, encontros[i].data.ano);
        printf("Horario: %d:%d\n", encontros[i].horario.hora, encontros[i].horario.minuto);
        printf("Descrição: %s\n", encontros[i].desc);
        printf("\n");
    }
    system("pause");
    system("cls");
}

void PrintaUmEncontro(int enc)
{
    int i;
    for (i = 0; i < encontros[enc].numAmigoEnc; i++)
    {
        printf("Amigo %d: %s\n", i + 1, encontros[enc].amigos[i].nome);
    }
    for (i = 0; i < encontros[enc].numCategoriaEnc; i++)
    {
        printf("Categoria %d: %s\n", i + 1, encontros[enc].categoria[i].nome);
    }
    printf("Local: %s\n", encontros[enc].local.nome_encontro);
    printf("Data: %d/%d/%d\n", encontros[enc].data.dia, encontros[enc].data.mes, encontros[enc].data.ano);
    printf("Horario: %d:%d\n", encontros[enc].horario.hora, encontros[enc].horario.minuto);
    printf("Descrição: %s\n", encontros[enc].desc);
    printf("\n");
    system("pause");
    system("cls");
}

void RelatorioPorCategoria()
{
    int i, j, k, cont = 0, op;
    for (i = 0; i < numCategoria; i++)
    {
        printf("%d) %s ", i + 1, categorias[i].nome);
        for (j = 0; j < numEncontro; j++)
        {
            for (k = 0; k < encontros[j].numCategoriaEnc; k++)
            {
                if(strcmp(categorias[i].nome, encontros[j].categoria[k].nome) == 0)
                {
                    cont++;
                }
            }
        }
        printf("[%d encontros]\n", cont);
        cont = 0;
    }

    printf("Se desejar ver quais os encontros em que cada categoria está digite o número da categoria. Caso contrário, digite 0 (zero)\n");
    scanf("%d", &op);
    if(validarValor(op, 0, numCategoria) == 0)
    {
        RelatorioPorCategoria();
        return;
    }

    if(op == 0)
    {
        system("cls");
        return;
    }
    else
    {
        system("cls");
        PrintaEncontrosDaCategoria(op - 1);
    }

    system("pause");
    system("cls");
}

void PrintaEncontrosDaCategoria(int cat)
{
    int i, j, k;
    for (i = 0; i < numEncontro; i++)
    {
        for (j = 0; j < encontros[i].numCategoriaEnc; j++)
        {
            if(strcmp(categorias[cat].nome, encontros[i].categoria[j].nome) == 0)
            {
                for (k = 0; k < encontros[i].numAmigoEnc; k++)
                {
                    printf("Amigo %d: %s\n", k + 1, encontros[i].amigos[k].nome);
                }
                for (k = 0; k < encontros[i].numCategoriaEnc; k++)
                {
                    printf("Categoria %d: %s\n", k + 1, encontros[i].categoria[k].nome);
                }
                printf("Local: %s\n", encontros[i].local.nome_encontro);
                printf("Data: %d/%d/%d\n", encontros[i].data.dia, encontros[i].data.mes, encontros[i].data.ano);
                printf("Horario: %d:%d\n", encontros[i].horario.hora, encontros[i].horario.minuto);
                printf("Descrição: %s\n", encontros[i].desc);
                printf("\n");
            }
        }
    }
}

void liberarPonteiros()
{
    int i;
    for (i = 0; i < numAmigo; i++)
    {
        free(amigos[i].nome);
        free(amigos[i].apelido);
        free(amigos[i].email);
        free(amigos[i].telefone);
    }
    for (i = 0; i < numLocal; i++)
    {
        free(locais[i].nome_encontro);
        free(locais[i].endereco.logradouro);
        free(locais[i].endereco.bairro);
        free(locais[i].endereco.cidade);
        free(locais[i].endereco.estado);
    }
    for (i = 0; i < numCategoria; i++)
    {
        free(categorias[i].nome);
    }
    for (i = 0; i < numEncontro; i++)
    {
        free(encontros[i].amigos);
        free(encontros[i].categoria);
        free(encontros[i].desc);
        free(encontros[i].indiceAmigo);

    }
    free(amigos);
    free(locais);
    free(categorias);
    free(encontros);
}

int validarValor(int num, int param1, int param2)
{
    if(num < param1 || num > param2)
    {
        ERRO(1);
        return 0;
    }
    return 1;
}

int valide_data(int dias, int mes, int ano)
{
    if (mes > 12 || mes <= 0)
    {
        return 0;
    }
    if (mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12)
    {
        if (dias <= 0 || dias > 31)
        {
            return 0;
        }
    }
    if (mes == 4 || mes == 6 || mes == 9 || mes == 11)
    {
        if (dias <= 0 || dias > 30)
        {
            return 0;
        }
    }
    if (ano % 4 == 0 && mes == 2)
    {
        if (dias <= 0 || dias > 29)
        {
            return 0;
        }
    }
    else if (mes == 2)
    {
        if (dias <= 0 || dias > 28)
        {
            return 0;
        }
    }
    return 1;
}

int validarHora(int hora, int minuto)
{
    if(hora >= 24 || hora < 0)
    {
        return 0;
    }
    if (minuto >= 60 || minuto < 0)
    {
        return 0;
    }
    return 1;
}

int validarAmigo(char amg[100])
{
    int i;
    for (i = 0; i < numAmigo; i++)
    {
        if (strcmp(amg, amigos[i].nome) == 0)
        {
            return 0;
        }
    }
    return 1;
}

int validarCategoria(char cat[100])
{
    int i;
    for (i = 0; i < numCategoria; i++)
    {
        if (strcmp(cat, categorias[i].nome) == 0)
        {
            return 0;
        }
    }
    return 1;
}

void ERRO(int id)
{
    if (id == 1)
    {
        printf("Valor invalido, tente novamente!\n");
    }
    else if (id == 2)
    {
        printf("Data invalida, tente novamente!\n");
    }
    else if (id == 3)
    {
        printf("Horario invalido, tente novamente!\n");
    }
    else if (id == 4)
    {
        printf("O amigo já está em um encontro, exclua todos os encontros em que ele está primeiro!\n");
    }
    else if (id == 5)
    {
        printf("Já existe um encontro com este local, exclua todos os encontros com este local primeiro!\n");
    }
    else if (id == 6)
    {
        printf("Já existe um encontro com esta categoria, exclua todos os encontros com esta categoria primeiro!\n");
    }
    else if (id == 7)
    {
        printf("Amigo já adicionado.\n");
    }
    else if (id == 8)
    {
        printf("Categoria ja adicionada.\n");
    }
    else if (id == 9)
    {
        printf("Não eh possivel excluir o amigo pois ele é o unico que ainda está cadastrado nesse encontro\n");
    }
    else if (id == 10)
    {
        printf("Não eh possivel excluir a categoria pois ela é a unica que ainda está cadastrada nesse encontro\n");  
    }
    else if (id == 11)
    {
        printf("Já existe um amigo com esse nome\n");
    }
    else if (id == 12)
    {
        printf("Ja existe uma categoria com esse nome\n");
    }
}

void salvarDados()
{
    salvarAmigo();
    salvarLocal();
    salvarCategoria();
    salvarEncontro();
}

void recuperarDados()
{
    recuperarAmigo();
    recuperarLocal();
    recuperarCategoria();
    recuperarEncontro();
}