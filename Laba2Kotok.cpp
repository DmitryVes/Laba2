#include "Laba2KotokH.h"

int main()
{
    setlocale(LC_ALL, "RU");
    Node* head = nullptr;
    Node* tail = nullptr;

    FillFromFile(head, tail);
    Show(head);
    DeleteList(head, tail);

    return 0;
}
