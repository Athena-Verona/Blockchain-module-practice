#include "main.h"

int main() {
    vector<user> Users;
    gen_user(Users);
    vector<transaction> Transactions;
    gen_trans(Users, Transactions);
    cout << Transactions[0];
}