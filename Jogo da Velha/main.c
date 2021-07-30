#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h> 

/*
*
* @author: Carlos Eduardo
* Jogo da Velha em C
*
*/

// Declara��o de um registro 
typedef struct {
	
	char nome[20];
	int simbolo;
	
}dados_jogadores;


void definicao_posicoes(int posicoes[3][3]);
void cadastro_jogadores(dados_jogadores *jogadores);
void preencher_tabuleiro_vizualizacao(int posicoes[3][3], char vizualizacao[3][3]);
int* posicao_tabuleiro(int posicao);
void tabuleiro(int tabuleiro_posi[3][3]);
int seleciona_posicao();
int jogada(int posicoes[3][3], int* posicao_jogada,dados_jogadores *dados,int jogador);
int posicao_valida(int posicoes[3][3], int* posi);
int verificacao_gahador(int posicoes[3][3]);

void limpar_buffer();
void limpa_tela();
void pause ();

int main() 
{
	setlocale (LC_ALL,"");
	
	int i,definicao_jogador=0, ganhou=0,numero_jogadas=0, jogada_valida;
	dados_jogadores jogadores[2];
	int tabuleiro_posi[3][3];
	char posicoes_tabuleiro[3][3];
	int posicao;
	int* posi=NULL;
	
	definicao_posicoes(tabuleiro_posi);	
	
	cadastro_jogadores (jogadores);

	srand(time(NULL));
	
	definicao_jogador = rand()%2;
	
	while ((ganhou != 1) && numero_jogadas < 9)
	{
		
		limpa_tela();
		printf ("\t\t\t\t\t\t    Vez de %s\n\n\n",jogadores[definicao_jogador].nome);
		tabuleiro(tabuleiro_posi);
		posicao = seleciona_posicao();
		posi = 	posicao_tabuleiro(posicao);	
		
		jogada_valida = jogada(tabuleiro_posi, posi,jogadores,definicao_jogador);
		preencher_tabuleiro_vizualizacao(tabuleiro_posi, posicoes_tabuleiro);
		
		// loop executará enquanto o jogador não digitar uma posição valida 
		while(jogada_valida != 1)
		{
			printf ("\n\t\t\t\t\t\t POSIÇÃO INVALIDA!\n");
			limpa_tela();
			printf ("\t\t\t\t\t\t    Vez de %s\n\n\n",jogadores[definicao_jogador].nome);
			tabuleiro(tabuleiro_posi);
			posicao = seleciona_posicao();
			posi = 	posicao_tabuleiro(posicao);
			
			jogada_valida = jogada(tabuleiro_posi, posi,jogadores,definicao_jogador);
			preencher_tabuleiro_vizualizacao(tabuleiro_posi, posicoes_tabuleiro);
		}	
			
		numero_jogadas++;
			
		ganhou = verificacao_gahador(tabuleiro_posi);
		
		// Teste que indicar a vez dos jogadores 
		if (definicao_jogador == 0 && ganhou != 1)
		{
				
			definicao_jogador++;
				
		}else if (ganhou != 1)
		{
				
			definicao_jogador--;
				
		}
		limpa_tela();
		
	}
		
	if (ganhou == 1)
	{
		printf ("\n\n\n\t\t\t\t\t\t   PARABÉNS %s\n\n", jogadores[definicao_jogador].nome);
		tabuleiro(tabuleiro_posi);
			
	}else 
	{
		
		printf ("\n\n\n\t\t\t\t\t\t       EMPATE!!\n\n\n");
		tabuleiro(tabuleiro_posi);	
	}

	pause();

	return 0;
}

// Declara todas as posições do tabuleiro com 0 (0 = livres)
void definicao_posicoes(int posicoes[3][3])
{
	
	for (int i=0;i<3;i++)
	{
		for (int j=0;j<3;j++)
		{ 
			posicoes[i][j] = 0;
		}
	}	
}

// Procediemnto que cadastra os jogadores da partida 
void cadastro_jogadores(dados_jogadores *jogadores)
{
	
	(jogadores + 0)->simbolo = 1;
	(jogadores + 1)->simbolo = 2;
	
	for (int i=0; i<2; i++)
	{
		
		printf ("Digite o nome do %d° jogador: ",i+1);
		fgets ((jogadores + i)->nome,20,stdin);
		
	}
}

// preenche a matriz com as teclas para selecionar a posição ou o simbolo de um jogador
void preencher_tabuleiro_vizualizacao(int posicoes[3][3], char vizualizacao[3][3])
{	

	int k=0;

	for (int i =0; i < 3; i++)
	{
		for (int j =0; j < 3; j++)
		{
			k++;
			vizualizacao[i][j] = '0'+k;
		}
	}

	for (int i =0; i < 3; i++)
	{
		for (int j =0; j < 3; j++)
		{	
			if (posicoes[i][j] == 1)
			{
				vizualizacao[i][j] = 'x';

			}
			else if (posicoes[i][j] == 2)
			{

				vizualizacao[i][j] = 'o';

			}	
		}
	}

}

// Exibe o tabuleiro para o usuário
void tabuleiro(int tabuleiro_posi[3][3])
{

	char posicoes[3][3];
	
	preencher_tabuleiro_vizualizacao(tabuleiro_posi, posicoes);
	
	printf ("\t\t\t\t\t          |              |           \n");
	printf ("\t\t\t\t\t     %c    |       %c      |	%c   \n",posicoes[0][0],posicoes[0][1],posicoes[0][2]);
	printf ("\t\t\t\t\t          |              |           \n");
	printf ("\t\t\t\t\t__________|______________|____________\n");
	printf ("\t\t\t\t\t          |              |           \n");
	printf ("\t\t\t\t\t     %c    |       %c      |	%c   \n",posicoes[1][0],posicoes[1][1],posicoes[1][2]);
	printf ("\t\t\t\t\t          |              |           \n");
	printf ("\t\t\t\t\t__________|______________|____________\n");
	printf ("\t\t\t\t\t          |              |           \n");
	printf ("\t\t\t\t\t          |              |           \n");
	printf ("\t\t\t\t\t     %c    |       %c      |	%c   \n",posicoes[2][0],posicoes[2][1],posicoes[2][2]);
	printf ("\t\t\t\t\t          |              |           \n");
	
}

// Captura a posição digitada e a retorna
// returna o numero exibido na tela refernte a posição escolhida
int seleciona_posicao()
{
	int jogada;

	printf ("\n\n\nDigite em qual casa você quer colocar a peça: ");
	scanf ("%d",&jogada);
	limpar_buffer();

	return jogada;
}

// Seta a posicao i e j num vetor
// returna um ponteiro para inteiro
int* posicao_tabuleiro(int posicao)
{
	int* posi = calloc(2,sizeof(posi));

	switch (posicao)
	{
		
		case 1:
			
			*(posi + 0) = 0;
			*(posi + 1) = 0;
			break;
			
		case 2:
			
			*(posi + 0) = 0;
			*(posi + 1) = 1;
			break;
		
		case 3:
			
			*(posi + 0) = 0;
			*(posi + 1) = 2;
			break;
		
		case 4:
			
			*(posi + 0) = 1;
			*(posi + 1) = 0;
			break;
		
		case 5:
			
			*(posi + 0) = 1;
			*(posi + 1) = 1;
			break;
		
		case 6:
			
			*(posi + 0) = 1;
			*(posi + 1) = 2;
			break;
		
		case 7:
			
			*(posi + 0) = 2;
			*(posi + 1) = 0;
			break;
		
		case 8:
			
			*(posi + 0) = 2;
			*(posi + 1) = 1;
			break;
		
		case 9:
			
			*(posi + 0) = 2;
			*(posi + 1) = 2;
			break;
		
		default:
			
			printf("\n\n\t\tPosicao invalida!!");
			break;	
	}

	return posi;

}

// Salva o simbolo conrespoindente ao usuário (x ou o)
// na matriz na posição digitada pelo usuário
// OBS: a funçãoo retorna se a posição digita é valida ou não 
int jogada(int posicoes[3][3], int* posicao_jogada,dados_jogadores *dados,int jogador)
{
	
	int opcao_valida, i = *(posicao_jogada + 0), j = *(posicao_jogada + 1), valida;
	
	// teste para saber se a posição é valida
	// se não for ela atribuir 10 a posicao_jogada 
	if (posicao_valida(posicoes,posicao_jogada) == 1)
	{
		posicoes[i][j] = (dados + jogador)->simbolo;
		opcao_valida = 1;
		
	}
	else
	{
		opcao_valida = 0;

	}
	
	pause ();
	
	return opcao_valida;
}

// Saber se na posição digitada já  está com um simbolo dentro
// Retornar 1 se a posição for valida e 0 se for invalida
int posicao_valida(int posicoes[3][3], int* posi)
{
	
	int i = *(posi + 0), j = *(posi + 1), valida;
	
	if (posicoes[i][j] == 0)
	{
		valida = 1;
	}
	else
	{
		valida = 0;

	}
	
	return valida;
	
}

// Verifica se existe algum ganhador
// Retornar 0 se não houver ganhador e 1 se houver 
int verificacao_gahador(int posicoes[3][3])
{
	
	int ganhou=0;
	
	for (int i=0; i<3; i++)
	{
		if (((posicoes[i][0] == posicoes[i][1]) && (posicoes[i][1] == posicoes[i][2])) && (posicoes[i][0] != 0))
		{
			
			ganhou = 1;	
		}
	}
	
	for (int i=0; i<3; i++)
	{
		if ((posicoes[0][i] == posicoes[1][i]) && (posicoes[1][i] == posicoes[2][i]) && (posicoes[0][i] != 0))
		{
			
			ganhou = 1;	
		}
	}
	
	if ((posicoes[0][0] == posicoes[1][1]) && (posicoes[1][1] == posicoes[2][2]) && (posicoes[0][0] != 0))
	{
			
		ganhou = 1;	
	}
	
	if ((posicoes[0][2] == posicoes[1][1]) && (posicoes[1][1] == posicoes[2][0]) && (posicoes[0][2] != 0))
	{
			
		ganhou = 1;		
	}

	return ganhou;
	
}

// Limpa o buffer do teclado
void limpar_buffer()
{
	
	char c;
	
	while ((c = getchar()) != '\n');
	
}

// Simula uma limpase de tela
void limpa_tela()
{

	printf ("\n\n\n\n");
	
	
}

// Pausa o sistema até o usuário digitar uma tecla
void pause ()
{
	
	printf ("\n\nPressione enter para continuar. . .");
	getchar();
	
}
