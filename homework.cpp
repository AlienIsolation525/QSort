#include <iostream>
#include <queue>
#include <thread>
#include <condition_variable>
#include <mutex>

struct Node
{
    int value;
    Node* next;
    std::mutex* node_mutex;
};

class FineGrainedQueue
{
public:
    FineGrainedQueue();

    void insertIntoMiddle(int value, int pos) {
        // Получение эксклюзивного доступа к очереди
        std::unique_lock<std::mutex> queue_lock(queue_mutex);

        // Проверка позиции вставки
        if (pos > length) {
            pos = length; // Вставка в конец списка
        }

        // Поиск позиции вставки
        Node* current = head;
        for (int i = 0; i < pos - 1; ++i) {
            current = current->next;
        }

        // Создание нового узла
        Node* new_node = new Node;
        new_node->value = value;
        new_node->next = current->next;

        // Установка node_mutex для нового узла
        new_node->node_mutex = new std::mutex;

        // Связывание нового узла с текущим списком
        current->next = new_node;

        // Освобождение блокировки текущего узла
        queue_lock.unlock();
    }

private:
    Node* head;
    int length;
    std::mutex queue_mutex;
};


int main() {

    return 0;
}