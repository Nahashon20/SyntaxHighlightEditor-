#include <iostream>
#include <string>
#include "text_buffer.h"
#include "file_io.h"

int main() {
    TextBuffer buffer;
    std::string language = "cpp"; // Default language
    std::string filename;

    while (true) {
        std::cout << "\n--- Text Editor ---\n";
        std::cout << "1. Add line\n";
        std::cout << "2. Insert line\n";
        std::cout << "3. Delete line (at cursor)\n";
        std::cout << "4. Edit line (at cursor)\n";
        std::cout << "5. Move cursor\n";
        std::cout << "6. Show cursor position\n";
        std::cout << "7. Display buffer\n";
        std::cout << "8. Undo\n";
        std::cout << "9. Redo\n";
        std::cout << "10. Save to file\n";
        std::cout << "11. Load from file\n";
        std::cout << "12. Search\n";
        std::cout << "0. Exit\n";
        std::cout << "Choose an option: ";

        int choice;
        std::cin >> choice;
        std::cin.ignore();  // clear newline

        switch (choice) {
            case 1: {
                std::string line;
                std::cout << "Enter line to add: ";
                std::getline(std::cin, line);
                buffer.addLine(line);
                break;
            }
            case 2: {
                int index;
                std::string line;
                std::cout << "Enter index to insert at: ";
                std::cin >> index;
                std::cin.ignore();
                std::cout << "Enter line: ";
                std::getline(std::cin, line);
                buffer.insertLine(index - 1, line);
                break;
            }
            case 3: {
                buffer.deleteLine(buffer.getCursorLine());
                std::cout << "Deleted line at cursor.\n";
                break;
            }
            case 4: {
                std::string newText;
                std::cout << "Enter new text for current line: ";
                std::getline(std::cin, newText);
                buffer.editLine(buffer.getCursorLine(), newText);
                break;
            }
            case 5: {
                char dir;
                std::cout << "Move (W/A/S/D): ";
                std::cin >> dir;
                dir = std::tolower(dir);
                if (dir == 'U') buffer.moveCursorUp();
                else if (dir == 'D') buffer.moveCursorDown();
                else if (dir == 'L') buffer.moveCursorLeft();
                else if (dir == 'R') buffer.moveCursorRight();
                else std::cout << "Invalid direction.\n";
                break;
            }
            case 6:
                buffer.showCursorPosition();
                break;
            case 7:
                buffer.display(language);
                break;
            case 8:
                buffer.undo();
                break;
            case 9:
                buffer.redo();
                break;
            case 10: {
                std::cout << "Enter filename to save: ";
                std::getline(std::cin, filename);
                saveToFile(filename, buffer);
                break;
            }
            case 11: {
                std::cout << "Enter filename to load: ";
                std::getline(std::cin, filename);
                loadFromFile(filename, buffer);
                break;
            }
            case 12: {
                std::string keyword;
                std::cout << "Enter keyword to search: ";
                std::getline(std::cin, keyword);
                buffer.search(keyword);
                break;
            }
            case 0:
                return 0;
            default:
                std::cout << "Invalid option.\n";
        }
    }

    return 0;
}
