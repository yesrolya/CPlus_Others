// ���������������� �����
#include <stdio.h>
//#include <unistd.h>
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
        sem_post(&semA); //���������� �� 1 �������� semA
        std::cout << "����������� ������ A" << std::endl;
    }
}

void* createB (void* argv){
    for (int i = 1; i <= n; i++){
        Sleep(3000);
        sem_post(&semB);   //���������� �� 1 �������� semB
        std::cout << "����������� ������ B" << std::endl;
    }
}

void* createC (void* argv){
    for (int i = 1; i <= n; i++){
        Sleep(4000);
        sem_post(&semC);  //���������� �� 1 �������� semC
        std::cout << "����������� ������ C" << std::endl;
    }
}

void* createAB (void* argv){
    for (int i = 1; i <= n; i++){
        Sleep(1);
        sem_wait(&semA); //���� semA = 1 � ���������� �� 1 �������� semA
        sem_wait(&semB); //���� semB = 1 � ���������� �� 1 �������� semB
        sem_post(&semAB);  //���������� �� 1 �������� semAB
        std::cout << "������ ������ AB" << std::endl;
    }
}

void* createWidget (){
    for (int i = 1; i <= n; i++){
        Sleep(1);
        sem_wait(&semAB);  //���� semAB = 1 � ���������� �� 1 �������� semAB
        sem_wait(&semC); //���� semC = 1 � ���������� �� 1 �������� semC
        std::cout << "���������� #" << i << " ������� �� ������ AB � ������ C" << std::endl;
    }
}

int main(){
    setlocale(LC_CTYPE,"Russian");
    pthread_t threadA;
    pthread_t threadB;
    pthread_t threadC;
    pthread_t threadAB;
    std::cout << "������� ��������� ���������, ������� ���������� ����������: ";
    std::cin >> n;

    sem_init(&semA, 0, 0); //�������������� �������� = 0
    sem_init(&semB, 0, 0); //�� ���� ��� ��������� ��������
    sem_init(&semC, 0, 0);
    sem_init(&semAB, 0, 0);

    pthread_create(&threadA, NULL, createA, NULL); //��� ��������� � ���������� (NULL)
    pthread_create(&threadB, NULL, createB, NULL);
    pthread_create(&threadC, NULL, createC, NULL);
    pthread_create(&threadAB, NULL, createAB, NULL);
    createWidget();

    return 0;
}
