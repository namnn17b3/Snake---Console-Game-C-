#include "DoHoa.h"

bool cmp(pair<string, int> alpha, pair<string, int> beta)
{
    if (alpha.second > beta.second)
        return true;
    if (alpha.second == beta.second)
        return alpha.first < beta.first;
    return false;
}

struct Point
{
    int x, y;
    char huong;
};

void SoundEffect();
void AddFront();
void Play();
void NewGame();
void ContinueGame();
void HighScore();
void PlayGame();
void ChooseLevel();
void MainMenu();
void LoadData();
void WriteData();
int ParseInt(string);

unordered_map<string, int> score_table;
vector<pair<string, int>> vt;
string current_player = "";
const string tym[] = {"\u2665", "\u2764"};
const int N = 1e5 + 7;
unordered_set<int> exist;
int score = 0;
int level = 150;
int current_high_score = 0;
string level_string = "2. NORMAL";
string status[] = {"PLAYING...", "PAUSING...", "GAME OVER "};
deque<Point> Q;

int Random(int minN, int maxN)
{
    return minN + rand() % (maxN - minN + 1);
}

Point RandomPoint()
{
    Point res;
    do
    {
        res.x = Random(1, 65);
        res.y = Random(1, 34);
    }
    while (exist.find(res.x * N + res.y) != exist.end());
    return res;
}

void SoundEffect()
{
    PlaySound(TEXT("effect.wav"), NULL, SND_LOOP);
}

void AddFront()
{
    if (Q.front().huong == 'a')
        Q.push_front({Q.front().x - 1, Q.front().y, 'a'});
    else if (Q.front().huong == 'd')
        Q.push_front({Q.front().x + 1, Q.front().y, 'd'});
    else if (Q.front().huong == 'w')
        Q.push_front({Q.front().x, Q.front().y - 1, 'w'});
    else if (Q.front().huong == 's')
        Q.push_front({Q.front().x, Q.front().y + 1, 's'});
}

void Play()
{
    exist.clear();
    Q.clear();
    score = 0;
    SetColor(0, 7);
    ClearScreen();
    SetFontSize(20);
    SetColor(10, 5);
    ResizeConsole(1000, 800);
    for (int i = 0; i < 38; i++)
    {
        Gotoxy(0, 0 + i);
        cout << "░" << endl;
        Gotoxy(70, 0 + i);
        cout << "░" << endl;
    }
    for (int i = 0; i < 70; i++)
    {
        Gotoxy(0 + i, 0);
        cout << "░";
        Gotoxy(0 + i, 37);
        cout << "░";
    }
    SetColor(11, 4);
    for (int i = 0; i < 13; i++)
    {
        Gotoxy(73, 0 + i);
        for (int j = 0; j < 27; j++)
            cout << ' ';
        cout << endl;
        Gotoxy(73, 25 + i);
        for (int j = 0; j < 27; j++)
            cout << ' ';
        cout << endl;
    }
    Gotoxy(73, 2);
    cout << "===========================" << endl;
    Gotoxy(74, 4);
    cout << "Design by Nguyễn Ngọc Nam" << endl;
    Gotoxy(73, 6);
    cout << "===========================" << endl;
    Gotoxy(73, 29);
    cout << "===========================" << endl;
    Gotoxy(78, 31);
    cout << "__17-B3__Legend__" << endl;
    Gotoxy(73, 33);
    cout << "===========================" << endl;
    SetColor(6, 4);
    for (int i = 0; i < 16; i++)
    {
        Gotoxy(73, 9 + i);
        for (int j = 0; j < 27; j++)
            cout << ' ';
        cout << endl;
    }
    SetColor(6, 15);
    Gotoxy(75, 10);
    cout << "Player Name: " << current_player << endl;
    Gotoxy(75, 11);
    cout << "Level: " << level_string << endl;
    Gotoxy(75, 12);
    cout << "High Score: " << current_high_score << endl;
    Gotoxy(82, 13);
    cout << "Left: A" << endl;
    Gotoxy(82, 14);
    cout << "Right: D" << endl;
    Gotoxy(82, 15);
    cout << "Up: W" << endl;
    Gotoxy(82, 16);
    cout << "Down: S" << endl;
    Gotoxy(82, 17);
    cout << "Pause: P" << endl;
    Gotoxy(82, 18);
    cout << "Replay: R" << endl;
    Gotoxy(82, 19);
    cout << "Back: B" << endl;
    Gotoxy(82, 20);
    cout << tym[0] << ": 10 Point" << endl;
    Gotoxy(82, 21);
    cout << tym[1] << ": 20 Point" << endl;
    Gotoxy(82, 22);
    cout << "Score: " << score << endl;
    Gotoxy(78, 23);
    SetColor(6, 4);
    cout << "Status: " << status[0] << endl;
    Point front = {2, 5, 'd'};
    Point back = {1, 5, 'd'};
    Point before_front = back;
    Point old_back;
    exist.insert(front.x * N + front.y);
    exist.insert(back.x * N + back.y);
    SetColor(12, 7);
    Gotoxy(back.x, back.y);
    cout << ' ';
    Gotoxy(front.x, front.y);
    SetColor(4, 7);
    cout << ' ';
    Q.push_back(front);
    Q.push_back(back);
    char huong = 'd';
    char old_huong = 'd';
    srand(time(0));
    Point food = RandomPoint();
    string heart = tym[Random(0, 1)];
    Gotoxy(food.x, food.y);
    SetColor(0, 4);
    cout << heart;
    Gotoxy(0, 0);
    Sleep(700);
    while (true)
    {
        if (kbhit())
        {
            huong = getch();
            if (huong != 'a' && huong != 'd' && huong != 's' && huong != 'w'
                && huong != 'p' && huong != 'r' && huong != 'b')
                    huong = old_huong;

            if (huong == 'p')
            {
                SetColor(6, 15);
                Gotoxy(82, 17);
                cout << "Continue: C" << endl;
                Gotoxy(78, 23);
                SetColor(6, 4);
                cout << "Status: " << status[1] << endl;
                while ((huong = getch()) != 'c');
            }
            else if (huong == 'a' || huong == 'd' || huong == 'w' || huong == 's')
            {
                if ((huong == 'a' && old_huong != 'a' && old_huong != 'd') || (huong == 'd' && old_huong != 'a' && old_huong != 'd')
                    || (huong == 's' && old_huong != 's' && old_huong != 'w') || (huong == 'w' && old_huong != 's' && old_huong != 'w'))
                {
                    Point tmp = Q.front();
                    Q.pop_front();
                    Q.push_front({tmp.x, tmp.y, huong});
                }
                else
                {
                    while (kbhit()) getch();
                }
            }
            else if (huong == 'r')
            {
                score_table[current_player] = current_high_score;
                WriteData();
                Play();
                break;
            }
            else if (huong == 'b')
            {
                score_table[current_player] = current_high_score;
                WriteData();
                SetFontSize(8);
                ResizeConsole(1000, 600);
                SetColor(0, 7);
                ClearScreen();
                PlayGame();
                break;
            }
        }
        old_huong = huong;
        SetColor(6, 15);
        Gotoxy(82, 17);
        cout << "Pause: P   " << endl;

        Gotoxy(78, 23);
        SetColor(6, 4);
        cout << "Status: " << status[0] << endl;

        old_back = Q.back();
        Q.pop_back();
        exist.erase(old_back.x * N + old_back.y);
        AddFront();

        if (Q.front().x > 0 && Q.front().x < 70 && Q.front().y > 0 && Q.front().y < 37
            && exist.find(Q.front().x * N + Q.front().y) == exist.end())
        {
            Gotoxy(before_front.x, before_front.y);
            SetColor(12, 7);
            cout << ' ';

            Gotoxy(old_back.x, old_back.y);
            SetColor(0, 7);
            cout << ' ';

            Gotoxy(Q.back().x, Q.back().y);
            SetColor(12, 7);
            cout << ' ';

            Gotoxy(Q.front().x, Q.front().y);
            SetColor(4, 7);
            cout << ' ';
            before_front = Q.front();

            exist.insert(Q.front().x * N + Q.front().y);
            if (Q.front().x == food.x && Q.front().y == food.y)
            {
                thread sound_effect(SoundEffect);
                sound_effect.detach();

                before_front = Q.front();
                Gotoxy(before_front.x, before_front.y);
                SetColor(12, 7);
                cout << ' ';
                exist.insert(before_front.x * N + before_front.y);

                AddFront();
                Gotoxy(Q.front().x, Q.front().y);
                SetColor(4, 7);
                cout << ' ';
                exist.insert(Q.front().x * N + Q.front().y);
                before_front = Q.front();

                score += (heart == tym[0]) ? 10 : 20;
                Gotoxy(82, 22);
                SetColor(6, 15);
                cout << "Score: " << score << endl;

                current_high_score = max(score, current_high_score);
                Gotoxy(75, 12);
                cout << "High Score: " << current_high_score << endl;

                food = RandomPoint();
                heart = tym[Random(0, 1)];
                Gotoxy(food.x, food.y);
                SetColor(0, 4);
                cout << heart;
            }
            Sleep(level);
        }
        else
        {
            Gotoxy(78, 23);
            SetColor(6, 4);
            cout << "Status: " << status[2] << endl;
            do
            {
                huong = getch();
            }
            while (huong != 'r' && huong != 'b');
            if (huong == 'r')
            {
                score_table[current_player] = current_high_score;
                WriteData();
                Play();
            }
            else if (huong == 'b')
            {
                score_table[current_player] = current_high_score;
                WriteData();
                SetFontSize(8);
                ResizeConsole(1000, 600);
                SetColor(0, 7);
                ClearScreen();
                PlayGame();
            }
            break;
        }
    }
}

void NewGame()
{
    SetFontSize(20);
    SetColor(10, 5);
    for (int i = 0; i < 24; i++)
    {
        Gotoxy(1, 20 + i);
        cout << "░" << endl;
        Gotoxy(90, 20 + i);
        cout << "░" << endl;
    }
    for (int i = 0; i < 89; i++)
    {
        Gotoxy(2 + i, 20);
        cout << "░";
        Gotoxy(2 + i, 43);
        cout << "░";
    }
    SetColor(14, 5);
    for (int i = 0; i < 5; i++)
    {
        Gotoxy(25, 29 + i);
        cout << "░" << endl;
        Gotoxy(65, 29 + i);
        cout << "░" << endl;
    }
    for (int i = 0; i < 40; i++)
    {
        Gotoxy(25 + i, 29);
        cout << "░";
        Gotoxy(25 + i, 33);
        cout << "░";
    }
    Gotoxy(38, 28);
    SetColor(11, 4);
    cout << "NEW PLAYER NAME\n";
    while (true)
    {
        ShowCur(true);
        Gotoxy(26, 31);
        SetColor(0, 15);
        string player_name;
        getline(cin, player_name);
        ShowCur(false);
        if (score_table.find(player_name) != score_table.end())
        {
            Gotoxy(35, 35);
            SetColor(0, 15);
            cout << "PLAYER ALREADY EXISTS" << endl;
            Gotoxy(26, 31);
            cout << "                                       ";
            Gotoxy(26, 31);
            continue;
        }
        else
        {
            current_player = player_name;
            current_high_score = 0;
            score_table[current_player] = 0;
            SetColor(0, 7);
            ClearScreen();
            Play();
            break;
        }
    }
}

void ContinueGame()
{
    SetFontSize(20);
    SetColor(10, 5);
    for (int i = 0; i < 24; i++)
    {
        Gotoxy(1, 20 + i);
        cout << "░" << endl;
        Gotoxy(90, 20 + i);
        cout << "░" << endl;
    }
    for (int i = 0; i < 89; i++)
    {
        Gotoxy(2 + i, 20);
        cout << "░";
        Gotoxy(2 + i, 43);
        cout << "░";
    }
    if (vt.size() > 0)
    {
        for (int i = 0; i < vt.size(); i++)
        {
            if (i == 0) SetColor(14, 5);
            else SetColor(0, 7);
            Gotoxy(38, 28 + i * 2);
            cout << i + 1 << "." << vt[i].first << endl;
        }
        int cnt = 0;
        while (true)
        {
            char c = getch();
            if (c == 13) break;
            if (c != -32) continue;
            c = getch();
            if (c == 72) cnt = (cnt - 1 + vt.size()) % vt.size();
            else if (c == 80) cnt = (cnt + 1 + vt.size()) % vt.size();
            for (int i = 0; i < vt.size(); i++)
            {
                if (i != cnt) SetColor(0, 7);
                else SetColor(14, 5);
                Gotoxy(38, 28 + i * 2);
                cout << i + 1 << "." << vt[i].first << endl;
            }
        }
        for (int i = 0; i < vt.size(); i++)
        {
            if (i == cnt)
            {
                current_player = vt[i].first;
                current_high_score = vt[i].second;
                break;
            }
        }
        Play();
    }
    else
    {
        Gotoxy(34, 30);
        SetColor(0, 15);
        cout << "LIST HIGH SCORE IS EMPTY" << endl;
        Gotoxy(34, 32);
        cout << "PRESS B TO BACK" << endl;
        char c;
        while ((c = getch()) != 'b');
        SetFontSize(8);
        ClearScreen();
        PlayGame();
    }
}

void HighScore()
{
    ResizeConsole(400, 250);
    SetFontSize(20);
    SetColor(10, 5);
    for (int i = 0; i < 24; i++)
    {
        Gotoxy(1, 20 + i);
        cout << "░" << endl;
        Gotoxy(90, 20 + i);
        cout << ' ' << endl;
    }
    for (int i = 0; i < 89; i++)
    {
        Gotoxy(2 + i, 20);
        cout << "░";
        Gotoxy(2 + i, 43);
        cout << "░";
    }
    SetColor(0, 12);
    for (int i = 0; i < vt.size(); i++)
    {
        Gotoxy(38, 28 + i * 2);
        cout << i + 1 << "." << vt[i].first << ": " << vt[i].second << endl;
    }
    Gotoxy(38, 28 + vt.size() * 2);
    cout << "Press B to back";
    char c;
    while ((c = getch()) != 'b');
    ClearScreen();
    MainMenu();
}

void PlayGame()
{
    ResizeConsole(400, 250);
    SetFontSize(20);
    SetColor(10, 5);
    for (int i = 0; i < 24; i++)
    {
        Gotoxy(1, 20 + i);
        cout << "░" << endl;
        Gotoxy(90, 20 + i);
        cout << "░" << endl;
    }
    for (int i = 0; i < 89; i++)
    {
        Gotoxy(2 + i, 20);
        cout << "░";
        Gotoxy(2 + i, 43);
        cout << "░";
    }
    string choose[] = {"1. NEW GAME\n", "2. CONTINUE\n", "3. BACK\n"};
    for (int i = 0; i < 3; i++)
    {
        if (i == 0) SetColor(14, 5);
        else SetColor(0, 7);
        Gotoxy(40, 29 + 2 * i);
        cout << choose[i];
    }
    int cnt = 0;
    while (true)
    {
        char c = getch();
        if (c == 13) break;
        if (c != -32) continue;
        c = getch();
        if (c == 72) cnt = (cnt + 2) % 3;
        else if (c == 80) cnt = (cnt + 4) % 3;
        for (int i = 0; i < 3; i++)
        {
            if (i != cnt) SetColor(0, 7);
            else SetColor(14, 5);
            Gotoxy(40, 29 + 2 * i);
            cout << choose[i];
        }
    }
    SetColor(0, 7);
    ClearScreen();
    if (cnt == 0) NewGame();
    else if (cnt == 1) ContinueGame();
    else if (cnt == 2) MainMenu();
}

void ChooseLevel()
{
    ResizeConsole(400, 250);
    SetFontSize(20);
    SetColor(10, 5);
    for (int i = 0; i < 24; i++)
    {
        Gotoxy(1, 20 + i);
        cout << "░" << endl;
        Gotoxy(90, 20 + i);
        cout << "░" << endl;
    }
    for (int i = 0; i < 89; i++)
    {
        Gotoxy(2 + i, 20);
        cout << "░";
        Gotoxy(2 + i, 43);
        cout << "░";
    }
    string choose[] = {"1. EASY\n", "2. NORMAL\n", "3. DIFFICULT\n"};
    for (int i = 0; i < 3; i++)
    {
        if (i == 0) SetColor(14, 5);
        else SetColor(0, 7);
        Gotoxy(40, 29 + 2 * i);
        cout << choose[i];
    }
    int cnt = 0;
    while (true)
    {
        char c = getch();
        if (c == 13) break;
        if (c != -32) continue;
        c = getch();
        if (c == 72) cnt = (cnt + 2) % 3;
        else if (c == 80) cnt = (cnt + 4) % 3;
        for (int i = 0; i < 3; i++)
        {
            if (i != cnt) SetColor(0, 7);
            else SetColor(14, 5);
            Gotoxy(40, 29 + 2 * i);
            cout << choose[i];
        }
    }
    SetColor(0, 7);
    ClearScreen();
    level_string = choose[cnt];
    if (cnt == 0) level = 200;
    else if (cnt == 1) level = 150;
    else if (cnt == 2) level = 70;
    MainMenu();
}

void MainMenu()
{
    SetConsoleOutputCP(65001);
    ShowCur(false);
    DisableSelection();
    DisableResizeWindow();
    DisableCtrButton(true, true, false);
    SetConsoleTitle("Snake");
    SetFontSize(8);
    ShowScrollbar(false);
    ResizeConsole(1000, 600);
    string menu_title[] =  {"~!!!!77777777777777777!.                                               .!77!!!!:                                 \n",
                            "#@@@#7!!!!!!!!!!!!!!!J@:                                               .!!J@@@@?                                 \n",
                            "B@@@B                ~&:                                                  ~@@@@?                                 \n",
                            "B@@@B                 :  :77777777777777777777.   .77777777777777777^     !@@@@?     ~777777:  !7777777777777777~\n",
                            "#@@@#^:^^^^^^^^^^^::::.  .!~5@@@@?~!!!!!!!!~J@:   :@J~!!!!!!!!~J@@@@J     !@@@@?     :7&G!!!. .&@@@#~!!!!!!!!!~#5\n",
                            "?YYYYJJJJJJJJJJJJJB&&&#:    ?@@@@^          ~&:   .~           ~@@@@J     !@@@@7     ~BJ      .#@@@G           G5\n",
                            "                  P@@@&:    J@@@@~          !&:   .YYJJJJJJJJJJP@@@@J     !@@@@GJJJJ5@!       .#@@@#JJJJJJJJJJJ#Y\n",
                            "Y~                P@@@&:    J@@@@~          !&:   :@7::::::::::7@@@@J     ~@@@@J::::^5G^      .#@@@B::::::::::::.\n",
                            "&J                P@@@&:    J@@@@~          !@:   :@~          !@@@@J     !@@@@?      7#J.    .&@@@G           5J\n",
                            "PPYYYYYYYYYYYYYYYYPBBBG. ^YYPBBBB5YJ.    ^YY5G5YY.:G5YYYYYYYYYY5BBBBPYY^JY5BBBBPYY:  :YPB5Y57 .PBBBGYYYYYYYYYYYGJ\n"
                            };

    SetColor(11, 4);
    for (int i = 0; i < 10; i++)
    {
        Gotoxy(63, 0 + i);
        cout << menu_title[i];
    }
    SetColor(10, 5);
    for (int i = 0; i < 50; i++)
    {
        Gotoxy(50, 20 + i);
        cout << "░" << endl;
        Gotoxy(189, 20 + i);
        cout << "░" << endl;
    }
    for (int i = 1; i < 140; i++)
    {
        Gotoxy(49 + i, 20);
        cout << "░";
        Gotoxy(49 + i, 69);
        cout << "░";
    }
    string choose[] = {"1. PLAY\n", "2. LEVEL\n", "3. HIGH SCORE\n", "4. QUIT\n"};
    for (int i = 0; i < 4; i++)
    {
        Gotoxy(112, 40 + i * 5);
        if (i != 0) SetColor(0, 7);
        else SetColor(14, 5);
        cout << choose[i];
    }
    SetColor(0, 7);
    Gotoxy(0, 0);
    int cnt = 0;
    while (true)
    {
        char c = getch();
        if (c == 13) break;
        if (c != -32) continue;
        c = getch();
        if (c == 72) cnt = (cnt + 3) % 4;
        else if (c == 80) cnt = (cnt + 5) % 4;
        for (int i = 0; i < 4; i++)
        {
            Gotoxy(112, 40 + i * 5);
            if (i != cnt) SetColor(0, 7);
            else SetColor(14, 5);
            cout << choose[i];
        }
    }
    ClearScreen();
    if (cnt == 0) PlayGame();
    else if (cnt == 1) ChooseLevel();
    else if (cnt == 2) HighScore();
    else if (cnt == 3) return;
}

int ParseInt(string s)
{
    int res = 0;
    for (char c : s)
        res = res * 10 + int(c) - 48;
    return res;
}

void LoadData()
{
    ifstream input("high_score.txt", ios_base::in);
    string s, name, str;
    int x;
    while (getline(input, s))
    {
        stringstream ss(s);
        vector<string> tmp;
        while (ss >> str) tmp.push_back(str);
        name = "";
        for (int i = 0; i < tmp.size() - 1; i++)
        {
            name = name + tmp[i];
            if (i < tmp.size() - 2) name = name + " ";
        }
        if (tmp.size() >= 2)
        {
            x = ParseInt(tmp.back());
            score_table[name] = x;
        }
    }
    for (pair<string, int> p : score_table)
        vt.push_back(p);

    sort(vt.begin(), vt.end(), cmp);
    input.close();
}

void WriteData()
{
    ofstream output("high_score.txt", ios_base::out);
    vt.clear();
    for (pair<string, int> p : score_table)
        vt.push_back(p);

    sort(vt.begin(), vt.end(), cmp);
    for (pair<string, int> p : vt)
        output << p.first << " " << p.second << endl;

    output.close();
}

int main()
{
    LoadData();
    MainMenu();

    return 0;
}
