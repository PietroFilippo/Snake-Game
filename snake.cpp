#include <conio.h>
#include <fstream>
#include "snake.h"
#include <windows.h>


snake::snake() 
{
    game_over = false;
    score = 0;
    direcao = parar;
    cabeca.x = largura / 2;
    cabeca.y = altura / 2;
    fruta.x = rand() % largura;
    fruta.y = rand() % altura;
    comprimento_cauda = 0;
    carregar_scores(); 
}
    
void snake::mapa() 
{
    COORD coord;
    coord.X = 0;
    coord.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    for (int i = 0; i < largura + 2; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < altura; i++) {
        for (int j = 0; j < largura; j++) {
            if (j == 0)
                cout << "#";
            if (i == cabeca.y && j == cabeca.x)
                cout << "O";
            else if (i == fruta.y && j == fruta.x)
                cout << "F";
            else {
                bool aumentar_cauda = false;
                for (int k = 0; k < comprimento_cauda; k++) {
                    if (cauda[k].x == j && cauda[k].y == i) {
                        cout << "o";
                        aumentar_cauda = true;
                    }
                }
                if (!aumentar_cauda)
                    cout << " ";
            }
            if (j == largura - 1)
                cout << "#";
        }
        cout << endl;
    }

    for (int i = 0; i < largura + 2; i++)
        cout << "#";
    cout << endl;

    cout << "Score: " << score << endl;
}
    
void snake::movimento() 
{
    if (_kbhit()) 
    {
        switch (_getch()) 
        {
            case 'a':
                direcao = esquerda;
                break;
            case 'd':
                direcao = direita;
                break;
            case 'w':
                direcao = cima;
                break;
            case 's':
                direcao = baixo;
                break;
            case 'x':
                game_over = true;
                break;
        }
    }
}

void snake::logica() 
{
    cobra movimento_cauda = cauda[0];
    cobra movimento_cauda2;

    cauda[0] = cabeca;

    for (int i = 1; i < comprimento_cauda; i++) 
    {
        movimento_cauda2 = cauda[i];
        cauda[i] = movimento_cauda;
        movimento_cauda = movimento_cauda2;
    }

    switch (direcao) 
    {
        case esquerda:
            cabeca.x--;
            break;
        case direita:
            cabeca.x++;
            break;
        case cima:
            cabeca.y--;
            break;
        case baixo:
            cabeca.y++;
            break;
    }

    if (cabeca.x >= largura)
        cabeca.x = 0;
    else if (cabeca.x < 0)
        cabeca.x = largura - 1;
    if (cabeca.y >= altura)
        cabeca.y = 0;
    else if (cabeca.y < 0)
        cabeca.y = altura - 1;

    for (int i = 0; i < comprimento_cauda; i++) 
    {
        if (cauda[i].x == cabeca.x && cauda[i].y == cabeca.y) 
        {
            game_over = true;
        }
    }

    if (cabeca.x == fruta.x && cabeca.y == fruta.y) 
    {
        score += 10;
        comprimento_cauda++;

        fruta.x = rand() % largura;
        fruta.y = rand() % altura;
    }
}

int snake::velocidade;

void snake::selecionar_dificuldade() 
{
    system("cls");
    cout << "Escolha a dificuldade:" << endl;
    cout << "1. Facil" << endl;
    cout << "2. Dificil" << endl;
}

void snake::dificuldade() 
{
    int opcao;

    do {
        selecionar_dificuldade();
        cout << "Escolha: ";
        cin >> opcao;

        if (opcao == 1) 
        {
            velocidade = 75; 
        } else if (opcao == 2) 
        {
            velocidade = 20; 
        } else 
        {
            cout << "Opção inválida. Escolha 1 para Fácil ou 2 para Difícil." << endl;
            Sleep(5000);
        }

        if (opcao != 1 && opcao != 2) 
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (opcao != 1 && opcao != 2);
}

bool snake::jogar() 
{
    while (!game_over) 
    {
        mapa();
        movimento();
        logica();
        Sleep(velocidade);
    }

    if (game_over) 
    {
        nome();
        update_scores();
}
    mostrar_scores();

    return !game_over;
}

void snake::nome() 
{
    cout << "Insira seu nome: ";
    cin >> nome_jogador;
}

void snake::carregar_scores() 
{
    ifstream file("scores.txt");
    if (file.is_open()) 
    {
        int score;
        string nome;
        while (file >> score >> nome) 
        {
            scoreboard.push_back(std::make_pair(score, nome));
        }
        file.close();
    }
}

void snake::update_scores() 
{
    scoreboard.push_back(std::make_pair(score, nome_jogador));
    sort(scoreboard.rbegin(), scoreboard.rend());
    if (scoreboard.size() > scores) 
    {
        scoreboard.resize(scores);
    }
    salvar_scores();
}

void snake::salvar_scores() 
{
    ofstream file("scores.txt");
    if (file.is_open()) 
    {
        for (const auto& entry : scoreboard) 
        {
            file << entry.first << " " << entry.second << endl;
        }
        file.close();
    }
}

void snake::mostrar_scores() 
{
    system("cls");
    cout << "SCOREBOARD" << endl;
    cout << "--------------------------" << endl;
    cout << "Rank\tScore\tNome" << endl;
    cout << "--------------------------" << endl;
    for (size_t i = 0; i < scoreboard.size(); i++) 
    {
        cout << i + 1 << "\t" << scoreboard[i].first << "\t" << scoreboard[i].second << endl;
    }
    cout << "--------------------------" << endl;
}

