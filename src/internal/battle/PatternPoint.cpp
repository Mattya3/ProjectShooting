#include <internal/battle/PatternPoint.hpp>

void PatternPoint::putPattern(string line){
    vector<string> data = split(line, ' ');
    changeHpLine = stod(data.at(1));
    for(int i = 1; i <= stoi(data.at(2)); i++){
        moveId.push_back(stoi(data.at(5 * i - 2)));
        shootId.push_back(stoi(data.at(5 * i - 1)));
        loopNum.push_back(stoi(data.at(5 * i)));
        angles.push_back(stod(data.at(5 * i + 1)));
        random.push_back(stod(data.at(5 * i + 2)));
    }
}

void PatternPoint::changeLoop(){
    nowLoop = 0;
    if(moveId.size() <= ++nowPattern) nowPattern = 0;
}

double PatternPoint::changeLine(){
    return changeHpLine;
}

short PatternPoint::nowShootId(){
    return shootId.at(nowPattern);
}

short PatternPoint::nowStatus(){
    return nowPattern;
}

short PatternPoint::nowMoveId(){
    return moveId.at(nowPattern);
}

double PatternPoint::nowAngle(){
    return angles.at(nowPattern);
}

double PatternPoint::nowRandom(){
    return random.at(nowPattern);
}

short PatternPoint::maxLoopNum(){
    return loopNum.at(nowPattern);
}

void PatternPoint::upStatus(){
    nowPattern++;
}

void PatternPoint::upLoop(){
    nowLoop++;
}

short PatternPoint::hasMoveId(){
    return moveId.size();
}

short PatternPoint::nowCountLoop(){
    return nowLoop;
}