#include "mygl.h"

unsigned char* fb_ptr = NULL;

struct Line {
  int x0;
  int y0;
  int x1;
  int y1;
  int* color0;
  int* color1;
};

struct Triangle {
  int x0;
  int y0;
  int x1;
  int y1;
  int x2;
  int y2;
  int* color0;
  int* color1;
  int* color2;
};

typedef struct Line Line;
typedef struct Triangle Triangle;

void InitMyGl(void) {
    fb_ptr = (unsigned char *)malloc(IMAGE_WIDTH * IMAGE_HEIGHT * 4 * sizeof(char));

    for (int i = 0; i < IMAGE_WIDTH * IMAGE_HEIGHT; ++i) {
        fb_ptr[i * 4] = 0;
        fb_ptr[i * 4 + 1] = 0;
        fb_ptr[i * 4 + 2] = 0;
        fb_ptr[i * 4 + 3] = 255;
    }
}

float SquareRoot (float number)
{
    int n;
    float walks = number;
    for (n = 0; n < 10; ++n) walks = walks/2 + number/(2*walks);
    return(walks);
}

unsigned char* GetFBMemPtr(void) {
	return fb_ptr;
}

void CloseMyGl(void) {
    if (!fb_ptr)
        free(fb_ptr);
}


void PutPixel(int x, int y, int *color) {
    for(int i = 0; i < 4; i++){
        fb_ptr[4*y*IMAGE_WIDTH + 4*x + i] = color[i];
    }
}

void DrawLine(struct Line line) {
    int dx, dy, x, y, pY, pX, p, caminho;
    float distancia_total, comparaR, comparaG, comparaB, comparaA, r, g, b, a;

    dx = line.x1 - line.x0;
    dy = line.y1 - line.y0;

    if(dx < 0){
        pX = -1;
    }else{
        pX = 1;
    }

    if(dy < 0){
        pY = -1;
    }else{
        pY = 1;
    }

    dx = abs(dx);
    dy = abs(dy);

    if(dx > dy){
        caminho = dx;
    }else{
        caminho = dy;
    }
    p = caminho/2;

    distancia_total = SquareRoot((dx*dx) + (dy*dy));


    r = line.color0[0];
    g = line.color0[1];
    b = line.color0[2];
    a = line.color0[3];


    comparaR = (line.color1[0] - line.color0[0]) / distancia_total;
    comparaG = (line.color1[1] - line.color0[1]) / distancia_total;
    comparaB = (line.color1[2] - line.color0[2]) / distancia_total;
    comparaA = (line.color1[3] - line.color0[3]) / distancia_total;

    x = line.x0;
    y = line.y0;

    PutPixel(x, y, line.color0);

    while(caminho > 0) {

         if(dx > dy) {
            x += pX;
            p += dy;

            if(p >= dx) {
                y += pY;
                p -= dx;
            }
        } else {
            y += pY;
            p += dx;

            if(p >= dy) {
                x += pX;
                p -= dy;
            }
        }

        r += comparaR;
        g += comparaG;
        b += comparaB;
        a += comparaA;

        int RGBA[4] = {r, g, b, a};

        PutPixel(x, y, RGBA);
        caminho--;
    }

    PutPixel(x, y, line.color1);
}

void DrawTriangle(struct Triangle triangle) {

    struct Line line0;
    struct Line line1;
    struct Line line2;

    line0.x0 = triangle.x0;
    line0.y0 = triangle.y0;
    line0.x1 = triangle.x1;
    line0.y1 = triangle.y1;
    line0.color0 = triangle.color0;
    line0.color1 = triangle.color1;

    line1.x0 = triangle.x1;
    line1.y0 = triangle.y1;
    line1.x1 = triangle.x2;
    line1.y1 = triangle.y2;
    line1.color0 = triangle.color1;
    line1.color1 = triangle.color2;

    line2.x0 = triangle.x2;
    line2.y0 = triangle.y2;
    line2.x1 = triangle.x0;
    line2.y1 = triangle.y0;
    line2.color0 = triangle.color2;
    line2.color1 = triangle.color0;

    DrawLine(line0);
    DrawLine(line1);
    DrawLine(line2);
}


// Definição da função que chamará as funções implementadas pelo aluno
void MyGlDraw(void) {

  // colors
  int red[4] = {255, 0, 0, 255};
  int green[4] = {0, 255, 0, 255};
  int blue[4] = {0, 0, 255, 255};

  // Draw Line

  // struct Line line;

  // line.x0 = 0;
  // line.y0 = 0;
  // line.x1 = 511;
  // line.y1 = 511;
  // line.color0 = red;
  // line.color1 = blue;

  // DrawLine(line);

  // End Draw Line


  // Draw draw Triangle

  struct Triangle triangle;

  triangle.x0 = 106;
  triangle.y0 = 406;

  triangle.x1 = 90;
  triangle.y1 = 106;

  triangle.x2 = 406;
  triangle.y2 = 406;

  triangle.color0 = red;
  triangle.color1 = green;
  triangle.color2 = blue;

  DrawTriangle(triangle);

  // End draw Triangle

  // PutPixel(100, 200, red);
  // PutPixel(200, 100, green);
  // PutPixel(200, 300, blue);

  // End draw Triangle
}
