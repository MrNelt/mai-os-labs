#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/mman.h>
#include <cassert>
#include <cstring>
#include <vector>
#include <algorithm>
#include <sys/stat.h>
#include <fstream>


#include "mappedFile.h"
#include "game.hpp"
#include "mutex.h"

TMappedFile mappedFile;
TCommonMutex mutex;
std:: string nickname;
bool playing = false;
std:: string currentGame;

void SendMessage (const std:: string &message) {
    if (pthread_mutex_lock(mutex.ptr) != 0) {
        std:: cout << "An error while locking mutex has been detected!" << std:: endl;
        exit(EXIT_FAILURE);
    }
    memset(mappedFile.data, '\0', _MAPPED_SIZE);
    sprintf(mappedFile.data, "%s", message.c_str());
    pthread_mutex_unlock(mutex.ptr);
}

bool ReceiveAnswer() {
    if (mappedFile.data[0] != 'T' || mappedFile.data[1] != 'O' || mappedFile.data[2] != _MSG_SEP) {
        return false;
    }
    std:: string message = mappedFile.data;
    std:: vector<std:: string> serverCommands;
    std:: string string;
    for (char i : message) {
        if (i == _MSG_SEP) {
            serverCommands.push_back(string);
            string = "";
        } 
        else {
            string.push_back(i);
        }
    }
    if (serverCommands[1] == nickname) {
        if (pthread_mutex_lock(mutex.ptr) != 0) {
            std:: cout << "An error while locking mutex has been detected!" << std:: endl;
            exit(EXIT_FAILURE);
        }
        memset(mappedFile.data, '\0', _MAPPED_SIZE);
        pthread_mutex_unlock(mutex.ptr);
        if (serverCommands[2] == "gamecreated") {
            playing = true;
            std:: cout << "Created successfully!" << std:: endl;
            std:: cout << "You are a player №1, cause you have created the game. Your field has been prepared!" << std:: endl;
            return true;
        }
        if (serverCommands[2] == "connected") {
            std:: cout << "Connected sucessfully" << std:: endl;
            std:: cout << "You are a player №2, cause you have connected to the game. Your field has been prepared!" << std:: endl;
            playing = true;
            return true;
        }
        if (serverCommands[2] == "notatgame") {
            playing = true;
            std:: cout << "You can't play without another player!" << std:: endl;;
            return true;
        }
        if (serverCommands[2] == "gamenotexists") {
            std:: cout << "Game with this name not exists" << std:: endl;
            playing = false;
            currentGame = "";
            return true;
        }
        if (serverCommands[2] == "wrongpassword") {
            std:: cout << "Wrong password has been detected!" << std:: endl;
            playing = false;
            currentGame = "";
            return true;
        }
        if (serverCommands[2] == "notyourturn") {
            std:: cout << "It's not your turn now!" << std:: endl;
            playing = true;
            return true;
        }
        if (serverCommands[2] == "youwounded") {
            playing = true;
            std:: cout << "You have wounded enemy's ship! Please enter coordinates again!" << std:: endl;
            return true;
        }
        if (serverCommands[2] == "youmissed") {
            playing = true;
            std:: cout << "Unfortunately you have missed! Now it's your enemy's turn!" << std:: endl;
            return true;
        }
        if (serverCommands[2] == "youkilled") {
            playing = true;
            std:: cout << "Congrats, you have KILLED enemy's ship! Please enter coordinates again!" << std:: endl;
            return true;
        }
        if (serverCommands[2] == "zeroplaces") {
            playing = false;
            std:: cout << "Sorry, but you can not create a game or connect to existing game. There are not free places!" << std:: endl;
            return true;
        }
        if (serverCommands[2] == "yourepeated") {
            playing = true;
            std:: cout << "You have already entered these coordinates! Please enter something new." << std:: endl;
            return true;
        }
        if (serverCommands[2] == "disconnected") {
            std:: cout << "You have successfully disconnected from the server!" << std:: endl;
            playing = false;
            return true;
        }
        if (serverCommands[2] == "youwon") {
            std:: cout << "YOU WON THE GAME!" << std:: endl;
            playing = false;
            return true;
        }
        if (serverCommands[2] == "stats") {
            int wins = stoi(serverCommands[3]);
            int loses = stoi(serverCommands[4]);
            int kills = stoi(serverCommands[5]);
            int misses = stoi(serverCommands[6]);
            int wounds = stoi(serverCommands[7]);
            std:: cout << "You have " << wins << " wins and " << loses << " loses!" << std:: endl;
            std:: cout << "FULL STATISTICS: " << std:: endl;
            std:: cout << '\t' << kills << " kills" << std:: endl;
            std:: cout << '\t' << wounds << " wounds" << std:: endl;
            std:: cout << '\t' << misses << " misses" << std:: endl;
            playing = true;
            return true;
        }
        else {
            std:: cout  << "Warning: unknown message has been detected!" << std::endl;
            playing = false;
            return true;
        }
        return true;
    }
    return false;
}

void Help() {
    std:: cout << "Follow next rules: " << std:: endl;
    std:: cout << '\t' << "create for creating a new game" << std:: endl;
    std:: cout << '\t' << "connect for connecting to the server" << std:: endl;
    std:: cout << '\t' << "shoot for shooting at enemy's ship" << std:: endl;
    std:: cout << '\t' << "stats for checking your stats" << std:: endl;
    std:: cout << '\t' << "disconnect for leaving from the server" << std:: endl;
    std:: cout << '\t' << "quit for leaving from the program" << std:: endl;
    std:: cout << '\t' << "help for checking rules" << std:: endl;
}

int main() {
    mappedFile.fd = shm_open(_BUFFER_NAME, O_RDWR, _SHM_OPEN_MODE);
    if (mappedFile.fd == -1 ) {
        std:: cout << "An error while shm_open has been detected!" << std:: endl;
        exit(EXIT_FAILURE);
    }
    mutex = SharedMutexInit(_MUTEX_NAME);
    mappedFile.data = (char*)mmap(0, _MAPPED_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, mappedFile.fd, 0);
    if (mappedFile.data == MAP_FAILED) {
        std:: cout << "An error while mmaping has been detected!" << std:: endl;
    }
    std:: cout << "Welcome to the SeaBattle! Please enter your nickname: " << std:: endl;
    std:: cout << "> ";
    std:: cin >> nickname;
    std:: cout << "Hello, " << nickname << "!" << std::endl;
    Help();
    std:: string command;
    while (std:: cout << "> " && std:: cin >> command) {
        if (!playing && command == "create") {
            std:: string gamename;
            std:: string password;
            std:: cin >> gamename >> password;
            currentGame = gamename;
            std::string on = "ON";
            std:: string serverMessage = on + _MSG_SEP + nickname + _MSG_SEP + "create" + _MSG_SEP + gamename + _MSG_SEP + password + _MSG_SEP;
            SendMessage (serverMessage);
            bool hasnotanswer = true;
            while (hasnotanswer) {
                hasnotanswer = !ReceiveAnswer();
            }
        } 
        else if (playing && command == "create") {
            std:: string gamename;
            std:: string password;
            std:: cin >> gamename >> password;
            std:: cout << "Can't create a new game, you are playing now! Please enter another command!" << std:: endl;
            continue;
        }
        else if (!playing && command == "connect") {
            std:: string gamename;
            std:: string password;
            std:: cin >> gamename >> password;
            currentGame = gamename;
            std::string on = "ON";
            std:: string serverMessage = on + _MSG_SEP + nickname + _MSG_SEP + "connect" + _MSG_SEP + gamename + _MSG_SEP + password + _MSG_SEP;
            SendMessage (serverMessage);
            bool hasnotanswer = true;
            while (hasnotanswer) {
                hasnotanswer = !ReceiveAnswer();
            }
        } 
        else if (playing && command == "connect") {
            std:: string gamename;
            std:: string password;
            std:: cin >> gamename >> password;
            std:: cout << "Can't connect to a new game, you've already connected! Please enter another command!" << std:: endl;
            continue;
        }
        else if (playing && command == "shoot") {
            int number;
			char letter;
            std:: cin >> letter >> number;
            if ((!((letter >= 'A') && (letter <= 'J'))) || ((number < 1) || (number > 10))) {
                std:: cout << "Please enter letter between A and J and number between 1 and 10!" << std:: endl;
                continue;
            }
            else {
                std:: string on = "ON";
                std:: string serverMessage = on + _MSG_SEP + nickname + _MSG_SEP + "shoot" + _MSG_SEP + currentGame + _MSG_SEP + letter + _MSG_SEP + std:: to_string(number) + _MSG_SEP;
                SendMessage (serverMessage);
                bool hasnotanswer = true;
                while (hasnotanswer) {
                    hasnotanswer = !ReceiveAnswer();
                }
            }
        }
        else if (playing && command == "stats") {
            std::string on = "ON";
            std:: string serverMessage = on + _MSG_SEP + nickname + _MSG_SEP + "stats" + _MSG_SEP + currentGame + _MSG_SEP;
            SendMessage (serverMessage);
            bool hasnotanswer = true;
            while (hasnotanswer) {
                hasnotanswer = !ReceiveAnswer();
            }
        }
        else if (!playing && command == "shoot") {
            int number;
            char letter;
            std:: cin >> letter >> number;
            std:: cout << "You are not in the game right now. Please create a game or connect to the existing one!" << std:: endl;
            continue;
        }
        else if (playing && command == "disconnect") {
            std:: string on = "ON";
            std:: string serverMessage = on + _MSG_SEP + nickname + _MSG_SEP + "disconnect" + _MSG_SEP + currentGame + _MSG_SEP;
            SendMessage (serverMessage);
            bool hasnotanswer = true;
            while (hasnotanswer) {
                hasnotanswer = !ReceiveAnswer();
            }
        }
        else if (command == "help") {
            Help();
        } 
        else if (!playing && command == "quit") {
            break;
        }
        else {
            std:: cout << "Wrong input!" << std:: endl;
        }
    }
    return 0;
}