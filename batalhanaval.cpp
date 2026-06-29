#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

//Variaveis Globais

const int MAX_TABULEIRO = 10;
int navios_nossos[3] = {0}, navios_inimigos[3] = {0}; //3 tipos de navios, cada posição armazena o numero de navios de cada tipo
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
char tabuleiro_inimigo[MAX_TABULEIRO][MAX_TABULEIRO] = {'~'};
char tabuleiro_nosso[MAX_TABULEIRO][MAX_TABULEIRO] = {'~'}; // tabuleiro char, '~' representa as ondinhas
bool jogar_novamente = false; //condição pra voce jogar duas vezes seguidas
bool posicao_valida = true; //variavel pra reinicar o ciclo de posicionamento de navios se a posiçao não for válida
bool fim_de_jogo = false;
string nome_do_navio[3] = {"Destroier (amarelo)", "Cruzador (verde)", "Porta-Aviao (vermelho)"};

void gerar_tabuleiro(char tabuleiro[MAX_TABULEIRO][MAX_TABULEIRO]){
    cout << endl;
    for(int i=0; i < tamanho_tabuleiro; i++){   // Gera a Matriz do tabuleiro
        for (int j=0; j < tamanho_tabuleiro; j++){
            tabuleiro[i][j] = '~';
        }
    }

}

void imprimir_colorido(char saida){ //imprime a saida colorida
    switch(saida){
        case '~':
            cout << "\033[34m" << saida << "\033[0m";
            break;
        case 'D':
            cout << "\033[33m" << saida << "\033[0m";
            break;
        case 'C':
            cout << "\033[32m" << saida << "\033[0m";
            break;  
        case 'P':
            cout << "\033[31m" << saida << "\033[0m";
            break;
        case 'X':
            cout << "\033[37m" << saida << "\033[0m";
            break;
        case '#':
            cout << "\033[38;2;255;165;0m" << saida << "\033[0m";
            break;
        default:
            cout << "\033[0m" << saida << "\033[0m";
            break;
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
            imprimir_colorido(tabuleiro_nosso[i][j]); //chama a função que vai colorir
            cout << " ";
        }
        cout << "\t\t"; 
        cout << alfabeto[i] << " "; //imprime as letras do lado do tabuleiro
        for (int j=0; j < tamanho_tabuleiro; j++){
            imprimir_colorido(tabuleiro_ataque[i][j]); //chama a função que vai colorir
            cout << " ";
        }
        cout << endl;
    }
}

void ataque(char tabuleiro[MAX_TABULEIRO][MAX_TABULEIRO], string dono){
    if (dono == "INIMIGO"){
        ataque_linha = rand()% tamanho_tabuleiro;
        ataque_coluna = rand()% tamanho_tabuleiro;
    }
    switch (tabuleiro[ataque_linha][ataque_coluna]){
        case '~':
            tabuleiro[ataque_linha][ataque_coluna] = 'X';
            jogar_novamente = false;
            break;
        default:
            tabuleiro[ataque_linha][ataque_coluna] = '#';
            jogar_novamente = true;
            break;
    }
}

void tipos_de_navio(int navios[3], string dono){
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
    
    cout << "Frota de " << dono << endl;
    for (int i=0; i < 3; i++){
        cout << navios[i] << " navios do tipo " << nome_do_navio[i] << endl; //informa quantos navios existem de cada tipo
    }
    
}

void escolher_posicoes(char tabuleiro[MAX_TABULEIRO][MAX_TABULEIRO], int navios[3]){
    int copia_navios[3] = {navios[0], navios[1], navios[2]}; //temos que criar uma copia do vetor pois será utlizado para tanto nós quanto para o inimigo e usamos navios[3]--
    for(int j = 0; j < 3; j++){ //Como o comprimento dos vetores navios e comprimento são iguais, usa 3 como numero de repetição!
        while(copia_navios[j] > 0){ //o codigo é feito para cada navio de cada tipo do vetor navios
            posicao_valida = true; //precisa disso senao o codigo não funciona, sla nao sei explicar direito
            direcao = rand() % 2; //escolhe se o navio vai ser vertical ou horizontal
            if (direcao == 0){ //Se Verical
                linha = rand()% (tamanho_tabuleiro - comprimento[j] + 1); //escolhe a linha do navio
                coluna = rand()% tamanho_tabuleiro; //escolhe a coluna do navio
                for(int k = 0; k < comprimento[j]; k++){ 
                    if(tabuleiro[linha + k][coluna] != '~'){ //verifica FINALMENTE se tem alguma coisa na posição
                        posicao_valida = false; //se já tiver algo, não coloca nada
                    }
                }
                if(posicao_valida == true){
                    for(int k = 0; k < comprimento[j]; k++){
                        tabuleiro[linha + k][coluna] = char_do_navio[j]; //a linha se altera pois o navio é na vertical, preenche o espaço
                    }
                    copia_navios[j]--; //prossegue no ciclo while
                }
            }
            else{ // Se Horizontal
                linha = rand()% tamanho_tabuleiro; //escolhe a linha do navio
                coluna = rand() % (tamanho_tabuleiro - comprimento[j] + 1);  //escolhe a coluna do navio
                for(int k = 0; k < comprimento[j]; k++){
                    if(tabuleiro[linha][coluna + k] != '~'){ //verifica FINALMENTE se tem alguma coisa na posição
                        posicao_valida = false;
                    }
                }
                if(posicao_valida == true){
                    for(int k = 0; k < comprimento[j]; k++){
                        tabuleiro[linha][coluna + k] = char_do_navio[j]; //a coluna se altera pois o navio é na v horizontal, preenche o espaço
                    }
                    copia_navios[j]--; //prossegue no ciclo while
                }
            }
        }
    }
}

void condicao_ataque(){
    while(jogar_novamente){
        imprimir_tabuleiros();
        cout << endl << "Digite as cordenadas de ataque: ";
        cin >> ataque_linha_char >> ataque_coluna;
        ataque(tabuleiro_ataque, "JOGADOR");
    }
}

void inimigo_jogar_novamente(){
    while(jogar_novamente){
        imprimir_tabuleiros();
        ataque_linha = rand()% tamanho_tabuleiro;
        ataque_coluna = rand()% tamanho_tabuleiro;
        ataque(tabuleiro_nosso, "INIMIGO");
    }
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

    tipos_de_navio(navios_nossos, "JOGADOR");

    gerar_tabuleiro(tabuleiro_nosso);

    gerar_tabuleiro(tabuleiro_inimigo);
    
    gerar_tabuleiro(tabuleiro_ataque);
    
    escolher_posicoes(tabuleiro_nosso, navios_nossos);

    tipos_de_navio(navios_inimigos, "INIMIGO");

    escolher_posicoes(tabuleiro_inimigo, navios_inimigos);

    while(!(fim_de_jogo)){
        cout << endl << "-------------FACA SEU ATAQUE-----------------------------" << endl;
        cout << "---------------------DIGITE X PARA FECHAR --------------------" << endl;
        imprimir_tabuleiros();
        cout << endl << "Digite as cordenadas de ataque: ";
        cin >> ataque_linha_char;
        ataque_linha_char = toupper(ataque_linha_char); //correção para aceitar maiusculo e minusculo
        if (ataque_linha_char == 'X'){
            break;
        }
        ataque_linha = ataque_linha_char - 65; //converte a coordenada da linah em forma de letra pra numero inteiro
        cin >> ataque_coluna;
        ataque(tabuleiro_ataque, "JOGADOR");
        condicao_ataque();
        ataque(tabuleiro_nosso, "INIMIGO");
        inimigo_jogar_novamente();
        cout << "------------------------------------------------------------------------------------" << endl;
    }
}
