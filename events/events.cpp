#include "events.h"


std::string Event::Evil_Woman(double& money){
    int count = 0;
    std::vector<Cockroach*> cock = Cockroach::GetAll();
    for(int i =0; i< cock.size(); i++){
        if(cock[i]->health>0)
            count++;
    }
    if(count < 30){
        std::string good = "Good boys, i will even not kill you))";
        return good;
    } else{
        money -= 1000.;
        if(money < 0.)
            money = 0.;
        std::string bad = "Bad boys, you should be ready to my attack";
        return bad;
    }
}


