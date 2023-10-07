#include <iostream>
#include <conio.h>

using namespace std;

bool gameover; // indica se o jogo acabou ou não

// tamanho do mapa
const int largura = 40;
const int altura = 20;

// posicoes da cabeça da cobra e da fruta
int x, y, frutaX, frutaY;
int rabinhoX[100], rabinhoY[100];
int rabinhoTAM;

int pontuacao;


// enumeradores que indicam a direção que a cobra anda
enum Direcao { STOP = 0, ESQUERDA, DIREITA, CIMA, BAIXO };
Direcao dir;



void Setup() {
    gameover = false;
    dir = STOP;
    // centraliza a cabeça da cobra
    x = largura / 2;
    y = altura / 2;
    // colocando a fruta aleatoriamente no mapa
    frutaX = rand() % largura;
    frutaY = rand() % altura;
    pontuacao = 0;
}

void Desenho() {
    system("cls");
    // desenhando o mapa
    for (int i = 0; i < largura + 2; i++) {
        cout << "#";
    }

    cout << endl;

    for (int i = 0; i < altura; i++) {
        for (int j = 0; j < largura; j++) {
            if (j == 0)
                cout << "#";
            if (i == y and j == x)
                cout << "[]";
            else if (i == frutaY and j == frutaX)
                cout << "<3";
            else {
                bool printado = false;
                for (int k = 0; k < rabinhoTAM; k++) {
                    
                    if (rabinhoX[k] == j and rabinhoY[k] == i) {
                        cout << "o";
                        printado = true;
                    }
                }
                if (!printado)
                    cout << " ";
            }  

            if (j == largura - 1)
                cout << "#";
        }
        cout << endl;  
    }

    for (int i = 0; i < largura + 2; i++) {
        cout << "#";
    }

    cout << endl;
    cout << "Pontuacao: " << pontuacao << endl;
}

void Input() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'a':
            dir = ESQUERDA;
            break;
        case 'd':
            dir = DIREITA;
            break;
        case 'w':
            dir = CIMA;
            break;
        case 's':
            dir = BAIXO;
            break;
        case 'x':
            gameover = true;
            break;
        }
    }
}

void Logica() {

    int Xanterior = rabinhoX[0];
    int Yanterior = rabinhoY[0];
    int ant2X, ant2Y;
    rabinhoX[0] = x;
    rabinhoY[0] = y;

    //movimentacao do rabinho da cobra
    for (int i = 1; i < rabinhoTAM; i++) {
        ant2X = rabinhoX[i];
        ant2Y = rabinhoY[i];
        rabinhoX[i] = Xanterior;
        rabinhoY[i] = Yanterior;
        Xanterior = ant2X;
        Yanterior = ant2Y;
    }

    switch (dir) {
    case CIMA:
        y--;
        break;
    case ESQUERDA:
        x--;
        break;
    case BAIXO:
        y++;
        break;
    case DIREITA:
        x++;
        break;
    }

    if (x > largura or x < 0 or y > altura or y < 0)
        gameover = true;
    if (x == frutaX and y == frutaY) {
        rabinhoTAM++;
        pontuacao += 10;
        frutaX = rand() % largura;
        frutaY = rand() % altura;
    }
       
}

int main() {

    Setup();

    while (!gameover) {
        Desenho();
        Input();
        Logica();
    }
    cout << "Game Over! Aperte ENTER para sair...";
    cin.get();
}