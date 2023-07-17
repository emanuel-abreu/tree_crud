#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no {
    int matricula;
    char nome[50];
    char curso[50];
    char email[50];
    char turma[50];
    float ano_ingresso;
    struct no* esq;
    struct no* dir;
} NO;

NO* raiz = NULL;

NO* busca_arvore(int x, NO* pt) {
    if (pt == NULL) {
        return NULL;
    } else if (x == pt->matricula) {
        return pt;
    } else if (x < pt->matricula) {
        if (pt->esq == NULL) {
            return pt;
        } else {
            return busca_arvore(x, pt->esq);
        }
    } else {
        if (pt->dir == NULL) {
            return pt;
        } else {
            return busca_arvore(x, pt->dir);
        }
    }
}

void buscar_aluno(int matricula) {
    NO* no = busca_arvore(matricula, raiz);
    if (no != NULL && no->matricula == matricula) {
        printf("\nDados do aluno:\n");
        printf("------------------------------------------------------------\n");
        printf("Matricula: %d\n", no->matricula);
        printf("Nome: %s\n", no->nome);
        printf("Curso: %s\n", no->curso);
        printf("Email: %s\n", no->email);
        printf("Turma: %s\n", no->turma);
        printf("Ano de Ingresso: %.1f\n", no->ano_ingresso);
        printf("------------------------------------------------------------\n");

        printf("\n");
    } else {
        printf("Aluno nao encontrado!\n");
    }
}

void insercao_aluno() {
    NO* pt = malloc(sizeof(NO));

    printf("\nDigite a matricula do aluno: ");
    scanf("%d", &pt->matricula);

    printf("\nDigite o nome do aluno: ");
    scanf(" %[^\n]", pt->nome);

    printf("\nDigite o curso do aluno: ");
    scanf(" %[^\n]", pt->curso);

    printf("\nDigite o email do aluno: ");
    scanf(" %[^\n]", pt->email);

    printf("\nDigite a turma do aluno: ");
    scanf(" %[^\n]", pt->turma);

    printf("\nDigite o ano de ingresso do aluno: ");
    scanf("%f", &pt->ano_ingresso);

    pt->esq = NULL;
    pt->dir = NULL;

    if (raiz == NULL) {
        raiz = pt;
    } else {
        NO* pai = busca_arvore(pt->matricula, raiz);

        if (pai->matricula == pt->matricula) {
            printf("Essa matricula ja existe, tente novamente!\n");
            free(pt);
        } else if (pt->matricula < pai->matricula) {
            pai->esq = pt;
        } else {
            pai->dir = pt;
        }
    }
    printf("\nAluno cadastrado com sucesso!\n");
}

NO* remocao_aluno(NO* pt, int valor) {
    if (pt == NULL)
        return NULL;
    else if (pt->matricula > valor)
        pt->esq = remocao_aluno(pt->esq, valor);
    else if (pt->matricula < valor)
        pt->dir = remocao_aluno(pt->dir, valor);
    else {
        if (pt->esq == NULL && pt->dir == NULL) {
            free(pt);
            pt = NULL;
        } else if (pt->esq == NULL) {
            NO* t = pt;
            pt = pt->dir;
            free(t);
        } else if (pt->dir == NULL) {
            NO* t = pt;
            pt = pt->esq;
            free(t);
        } else {
            NO* f = pt->esq;
            while (f->dir != NULL) {
                f = f->dir;
            }
            pt->matricula = f->matricula;
            strcpy(pt->nome, f->nome);
            strcpy(pt->curso, f->curso);
            strcpy(pt->email, f->email);
            strcpy(pt->turma, f->turma);
            pt->ano_ingresso = f->ano_ingresso;
            pt->esq = remocao_aluno(pt->esq, valor);
        }
    }
    printf("\nAluno removido com sucesso!\n");
    return pt;
}

void listagem_pre_ordem(NO* pt) {
    if (pt != NULL) {
        printf("------------------------------------------------------------\n");
        printf("Matricula: %d\n", pt->matricula);
        printf("Nome: %s\n", pt->nome);
        printf("Curso: %s\n", pt->curso);
        printf("Email: %s\n", pt->email);
        printf("Turma: %s\n", pt->turma);
        printf("Ano de Ingresso: %.1f\n", pt->ano_ingresso);
        printf("------------------------------------------------------------\n");

        if (pt->esq != NULL) {
            listagem_pre_ordem(pt->esq);
        }
        if (pt->dir != NULL) {
            listagem_pre_ordem(pt->dir);
        }
    } else {
        printf("------------------------------------------------------------\n");
        printf("Nenhum aluno cadastrado ainda\n");
        printf("------------------------------------------------------------\n");
    }
}

void atualizar_nome(NO* pt) {
    printf("Digite o novo nome do aluno: ");
    scanf(" %[^\n]", pt->nome);
    printf("Nome atualizado com sucesso!\n");
}

void atualizar_curso(NO* pt) {
    printf("Digite o novo curso do aluno: ");
    scanf(" %[^\n]", pt->curso);
    printf("Curso atualizado com sucesso!\n");
}

void atualizar_email(NO* pt) {
    printf("Digite o novo email do aluno: ");
    scanf(" %[^\n]", pt->email);
    printf("Email atualizado com sucesso!\n");
}

void atualizar_turma(NO* pt) {
    printf("Digite a nova turma do aluno: ");
    scanf(" %[^\n]", pt->turma);
    printf("Turma atualizada com sucesso!\n");
}

void atualizar_ano_ingresso(NO* pt) {
    printf("Digite o novo ano de ingresso do aluno: ");
    scanf("%f", &pt->ano_ingresso);
    printf("Ano de ingresso atualizado com sucesso!\n");
}

void atualizar_aluno(NO* pt) {
    int opcao;
    printf("Escolha o dado a ser atualizado:\n");
    printf("1. Nome\n");
    printf("2. Curso\n");
    printf("3. Email\n");
    printf("4. Turma\n");
    printf("5. Ano de Ingresso\n");
    printf("0. Cancelar\n");
    printf("Opcao: ");
    scanf("%d", &opcao);

    switch (opcao) {
        case 1:
            atualizar_nome(pt);
            break;
        case 2:
            atualizar_curso(pt);
            break;
        case 3:
            atualizar_email(pt);
            break;
        case 4:
            atualizar_turma(pt);
            break;
        case 5:
            atualizar_ano_ingresso(pt);
            break;
        case 0:
            printf("Operacao cancelada.\n");
            break;
        default:
            printf("Opcao invalida!\n");
    }
}

int main() {
    int opcao, matricula;

    do {
        printf("Menu:\n");
        printf("1. Inserir aluno\n");
        printf("2. Remover aluno\n");
        printf("3. Atualizar dados do aluno\n");
        printf("4. Listar alunos cadastrados\n");
        printf("5. Buscar aluno\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                insercao_aluno();
                break;
            case 2:
                printf("Digite a matricula do aluno a ser removido: ");
                scanf("%d", &matricula);
                raiz = remocao_aluno(raiz, matricula);
                break;
            case 3:
                printf("Digite a matricula do aluno: ");
                scanf("%d", &matricula);
                NO* no = busca_arvore(matricula, raiz);
                if (no != NULL && no->matricula == matricula) {
                    atualizar_aluno(no);
                } else {
                    printf("Aluno nao encontrado!\n");
                }
                break;
            case 4:
                printf("\nAlunos cadastrados, lista em pre-ordem:\n");
                listagem_pre_ordem(raiz);
                printf("\n");
                break;
            case 5:
                printf("Digite a matricula do aluno: ");
                scanf("%d", &matricula);
                buscar_aluno(matricula);
                break;
            case 0:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }

        printf("\n");

    } while (opcao != 0);

    return 0;
}
