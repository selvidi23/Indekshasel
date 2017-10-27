/*Zadanie polega na utworzeniu i wyświetleniu indeksu haseł występujących w podanym tekście. Indeks haseł jest to lista haseł wraz z wykazem linii, w których pojawia się dane hasło.

Hasła w wykazie mają być uporządkowane alfabetycznie, zaś linie rosnąco. W hasłach dopuszczane są tylko znaki alfabetu angielskiego oraz cyfry. Numery linii są liczbami naturalnymi (>0). Każde hasło występuje w indeksie tylko raz. Numery linii w wykazie linii pojedynczego hasła nie mogą się powtarzać.

Strukturami umożliwiającymi realizację tego zadania mają być binarne drzewa wyszukiwania oraz ewentualnie lista liniowa. Należy samodzielnie zaimplementować te struktury.

UWAGA: Nie można wykorzystywać gotowych struktur i algorytmów.

Bardziej szczegółowo:

program w pierwszym wierszu otrzymuje liczbę linii tekstu do przetworzenia,
następnie w każdym nowym wierszu otrzymuje linię tekstu złożoną z liczby wyrazów w tej linii oraz z kolejnych wyrazów (elementy linii są oddzielone spacjami),
program powinien przetworzyć kolejno wszystkie linie tekstu a następnie wyświetlić opisany wyżej indeks haseł,
        każdy wpis w indeksie haseł powinien mieć postać:
        hasło => lista_numerów_linii
        Przykład 1

Wejście:

4
5 Adam Beata Celina Jan Zofia
2 Leokadia Beata
1 Zofia
1 Adam
        Wyjście:

Adam => 1 4
Beata => 1 2
Celina => 1
Jan => 1
Leokadia => 2
Zofia => 1 3
Przykład 2

Wejście:

5
3 a b c
2 a a
2 b a
4 c b d a
3 b b d
        Wyjście:

a => 1 2 3 4
b => 1 3 4 5
c => 1 4
d => 4 5
*/


#include <iostream>

using namespace std;

class LinesList {
    struct Node {
        int data;
        Node * next;
    };

    Node* start;
    Node* end;
    int count;

public:
    LinesList() {
        start = NULL;
        end = NULL;
        count = 0;
    }

    void add(int line) {
        if (start != NULL and line == end->data) {
            return;
        }
        Node* tmp = new Node();
        tmp->data = line;
        tmp->next = NULL;

        if (isEmpty()) {
            start = end = tmp;
        } else {
            end->next = tmp;
            end = tmp;
        }

        count++;
    }

    void print() {
        Node * n = start;
        while(n != NULL) {
            cout << n->data << " ";
            n = n->next;
        }
    }

    bool isEmpty()
    {
        return count == 0 ? true : false;
    }
};

class StringTree{

    class TreeNode{
        friend class StringTree;
        string str;
        LinesList lines;
        TreeNode *left;
        TreeNode *right;
        TreeNode(string s, TreeNode *l=NULL, TreeNode *r=NULL){
            str=s, left=l, right=r;
            LinesList lines;
        }
    };
    TreeNode *root;

    void insert(TreeNode *&tree, string word, int line);
    void displayInOrder(TreeNode *tree);

public:
    StringTree()
    {
        root=NULL;
    }

    void showInOrder(void)
    {
        displayInOrder(root);
    }
    void insert(string word, int line);
};

void StringTree::insert(string word, int line)
{
    insert(root, word, line);
}


void StringTree::insert(TreeNode *&tree, string word, int line) {
    if (!tree) {
        tree = new TreeNode(word);
        tree->lines.add(line);
        return;
    }

    if (tree->str.compare(word) == 0){
        tree->lines.add(line);
        return;
    }
    if (tree->str.compare(word) < 0) {
        insert(tree->right, word, line);
    } else {
        insert(tree->left, word, line);

    }
}


void StringTree::displayInOrder(TreeNode *tree){
    if(tree){
        displayInOrder(tree->left);
        cout << tree->str << " => ";
        tree->lines.print();
        cout << "\n";
        displayInOrder(tree->right);
    }
}

int main(int argc, char* argv[]) {

    int liczbalini;
    int liczbasl;

    StringTree drzewo;
    string token;

    scanf("%d",&liczbalini);
    for(int i =1;i<liczbalini+1;i++)
    {
        scanf("%d",&liczbasl);
        for(int j =0 ;j<liczbasl;j++){
            cin>>token;
            drzewo.insert(token,i);
        }

    }


    drzewo.showInOrder();
    return 0;
}