#include <fstream>
#include <iostream>
#include "snake.h"
#include <windows.h>


void exibir_menu() {
    std::cout << "----- MENU -----" << std::endl;
    std::cout << "1. Jogar" << std::endl;
    std::cout << "2. Scoreboard" << std::endl;
    std::cout << "3. Comandos" << std::endl;
    std::cout << "4. Sair" << std::endl;

    std::cout << "Escolha uma opcao: ";
}

bool b_voltar_menu() {
    char escolha;
    do {
        cout << "Deseja voltar para o menu? (S) ou sair? (N): ";
        cin >> escolha;
        escolha = tolower(escolha); 
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (escolha != 's' && escolha != 'n') {
        cout << "Escolha inválida. Digite 'S' para voltar ao menu ou 'N' para sair." << endl;
        }
    } while (escolha != 's' && escolha != 'n');
    return (escolha == 's');
}

void exibir_comandos_e_voltar_menu(bool &voltar_menu) {
    system("cls"); 

    cout << "Comandos do Jogo:" << endl;
    cout << "Aperte 'A' para mover para a esquerda" << endl;
    cout << "Aperte 'D' para mover para a direita" << endl;
    cout << "Aperte 'W' para mover para cima" << endl;
    cout << "Aperte 'S' para mover para baixo" << endl;
    cout << "Aperte 'X' para parar o jogo" << endl;
    cin.ignore(); 
    voltar_menu = true;
}

int main() 
{
    bool voltar_menu = true;

    while (voltar_menu) 
    {
         exibir_menu();

    int opcao;
    std::cin >> opcao;

    switch (opcao) 
    {
        case 1: 
        {
            snake jogar_snake;
            jogar_snake.dificuldade();
            if (jogar_snake.jogar()) 
            {
                cout << "Escolha a dificuldade:" << endl;
                cout << "1. Facil" << endl;
                cout << "2. Dificil" << endl;
                cout << "Escolha: ";
                cin >> jogar_snake.velocidade;
            }
            break;
        }
        case 2: 
        {
            snake jogar_snake;
            jogar_snake.mostrar_scores();
            break;
        }
        case 3: 
        {
            exibir_comandos_e_voltar_menu(voltar_menu);
            break;
        }
        case 4:
            voltar_menu = false;
            break;
        default:
            std::cout << "Opcao invalida. Escolha uma opcao valida." << std::endl;
            break;
        }
        if (opcao != 4) 
        {
            voltar_menu = b_voltar_menu();
            system("cls");
        }
    }

    return 0;
}
