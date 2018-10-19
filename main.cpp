#include <iostream>
#include <deque>

using namespace std;


#define MAX_CLIENT 10


//Item b, número 1
typedef struct Cart {
    int id;
    string clientName;
    int numberOfProducts;
    double purchaseValue;
} Cart;

//ITEM B: QUESTÃO 2 E 3
deque<Cart> CAIXA_1;
deque<Cart> CAIXA_2;
deque<Cart> CAIXA_3;

int ID_COUNT = 0;

void menu();
void initDay();
void insertClient(Cart cart);
Cart enterCartInformation();
bool pushEnqueue1(Cart cart);
bool pushEnqueue2(Cart cart);
bool pushEnqueue3(Cart cart);
bool pushAutomatic(Cart cart);
void removeDaFila();
void calculoTotalDaFila();
void calculaTotal(deque<Cart> carts);
void print(deque<Cart> carts);
void printClients();


int main() {
    initDay();
    menu();
    return 0;
}


void menu() {

    int choice = -999999;

    cout << "--------------------" << endl;
    cout << "Main Menu - FIFO" << endl;
    cout << "--------------------" << endl << endl;


    cout << "[1] Insere cliente\n";
    cout << "[2] Remove cliente de uma fila\n";
    cout << "[3] Calcula total de uma determinada fila\n";
    cout << "[4] Print de uma determinada fila\n";
    cout << "[0] FINISH PROGRAM\n";

    cout << "Enter a valid option" << endl;
    cin >> choice;

    switch (choice) {

        case 0:
            return;
        case 1:
            insertClient(enterCartInformation());
            break;

        case 2:
            removeDaFila();
            break;

        case 3:
            calculoTotalDaFila();
            break;

        case 4:
            printClients();
            break;


        default:
            cout << "Invalid option. Try again..." << endl << endl;
    }

    menu();
}

void removeDaFila() {

    int number_fila = -999;
    cout << "De qual fila deseja remover? [1, 2 or 3]";
    cin >> number_fila;

    switch (number_fila) {

        case 1:
            if (!CAIXA_1.empty()) {
                CAIXA_1.pop_front();
            } else {
                cout << "CAIXA 1 JÁ ESTA VAZIO" << endl << endl;
            }
            break;

        case 2:
            if (!CAIXA_2.empty()) {
                CAIXA_2.pop_front();
            } else {
                cout << "CAIXA 2 JÁ ESTA VAZIO" << endl << endl;
            }
            break;

        case 3:
            if (!CAIXA_3.empty()) {
                CAIXA_3.pop_front();
            } else {
                cout << "CAIXA 3 JÁ ESTA VAZIO" << endl << endl;
            }
            break;

        default:
            cout << "Invalid Option..." << endl;
            removeDaFila();
    }
}

Cart enterCartInformation() {

    Cart cart;

    cart.id = ID_COUNT;
    cout << "Enter client name: ";
    cin >> cart.clientName;
    cout << "Enter numbers of products: ";
    cin >> cart.numberOfProducts;
    cout << "Enter Purchase Value: ";
    cin >> cart.purchaseValue;


    ++ID_COUNT;

    return cart;

}

void insertClient(Cart cart) {

    int choice = -9999;
    bool conseguiuInserir = false;


    cout << "Qual fila deseja entrar?" << endl;

    cout << "[1] FILA 1" << endl;
    cout << "[2] FILA 2" << endl;
    cout << "[3] FILA 3" << endl;
    cout << "[4] Automatic Choice" << endl;
    cout << "[0] Back" << endl;
    cin >> choice;

    switch (choice) {

        case 1:
            conseguiuInserir = pushEnqueue1(cart);
            break;

        case 2:
            conseguiuInserir = pushEnqueue2(cart);
            break;

        case 3:
            conseguiuInserir = pushEnqueue3(cart);
            break;

        case 4:
            conseguiuInserir = pushAutomatic(cart);
            break;

        default:
            cout << "Invalid Option. Try Again..." << endl << endl;

    }

    if (conseguiuInserir) {
        cout << "Legal! Você conseguiur entrar na fila de espera!" << endl;
        return;
    } else {
        cout << "Esta fila esta cheia. Tente outra ou volte mais tarde!" << endl;
        insertClient(cart);
    }

}

void initDay() {
    cout << "Init your job day..." << endl << endl;
    CAIXA_1.clear();
    CAIXA_2.clear();
    CAIXA_3.clear();
}

bool pushEnqueue1(Cart cart) {

    if (CAIXA_1.size() < MAX_CLIENT) {
        CAIXA_1.push_back(cart);
        return true;
    }

    return false;

}

bool pushEnqueue2(Cart cart) {

    if (CAIXA_2.size() < MAX_CLIENT) {
        CAIXA_2.push_back(cart);
        return true;
    }

    return false;

}

bool pushEnqueue3(Cart cart) {

    if (CAIXA_3.size() < MAX_CLIENT) {
        CAIXA_3.push_back(cart);
        return true;
    }

    return false;

}

bool pushAutomatic(Cart cart) {

    /**
     * 1. Verifica se Caixa 1 é a fila menor
     * 2. Verifica se Caixa 2 é a fila menor
     * 3. Verifica se Caixa 3 é a fila menor
     */
    if(CAIXA_1.size() <= CAIXA_2.size() && CAIXA_1.size() <= CAIXA_3.size()) {
        if (CAIXA_1.size() < MAX_CLIENT) {
            CAIXA_1.push_back(cart);
            return true;
        }
    } else if (CAIXA_2.size() <= CAIXA_1.size() && CAIXA_2.size() <= CAIXA_3.size()) {
        if (CAIXA_2.size() < MAX_CLIENT) {
            CAIXA_2.push_back(cart);
            return true;
        }
    } else if (CAIXA_3.size() <= CAIXA_1.size() && CAIXA_3.size() <= CAIXA_2.size()) {
        if (CAIXA_3.size() < MAX_CLIENT) {
            CAIXA_3.push_back(cart);
            return true;
        }
    }

    return false;


}

void calculoTotalDaFila() {


    int choice = -9999999;
    cout << "Qual caixa deseja calcular? [1,2 or 3]";
    cin >> choice;

    cout << "[1] FILA 1" << endl;
    cout << "[2] FILA 2" << endl;
    cout << "[3] FILA 3" << endl;
    cout << "[0] Back" << endl;

    switch (choice) {
        case 0:
            return;
        case 1:
            calculaTotal(CAIXA_1);
            break;

        case 2:
            calculaTotal(CAIXA_2);
            break;

        case 3:
            calculaTotal(CAIXA_3);
            break;

        default:
            cout << "Invalid Option..." << endl;
            calculoTotalDaFila();
    }

}

void calculaTotal(deque<Cart> carts) {

    double total = 0;
    if (!carts.empty()) {
        for (deque<Cart>::iterator it = carts.begin(); it != carts.end(); ++it) {
            total += it->purchaseValue;
        }
    }

    cout << "O total dessa fila é R$" << total << endl << endl;
}

void printClients() {

    int escolha;

    cout << "Qual fila deseja imprimir" << endl;
    cout << "[1] FILA 1" << endl;
    cout << "[2] FILA 2" << endl;
    cout << "[3] FILA 3" << endl;
    cout << "[0] Back" << endl;
    cin >> escolha;

    switch (escolha) {
        case 0:
            return;
        case 1:
            print(CAIXA_1);
            break;
        case 2:
            print(CAIXA_2);
            break;
        case 3:
            print(CAIXA_3);
            break;
        default:
            cout << "Invalid Option. Try Again..." << endl << endl;
            printClients();

    }

}

void print(deque<Cart> carts) {
    if (!carts.empty()) {
        cout << "\n\n--------------" << endl;
        for (deque<Cart>::iterator it = carts.begin(); it != carts.end(); ++it) {
            cout << "ID: " << it->id << endl;
            cout << "CLIENT: " << it->clientName << endl;
            cout << "QUANTIDADE DE PRODUTOS: " << it->numberOfProducts << endl;
            cout << "TOTAL: " << (it->purchaseValue) << endl;
            cout << "--------------\n\n" << endl;
        }
    } else {
        cout << "Seu caixa esta vazio" << endl;
    }
}