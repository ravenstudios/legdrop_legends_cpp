#pragma once

enum class BattleMenuAction{
    None,
    Attack,
    Item,
    Tag,
    Run
};

struct BattleCommand {
    BattleMenuAction type = BattleMenuAction::None;
    int selectionIndex;
};
