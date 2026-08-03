#pragma once
namespace StoreMenu{
    enum class MenuLevel{
        None,
        Main,
        Buy,
        Sell,
        Exit,
    };


    struct MenuAction{
            StoreMenu::MenuLevel menuLevel;
            int selectedIndex;
    };
}