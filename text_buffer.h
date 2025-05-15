#ifndef TEXT_BUFFER_H
#define TEXT_BUFFER_H

#include <vector>
#include <string>
#include <stack>
#include "action.h"

class TextBuffer {
public:
    TextBuffer();
    int getCursorLine() const; // Add this


    void addLine(const std::string& line);
    void insertLine(int index, const std::string& line);
    void deleteLine(int index);
    void editLine(int index, const std::string& newText);

    void moveCursor(int line, int column);
    void moveCursorUp();
    void moveCursorDown();
    void moveCursorLeft();
    void moveCursorRight();

    void showCursorPosition() const;
    void display(const std::string& language) const;

    const std::vector<std::string>& getLines() const;
    void undo();
    void redo();
    void clear();

    void search(const std::string& keyword) const; // Added search method

private:
    std::vector<std::string> lines;
    int cursorLine, cursorColumn;

    std::stack<Action> undoStack;
    std::stack<Action> redoStack;

    void recordAction(ActionType type, int lineIndex, const std::string& oldText, const std::string& newText);
};

#endif