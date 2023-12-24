#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <heads.h>


class Event{



public:
    std::string s;
    std::string s_second;

    Event(const std::string& str){
        s = str;
    }

    Event(const std::string& str, const std::string& str2){
        s = str;
        s_second = str2;
    }

    void print(){
        std::cout<<s<<std::endl;
    }

    void second_print(){
        std::cout<<s_second<<std::endl;       
    }

};

class Comenda : public Event
{
public:
    int cocroaches_limit = 0;
    Comenda() = delete;
    Comenda(const std::string& good_str, const std::string& bad_str) : Event(good_str, bad_str) {};

    void checking(std::vector<Cockroach*>& cocroaches){
        int count = 0; 
        for(int i = 0; i < cocroaches.size(); i++){
            if(cocroaches[i]->health > 0){
                count++;
            }
        }
        if(count < cocroaches_limit){
            print();
        } else{
            second_print();
        }
    }
};


class Stipuha : public Event
{
public:
    double stipubl = 0.;
    Stipuha() = delete;
    Stipuha(const std::string& good_str) : Event(good_str) {};

    void money_gang(Student_money& student){
        student.money += 2700.;
    }
};

/*    int a = 5;
    int* b = &a;
    */