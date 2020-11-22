#include <stdio.h>
#include <stdlib.h>
//Biblioteca para pegar acentuações
#include <locale.h>
// Biblioteca para utilizar funções específicas, no caso deste código
// a função "getch"
#include <conio.h>

/*
Alunos: 

Alan Silva         161031151
Bruno Santos       181050356
Felipe Nascimento  191051408
Isaías Rosa        1920530514
Lucas Santos       182051751
Jônatas Bonfim     2010534842
Larissa Sena       182051436
Maria Eugênia      191050610
Weverson Magalhães 151030399

*/

// Constante para que todas as variaveis delimitadoras sejam fáceis de manusear
#define numeroUSER 100

// Variaveis dos usuários separadas por posições
// A Variável "Nome" precisou ser feito uma matriz para referenciar as strings em cada posição,
// exemplo: na COLUNA 0 temos a string "Jonatas Bonfim", e assim por diante
char nome[numeroUSER][100] = {"Jonatas Bonfim", "Larissa Sena", "Isaias Rosa"};
int conta[numeroUSER] = {71000, 71001, 71002};
int agencia[numeroUSER] = {901, 901, 901};
float saldo[numeroUSER] = {1200, 300, 600};
int senha[numeroUSER] = {1234, 1234, 1234};

//inicialização das funções
int menu(int id_us);
int logar();
int cadastro();
void saque(int id_us);
void transferencia(int id_us);
void deposito(int id_us);

//Variáveis para a função de cadastro
int cadastrados = 2;

//Variável para correção do erro na opção de sair, informando
//erro de conta ou senha incorreta junto, causado pela linha 150
int erroSair = 0;

//Variavel para não aparecer bem vindo toda hora, se for 1, ele já entrou
//nesse caso, não precisa aparecer "Bem Vindo" novamente.
int entradaOk = 0;

//inicialização do programa.
int main()
{
  //Leitura de acentuações (' ` ~ ^)
  setlocale(LC_ALL, "");
  //controlador de ações do menu, se for -1 ele faz o logon,
  //se for diferente de -1, ele pegou o return de logon e fará a opção correspondente no menu
  int indice = -1;
  //contador de tentativas
  int tentativas = 0;
  //Variável para continuidade do saque (ou não)
  char res = 's';

  while (tentativas < 3)
  {
    if (indice == -1)
    {
      indice = logar();
    }
    if (indice != -1)
    {
      switch (menu(indice))
      {
      case 1:

        saque(indice);
        // Estrutura de repetição FAÇA
        do
        {
          printf("\nDeseja Realizar outro Saque? (s/n)");
          // Função getch Reserva apenas a primeira letra inserida
          getch();
          // variável "res" assume a letra reservada em getch
          res = getch();
          system("cls || clear");
          if (res == 's')
          {
            saque(indice);
          }
        } while (res != 'n');

        break;
      case 2:
        printf("\nSaldo: %.2f\n", saldo[indice]);
        entradaOk = 1;
        //system("PAUSE");
        break;
      case 3:

        transferencia(indice);
        // Estrutura de repetição FAÇA
        do
        {

          printf("\nDeseja Realizar outra Transferência? (s/n)");
          // Reserva apenas a primeira letra inserida
          getch();
          // variável "res" assume a letra inserida
          res = getch();
          system("cls || clear");
          if (res == 's')
          {
            transferencia(indice);
          } //CORRIGIDO ERRO AO TRANSFERIR NOVAMENTE
        } while (res != 'n');
        break;
      case 4:
        deposito(indice);
        // Estrutura de repetição FAÇA
        do
        {

          printf("Deseja depositar novamente? [s/n]\n");
          // Reserva apenas a primeira letra inserida
          getch();
          // variável "res" assume a letra inserida
          res = getch();
          system("cls || clear");
          if (res == 's')
          {
            deposito(indice);
          } //CORRIGIDO ERRO AO DEPOSITAR NOVAMENTE
        } while (res != 'n');
        break;
      case 5:
        //Finaliza o programa retornando "false" ao int main
        return 0;
        break;

      case 0:
        indice = -1; //indice -1 é verificado na linha 66 para procedencia de logon
        entradaOk = 0;
        break;
      default:
        printf("\nEscolha incorreta!!!");
      }
    }
    else
    {
      //system("clear || CLS");
      if (erroSair == 0)
      {
        printf("\nConta ou Agência não cadastrados!!");
        printf("\nRetornando ao menu principal!");
        tentativas++;
        if (tentativas == 2)
        {
          printf("\nVocê só tem mais uma chance de logar no sistema.");
        }
      }
    }
  }
  return 0; //Finaliza o programa retornando "false" ao int main
}

//Tela inicial de Logon
int logar()
{
  int contaLOG, agenciaLOG, senhaLOG; //variaveis para leitura de informações de login
  char cadastrar = 'n', sair;
  //system("clear");
  printf("\nSeja bem vindo ao sistema bancário!!!");

  printf("\nDeseja realizar um cadastro? [s/n]");
  getch();
  cadastrar = getch();
  system("cls || clear"); //Limpar tela pelo sistema tanto no linux quanto no windows
  if (cadastrar == 's')
  {
    cadastro();
  }
  else if (cadastrar != 'n')
  {
    system("cls || clear");
    printf("\nVocê digitou uma opção inválida, estaremos retornando ao menu inicial !\n");
    logar(); //a função de logar é refeita
  }

  //Opção para sair da simulação
  printf("\nDeseja sair da aplicação? [s/n]");
  getch();
  sair = getch();
  system("cls || clear");
  if (sair == 's')
  {
    return 0; //Finaliza o programa retornando "false" ao int main
  }
  else if (sair != 'n')
  {
    system("cls || clear");
    printf("\nVocê digitou uma opção inválida, estaremos retornando ao menu inicial !\n");
    erroSair = 1;
    return -1;
  }
  //#DONE Erro ainda, possivelmente não é de lógica
  //Ter que inserir os dados da conta 2 vezes ou errar 1 vez para conseguir entrar

  printf("\nDigite sua Conta:");
  scanf("%d", &contaLOG);
  printf("\nDigite sua Agência:");
  scanf("%d", &agenciaLOG);
  printf("\nDigite sua Senha:");
  scanf("%d", &senhaLOG);
  system("cls || clear");

  //Laço de repetição para validar o login inserido com algum dos usuários já cadastrados
  for (int x = 0; x < numeroUSER; x++)
  {
    if (agencia[x] == agenciaLOG && conta[x] == contaLOG && senha[x] == senhaLOG)
    {
      return x;
    }
  }
  return -1; //indice -1 é verificado na linha 66 para procedencia de logon
}

//Menu pós logon
//id_us serve para referenciar o usuário logado
int menu(int id_us)
{
  int escolha;
  //system("clear");
  // \n = pular linha | \t = espaçamento
  if (entradaOk == 1)
  {
    printf("\nOlá %s!", nome[id_us]);
    printf("\nSuas Opções são:");
    printf("\n\t 1 - Saque");
    printf("\n\t 2 - Saldo");
    printf("\n\t 3 - Transferência");
    printf("\n\t 4 - Deposito");
    printf("\n\t 5 - Sair do sistema");
    printf("\n\t 0 - Sair da sua conta");
    printf("\nEscolha: ");
    scanf("%d", &escolha);
    system("cls || clear");
    return escolha;
  }
  else if (entradaOk == 0)
  {
    printf("\nBem vindo %s!", nome[id_us]);
    printf("\nSuas Opções são:");
    printf("\n\t 1 - Saque");
    printf("\n\t 2 - Saldo");
    printf("\n\t 3 - Transferência");
    printf("\n\t 4 - Deposito");
    printf("\n\t 5 - Sair do sistema");
    printf("\n\t 0 - Sair da sua conta");
    printf("\nEscolha: ");
    scanf("%d", &escolha);
    system("cls || clear");
    return escolha;
  }
}

void transferencia(int id_us) //id_us serve para referenciar o usuário logado
{
  float valor_tr = 0;
  int conta_tr, agencia_tr, id_ustr;
  int erro = 1;

  printf("\n\tTRANSFERÊNCIA\n");
  printf("\nDigite a Conta:");
  scanf("%d", &conta_tr);
  printf("\nDigite a Agência:");
  scanf("%d", &agencia_tr);
  printf("\nDigite o Valor:");
  scanf("%f", &valor_tr);

  for (int y = 0; y < numeroUSER; y++)
  {
    if (agencia[y] == agencia_tr && conta[y] == conta_tr)
    {
      //id referenciando o usuário a ser beneficiado com a transferência
      id_ustr = y;
      erro = 0;
    }
  }
  if (id_ustr == id_us)
  {
    erro = 1;
  }
  if (valor_tr > saldo[id_us])
  {
    erro = 2;
  }
  switch (erro)
  {
  case 0:
    saldo[id_us] -= valor_tr;
    saldo[id_ustr] += valor_tr;
    printf("\nTransferência realizada com Sucesso");
    printf("\nFavorecido(a): %s", nome[id_ustr]); //id_ustr refere ao usuário beneficiado com a transferencia
    printf("\nNo valor de R$ %.2f", valor_tr);
    entradaOk = 1;
    break;
  case 1:
    printf("\nConta ou Agência inválida!!!");
    break;
  case 2:
    printf("\nSeu Saldo é insuficiente!!!");
    break;
  }
}

void saque(int id_us) //id_us serve para referenciar o usuário logado
{
  float valor_sq = 0;
  printf("\n\tSAQUE\n");
  printf("\nDigite o Valor:");
  scanf("%f", &valor_sq);
  if (valor_sq > saldo[id_us])
  {
    printf("\nSeu Saldo é insuficiente!!!");
  }
  else
  {
    saldo[id_us] -= valor_sq;
    entradaOk = 1;
  }
}

void deposito(int id_us) //id_us serve para referenciar o usuário logado
{
  float valor_dp = 0;
  printf("\n\tDEPÓSITO\n");
  printf("\nDigite o Valor:");
  scanf("%f", &valor_dp);
  if (valor_dp <= 0)
  {
    printf("\nVocê digitou um valor inválido!!!");
  }
  else
  {
    saldo[id_us] += valor_dp;
    entradaOk = 1;
  }
}

int cadastro()
{
  cadastrados++;
  char vlrInicial = 'n';
  char nvUsuario;

  system("cls || clear");
  printf("\n\tCADASTRO\n");
  printf("Digite seu nome: ");
  scanf("%s", &nome[cadastrados]);
  printf("\nDefina uma senha para o novo usuário: ");
  scanf("%d", &senha[cadastrados]);
  conta[cadastrados] = conta[cadastrados - 1] + 1;     //soma o valor da conta anterior + 1 sempre que for necessário
  agencia[cadastrados] = agencia[cadastrados - 1] + 1; //soma o valor da agencia anterior + 1 sempre que for necessário

  printf("Parabéns! Seu usuário foi cadastrado no nosso sistema!!\n");
  printf("O número de sua conta é %d\n", conta[cadastrados]);     //informa a conta referente a posição atual do cadastro
  printf("O número de sua agencia é %d\n", agencia[cadastrados]); //informa a agencia referente a posição atual do cadastro

  printf("Deseja depositar um valor inicial? [s/n]\n");
  getch();
  vlrInicial = getch();
  if (vlrInicial == 's')
  {
    system("cls || clear");
    printf("Digite quanto você deseja depositar:");
    scanf("%f", &saldo[cadastrados]);
    printf("Corretista cadastrado com sucesso !!!\n");
  }
  else if (vlrInicial != 'n')
  {
    system("cls || clear");
    printf("Você digitou uma opção inválida!\n");
    printf("Mas poderá depositar um valor ao entrar na conta!\n");
  }
  do
  {
    printf("Cadastrar novo usuario ? [s/n]\n");
    getch();
    nvUsuario = getch();
    //system("cls || clear");
    if (nvUsuario == 's')
    {
      cadastro();
    }
    else if (nvUsuario != 'n')
    {
      printf("Você digitou uma opção inválida!\n");
    }

  } while (nvUsuario != 'n');
  //system("cls || clear");
  return 1;
}