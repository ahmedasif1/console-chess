#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include "inter.h"
#include <fstream>
#include <string.h>
/**********************/
/*   AHMED ASIF       */
/*	  11-4029         */
/*	  CHESS           */
/*  FINAL PROJECT ITC */
/**********************/

using namespace std;
extern const int dim=8;
extern char chess[dim][dim];
extern int castle[2][3];

int turn;

int main()
{
    color(15);
    resizescreen( 79,50 );
    menu();
}

//////////////////////////////////////////////////////////////////////////
void startgame()
{
    system("cls");
    print_board_2();
    int sr=0,sc=0,er=0,ec=0;
    sideline();
    displaychars();
    do
    {
        input_from_user( sr,sc,er,ec );
    }
    while ( 1 );
}

//////////////////////////////////////////////////////////////////////////
void initialize(char file_name[])
{
    int r=0;
    int c=0;
    char a;
    ifstream fin(file_name);
    if(fin)
    {
        do
        {
            fin.get(a);
            if(a=='\n')
                fin.get(a);
            chess[r][c]=a;
        }
        while(nestedfor(r,c,dim));
        if(r==dim)
        {
            fin>>turn;
            for(int i=0; i<2; i++)
                for (int j=0; j<3; j++)
                {
                    fin>>castle[i][j];
                }
        }
    }
}
//////////////////////////////////////////////////////////////////////////
void turnchange( int & bari )
{
    bari=bari%2+1;
}
void input_from_user( int sr,int sc,int er,int ec )
{
    {
        setXY( 0,30 );
        for( int i=0; i<5; i++ )
            cout<<setw( 30 )<<" "<<endl;
        if(turn==1)
            color(12);
        else color(9);
    }
    char abc;
    setXY( 0,30 );
    cout<<"PLAYER "<<turn<<" :"<<endl;

    enddecision( sr,sc,er,ec );

    setXY( 0,31 );
    cin>>abc;
    sc=int( abc )-'a';
    cin>>abc;
    sr=int( abc )-'1';
    cin>>abc;
    ec=int( abc )-'a';
    cin>>abc;
    er=int( abc )-'1';
    movepiece( sr,sc,er,ec );
}
//////////////////////////////////////////////////////////////////////////
/***********************/
/* FIND IF CHECKED     */
/***********************/
void findking( int bari, int &x,int &y )
{
    do
    {
        if( piece_identifier( bari,x,y )&&isking( x,y ) )
            return;
    }
    while(nestedfor(y,x,dim));
}
bool isking( int x,int y )
{
    return ( chess[y][x]=='k'||chess[y][x]=='K' );
}
//makes the given move and finds the king
//finds if checked
//by using it as the destination coordinates
bool not_checked( int sr,int sc,int er,int ec,bool type )
{
    bool check=false;
    char temp;
    int kingrow=0,kingcol=0;
    if( type )
    {
        temp=storage( sr,sc,er,ec );
    }
    findking( turn, kingcol,kingrow );

    check=(destinationmove(kingrow,kingcol,turn%2+1));
    if( type )
    {
        reset( sr,sc,er,ec,temp );
    }

    return !check;
}
//////////////////////////////////////////////////////////////////////////
//takes as input destination coordinates and checks for
//legal moves to get there of all other opponent pieces
bool destinationmove(int er,int ec,int turn )
{
    int srow=0;
    int scol=0;
    do
    {
        if(( piece_identifier( turn,scol,srow ) &&
                legal_move_piece( srow,scol,er,ec ,false) ))
            return true;
    }
    while(nestedfor(srow,scol,dim));

    return false;
}
//////////////////////////////////////////////////////////////////////////
char storage( int sr,int sc,int er,int ec )
{
    char temp=chess[er][ec];
    chess[er][ec]=chess[sr][sc];
    chess[sr][sc]=' ';
    return temp;
}
void reset( int sr,int sc,int er,int ec,char a )
{
    chess[sr][sc]=chess[er][ec];
    chess[er][ec]=a;
}
//////////////////////////////////////////////////////////////////////////
/////////////////////////////PAWN////PROMOTION///////////////////////////
bool promotion( int turn, int er )
{
    return ( turn==1&&er==7 )||( turn==2&&er==0 );
}
void askprom( int x,int y )
{
    char a;
    setXY( 0,34 );
    cout<<"Input promotion of pawn : ";
    do
    {
        cin>>a;
        caseup( a );
    }
    while( a!='Q'&&a!='B'&&a!='R'&&a!='N' );
    if( turn==2 )
        casedown( a );
    chess[y][x]=a;
}

bool ispawn( int x,int y )
{
    return chess[y][x]=='p'||chess[y][x]=='P';
}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//selects an opponent piece and calls sourcemove
bool stalemate( int bari )
{
    int r=0;
    int c=0;
    do
    {
        if( piece_identifier( bari,c,r )&&sourcemove( bari,r,c ) )
            return false;
    }
    while(nestedfor(r,c,dim));
    return true;
}
//uses the coordinates given as a source and checks for legal moves
bool sourcemove( int bari,int y,int x )
{
    int r=0;
    int c=0;
    do
    {
        if(
            legal_move_piece( y,x,r,c ,false)&&
            endpoint( r,c ,bari)&&
            not_checked( y,x,r,c,true ) )
            return true;
    }
    while(nestedfor(r,c,dim));
    return false;
}
//////////////////////////////////////////////////////////////////////////

bool checkmate(int sr,int sc,int er,int ec)
{
    return !not_checked(sr,sc,er,ec,false)
           &&stalemate(turn);
}
bool nestedfor(int &r,int &c,int lim)
{
    if(c<lim-1)
    {
        c++;
    }
    else
    {
        c=0;
        r++;
    }
    if(r==dim)
        return false;
    else
        return true;
}
bool draw()
{
    int r=0;
    int c=0;
    char board[10];
    char test[10];
    int i=0;
    do
    {
        if(chess[r][c]!=' ')
        {
            board[i]=chess[r][c];
            i++;
        }
    }
    while(nestedfor(r,c,dim)&&i<10);
    board[9]=0;
    sort_string(board);
    ifstream fin("Dependent\\drawcons.txt");
    if(fin&&!fin.eof())
    {
        fin.getline(test,10,'\n');
        sort_string(test);
        if(!strcmp(test,board))
            return true;
    }
    return false;
}
void sort_string(char str[])
{
    int i = 0;
    int j = 0;
    for(int i=0; i<strlen(str); i++)
    {
        for(int j=i; j<strlen(str); j++)
        {
            if(str[j]<str[i])
                swap(str[j],str[i]);
        }
    }
    while(nestedfor(i,j,strlen(str)));
}
//////////////////////////////////////////////////////////////////////////
void savegame()
{
    ofstream fout("Dependent\\savegame.txt");
    if(fout)
    {
        int r=0;
        int c=0;
        do
        {
            fout<<chess[r][c];
            if(c==dim-1)
                fout<<"\n";
        }
        while (nestedfor(r,c,dim));
    }
    fout<<turn<<'\n';
    for(int i=0; i<2; i++)
    {
        for(int j=0; j<3; j++)
        {
            fout<<castle[i][j]<<' ';
        }
        fout<<'\n';
    }
}
void menu()
{
    system("cls");
    cout<<setw( 20)<<"New Game : 1\n"<<setw( 20)
        <<"Saved Game : 2\n"<<"Replay last game : 3\n"
        <<setw( 16 )<<"Exit : 4";
    char com;
    do
    {
        com=_getch();
    }
    while (com<'1'||com>'4');
    system("cls");
    switch(com)
    {
    case '1':
    {
        initialize("Dependent\\initialize.txt");
        turn=1;
        savegame();
        turn=1;
        ofstream fout("Dependent\\rep_moves.txt");
        break;
    }

    case '2':
        initialize("Dependent\\savegame.txt");
        break;
    case '3':
        initialize("Dependent\\initialize.txt");
        replay();
        break;
    default :
        exit(1);
    }
    startgame();
}
//////////////////////////////////////////////////////////////////////////
void rep_moves(int sr,int sc,int er,int ec)
{
    ofstream fout("Dependent\\rep_moves.txt",ios::app);
    if(fout)
    {
        fout<<sr<<' '<<sc<<' '<<er<<' '<<ec<<' '<<'\n';
    }
}
void replay()
{
    int sr,sc,er,ec;
    print_board_2();
    displaychars();
    sideline();
    ifstream fin("Dependent\\rep_moves.txt");
    while(!fin.eof())
    {
        fin>>sr>>sc>>er>>ec;
        _getch();
        if(isking(sc,sr)&&abs(sc-ec)==2)
        {
            int rsx=(sc>ec? 0 : 7);
            int rdx=( sc>ec ? ec+1: ec-1);
            storage(sr,rsx,er,rdx);
            refreshpiece(sr,rsx,er,rdx);
        }
        storage(sr,sc,er,ec);
        refreshpiece(sr,sc,er,ec);
    }
    menu();
}
//////////////////////////////////////////////////////////////////////////
