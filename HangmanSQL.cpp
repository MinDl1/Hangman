#include <iostream>
#include <jdbc.h>
#include <string>
using namespace std;

const string server = "tcp://127.0.0.1:3306";
const string username = "root";
const string password = "123";

int main()
{
    int dictionary_size = 6;
    srand(time(0));
    while (1) {
        cout << "          _______  _        _______  _______  _______  _\n";
        cout << "|\\     /|(  ___  )( (    /|(  ____ \\(       )(  ___  )( (    /|\n";
        cout << "| )   ( || (   ) ||  \\  ( || (    \\/| () () || (   ) ||  \\  ( |\n";
        cout << "| (___) || (___) ||   \\ | || |      | || || || (___) ||   \\ | |\n";
        cout << "|  ___  ||  ___  || (\\ \\) || | ____ | |(_)| ||  ___  || (\\ \\) |\n";
        cout << "| (   ) || (   ) || | \\   || | \\_  )| |   | || (   ) || | \\   |\n";
        cout << "| )   ( || )   ( || )  \\  || (___) || )   ( || )   ( || )  \\  |\n";
        cout << "|/     \\||/     \\||/    )_)(_______)|/     \\||/     \\||/    )_)\n";

        sql::Driver* driver;
        sql::Connection* con;
        sql::Statement* stmt;
        sql::PreparedStatement* pstmt;
        sql::ResultSet* result;
        //check connection
        try {
            driver = get_driver_instance();
            con = driver->connect(server, username, password);
        }
        catch (sql::SQLException e) {
            cout << "Could not connect to server. Error message: " << e.what() << endl;
            system("pause");
            exit(1);
        }
        string word;
        int rand_word = rand() % dictionary_size;
        con->setSchema("Dictionary");
        pstmt = con->prepareStatement("SELECT word FROM Words WHERE id = ?;");
        pstmt->setInt(1, rand_word);
        result = pstmt->executeQuery();
        while (result->next()) {
            word = result->getString(1);
        }
        delete result;
        delete pstmt;

        char* player_word = new char[word.size()];
        for (int i = 0; i < word.size(); i++) {
            player_word[i] = '_';
            cout << " _";
        }
        cout << endl;
        for (int i = 0; i < word.size(); i++) {
            cout << " _";
        }

        cout << endl;
        int i = 0, solved = 0, check_solved = 0;
        for (; i < 6; ) {
            char letter;
            cout << "Enter letter: ";
            cin >> letter;
            for (int j = 0; j < word.size(); j++) {
                if (letter == word[j] && player_word[j] == '_') {
                    player_word[j] = letter;
                    solved++;
                }
                cout << player_word[j] << ' ';
            }
            if (solved == check_solved) {
                i++;
            }
            else {
                check_solved = solved;
            }
            if (solved == word.size()) {
                break;
            }
            cout << "Mistakes: " << i << '\t';
        }

        if (i > 5) {
            cout << "\nYou lose!\nWord: " << word << endl;
        }
        else {
            cout << "\nYou win!\nWord: " << word << endl;
        }
        string exit;
        while (true) {
            cout << "Play again(Y/n): ";
            cin >> exit;
            if (exit == "y" || exit == "Y") {
                break;
            }
            else if (exit == "n" || exit == "N") {
                break;
            }
            else {
                cout << "Wrong input\n";
            }
        }
        if (exit == "n") {
            break;
        }
        delete[] player_word;
    }

    system("pause");
    return 0;
}
