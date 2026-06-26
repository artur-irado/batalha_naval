#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

//Variaveis Globais

const int MAX_TABULEIRO = 10;
int ataque_linha; //coordenada que voce insire pra atacar (linha, a..b...c) em forma de inteiro
int ataque_coluna; //coordenada que voce insire atacar (coluna)
int comprimento[3] = {2,3,4}; // diferentes comprimentos armazenados
int direcao; //variavel 1 para horizontal e 0 para vertical 
int linha, coluna; //variaveis para determinar a linha e coluna em que o navio gerado aleatoriamente vai ser posicionado
int numero_navios = 0, tipo, contagem;
int tamanho_tabuleiro = 1;
char alfabeto[10] = {'A','B','C','D','E','F','G','H','I','J'};
char ataque_linha_char; //coordenada que voce insire pra atacar (linha, a..b...c) em forma de char
char char_do_navio[3] = {'D', 'C', 'P'};
char tabuleiro_ataque[MAX_TABULEIRO][MAX_TABULEIRO] = {'~'};
char tabuleiro_nosso[MAX_TABULEIRO][MAX_TABULEIRO] = {'~'}; // tabuleiro char, '~' representa as ondinhas
bool posicao_valida = true; //variavel pra reinicar o ciclo de posicionamento de navios se a posiçao não for válida
string nome_do_navio[3] = {"Destroier", "Cruzador", "Porta-Aviao"};

void gerar_tabuleiro(){
    cout << endl;
    for(int i=0; i < tamanho_tabuleiro; i++){   // Gera a Matriz do tabuleiro
        for (int j=0; j < tamanho_tabuleiro; j++){
            tabuleiro_nosso[i][j] = '~';
        }
    }

}



void gerar_tabuleiro_ataque(){
    cout << endl;
    for(int i=0; i < tamanho_tabuleiro; i++){   // Gera a Matriz do tabuleiro
    for (int j=0; j < tamanho_tabuleiro; j++){
        tabuleiro_ataque[i][j] = '~';
        }
    }

}

void imprimir_tabuleiros(){

    cout << "  "; 
    for(int j = 0; j < tamanho_tabuleiro; j++){ //imprime os numeros encima do tabuleiro
        cout << j << " ";
    }
    cout << "\t\t";
    cout << "  ";
    for(int j = 0; j < tamanho_tabuleiro; j++){ //imprime os numeros encima do tabuleiro
        cout << j << " ";
    }
    cout << endl;
    
    for(int i = 0; i < tamanho_tabuleiro; i++){   // Imprime a Matriz do tabuleiro
        cout << alfabeto[i] << " "; //imprime as letras do lado do tabuleiro
        for (int j=0; j < tamanho_tabuleiro; j++){
            cout << tabuleiro_nosso[i][j] << " ";
        }
        cout << "\t\t"; 
        cout << alfabeto[i] << " "; //imprime as letras do lado do tabuleiro
        for (int j=0; j < tamanho_tabuleiro; j++){
            cout << tabuleiro_ataque[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl << "Digite as cordenadas de ataque: ";
    cin >> ataque_linha_char >> ataque_coluna;
}

void seu_ataque(){
    ataque_linha = ataque_linha_char - 65; //converte a coordenada da linah em forma de letra pra numero inteiro
    
}

int main(){
    srand(time(NULL));
    while(numero_navios < 1 || numero_navios > 5){
        cout << "Insira o numero de navios (max 5): ";
        cin >> numero_navios;
    }

    while(tamanho_tabuleiro < 6 || tamanho_tabuleiro > 10){
        cout << "Insira o tamanho do tabuleiro (min 6 e max 10): ";
        cin >> tamanho_tabuleiro;
    }

    int navios[3] = {0}; //3 tipos de navios, cada posição armazena o numero de navios de cada tipo
    for(int i=0; i<numero_navios; i++){
        tipo = rand()% 3; // variavel tipo para gerar o número aleatorio usado no switch
        switch(tipo) {
            case 0:
                navios[0]++;
                break;
            case 1:
                navios[1]++;
                break;
            case 2:
                navios[2]++;
                break;
        }
    }

    for (int i=0; i < 3; i++){
        cout << navios[i] << " navios do tipo " << nome_do_navio[i] << endl; //informa quantos navios existem de cada tipo
    }

    gerar_tabuleiro();

    for(int j = 0; j < 3; j++){ //Como o comprimento dos vetores navios e comprimento são iguais, usa 3 como numero de repetição!
        while(navios[j] > 0){ //o codigo é feito para cada navio de cada tipo do vetor navios
            posicao_valida = true; //precisa disso senao o codigo não funciona, sla nao sei explicar direito
            direcao = rand() % 2; //escolhe se o navio vai ser vertical ou horizontal
            if (direcao == 0){ //Se Verical
                linha = rand()% (tamanho_tabuleiro - comprimento[j] + 1); //escolhe a linha do navio
                coluna = rand()% tamanho_tabuleiro; //escolhe a coluna do navio
                for(int k = 0; k < comprimento[j]; k++){ 
                    if(tabuleiro_nosso[linha + k][coluna] != '~'){ //verifica FINALMENTE se tem alguma coisa na posição
                        posicao_valida = false; //se já tiver algo, não coloca nada
                    }
                }
                if(posicao_valida == true){
                    for(int k = 0; k < comprimento[j]; k++){
                        tabuleiro_nosso[linha + k][coluna] = char_do_navio[j]; //a linha se altera pois o navio é na vertical, preenche o espaço
                    }
                    navios[j]--; //prossegue no ciclo while
                }
            }
            else{ // Se Horizontal
                linha = rand()% tamanho_tabuleiro; //escolhe a linha do navio
                coluna = rand() % (tamanho_tabuleiro - comprimento[j] + 1);  //escolhe a coluna do navio
                for(int k = 0; k < comprimento[j]; k++){
                    if(tabuleiro_nosso[linha][coluna + k] != '~'){ //verifica FINALMENTE se tem alguma coisa na posição
                        posicao_valida = false;
                    }
                }
                if(posicao_valida == true){
                    for(int k = 0; k < comprimento[j]; k++){
                        tabuleiro_nosso[linha][coluna + k] = char_do_navio[j]; //a coluna se altera pois o navio é na v horizontal, preenche o espaço
                    }
                    navios[j]--; //prossegue no ciclo while
                }
            }
        }
    }
while (ataque_linha_char != 'X'){
    cout << endl << "-------------FACA SEU ATAQUE-----------------------------" << endl;
    cout << "---------------------DIGITE X X PARA FECHAR --------------------" << endl;
    gerar_tabuleiro_ataque();
    imprimir_tabuleiros();
    seu_ataque();
    cout << "------------------------------------------------------------------------------------" << endl;
}
}
