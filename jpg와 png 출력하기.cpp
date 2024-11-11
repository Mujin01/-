#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    // SDL 초기화
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL 초기화 실패: %s\n", SDL_GetError());
        return -1;
    }

    // 이미지 로딩을 위한 SDL_image 초기화
    if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0) {
        fprintf(stderr, "SDL_image 초기화 실패: %s\n", IMG_GetError());
        SDL_Quit();
        return -1;
    }

    // 윈도우 생성
    SDL_Window* window = SDL_CreateWindow("이미지 출력", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        fprintf(stderr, "윈도우 생성 실패: %s\n", SDL_GetError());
        IMG_Quit();
        SDL_Quit();
        return -1;
    }

    // 렌더러 생성
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        fprintf(stderr, "렌더러 생성 실패: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return -1;
    }

    // 첫 번째 이미지 로드 (jcshim.png)
    SDL_Surface* imageSurface1 = IMG_Load("jcshim.png");
    if (imageSurface1 == NULL) {
        fprintf(stderr, "첫 번째 이미지 로드 실패: %s\n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return -1;
    }

    // 두 번째 이미지 로드 (jcshim.jpg)
    SDL_Surface* imageSurface2 = IMG_Load("jcshim.jpg");
    if (imageSurface2 == NULL) {
        fprintf(stderr, "두 번째 이미지 로드 실패: %s\n", IMG_GetError());
        SDL_FreeSurface(imageSurface1);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return -1;
    }

    // 이미지들을 텍스처로 변환
    SDL_Texture* texture1 = SDL_CreateTextureFromSurface(renderer, imageSurface1);
    SDL_Texture* texture2 = SDL_CreateTextureFromSurface(renderer, imageSurface2);
    SDL_FreeSurface(imageSurface1);  // Surface는 더 이상 필요 없음
    SDL_FreeSurface(imageSurface2);

    if (texture1 == NULL || texture2 == NULL) {
        fprintf(stderr, "텍스처 생성 실패: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return -1;
    }

    // 첫 번째 이미지의 위치 지정 (왼쪽 상단)
    SDL_Rect destRect1 = { 100, 100, 300, 300 };  // x, y, width, height
    // 두 번째 이미지의 위치 지정 (오른쪽 상단)
    SDL_Rect destRect2 = { 400, 100, 300, 300 };  // x, y, width, height

    // 화면에 두 이미지 출력
    SDL_RenderClear(renderer);  // 화면 지우기
    SDL_RenderCopy(renderer, texture1, NULL, &destRect1);  // 첫 번째 이미지 출력
    SDL_RenderCopy(renderer, texture2, NULL, &destRect2);  // 두 번째 이미지 출력
    SDL_RenderPresent(renderer);  // 렌더링 결과 화면에 표시

    // 이벤트 루프 (ESC키로 종료)
    SDL_Event e;
    int quit = 0;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
        }
    }

    // 리소스 해제
    SDL_DestroyTexture(texture1);
    SDL_DestroyTexture(texture2);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    // 종료 처리
    IMG_Quit();
    SDL_Quit();

    return 0;
}
