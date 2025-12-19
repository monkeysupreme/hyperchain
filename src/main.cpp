//
// Created by caleb on 12/18/25.
//

#include <CLI/CLI.hpp>
#include <iostream>

#include "wallet/wallet.h"

int main(int argc, char** argv)
{
    CLI::App app{"HyperChain Command Line"};
    argv = app.ensure_utf8(argv);

    // Require at least one module
    app.require_subcommand(1);

    // =================================================
    // WALLET MODULE
    // =================================================
    CLI::App* wallet = app.add_subcommand("wallet", "Wallet operations");

    // wallet create <name>
    CLI::App* wallet_create = wallet->add_subcommand("create", "Create a wallet");
    std::string wallet_name;

    wallet_create->add_option("name", wallet_name, "Wallet name")->required();

    wallet_create->callback([&]() {
        CWallet w(wallet_name);
        std::cout << "\n";
        std::cout << "Wallet created: " << wallet_name << "\n";
        std::cout << "\n";
        std::cout << "Annotation: " << wallet_name << "\n";
        std::cout << "Wallet data folder: " << "/" << wallet_name << "\n";
        std::cout << "Address: " << w.Information.Address << "\n";
        std::cout << "Secret key file: " << "wallet_name-?" << "\n";
        std::cout << "\n";
    });

    // =================================================
    // CHAIN MODULE
    // =================================================
    CLI::App* chain = app.add_subcommand("chain", "Blockchain operations");

    // chain info
    CLI::App* chain_info = chain->add_subcommand("info", "Show chain information");

    chain_info->callback([&]() {
        std::cout << "Chain info not implemented yet\n";
    });

    // =================================================
    // PARSE & EXECUTE
    // =================================================
    CLI11_PARSE(app, argc, argv);

    return 0;
}
