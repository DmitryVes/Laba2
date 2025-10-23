#include <iostream>
#include <functional>
#include <fstream>
#include <string>

using namespace std;

struct BList
{
    string FIO;
    string WorkPlace;
    string OpenData;
    int Illness;
    int WorkLessDays;
    BList(string _FIO = "", string _WorkPlace = "",
        int _Illness = 0, string _OpenData = "", int _WorkLessDays = 0);
};

struct Node
{
    BList* data;
    Node* next, * prev;
    Node(BList* _data = nullptr);
};

bool isEmpty(Node* head);
string normalize_data(string& data);
Node* Find(Node* head, BList& data);
void DeleteFromHead(Node*& head, Node*& tail);
void DeleteFromTail(Node*& tail, Node*& head);
void AddToTail(Node*& tail, Node*& head, BList& data);
void AddToHead(Node*& head, Node*& tail, BList& data);
void DeleteAfter(Node* pNode, Node*& tail, BList& data);
void AddAfter(Node* head, Node*& tail, BList& data, BList& _data);
void AddBefore(Node*& head, BList& data, BList& _data);
void DeleteList(Node*& head, Node*& tail);
void Show(Node* head);
bool operator==(const BList& blist, const BList& blist2);
Node* FindInsertPlace(Node* head, BList& blist);
void SortedFill(function <bool(BList&, BList&)> val, Node*& head, Node*& tail, BList& blist);
void FillFromFile(Node*& head, Node*& tail);
void BubbleSort(Node*& head);
ostream& operator<<(ostream& out, const BList& blist);


int main()
{
    setlocale(LC_ALL, "");
    Node* head = nullptr;
    Node* tail = nullptr;

    FillFromFile(head, tail);
    //Show(head);
    BubbleSort(head);
    Show(head);
    DeleteList(head, tail);

    return 0;
}

void BubbleSort(Node*& head)
{
    Node* p = head, *cur_p = head;

    int krit{};
    cout << "Введите критерий упорядочения" << endl
        << "1 - по убыванию больничных дней" << endl
        << "2 - по убыванию даты открытия больничных" << endl
        << "3 - по убыванию кодов заболеваний" << endl
        << "любой другой символ - выход" << endl << endl;

    cin >> krit;

    while (p)
    {
        while (cur_p->next)
        {
            switch (krit)
            {
            case 1:
                if (cur_p->data->WorkLessDays < cur_p->next->data->WorkLessDays)
                    swap(cur_p->data->WorkLessDays, cur_p->next->data->WorkLessDays);
                break;
            case 2:
                if (head->data->OpenData < cur_p->next->data->OpenData)
                    swap(head->data->OpenData, cur_p->next->data->OpenData);
                break;
            case 3:
                if (cur_p->data->Illness < cur_p->next->data->Illness)
                    swap(cur_p->data->Illness, cur_p->next->data->Illness);
                break;
            default: break;
            }
            cur_p = cur_p->next;
        }
        p = p->next;
    }
}


BList::BList(string _FIO, string _WorkPlace,
    int _Illness, string _OpenData, int _WorkLessDays)
{
    FIO = _FIO;
    WorkPlace = _WorkPlace;
    Illness = _Illness;
    OpenData = _OpenData;
    WorkLessDays = _WorkLessDays;
}

Node::Node(BList* _data)
{
    data = _data;
    next = prev = nullptr;
}

string normalize_data(string& data)
{
    return data.substr(6, 2) + data.substr(3, 2) + data.substr(0, 2);
}

bool isEmpty(Node* head)
{
    return !head;
}

void DeleteFromHead(Node*& head, Node*& tail)
{
    if (head)
    {
        Node* p = head->next;
        delete head;
        if (p) p->prev = nullptr;
        else tail = nullptr;
        head = p;
    }
}

void DeleteFromTail(Node*& tail, Node*& head)
{
    if (tail)
    {
        Node* p = tail->prev;
        delete tail;
        if (p) p->next = nullptr;
        else head = nullptr;
        tail = p;
    }
}

void AddToTail(Node*& tail, Node*& head, BList& data)
{
    Node* p = new Node(&data);
    if (tail) tail->next = p;
    else head = p;
    p->prev = tail;
    tail = p;
}

void AddToHead(Node*& head, Node*& tail, BList& data)
{
    Node* p = new Node(&data);
    p->next = head;
    if (head) head->prev = p;
    else tail = p;
    head = p;
}

void DeleteAfter(Node* head, Node*& tail, BList& data)
{
    Node* pNode = Find(head, data);
    Node* p = pNode->next;
    if (p)
    {
        pNode->next = p->next;
        if (p->next) p->next->prev = pNode;
        else tail = p->prev;
    }
    delete p;
    p = nullptr;
}

void AddAfter(Node* head, Node*& tail, BList& data, BList& _data)
{
    Node* pNode = Find(head, data);
    Node* p = new Node(&_data);
    p->next = pNode->next;
    p->prev = pNode;
    if (pNode->next) pNode->next->prev = p;
    else tail = p;
    pNode->next = p;
}

void AddBefore(Node*& head, BList& data, BList& _data)
{
    Node* pNode = Find(head, data);
    Node* p = new Node(&_data);
    p->next = pNode;
    p->prev = pNode->prev;
    if (pNode->prev) pNode->prev->next = p;
    else head = p;
    pNode->prev = p;
}

Node* Find(Node* head, BList& data)
{
    Node* p = head;

    while (p)
    {
        if (p->data == &data)
        {
            return p;
        }
        p = p->next;
    }
    return nullptr;
}

void DeleteList(Node*& head, Node*& tail)
{
    while (!isEmpty(head))
    {
        DeleteFromHead(head, tail);
    }
}

void Show(Node* head)
{
    Node* p = head;

    while (p)
    {
        cout << *p->data;
        p = p->next;
    }
}

void FillFromFile(Node*& head, Node*& tail)
{
    ifstream in;
    in.open("TestFile.txt");
    string tmp = "";
    BList* blist = new BList;

    int krit{};
    cout << "Введите критерий упорядочения" << endl
        << "1 - по убыванию больничных дней" << endl
        << "2 - по убыванию даты открытия больничных" << endl
        << "3 - по убыванию кодов заболеваний" << endl
        << "любой другой символ - выход" << endl << endl;

    cin >> krit;

    if (in.is_open())
    {
        while (in.good())
        {
            getline(in, blist->FIO);
            getline(in, blist->WorkPlace);
            getline(in, blist->OpenData);
            getline(in, tmp);
            blist->Illness = stoi(tmp);
            getline(in, tmp);
            blist->WorkLessDays = stoi(tmp);
            switch (krit)
            {
            case 1:
                SortedFill((function <bool(BList&, BList&)>)[](BList& blist, BList& blist2)
                    { return blist.WorkLessDays >= blist2.WorkLessDays; }, head, tail, *(new BList(*blist)));
                break;
            case 2:
                SortedFill((function <bool(BList&, BList&)>)[](BList& blist, BList& blist2)
                    { return normalize_data(blist2.OpenData) >= normalize_data(blist2.OpenData); }, head, tail, *(new BList(*blist)));
                break;
            case 3:
                SortedFill((function <int(BList&, BList&)>)[](BList& blist, BList& blist2)
                    { return blist.Illness >= blist2.Illness; }, head, tail, *(new BList(*blist)));
                break;
            default: break;
            }
        }

        in.close();

        if (!isEmpty(head))
            cout << endl
            << "Список сформирован" << endl << endl;
    }
    else cout << "Не удалось открыть файл" << endl;

    delete blist;
    blist = nullptr;
}

Node* FindInsertPlace(Node* head, BList& blist)
{
    Node* p = head;

    while (p)
    {
        if (blist == *p->data)
            break;
        p = p->next;
    }
    return p;
}

void SortedFill(function <bool(BList&, BList&)> val, Node*& head, Node*& tail, BList& blist)
{
    if (head)
    {
        if (val(blist, *head->data))
            AddToHead(head, tail, blist);
        else
        {
            Node* p = FindInsertPlace(head, blist);
            p ? AddBefore(head, *p->data, blist) :
                AddToTail(tail, head, blist);
        }
    }
    else AddToHead(head, tail, blist);
}

bool operator==(const BList& blist, const BList& blist2)
{
    return
        blist.FIO == blist2.FIO &&
        blist.Illness == blist2.Illness &&
        blist.OpenData == blist2.OpenData &&
        blist.WorkLessDays == blist2.WorkLessDays &&
        blist.WorkPlace == blist2.WorkPlace;
}

ostream& operator<<(ostream& out, const BList& blist)
{
    out << "ФИО " << blist.FIO << endl
        << "Место работы " << blist.WorkPlace << endl
        << "Болезнь " << blist.Illness << endl
        << "Дата открытия " << blist.OpenData << endl
        << "Безработные дни " << blist.WorkLessDays << endl << endl;
    return out;
}
