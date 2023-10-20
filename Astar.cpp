#include <iostream>
#include <cmath>
#include <queue>
#include <vector>
#include <unordered_set>
using namespace std;
#define Zcost 10
#define Xcost 14
class Point
{
public:
    Point() {}
    Point(int m, int n)
    {
        this->x = m;
        this->y = n;
        g = 0;
        f = 0;
        h = 0;
        parent = nullptr;
    }
    int get_h(Point& endPos) {
        return Zcost * (abs(endPos.x - this->x) + abs(endPos.y - this->y));
    }
public:
    int x, y, g, h, f;
    Point* parent;
};
enum MyEnum
{
    UP = 0,
    DOWN,
    LEFT,
    RIGHT,
    LEFT_UP,
    LEFT_DOWM,
    RIGHT_UP,
    RIGHT_DOWN
};
int PosFlag = 0;
int main(int argc, char const* argv[])
{
    vector<Point*> openList;
    vector<Point*> closeList;
    vector<Point*>::iterator exist;
    int Map[10][10] = {
        {0,0,0,0,0,0,0,0,0,0},//0
        {0,0,0,0,1,0,0,0,0,0},//1
        {0,0,0,0,1,0,0,0,0,0},//2
        {0,0,0,0,1,1,1,1,0,0},//3
        {0,0,0,0,1,0,0,0,0,0},//4
        {0,0,0,0,1,1,0,1,0,0},//5
        {0,0,0,0,1,0,1,1,1,0},//6
        {0,0,0,0,1,0,1,0,1,1},//7
        {0,0,0,0,1,1,0,1,0,0},//8
        {0,0,0,0,1,1,0,0,0,0},//9
    };
    bool existMap[10][10] = { 0 };
    Point* beginPos = new Point(8, 1);
    Point* endPos = new Point(8, 8);
    beginPos->g = 0;
    beginPos->h = beginPos->get_h((*endPos));
    beginPos->f = beginPos->g + beginPos->h;
    openList.push_back(beginPos);
    cout << openList.size() << endl;
    vector<Point*>::iterator delete_it;
    Point* min = nullptr;
    while (true)
    {
        min = (*openList.begin());
        for (auto it : openList)
        {
            min = min->f < it->f ? min : it;
        }
        for (int i = 0; i < 8; i++)
        {
            Point* child = new Point(*min);
            switch (i)
            {
            case UP:
                child->y--;
                PosFlag = UP;
                break;
            case DOWN:
                child->y++;
                PosFlag = DOWN;
                break;
            case LEFT:
                child->x--;
                PosFlag = LEFT;
                break;
            case RIGHT:
                child->x++;
                PosFlag = RIGHT;
                break;
            case LEFT_UP:
                child->x--;
                child->y--;
                PosFlag = LEFT_UP;
                break;
            case LEFT_DOWM:
                child->x--;
                child->y++;
                PosFlag = LEFT_DOWM;
                break;
            case RIGHT_UP:
                child->x++;
                child->y--;
                PosFlag = RIGHT_UP;
                break;
            case RIGHT_DOWN:
                child->x++;
                child->y++;
                PosFlag = RIGHT_DOWN;
                break;
            }
            if (child->x < 0 || child->x > 9)
            {
                delete child;
                continue;
            }
            if (child->y < 0 || child->y>9)
            {
                delete child;
                continue;
            }
            if (Map[child->x][child->y] == 1)
            {
                delete child;
                continue;
            }
            if (false == existMap[child->x][child->y])
            {
                if (UP == PosFlag || DOWN == PosFlag || LEFT == PosFlag || RIGHT == PosFlag)
                {
                    child->g += Zcost;
                    child->h = child->get_h(*endPos);
                    child->f = child->g + child->h;
                }
                if (LEFT_UP == PosFlag || LEFT_DOWM == PosFlag || RIGHT_UP == PosFlag || RIGHT_DOWN == PosFlag)
                {
                    child->g += Xcost;
                    child->h = child->get_h(*endPos);
                    child->f = child->g + child->h;
                }
                for (vector<Point*>::iterator it = openList.begin(); it != openList.end(); it++)
                {
                    if ((*it)->x == min->x && (*it)->y == min->y)
                    {
                        child->parent = (*it);
                    }
                }
                openList.push_back(child);
                existMap[child->x][child->y] = true;
            }
            else if (true == existMap[child->x][child->y])
            {
                for (auto it : openList)
                {
                    if (it->x == child->x && it->y == child->y)
                    {
                        if (UP == PosFlag || DOWN == PosFlag || LEFT == PosFlag || RIGHT == PosFlag)
                        {
                            if(min->g + Zcost < it->g)
                            {
                                it->g = min->g + Zcost;
                                it->f = it->g + it->h;
                                for(vector<Point*>::iterator _it = openList.begin(); _it != openList.end(); _it++)
                                {
                                    if((*_it)->x == min->x && (*_it)->y == min->y)
                                    {
                                        it->parent = (*_it);
                                        break;
                                    }            
                                }
                            }
                        }
                        else if(LEFT_UP == PosFlag || LEFT_DOWM == PosFlag || RIGHT_UP == PosFlag || RIGHT_DOWN == PosFlag)
                        {   
                            if(min->g + Xcost < it->g)
                            {
                                it->g = min->g + Xcost;
                                it->f = it->g + it->h;
                                for(vector<Point*>::iterator _it = openList.begin(); _it != openList.end(); _it++)
                                {
                                    if((*_it)->x == min->x && (*_it)->y == min->y)
                                    {
                                        it->parent = (*_it);
                                        break;
                                    }            
                                }
                            }
                        }          
                    }
                }
                delete child;
            }   
        }
        for (vector<Point*>::iterator it = openList.begin(); it != openList.end(); it++)
        {
            if ((*it)->x == min->x && (*it)->y == min->y)
            {
                Map[min->x][min->y] = 1;
                openList.erase(it);
                break;
            }
        }
        for (auto it : openList)
        {
            if (it->x == endPos->x && it->y == endPos->y)
            {
                    cout << it->x << ":" << it->y << endl;
                while (it != nullptr)
                {
                    cout << it->x << ":" << it->y << endl;
                    it = it->parent;
                }
                return 0;
            }
        }
        if(openList.size() == 0)
        {
            cout<<"game over"<<endl;
            return 0;
        }
    }
    return 0;
}
