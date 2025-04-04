#include <iostream>
#include <cctype>
#include <cstring>
using namespace std;

// Global variables used by the lexer:
// 'charClass' indicates the type of the current character (LETTER, DIGIT, etc.)
// 'lexeme' stores the string (or lexeme) that is being built for a token
// 'nextChar' holds the most recently read character from input
// 'lexLen' tracks the length of the current lexeme
// 'nextToken' stores the token code for the lexeme that was just built
int charClass;
char lexeme[100];
char nextChar;
int lexLen;
int token;
int nextToken;

// Function declarations used by the lexer:
void addChar();       // Adds nextChar to lexeme
void getChar();       // Reads the next character from input and sets its class
void getNonBlank();   // Skips whitespace characters in the input
int lex();            // The main function that analyzes input and identifies tokens

// Token and character class definitions:
#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99

// Token codes for the various types of tokens:
#define INT_LIT 10      // Integer literal token
#define IDENT 11        // Identifier token (names, variables)
#define ASSIGN_OP 20    // Assignment operator token (=)
#define ADD_OP 21       // Addition operator token (+)
#define SUB_OP 22       // Subtraction operator token (-)
#define MULT_OP 23      // Multiplication operator token (*)
#define DIV_OP 24       // Division operator token (/)
#define LEFT_PAREN 25   // Left parenthesis token '('
#define RIGHT_PAREN 26  // Right parenthesis token ')'

// The main function: prompts the user, initializes the first character, and then processes the input.
int main() {
    cout << "Enter expression (press Ctrl+D or Ctrl+Z then Enter to finish): ";
    getChar(); // Initialize nextChar by reading the first character from input.
    do {
        lex(); // Keep getting tokens until we hit end-of-file.
    } while (nextToken != EOF);
    return 0;
}

// lookup: Handles characters that are operators or delimiters.
// It checks the current character and sets up the lexeme and token type accordingly.
int lookup(char ch) {
    switch (ch) {
    case '(':
        addChar();           // Add '(' to lexeme.
        nextToken = LEFT_PAREN;
        break;
    case ')':
        addChar();           // Add ')' to lexeme.
        nextToken = RIGHT_PAREN;
        break;
    case '+':
        lexeme[0] = '+';
        lexeme[1] = 0;       // Null-terminate the lexeme.
        lexLen = 1;
        nextToken = ADD_OP;
        break;
    case '-':
        lexeme[0] = '-';
        lexeme[1] = 0;
        lexLen = 1;
        nextToken = SUB_OP;
        break;
    case '*':
        lexeme[0] = '*';
        lexeme[1] = 0;
        lexLen = 1;
        nextToken = MULT_OP;
        break;
    case '/':
        lexeme[0] = '/';
        lexeme[1] = 0;
        lexLen = 1;
        nextToken = DIV_OP;
        break;
    case '=':
        lexeme[0] = '=';
        lexeme[1] = 0;
        lexLen = 1;
        nextToken = ASSIGN_OP;
        break;
    default:
        lexeme[0] = ch;
        lexeme[1] = 0;
        lexLen = 1;
        nextToken = UNKNOWN; // If the character is not recognized, mark it as UNKNOWN.
        break;
    }
    return nextToken;
}

// addChar: Appends the current character (nextChar) to the lexeme buffer.
// It also ensures that the lexeme doesn't exceed its allocated size.
void addChar() {
    if (lexLen <= 98) {  // Allow room for the null terminator.
        lexeme[lexLen++] = nextChar;
        lexeme[lexLen] = 0; // Null-terminate the lexeme string.
    }
    else {
        cout << "Error - lexeme is too long" << endl;
    }
}

// getChar: Reads the next character from input.
// It also categorizes the character into LETTER, DIGIT, or UNKNOWN.
void getChar() {
    if (cin.get(nextChar)) {
        if (isalpha(nextChar))
            charClass = LETTER;  // The character is alphabetic.
        else if (isdigit(nextChar))
            charClass = DIGIT;   // The character is numeric.
        else
            charClass = UNKNOWN; // Neither letter nor digit.
    }
    else {
        charClass = EOF;         // End-of-file reached.
    }
}

// getNonBlank: Skips any whitespace so that lex() starts processing on a non-space character.
void getNonBlank() {
    while (isspace(nextChar))
        getChar(); // Keep reading until a non-space character is found.
}

// lex: The core function that performs lexical analysis.
// It uses the current character to build up lexemes and assign token types.
int lex() {
    lexLen = 0;      // Reset the length of the current lexeme.
    getNonBlank();   // Skip any whitespace before the next token.

    // Decide what to do based on the class of the current character.
    switch (charClass) {
    case LETTER:
        // If it starts with a letter, treat it as an identifier.
        addChar();
        // Convert the first character to uppercase.
        lexeme[0] = toupper(lexeme[0]);
        getChar();
        // Continue collecting letters or digits.
        while (charClass == LETTER || charClass == DIGIT) {
            addChar();
            // Convert each character to uppercase.
            lexeme[lexLen - 1] = toupper(lexeme[lexLen - 1]);
            getChar();
        }
        nextToken = IDENT;  // Set token type to identifier.
        break;

    case DIGIT:
        // If it starts with a digit, treat it as an integer literal.
        // Here, the lexeme is prefixed with "NUM_" for clarity.
        strcpy_s(lexeme, sizeof(lexeme), "NUM_");
        lexLen = 4;
        addChar();       // Add the first digit.
        getChar();
        // Continue adding digits to the lexeme.
        while (charClass == DIGIT) {
            addChar();
            getChar();
        }
        nextToken = INT_LIT;  // Set token type to integer literal.
        break;

    case UNKNOWN:
        // If the character is not a letter or digit, use lookup to decide its token.
        lookup(nextChar);
        getChar();
        break;

    case EOF:
        // If end-of-file is reached, set the lexeme to "EOF" and token accordingly.
        nextToken = EOF;
        lexeme[0] = 'E';
        lexeme[1] = 'O';
        lexeme[2] = 'F';
        lexeme[3] = 0;
        break;
    }
    // Output the token type and the lexeme for this pass.
    cout << "Next token is: " << nextToken << ", Next lexeme is " << lexeme << endl;
    return nextToken;

}
