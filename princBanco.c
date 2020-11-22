#include<stdio.h>
#include<stdlib.h>
//Biblioteca LOCALE para pegar acentuações nas palavras ('`~ etc...)
#include<locale.h>
#include<conio.h>
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
//Nome precisou ser feito uma matriz para referenciar as strings em cada posição
char nome[numeroUSER][100] = {"Jonatas Bonfim","Larissa Sena","Isaias Rosa"};
int conta[numeroUSER] = {71000,71001,71002};
int agencia[numeroUSER] = {901,901,901};
float saldo[numeroUSER] = {1200,300,600};
int senha[numeroUSER] = {1234, 1234, 1234};

//inicialização das funções
int menu(int id_us);
int logar();
int cadastro();
void saque(int id_us);
void transferencia(int id_us);

//Variáveis para a função de cadastro
int cadastrados = 2;

//inicialização do programa.
int main(){
  //Leitura de acentuações
	setlocale(LC_ALL,"");
		//contador de tentativas
    int indice = 3;
    int tentativas = 0;
		//Variável para continuidade do saque (ou não)
    char res = 's';
    
    indice = -1;
		//enquanto não tiver feito 3 tentativas, faça
    while(tentativas < 3){
    	if(indice == -1){
				//início do programa
	    	indice = logar();
	    }
	    
			// IF abaixo servirá para a escolha das operações
			if( indice != -1){
	        switch(menu(indice)){
						//caso 1 para saquie
	        	case 1:
	        		while (res == 's'){
	        			saque(indice);
	        			printf("\nDeseja Realizar outro Saque? (s/n)");
								scanf("%c",&res);
	        			getch();
	        			res = getch();
					}
	        		break;
						//caso 2 para saldo
	        	case 2:
    				printf("\nSaldo: %.2f\n",saldo[indice]);
    				//system("PAUSE");
	        		break;

						//Caso 3 para Transferência
	        	case 3:
							//Por que o laço Do while? Para fazer primeiramente a transferência 
							//e DEPOIS perguntar se quer fazer mais alguma
	        		do{
								// Roda o subprograma transferência
	        			transferencia(indice);
								//Ao termino de rodar a transferência, faz a seguinte pergunta
	        			printf("\nDeseja Realizar outra Transferência? (s/n)");
								// função getch armazena o valor inserido [s/n] e o "res" armazena
	        			res = getch();
								//fez a repetição e confere o valor armazenado em "res" se for "s" repete
								//senão, termina (break)
					}while(res == 's');
	        		break;
	        	case 0:
	        		//escolha 0, faz a função para sair do programa, saindo ele retorna para o menu 
							//principal na linha 55, onde se indice = -1, faz a ação de logar.
							indice = -1;
	        		break;
	        	default:
							//caso a escolha não seja nenhuma das ofertadas no menu
	        		printf("\nEscolha incorreta!!!");
			}
	    }else{
					//mensagem de Erros
	        printf("\nConta ou Agência não cadastrados!!");
	        printf("\nRetornando ao menu principal!");
					//somatório para contador de tentativas
	        tentativas++;
	        if(tentativas == 2){
	        	printf("\nVocê só tem mais uma chance de logar no sistema.");
			}
	    }
	}
    return 0;
}

//Tela inicial de Logon
int logar(){
		//informações de login a ser inseridas, afim de validar se batem com 
		//as variáveis já cadastradas
    int contaLOG, agenciaLOG, senhaLOG;
    //var de cadastro para receber a resposta validada em caracter [s/n]
		char cadastrar;
    printf("\nSeja bem vindo ao sistema bancário!!!");
    printf("\nDeseja realizar um cadastro? [s/n]");
    // Função para pegar apenas a letra inserida em seguida da proposta acima
		getch();
		//cadastrar recebe a letra inserida
    cadastrar = getch();
		//validar se a resposta é sim ou não
		//se sim, faça, se não, segue o código
    if ( cadastrar == 's'){
      cadastro();
    }

		//inserção de dados da conta
    printf("\nDigite sua Conta:");
    scanf("%d", &contaLOG);
    printf("\nDigite sua Agência:");
    scanf("%d", &agenciaLOG);
    printf("\nDigite sua Senha:");
    scanf("%d", &senhaLOG);

		//Laço de repetição para validar o login inserido com usuários cadastrados
    for(int x=0; x<numeroUSER; x++){
				//para valor de x = 0, enquanto for menor que o número MÁXIMO de usuários cadastrados
				//faça a seguinte validação de dados
				//Agencia, conta e senha na posição do x tem que ser igual ao valor fornecido nessa vez
        if(agencia[x] == agenciaLOG && conta[x]==contaLOG && senha[x]==senhaLOG){
            return x;
        }
    }
    return -1;
}

//Menu pós entrada no logon
//id_us é um parametro para referenciar ao usuário ativo
int menu(int id_us){
	int escolha;
    printf("\n\nBem vindo %s!", nome[id_us]);
    printf("\nSuas Opções são:");
    printf("\n\t 1 - Saque");
    printf("\n\t 2 - Saldo");
    printf("\n\t 3 - Transferência");
    printf("\n\t 0 - Sair");
    printf("\nEscolha: ");
		//Ao executar o menu e escolher a devida opção, é inserido na variavel escolha
		// e é retornado o valor para a próxima etapa
    scanf("%d", &escolha);
		return escolha;
}


void transferencia(int id_us){
	//foi escolhida a variavel FLOAT para que seja possível inserir centavos na operação.
	float valor_tr = 0;
	//declarar dados da conta a receber o pagamento
	int conta_tr, agencia_tr, id_ustr;
	//Inserir variavel do erro
	int erro = 1;

	printf("\nDigite a Conta:");
    scanf("%d", &conta_tr);
    printf("\nDigite a Agência:");
    scanf("%d", &agencia_tr);
    printf("\nDigite o Valor:");
    scanf("%f", &valor_tr);

		//para valor de x = 0, enquanto for menor que o número MÁXIMO de usuários cadastrados
		//faça a seguinte validação de dados
		//Agencia, conta e senha na posição do x tem que ser igual ao valor fornecido nessa vez
    for(int y=0; y<numeroUSER; y++){
    	if(agencia[y] == agencia_tr && conta[y] == conta_tr){
    		//ID para referenciar o usuário  inserindo info incorreta, o ID é usado na linha 199
				//CASO realmente aconteça alguma incoerencia com as informaçoes inseridas
				id_ustr = y;
				//erro = 0 significa que não houve nenhum erro e o processo 
				//seguirá normalmente na linha 211
    		erro = 0;
		}
	}
	if(id_ustr == id_us){
		//variável de erro é realizado na linha 215, referente a agencia ou conta inválida
		erro = 1;
	}
	if(valor_tr>saldo[id_us]){
		//valor informado para transferir é maior que o saldo existente no usuário ativo.
		erro = 2;
	}
	switch(erro){
		case 0:
			//caso não tenha ocorrido erros, neste CASE é feito o 
			//decremento do saldo do usuário que está transferindo 
			//e incremento no usuário à receber
			
			saldo[id_us] -= valor_tr;
			saldo[id_ustr] += valor_tr;
			printf("\nTransferência realizada com Sucesso");
			printf("\nFavorecido: %s", nome[id_ustr]);
			printf("\nNo valor de R$ %.2f", valor_tr);
			break;
		case 1:
			printf("\nConta ou Agência inválida!!!");
			break;
		case 2:
			printf("\nSeu Saldo é insuficiente!!!");
			break;
	}
}

void saque(int id_us){
	//Escolhido tipo FLOAT para inserir centavos
	float valor_sq = 0;
	printf("\nDigite o Valor:");
    scanf("%f", &valor_sq);
	if(valor_sq>saldo[id_us]){
		printf("\nSeu Saldo é insuficiente!!!");
	}else{
		//decremento do saldo pelo valor de saque
		saldo[id_us] -= valor_sq;
	}

}

void deposito(int id_us){
	
	float valor_dp = 0;
	printf("\nDigite o Valor:");
    scanf("%f", &valor_dp);
	if(valor_sq>saldo[id_us]){
		printf("\nSeu Saldo é insuficiente!!!");
	}else{
		//decremento do saldo pelo valor de saque
		saldo[id_us] -= valor_sq;
	}

}

int cadastro(){
		//cadastrados possui o valor dos usuários JÁ cadastrados no código
		//a partir daqui, cadastrados incremeta +1 para definir a posição do usuário a ser
		//cadastrado.
    cadastrados++;
    
    char vlrInicial;
    char nvUsuario;
		//Limpar tela
    system("cls || clear");
    printf("Cadastro de um novo cliente\n");
    printf("Digite seu nome:");
    scanf("%s", &nome[cadastrados]);
    printf("\nDefina uma senha para o novo usuário");
    scanf("%d",&senha[cadastrados]);
		//feito a atribuição de valor dessa maneira para pegar o cadastrado 
		//anterior, e inserir um núemro a mais, assim mantendo controle entre cadastrados
		//Foi feito desse modo para não sobrescrever os valores já inseridos
    conta[cadastrados] = conta[cadastrados-1] + 1;
    agencia[cadastrados] = agencia[cadastrados-1] + 1;
    printf("Parabéns! Seu usuário foi cadastrado no nosso sistema!!\n");
    printf("O número de sua conta é %d\n",conta[cadastrados]);
    printf("O número de sua agencia é %d\n",agencia[cadastrados]);
    printf("Deseja depositar um valor inicial? [s/n]\n");
		//função getch para armazenar apenas a primeira letra inserida
    getch();
    vlrInicial = getch();
    if ( vlrInicial == 's' ){
      printf("Digite quanto você deseja depositar:");
      scanf("%f", &saldo[cadastrados]);
    }
    
    // printf("Digite o numero da agencia:");
    // scanf("%d",&agencia[cadastrados]);
    // printf("Digite o numero da conta:");
    // scanf("%d",&conta[count]);

    system("cls || clear");
    printf("Corretista cadastrado com sucesso !!!\n");
    do
    {

        printf("Cadastrar novo usuario ? [s/n]\n");
				//função getch para armazenar apenas uma letra
        getch();
				//nvusuario recebe o valor da função getch
        nvUsuario = getch();

        switch(nvUsuario)
        {
        case 's':
          return  cadastro();
            break;

        }
    }while(nvUsuario != 'n');
    return 1;
}