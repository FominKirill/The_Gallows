#include <iostream>
#include <Windows.h>
#include <cstdlib>
#include <ctime>
#include <string>
#include <locale>
#include <vector>
#include <algorithm>

using namespace std;

bool isRussianLetter(char c) {
    return (c >= '�' && c <= '�') || (c >= '�' && c <= '�') || c == '�' || c == '�';
}

bool isRussianWord(const string& word) {
    for (char c : word) {
        if (!isRussianLetter(c)) {
            return false;
        }
    }
    return !word.empty();
}

static void SHOW(string arr[5][8])
{
    cout << "========" << endl;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            cout << arr[i][j];
        }
        cout << endl;
    }
    cout << "========" << endl;
}

static void SHOW_GUESS_WORD(string guess[], int nn)
{
    for (int i = 0; i < nn; i++)
    {
        cout << guess[i] << " ";
    }
    cout << endl;
}

char toLowerRussian(char c) {
    if (c >= '�' && c <= '�') {
        return c + ('�' - '�');
    }
    if (c == '�') {
        return '�';
    }
    return c;
}

string base_word4[] = { "����","����","����","����","����","����","����","����","����","����" };
string base_word5[] = { "�����","�����","�����","�����","�����","�����","�����","�����","�����","�����" };
string base_word6[] = { "������","������","������","������","������","������","������","������","������","������" };
string base_word7[] = { "�������","�������","�������","�������","�������","�������","�������","�������","�������","�������" };

int main()
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    int next_game = 0;
    do {
        srand(time(NULL));
        bool game_end = false;
        string arr[5][8];
        int pictures = 0;
        string letter;

        vector<char> used_letters;

        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 8; j++) {
                arr[i][j] = " ";
            }
        }

        string word;
        size_t n;

        int nol;
        bool valid_length = false;

        while (!valid_length) {
            cout << "������� ���� ������ ���� � ���������� �����? (�� 4 �� 7)" << endl << "-> ";
            cin >> nol;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "������! ������� ����� �� 4 �� 7." << endl;
                continue;
            }

            switch (nol)
            {
            case 4:
                n = sizeof(base_word4) / sizeof(base_word4[0]);
                word = base_word4[rand() % n];
                valid_length = true;
                break;
            case 5:
                n = sizeof(base_word5) / sizeof(base_word5[0]);
                word = base_word5[rand() % n];
                valid_length = true;
                break;
            case 6:
                n = sizeof(base_word6) / sizeof(base_word6[0]);
                word = base_word6[rand() % n];
                valid_length = true;
                break;
            case 7:
                n = sizeof(base_word7) / sizeof(base_word7[0]);
                word = base_word7[rand() % n];
                valid_length = true;
                break;
            default:
                cout << "������! ����� ����� ������ ���� �� 4 �� 7 ����." << endl;
                break;
            }
        }

        int nn = word.size();
        string* guess = new string[nn];
        for (int i = 0; i < nn; i++)
        {
            guess[i] = "_";
        }

        cout << "���������� �����: ";
        SHOW_GUESS_WORD(guess, nn);

        while (!game_end)
        {
            bool valid_letter = false;
            string input;
            char lower_letter;

            while (!valid_letter) {
                cout << "������� �����: ";
                cin >> input;

                if (input.length() != 1) {
                    cout << "������! ������� ������ ���� �����." << endl;
                    continue;
                }

                if (!isRussianLetter(input[0])) {
                    cout << "������! ������� ������� �����." << endl;
                    continue;
                }

                lower_letter = toLowerRussian(input[0]);

                if (find(used_letters.begin(), used_letters.end(), lower_letter) != used_letters.end()) {
                    cout << "������! �� ��� ������� ����� '" << input[0] << "'. ���������� ������." << endl;
                    continue;
                }

                valid_letter = true;
                letter = input;
            }

            used_letters.push_back(lower_letter);

            bool enter_letter = false;

            for (int i = 0; i < nn; i++)
            {
                if (letter[0] == word[i]) {
                    guess[i] = word[i];
                    enter_letter = true;
                }
            }

            cout << "�������������� �����: ";
            for (char used : used_letters) {
                cout << used << " ";
            }
            cout << endl;

            cout << "���������� �����: ";
            SHOW_GUESS_WORD(guess, nn);

            if (!enter_letter) {
                pictures++;
                cout << "��� ����� �����! ������: " << pictures << "/11" << endl;

                switch (pictures)
                {
                case 1:
                    arr[0][1] = "o"; arr[1][1] = "|"; arr[2][1] = "|"; arr[3][1] = "|"; SHOW(arr);
                    break;
                case 2:
                    arr[4][0] = "-"; arr[4][1] = "-"; arr[4][2] = "-"; SHOW(arr);
                    break;
                case 3:
                    arr[0][2] = "-"; arr[0][3] = "-"; arr[0][4] = "-"; arr[0][5] = "-"; SHOW(arr);
                    break;
                case 4:
                    arr[1][2] = "/"; SHOW(arr);
                    break;
                case 5:
                    arr[0][6] = "|"; SHOW(arr);
                    break;
                case 6:
                    arr[1][6] = "0"; SHOW(arr);
                    break;
                case 7:
                    arr[2][6] = "I"; SHOW(arr);
                    break;
                case 8:
                    arr[2][7] = "-"; SHOW(arr);
                    break;
                case 9:
                    arr[2][5] = "-"; SHOW(arr);
                    break;
                case 10:
                    arr[3][7] = "b"; SHOW(arr);
                    break;
                case 11:
                    arr[3][5] = "d"; SHOW(arr);
                    break;
                }

                if (pictures >= 11) {
                    cout << "�� ���������! ���������� ����� ����: " << word << endl;
                    game_end = true;
                }
            }

            bool all_guessed = true;
            for (int i = 0; i < nn; i++)
            {
                if (guess[i] == "_") {
                    all_guessed = false;
                    break;
                }
            }

            if (all_guessed) {
                cout << "�����������! �� ������� �����: " << word << endl;
                game_end = true;
            }
        }

        delete[] guess;

        bool valid_choice = false;
        while (!valid_choice) {
            cout << "������ ���?" << endl << "(1 - ��)" << endl << "(2 - ���)" << endl << "����: ";
            cin >> next_game;

            if (cin.fail() || (next_game != 1 && next_game != 2)) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "������! ������� 1 ��� 2." << endl;
            }
            else {
                valid_choice = true;
            }
        }

    } while (next_game == 1);

    cout << "������� �� ����!" << endl;
    return 0;
}
