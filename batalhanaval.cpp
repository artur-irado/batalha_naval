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
int rodada = 1;
int pedacos_de_navios_nossos = 0;
int pedacos_de_navios_inimigos = 0;
int tamanho_tabuleiro = 1;
float pontuacao_voce = 0;
float pontuacao_inimigo = 0;
char alfabeto[10] = {'A','B','C','D','E','F','G','H','I','J'};
char ataque_linha_char; //coordenada que voce insire pra atacar (linha, a..b...c) em forma de char
char char_do_navio[3] = {'D', 'C', 'P'};
char tabuleiro_ataque[MAX_TABULEIRO][MAX_TABULEIRO] = {'~'};
char tabuleiro_inimigo[MAX_TABULEIRO][MAX_TABULEIRO] = {'~'};
char tabuleiro_nosso[MAX_TABULEIRO][MAX_TABULEIRO] = {'~'}; // tabuleiro char, '~' representa as ondinhas
bool jogar_novamente = false; //condição pra voce jogar duas vezes seguidas
bool posicao_valida = true; //variavel pra reinicar o ciclo de posicionamento de navios se a posiçao não for válida
bool fim_de_jogo = false;
bool ausencia_de_navios = false;
bool alguem_ganhou = false;
string nome_do_navio[3] = {"Destroier (amarelo)", "Cruzador (verde)", "Porta-Aviao (vermelho)"};
string vencedor;

void gerar_tabuleiro(char tabuleiro[MAX_TABULEIRO][MAX_TABULEIRO]){
    cout << endl;
    for(int i=0; i < tamanho_tabuleiro; i++){   // Gera a Matriz do tabuleiro
        for (int j=0; j < tamanho_tabuleiro; j++){
            tabuleiro[i][j] = '~';
        }
    }

}

void calcular_pontuacao(string pontuante){ 
    if (pontuante == "voce"){
        pontuacao_voce += 10*(rodada/0.9);
    } else{
        pontuacao_inimigo += 10*(rodada/0.9);
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

void verificar_tabuleiro(){
    if(pedacos_de_navios_inimigos == 0){
        vencedor = "JOGADOR";
        fim_de_jogo = true;
        alguem_ganhou = true;
    }
    if (pedacos_de_navios_nossos == 0){
        vencedor = "INIMIGO";
        fim_de_jogo = true;
        alguem_ganhou = true;
    }
}

void contar_partes_de_navio (string dono_do_tabuleiro){
    if (dono_do_tabuleiro == "INIMIGO"){
        pedacos_de_navios_inimigos++;
    }
    else {
        pedacos_de_navios_nossos++;
    }
}

void escolher_posicoes(char tabuleiro[MAX_TABULEIRO][MAX_TABULEIRO], int navios[3], string dono_do_tabuleiro){
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
                        contar_partes_de_navio(dono_do_tabuleiro);
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
                        contar_partes_de_navio(dono_do_tabuleiro);
                        tabuleiro[linha][coluna + k] = char_do_navio[j]; //a coluna se altera pois o navio é na v horizontal, preenche o espaço
                    }
                    copia_navios[j]--; //prossegue no ciclo while
                }
            }
        }
    }
}

void ataque(string atacante){
    if (atacante == "INIMIGO"){
        do {
            ataque_linha = rand() % tamanho_tabuleiro;
            ataque_coluna = rand() % tamanho_tabuleiro;
        } while (tabuleiro_nosso[ataque_linha][ataque_coluna] == 'X' || tabuleiro_nosso[ataque_linha][ataque_coluna] == '#');
        switch (tabuleiro_nosso[ataque_linha][ataque_coluna]){
            case '~':
                tabuleiro_nosso[ataque_linha][ataque_coluna] = 'X';
                jogar_novamente = false;
                break;
            case 'X':
                jogar_novamente = false;
                break;
            case '#':
                jogar_novamente = false;
                break;
            default:
                tabuleiro_nosso[ataque_linha][ataque_coluna] = '#';
                jogar_novamente = true;
                pedacos_de_navios_nossos--;
                calcular_pontuacao("inimigo");
                break;
        }
    }
    else{
        if(tabuleiro_ataque[ataque_linha][ataque_coluna] != '~'){
            cout << "Voce ja atacou nessa coordenada!, perdeu a vez!";
        }
        else{
            switch (tabuleiro_inimigo[ataque_linha][ataque_coluna]){
                case '~':
                    tabuleiro_ataque[ataque_linha][ataque_coluna] = 'X';
                    tabuleiro_inimigo[ataque_linha][ataque_coluna] = 'X';
                    jogar_novamente = false;
                    break;
                case 'X':
                    jogar_novamente = false;
                    break;
                case '#':
                    jogar_novamente = false;
                    break;
                default:
                    tabuleiro_ataque[ataque_linha][ataque_coluna] = '#';
                    tabuleiro_inimigo[ataque_linha][ataque_coluna] = '#';
                    calcular_pontuacao("voce");
                    pedacos_de_navios_inimigos--;
                    jogar_novamente = true;
                break;
            }
        }
    }
    cout << endl << atacante << " atacou nas posicoes: " << alfabeto[ataque_linha] << " " << ataque_coluna << endl; 
}

void condicao_ataque(string vez){
    while(jogar_novamente && fim_de_jogo == false){ //verifica se é possivel algum dos jogadores jogar de novo
        imprimir_tabuleiros();
        if(vez == "JOGADOR"){
            cout << endl << "Digite as cordenadas de ataque: ";
            cin >> ataque_linha_char;
            ataque_linha_char = toupper(ataque_linha_char);
            if (ataque_linha_char == 'X'){
                fim_de_jogo = true;
                break;
            }
            ataque_linha = ataque_linha_char - 65;
            cin >> ataque_coluna;
        }
        else{
            do{
                ataque_linha = rand() % tamanho_tabuleiro;
                ataque_coluna = rand() % tamanho_tabuleiro;
            }while(tabuleiro_nosso[ataque_linha][ataque_coluna] == 'X' || tabuleiro_nosso[ataque_linha][ataque_coluna] == '#');
        }
        ataque(vez);
        verificar_tabuleiro();
    }
}

void inputs(){
    while(numero_navios < 1 || numero_navios > 5){
        cout << "Insira o numero de navios (max 5): ";
        cin >> numero_navios;
    }
    
    while(tamanho_tabuleiro < 6 || tamanho_tabuleiro > 10){
        cout << "Insira o tamanho do tabuleiro (min 6 e max 10): ";
        cin >> tamanho_tabuleiro;
    }

}

void pos_vitoria(){
    char permissao;
    if(alguem_ganhou == true){
    cout << endl << "========================================" << endl;
    cout << "           TABULEIRO FINAL             " << endl;
    cout << "========================================" << endl;
    
    imprimir_tabuleiros(); 

    cout << endl << "========================================" << endl;
    cout << "FIM DE JOGO! O VENCEDOR FOI O: " << vencedor << endl;
    cout << "========================================" << endl;

    cout << "Sua Pontuacao: " << pontuacao_voce << endl;
    cout << "Pontuacao do Inimigo: " << pontuacao_inimigo << endl; 
    }
}

void gameplay(){
    tipos_de_navio(navios_nossos, "JOGADOR");

    gerar_tabuleiro(tabuleiro_nosso);

    gerar_tabuleiro(tabuleiro_inimigo);
    
    gerar_tabuleiro(tabuleiro_ataque);
    
    escolher_posicoes(tabuleiro_nosso, navios_nossos, "JOGADOR");

    tipos_de_navio(navios_inimigos, "INIMIGO");

    escolher_posicoes(tabuleiro_inimigo, navios_inimigos, "INIMIGO");

    while(fim_de_jogo == false){
        cout << endl << "-------------FACA SEU ATAQUE-----------------------------" << endl;
        cout << "---------------------DIGITE X PARA FECHAR --------------------" << endl;
        imprimir_tabuleiros();
        cout << endl << "Numero da Rodada: " << rodada << endl;
        cout << endl << "Digite as cordenadas de ataque: ";
        cin >> ataque_linha_char;
        ataque_linha_char = toupper(ataque_linha_char); //correção para aceitar maiusculo e minusculo
        if (ataque_linha_char == 'X'){
            break;
        }
        ataque_linha = ataque_linha_char - 65; //converte a coordenada da linah em forma de letra pra numero inteiro
        cin >> ataque_coluna;
        ataque("JOGADOR");
        verificar_tabuleiro();
        condicao_ataque("JOGADOR");
        if (fim_de_jogo){
            break;
        }
        cout << "------------------------------------------------------------------------------------" << endl;
        ataque("INIMIGO");
        verificar_tabuleiro();
        condicao_ataque("INIMIGO");
        verificar_tabuleiro();
        cout << "sua pontuacao: " << pontuacao_voce << endl;
        cout << "pontuacao do inimigo: " << pontuacao_inimigo << endl;
        if (fim_de_jogo){
            break;
        }
        rodada++;
    }
    pos_vitoria();
}

int main(){
    srand(time(NULL));

    inputs();

    gameplay();
}
