#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    // SDL �ʱ�ȭ
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL �ʱ�ȭ ����: %s\n", SDL_GetError());
        return -1;
    }

    // �̹��� �ε��� ���� SDL_image �ʱ�ȭ
    if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0) {
        fprintf(stderr, "SDL_image �ʱ�ȭ ����: %s\n", IMG_GetError());
        SDL_Quit();
        return -1;
    }

    // ������ ����
    SDL_Window* window = SDL_CreateWindow("�̹��� ���", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        fprintf(stderr, "������ ���� ����: %s\n", SDL_GetError());
        IMG_Quit();
        SDL_Quit();
        return -1;
    }

    // ������ ����
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        fprintf(stderr, "������ ���� ����: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return -1;
    }

    // ù ��° �̹��� �ε� (jcshim.png)
    SDL_Surface* imageSurface1 = IMG_Load("jcshim.png");
    if (imageSurface1 == NULL) {
        fprintf(stderr, "ù ��° �̹��� �ε� ����: %s\n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return -1;
    }

    // �� ��° �̹��� �ε� (jcshim.jpg)
    SDL_Surface* imageSurface2 = IMG_Load("jcshim.jpg");
    if (imageSurface2 == NULL) {
        fprintf(stderr, "�� ��° �̹��� �ε� ����: %s\n", IMG_GetError());
        SDL_FreeSurface(imageSurface1);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return -1;
    }

    // �̹������� �ؽ�ó�� ��ȯ
    SDL_Texture* texture1 = SDL_CreateTextureFromSurface(renderer, imageSurface1);
    SDL_Texture* texture2 = SDL_CreateTextureFromSurface(renderer, imageSurface2);
    SDL_FreeSurface(imageSurface1);  // Surface�� �� �̻� �ʿ� ����
    SDL_FreeSurface(imageSurface2);

    if (texture1 == NULL || texture2 == NULL) {
        fprintf(stderr, "�ؽ�ó ���� ����: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return -1;
    }

    // ù ��° �̹����� ��ġ ���� (���� ���)
    SDL_Rect destRect1 = { 100, 100, 300, 300 };  // x, y, width, height
    // �� ��° �̹����� ��ġ ���� (������ ���)
    SDL_Rect destRect2 = { 400, 100, 300, 300 };  // x, y, width, height

    // ȭ�鿡 �� �̹��� ���
    SDL_RenderClear(renderer);  // ȭ�� �����
    SDL_RenderCopy(renderer, texture1, NULL, &destRect1);  // ù ��° �̹��� ���
    SDL_RenderCopy(renderer, texture2, NULL, &destRect2);  // �� ��° �̹��� ���
    SDL_RenderPresent(renderer);  // ������ ��� ȭ�鿡 ǥ��

    // �̺�Ʈ ���� (ESCŰ�� ����)
    SDL_Event e;
    int quit = 0;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
        }
    }

    // ���ҽ� ����
    SDL_DestroyTexture(texture1);
    SDL_DestroyTexture(texture2);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    // ���� ó��
    IMG_Quit();
    SDL_Quit();

    return 0;
}
