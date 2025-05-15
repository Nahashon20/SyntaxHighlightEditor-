#include "undo_redo.h"
#include <iostream>
#include "action.h"

void UndoRedoManager::recordInsert(int row, const std::string& line) {
    undoStack.push({ActionType::Insert, row, "", line});
    while (!redoStack.empty()) redoStack.pop();
}

void UndoRedoManager::recordDelete(int row, const std::string& line) {
    undoStack.push({ActionType::Delete, row, line, ""});
    while (!redoStack.empty()) redoStack.pop();
}

void UndoRedoManager::recordCursorMove(int prevRow, int prevCol) {
    undoStack.push({ActionType::CursorMove, 0, "", "", prevRow, prevCol});
    while (!redoStack.empty()) redoStack.pop();
}

void UndoRedoManager::undo(TextBuffer& buffer) {
    if (undoStack.empty()) {
        std::cout << "Nothing to undo.\n";
        return;
    }

    Action action = undoStack.top();
    undoStack.pop();
    redoStack.push(action);

    switch (action.type) {
        case ActionType::Insert:
            buffer.deleteLine(action.lineIndex);
            break;
        case ActionType::Delete:
            buffer.insertLine(action.lineIndex, action.oldText);
            break;
        case ActionType::Edit:
            buffer.editLine(action.lineIndex, action.oldText);
            break;
        case ActionType::CursorMove:
            buffer.moveCursor(action.prevRow, action.prevCol);
            break;
    }
}

void UndoRedoManager::redo(TextBuffer& buffer) {
    if (redoStack.empty()) {
        std::cout << "Nothing to redo.\n";
        return;
    }

    Action action = redoStack.top();
    redoStack.pop();
    undoStack.push(action);

    switch (action.type) {
        case ActionType::Insert:
            buffer.insertLine(action.lineIndex, action.newText);
            break;
        case ActionType::Delete:
            buffer.deleteLine(action.lineIndex);
            break;
        case ActionType::Edit:
            buffer.editLine(action.lineIndex, action.newText);
            break;
        case ActionType::CursorMove:
            buffer.moveCursor(action.prevRow, action.prevCol);
            break;
    }
}