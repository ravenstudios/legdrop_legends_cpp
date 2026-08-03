#pragma once
namespace PauseMenu{
    enum class MenuLevel{
        None,
        Main,
        Settings,
        Items,
        Roster
    };
}

struct MenuAction{
        PauseMenu::MenuLevel menuLevel;
        int selectedIndex;
};
