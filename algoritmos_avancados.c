#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Desafio Detective Quest
// Tema 4 - Árvores e Tabela Hash
// Este código inicial serve como base para o desenvolvimento das estruturas de navegação, pistas e suspeitos.
// Use as instruções de cada região para desenvolver o sistema completo com árvore binária, árvore de busca e tabela hash.

// Tamanho máximo para o nome da sala
#define MAX_NOME 50

// Estrutura do Nó (Cômodo)
typedef struct Sala {
    char nome[MAX_NOME];
    struct Sala *esquerda; // Caminho 'e'
    struct Sala *direita;  // Caminho 'd'
} Sala;


Sala* criarSala(const char* nome) {
    // Aloca memória para a nova sala
    Sala* novaSala = (Sala*)malloc(sizeof(Sala));
    
    // Verifica se a alocação foi bem-sucedida
    if (novaSala == NULL) {
        perror("Erro ao alocar memória para a sala");
        exit(EXIT_FAILURE);
    }
    
    // Copia o nome para a estrutura
    strncpy(novaSala->nome, nome, MAX_NOME - 1);
    novaSala->nome[MAX_NOME - 1] = '\0'; // Garante terminação nula
    
    // Inicializa os ponteiros dos filhos como NULL (sem caminhos)
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;
    
    return novaSala;
}

void explorarMansao(Sala* hall) {
    Sala* atual = hall;
    char escolha;
    
    printf("\n--- 🕵️ Detetive Quest: Explorando a Mansão 🕵️ ---\n");
    printf("Você está no %s.\n", atual->nome);

    // Loop de exploração: continua enquanto houver caminhos
    while (atual != NULL) {
        // Se for um nó-folha (não tem caminhos à esquerda nem à direita)
        if (atual->esquerda == NULL && atual->direita == NULL) {
            printf("\n🎉 Você chegou a um beco sem saída: %s!\n", atual->nome);
            printf("A exploração terminou.\n");
            break; // Sai do loop (fim da jornada)
        }

        // Exibe os caminhos disponíveis
        printf("\nCaminhos disponíveis:\n");
        if (atual->esquerda != NULL) {
            printf("  (e) Esquerda -> Próximo: %s\n", atual->esquerda->nome);
        }
        if (atual->direita != NULL) {
            printf("  (d) Direita -> Próximo: %s\n", atual->direita->nome);
        }
        
        // Solicita a escolha do jogador
        printf("Para onde deseja ir ('e' ou 'd')? ");
        
        // Loop para garantir uma entrada válida
        while (scanf(" %c", &escolha) != 1 || (escolha != 'e' && escolha != 'd')) {
            printf("Escolha inválida. Digite 'e' para Esquerda ou 'd' para Direita: ");
            // Limpa o buffer de entrada para evitar loops infinitos
            while (getchar() != '\n');
        }
        
        // Processa a escolha e avança
        Sala* proximo = NULL;
        if (escolha == 'e' && atual->esquerda != NULL) {
            proximo = atual->esquerda;
        } else if (escolha == 'd' && atual->direita != NULL) {
            proximo = atual->direita;
        } else {
            // Caso o caminho escolhido não exista (o que não deve ocorrer se a 
            // verificação do while(atual != NULL) estiver correta, mas é uma segurança)
            printf("Não há caminho nessa direção. Tente novamente.\n");
            continue;
        }

        // Atualiza a posição e exibe a próxima sala
        atual = proximo;
        printf("\n-> Você entrou no %s.\n", atual->nome);
    }
}

void liberarMansao(Sala* raiz) {
    if (raiz != NULL) {
        // Libera recursivamente as sub-árvores
        liberarMansao(raiz->esquerda);
        liberarMansao(raiz->direita);
        
        // Libera o nó atual
        free(raiz);
    }
}

int main() {

    // 🌱 Nível Novato: Mapa da Mansão com Árvore Binária
    //
    // - Crie uma struct Sala com nome, e dois ponteiros: esquerda e direita.
    // - Use funções como criarSala(), conectarSalas() e explorarSalas().
    // - A árvore pode ser fixa: Hall de Entrada, Biblioteca, Cozinha, Sótão etc.
    // - O jogador deve poder explorar indo à esquerda (e) ou à direita (d).
    // - Finalize a exploração com uma opção de saída (s).
    // - Exiba o nome da sala a cada movimento.
    // - Use recursão ou laços para caminhar pela árvore.
    // - Nenhuma inserção dinâmica é necessária neste nível.

    // Nível 0: Raiz
    Sala *hall = criarSala("Hall de Entrada");

    // Nível 1
    hall->esquerda = criarSala("Sala de Estar");
    hall->direita = criarSala("Corredor Principal");

    // Nível 2
    hall->esquerda->esquerda = criarSala("Cozinha");
    hall->esquerda->direita = criarSala("Jardim"); 
    
    hall->direita->esquerda = criarSala("Escritório");
    hall->direita->direita = criarSala("Biblioteca");

    // Nível 3 (Nós-folha, onde a exploração termina)
    hall->direita->esquerda->esquerda = criarSala("Quarto de Hóspedes"); // Folha
    hall->direita->esquerda->direita = criarSala("Despensa"); // Folha

    // Note que "Cozinha", "Jardim" e "Biblioteca" são nós-folha por padrão
    // pois não foram atribuídos filhos a eles.

    // 2. Permitir a Exploração Interativa
    explorarMansao(hall);
    
    // 3. Libera a memória alocada
    liberarMansao(hall);

    // 🔍 Nível Aventureiro: Armazenamento de Pistas com Árvore de Busca
    //
    // - Crie uma struct Pista com campo texto (string).
    // - Crie uma árvore binária de busca (BST) para inserir as pistas coletadas.
    // - Ao visitar salas específicas, adicione pistas automaticamente com inserirBST().
    // - Implemente uma função para exibir as pistas em ordem alfabética (emOrdem()).
    // - Utilize alocação dinâmica e comparação de strings (strcmp) para organizar.
    // - Não precisa remover ou balancear a árvore.
    // - Use funções para modularizar: inserirPista(), listarPistas().
    // - A árvore de pistas deve ser exibida quando o jogador quiser revisar evidências.

    // 🧠 Nível Mestre: Relacionamento de Pistas com Suspeitos via Hash
    //
    // - Crie uma struct Suspeito contendo nome e lista de pistas associadas.
    // - Crie uma tabela hash (ex: array de ponteiros para listas encadeadas).
    // - A chave pode ser o nome do suspeito ou derivada das pistas.
    // - Implemente uma função inserirHash(pista, suspeito) para registrar relações.
    // - Crie uma função para mostrar todos os suspeitos e suas respectivas pistas.
    // - Adicione um contador para saber qual suspeito foi mais citado.
    // - Exiba ao final o “suspeito mais provável” baseado nas pistas coletadas.
    // - Para hashing simples, pode usar soma dos valores ASCII do nome ou primeira letra.
    // - Em caso de colisão, use lista encadeada para tratar.
    // - Modularize com funções como inicializarHash(), buscarSuspeito(), listarAssociacoes().

    return 0;
}

