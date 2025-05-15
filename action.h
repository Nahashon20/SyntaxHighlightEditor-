#ifndef ACTION_H
#define ACTION_H

#include <string>

enum class ActionType {
    Insert,
    Delete,
    Edit,
    CursorMove
};

struct Action {
    ActionType type;
    int lineIndex;             // Line index for Insert/Delete/Edit
    std::string oldText;       // Old text for Edit/Delete
    std::string newText;       // New text for Edit/Insert
    int prevRow = 0;           // Previous row for CursorMove
    int prevCol = 0;           // Previous column for CursorMove

    // Constructor
    Action(ActionType type, int lineIndex, const std::string& oldText = "", const std::string& newText = "", int prevRow = 0, int prevCol = 0)
        : type(type), lineIndex(lineIndex), oldText(oldText), newText(newText), prevRow(prevRow), prevCol(prevCol) {}
};

#endif