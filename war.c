// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
// ============================================================================
//
// OBJETIVOS:
// - Modularizar completamente o código em funções especializadas.
// - Implementar um sistema de missões para um jogador.
// - Criar uma função para verificar se a missão foi cumprida.
// - Utilizar passagem por referência (ponteiros) para modificar dados e
//   passagem por valor/referência constante (const) para apenas ler.
// - Foco em: Design de software, modularização, const correctness, lógica de jogo.
//
// ============================================================================

// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.
//#define MAX_TERRITORIOS 5
#define NUM_MISSOES 5
#define TAM_STRING 100

// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.
struct TERRITORIO {
    char nome[TAM_STRING];
    char cor_exercito[TAM_STRING];
    int numero_tropas;
};

// --- Protótipos das Funções ---
// Declarações antecipadas de todas as funções que serão usadas no programa, organizadas por categoria.
// Funções de setup e gerenciamento de memória:
// Funções de interface com o usuário:
// Funções de lógica principal do jogo:
// Função utilitária:
// Protótipos das funções
void cadastrar(struct TERRITORIO *mapa, int MAX_TERRITORIOS, int *total_territorios);
int limparBufferEntrada();

//Função para limpar o buffer de entrada
int limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    return 0;
}

// Função para cadastrar territórios

void cadastrar(struct TERRITORIO *mapa, int MAX_TERRITORIOS, int *total_territorios) {
    while (*total_territorios < MAX_TERRITORIOS) {
        printf("\n--- Cadastro do território %d ---\n", *total_territorios + 1);
        printf("Digite o nome do território: ");
        fgets(mapa[*total_territorios].nome, TAM_STRING, stdin);

        printf("Digite a cor do exército: ");
        fgets(mapa[*total_territorios].cor_exercito, TAM_STRING, stdin);

        printf("Digite o número de tropas: ");
        scanf("%d", &mapa[*total_territorios].numero_tropas);
        limparBufferEntrada(); // Limpa o buffer após ler um número

        // Remove a nova linha lida pelo fgets
        mapa[*total_territorios].nome[strcspn(mapa[*total_territorios].nome, "\n")] = 0;
        mapa[*total_territorios].cor_exercito[strcspn(mapa[*total_territorios].cor_exercito, "\n")] = 0;

        (*total_territorios)++;
    }
}

// Função para EXIBIR o mapa do mundo
int exibirMapa(const struct TERRITORIO *mapa, int total_territorios) {
    printf("====================================\n");
    printf("  MAPA DO MUNDO - ESTADO ATUAL\n");
    printf("====================================\n\n");
        for (int i = 0; i < total_territorios; i++) {
            printf("%d. %s (Exército %s, Tropas: %d)\n", i + 1, mapa[i].nome, mapa[i].cor_exercito, mapa[i].numero_tropas);
    }
    printf("\n====================================\n");
    return 0;
}

// Função para realizar o ATAQUE entre territórios

void ataque(struct TERRITORIO *mapa, int *total_territorios) {  
    int *atacante = (int*)malloc(sizeof(int));
    int *defesa = (int*)malloc(sizeof(int));
    int sorteio_atacante, sorteio_defesa;
    char continuar[5]; // Variável para controlar a continuação do ataque    
    while (1) {
    printf("\n --- FASE DE ATAQUE ---\n\n");
    printf("Escolha o território atacante (1 a %d, ou 0 para SAIR): ", *total_territorios);
    scanf("%d", atacante);
    limparBufferEntrada(); // Limpa o buffer após ler um número
    if (*atacante == 0) {
        printf("Saindo da fase de ataque.\n");
        break;      
    } else {sorteio_atacante = 1 + rand() % 6;} // Simula o dado do atacante
     
    printf("Escolha o território defensor (1 a %d, ou 0 para SAIR): ", *total_territorios);
    scanf("%d", defesa);    
    limparBufferEntrada(); // Limpa o buffer após ler um número
    if (*defesa == *atacante) {
        while (*defesa == *atacante) {
        printf("Erro: O território defensor não pode ser o mesmo que o atacante. Tente novamente.\n");    
        printf("Escolha o território defensor (1 a %d, ou 0 para SAIR): ", *total_territorios);
        scanf("%d", defesa);    
        limparBufferEntrada(); // Limpa o buffer após ler um número
        }
    }
    if (*defesa == 0) {
        printf("Saindo da fase de ataque.\n");
        break;
    } else {
        
        sorteio_defesa = 1 + rand() % 6; // Simula o dado do defensor
        while (sorteio_defesa == sorteio_atacante) {
            sorteio_atacante = 1 + rand() % 6; // Simula novo dado do atacante
            sorteio_defesa = 1 + rand() % 6; // Simula novo dado do defensor
        }
    }
    printf("\n--- RESULTADO DA BATALHA ---\n\n");
    printf("O atacante %s rolou o dado e tirou: %d\n", mapa[*atacante - 1].nome, sorteio_atacante);
    printf("O defensor %s rolou o dado e tirou: %d\n", mapa[*defesa - 1].nome, sorteio_defesa);    
    
    if (sorteio_atacante > sorteio_defesa) {
        printf("\nVITÓRIA DO ATAQUE! O defensor %s perdeu 1 tropa.\n", mapa[*defesa - 1].nome);
        mapa[*defesa - 1].numero_tropas -= 1;
            if (mapa[*defesa - 1].numero_tropas <= 0) {
                printf("\nCONQUISTA! O território %s foi dominado pelo Exército %s!\n", mapa[*defesa - 1].nome, mapa[*atacante - 1].cor_exercito);
                // Atualiza o dono do território defensor para o atacante
                strcpy(mapa[*defesa - 1].cor_exercito, mapa[*atacante - 1].cor_exercito);
                mapa[*defesa - 1].numero_tropas = 1; // Move uma tropa para o território conquistado
                mapa[*atacante - 1].numero_tropas -= 1; // Remove uma tropa do território atacante
            }
    } else {
        printf("\nDEFESA BEM-SUCEDIDA! O atacante %s perdeu 1 tropa.\n", mapa[*atacante - 1].nome);
        mapa[*atacante - 1].numero_tropas -= 1;
        if (mapa[*atacante - 1].numero_tropas == 0) { 
            printf("\nCONQUISTA! O território %s foi dominado pelo Exército %s!\n", mapa[*atacante - 1].nome, mapa[*defesa - 1].cor_exercito);
            // Atualiza o dono do território atacante para o defensor
            strcpy(mapa[*atacante - 1].cor_exercito, mapa[*defesa - 1].cor_exercito);
            mapa[*atacante - 1].numero_tropas = 1; // Move uma tropa para o território conquistado
            mapa[*defesa - 1].numero_tropas -= 1; // Remove uma tropa do território defensor
        }
    }
    printf("\n");

    exibirMapa(mapa, *total_territorios);
    
    printf("\nPressione ENTER para continuar com o próximo round de ataque, ou 0 para SAIR...");
    fgets(continuar, sizeof(continuar), stdin);
        if (continuar[0] == '0') {
            printf("Saindo da fase de ataque.\n");
            break;  
        }
    } 
    free(atacante);
    free(defesa);  
}

    
// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
// 1. Configuração Inicial (Setup):

int main() {
    srand(time(NULL)); // Inicializa o gerador para números aleatórios com o tempo atual
    setlocale(LC_ALL, "pt_BR.UTF-8"); // - Define o locale para português.
    struct TERRITORIO *mapa; // Ponteiro para o vetor de territórios (mapa do jogo).
    int total_territorios = 0; // Número total de territórios no jogo.
    
    printf("\n==========================================================================\n");
    printf("Vamos cadastrar os territórios iniciais do nosso mundo.\n");
    printf("==========================================================================\n\n");
    printf("-------------------------------\n");

// INDICAR NÚMERO DE TERRITÓRIOS TOTAL
    int MAX_TERRITORIOS;
    printf("Indique o número de TERRITÓRIOS: ");
    scanf("%d", &MAX_TERRITORIOS);
    limparBufferEntrada(); // Limpa o buffer após ler um número

    mapa = (struct TERRITORIO *) malloc(MAX_TERRITORIOS * sizeof(struct TERRITORIO));

    if (mapa == NULL) {
        printf("Erro ao alocar memória para o mapa.\n");
        return 1; // Sai do programa em caso de erro de alocação
    }
    
// CADASTRAR TERRITÓRIOS
    cadastrar(mapa, MAX_TERRITORIOS, &total_territorios); 
    printf("\n");    

// exibir mapa cadastrado
    exibirMapa(mapa, total_territorios);  
    
    if (total_territorios == 0) {
        printf("====================================\n");
        printf("Nenhum território cadastrado. Encerrando o jogo.\n");
        printf("====================================\n");
        return 0;
    }

// Fase de ataque
 
    ataque(mapa, &total_territorios);
     
    // - Inicializa a semente para geração de números aleatórios com base no tempo atual.
    // - Aloca a memória para o mapa do mundo e verifica se a alocação foi bem-sucedida.
    // - Preenche os territórios com seus dados iniciais (tropas, donos, etc.).
    // - Define a cor do jogador e sorteia sua missão secreta.

    // 2. Laço Principal do Jogo (Game Loop):
    // - Roda em um loop 'do-while' que continua até o jogador sair (opção 0) ou vencer.
    // - A cada iteração, exibe o mapa, a missão e o menu de ações.
    // - Lê a escolha do jogador e usa um 'switch' para chamar a função apropriada:
    //   - Opção 1: Inicia a fase de ataque.
    //   - Opção 2: Verifica se a condição de vitória foi alcançada e informa o jogador.
    //   - Opção 0: Encerra o jogo.
    // - Pausa a execução para que o jogador possa ler os resultados antes da próxima rodada.

    // 3. Limpeza:
    // - Ao final do jogo, libera a memória alocada para o mapa para evitar vazamentos de memória.

    free(mapa); // Libera a memória alocada para o mapa
    
    
    
    printf("Pressione ENTER 2x para sair...");
    getchar();
    getchar();

    return 0;
}

// --- Implementação das Funções ---

// alocarMapa():
// Aloca dinamicamente a memória para o vetor de territórios usando calloc.
// Retorna um ponteiro para a memória alocada ou NULL em caso de falha.

// inicializarTerritorios():
// Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
// Esta função modifica o mapa passado por referência (ponteiro).

// liberarMemoria():
// Libera a memória previamente alocada para o mapa usando free.

// exibirMenuPrincipal():
// Imprime na tela o menu de ações disponíveis para o jogador.

// exibirMapa():
// Mostra o estado atual de todos os territórios no mapa, formatado como uma tabela.
// Usa 'const' para garantir que a função apenas leia os dados do mapa, sem modificá-los.

// exibirMissao():
// Exibe a descrição da missão atual do jogador com base no ID da missão sorteada.

// faseDeAtaque():
// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
// Chama a função simularAtaque() para executar a lógica da batalha.

// simularAtaque():
// Executa a lógica de uma batalha entre dois territórios.
// Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
// Se um território for conquistado, atualiza seu dono e move uma tropa.

// sortearMissao():
// Sorteia e retorna um ID de missão aleatório para o jogador.

// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.

// limparBufferEntrada():
// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.
