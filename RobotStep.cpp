#include <iostream>
#include <stack>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <stdio.h>
#include <conio.h>
#include <sstream>
#include <queue>
#include <fstream>

using namespace std;

class Robot
{
public:
    int power;
    int camera;
    int brush;
    pair <int,int> posR;
    pair <int,int> posPR;
    vector<int> direction;

    Robot(int p, int c, int br ,vector<int> d, pair<int,int> pos,pair<int,int> posPa) : power(p), camera(c), brush(br),direction(d) , posR(pos), posPR(posPa) {}

    int cleanDirt(int dirt)
    {
        return abs(brush - dirt);
    }

    void toggleCamera()
    {
        if(camera==0) camera = 1;
        else camera = 0;
    }

    void setBrush(int b)
    {
        brush = b;
    }

    void standBy()
    {
        power = 1;
    }

    void turnOn()
    {
        power = 2;
    }

    void turnOff()
    {
        power = 0;
    }
};

int n = 20;

int toInt(vector<int> x)
{
    int total = 0;
    for(int i = 0; i < 4 ; i++)
        total += (pow(2,i))*x[3-i];
    return total;
}

void countUp(vector<int> &x)
{
    if(x[3] == 0)
    {
        x[3] = 1;
        return;
    }
    else x[3] = 0;
    for(int i = 2 ; i >=0 ; i--)
    {
        if(x[i]==0)
        {
            x[i] = 1;
            break;
        }
        else x[i] = 0;
    }
    if(x[0]==1)
    {
        x[0]=x[1]=x[2]=x[3]=0;
    }
}

int countZero(vector<vector<int>> &m)
{
    int c = 0;
    for(int i = 0 ; i < n; i++)
    {
        for(int j = 0 ; j < n ; j++)
        {
            if(m[i][j]==0) c++;
        }
    }
    return c;
}

int countDust(vector<vector<int>> &m)
{
    int c = 0;
    for(int i = 0 ; i < n; i++)
    {
        for(int j = 0 ; j < n ; j++)
        {
            c += m[i][j];
        }
    }
    return c;
}

void printMap(vector<vector<int>> &m)
{
    stringstream print;
    for(int i = 0; i < n ; i++)
    {
        for(int j = 0; j < n; j++)
        {
            print << (m[i][j]) << " ";
        }
        print << "\n";
    }
    cout << print.str();
}

bool canMove(int x, pair<int,int> pos, vector<vector<int>> &m)
{
    if(x==0)
    {
        if(pos.first - 1 < 0 || m[pos.first-1][pos.second] == 0)
            return false;
        else return true;
    }
    if(x==1)
    {
        if(pos.first - 1 < 0 || pos.second + 1 > (n-1) || m[pos.first-1][pos.second+1] == 0)
            return false;
        else return true;
    }
    if(x==2)
    {
        if(pos.second + 1 > (n-1)|| m[pos.first][pos.second+1] == 0)
            return false;
        else return true;
    }
    if(x==3)
    {
        if(pos.first + 1 > (n-1) || pos.second + 1 > (n-1) || m[pos.first+1][pos.second+1] == 0)
            return false;
        else return true;
    }
    if(x==4)
    {
        if(pos.first + 1 > (n-1) || m[pos.first+1][pos.second] == 0)
            return false;
        else return true;
    }
    if(x==5)
    {
        if(pos.first + 1 > (n-1) || pos.second - 1 < 0 || m[pos.first+1][pos.second-1] == 0)
            return false;
        else return true;
    }
    if(x==6)
    {
        if(pos.second - 1 < 0 || m[pos.first][pos.second-1] == 0)
            return false;
        else return true;
    }
    if(x==7)
    {
        if(pos.first - 1 < 0 || pos.second - 1 < 0 || m[pos.first-1][pos.second-1] == 0)
            return false;
        else return true;
    }
}

vector<int> getRetDirection(pair<int,int> start,pair<int,int>stop){
    vector<int> a;
    if(start.second == stop.second && start.first - stop.first == 1){a = {0,0,0,0}; return a;}
    else if(start.second - stop.second == -1 && start.first - stop.first == 1){a = {0,0,0,1}; return a;}
    else if(start.second - stop.second == -1 && start.first == stop.first){a = {0,0,1,0}; return a;}
    else if(start.second - stop.second == -1 && start.first - stop.first == -1){a = {0,0,1,1}; return a;}
    else if(start.second == stop.second && start.first - stop.first == -1){a = {0,1,0,0}; return a;}
    else if(start.second - stop.second == 1 && start.first - stop.first == -1){a = {0,1,0,1}; return a;}
    else if(start.second - stop.second == 1&& start.first == stop.first){a = {0,1,1,0}; return a;}
    else if(start.second - stop.second == 1 && start.first - stop.first == 1){a = {0,1,1,1}; return a;}
}

bool stuck(vector<vector<int>> &m,pair<int,int> d)
{
    vector<int> x = {0,0,0,0};
    for(int i = 0 ; i < 8 ; i++)
    {
        if(!canMove(toInt(x),d,m))
        {
            countUp(x);
        }
        else return false;
    }
    return true;
}

int main()
{
    vector<vector<int>> mapC(n);
    vector<vector<int>> mapT(n);

    cout << "ENTER MAP 20 x 20 :" << endl;
    for(int i = 0 ; i < n ; i++)
    {
        for(int j = 0; j < n; j++)
        {
            int k;
            cin >> k;
            mapC[i].push_back(k);
            if(k==0)  mapT[i].push_back(0);
            else mapT[i].push_back(1);
        }
    }

    vector<vector<int>> mapP(mapT);

    pair<int,int> pos;
    pos = make_pair(15,5);

    vector<int> x = {1,0,0,0};

    stack<Robot> s;
    queue<vector<int>> q;
    stack<pair<int,int>> sP;

    ///Initial State Push

        ///Set Brush = 3
        Robot R = Robot(2,1,3,x,pos,pos);
        s.push(R);
        ///Camera On Robot(2,1,0,xpos,pos);
        R.setBrush(0);
        s.push(R);

        ///Power On Robot(2,0,0,x,pos,pos);
        R.toggleCamera();
        s.push(R);

        ///Stand By Robot(1,0,0,x,pos,pos);
        R.standBy();
        s.push(R);

        ///Power Off Robot(0,0,0,x,pos,pos);
        R.turnOff();
        s.push(R);

    int usage = 0;
    int moveCount = -1;
    int check = 0;
    int pushFinalState = 0;
    int finish = 0;
    int init = 0;
    int notDetect = 0;

    string direction[9] = {"N","NE","E","SE","S","SW","W","NW","STAY"};

    ofstream myfile;
    myfile.open("step.txt");

    while(!s.empty())
    {
        Robot R = s.top();
        vector<int> qq = {R.power,R.camera,R.brush,toInt(R.direction)};
        q.push(qq); /// Push to State

        usage++;
        myfile << R.power << " " << R.camera << " " << R.brush << " " << toInt(R.direction);
        myfile << endl;

        if(q.size()==2000) {
            cout << "At 2000 States"<< endl << endl;
            cout << "DustCount = " << countDust(mapC) << endl << endl;
            cout << "--------------------------------------------------" << endl << endl;
        }

        s.pop(); /// Pop State

        if(toInt(R.direction)==8 && init >=5 && pushFinalState == 0){
            //cout << "Direction = " << direction[toInt(R.direction)] << endl << endl;
            continue;
        }

        /// Init State Description
        if(init < 5){
            init++;
            if(R.power == 2 && R.camera == 1 && R.brush > 0) {
                /*cout << "Set Brush" << endl << endl;*/
            }
            else if(R.power == 2 && R.camera == 1) {/*cout << "Turn On Camera" << endl << endl;*/ continue;}
            else if (R.power == 2) {/*cout << "Turn On" << endl << endl;*/ continue; }
            else if (R.power == 1) {/*cout << "Stand By" << endl << endl;*/ continue; }
            else if (R.power == 0) {/*cout << "Power Off" << endl << endl;*/ continue;}
        }

        ///Final State Push
         if(/*(usage>=1996 && pushFinalState==0)||*/finish==1)
        {
            /*if(finish==0){
                cout << "--------------------------------------------------" << endl << endl;
                cout << "Low Battery need to Power Off" << endl << endl;
                cout << "DustCount = " << countDust(mapC) << endl << endl;
                cout << "MoveCount = " << moveCount << endl << endl;
                printMap(mapC);
                cout << endl << endl;
                cout << "--------------------------------------------------" << endl << endl;
            }
            else*/
            //cout << "Prepare to Power Off" << endl << endl;
            vector<int> x= {1,0,0,0};
            ///Power Off
            Robot R1 = Robot(0,0,0,x,R.posR,R.posPR);
            s.push(R1);
            ///Stand By /// Robot(1,0,0,x,R.posR.posPR)
            R1.standBy();
            s.push(R1);
            ///Turn Off Camera /// Robot(2,0,0,x,R.posR.posPR)
            R1.turnOn();
            s.push(R1);
            ///Turn Off Brush /// Robot(2,1,0,x,R.posR.posPR)
            R1.toggleCamera();
            R1.setBrush(0);
            s.push(R1);
            pushFinalState = 1;
            finish = 0;
        }

        /// Final State Description
        if(pushFinalState) {
            if(R.power==0) {/*cout << "Power Off" << endl <<endl;*/ break;}
            //else if(R.power==2 && R.camera == 0) cout << "Turn Off Camera" << endl << endl;
            //else if(R.power==2 && R.brush == 0) cout << "Turn Off Brush" << endl << endl;
            //else if(R.power==1) cout << "Stand By" << endl << endl;
            continue;
        }

        //cout << "Direction = " << direction[toInt(R.direction)] << endl << endl;

        ///Detect Dirt By Camera
        if(R.camera)
        {
            if(mapC[R.posR.first][R.posR.second] !=0 ){

                if(check==1 && R.brush==3){
                    R.setBrush(1);
                    s.push(R);
                    continue;
                }
                else if(check == 1 && R.brush ==0){
                    R.setBrush(1);
                    s.push(R);
                    continue;
                }
                mapC[R.posR.first][R.posR.second] = R.cleanDirt(mapC[R.posR.first][R.posR.second]);
            }
            else if (mapC[R.posR.first][R.posR.second] ==0){
                if(R.brush!=0){
                    R.setBrush(0);
                    s.push(R);
                    continue;
                }
            }
        }

        moveCount++;
        mapP[R.posR.first][R.posR.second] = 0;

        ///First All Map Movement
        if(countZero(mapP)==400)
        {
            if(check==0){
                cout << "--------------------------------------------------" << endl << endl;
                cout << "First Time All Map Traversed" << endl << endl;
                cout << "DustCount = " << countDust(mapC) << endl << endl;
                cout << "Number of States = " << q.size() << endl << endl;
                cout << "--------------------------------------------------" << endl << endl;
            }
            mapP = mapT;
            check = 1;
        }

        ///Finish Cleaning
        if(countDust(mapC)==0)
        {
            cout << "Finish Cleaning" << endl << endl;
            cout << "MoveCount = " << moveCount << endl << endl;
            cout << "Number Of State = " << q.size() << endl << endl;
            cout << "--------------------------------------------------" << endl << endl;
            finish = 1;
            continue;
        }

        vector<int> x = {0,0,0,0};
        if(!stuck(mapP,R.posR))
        {
            for(int i = 0 ; i < 8 ; i++)
            {
                pair<int,int> pos(R.posR);
                if(canMove(toInt(x),pos,mapP))
                {
                    if(toInt(x)==0)
                    {
                        pos.first--;
                    };
                    if(toInt(x)==1)
                    {
                        pos.first--;
                        pos.second++;
                    };
                    if(toInt(x)==2)
                    {
                        pos.second++;
                    };
                    if(toInt(x)==3)
                    {
                        pos.first++;
                        pos.second++;
                    };
                    if(toInt(x)==4)
                    {
                        pos.first++;
                    };
                    if(toInt(x)==5)
                    {
                        pos.first++;
                        pos.second--;
                    };
                    if(toInt(x)==6)
                    {
                        pos.second--;
                    };
                    if(toInt(x)==7)
                    {
                        pos.first--;
                        pos.second--;
                    };
                    ///Change Direction
                    Robot R1(2,1,R.brush,x,pos,R.posR);
                    vector<int> y = {1,0,0,0};
                    ///Prepare to change Direction
                    Robot R2(2,1,R.brush,y,pos,R.posR);
                    s.push(R1);
                    s.push(R2);
                }
                countUp(x);
            }
            sP.push(R.posR);
        }
        else
        {
            stack<pair<int,int>> a(sP);
            pair<int,int> top = sP.top();
            sP.pop();
            ///Change Direction
            Robot R1(2,1,R.brush,getRetDirection(R.posR,top),top,R.posR);
            vector<int> y = {1,0,0,0};
            ///Prepare to change Direction
            Robot R2(2,1,R.brush,y,pos,R.posR);
            s.push(R1);
            s.push(R2);
        }
    }
    myfile.close();
    return 0;
}
