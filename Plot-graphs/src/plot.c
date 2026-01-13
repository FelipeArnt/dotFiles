/* Projeto para passar em cálculo 1;
*---------------------------------------------------------------------------
*       Fórmulas
* escalaX = 50
* escalaY = 100
*
* x_math  = (x_pixel - Y_AXIS_X) / 50.0f
* y_math  = sin(x_math)
* y_pixel = X_AXIS_Y - y_math * 100.0f
*----------------------------------------------------------------------------
*       Conversão de pixel X para X matemático
* float math_x1 = (float)(x - Y_AXIS_X) / 50.0f;
* float math_x2 = (float)((x + 1) - Y_AXIS_X) / 50.0f;
*
* Y_AXIS_X É a posição em pixels, onde o Y vertical foi colocado na tela;
*
* (X - Y_AXIS_X) Desloca a origem do eixo X da tela para o eixo Y matematico,
* fazendo o eixo x = 0 da matematica coincidir com a coluna Y_AXIS_X;
* 50 pixels em X na tela correspondem a 1 unidade em X no mundo matemático
* math_x=  x*pixel - XeixoY / 50; Divisão por 50.0f é por um fator de escala.
*----------------------------------------------------------------------------
*       Função senoidal
* Aqui é calculado: y = sin(x) para os dois pontos vizinhos em X.
*
* float math_y1 = sin(math_x1); float math_y2 = sin(math_x2);
* math_y1 e math_y2 são valores reais no intervalo [-1,1]
* Que representam a altura da função em coordenadas matemáticas
*-----------------------------------------------------------------------------
*         Conversão de Y matemático para Y de tela
* int screen_y1 = X_AXIS_Y - (int)(math_y1 * 100.0f);
* int screen_y2 = X_AXIS_Y - (int)(math_y2 * 100.0f);
*
* X_AXIS_Y é a linha em pixels, onde o eixo X horizontal na tela foi colocado.
*------------------------------------------------------------------------------
*         Multiplicação por 100 reescala a amplitude:
* 1 unidade em Y matemático correponde a 100 pixels na tela
* Como sin(x) varia entre [-1 e 1] o gráfico vai de: 
* [X_AXIS_Y - 100] até [X_AXIS_Y + 100]
*-------------------------------------------------------------------------------
*         O sinal é invertido por conta do sistema da tela:
* Na matemática, Y aumenta para CIMA
* Na tela, o índice Y aumenta para baixo.
*
* Por isso usa X_AXIS_Y - (...)
* ypixel = Y_AXIS_X − (math_y⋅escalaY)
* Se math_y é positivo, subtrai e sobe na tela; se é negativo, soma e desce.
*--------------------------------------------------------------------------------
*       Desenho da curva por segmentos
* DrawLine(x, screen_y1, x + 1, screen_y2, RED); Para cada coluna x: 
* O ponto (x, screen_y1) liga com o ponto: (x + 1,screen_y2);
* Esses pequenos segmentos aproximam a curva contínua de y=sin(x) no discreto da tela.
*
*/

#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450
#define X_AXIS_Y (SCREEN_HEIGHT / 2)
#define Y_AXIS_X (SCREEN_WIDTH / 2)


int main(void)
{
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Visualizador de funções");
  SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("Primeira função do projeto de plot!", 20, 20, 20, BLACK);
            
            DrawLine(0, X_AXIS_Y, SCREEN_WIDTH, X_AXIS_Y, LIGHTGRAY);
            DrawLine(Y_AXIS_X, 0, Y_AXIS_X, SCREEN_HEIGHT, LIGHTGRAY);
            
            for (int x = 0; x < SCREEN_WIDTH - 1; x++){
                float math_x1 = (float)(x - Y_AXIS_X) / 50.0f;
                float math_x2 = (float)((x + 1) - Y_AXIS_X) / 50.0f;

                float math_y1 = sin(math_x1);
                float math_y2 = sin(math_x2);

                int screen_y1 = X_AXIS_Y - (int)(math_y1 * 100.0f);
                int screen_y2 = X_AXIS_Y - (int)(math_y2 * 100.0f);

                DrawLine(x, screen_y1, x + 1, screen_y2, RED);

    }
        EndDrawing();

    }

    CloseWindow();

    return 0;
}
