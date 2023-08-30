#include <iostream>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <string>
#include "board.h"

using namespace std;
using namespace sf;
using namespace chrono;

void setText(Text &text, float x, float y){
    FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top +
        textRect.height/2.0f);
    text.setPosition(Vector2f(x, y));
}

int main()
{
//  initialization of config values
    int window_width;
    int window_height;
    int mine_count;
    int tile_count;
    int numcol;
    int numrow;

//  opens and reads board_config
    fstream configs;
    configs.open("files/board_config.cfg",ios_base::in);
    if(configs.is_open()){
        string readLine;
        getline(configs, readLine);
        numcol = stoi(readLine);

        getline(configs, readLine);
        numrow = stoi(readLine);

        getline(configs, readLine);
        mine_count = stoi(readLine);

        configs.close();
    }
    else{
        cout << "file not opened\n";
    }

//    sets window configurations to variables
    tile_count = numrow * numcol;
    window_width = numcol * 32;
    window_height = numrow * 32 + 100;
//    mine_count = 2;
    Board game = Board(window_width, window_height, mine_count, tile_count);

//    cout << tile_count << endl;
//    cout << window_width << endl;
//    cout << window_height << endl;
//    cout << mine_count << endl;

    fstream ldrbrd;
    ldrbrd.open("files/leaderboard.txt",ios_base::in);
    if(ldrbrd.is_open()){
        string readLine;
        string split = ",";
        while (getline(ldrbrd, readLine)){
            string time = "";
            string name = "";
            time = readLine.substr(0, readLine.find(split));
            readLine = readLine.substr(readLine.find(split)+1);
            name = readLine.substr(0, readLine.find(split));
            game.leaderboard.emplace(time, name);
        }
        ldrbrd.close();
    }
    else{
        cout << "file not opened\n";
    }
//    for (game.iter = game.leaderboard.begin(); game.iter != game.leaderboard.end(); game.iter++){
//        cout << game.iter->first << endl;
//        cout << game.iter->second << endl;
//    }

// fonts
    Font font;
    if(!font.loadFromFile("files/font.ttf")){
        cout << "error loading font file\n";
    }

//    text configs
    string cursor = "|";
    Text welcomeText; // pos- width/2.0, height/2.0 - 150
    welcomeText.setFont(font);
    welcomeText.setString("WELCOME TO MINESWEEPER!");
    welcomeText.setStyle(Text::Bold | Text::Underlined);
    welcomeText.setCharacterSize(24);
    setText(welcomeText, window_width/2.0f, window_height/2.0f - 150);

    Text inputPromptText; // pos- width/2.0, height/2.0 - 75
    inputPromptText.setFont(font);
    inputPromptText.setString("Enter your name:");
    inputPromptText.setStyle(Text::Bold);
    inputPromptText.setCharacterSize(20);
    setText(inputPromptText, window_width/2.0f, window_height/2.0f - 75);

    Text inputText; // pos- width/2.0, height/2.0 - 45
    inputText.setFont(font);
    inputText.setString(cursor);
    inputText.setStyle(Text::Bold);
    inputText.setCharacterSize(20);
    inputText.setFillColor(Color::Yellow);
    setText(inputText, window_width/2.0f, window_height/2.0f - 45);
    string input;

    // draws welcome window with configurations
    RenderWindow welcomeWindow(VideoMode(window_width, window_height), "Minesweeper", Style::Close);
//  if window is opened
//    string playername = "";
    while (welcomeWindow.isOpen()){
        Event event;
        while (welcomeWindow.pollEvent(event))
        {
            if (event.type == Event::Closed) {
                welcomeWindow.close();
                return 0;
            }
            if (event.type == Event::TextEntered){
                if (input.size()<10){
                    if(isalpha(event.text.unicode)){
                        if (input.size() == 0){
                            input += toupper(event.text.unicode);
                        }
                        else {
                            input += tolower(event.text.unicode);
                        }
                        inputText.setString(input + cursor);
                        setText(inputText, window_width/2.0f, window_height/2.0f - 45);
                    }
                }
                if(Keyboard::isKeyPressed(Keyboard::BackSpace)){
                    input = input.substr(0, input.size()-1);
                    inputText.setString(input + cursor);
                    setText(inputText, window_width/2.0f, window_height/2.0f - 45);
                }
            }
            if(input.size()>0){
                if (Keyboard::isKeyPressed(Keyboard::Enter)){
                    welcomeWindow.close();
                }
            }
        }

        welcomeWindow.clear(Color::Blue);
        welcomeWindow.draw(welcomeText);
        welcomeWindow.draw(inputPromptText);
        welcomeWindow.draw(inputText);
        welcomeWindow.display();

    }
    RenderWindow gameWindow(VideoMode(window_width, window_height), "Minesweeper", Style::Close);

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

    Texture happyfaceimage;
    happyfaceimage.loadFromFile("files/images/face_happy.png");

    Texture winfaceimage;
    winfaceimage.loadFromFile("files/images/face_win.png");

    Texture losefaceimage;
    losefaceimage.loadFromFile("files/images/face_lose.png");

    Sprite facebutton;
    facebutton.setTexture(happyfaceimage);
    facebutton.setPosition(Vector2f((((numcol) / 2.0) * 32) - 32, 32 *((numrow)+0.5f)));

    Texture flagimage;
    flagimage.loadFromFile("files/images/flag.png");
    Sprite flag;
    flag.setTexture(flagimage);

    Texture debugimage;
    debugimage.loadFromFile("files/images/debug.png");
    Sprite debugbutton;
    debugbutton.setTexture(debugimage);
    debugbutton.setPosition(Vector2f(((numcol) * 32) - 304, 32 * ((numrow)+0.5f)));

    Texture pauseimage;
    pauseimage.loadFromFile("files/images/pause.png");

    Texture playimage;
    playimage.loadFromFile("files/images/play.png");

    Sprite pauseplaybutton;
    pauseplaybutton.setTexture(pauseimage);
    pauseplaybutton.setPosition(Vector2f(((numcol) * 32) - 240, 32 * ((numrow)+0.5f)));

    Texture leaderboardimage;
    leaderboardimage.loadFromFile("files/images/leaderboard.png");
    Sprite button;
    button.setTexture(leaderboardimage);
    button.setPosition(Vector2f(((numcol) * 32) - 176, 32 * ((numrow)+0.5f)));

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

    game.updateCounter(gameWindow, mine_count);

//    bool gameover = false;

    Clock clock;

    bool gameGenerate = true;
    bool debugmode = false;
    int debugcount = 0;
    int pauseplaybuttoncount = 0;
    bool ispause = false;
    int remainingMineCount = mine_count;
    bool gamelose = false;
    bool gamewin = false;
    bool flagged = false;
    bool gameover = false;
    int correctflag = 0;
    int currtime = 0;
    int ispausetime = 0;
    int diff = 0;
    int nonrevealedtiles = 0;

    while (gameWindow.isOpen()){
        Event event;
        Time time = clock.getElapsedTime();
        currtime = time.asSeconds();
//        game.updateTime(gameWindow, currtime);
        while (gameWindow.pollEvent(event)){
            if (event.type == Event::Closed){
                gameWindow.close(); }

            while (gameGenerate){
                game.generateMine();
                game.fillNum();
                gameGenerate = false;
            }


            if(event.type == Event::MouseButtonPressed){
                if (event.mouseButton.button == Mouse::Left){
                    int count = 0;
                    Vector2i pos = Mouse::getPosition(gameWindow);
//                    cout << pos.x << " " << pos.y << endl;
                    if(facebutton.getGlobalBounds().contains(pos.x, pos.y)){
                        // RESTART
                        game.newGame(gameWindow);
                        gamelose = false;
                        gamewin = false;
                        gameover = false;
                        debugmode = false;
                        remainingMineCount = mine_count;
                        correctflag = 0;
                        clock.restart();
                         debugcount = 0;
                         pauseplaybuttoncount = 0;
                         ispause = false;
                         ispausetime = 0;
                         correctflag = 0;
                         currtime = 0;
                         pauseplaybutton.setTexture(pauseimage);
                        facebutton.setTexture(happyfaceimage);
                    }
                    else if(debugbutton.getGlobalBounds().contains(pos.x, pos.y)){
                        if (debugcount%2 == 0 && !gameover && !ispause){ // debug button
                            debugmode = true;
                        }
                        else{
                            debugmode = false;
                        }
                        debugcount++;
                    }
                    else if(pauseplaybutton.getGlobalBounds().contains(pos.x, pos.y)){
                        if (!gamelose && !gameover){ // pause or play button
                            if (pauseplaybuttoncount % 2 == 0) { // PAUSE
                                pauseplaybutton.setTexture(playimage);
                                ispausetime += currtime;
                                ispause = true;
//                                cout << "PAUSE time: " << ispausetime << endl;
                            } else { // PLAY
                                pauseplaybutton.setTexture(pauseimage);
                                ispause = false;
//                                cout << "PLAY time: " << currtime << endl;
//                                diff =  currtime - ispausetime;
//                                currtime -= diff;
//                                cout << "PLAY UPDATE: " << currtime << endl;
//                                cout << endl;
//                                game.updateTime(gameWindow, currtime);
//                                ispausetime = 0;

                            }
                            pauseplaybuttoncount++;
                        }
                    }
                    else if(button.getGlobalBounds().contains(pos.x, pos.y)){
                        // leaderboard button
                        diff = ispausetime;
                        ispause = true;
                        RenderWindow leadershipWindow(VideoMode(window_width/2, window_height/2), "Minesweeper", Style::Close);
                        Text leaderboardText; // pos- width/2.0, height/2.0 - 150
                        leaderboardText.setFont(font);
                        leaderboardText.setString("LEADERBOARD");
                        leaderboardText.setStyle(Text::Bold | Text::Underlined);
                        leaderboardText.setCharacterSize(20);
                        setText(leaderboardText, window_width/4.0f, window_height/4.0f - 120);

                        Text recordtext;
                        recordtext.setFont(font);
                        recordtext.setStyle(Text::Bold);
                        recordtext.setCharacterSize(18);
                        setText(recordtext, window_width/4.0f - 120, window_height/4.0f - 80);

                        int count = 1;

                        string record;
                        for (game.iter = game.leaderboard.begin(); game.iter != game.leaderboard.end(); game.iter++){
                            if (count > 5){
                                continue;
                            }
                            record += to_string(count) + ".\t" + game.iter->first + "\t" + game.iter->second + "\n\n";
                            count++;
                        }

                        recordtext.setString(record);

                        while (leadershipWindow.isOpen()){
                            game.allrevealedtiles(gameWindow, revealed_tile);
                            gameWindow.display();

                            Event event;
                            while (leadershipWindow.pollEvent(event)){
                                if (event.type == Event::Closed)
                                    leadershipWindow.close();
                                if (pauseplaybuttoncount % 2 == 1) {
                                    ispausetime = diff;
                                    ispause = true; }
                                else {
//                                    cout << "pause time leader: " << ispausetime;
//                                    cout << "    curr time leader: " << currtime ;
//                                    cout << "    diff time leader: " << diff << endl ;
                                    ispausetime = diff + currtime;
                                    clock.restart();
                                    ispause = false; }
                            }

                            leadershipWindow.clear(Color::Blue);
                            leadershipWindow.draw(leaderboardText);
                            leadershipWindow.draw(recordtext);
                            leadershipWindow.display();
                        }
                    }
                    if(pos.y < numrow*32){
                        int xx = pos.x/32;
                        int yy = pos.y/32;
//                        cout << "x: " << xx << endl;
//                        cout << "y: " << yy << endl;
//                        cout << game.board[yy][xx] << endl;
                        if(!gamelose && !gameover && !ispause){
                            if (game.board[yy][xx] == 9 && game.gameboard[yy][xx] != 11) {
                                facebutton.setTexture(losefaceimage);
                                gamelose = true;
                                debugmode = false;
                            } else if (game.board[yy][xx] == 0 && game.gameboard[yy][xx] != 11) {
                                game.reveal(gameWindow, yy, xx);
                            } else if (game.gameboard[yy][xx] != 11) {
                                game.gameboard[yy][xx] = game.board[yy][xx];
                            }
                        }
                    }
                }
                if (event.mouseButton.button == Mouse::Right){
                    // insert flag
                    Vector2i pos = Mouse::getPosition(gameWindow);
                    if(pos.y < numrow*32){
                        int xx = pos.x/32;
                        int yy = pos.y/32;
                        if (game.gameboard[yy][xx] == 11){
                            flagged = true;
                        }
                        else {
                            flagged = false;
                        }
                        if (!flagged && !gameover && !ispause){
                            if (game.gameboard[yy][xx] == 10) {
                                game.gameboard[yy][xx] = 11;
                                game.flagspace[yy][xx] += 1;
                                remainingMineCount--;
                                game.updateCounter(gameWindow, remainingMineCount);
                                if (game.board[yy][xx] == 9) { correctflag++; }
                                game.revealFlags(gameWindow, flag);
                            }
                        }
                        if (flagged && !gameover){
                            game.gameboard[yy][xx] = 10;
                            game.flagspace[yy][xx] -= 1;
                            remainingMineCount++;
                            game.updateCounter(gameWindow, remainingMineCount);
                            if(game.board[yy][xx] == 9) { correctflag--; }
                            game.revealFlags(gameWindow, flag);
                        }

                    }
                }
            }
            nonrevealedtiles = 0;
            for(int i =0; i<game.gameboard.size();i++){
                for (int j=0; j<game.gameboard[i].size(); j++){
                    if (game.gameboard[i][j] == 10 || game.gameboard[i][j] == 11 ){
                        nonrevealedtiles++;
                    }
                }
            }
            if(nonrevealedtiles == mine_count){
                for (int x=0; x<game.gameboard.size(); x++){
                    for (int y=0; y<game.gameboard[x].size(); y++){
                        if (game.board[x][y] == 9){
                            game.flagspace[x][y] = 1;
                            game.gameboard[x][y] = 11;
                            game.revealFlags(gameWindow, flag);
                        }
                    }
                }
                game.updateCounter(gameWindow, 0);
                remainingMineCount = 0;
                game.drawGameBoard(gameWindow);
            }
//            cout << nonrevealedtiles << endl;
            if ((correctflag == mine_count && remainingMineCount == 0) || (nonrevealedtiles == mine_count)){
                game.updateCounter(gameWindow, 0);
                if (!gameover && !gamelose) {
                    gamewin = true;
                    ispause = true;

//                    game.drawGameBoard(gameWindow);
//                    gameWindow.display();

                    currtime += ispausetime;
                    ispausetime = currtime;
                    int one = (currtime/60)/10;
                    int two = (currtime/60)%10;
                    int three = (currtime%60)/10;
                    int four = (currtime%60)%10;

                    string playername = "";
                    for (int i = 0; i < input.size(); i++){
                        if (i == 0){
                            playername += toupper(input.at(i));
                        }
                        else{
                            playername += tolower(input.at(i));
                        }
                    }
                    playername += "*";

                    string stime = "";
                    stime = to_string(one) + to_string(two) + ":"
                            + to_string(three) + to_string(four);

                    game.leaderboard.emplace(stime, playername);

                    facebutton.setTexture(winfaceimage);
                    gameWindow.draw(facebutton);
                    gameWindow.display();

                    gameover = true;
                    RenderWindow leadershipWindow(VideoMode(window_width / 2, window_height / 2), "Minesweeper",
                                                  Style::Close);
                    Text leaderboardText; // pos- width/2.0, height/2.0 - 150
                    leaderboardText.setFont(font);
                    leaderboardText.setString("LEADERBOARD");
                    leaderboardText.setStyle(Text::Bold | Text::Underlined);
                    leaderboardText.setCharacterSize(20);
                    setText(leaderboardText, window_width / 4.0f, window_height / 4.0f - 120);

                    Text recordtext;
                    recordtext.setFont(font);
                    recordtext.setStyle(Text::Bold);
                    recordtext.setCharacterSize(18);
                    setText(recordtext, window_width / 4.0f - 120, window_height / 4.0f - 80);

                    int count = 1;

                    string record;
                    for (game.iter = game.leaderboard.begin(); game.iter != game.leaderboard.end(); game.iter++) {
                        if (count > 5) {
                            continue;
                        } else {
                            record += to_string(count) + ".\t" + game.iter->first + "\t" + game.iter->second + "\n\n";
                            count++;
                        }
                    }

                    recordtext.setString(record);

                    while (leadershipWindow.isOpen()) {

                        Event event;
                        while (leadershipWindow.pollEvent(event)) {
                            if (event.type == Event::Closed)
                            leadershipWindow.close();
                        }

                        leadershipWindow.clear(Color::Blue);
                        leadershipWindow.draw(leaderboardText);
                        leadershipWindow.draw(recordtext);
                        leadershipWindow.display();
                    }
                    playername = playername.substr(0, playername.size()-1);
                    game.leaderboard[stime] = playername;
                }
            }

        }

        gameWindow.clear(Color::White);
        if (gamewin){
            for (int x=0; x<game.gameboard.size(); x++){
                for (int y=0; y<game.gameboard[x].size(); y++){
                    if (game.board[x][y] == 9){
                        game.flagspace[x][y] = 1;
                        game.gameboard[x][y] = 11;
                        game.revealFlags(gameWindow, flag);
                    }
                }
            }
            game.drawGameBoard(gameWindow);
        }
        else if (ispause){
            debugmode = false;
            game.allrevealedtiles(gameWindow, revealed_tile);
        }
        else{
            if (debugcount%2 == 0){ // debug button
                debugmode = false;
            }
            else{
                debugmode = true;
            }
            game.drawGameBoard(gameWindow);
        }
//        game.drawGameBoard(gameWindow);


        if (debugmode || gamelose){ game.revealMine(gameWindow,mine); }

        if (!gamelose || !gameover){
            if (ispause) {
                game.updateTime(gameWindow, ispausetime);
                clock.restart();}
            else {
                currtime += ispausetime;
                game.updateTime(gameWindow, currtime);
            }
        }
        if(gamelose || gameover){
            game.updateTime(gameWindow, ispausetime);
        }

        game.updateCounter(gameWindow, remainingMineCount);
        gameWindow.draw(facebutton);
        gameWindow.draw(debugbutton);
        gameWindow.draw(pauseplaybutton);
        gameWindow.draw(button);
        gameWindow.display();

    }

    return 0;
}

//shape draw example
//    CircleShape shape(100.f);
//    shape.setFillColor(Color::Red);