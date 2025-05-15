#ifndef FILE_IO_H
#define FILE_IO_H

#include <string>
#include "text_buffer.h"

// Now return a bool to indicate success or failure
bool saveToFile(const std::string& filename, const TextBuffer& buffer);
bool loadFromFile(const std::string& filename, TextBuffer& buffer);

#endif
