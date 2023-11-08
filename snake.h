#ifndef SNAKE_H
#define SNAKE_H

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int largura = 20;
const int altura = 20;
const int scores = 10;

struct cobra 
{
    int x;
    int y;
};

enum direcao
{
    parar = 0,
    esquerda,
    direita,
    cima,
    baixo,
};

class snake 
{
private:
    bool game_over;
    int score;
    int comprimento_cauda;
    direcao direcao;
    cobra cabeca;
    cobra fruta;
    cobra cauda[100];
    std::vector<std::pair<int, std::string>> scoreboard;
    string nome_jogador;
public:
    snake();
    static int velocidade;
    void mapa();
    void movimento();
    void logica();
    bool jogar();

    void nome();
    void carregar_scores();
    void update_scores();
    void salvar_scores();
    void mostrar_scores();
    void selecionar_dificuldade();
    void dificuldade();
};

#endif