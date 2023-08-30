#include <iostream>
#include <SFML/Graphics.hpp>
#include "fstream"
#include <vector>

using namespace std;
using namespace sf;

class Board{
public:
    int window_width;
    int window_height;
    int mine_count;
    int tile_count;
    int row;
    int column;
    vector<int> boardrow;
    vector<int> gameboardrow;
    vector<vector<int>> board;
    vector<vector<int>> allrevealed;
    vector<vector<int>> flagspace;
    vector<vector<int>> gameboard;
    map<string, string> leaderboard;
    map<string, string>::iterator iter;

    Board(int width, int height, int mines, int tiles){
        window_width = width;
        window_height = height;
        mine_count = mines;
        tile_count = tiles;
        row = (height - 100)/32;
        column = width/32;
//        cont = true;
//        win = false;
//        lose = false;
//        debug = false;
//        cout << width << height << endl;
        for(int i = 0; i<column; i++){
            boardrow.push_back(0); }

        for (int j = 0; j<row; j++){
            board.push_back(boardrow); }

        for (int j = 0; j<row; j++){
            allrevealed.push_back(boardrow); }

        for (int j = 0; j<row; j++){
            flagspace.push_back(boardrow); }

        for(int i = 0; i<column; i++){
            gameboardrow.push_back(10); }

        for (int j = 0; j<row; j++){
            gameboard.push_back(gameboardrow); }
    }

    void generateMine(){
        int xrow;
        int ycol;
        int minecout = 0;
        for (int i = 0; i < mine_count; i++){
            xrow = rand() % row;
            ycol = rand() % column;
            if (board[xrow][ycol] == 9){
                i--;
                continue;
            }
            board[xrow][ycol] = 9;
        }

        // checking num mines generated
//        for(int i=0; i < row; i++){
//            for(int j=0; j<column; j++){
//                if(board[i][j] == 9) minecout++;
//            }
//        }
//        cout << "number of mines: " << minecout << endl;
    }

    void revealMine(RenderWindow &window, Sprite sprite){
        for(int i=0; i < row; i++){
            for(int j=0; j<column; j++){
                if(board[i][j] == 9){
                    sprite.setPosition(Vector2f(j*32, i*32));
                    window.draw(sprite);
                }
            }
        }
    }

    void revealFlags(RenderWindow &window, Sprite sprite){
        for(int i=0; i < row; i++){
            for(int j=0; j<column; j++){
                if(flagspace[i][j] == 1){
                    sprite.setPosition(Vector2f(j*32, i*32));
                    window.draw(sprite);
                }
            }
        }
    }
    void allrevealedtiles(RenderWindow &window, Sprite sprite){
        for(int i=0; i < row; i++){
            for(int j=0; j<column; j++){
                sprite.setPosition(Vector2f(j*32, i*32));
                window.draw(sprite);
            }
        }
    }

    void updateTime(RenderWindow &window, int currtime){
        Texture digitsimage0;
        digitsimage0.loadFromFile("files/images/digits.png", IntRect(0, 0, 21, 32));

        Texture digitsimage1;
        digitsimage1.loadFromFile("files/images/digits.png", IntRect(21, 0, 21, 32));

        Texture digitsimage2;
        digitsimage2.loadFromFile("files/images/digits.png", IntRect(42, 0, 21, 32));

        Texture digitsimage3;
        digitsimage3.loadFromFile("files/images/digits.png", IntRect(63, 0, 21, 32));

        Texture digitsimage4;
        digitsimage4.loadFromFile("files/images/digits.png", IntRect(84, 0, 21, 32));

        Texture digitsimage5;
        digitsimage5.loadFromFile("files/images/digits.png", IntRect(105, 0, 21, 32));

        Texture digitsimage6;
        digitsimage6.loadFromFile("files/images/digits.png", IntRect(126, 0, 21, 32));

        Texture digitsimage7;
        digitsimage7.loadFromFile("files/images/digits.png", IntRect(147, 0, 21, 32));

        Texture digitsimage8;
        digitsimage8.loadFromFile("files/images/digits.png", IntRect(168, 0, 21, 32));

        Texture digitsimage9;
        digitsimage9.loadFromFile("files/images/digits.png", IntRect(189, 0, 21, 32));

        Sprite min1;
        Sprite min2;
        Sprite sec1;
        Sprite sec2;

        int mm1;
        int mm2;
        int ss1;
        int ss2;

        min1.setPosition(Vector2f(((column)*32)-97, 32*((row)+0.5f)+16));
        min2.setPosition(Vector2f(((column)*32)-76, 32*((row)+0.5f)+16));

        sec1.setPosition(Vector2f(((column)*32)-54, 32*((row)+0.5f)+16));
        sec2.setPosition(Vector2f(((column)*32)-33, 32*((row)+0.5f)+16));

        int min = currtime/60;
        mm1 = min/10;
        mm2 = min%10;

        if(mm1 == 0){ min1.setTexture(digitsimage0); }
        else if (mm1 == 1){ min1.setTexture(digitsimage1); }
        else if (mm1 == 2){ min1.setTexture(digitsimage2); }
        else if (mm1 == 3){ min1.setTexture(digitsimage3); }
        else if (mm1 == 4){ min1.setTexture(digitsimage4); }
        else if (mm1 == 5){ min1.setTexture(digitsimage5); }
        else if (mm1 == 6){ min1.setTexture(digitsimage6); }
        else if (mm1 == 7){ min1.setTexture(digitsimage7); }
        else if (mm1 == 8){ min1.setTexture(digitsimage8); }
        else if (mm1 == 9){ min1.setTexture(digitsimage9); }

        if(mm2 == 0){ min2.setTexture(digitsimage0); }
        else if (mm2 == 1){ min2.setTexture(digitsimage1); }
        else if (mm2 == 2){ min2.setTexture(digitsimage2); }
        else if (mm2 == 3){ min2.setTexture(digitsimage3); }
        else if (mm2 == 4){ min2.setTexture(digitsimage4); }
        else if (mm2 == 5){ min2.setTexture(digitsimage5); }
        else if (mm2 == 6){ min2.setTexture(digitsimage6); }
        else if (mm2 == 7){ min2.setTexture(digitsimage7); }
        else if (mm2 == 8){ min2.setTexture(digitsimage8); }
        else if (mm2 == 9){ min2.setTexture(digitsimage9); }

        int sec = currtime%60;
        ss1 = sec/10;
        ss2 = sec%10;

        if(ss1 == 0){ sec1.setTexture(digitsimage0); }
        else if (ss1 == 1){ sec1.setTexture(digitsimage1); }
        else if (ss1 == 2){ sec1.setTexture(digitsimage2); }
        else if (ss1 == 3){ sec1.setTexture(digitsimage3); }
        else if (ss1 == 4){ sec1.setTexture(digitsimage4); }
        else if (ss1 == 5){ sec1.setTexture(digitsimage5); }
        else if (ss1 == 6){ sec1.setTexture(digitsimage6); }
        else if (ss1 == 7){ sec1.setTexture(digitsimage7); }
        else if (ss1 == 8){ sec1.setTexture(digitsimage8); }
        else if (ss1 == 9){ sec1.setTexture(digitsimage9); }

        if(ss2 == 0){ sec2.setTexture(digitsimage0); }
        else if (ss2 == 1){ sec2.setTexture(digitsimage1); }
        else if (ss2 == 2){ sec2.setTexture(digitsimage2); }
        else if (ss2 == 3){ sec2.setTexture(digitsimage3); }
        else if (ss2 == 4){ sec2.setTexture(digitsimage4); }
        else if (ss2 == 5){ sec2.setTexture(digitsimage5); }
        else if (ss2 == 6){ sec2.setTexture(digitsimage6); }
        else if (ss2 == 7){ sec2.setTexture(digitsimage7); }
        else if (ss2 == 8){ sec2.setTexture(digitsimage8); }
        else if (ss2 == 9){ sec2.setTexture(digitsimage9); }

        window.draw(min1);
        window.draw(min2);
        window.draw(sec1);
        window.draw(sec2);

//        cout << "CurrTIme: " << currtime << "\t";
//
//        cout << mm1 << mm2 << ss1 << ss2 << endl;

    }

    void fillNum(){
        for(int i = 0; i<row; i++){
            for(int j=0; j<column; j++){
                if(board[i][j] == 9){
                    if (i == 0) {
                        if (j == 0) {
                            if(board[i][j + 1] != 9) board[i][j + 1] += 1;
                            if(board[i + 1][j + 1] != 9) board[i + 1][j + 1] += 1;
                            if (board[i + 1][j] != 9) board[i + 1][j] += 1;
                        } else if (j == column - 1) {
                            if(board[i][j - 1] != 9) board[i][j - 1] += 1;
                            if (board[i + 1][j - 1] != 9) board[i + 1][j - 1] += 1;
                            if (board[i + 1][j] != 9) board[i + 1][j] += 1;;
                        } else if (j > 0 && j < column - 1) {
                            if(board[i][j + 1] != 9) board[i][j + 1] += 1;
                            if(board[i + 1][j + 1] !=9) board[i + 1][j + 1] += 1;
                            if (board[i + 1][j] != 9) board[i + 1][j] += 1;;
                            if(board[i][j - 1] != 9) board[i][j - 1] += 1;
                            if(board[i + 1][j - 1] != 9) board[i + 1][j - 1] += 1;
                        }
                    } else if (i == row - 1) {
                        if (j == 0) {
                            if(board[i][j + 1] != 9) board[i][j + 1] += 1;
                            if(board[i - 1][j + 1] != 9) board[i - 1][j + 1] += 1;
                            if(board[i - 1][j] != 9) board[i - 1][j] += 1;
                        } else if (j == column - 1) {
                            if(board[i][j - 1] != 9) board[i][j - 1] += 1;
                            if(board[i - 1][j - 1] != 9) board[i - 1][j - 1] += 1;
                            if(board[i - 1][j] != 9) board[i - 1][j] += 1;
                        } else if (j > 0 && j < column - 1) {
                            if(board[i][j - 1] != 9) board[i][j - 1] += 1;
                            if(board[i - 1][j - 1] != 9) board[i - 1][j - 1] += 1;
                            if(board[i - 1][j] != 9) board[i - 1][j] += 1;
                            if(board[i][j + 1] != 9) board[i][j + 1] += 1;
                            if(board[i - 1][j + 1] != 9) board[i - 1][j + 1] += 1;
                        }
                    } else if (j == 0) {
                        if (i > 0) {
                            if(board[i - 1][j] != 9) board[i - 1][j] += 1;
                            if(board[i - 1][j + 1] != 9) board[i - 1][j + 1] += 1;
                            if(board[i][j + 1] != 9) board[i][j + 1] += 1;
                            if (board[i + 1][j] != 9) board[i + 1][j] += 1;;
                            if(board[i + 1][j + 1] !=9) board[i + 1][j + 1] += 1;
                        }
                    } else if (j == column - 1) {
                        if (i > 0) {
                            if(board[i - 1][j] != 9) board[i - 1][j] += 1;
                            if(board[i - 1][j - 1] != 9) board[i - 1][j - 1] += 1;
                            if(board[i][j - 1] != 9) board[i][j - 1] += 1;
                            if (board[i + 1][j] != 9) board[i + 1][j] += 1;;
                            if(board[i + 1][j - 1] != 9) board[i + 1][j - 1] += 1;
                        }
                    } else {
                        if(board[i][j - 1] != 9) board[i][j - 1] += 1;
                        if(board[i][j + 1] != 9) board[i][j + 1] += 1;
                        if(board[i - 1][j - 1] != 9) board[i - 1][j - 1] += 1;
                        if(board[i - 1][j] != 9) board[i - 1][j] += 1;
                        if(board[i - 1][j + 1] != 9) board[i - 1][j + 1] += 1;
                        if(board[i + 1][j - 1] != 9) board[i + 1][j - 1] += 1;
                        if (board[i + 1][j] != 9) board[i + 1][j] += 1;;
                        if(board[i + 1][j + 1] !=9) board[i + 1][j + 1] += 1;
                    }
                }
            }
        }
    }

    void newGame(RenderWindow &window){
        for(int i=0; i<row; i++){
            for(int j=0; j<column; j++){
                board[i][j] = 0;
                flagspace[i][j] = 0;
                gameboard[i][j] = 10;
            }
        }
        generateMine();
        fillNum();
    }

    void reveal(RenderWindow &window, int i, int j){
        // type code
        if (board[i][j] == 0 && gameboard[i][j] == 10){
            // reveal surrounding
            if (flagspace[i][j] != 1){
                if(board[i][j] != 9){
                    gameboard[i][j] = board[i][j];
                }
            }

            if (i == 0) {
                if (j == 0) {
                    reveal(window, i, j+1);
                    if (gameboard[i][j+1] != 11) gameboard[i][j + 1] = board[i][j + 1];
                    reveal(window, i+1, j+1);
                    if (gameboard[i+1][j+1] != 11)gameboard[i + 1][j + 1] = board[i + 1][j + 1];
                    reveal(window, i+1, j);
                    if (gameboard[i+1][j] != 11)gameboard[i + 1][j] = board[i + 1][j];
                } else if (j == column - 1) {
                    reveal(window, i, j-1);
                    if (gameboard[i][j-1] != 11)gameboard[i][j - 1] = board[i][j - 1];
                    reveal(window, i+1, j-1);
                    if (gameboard[i+1][j-1] != 11)gameboard[i + 1][j - 1] = board[i + 1][j - 1];
                    reveal(window, i+1, j);
                    if (gameboard[i+1][j] != 11)gameboard[i + 1][j] = board[i + 1][j];
                } else if (j > 0 && j < column - 1) {
                    reveal(window, i, j+1);
                    if (gameboard[i][j+1] != 11)gameboard[i][j + 1]= board[i][j + 1];
                    reveal(window, i+1, j+1);
                    if (gameboard[i+1][j+1] != 11)gameboard[i + 1][j + 1] = board[i + 1][j + 1];
                    reveal(window, i+1, j);
                    if (gameboard[i+1][j] != 11)gameboard[i + 1][j] = board[i + 1][j];
                    reveal(window, i, j-1);
                    if (gameboard[i][j-1] != 11)gameboard[i][j - 1] = board[i][j - 1];
                    reveal(window, i+1, j-1);
                    if (gameboard[i+1][j-1] != 11)gameboard[i + 1][j - 1] = board[i + 1][j - 1];
                }
            } else if (i == row - 1) {
                if (j == 0) {
                    reveal(window, i, j+1);
                    if (gameboard[i][j+1] != 11)gameboard[i][j + 1] = board[i][j + 1];
                    reveal(window, i-1, j+1);
                    if (gameboard[i-1][j+1] != 11)gameboard[i - 1][j + 1] =board[i - 1][j + 1];
                    reveal(window, i-1, j);
                    if (gameboard[i-1][j] != 11)gameboard[i - 1][j] = board[i - 1][j];
                } else if (j == column - 1) {
                    reveal(window, i, j-1);
                    if (gameboard[i][j-1] != 11)gameboard[i][j - 1] = board[i][j - 1];
                    reveal(window, i-1, j-1);
                    if (gameboard[i-1][j-1] != 11)gameboard[i - 1][j - 1] = board[i - 1][j - 1];
                    reveal(window, i-1, j);
                    if (gameboard[i-1][j] != 11)gameboard[i - 1][j] = board[i - 1][j];
                } else if (j > 0 && j < column - 1) {
                    reveal(window, i, j-1);
                    if (gameboard[i][j-1] != 11)gameboard[i][j - 1] = board[i][j - 1];
                    reveal(window, i-1, j-1);
                    if (gameboard[i-1][j-1] != 11)gameboard[i - 1][j - 1] = board[i - 1][j - 1];
                    reveal(window, i-1, j);
                    if (gameboard[i-1][j] != 11)gameboard[i - 1][j] = board[i - 1][j];
                    reveal(window, i, j+1);
                    if (gameboard[i][j+1] != 11)gameboard[i][j + 1] =board[i][j + 1];
                    reveal(window, i-1, j+1);
                    if (gameboard[i-1][j+1] != 11)gameboard[i - 1][j + 1] = board[i - 1][j + 1];
                }
            } else if (j == 0) {
                if (i > 0) {
                    reveal(window, i-1, j);
                    if (gameboard[i-1][j] != 11)gameboard[i - 1][j] =board[i - 1][j];
                    reveal(window, i-1, j+1);
                    if (gameboard[i-1][j+1] != 11)gameboard[i - 1][j + 1] =board[i - 1][j + 1];
                    reveal(window, i, j+1);
                    if (gameboard[i][j+1] != 11)gameboard[i][j + 1] =board[i][j + 1];
                    reveal(window, i+1, j);
                    if (gameboard[i+1][j] != 11)gameboard[i + 1][j] = board[i + 1][j];
                    reveal(window, i+1, j+1);
                    if (gameboard[i+1][j+1] != 11)gameboard[i + 1][j + 1] = board[i + 1][j + 1];
                }
            } else if (j == column - 1) {
                if (i > 0) {
                    reveal(window, i-1, j);
                    if (gameboard[i-1][j] != 11)gameboard[i - 1][j] = board[i - 1][j];
                    reveal(window, i-1, j-1);
                    if (gameboard[i-1][j-1] != 11)gameboard[i - 1][j - 1] = board[i - 1][j - 1];
                    reveal(window, i, j-1);
                    if (gameboard[i][j-1] != 11)gameboard[i][j - 1] = board[i][j - 1];
                    reveal(window, i+1, j);
                    if (gameboard[i+1][j] != 11)gameboard[i + 1][j] = board[i + 1][j] ;
                    reveal(window, i+1, j-1);
                    if (gameboard[i+1][j-1] != 11)gameboard[i + 1][j - 1] = board[i + 1][j - 1];
                }
            } else {
                reveal(window, i, j-1);
                if (gameboard[i][j-1] != 11)gameboard[i][j - 1]= board[i][j - 1];
                reveal(window, i, j+1);
                if (gameboard[i][j+1] != 11)gameboard[i][j + 1] =board[i][j + 1];
                reveal(window, i-1, j-1);
                if (gameboard[i-1][j-1] != 11)gameboard[i - 1][j - 1] =board[i - 1][j - 1];
                reveal(window, i-1, j);
                if (gameboard[i-1][j] != 11)gameboard[i - 1][j] = board[i - 1][j];
                reveal(window, i-1, j+1);
                if (gameboard[i-1][j+1] != 11)gameboard[i - 1][j + 1]= board[i - 1][j + 1];
                reveal(window, i+1, j-1);
                if (gameboard[i+1][j-1] != 11)gameboard[i + 1][j - 1] = board[i + 1][j - 1];
                reveal(window, i+1, j);
                if (gameboard[i+1][j] != 11)gameboard[i + 1][j] = board[i + 1][j];
                reveal(window, i+1, j+1);
                if (gameboard[i+1][j+1] != 11)gameboard[i + 1][j + 1] = board[i + 1][j + 1];
            }
        }
    }

    void drawGameBoard(RenderWindow &window){
        Texture mineimage;
        mineimage.loadFromFile("files/images/mine.png");
        Sprite mine;
        mine.setTexture(mineimage);

        Texture flagimage;
        flagimage.loadFromFile("files/images/flag.png");
        Sprite flag;
        flag.setTexture(flagimage);

        Texture revealedimage;
        revealedimage.loadFromFile("files/images/tile_revealed.png");
        Sprite revealed_tile;
        revealed_tile.setTexture(revealedimage);

        Texture hiddenimage;
        hiddenimage.loadFromFile("files/images/tile_hidden.png");
        Sprite hidden_tile;
        hidden_tile.setTexture(hiddenimage);

        Texture number1image;
        number1image.loadFromFile("files/images/number_1.png");
        Sprite number1;
        number1.setTexture(number1image);

        Texture number2image;
        number2image.loadFromFile("files/images/number_2.png");
        Sprite number2;
        number2.setTexture(number2image);

        Texture number3image;
        number3image.loadFromFile("files/images/number_3.png");
        Sprite number3;
        number3.setTexture(number3image);

        Texture number4image;
        number4image.loadFromFile("files/images/number_4.png");
        Sprite number4;
        number4.setTexture(number4image);

        Texture number5image;
        number5image.loadFromFile("files/images/number_5.png");
        Sprite number5;
        number5.setTexture(number5image);

        Texture number6image;
        number6image.loadFromFile("files/images/number_6.png");
        Sprite number6;
        number6.setTexture(number6image);

        Texture number7image;
        number7image.loadFromFile("files/images/number_7.png");
        Sprite number7;
        number7.setTexture(number7image);

        Texture number8image;
        number8image.loadFromFile("files/images/number_8.png");
        Sprite number8;
        number8.setTexture(number8image);

        Sprite temp;
        for(int i=0; i < row; i++){
            for(int j=0; j<column; j++){
                temp = revealed_tile;
                temp.setPosition(Vector2f(j*32,i*32));
                window.draw(temp);

                if(gameboard[i][j] == 0){
                    continue;
                }
                if(gameboard[i][j] == 1){
                    temp = number1;
                }
                if(gameboard[i][j] == 2){
                    temp = number2;
                }
                if(gameboard[i][j] == 3){
                    temp = number3;
                }
                if(gameboard[i][j] == 4){
                    temp = number4;
                }
                if(gameboard[i][j] == 5){
                    temp = number5;
                }
                if(gameboard[i][j] == 6){
                    temp = number6;
                }
                if(gameboard[i][j] == 7){
                    temp = number7;
                }
                if(gameboard[i][j] == 8){
                    temp = number8;
                }
                if(gameboard[i][j] == 9){
                    temp = mine;
                }
                if(gameboard[i][j] == 10){
                    temp = hidden_tile;
                }
                if(gameboard[i][j] == 11){
                    temp = hidden_tile;
                    temp.setPosition(Vector2f(j*32, i*32));
                    window.draw(temp);
                    temp = flag;
                }
                temp.setPosition(Vector2f(j*32, i*32));
                window.draw(temp);
            }
        }
    }

    void updateCounter(RenderWindow &window, int remaining){
        Texture digitsimage0;
        digitsimage0.loadFromFile("files/images/digits.png", IntRect(0, 0, 21, 32));

        Texture digitsimage1;
        digitsimage1.loadFromFile("files/images/digits.png", IntRect(21, 0, 21, 32));

        Texture digitsimage2;
        digitsimage2.loadFromFile("files/images/digits.png", IntRect(42, 0, 21, 32));

        Texture digitsimage3;
        digitsimage3.loadFromFile("files/images/digits.png", IntRect(63, 0, 21, 32));

        Texture digitsimage4;
        digitsimage4.loadFromFile("files/images/digits.png", IntRect(84, 0, 21, 32));

        Texture digitsimage5;
        digitsimage5.loadFromFile("files/images/digits.png", IntRect(105, 0, 21, 32));

        Texture digitsimage6;
        digitsimage6.loadFromFile("files/images/digits.png", IntRect(126, 0, 21, 32));

        Texture digitsimage7;
        digitsimage7.loadFromFile("files/images/digits.png", IntRect(147, 0, 21, 32));

        Texture digitsimage8;
        digitsimage8.loadFromFile("files/images/digits.png", IntRect(168, 0, 21, 32));

        Texture digitsimage9;
        digitsimage9.loadFromFile("files/images/digits.png", IntRect(189, 0, 21, 32));

        Texture negative;
        negative.loadFromFile("files/images/digits.png", IntRect(210, 0, 21, 32));

        Sprite temp1;
        Sprite temp2;
        Sprite temp3;
        Sprite neg;

        neg.setPosition(Vector2f(12, 32 *((row)+0.5f)+16));
        temp1.setPosition(Vector2f(33, 32 * ((row)+0.5f)+16));
        temp2.setPosition(Vector2f(54, 32 * ((row)+0.5f)+16));
        temp3.setPosition(Vector2f(75, 32 * ((row)+0.5f)+16));

        if(remaining < 0){ neg.setTexture(negative);
            window.draw(neg);}

        int hundreds = abs(remaining/100);
        if(hundreds == 0){ temp1.setTexture(digitsimage0); }
        else if (hundreds == 1){ temp1.setTexture(digitsimage1); }
        else if (hundreds == 2){ temp1.setTexture(digitsimage2); }
        else if (hundreds == 3){ temp1.setTexture(digitsimage3); }
        else if (hundreds == 4){ temp1.setTexture(digitsimage4); }
        else if (hundreds == 5){ temp1.setTexture(digitsimage5); }
        else if (hundreds == 6){ temp1.setTexture(digitsimage6); }
        else if (hundreds == 7){ temp1.setTexture(digitsimage7); }
        else if (hundreds == 8){ temp1.setTexture(digitsimage8); }
        else if (hundreds == 9){ temp1.setTexture(digitsimage9); }

        int tens = abs(remaining)/10;
        if(tens == 0){ temp2.setTexture(digitsimage0); }
        else if (tens == 1){ temp2.setTexture(digitsimage1); }
        else if (tens == 2){ temp2.setTexture(digitsimage2); }
        else if (tens == 3){ temp2.setTexture(digitsimage3); }
        else if (tens == 4){ temp2.setTexture(digitsimage4); }
        else if (tens == 5){ temp2.setTexture(digitsimage5); }
        else if (tens == 6){ temp2.setTexture(digitsimage6); }
        else if (tens == 7){ temp2.setTexture(digitsimage7); }
        else if (tens == 8){ temp2.setTexture(digitsimage8); }
        else if (tens == 9){ temp2.setTexture(digitsimage9); }

        int ones = abs(remaining)%10;
        if(ones == 0){ temp3.setTexture(digitsimage0); }
        else if (ones == 1){ temp3.setTexture(digitsimage1); }
        else if (ones == 2){ temp3.setTexture(digitsimage2); }
        else if (ones == 3){ temp3.setTexture(digitsimage3); }
        else if (ones == 4){ temp3.setTexture(digitsimage4); }
        else if (ones == 5){ temp3.setTexture(digitsimage5); }
        else if (ones == 6){ temp3.setTexture(digitsimage6); }
        else if (ones == 7){ temp3.setTexture(digitsimage7); }
        else if (ones == 8){ temp3.setTexture(digitsimage8); }
        else if (ones == 9){ temp3.setTexture(digitsimage9); }

        window.draw(temp1);
        window.draw(temp2);
        window.draw(temp3);
    }

    void drawtestBoard(RenderWindow &window){ // FOR ALL REVEALED TILES
        Texture mineimage;
        mineimage.loadFromFile("files/images/mine.png");
        Sprite mine;
        mine.setTexture(mineimage);

        Texture revealedimage;
        revealedimage.loadFromFile("files/images/tile_revealed.png");
        Sprite revealed_tile;
        revealed_tile.setTexture(revealedimage);

        Texture hiddenimage;
        hiddenimage.loadFromFile("files/images/tile_hidden.png");
        Sprite hidden_tile;
        hidden_tile.setTexture(hiddenimage);

        Texture number1image;
        number1image.loadFromFile("files/images/number_1.png");
        Sprite number1;
        number1.setTexture(number1image);

        Texture number2image;
        number2image.loadFromFile("files/images/number_2.png");
        Sprite number2;
        number2.setTexture(number2image);

        Texture number3image;
        number3image.loadFromFile("files/images/number_3.png");
        Sprite number3;
        number3.setTexture(number3image);

        Texture number4image;
        number4image.loadFromFile("files/images/number_4.png");
        Sprite number4;
        number4.setTexture(number4image);

        Texture number5image;
        number5image.loadFromFile("files/images/number_5.png");
        Sprite number5;
        number5.setTexture(number5image);

        Texture number6image;
        number6image.loadFromFile("files/images/number_6.png");
        Sprite number6;
        number6.setTexture(number6image);

        Texture number7image;
        number7image.loadFromFile("files/images/number_7.png");
        Sprite number7;
        number7.setTexture(number7image);

        Texture number8image;
        number8image.loadFromFile("files/images/number_8.png");
        Sprite number8;
        number8.setTexture(number8image);

        Sprite temp;
        int x = 0;
        for(int i=0; i < row; i++){
            for(int j=0; j<column; j++){
                temp = revealed_tile;
                temp.setPosition(Vector2f(j*32,i*32));
                window.draw(temp);

                if(board[i][j] == 0){
                    continue;
                }
                if(board[i][j] == 1){
                    temp = number1;
                }
                if(board[i][j] == 2){
                    temp = number2;
                }
                if(board[i][j] == 3){
                    temp = number3;
                }
                if(board[i][j] == 4){
                    temp = number4;
                }
                if(board[i][j] == 5){
                    temp = number5;
                }
                if(board[i][j] == 6){
                    temp = number6;
                }
                if(board[i][j] == 7){
                    temp = number7;
                }
                if(board[i][j] == 8){
                    temp = number8;
                }
                if(board[i][j] == 9){
                    temp = mine;
                }
                if(board[i][j] == 10){
                    temp = hidden_tile;
                }
                temp.setPosition(Vector2f(j*32, i*32));
                window.draw(temp);
            }
        }
    }

};