#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

//declaração da estrutura
typedef struct{
    int ID;
    char nome[20];
    char sexo[10];
    int pontuacao[2];
    int pont_total;
}Registro;

//declaração do escopo das funções
void adicionar_registro(Registro *aluno, int *ind_aluno);
void remove_registro(Registro *aluno, int *ind_aluno);
void atualizar_registro(Registro *aluno, int *ind_aluno);
void ver_todos_registros(Registro *aluno, int *ind_aluno);
void maior_nota(Registro *aluno, int *ind_aluno);
void menor_nota(Registro *aluno, int *ind_aluno);
void econtrar_ID(Registro *aluno, int *ind_aluno);
void ordenar_registros(Registro *aluno, int *ind_aluno);

int main(void) {
setlocale(LC_ALL, "Portuguese");

//alocando variavel do tipo da minha struct dinamicamente
Registro *aluno = malloc(0*sizeof(Registro));
int opcao=0, ind_aluno=0;

do{
    printf("\n\n----------------------------------------------\n");
    printf("                    MENU                        \n");
    printf("----------------------------------------------\n");
    printf("1. Adicionar registros de estudante\n");
    printf("2. Deletar registros de estudantes\n");
    printf("3. Atualizar registros de estudantes\n");
    printf("4. Ver registros de todos os estudantes\n");
    printf("5. Mostrar aluno com a maior nota\n");
    printf("6. Mostrar aluno com a menor nota\n");
    printf("7. Encontrar aluno por ID\n");
    printf("8. Ordenas os registros por pontuação total\n");
    printf("9. Sair\n");
    printf("Sua escolha: ");
    scanf("%d", &opcao);

    //switch de chamada das funções
    switch(opcao){
      case 1: //alocando o espaço para o vetor do tipo registro a cada novo registro
              aluno = (Registro *)realloc(aluno, (ind_aluno+1)*sizeof(Registro));
              adicionar_registro(aluno, &ind_aluno);
              ind_aluno++;
              break;
      case 2: remove_registro(aluno, &ind_aluno);
              break;
      case 3: atualizar_registro(aluno, &ind_aluno);
              break;
      case 4: ver_todos_registros(aluno, &ind_aluno);
              break;
      case 5: maior_nota(aluno, &ind_aluno);
              break;
      case 6: menor_nota(aluno, &ind_aluno);
              break;
      case 7: econtrar_ID(aluno, &ind_aluno);
              break;
      case 8: ordenar_registros(aluno, &ind_aluno);
              break;
      case 9: break;
      default: printf("\n\nAtenção: digite um dígito válido!\n\n");
    }
}while(opcao!=9);

return 0;
}

void adicionar_registro(Registro *aluno, int *ind_aluno){
  //adiciondo um novo registro
   /* Registro *tmp;
    tmp = realloc(aluno, (*ind_aluno+1)*sizeof(Registro));
    free(aluno);
    aluno = realloc(tmp, sizeof(tmp));
    free(tmp); */
    printf("\n\n|-------Adicionando um registro-------|");
    printf("\n   |ID do aluno: ");
    scanf("%d", &aluno[*ind_aluno].ID);
    printf("\n   |Nome do aluno: ");
    scanf("%s", aluno[*ind_aluno].nome);
    for(int i=0; i<2; i++){
        printf("\n   |Pontuação [%d]: ", i+1);
        scanf("%d", &aluno[*ind_aluno].pontuacao[i]);
        aluno[*ind_aluno].pont_total += aluno[*ind_aluno].pontuacao[i];
    }
    printf("\n   |Sexo: ");
    scanf("%s", aluno[*ind_aluno].sexo);

    printf("\n   Aluno cadastrado!\n");
}

void remove_registro(Registro *aluno, int *ind_aluno){
  //removendo um registro
  int remove_registro, aux=0, cont=0, ind_remove;

  printf("\n\n|-------------------Remover um registro------------------------|");
  if(*ind_aluno > 0){
    printf("\n   Digite o ID do aluno que você deseja apagar o registro: ");
    scanf("%d", &remove_registro);

    //descobrindo qual o registro deve ser removido
    for(int i=0; i<*ind_aluno; i++){
      if(remove_registro == aluno[i].ID){
        aux=1;
        ind_remove = i;
      }
      //contando quantos registros vao precisar ser realocados para frente
      if(aux==1) cont+=1;
    }

    if(aux==0) printf("\nNão existe aluno com esse ID!");
    else {
    //memmove(&aluno[ind_remove], &aluno[ind_remove+1], sizeof(Registro)*(cont-1));
    for(int i=ind_remove; i<cont-1; i++){
      aluno[i].ID = aluno[i+1].ID;
      aluno[i].pont_total = aluno[i+1].pont_total;
      for(int j=0; j<2; j++){
        aluno[i].pontuacao[j] = aluno[i+1].pontuacao[j];
      }
      strcpy(aluno[i].nome, aluno[i+1].nome);
      strcpy(aluno[i].sexo, aluno[i+1].sexo);
    }
      *ind_aluno = *ind_aluno - 1;
      aluno = (Registro *)realloc(aluno,(*ind_aluno)*sizeof(Registro));
    }
    }
  else printf("\n   Não há alunos registrados!\n");
}

void atualizar_registro(Registro *aluno, int *ind_aluno){
  int atualiza_registro=0, ind_atualiza=0, aux=0;

  printf("\n\n|------------------Atualizar um registro-----------------------|");
  if(*ind_aluno > 0){
    printf("\n  Digite o ID do aluno que você deseja atualizar o registro: ");
    scanf("%d", &atualiza_registro);

    for(int i=0; i<*ind_aluno; i++){
      if(atualiza_registro == aluno[i].ID){
        ind_atualiza = i;
        aux=1;
      }
    }

    if(aux){
      printf("\n|-------Adicionando um registro-------|");
      printf("\n   |ID do aluno: ");
      scanf("%d", &aluno[ind_atualiza].ID);
      printf("\n   |Nome do aluno: ");
      scanf("%s", aluno[ind_atualiza].nome);
      aluno[ind_atualiza].pont_total = 0;
      for(int i=0; i<2; i++){
          printf("\n   |Pontuação [%d]: ", i+1);
          scanf("%d", &aluno[ind_atualiza].pontuacao[i]);
          aluno[ind_atualiza].pont_total += aluno[ind_atualiza].pontuacao[i];
      }
      printf("\n   |Sexo: ");
      scanf("%s", aluno[ind_atualiza].sexo);
    }else printf("\n\n  Não há aluno associado a esse ID!");
  }else printf("\n\n  Não há alunos registrados!\n");
}

void ver_todos_registros(Registro *aluno, int *ind_aluno){
//se houver registros, o for mostrará todos os registrados
  printf("\n\n|-------Ver todos os registros-------|");
   if(*ind_aluno > 0){
    for(int i=0; i<*ind_aluno; i++){
      printf("\n   |Aluno: %s", aluno[i].nome);
      printf("\n   |ID: %d", aluno[i].ID);
      printf("\n   |Sexo: %s", aluno[i].sexo);
      for(int j=0; j<2; j++){
        printf("\n   |Pontuacao do %dº teste: %d", j+1, aluno[i].pontuacao[j]);
      }
      printf("\n   |Pontuação Total: %d", aluno[i].pont_total);
    }
     printf("\n\n");
   }
  else{
    printf("\n   Não há alunos registrados!\n");
  }
}

void maior_nota(Registro *aluno, int *ind_aluno){
  printf("\n\n|------------Aluno com a maior nota------------|");
   if(*ind_aluno > 0){
      int maior_nota = aluno[0].pont_total, ind_maior_nota = 0;
      for(int i=0; i<*ind_aluno; i++){
        if(aluno[i].pont_total > maior_nota){
          maior_nota = aluno[i].pont_total;
          ind_maior_nota = i;
        }
      }
    printf("\n   |Aluno com a maior nota total: %s", aluno[ind_maior_nota].nome);
    printf("\n   |Nota total do aluno: %d", aluno[ind_maior_nota].pont_total);
   }else{
     printf("\n   |Não há alunos registrados!\n");
   }
}

void menor_nota(Registro *aluno, int *ind_aluno){
  printf("\n\n|------------Aluno com a menor nota------------|");
   if(*ind_aluno > 0){
      int menor_nota = aluno[0].pont_total, ind_menor_nota = 0;
      for(int i=0; i<*ind_aluno; i++){
        if(aluno[i].pont_total < menor_nota){
          menor_nota = aluno[i].pont_total;
          ind_menor_nota = i;
        }
      }
    printf("\n   |Aluno com a menor nota total: %s", aluno[ind_menor_nota].nome);
    printf("\n   |Nota total do aluno: %d", aluno[ind_menor_nota].pont_total);
   }else{
     printf("\n   |Não há alunos registrados!\n");
   }
}

void econtrar_ID(Registro *aluno, int *ind_aluno){
  printf("\n\n|-------------Encontrar aluno por ID-----------------|");
    if(*ind_aluno > 0){
    int encontra_ID, ind_ID=0, aux=0;
    printf("\n  Digite o ID do aluno que você deseja encontrar: ");
    scanf("%d", &encontra_ID);

    for(int i=0; i<*ind_aluno; i++){
        if(encontra_ID == aluno[i].ID){
          ind_ID = i;
          aux = 1;
        }
    }
    if(aux){
      printf("\n   |Aluno: %s", aluno[ind_ID].nome);
      printf("\n   |ID: %d", aluno[ind_ID].ID);
      printf("\n   |Sexo: %s", aluno[ind_ID].sexo);
      for(int j=0; j<2; j++){
       printf("\n   |Pontuacao do %dº teste: %d", j+1, aluno[ind_ID].pontuacao[j]);
      }
      printf("\n   |Pontuação Total: %d", aluno[ind_ID].pont_total);
    }else printf("\n   Não há aluno associado a esse ID!");
  }else printf("\n   Não há alunos registrados!\n");
}

void ordenar_registros(Registro *aluno, int *ind_aluno){
  printf("\n\n|-------Registros ordenados por maior nota-------|");
   if(*ind_aluno > 0){
      int maior_nota = aluno[0].pont_total, ind_maior_nota = 0;
      int aux=0, ta_usado=0;
      //alocando dinamicamente o vetor que guardara a
      //ordem decrescente de notas
      int * ind_usado = (int*) malloc(0*sizeof(int));
      ind_usado = (int*) realloc(ind_usado, (*ind_aluno)*sizeof(int));

     //enquanto todos os indices não forem ordanos, faça
     do{
      //procurando a maior nota
      for(int i=0; i<*ind_aluno; i++){
        if(aluno[i].pont_total > maior_nota){
          //checando se esse indice já não foi ordenado
          for(int k=0; k<aux; k++){
             if(i == ind_usado[k]){
               ta_usado = 1;
             }
            }
          //caso não tenha sido ordenado,
          //pegamos o elemento seguinte da ordenação
            if(ta_usado == 0){
            maior_nota = aluno[i].pont_total;
            ind_maior_nota = i;
            }
          }
        ta_usado=0;
      }
      //inserindo o indice referente ao aluno com a maior nota
      //possivel depois dos já ordenados
      ind_usado[aux++] = ind_maior_nota;
      maior_nota =0;
     }while (aux < *ind_aluno);

       //imprimindo em ordem os alunos com as maiores notas
       for(int j=0; j<aux; j++){
        printf("\n   |Aluno: %s", aluno[ind_usado[j]].nome);
        printf("\n   |ID: %d", aluno[ind_usado[j]].ID);
        printf("\n   |Sexo: %s", aluno[ind_usado[j]].sexo);
        for(int k=0; k<2; k++){
          printf("\n   |Pontuacao do %dº teste: %d", k+1, aluno[ind_usado[j]].pontuacao[k]);
        }
        printf("\n   |Pontuação Total: %d", aluno[ind_usado[j]].pont_total);
        printf("\n");
    }
     printf("\n\n");

     }else printf("\n   Não há alunos registrados!\n");
}
