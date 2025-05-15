#include "text_buffer.h"
#include "syntax_highlighter.h"
#include <iostream>

TextBuffer::TextBuffer() : cursorLine(0), cursorColumn(0) {}

int TextBuffer::getCursorLine() const {
    return cursorLine;
}

void TextBuffer::addLine(const std::string& line) {
    lines.push_back(line);
    recordAction(ActionType::Insert, lines.size() - 1, "", line);
}

void TextBuffer::insertLine(int index, const std::string& line) {
    if (index >= 0 && index <= static_cast<int>(lines.size())) {
        lines.insert(lines.begin() + index, line);
        recordAction(ActionType::Insert, index, "", line);
    }
}

void TextBuffer::deleteLine(int index) {
    if (index >= 0 && index < static_cast<int>(lines.size())) {
        std::string oldText = lines[index];
        lines.erase(lines.begin() + index);
        recordAction(ActionType::Delete, index, oldText, "");
    }
}

void TextBuffer::editLine(int index, const std::string& newText) {
    if (index >= 0 && index < static_cast<int>(lines.size())) {
        std::string oldText = lines[index];
        lines[index] = newText;
        recordAction(ActionType::Edit, index, oldText, newText);
    }
}

void TextBuffer::moveCursor(int line, int column) {
    if (line >= 0 && line < static_cast<int>(lines.size())) {
        cursorLine = line;
    } else {
        std::cout << "Invalid line number.\n";
    }

    if (column >= 0 && column <= static_cast<int>(lines[cursorLine].size())) {
        cursorColumn = column;
    } else {
        std::cout << "Invalid column number.\n";
    }
}

void TextBuffer::moveCursorUp() {
    if (cursorLine > 0) cursorLine--;
}

void TextBuffer::moveCursorDown() {
    if (cursorLine < static_cast<int>(lines.size()) - 1) cursorLine++;
}

void TextBuffer::moveCursorLeft() {
    if (cursorColumn > 0) cursorColumn--;
}

void TextBuffer::moveCursorRight() {
    if (cursorColumn < static_cast<int>(lines[cursorLine].size())) cursorColumn++;
}

void TextBuffer::showCursorPosition() const {
    std::cout << "Cursor at line: " << cursorLine << ", column: " << cursorColumn << std::endl;
}

void TextBuffer::display(const std::string& language) const {
    for (const auto& line : lines) {
        std::cout << applySyntaxHighlighting(line, language) << std::endl;
    }
}

const std::vector<std::string>& TextBuffer::getLines() const {
    return lines;
}

void TextBuffer::recordAction(ActionType type, int lineIndex, const std::string& oldText, const std::string& newText) {
    undoStack.push({ type, lineIndex, oldText, newText });
    // Clear redo stack when new action is made
    while (!redoStack.empty()) redoStack.pop();
}
void TextBuffer::undo() {
    if (undoStack.empty()) {
        std::cout << "Nothing to undo.\n";
        return;
    }

    Action action = undoStack.top();
    undoStack.pop();
    redoStack.push(action);

    switch (action.type) {
        case ActionType::Insert:
            lines.erase(lines.begin() + action.lineIndex);
            break;
        case ActionType::Delete:
            lines.insert(lines.begin() + action.lineIndex, action.oldText);
            break;
        case ActionType::Edit:
            lines[action.lineIndex] = action.oldText;
            break;
        case ActionType::CursorMove: // Handle CursorMove
            moveCursor(action.prevRow, action.prevCol);
            break;
    }
}

void TextBuffer::redo() {
    if (redoStack.empty()) {
        std::cout << "Nothing to redo.\n";
        return;
    }

    Action action = redoStack.top();
    redoStack.pop();
    undoStack.push(action);

    switch (action.type) {
        case ActionType::Insert:
            lines.insert(lines.begin() + action.lineIndex, action.newText);
            break;
        case ActionType::Delete:
            lines.erase(lines.begin() + action.lineIndex);
            break;
        case ActionType::Edit:
            lines[action.lineIndex] = action.newText;
            break;
        case ActionType::CursorMove: // Handle CursorMove
            moveCursor(action.prevRow, action.prevCol);
            break;
    }
}

void TextBuffer::clear() {
    lines.clear();
    cursorLine = 0;
    cursorColumn = 0;
}

void TextBuffer::search(const std::string& keyword) const {
    bool found = false;
    for (size_t i = 0; i < lines.size(); ++i) {
        if (lines[i].find(keyword) != std::string::npos) {
            std::cout << "Line " << i << ": " << lines[i] << std::endl;
            found = true;
        }
    }
    if (!found) {
        std::cout << "No match found for \"" << keyword << "\".\n";
    }
}

