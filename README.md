This project implements a simple yet illustrative lexical analyzer in C++ designed to tokenize arithmetic expressions.
At its core, the analyzer reads an input expression character-by-character, identifies the structure of the language, and categorizes various segments into tokens.
The lexical analyzer serves as a fundamental building block for compiler design and demonstrates essential concepts such as tokenization, character classification, and error handling in parsing.
The lexer handles input by reading each character and determining its role based on its type—whether it is an alphabetic letter, a numerical digit, or a special character.
For alphabetic characters, it constructs identifiers by accumulating letters and digits, converting them to uppercase to standardize the representation. When encountering a digit, the analyzer builds an integer literal,
appending a prefix (NUM_) to clearly distinguish it from other tokens. Special characters, including arithmetic operators and delimiters such as +, -, *, /, (, ), and the assignment operator =, are recognized using a dedicated lookup mechanism.
This comprehensive process not only demonstrates the systematic approach to tokenizing a string but also highlights key programming techniques such as the use of global variables for state management, buffer manipulation for lexeme storage,and control flow via switch-case constructs.
In addition, the code includes mechanisms to skip over whitespace and prevent buffer overflow, ensuring robust and reliable token processing. 
This analyzer is an excellent starting point for anyone interested in learning about lexical analysis, compiler construction, or the inner workings of interpreters.
