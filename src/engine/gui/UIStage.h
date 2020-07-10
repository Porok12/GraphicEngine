#ifndef UISTAGE_H
#define UISTAGE_H

class Strategy {

};

class UIStage {
private:
    std::unique_ptr<Strategy> strategy;
public:
    void setStrategy(Strategy* strategy);
};

#endif // UISTAGE_H