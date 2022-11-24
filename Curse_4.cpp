#include <bits/stdc++.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#define kAuthorSize 12
#define kContentSize 32
#define kPublishingHouseSisze 16
#define N 4000

using namespace std;

struct record {
    char author_name[kAuthorSize];
    char content[kContentSize];
    char publishing_house[kPublishingHouseSisze];
    short int publish_year;
    short int list_count;
};

struct queue_q {
    record* q;
    queue_q* next;
};

struct Vertex {
    record* publish_year;
    Vertex *left, *right, *equal, *next;
    int Balance;
};

bool Rost = true;
bool Ymen = true;
bool HR = false, VR = false;

string key_S(record** ind, int q)
{
    string S1_content;
    int point = 0, tpoint = 0;
    point = 0;
    tpoint = 0;
    for (int j = 0; j < kContentSize; j++) {
        if (ind[q]->content[j] == ' ')
            point++;
        if (point == 2 && tpoint < 3) {
            S1_content += (ind[q]->content[j + 1]);
            tpoint++;
        }
    }
    return S1_content;
}

inline bool key(int q, int l, record** ind)
{
    if (key_S(ind, q) >= key_S(ind, l))
        return true;
    return false;
}

inline void heapPostr(record** ind, int l, int r)
{
    int i = l, j;
    ind[N] = ind[l];
    while (1) {
        j = i << 1;
        if (j > r)
            break;
        if (j < r && (key(j + 1, j, ind)))
            ++j;
        if (key(N, j, ind))
            break;
        ind[i] = ind[j];
        i = j;
    }
    ind[i] = ind[N];
}

inline void heapSort(record** ind, int n)
{
    int l = n >> 1, r = n;
    while (l + 1 > 0) {
        heapPostr(ind, l, r);
        --l;
    }
    while (r > 1) {
        swap(ind[0], ind[r - 1]);
        --r;
        heapPostr(ind, 0, r - 1);
    }
}

inline void print_20(record** ind, int j)
{
    system("CLS");
    cout << "Number" << setw(12) << " Author " << setw(32) << " Content "
         << setw(16) << " Publisher " << setw(10) << " Year " << setw(10)
         << "     Pages " << endl;
    for (int i = j; i < j + 20; i++) {
        cout << setw(4) << i + 1 << ")" << setw(12) << ind[i]->author_name
             << "  " << setw(32) << ind[i]->content << "  " << setw(16)
             << ind[i]->publishing_house << "  " << setw(10)
             << ind[i]->publish_year << "  " << setw(5) << ind[i]->list_count
             << endl;
    }
}

inline void print(record** ind)
{
    int key, j = 0;
    bool iteration = true;
    while (iteration) {
        cout << "Menu : 1 - continue| 2 - go end| 3 - go start| 4 - back | 5 - "
                "end"
             << endl;
        cout << ">>";
        cin >> key;
        switch (key) {
        case 1: {
            if (j != N - 20) {
                print_20(ind, j);
                j = j + 20;
            } else {
                cout << "Error: Out of bounds array" << endl;
            }
            break;
        }
        case 2: {
            print_20(ind, N - 20);
            j = N - 20;
            break;
        }
        case 3: {
            print_20(ind, 0);
            j = 20;
            break;
        }
        case 4: {
            if (j != 0) {
                print_20(ind, j - 20);
                j = j - 20;
            } else {
                cout << "Error: Out of bounds array" << endl;
            }
            break;
        }
        case 5: {
            cout << " >>END<<" << endl;
            ;
            iteration = false;
            break;
        }
        default:
            break;
        }
    }
}

inline int search_less(record** ind, string key, int M)
{
    string S1_content;
    int point = 0, tpoint = 0;
    point = 0;
    tpoint = 0;
    for (int j = 0; j < kContentSize; j++) {
        if (ind[M]->content[j] == ' ')
            point++;
        if (point == 2 && tpoint < 3) {
            S1_content += (ind[M]->content[j + 1]);
            tpoint++;
        }
    }
    if (key < S1_content)
        return -1;
    else if (key > S1_content)
        return 1;
    return 0;
}

inline int binsearch(record** ind, string key, int L, int R)
{
    int M;
    while (L < R) {
        M = (L + R) >> 1;
        if (search_less(ind, key, M) <= 0)
            R = M;
        else
            L = M + 1;
    }
    if (search_less(ind, key, L) == 0)
        return L;
    else
        return -1;
}

int asd = 0;

inline void B2insert(record* D, Vertex*& p)
{
    if (p == NULL) {
        p = new Vertex;
        p->publish_year = D;
        ++asd;
        p->equal = NULL;
        p->left = NULL;
        p->right = NULL;
        p->Balance = 0;
        VR = true;
    } else {
        if (D->publish_year < p->publish_year->publish_year) {
            B2insert(D, p->left);
            if (VR) {
                if (p->Balance == 0) {
                    Vertex* q = NULL;
                    q = p->left;
                    p->left = q->right;
                    q->right = p;
                    p = q;
                    q->Balance = 1;
                    VR = true;
                    HR = false;
                } else {
                    p->Balance = 0;
                    VR = true;
                    HR = false;
                }
            } else
                HR = false;
        } else if (D->publish_year > p->publish_year->publish_year) {
            B2insert(D, p->right);
            if (VR) {
                p->Balance = 1;
                HR = true;
                VR = false;
            } else {
                if (HR) {
                    if (p->Balance == 1) {
                        Vertex* q = NULL;
                        q = p->right;
                        p->Balance = 0;
                        q->Balance = 0;
                        p->right = q->left;
                        q->left = p;
                        p = q;
                        VR = true;
                        HR = false;
                    } else {
                        HR = false;
                    }
                }
            }

        } else if (D->publish_year == p->publish_year->publish_year)
            B2insert(D, p->equal);
    }
}

void ocered(queue_q*& p, int& t, record** ind, Vertex*& DBD)
{
    if (!p) {
        p = new queue_q;
        p->q = ind[t];
        B2insert(p->q, DBD);
        p->next = NULL;
    } else
        ocered(p->next, t, ind, DBD);
}

void Obhod(Vertex*& p)
{
    if (p) {
        Obhod(p->equal);
        Obhod(p->left);
        cout << setw(12) << p->publish_year->author_name << "  " << setw(32)
             << p->publish_year->content << "  " << setw(16)
             << p->publish_year->publishing_house << "  " << setw(10)
             << p->publish_year->publish_year << "  " << setw(5)
             << p->publish_year->list_count << endl;
        Obhod(p->right);
    }
}

void printQueue(queue_q*& p, int i)
{
    if (p) {
        cout << setw(12) << p->q->author_name << "  " << setw(32)
             << p->q->content << "  " << setw(16) << p->q->publishing_house
             << "  " << setw(10) << p->q->publish_year << "  " << setw(5)
             << p->q->list_count << endl;
        printQueue(p->next, i);
    }
}

void search(Vertex*& p, int& key)
{
    if (p) {
        if (p->publish_year->publish_year > key)
            search(p->left, key);
        else if (p->publish_year->publish_year < key)
            search(p->right, key);
        if (p->publish_year->publish_year == key) {
            search(p->equal, key);
            cout << setw(12) << p->publish_year->author_name << "  " << setw(32)
                 << p->publish_year->content << "  " << setw(16)
                 << p->publish_year->publishing_house << "  " << setw(10)
                 << p->publish_year->publish_year << "  " << setw(5)
                 << p->publish_year->list_count << endl;
        }
    }
}

void freeTree(Vertex* Tree)
{
    if (Tree) {
        freeTree(Tree->equal);
        freeTree(Tree->left);
        delete Tree;
        freeTree(Tree->right);
    }
}

inline void delQueue(queue_q*& p)
{
    queue_q* q;
    while (p) {
        q = p;
        p = p->next;
        delete q;
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    FILE* fp = fopen("testBase1.dat", "rb");
    record* mas = new record[N];
    record** ind = new record*[N];
    for (int i = 0; i < N; ++i)
        ind[i] = &mas[i];
    auto j = fread((record*)mas, sizeof(record), N, fp);
    cout << "Choose:" << endl
         << "1) Print" << endl
         << "2) Sort" << endl
         << "3) Key" << endl
         << "4) Coding(not implemented)" << endl
         << ">> ";
    int act;
    cin >> act;
    switch (act) {
    case 1: {
        print(ind);
        break;
    }
    case 2: {
        heapSort(ind, N);
        print(ind);
        break;
    }
    case 3: {
        heapSort(ind, N);
        string key;
        while (1) {
        retry:
            queue_q* root = NULL;
            Vertex* DBD = NULL;
            cout << "Input key: ";
            cin >> key;
            if (key == "-+")
                break;
            int t = binsearch(ind, key, 0, N - 1);
            if (t > -1)
                cout << "First element number is: " << t + 1 << endl;
            else {
                cout << "Element not found. ";
                goto retry;
            }
            asd = 0;
            for (int a = 0, i = t; i > -1 && i < 4000; ++i) {
                if (key_S(ind, i) != key)
                    break;
                ocered(root, i, ind, DBD);
            }
            Obhod(DBD);
            cout << "->" << asd << "<-" << endl;
            //			printQueue(root, t);

            while (1) {
                int key1;
                cout << "Enter search key: ";
                cin >> key1;
                if (key1 == -1)
                    break;
                search(DBD, key1);
            }
            freeTree(DBD);
            delQueue(root);
            delete root;
        }
        break;
    }
    default:
        break;
    }
}
