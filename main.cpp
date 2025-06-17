#include <iostream>
#include <string>
#include <list>
#include <cctype>
#include <cmath>
#include <iomanip>
#include <sstream>

std::list<std::string> tokenize(std::string equation) { // this function tokenizes the equation into a list of strings
    std::list<std::string> tokens;
    for (size_t i = 0; i < equation.length();) {
        if (equation[i] == ' ') {
            i++; // skip the space
            continue; // continue to the next iteration
        }
        
        if (isdigit(equation[i]) || equation[i] == '.') { // if the current character is a digit or a dot, then we need to add the number to the list
            std::string num;
            while (i < equation.length() && (isdigit(equation[i]) || equation[i] == '.')) {
                num += equation[i++];
            }
            tokens.push_back(num); // add the number to the list
        } else {
            tokens.push_back(std::string(1, equation[i++])); // add the operator to the list
        }
    }
    return tokens;
}

std::list<std::string> tokens;
std::list<std::string>::iterator current;

void advance() {
    ++current;
} // this just moves the current pointer to the next token

std::string peek() {
    return *current;
} // allows us to look at the current token without moving the pointer

double expr();
double term();
double factor();
double power(); // preinitilized functions because for some reason it's not working without them

std::string preprocess(std::string equation) { // this function preprocesses the equation to make it easier to evaluate because FUCK sqrt()
    std::string result;
    size_t i = 0; // we are at the beginning of the equation

    while (i < equation.length()) {
        if (equation.substr(i, 5) == "SQRT(") {
            i += 5; // skip the SQRT()
            int depth = 1; // we are at the beginning of the inner equation
            std::string inner; // we are at the beginning of the inner equation

            while (i < equation.length() && depth > 0) {
                if (equation[i] == '(') depth++; // if we see an opening parenthesis, we increment the depth
                else if (equation[i] == ')') depth--; // if we see a closing parenthesis, we decrement the depth

                if (depth > 0) {
                    inner += equation[i]; // add the character to the inner equation
                }
                i++; // move to the next character
            }

            result += "(" + preprocess(inner) + ")^0.5"; // add the inner equation to the result
        } else {
            result += equation[i]; // add the character to the result
            i++; // move to the next character

            // if your confused on why we did that its so like 5*(sqrt(2)*3) exists
        }
    }

    return result;
}

double power() {
    double result = factor(); // evaluate the factor
    
    while (current != tokens.end() && peek() == "^") { // while we are not at the end of the tokens and the current token is a power
        advance(); // move to the next token
        double right = factor(); // evaluate the factor
        result = std::pow(result, right); // raise the result to the power of the right factor
    }

    return result; // return the result
}


double factor() {
    if (current != tokens.end() && peek() == "-") { // handle negative numbers
        advance(); // move past the negative sign
        return -factor(); // recursively handle the negative factor
    }
    
    if (peek() == "(") { // if the current token is an opening parenthesis
        advance(); // move to the next token
        double result = expr(); // evaluate the expression
        if (peek() != ")") { // if the current token is not a closing parenthesis
            std::cerr << "Expected ')'\n"; // print an error message
            exit(1); // exit the program
        }
        advance(); // move to the next token
        return result; // return the result
    } else { // if the current token is not an opening parenthesis
        double val = std::stod(peek()); // convert the current token to a double
        advance(); // move to the next token
        return val; // return the value
    }
}

double term() {
    double result = power(); // evaluate the power

    while (current != tokens.end() && (peek() == "*" || peek() == "/")) { // while we are not at the end of the tokens and the current token is a multiplication or division
        std::string op = peek(); // get the operator
        advance(); // move to the next token
        double right = power(); // evaluate the power

        if (op == "*") result *= right; // multiply the result by the right factor
        else result /= right; // divide the result by the right factor
    }

    return result; // return the result
}

double expr() {
    double result = term(); // evaluate the term

    while (current != tokens.end() && (peek() == "+" || peek() == "-")) { // while we are not at the end of the tokens and the current token is a addition or subtraction
        std::string op = peek(); // get the operator
        advance(); // move to the next token
        double right = term(); // evaluate the term

        if (op == "+") result += right; // add the result to the right factor
        else result -= right; // subtract the result from the right factor
    }

    return result; // return the result
}

double round_half_away_from_zero(double value, int decimals) {
    double factor = std::pow(10.0, decimals);
    if (value > 0)
        return std::floor(value * factor + 0.5) / factor;
    else
        return std::ceil(value * factor - 0.5) / factor;
}

std::string format(double val) {
    val = round_half_away_from_zero(val, 3);
    if (std::abs(val) < 1e-9) val = 0.0; // avoid -0

    std::ostringstream out;
    if (std::abs(val - std::round(val)) < 1e-9) {
        out << static_cast<int>(std::round(val));
    } else {
        out << std::fixed << std::setprecision(3) << val;
        std::string s = out.str();
        while (s.back() == '0') s.pop_back();
        if (s.back() == '.') s.pop_back();
        
        if (s.length() > 2 && s[0] == '0' && s[1] == '.') {
            s = s.substr(1);
        } else if (s.length() > 3 && s[0] == '-' && s[1] == '0' && s[2] == '.') {
            s = "-" + s.substr(2);
        }
        
        return s;
    }
    return out.str();
}

void solve() {
    std::string equation;
    std::getline(std::cin, equation);
    
    size_t eq_pos = equation.find('=');
    std::string left = equation.substr(0, eq_pos);
    std::string right = equation.substr(eq_pos + 1);
    right.erase(0, right.find_first_not_of(" \t"));
    right.erase(right.find_last_not_of(" \t") + 1);
    
    tokens = tokenize(preprocess(left));
    current = tokens.begin();
    
    double result = expr();
    double answer = std::stod(right);

    double rounded_result = round_half_away_from_zero(result, 3);
    double rounded_answer = round_half_away_from_zero(answer, 3);
    if (std::abs(rounded_result) < 1e-9) rounded_result = 0.0;
    if (std::abs(rounded_answer) < 1e-9) rounded_answer = 0.0;

    if (std::abs(rounded_result - rounded_answer) < 1e-6) {
        std::cout << "Correct\n";
    } else {
        std::cout << format(rounded_result) << '\n';
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int t;
    std::cin >> t;
    std::cin.ignore();
    
    for (int i = 0; i < t; i++) {
        solve();
    }
    
    return 0;
}

bool is_correct(std::string equation) {
    size_t eq_pos = equation.find('='); // find the position of the equal sign
    std::string left = equation.substr(0, eq_pos);
    std::string right = equation.substr(eq_pos + 1);

    tokens = tokenize(preprocess(left)); 
    current = tokens.begin(); // set the current token to the first token like a pointer
    double result = expr(); // evaluate the left side of the equation
    double answer = std::stod(right); // convert the right side of the equation to a double
    return std::abs(result - answer) < 1e-6; // check if the result is correct
}

