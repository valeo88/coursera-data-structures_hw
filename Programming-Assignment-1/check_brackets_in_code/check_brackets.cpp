#include <iostream>
#include <stack>
#include <string>

struct Bracket {
    Bracket(char type, int position):
        type(type),
        position(position)
    {}

    bool Matchc(char c) {
        if (type == '[' && c == ']')
            return true;
        if (type == '{' && c == '}')
            return true;
        if (type == '(' && c == ')')
            return true;
        return false;
    }

    char type;
    int position;
};

int main() {
    std::string text;
    getline(std::cin, text);

    bool is_balanced = true;
    int result_position = 0;
    std::stack <Bracket> opening_brackets_stack;
    for (int position = 0; position < text.length(); ++position) {
        char next = text[position];

        if (next == '(' || next == '[' || next == '{') {
            // Process opening bracket, write your code here
            opening_brackets_stack.push({next, position + 1});
        }

        if (next == ')' || next == ']' || next == '}') {
            // Process closing bracket, write your code here
            if (opening_brackets_stack.empty()) {
                is_balanced = false;
                result_position = position + 1;
                break;
            }
            Bracket top = opening_brackets_stack.top();
            opening_brackets_stack.pop();
            if (!top.Matchc(next)) {
                is_balanced = false;
                result_position = position + 1;
                break;
            }
        }
    }

    // check stack on empty when is_balanced
    if (is_balanced && !opening_brackets_stack.empty()) {
        Bracket top = opening_brackets_stack.top();
        is_balanced = false;
        result_position = top.position;
    }

    // Printing answer, write your code here
    if (is_balanced) {
        std::cout << "Success";
    } else {
        std::cout << result_position;
    }

    return 0;
}
