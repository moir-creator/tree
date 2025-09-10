#include <iostream>
#include <cmath>

struct Node {
    Node* left;
    int data;
    Node* right;
};

Node* head = nullptr;
int countL = 0;
int countR = 0;

//Методы проекта:
/*
add - создает узел (без рекурсии)
addRecursive - создает узел (рекурсивно)
isBalance - проверяет сбалансировано ли дерево (без рекурсии)
searchData - поиск узла, пишет путь left/right (без рекурсии)
searchMin, searchMax - ищет крайний минимальный и максимальный узел, выводит адрес узла (рекурсивно)
remove - незавершен; удаляет узел; (с рекурсией и без)
reBalance -

 */

void add(int data) {
    if (head == nullptr) {
        head = new Node(nullptr, data, nullptr);
        return;
    }
    Node* tmp = head;
    Node* prev = nullptr;
    while (tmp != nullptr) {
        if (data > tmp->data) {
            prev = tmp;
            tmp = tmp->right;
        }
        else {
            prev = tmp;
            tmp = tmp->left;
        }
    }
    if (data > prev->data) {
        prev->right = new Node(nullptr, data, nullptr);
    }
    else {
        prev->left = new Node(nullptr, data, nullptr);
    }
}

void addRecursive(Node* node, int data) {
    if (head == nullptr) {
        head = new Node(nullptr, data, nullptr);
        return;
    }
    if (data < node->data && node->left == nullptr) {
        node->left = new Node(nullptr, data, nullptr);
        return;
    }
    if (data > node->data && node->right == nullptr) {
        node->right = new Node(nullptr, data, nullptr);
        return;
    }
    if (data < node->data && node->left != nullptr) {
        addRecursive (node->left, data);
    }
    if (data > node->data && node->right != nullptr) {
        addRecursive (node->right, data);
    }
}

Node* searchMin(Node* node) {
    if (node == nullptr) {
        return nullptr;
    }
    if (node->left == nullptr) {
        std::cout << "Minimal value is: " << node->data << "." << std::endl;
        return node;
    }
    return searchMin(node->left);
}

Node* searchMax(Node* node) {
    if (node == nullptr) {
        return nullptr;
    }
    if (node->right == nullptr) {
        std::cout << "Maximal value is: " << node->data << "." << std::endl;
        return node;
    }
    return searchMax(node->right);
}

void remove(int data) {
    if (head == nullptr) {
        return;
    }
    if (data == head->data) {
        if (head->left == nullptr && head->right == nullptr) {
            Node* tmp = head;
            head = nullptr;
            delete tmp;
        }
        if (head->right == nullptr) {
            Node* tmp = head;
            head = head->left;
            delete tmp;
        }
        if (head->left == nullptr) {
            Node* tmp = head;
            head = head->right;
            delete tmp;
        }
        if (head->left != nullptr && head->right != nullptr) {
            Node* tmp = head;
            if (head->right->left == nullptr) {
                head->right->left = head->left;
                head = head->right;
                delete tmp;
                return;
            }
            if (head->right->left != nullptr) {
               Node* tmp = head;
               Node* minValue = searchMin(head->right->left);

               Node* prev = head->right->left;
               while (prev->left->data != minValue->data) {
                   prev = prev->left;
               }
               if (prev->left->right == nullptr)
                   prev->left = nullptr;
               if (prev->left->right != nullptr) {
                   prev->left = prev->left->right;
                   minValue->right = head->right;
               }
               minValue->left = head->left;
               head = minValue;
               delete tmp;
               return;
            }
        }
    }
    //НЕДОРАБОТАН!!! НЕДОРАБОТАН!!! НЕДОРАБОТАН!!! НЕДОРАБОТАН!!!
}

//метод поиска возвращает и сам адрес нужного узла
Node* searchDataLink(Node* node, int data) {
    Node* tmp = node;
    if (data > node->data) {
        while (tmp != nullptr && tmp->data != data) {
            if (data > tmp->left->data) {
                std::cout << "Right ";
                tmp = tmp->right;
            }
            if (tmp->data > data) {
                std::cout << "Left ";
                tmp = tmp->left;
            }
        }
        return tmp;
    }
    if (data < node->data) {
        while (tmp != nullptr && tmp->data != data) {
            if (data < tmp->right->data) {
                std::cout << "Left ";
                tmp = tmp->left;
            }
            if (tmp->data < data) {
                std::cout << "Right ";
                tmp = tmp->right;
            }
        }
        return tmp;
    }

    std::cout << ": ";
    std::cout << "Data " << tmp->data << " was found" << std::endl;
}

int searchData(Node* node, int data) {
    Node* tmp = node;
    int countL = 0;
    int countR = 0;
    if (data > node->data) {
        while (tmp != nullptr && tmp->data != data) {
            if (data > tmp->left->data) {
                std::cout << "Right ";
                tmp = tmp->right;
                countL += 1;
            }
            if (tmp->data > data) {
                std::cout << "Left ";
                tmp = tmp->left;
                countL += 1;
            }
        }
        return countL;
    }
    if (data < node->data) {
        while (tmp != nullptr && tmp->data != data) {
            if (data < tmp->right->data) {
                std::cout << "Left ";
                tmp = tmp->left;
                countR += 1;
            }
            if (tmp->data < data) {
                std::cout << "Right ";
                tmp = tmp->right;
                countR += 1;
            }
        }
        return countR;
    }

    std::cout << ": ";
    std::cout << "Data " << tmp->data << " was found" << std::endl;
}

int countLeft (Node* node) {
    if (node == nullptr) {
        return 0;
    }
    Node* tmp = node;
    int countLeft = 0;
    while (tmp->left != nullptr) {
        tmp = tmp->left;
        countLeft += 1;
        if (tmp->right != nullptr) {
            countLeft += 1;
            if (tmp->right->left != nullptr) {
                countLeft += 1;
                if (tmp->right->left->left != nullptr) {
                    countLeft += 1;
                }
                if (tmp->right->left->right != nullptr) {
                    countLeft += 1;
                }
            }
            if (tmp->right->right != nullptr) {
                countLeft += 1;
                if (tmp->right->right->left != nullptr) {
                    countLeft += 1;
                }
                if (tmp->right->right->right != nullptr) {
                    countLeft += 1;
                }
            }
        }
    }
    return countLeft;
}

int countRight (Node* node) {
    Node* tmp = node;
    int countRight = 0;
    while (tmp->right != nullptr) {
        tmp = tmp->right;
        countRight += 1;
        if (tmp->left != nullptr) {
            countRight += 1;
            if (tmp->left->left != nullptr) {
                countRight += 1;
                if (tmp->left->left->left != nullptr) {
                    countRight += 1;
                }
                if (tmp->left->left->right != nullptr) {
                    countRight += 1;
                }
            }
            if (tmp->left->right != nullptr) {
                countRight += 1;
                if (tmp->left->right->left != nullptr) {
                    countRight += 1;
                }
                if (tmp->left->right->right != nullptr) {
                    countRight += 1;
                }
            }
        }
    }
    return countRight;
}

int isBalance(Node* node) {
    if (node == nullptr) {
        return 0;
    }
    int left = countLeft(head);
    int right = countRight(head);
    int dif;
    std::cout << "CountLeft " << left << std::endl;
    std::cout << "CountRight " << right << std::endl;

    if (left > right) {
        dif = left/right;
    }
    if (right > left) {
        dif = right/left;
    }
    //int dif = std::abs(countLeft - countRight);
    if ( dif <= 2) {
        std::cout << "The tree is balanced." << std::endl;
        return 1;
    }
    else {
        std::cout << "The tree is not balanced." << std::endl;
        return 0;
    }
}

void output(Node* node) {
    if (node == nullptr) {
        return;
    }
    output(node->left);
    std::cout << node->data << " ";
    output(node->right);
}



void reBalance(Node* node) {
    if (isBalance(node))
        return;
    //определяю насколько смещен баланс дерева
    int left = countLeft(node);
    int right = countRight(node);
    int dif;
    if (left > right) {
        dif = left/right;
    }
    if (right > left) {
        dif = right/left;
    }
    //определяю в какую сторону смещать указатель для нового head
    Node* tmp = node;
    for (int i = 0; i < dif-1; i++ ) {
        if (left > right)
            tmp = tmp->left;
        if (right > left)
            tmp = tmp->right;
    }
    //как теперь создать дерево заново?
    Node* t= tmp;
    Node* thead = node;
    head = nullptr;
    //НЕДОРАБОТАН!!! НЕДОРАБОТАН!!! НЕДОРАБОТАН!!! НЕДОРАБОТАН!!!
}

//++ еще один add рекурсивный
//метод который делает ребалансировку дерева
//remove (и через рекурсию и не через рекурсию)
//++isBalance метод проверки сбалансированное дерево или нет (возвращает не bool а число)
//++ нахождение элементов в дереве (выводил все элементы встреченные на пути) указывать left или right

int main() {
    /*add(10);
    add(8);
    add(9);
    add(14);
    add(12);
    add(16);
    add(4);*/

    /*add(12);
    add(10);
    add(11);
    add(8);
    add(9);
    add(3);
    add(14);
    add(13);
    add(15);
    add(18);
    add(17);
    add(16);
    add(4);*/

    addRecursive(head, 26);
    addRecursive(head, 18);
    addRecursive(head, 36);
    //addRecursive(head, 12);
    addRecursive(head, 22);

    addRecursive(head, 30);
    addRecursive(head, 28);
    addRecursive(head, 34);
    addRecursive(head, 29);

    addRecursive(head, 48);
    addRecursive(head, 20);
    addRecursive(head, 24);

    //addRecursive(head, 6);
    //addRecursive(head, 15);
    addRecursive(head, 42);

    //addRecursive(head, 14);
    //addRecursive(head, 17);
    addRecursive(head, 38);
    addRecursive(head, 46);

    //addRecursive(head, 8);
    //addRecursive(head, 7);
    //addRecursive(head, 10);
    //addRecursive(head, 4);

    addRecursive(head, 64);
    addRecursive(head, 58);
    addRecursive(head, 54);
    addRecursive(head, 62);
    addRecursive(head, 80);
    remove(26);


    //searchMin(head);
    //searchMax(head);
    //Node* search  = searchData(head, 20);
    //std::cout << "data: " << search->data << " node ID: " << search << std::endl;


    //reBalance(head);
    //std::cout << L << std::endl;
    countLeft(head);
    countRight(head);

    output(head);
    return 0;
}