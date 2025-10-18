#pragma once

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
    Node* next, *prev;
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
void FillFromFile(Node*& head, Node*& tail);
template<class T>
void SortedFill(function <T(BList&)> val, Node*& head, Node*& tail, BList& blist)
{
    if (head)
    {
        if (val(blist) >= val(*head->data))
            AddToHead(head, tail, blist);
        else
        {
            Node* p = FindInsertPlace(val, head, blist);
            p ? AddBefore(head, *p->data, blist) :
                AddToTail(tail, head, blist);
        }
    }
    else AddToHead(head, tail, blist);
}
template<class T>
Node* FindInsertPlace(function <T(BList&)> val, Node* head, BList& blist)
{
    Node* p = head;

    while (p)
    {
        if (val(blist) > val(*p->data))
            break;
        p = p->next;
    }
    return p;
}
ostream& operator<<(ostream& out, const BList& blist);
