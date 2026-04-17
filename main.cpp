#include "includes.hpp"
#include <iostream>
#include <thread>

void main() {
    Sleep(500);
    {
        printf("Waiting for Fortnite...");

        while (game_wnd == 0)
        {
            Sleep(1);
            processID = mem::find_process(L"FortniteClient-Win64-Shipping.exe");
            game_wnd = get_process_wnd(processID);
            Sleep(1);
        }

        system("cls");
        printf("Fn Base - By quotesoditaly");
        printf("Menu Key: INS");

        if (!input::init())
        {
            printf("The input was not initialized");
            Sleep(3000);
            exit(0);
        }

        if (!gui::init())
        {
            printf("The gui was not initialized");
            exit(0);
        }

        if (!mem::find_driver())
        {
            printf("The driver was not initialized");
            Sleep(3000);
            exit(0);
        }

        if (!mem::fetch_cr3())
        {

        }

        Base = mem::find_image();

        if (!Base)
        {
            printf("The driver couldn't get the base address");
            Sleep(3000);
            exit(0);
        }

        create_overlay();
        directx_init();
        config_system::refresh();
        render_loop();
    }
}
