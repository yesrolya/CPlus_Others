// Производственная линия
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include<locale>
#include <windows.h>
#include <iostream>

sem_t semA, semB, semC, semAB;
int n;

void* createA (void* argv){
    for (int i = 1; i <= n; i++){
        Sleep(2000);
        sem_post(&semA); //увеличение на 1 семафора semA
        std::cout << "Произведена деталь A" << std::endl;
    }
}

void* createB (void* argv){
    for (int i = 1; i <= n; i++){
        Sleep(3000);
        sem_post(&semB);   //увеличение на 1 семафора semB
        std::cout << "Произведена деталь B" << std::endl;
    }
}

void* createC (void* argv){
    for (int i = 1; i <= n; i++){
        Sleep(4000);
        sem_post(&semC);  //увеличение на 1 семафора semC
        std::cout << "Произведена деталь C" << std::endl;
    }
}

void* createAB (void* argv){
    for (int i = 1; i <= n; i++){
        Sleep(1);
        sem_wait(&semA); //ждет semA = 1 и уменьшение на 1 семафора semA
        sem_wait(&semB); //ждет semB = 1 и уменьшение на 1 семафора semB
        sem_post(&semAB);  //увеличение на 1 семафора semAB
        std::cout << "Собран модуль AB" << std::endl;
    }
}

void* createWidget (){
    for (int i = 1; i <= n; i++){
        Sleep(1);
        sem_wait(&semAB);  //ждет semAB = 1 и уменьшение на 1 семафора semAB
        sem_wait(&semC); //ждет semC = 1 и уменьшение на 1 семафора semC
        std::cout << "Устройство #" << i << " собрано из модуля AB и детали C" << std::endl;
    }
}

int main(){
    setlocale(LC_CTYPE,"Russian");
    pthread_t threadA;
    pthread_t threadB;
    pthread_t threadC;
    pthread_t threadAB;
    std::cout << "Введите количесво устройств, которые необходимо произвести: ";
    std::cin >> n;
    
    sem_init(&semA, 0, 0); //первоначальное значение = 0
    sem_init(&semB, 0, 0); //то есть все конвейеры свободны
    sem_init(&semC, 0, 0);
    sem_init(&semAB, 0, 0);

    pthread_create(&threadA, NULL, createA, NULL); //без атрибутов и аргуметнов (NULL)
    pthread_create(&threadB, NULL, createB, NULL);
    pthread_create(&threadC, NULL, createC, NULL);
    pthread_create(&threadAB, NULL, createAB, NULL);
    createWidget();
    return 0;
}
