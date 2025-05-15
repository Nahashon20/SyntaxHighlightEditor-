#ifndef UNDO_REDO_H
#define UNDO_REDO_H

#include "action.h" // Include centralized ActionType and Action definitions
#include "text_buffer.h"
#include <stack>
#include <string>

class UndoRedoManager {
public:
    void recordInsert(int row, const std::string& line);
    void recordDelete(int row, const std::string& line);
    void recordCursorMove(int prevRow, int prevCol);

    void undo(TextBuffer& buffer);
    void redo(TextBuffer& buffer);

private:
    std::stack<Action> undoStack;
    std::stack<Action> redoStack;
};

#endif