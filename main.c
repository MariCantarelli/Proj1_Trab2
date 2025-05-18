//Beatriz Di Palma Carvalho, RA: 10439477
//Luiza Marinho de Mesquita, RA: 10438045
//Marina Cantarelli Barroca, RA: 10740412


#include <stdio.h>      
#include <stdlib.h>     
#include <time.h>      
     
// Definindo constantes para tamanhos máximos(vetor, nome do aluno e arq csv)
#define MAX 1000000          
#define TAM_MAX_NOME 100     
#define TAM_MAX_LINHA 256    

// Estrutura que armazena os dados de um aluno
typedef struct {
    int ano;                
    char turma;              
    char serie;             
    char nome[TAM_MAX_NOME]; 
    char disciplina[20];     
    float nota;              
} Aluno;

// Função que troca dois elementos do vetor
void trocar(Aluno *a, Aluno *b) {
    // Cria uma variável temporária para armazenar o conteúdo de 'a'
    Aluno temp = *a;
    *a = *b; // Copia de 'b' para o 'a'
    *b = temp; // Copia emporária para 'b'
}

// Função que compara duas strings
int comparar_string(char *a, char *b){
    while(*a && *b){
        if (*a != *b){  //   se os caracteres forem diferentes  
            return (*a - *b); // Retorna a diferença
        }
        a++;
        b++; // Vai pro proximo caractere
    }
    return (*a - *b); // Se forem iguais retorna 0
}

// Funcao que copia a string
int copiar_string(char *dest, char*src){
    while(*src){    // Enquanto o caractere atual nao for o fim da string copia o caractere
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
}

// Implementação do Bubble Sort com contador de comparações 
void bubbleSort(Aluno *vetor, int n, size_t *comparacoes) {
    *comparacoes = 0;    // Reseta o contador de comparações
    // Loop externo para percorrer o nosso vetor
    for (int i = 0; i < n - 1; i++) {
        // Loop interno para comparar os elementos adjacentes
        for (int j = 0; j < n - i - 1; j++) {
            (*comparacoes)++; // Incrementa o contador de comparações
            // Se a nota do elemento atual for maior, ele troca os elementos
            if (vetor[j].nota > vetor[j + 1].nota) {
                trocar(&vetor[j], &vetor[j + 1]);
            }
        }
    }
}

// Função que auxilia o Merge Sort para mesclar dois subvetores ordenados 
void merge(Aluno *vetor, int esquerda, int meio, int direita, size_t *comparacoes) {
    // Calcula os tamanhos dos subvetores
    int n1 = meio - esquerda + 1; //tam do subvetor esquerdo
    int n2 = direita - meio; // Tama do subvetor direito

    // Aloca vetores temporários para os subvetores
    Aluno *L = malloc(n1 * sizeof(Aluno));
    Aluno *R = malloc(n2 * sizeof(Aluno));

    // Copia os dados para os vetores temporários
    for (int i = 0; i < n1; i++)
        L[i] = vetor[esquerda + i];
    for (int j = 0; j < n2; j++)
        R[j] = vetor[meio + 1 + j];

    // Mescla os subvetores ordenados de volta ao vetor original
    int i = 0, j = 0, k = esquerda;
    while (i < n1 && j < n2) {
        (*comparacoes)++; // Adiciona o contador de comparações
        // Compara as notas e copia o menor elemento
        if (L[i].nota <= R[j].nota) {
            vetor[k++] = L[i++];
        } else {
            vetor[k++] = R[j++];
        }
    }

    // Copia os elementos restantes do subvetor esquerdo, se tiver
    while (i < n1) vetor[k++] = L[i++];
    // Copia os elementos restantes do subvetor direito, se tiver
    while (j < n2) vetor[k++] = R[j++];

    // Libera a memória alocada para os nossos vetores temporários
    free(L);
    free(R);
}

// Implementação do Merge Sort com contador de comparações como parâmetro
void mergeSort(Aluno *vetor, int esquerda, int direita, size_t *comparacoes) {
    // Verifica se há mais de um elemento para dividir
    if (esquerda < direita) {
        // Calcula o ponto médio evitando o overflow
        int meio = esquerda + (direita - esquerda) / 2;
        // Ordena recursivamente as 2 metades
        mergeSort(vetor, esquerda, meio, comparacoes);
        mergeSort(vetor, meio + 1, direita, comparacoes);
        // Mescla os subvetores ordenados
        merge(vetor, esquerda, meio, direita, comparacoes);
    }
}

// Geração de entrada aleatória em um arquivo CSV
void gerarEntradaAleatoria(const char *arquivo, int n) {
    // Abre o arquivo
    FILE *fp = fopen(arquivo, "w");
    if (!fp) {
        //caso o arquivo não puder ser criado mostra a mensagem
        printf("Erro ao criar o arquivo %s\n", arquivo);
        return;
    }

    // Arrays com opções para geração aleatória
    char *disciplinas[] = {"Matemática", "Português", "Geografia"};
    char *nomes[] = {"João", "Maria", "Camila", "José", "Ana", "Carlos", "Beatriz", "Pedro", "Patricia", "Leandro", "Luiza", "Leonardo", "Marina", "Fernanda", "Rafael", "Juliana", "Gustavo", "Andre", "Theo", "Andressa", "Laura"};
    char *sobrenome[] = {"Carvalho", "Di Palma", "Marinho", "Cantarelli", "Aquino", "Soares", "Oliveira", "Souza", "Rodrigues", "Silva", "Marques", "Yoshida", "Bevilaqua", "Souza", "Lima", "Ferreira", "Mesquita", "Duarte"};
    // Inicializa a semente do gerador de números aleatórios com o tempo atual
    srand(time(NULL));

    // Gera 'n' registros aleatórios
    for (int i = 0; i < n; i++) {
        int ano = 1 + rand() % 3;                    // Ano entre 1 e 3
        char turma = 'A' + rand() % 3;               // Turma entre A e C
        char serie = 'M' + rand() % 2;               // Série entre Manhã(M) e Noite(N)
        char *nome_aleatorio = nomes[rand() % 13];   // Nome aleatório
        char *sobrenome_aleatorio = sobrenome[rand() % 9]; // Sobrenome aleatório
        char nome_inteiro[TAM_MAX_NOME];
        // Junta o nome e sobrenome em uma string
        snprintf(nome_inteiro, TAM_MAX_NOME, "%s %s", nome_aleatorio, sobrenome_aleatorio);
        char *disciplina = disciplinas[rand() % 3];   // Escolhe uma disciplina
        float nota = (float)(rand() % 101) / 10.0;   // Nota entre 0.0 e 10.0

        // Escreve o registro no arquivo CSV
        fprintf(fp, "%d,%c,%c,%s,%s,%.1f\n", ano, turma, serie, nome_inteiro, disciplina, nota);
    }

    // Fecha o arquivo
    fclose(fp);
    printf("Arquivo %s gerado com %d alunos.\n", arquivo, n);
}

// Função para ler alunos de um arquivo CSV
Aluno* lerAlunos(const char *arquivo, int *n) {
    // Abre o arquivo em modo de leitura
    FILE *fp = fopen(arquivo, "r");
    if (!fp) {
        // Mostra mensagem de erro se o arquivo não puder ser aberto
        printf("Erro ao abrir o arquivo %s\n", arquivo);
        return NULL;
    }

    // Começa o vetor de alunos e o nosso contador
    Aluno *alunos = NULL;
    *n = 0;
    char linha[TAM_MAX_LINHA];

    // Lê cada linha do arquivo
    while (fgets(linha, TAM_MAX_LINHA, fp)) {
        // Realoca o vetor para mais um aluno
        alunos = realloc(alunos, (*n + 1) * sizeof(Aluno));
        // Divide a linha em tokens usando a vírgula como o delimitador
        char *token = strtok(linha, ",");
        alunos[*n].ano = atoi(token); // Converte o ano para inteiro
        token = strtok(NULL, ",");
        alunos[*n].turma = token[0]; // Obtém a turma (o primeiro caractere)
        token = strtok(NULL, ",");
        alunos[*n].serie = token[0]; // Obtém a série
        token = strtok(NULL, ",");
        // Copia o nome, garantindo que não exceda o limite que colocamos anteriormente
        strncpy(alunos[*n].nome, token, TAM_MAX_NOME - 1);
        alunos[*n].nome[TAM_MAX_NOME - 1] = '\0'; // Adiciona o terminador nulo
        token = strtok(NULL, ",");
        // Copia a disciplina
        strncpy(alunos[*n].disciplina, token, 19);
        alunos[*n].disciplina[19] = '\0'; // Adiciona o terminador nulo
        token = strtok(NULL, ",");
        alunos[*n].nota = atof(token); // Converte a nota para float
        (*n)++; // Incrementa o contador de alunos
    }

    // Fecha o arquivo
    fclose(fp);
    return alunos;
}

// Função para escrever alunos ordenados em um novo arquivo CSV
void escreverAlunos(const char *arquivo, Aluno *alunos, int n) {
    // Abre o arquivo em modo de escrita
    FILE *fp = fopen(arquivo, "w");
    if (!fp) {
        // Exibe mensagem de erro se o arquivo não puder ser criado
        printf("Erro ao criar o arquivo %s\n", arquivo);
        return;
    }

    // Escreve cada aluno no arquivo CSV
    for (int i = 0; i < n; i++) {
        fprintf(fp, "%d,%c,%c,%s,%s,%.1f\n",
                alunos[i].ano, alunos[i].turma, alunos[i].serie,
                alunos[i].nome, alunos[i].disciplina, alunos[i].nota);
    }

    // Fecha o arquivo
    fclose(fp);
    printf("Arquivo %s gerado com %d alunos ordenados.\n", arquivo, n);
}

// Função para medir o desempenho (tempo e comparações)
// Função para medir o desempenho (tempo e comparações)
void medirDesempenho(void (funcOrdenar)(Aluno*, int, size_t*), Aluno *alunos, int n, const char *nomeAlg, const char *arquivoSaida) {
    double tempoTotal = 0.0;     // Acumula o tempo de execução
    long long comparacoesTotais = 0; // Acumula o número de comparações
    const int execucoes = 10;    // Número de execuções para calcular a média

    // Executa o nosso algoritmo várias vezes para obter médias
    for (int i = 0; i < execucoes; i++) {
        // Cria uma cópia do vetor de alunos
        Aluno *copia = malloc(n * sizeof(Aluno));
        for (int j=0; j <n; j++){
            copia[j] = alunos[j];
        }

        size_t comparacoes = 0; // Contador local para esta execução
        clock_t inicio_bubble = clock();

        // Mede o tempo de execução
        //double in_bubble = (double)clock(); // Tempo de início
        if (comparar_string((char*)nomeAlg, "Merge Sort") == 0) {
            mergeSort(copia, 0, n - 1, &comparacoes); // Chama Merge Sort
        } else {
            funcOrdenar(copia, n, &comparacoes); // Chama Bubble Sort
        }
        //double end_bubble = (double)clock(); // Tempo de fim

        clock_t fim_bubble = clock();

        // Calcula o tempo em segundos
        tempoTotal += (double)(fim_bubble - inicio_bubble) / CLOCKS_PER_SEC;
        comparacoesTotais += comparacoes;

        // Grava o resultado da primeira execução no arquivo
        if (i == 0) {
            escreverAlunos(arquivoSaida, copia, n);
        }

        // Libera a cópia do vetor
        free(copia);
    }

    // Exibe os resultados médios resultantes
    printf("\nAlgoritmo: %s\n", nomeAlg);
    printf("Tamanho da entrada: %d\n", n);
    printf("Tempo de execução médio: %.6f segundos\n", tempoTotal / execucoes);
    printf("Média de comparações: %lld\n", comparacoesTotais / execucoes);
}


// Função principal com um menu interativo
int main() {
    int opcao, n; // Variáveis para a opção do menu e número de alunos
    Aluno *alunos = NULL; // Ponteiro para o nosso vetor de alunos

    // Loop do menu
    do {
        // Exibe o menu
        printf("\nMenu:\n");
        printf("1. Gerar entrada aleatória (entrada.csv)\n");
        printf("2. Ordenar por nota (Bubble Sort)\n");
        printf("3. Ordenar por nota (Merge Sort)\n");
        printf("4. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        // Processa a opção que foi escolhida
        switch (opcao) {
            case 1:
                // Solicita o número de alunos e gera o arquivo
                printf("Digite a quantidade de alunos: ");
                scanf("%d", &n);
                gerarEntradaAleatoria("entrada.csv", n);
                break;

            case 2:
                // Lê o arquivo e ordena com Bubble Sort
                alunos = lerAlunos("entrada.csv", &n);
                if (alunos) {
                    medirDesempenho(bubbleSort, alunos, n, "Bubble Sort", "saidabubble.csv");
                    free(alunos); // Libera a memória
                }
                break;

            case 3:
                // Lê o arquivo e ordena com Merge Sort
                alunos = lerAlunos("entrada.csv", &n);
                if (alunos) {
                    medirDesempenho(NULL, alunos, n, "Merge Sort", "saidamerge.csv");
                    free(alunos); // Libera a memória
                }
                break;

            case 4:
                // Encerra o programa
                printf("Saindo...\n");
                break;

            default:
                // Exibe mensagem para opção inválida
                printf("Opção inválida!\n");
        }
    } while (opcao != 4); // Continua até o usuário escolher sair

    return 0; // Finaliza o programa
}
