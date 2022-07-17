#include <iostream>
#include <string>

char get_element (std::string first_row, std::string second_row, std::string third_row, int x, int y){
    switch (y) {
        case 1:
            return first_row[x - 1];
        case 2:
            return second_row[x - 1];
        case 3:
            return third_row[x - 1];
    }
}

int get_number_of_el(std::string first_row, std::string second_row, std::string third_row, char element){
    int number = 0;
    for (int i = 1; i <= 3; ++i) {
        for (int j = 1; j < 3; ++j) {
            if (get_element(first_row, second_row, third_row, i, j) == element) number++;
        }
    }
    return number;
}

char row_winner(std::string row){
    if (row[0] == row[1] && row[1] == row[2]) {
        if (row[0] == 'O') return 'O';
        else if (row[0] == 'X') return 'X';
    }
    else return '.';
}

char diagonal_winner(std::string first_row, std::string second_row, std::string third_row){
    if ((get_element(first_row, second_row, third_row, 1, 1) == get_element(first_row, second_row, third_row, 3, 3)
        || get_element(first_row, second_row, third_row, 1, 3) == get_element(first_row, second_row, third_row, 3, 1))
        && ((get_element(first_row, second_row, third_row, 2, 2) == get_element(first_row, second_row, third_row, 3, 3))
        && get_element(first_row, second_row, third_row, 2, 2) == get_element(first_row, second_row, third_row, 1, 1))
        || (get_element(first_row, second_row, third_row, 2, 2) == get_element(first_row, second_row, third_row, 1, 3)
        && (get_element(first_row, second_row, third_row, 2, 2) == get_element(first_row, second_row, third_row, 3, 1)))){
        if (get_element(first_row, second_row, third_row, 2, 2) == 'X') return 'X';
        else if (get_element(first_row, second_row, third_row, 2, 2) == 'O') return 'O';
    }
    else return '.';
}

std::string get_column(std::string first_row, std::string second_row, std::string third_row, int index){
    std::string row;
    for (int i = 1; i <= 3; ++i) {
        row += get_element(first_row, second_row, third_row, index, i);
    }
    return row;
}

char column_winner(std::string first_row, std::string second_row, std::string third_row, int index){
    return row_winner(get_column(first_row, second_row, third_row, index));
}

int wins_count(std::string first_row, std::string second_row, std::string third_row, char letter){
    int wins = 0;
    if (row_winner(first_row) == letter || row_winner(second_row) == letter || row_winner(third_row) == letter
        || diagonal_winner(first_row, second_row, third_row) == letter) wins++;
    for (int i = 1; i <= 3; ++i) {
        if (column_winner(first_row, second_row, third_row, i) == letter && row_winner(first_row) != letter
            && row_winner(second_row) != letter && row_winner(third_row) != letter) wins++;
    }
    return wins;
}

std::string winner(std::string first_row, std::string second_row, std::string third_row){
    if (first_row.length() != 3 || second_row.length() != 3 || third_row.length() != 3) return "Incorrect\n";
    int x_wins = wins_count(first_row, second_row, third_row, 'X'), o_wins = wins_count(first_row, second_row, third_row, 'O');
    if(x_wins + o_wins > 1) return "Incorrect\n";
    int x_count = 0, o_count = 0, points_count = 0;
    for (int i = 1; i <= 3; ++i) {
        for (int j = 1; j <= 3; ++j) {
            if (get_element(first_row, second_row, third_row, i, j) == 'X') x_count++;
            else if (get_element(first_row, second_row, third_row, i, j) == 'O') o_count++;
            else if (get_element(first_row, second_row, third_row, i, j) == '.') points_count++;
            else return "Incorrect\n";
        }
    }
    if (o_wins == 1 && x_count != o_count) return "Incorrect\n";
    if (x_wins == 1 && o_count >= x_count) return "Incorrect\n";
    if (x_wins == 1) return "Petya won\n";
    if (o_wins == 1) return "Vanya won\n";
    else return "Nobody\n";
}

int main() {
    std::cout << "Welcome to tic-tak-toe winner identification app!" << std::endl;
    std::cout << "Input your tic-tak-toe field:\n";
    std::string first_row, second_row, third_row;
    std::cin >> first_row >> second_row >> third_row;
    std::cout << winner(first_row, second_row, third_row);
    return 0;
}
