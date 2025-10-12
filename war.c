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

// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.
#define MAX_TERRITORIOS 5
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
//Função para limpar o buffer de entrada
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
int main() {
    struct TERRITORIO mapa[MAX_TERRITORIOS]; // Ponteiro para o vetor de territórios (mapa do jogo).
    int total_territorios = 0; // Número total de territórios no jogo.
    
    printf("\n==========================================================================\n");
    printf("Vamos cadastrar os 05 territórios iniciais do nosso mundo.\n");
    printf("==========================================================================\n\n");
    printf("-------------------------------\n");
    while (total_territorios <= MAX_TERRITORIOS)
    {
    if (total_territorios < MAX_TERRITORIOS) {
        
        printf("\n--- Cadastro do território %d ---\n", total_territorios + 1);
        printf("Digite o nome do território: ");
        fgets(mapa[total_territorios].nome, TAM_STRING, stdin);

        printf("Digite a cor do exército: ");
        fgets(mapa[total_territorios].cor_exercito, TAM_STRING, stdin);

        printf("Digite o número de tropas: ");
        scanf("%d", &mapa[total_territorios].numero_tropas);
        limparBufferEntrada(); // Limpa o buffer após ler um número
        

        // Remove a nova linha lida pelo fgets
        mapa[total_territorios].nome[strcspn(mapa[total_territorios].nome, "\n")] = 0;
        mapa[total_territorios].cor_exercito[strcspn(mapa[total_territorios].cor_exercito, "\n")] = 0;

        total_territorios++;
    } else {
        printf("\n\n-------------------------------\n");
        printf("Cadastro inicial concluído.\n");
        printf("-------------------------------\n\n");
        break;  
    }}

    if (total_territorios == 0) {
        printf("====================================\n");
        printf("Nenhum território cadastrado. Encerrando o jogo.\n");
        printf("====================================\n");
        return 0;
    }else {
        printf("====================================\n");
        printf("  MAPA DO MUNDO - ESTADO ATUAL\n");
        printf("====================================\n\n");
        for (int i = 0; i < total_territorios; i++) {
            printf("TERRITÓRIO %d\n", i + 1);
            printf("  - Nome: %s\n", mapa[i].nome); 
            printf("  - Dominado por: Exército %s\n", mapa[i].cor_exercito);
            printf("  - Tropas: %d\n\n", mapa[i].numero_tropas);
             
                   
        } printf("------------ FIM ----------------\n");
    }
    
    // 1. Configuração Inicial (Setup):
    // - Define o locale para português.
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
