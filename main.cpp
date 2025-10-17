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

void remove(Node* node, int data) {
    if (head == nullptr) {
        return;
    }
    //if data is head
    if (data == head->data) {
        if (head->left == nullptr && head->right == nullptr) {
            Node* tmp = head;
            head = nullptr;
            delete tmp;
            return;
        }
        if (head->right == nullptr) {
            Node* tmp = head;
            head = head->left;
            delete tmp;
            return;
        }
        if (head->left == nullptr) {
            Node* tmp = head;
            head = head->right;
            delete tmp;
            return;
        }
        if (head->left != nullptr && head->right != nullptr) {
            Node* tmp = head;
            //>>> right branch only
            if (head->right->left == nullptr) {
                head->right->left = head->left;
                head = head->right;
                delete tmp;
                return;
            }
            if (head->right->left != nullptr) {
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
    //Search the data in all the tree:
    Node* tmp = node;
    Node* prev = nullptr;
    //Search the data Node*
    while (tmp != nullptr && tmp->data != data) {
        if (data < tmp->data) {
            prev = tmp;
            tmp = tmp->left;
        }
        if (data > tmp->data) {
            prev = tmp;
            tmp = tmp->right;
        }
    }
    //Data Node* is find.
    //DELETING PROCESS:
    //If data Node* it doesn't have leaves:
    if (tmp->right && tmp->left == nullptr) {
        if (prev->left == tmp) {
            delete prev->left;
        }
        if (prev->right == tmp) {
            delete prev->right;
        }
    }
    //If data Node* have leaves Only in Left:
    if (tmp->left != nullptr && tmp->right == nullptr) {
        if (prev->left == tmp) {
            prev->left == tmp->left;
            delete tmp;
        }
        if (prev->right == tmp) {
            prev->right = tmp->left;
            delete tmp;
        }
    }
    //If data Node* have leaves Only in Right:
    if (tmp->left == nullptr && tmp->right != nullptr) {
        if (prev->left == tmp) {
            prev->left = tmp->right;
            delete tmp;
        }
        if (prev->right == tmp) {
            prev->right = tmp->right;
            delete tmp;
            return;
        }
    }
    ////If data Node* have Left & Right leaves:
    if (tmp->left != nullptr && tmp->right != nullptr) {
        if (tmp->left->left == nullptr && tmp->left->right == nullptr && tmp->right->left == nullptr && tmp->right->right == nullptr) {
            //If it has only one generation
            if (prev->left == tmp) {
                prev->left = tmp->left;
                delete tmp;
                return;
            }
            if (prev->right == tmp) {
                prev->right = tmp->left;
                delete tmp;
                return;
            }
        }
        //If it has two and more generation of leaves
        //HAVE NOT TEST:
        if (tmp->left->left != nullptr || tmp->left->right != nullptr || tmp->right->left != nullptr || tmp->right->right != nullptr) {
            if (prev->left == tmp) {
                prev->left = tmp->left;
                delete tmp;
                return;
            }
            if (prev->right == tmp) {
                prev->right = tmp->left;
                delete tmp;
            }
        }
    }
    //If data Node* have full stack of leaves:
    else {
        Node* min = searchMin(tmp->right);
        if (prev->left == tmp) {
            prev->left = min;
            min->left = tmp->left;
            min->right = tmp->right;
            tmp->right->left = nullptr;
            delete tmp;
            return;
        }
        if (prev->right == tmp) {
            prev->right = min;
            min->left = tmp->left;
            min->right = tmp->right;
            tmp->right->left = nullptr;
            delete tmp;
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
int i = 0;
int arr[] = {};
void copyTree(Node* node) {
    if (node == nullptr) {
        return;
    }
    copyTree(node->left);
    arr[i] = node->data;
    std::cout << arr[i] << " ";
    i++;
    copyTree(node->right);
}

void deleteTree(Node* node) {
    if (node == nullptr) {
        return;
    }
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

void reBalanceQuick (Node* node) {
    int size = countLeft(node) + countRight(node);
    int mediana = size / 2;
    deleteTree(node);

    for (int i = mediana; i >= 0; i--) {
        add(arr[i]);
    }
    for (int i = mediana+1; i < size; i++) {
        add(arr[i]);
    }
}

void reBalance(Node* node) {
    if (isBalance(node))
        return;
    //определяю насколько смещен баланс дерева
    int left = countLeft(node);
    int right = countRight(node);
    int dif;
    Node* last = nullptr;
    if (left > right) {
        dif = left-right;
        Node* tmp = node;
        while (tmp->left != nullptr) {
            tmp = tmp->left;
            dif--;
            last = tmp;
            if (tmp->right != nullptr) {
                dif--;
                last = tmp->right;
                if (tmp->right->left != nullptr) {
                    dif--;
                    last = tmp->right->left;
                    if (tmp->right->left->left != nullptr) {
                        dif--;
                        last = tmp->right->left->left;
                    }
                    if (tmp->right->left->right != nullptr) {
                        dif--;
                        last = tmp->right->left->right;
                    }
                }
                if (tmp->right->right != nullptr) {
                    dif--;
                    last = tmp->right->right;
                    if (tmp->right->right->left != nullptr) {
                        dif--;
                        last = tmp->right->right->left;
                    }
                    if (tmp->right->right->right != nullptr) {
                        dif--;
                        last = tmp->right->right->right;
                    }
                }
            }
        }
    }
    if (right > left) {
        dif = right-left;
        Node* tmp = node;
        while (tmp->right != nullptr) {
            tmp = tmp->right;
            dif--;
            last = tmp->right;
            if (tmp->left != nullptr) {
                dif--;
                last = tmp->left;
                if (tmp->left->left != nullptr) {
                    dif--;
                    last = tmp->left->left;
                    if (tmp->left->left->left != nullptr) {
                        dif--;
                        last = tmp->left->left->left;
                    }
                    if (tmp->left->left->right != nullptr) {
                        dif--;
                        last = tmp->left->left->right;
                    }
                }
                if (tmp->left->right != nullptr) {
                    dif--;
                    last = tmp->left->right;
                    if (tmp->left->right->left != nullptr) {
                        dif--;
                        last = tmp->left->right->left;
                    }
                    if (tmp->left->right->right != nullptr) {
                        dif--;
                        last = tmp->left->right->right;
                    }
                }
            }
        }
    }
    Node* tmp = head;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    head->data = last->data;



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
    remove(head, 42);


    //searchMin(head);
    //searchMax(head);
    //Node* search  = searchData(head, 20);
    //std::cout << "data: " << search->data << " node ID: " << search << std::endl;


    //reBalance(head);
    //std::cout << L << std::endl;
    std::cout << countLeft(head) << std::endl;
    std::cout << countRight(head) << std::endl;


    copyTree(head);
   // for (int j = 0; j < sizeof(arr) / sizeof(arr[0]); j++) {
   //     std::cout << arr[j] << " ";
   // }
    std::cout << std::endl;
    std::cout << arr[2] << std::endl;
    //output(head);

    reBalanceQuick(head);
    std::cout << std::endl;
    output(head);
    return 0;
}