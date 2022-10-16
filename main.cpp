#include <iostream>
#include <string.h>
#include <time.h>

using namespace std;


struct Football_Player
{
    string name;
    long double price;
    int speed;
    int finishing;
    int defence;
    int teamID=-1;
    char post[20];
    int total=0;
}players[100];


struct Team
{
    string name;
    long double money;
    int PlayersOfTeam=0;
    int total_force_of_teams=0;
    int goalw=0;
    int goall=0;
    int pID[11];
}teams[100];


void TotalForcePlayer ( int np )
{

    for( int i = 0 ; i < np ; i++ )
         players[i].total = (players[i].speed + players[i].finishing + players[i].defence);

}


void TotalForceTeam ( int idt )
{
    for( int i = 0 ; i < 11 ; i++ )
    {
        int p = teams[idt-1].pID[i];

        (teams[idt-1].total_force_of_teams) = (teams[idt-1].total_force_of_teams + players[p-1].total);
    }
}


void New_Player(int i)
{
   cin>>players[i].name>>players[i].price>>players[i].speed>>players[i].finishing>>players[i].defence;
}


int Search_Player( int i , int n )
{
    if( 0<=i-1 && i-1<=n-1 )
       return 0;

    else
        return 1;
}


void New_Team(int i)
{
    cin>>teams[i].name>>teams[i].money;
}


int Search_Team( int i , int n )
{
    if( 0<=i-1 && i-1<=n-1 )
       return 0;

    else
        return 1;
}


int Search_Player_of_Team( int pID )
{
    if(players[pID-1].teamID == -1)
        return 0;

    else
        return 1;
}


void all_players_of_a_team ( int tID , int np )
{
    int j=0;
    for(int i=0;i<np;i++)
        if(players[i].teamID == tID)
        {
            teams[tID-1].pID[j] = i+1;

            j++;
        }
}


void Buy_Player ( int tID , int pID , int np , int nt )
{

   if(Search_Player(pID,np)==1)
   {
        cout<< "player with the id " << pID << " doesnt exist" << endl;
        return;
   }


   if(Search_Team(tID,nt)==1)
   {
        cout<< "team with the id " << tID << " doesnt exist" << endl;
        return;
   }


   if(teams[tID-1].money < players[pID-1].price)
   {
       cout<< "the team cant afford to buy this player" << endl;
       return;
   }


   if(Search_Player_of_Team(pID)==1)
   {
       cout<< "player already has a team" << endl;
       return;
   }

   else
       teams[tID-1].PlayersOfTeam += 1;


   players[pID-1].teamID=tID;


   if( teams[tID-1].PlayersOfTeam > 11 )
   {
      cout<< "team is full" << endl;
      return;
   }

   (teams[tID-1].money) -= (players[pID-1].price);

   cout<< "player " << pID <<  " added to the team " << tID << " successfully" << endl;

}


void Sell_Player ( int pID , int tID , int np , int nt )
{
    if ( Search_Team(tID,nt) == 1)
    {
        cout<< "team doesnt exist" << endl;
        return;
    }

    if( players[pID-1].teamID != tID )
    {
        cout<< "team doesnt have this player" << endl;
        return;
    }

    players[pID-1].teamID = -1;

    teams[tID-1].money += players[pID-1].price;

    teams[tID-1].PlayersOfTeam -= 1;

    cout<< "player " << pID << " removed from the team " << tID << " successfully" << endl;
}


void Post_of_each_player ( int pID )
{

    if( (players[pID-1].defence > players[pID-1].finishing) && (players[pID-1].defence > players[pID-1].speed) )
    {
        strcpy ( players[pID-1].post , "defender" );
        return;
    }


    else if( (players[pID-1].speed > players[pID-1].defence) && (players[pID-1].speed > players[pID-1].finishing) )
    {
        strcpy ( players[pID-1].post , "midfielder" );
        return;
    }


    else if( (players[pID-1].finishing > players[pID-1].defence) && (players[pID-1].finishing > players[pID-1].speed))
    {
        strcpy ( players[pID-1].post , "attacker" );
        return;
    }


    else
    {
        strcpy ( players[pID-1].post , "normal" );
        return;
    }

}


char climates[20];


int climate ()
{
    static int i=0;
    i++;

    if(i == 1)
        srand(time(0));

    int mini=100;
    int maxi=500;

    double val = 1.0 * rand() / RAND_MAX;

    int r = val * ( maxi - mini ) + mini;


    if( (r%4) == 1 )
    {
        strcpy(climates,"cloudy");
        return 1;
    }

    if( (r%4) == 2 )
    {
        strcpy(climates,"snowy");
        return 2;
    }

    if( (r%4) == 3 )
    {
        strcpy(climates,"sunny");
        return 3;
    }

    if( (r%4) == 0 )
    {
        strcpy(climates,"rainy");
        return 0;
    }

}


int z[100];

void climate_effects ( int c , int np )
{
    if( c == 1 )
        return;

    else if( c == 2 )
    {
        for ( int i=0 ; i < np ; i++ )
        {
            Post_of_each_player( i+1 );

            if ( strcmp ( players[i].post , "defender" ) == 0)
                players[i].defence = (-(players[i].defence));
        }

        return;
    }

    else if( c == 3 )
    {
        for ( int i=0 ; i < np ; i++ )
        {
            Post_of_each_player( i+1 );

            if ( strcmp ( players[i].post , "attacker" ) == 0 )
                players[i].finishing -= 10;

        }

        return;
    }

    else if( c == 0 )
    {
        for ( int i=0 ; i < np ; i++ )
        {
            Post_of_each_player( i+1 );

            if ( strcmp ( players[i].post , "midfielder" ) == 0 )
            {
                if( ((players[i].speed) % 2) == 0 )
                    z[i]=0;

                else
                    z[i]=1;

                players[i].speed /= 2;
            }
        }

        return;
    }
}


int random_goal_winner ()
{
    static int i=0;

    i++;

    if( i == 1 )
        srand(time(0));

    double val = (double)rand() / RAND_MAX;

    int random;

    if (val < 0.5)       //  50%
        random = 1;

    else if (val < 0.8)  //  50% + 30%
        random = 2;

    else if (val < 0.95)  //  50% + 30% + 15%
        random = 3;

    else if (val < 1)  // 50% + 30% + 15% + 5%
    {
        double val2 = (double)rand() / RAND_MAX;

        random = val2 * ( 20 - 4 ) + 4;
    }

    return random;
}


int random_goal_loser ( int maxi )
{
    static int i=0;

    i++;

    if( i == 1 )
        srand(time(0));

    double val = (double)rand() / RAND_MAX;

    int result = val * ( maxi - 0 ) + 0;

    return result;
}


void PrinteInformation ( int tID , int np )
{
    all_players_of_a_team(tID,np);

    cout << "information of team " << tID << " : " << endl;

    for(int i=0;i<11;i++)
    {
        int j=(teams[tID-1].pID[i]);

        j--;

        cout << players[j].name << "\t" << " defence : " << players[j].defence << "\t" << " finishing : " << players[j].finishing << "\t" << " speed : " << players[j].speed << "\t" << " price : " << players[j].price << "\t" << " post : " << players[j].post;

        cout << endl;
    }
}


void Back ( int c , int np )
{
    if ( c == 1 )
        return;


    else if ( c == 2 )
    {
        for ( int i=0 ; i < np ; i++ )
        {
            if (  strcmp ( players[i].post , "defender" ) == 0 )
                players[i].defence = -(players[i].defence);
        }

        return;
    }


    else if ( c == 3 )
    {
        for ( int i=0 ; i < np ; i++ )
        {

            if (  strcmp ( players[i].post , "attacker" ) == 0  )
                players[i].finishing += 10;
        }

        return;
    }

    else if ( c == 0 )
    {
        for ( int i=0 ; i < np ; i++ )
        {

            if ( strcmp ( players[i].post , "midfielder" ) == 0 )
            {
                if(z[i] == 0)
                    players[i].speed *= 2;

                else if(z[i] == 1)
                    players[i].speed = (players[i].speed * 2 + 1);
            }

        }

        return;
    }

}


void Match ( int id1 , int id2 , int nt , int np )
{
    if( (Search_Team(id1,nt) == 1) || (Search_Team(id2,nt) == 1) )
    {
        cout<< "team doesnt exist" << endl;
        return;
    }

    if( (teams[id1-1].PlayersOfTeam < 11) || (teams[id2-1].PlayersOfTeam < 11) )
    {
        cout<< "the game can not be held due to loss of the players" << endl;
        return;
    }

    int c = climate();

    climate_effects(c,np);

    all_players_of_a_team(id1,np);
    all_players_of_a_team(id2,np);

    TotalForcePlayer(np);

    teams[id1-1].total_force_of_teams=0;
    teams[id2-1].total_force_of_teams=0;


    TotalForceTeam(id1);
    TotalForceTeam(id2);

    PrinteInformation(id1,np);
    PrinteInformation(id2,np);

    Back(c,np);

    cout << climates << endl;


    if( teams[id1-1].total_force_of_teams == teams[id2-1].total_force_of_teams )
    {
        cout<< "the match is draw" << endl;

        int goalW = random_goal_winner();
        int goalL = goalW;

        teams[id1-1].goalw = goalW;
        teams[id1-1].goall = goalL;

        teams[id2-1].goalw = goalL;
        teams[id2-1].goall = goalW;

        cout << "goal " << id1 << " and " << id2 << " : " << goalW << endl;

        return;
    }

    else if ( teams[id1-1].total_force_of_teams > teams[id2-1].total_force_of_teams )
    {
        cout<< "team " << id1 << " win"<<endl;

        int goalW = random_goal_winner();
        int goalL = random_goal_loser(goalW);

        teams[id1-1].goalw = goalW;
        teams[id1-1].goall = goalL;

        teams[id2-1].goalw = goalL;
        teams[id2-1].goall = goalW;

        cout << "goal " << id1 << " : " << goalW << "\t" << "goal " << id2 << " : " << goalL << endl;

        return;
    }

    else if ( teams[id1-1].total_force_of_teams < teams[id2-1].total_force_of_teams )
    {
        cout<< "team " << id2 << " win"<<endl;

        int goalW = random_goal_winner();
        int goalL = random_goal_loser(goalW);

        teams[id2-1].goalw = goalW;
        teams[id2-1].goall = goalL;

        teams[id1-1].goalw = goalL;
        teams[id1-1].goall = goalW;

        cout << "goal " << id2 << " : " << goalW << "\t" << "goal " << id1 << " : " << goalL << endl;

        return;
    }
}


int main()
{
    char func[10];

    int np=0;
    int nt=0;

    do
    {
        cin>>func;

        if(strcmp(func,"new") == 0)
        {
            char func2[10];
            cin>>func2;

            if(strcmp(func2,"player") == 0)
            {
                New_Player(np);
                np++;
                Post_of_each_player(np);
            }

            else if (strcmp(func2,"team") == 0)
            {
                New_Team(nt);
                nt++;
            }
        }

        if(strcmp(func,"buy") == 0)
        {
            int pid,tid;
            cin>>pid>>tid;

            Buy_Player(tid,pid,np,nt);
        }

        if(strcmp(func,"sell") == 0)
        {
            int pid,tid;
            cin>>pid>>tid;

            Sell_Player(pid,tid,np,nt);
        }

        if(strcmp(func,"friendlyMatch") == 0)
        {
            int tid1,tid2;
            cin>>tid1>>tid2;

            Match(tid1,tid2,nt,np);
        }


    }while(strcmp(func,"end") != 0);



    return 0;
}
