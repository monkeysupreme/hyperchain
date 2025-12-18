#include "wallet/wallet.h"
int main()
{
    CWallet wallet = CWallet("mycoolwallet");
    wallet.Dump();
}
