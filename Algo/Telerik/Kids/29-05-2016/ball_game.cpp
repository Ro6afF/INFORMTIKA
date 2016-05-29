#include <iostream>
using namespace std;

#include"QmKuftaci.hpp"
#include"AI_code.h"

bool alreadyLose[10]= {false};
int diapason_MIN[10]= {1,2,3,4};
int diapason_MAX[10]= {3,4,5,5};
int number_of_balls=10,number_of_players=4,player_on_turn=0,min_balls=1,max_balls=3;
int onlinePlayers=number_of_players;
int player_uses[4]= {0,1,2,3};
void switch_diapasons()
{
    int rem=player_uses[0];
    for(int i=0; i<3; i++)
    {
        player_uses[i]=player_uses[i+1];
    }
    player_uses[3]=rem;
}
int main()
{
    cout<<"Number of players: \t"<<number_of_players<<endl;
    cout<<"Number of balls: \t"<<number_of_balls<<endl;
    cout<<"Available diapasons: ";
    for(int i=0; i<4; i++)
    {
        if(i==0)
        {
            cout<<"\t["<<diapason_MIN[i]<<";"<<diapason_MAX[i]<<"]\n";
        }
        else
        {
            cout<<"\t\t\t["<<diapason_MIN[i]<<";"<<diapason_MAX[i]<<"]\n";
        }
    }
    cout<<"ENTER player_turn: \t";
    cin>>player_on_turn;
    string name[4]= {"nameless0","nameless1","nameless2","nameless3"};
    while(onlinePlayers>1)
    {
        int current_number_of_balls=number_of_balls,turns=0;
        while(current_number_of_balls>min_balls)
        {

            if(player_on_turn>=number_of_players)
            {
                player_on_turn=0;
            }
            //cout<<diapason_MIN[player_uses[player_on_turn]]<<";"<<diapason_MAX[player_uses[player_on_turn]];
            int next_taking=how_many_balls_0(diapason_MIN[player_uses[player_on_turn]],diapason_MAX[player_uses[player_on_turn]],current_number_of_balls);

            if(next_taking<diapason_MIN[player_uses[player_on_turn]] or next_taking>diapason_MAX[player_uses[player_on_turn]] or next_taking>=current_number_of_balls)
            {
                cout<<"Player "<<player_on_turn<<" have made a wrong turn! ";
                break;
            }
            else
            {
                current_number_of_balls-=next_taking;
                if(current_number_of_balls==1)
                {
                    cout<<"At the moment, there is "<<current_number_of_balls<<endl;
                }
                else
                {
                    cout<<"At the moment, there are "<<current_number_of_balls<<endl;
                }
            }


            player_on_turn++;
            while(alreadyLose[player_on_turn])player_on_turn++;
            if(player_on_turn>=number_of_players)
            {
                player_on_turn=0;
                while(alreadyLose[player_on_turn])player_on_turn++;
            }
            if(turns%(number_of_players-1)==0)
            {
                switch_diapasons();
            }
            turns++;
        }
        onlinePlayers--;
        alreadyLose[player_on_turn]=true;
        cout<<"Player "<<player_on_turn<<" lost the game!\n";
        if(onlinePlayers>1)
        {
            cout<<"The game started again with "<<number_of_balls<<" balls"<<endl;
            cout<<"The following players are still in the game: ";
            for(int i=0; i<number_of_players; i++)
            {
                if(!alreadyLose[i])
                {
                    cout<<name[i]<<"   ";
                }
            }
            cout<<"\n\n-------------------------------------------------------\n";
            player_on_turn++;
            while(alreadyLose[player_on_turn])player_on_turn++;
            if(player_on_turn>=number_of_players)
            {
                player_on_turn=0;
                while(alreadyLose[player_on_turn])player_on_turn++;
            }
            cout<<"Player "<<player_on_turn<<" will be first";
        }
    }
    int wonPlayer;
    for(wonPlayer=0; alreadyLose[wonPlayer]; wonPlayer++) {}
    cout<<"Player "<<wonPlayer<<" won the game";
    return 0;
}
