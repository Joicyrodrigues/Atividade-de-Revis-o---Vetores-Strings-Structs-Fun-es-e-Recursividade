#include <iostream>
#include <string.h>
#include <iomanip>
#include <locale.h>

#define MAX_ATIVOS 100

using namespace std;

typedef struct {
    char ticket[7];
    int quantidade;
    double preco_medio;
} Ativo;

Ativo patrimonio[MAX_ATIVOS];
int num_ativos = 0;

void registrar_compra();
void registrar_venda();
void ver_saldo();
void listar_patrimonio();
int buscar_ativo(char ticket[]);
int buscar_ativo_binaria(int inicio, int fim, char ticket[]);
void ordenar_ativos();

int main() {

    setlocale(LC_ALL,"portuguese");

    int opcao;

    do {
        system("cls");
        cout<<"Menu:"<<endl;
        cout<<"1. Registrar compra"<<endl;
        cout<<"2. Registrar venda"<<endl;
        cout<<"3. Ver saldo de um ativo"<<endl;
        cout<<"4. Listar patrimônio"<<endl;
        cout<<"5. Sair"<<endl;
        cout<<"Escolha uma opção: ";
        cin>>opcao;

        switch(opcao) {
            case 1:
                system("cls");
                registrar_compra();
                system("pause");
                break;
            case 2:
                system("cls");
                registrar_venda();
                system("pause");
                break;
            case 3:
                system("cls");
                ver_saldo();
                system("pause");
                break;
            case 4:
                system("cls");
                listar_patrimonio();
                system("pause");
                break;
            case 5:
                system("cls");
                cout<<"Saindo...\n";
                system("pause");
                break;
            default:
                system("cls");
                cout<<"Opção inválida! Tente novamente.\n";
                system("pause");
        }
    } while(opcao != 5);

    return 0;
}

void registrar_compra() {
    char ticket[7];
    int quantidade;
    double valor;

    cout<<"Ticket (max 6 letras): ";
    cin>>ticket;
    cout<<"Quantidade comprada: ";
    cin>>quantidade;
    cout<<"Valor do ativo na compra: ";
    cin>>valor;
    cout<<endl;

    int idx = buscar_ativo(ticket);

    if (idx == -1) {

        strcpy(patrimonio[num_ativos].ticket, ticket);
        patrimonio[num_ativos].quantidade = quantidade;
        patrimonio[num_ativos].preco_medio = valor;
        num_ativos++;
        ordenar_ativos();
    } else {

        int total_quantidade = patrimonio[idx].quantidade + quantidade;
        patrimonio[idx].preco_medio = ((patrimonio[idx].preco_medio * patrimonio[idx].quantidade) + (valor * quantidade)) / total_quantidade;
        patrimonio[idx].quantidade = total_quantidade;
    }

    cout<<"Compra registrada com sucesso!\n"<<endl;
}

void registrar_venda() {
    char ticket[7];
    int quantidade;
    double valor;

    cout<<"Ticket (max 6 letras): ";
    cin>>ticket;
    cout<<"Quantidade vendida: ";
    cin>>quantidade;

    int idx = buscar_ativo(ticket);

    if (idx == -1) {
        cout<<"\nAtivo não encontrado!\n"<<endl;
    } else if (patrimonio[idx].quantidade < quantidade) {
        cout<<"\nSaldo insuficiente para venda!\n"<<endl;
    } else {
        patrimonio[idx].quantidade -= quantidade;
        cout<<"\nVenda registrada com sucesso!\n"<<endl;
    }
}

void ver_saldo() {
    char ticket[7];
    cout<<"Ticket (max 6 letras): ";
    cin>>ticket;

    int idx = buscar_ativo(ticket);

    if (idx == -1) {
        cout<<"Ativo não encontrado!\n";
    } else {
        cout<<"Ticket: "<<patrimonio[idx].ticket<<"\n";
        cout<<"Quantidade: "<<patrimonio[idx].quantidade<<"\n";
        cout<<"Preço médio: "<<patrimonio[idx].preco_medio<<"\n"<<endl;
    }
}

void listar_patrimonio() {
    if (num_ativos == 0) {
        cout<<"Nenhum ativo registrado!\n"<<endl;
    } else {
        cout<<"Patrimônio:\n";
        for (int i = 0; i < num_ativos; i++) {
            cout<<"Ticket: "<<patrimonio[i].ticket<<"\nQuantidade: "<<patrimonio[i].quantidade<<"\nPreço médio: "<<patrimonio[i].preco_medio<<"\n"<<endl;
        }
    }
}

int buscar_ativo(char ticket[]) {
    return buscar_ativo_binaria(0, num_ativos - 1, ticket);
}

int buscar_ativo_binaria(int inicio, int fim, char ticket[]) {
    if (inicio > fim) {
        return -1;
    }

    int meio = (inicio + fim) / 2;
    int cmp = strcmp(patrimonio[meio].ticket, ticket);

    if (cmp == 0) {
        return meio; // Encontrado
    } else if (cmp > 0) {
        return buscar_ativo_binaria(inicio, meio - 1, ticket);
    } else {
        return buscar_ativo_binaria(meio + 1, fim, ticket);
    }
}

void ordenar_ativos() {
    Ativo temp;
    for (int i = 0; i < num_ativos - 1; i++) {
        for (int j = i + 1; j < num_ativos; j++) {
            if (strcmp(patrimonio[i].ticket, patrimonio[j].ticket) > 0) {
                temp = patrimonio[i];
                patrimonio[i] = patrimonio[j];
                patrimonio[j] = temp;
            }
        }
    }
}
