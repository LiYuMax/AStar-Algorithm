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
    int Map[10][10] = {
        //0 1 2 3 4 5 6 7 8 9
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
    vector<Point*> openList;
    vector<Point*> closeList;
    Point* beginPos = new Point(8, 1);
    Point* endPos = new Point(8, 8);
    beginPos->g = 0;
    beginPos->h = beginPos->get_h((*endPos));
    beginPos->f = beginPos->g + beginPos->h;
    openList.push_back(beginPos);
    cout << openList.size() << endl;

    int flag = 0;
    int existFlag = 0;
    vector<Point*> buff;
    int count = 0;
    int num = 0;
    
    while (true)
    {
        cout << "buffSize=" << buff.size() << ",openListSize=" << openList.size() << ",closeListSize=" << closeList.size() << endl;
        if (0 != buff.size())
        {
            for (vector<Point *>::iterator _it = buff.begin(); _it != buff.end();)
            {
                openList.push_back((*_it));
                _it = buff.erase(_it);
            }
        }
        for (auto it : openList)
        {
            if (it->x == endPos->x && it->y == endPos->y)
            {
                cout << "找到了" << endl;
                while (it != nullptr)
                {
                    cout << "<" << it->x << "," << it->y << ">" << endl;
                    it = it->parent;
                }
                return 0;
            }
        }
        cout << "buffSize=" << buff.size() << ",,openListSize=" << openList.size() << ",,closeListSize=" << closeList.size() << endl; 
        if (openList.size() == 0)
        {
            cout<<"game over"<<endl;
            break;
        }
        vector<Point*>::iterator min = openList.begin();
        for (auto it = openList.begin(); it != openList.end(); it++)
        {
            min = (*min)->f <= (*it)->f ? min : it;
        }
        for (int i = -1; i <= 1; i++)
        {
            for (int j = -1; j <= 1; j++)
            {
                flag = 0;
                existFlag = 0;
                Point* child = new Point((*min)->x + i, (*min)->y + j);
                if (i == 0 && j == 0)
                {
                    delete child;
                    continue;
                }
                if (child->x < 0 || child->x > 9)
                {
                    delete child;
                    continue;
                }
                if (child->y < 0 || child->y > 9)
                {
                    delete child;
                    continue;
                }
                if (1 == Map[child->x][child->y])
                {
                    delete child;
                    continue;
                }
                for (auto it_ : closeList)
                {
                    if (it_->x == child->x && it_->y == child->y)
                    {
                        flag = 1;
                        break;
                    }
                }
                if (1 == flag)
                {
                    delete child;
                    continue;
                }
                for (auto it : openList)
                {
                    if (it->x == child->x && it->y == child->y)
                    {
                        existFlag = 1;
                        break;
                    }
                }
                cout << "7" << existFlag << endl;
                cout << "flag=" << flag << endl;
                if (1 == existFlag)
                {
                    for (auto it = openList.begin(); it != openList.end(); it++)
                    {
                        if ((*it)->x == child->x && (*it)->y == child->y)
                        {
                            if (i == 0 || j == 0)
                            {
                                if ((*min)->g + Zcost < (*it)->g)
                                {
                                    (*it)->g = (*min)->g + Zcost;
                                    (*it)->f = (*it)->g + (*it)->h;
                                    (*it)->parent = (*min);
                                }
                            }
                            else
                            {
                                if ((*min)->g + Xcost < (*it)->g)
                                {
                                    (*it)->g = (*min)->g + Xcost;
                                    (*it)->f = (*it)->g + (*it)->h;
                                    (*it)->parent = (*min);
                                }
                            }
                        }
                    }
                    delete child;
                }
                else if (0 == existFlag)
                {
                    if (i == 0 || j == 0)
                    {
                        child->g = (*min)->g + Zcost;
                    }
                    else
                    {
                        child->g = (*min)->g + Xcost;
                    }
                    child->h = child->get_h((*endPos));
                    child->f = child->g + child->h;
                    child->parent = (*min);
                    buff.push_back(child);
                }
            }
        }
        for (auto it : closeList)
        {
            if (it->x == (*min)->x && it->y == (*min)->y)
            {
                goto next;
            }
        }
         closeList.push_back(*min);
         next:
        openList.erase(min);
    }
    return 0;
}



