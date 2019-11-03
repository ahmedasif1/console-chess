#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include "inter.h"
const int dim=8;
extern char chess[dim][dim];
using namespace std;
extern int castle[2][3];

//////////////////////////////////////////////////////////////////////////
/**********************/
/*   AHMED ASIF       */
/*	  11-4029         */
/*	  CHESS           */
/*  FINAL PROJECT ITC */
/**********************/
void movepiece( int sr ,int sc,int er,int ec )
{
    if (
        withinbound( sr,sc,er,ec )&&
        piece_identifier( turn,sc,sr )&&
        endpoint( er,ec ,turn)&&
        legal_move_piece( sr,sc,er,ec ,true)&&
        not_checked( sr,sc,er,ec,true ) )
    {
        rep_moves(sr,sc,er,ec);
        storage( sr,sc,er,ec );
        refreshpiece( sr,sc,er,ec );
        aftermove( sr,sc,er,ec );
    }
    else
    {
        setXY( 0,28 );
        cout<<"Invalid Move";
    }
}
void aftermove( int sr,int sc,int er ,int ec )
{
    if( ispawn( ec,er )&&promotion( turn,er ) )
    {
        askprom( ec,er );
        refreshpiece( sr,sc,er,ec );
    }
    turnchange( turn );
    setXY( 0,28 );
    cout<<setw( 15 )<<" ";


}
void enddecision( int sr,int sc,int er ,int ec )
{
    setXY( 50,10 );
    if( checkmate(sr,sc,er,ec) )
    {
        cout<<"Player "<<turn<<" CHECKMATED";
        _getch();
        menu();
    }

    else if( stalemate( turn ) )
    {
        cout<<"STALEMATE";
        _getch();
        menu();
    }
    else if(draw())
    {
        cout<<"DRAW";
        _getch();
        menu();
    }
    else if( !not_checked( sr,sc,er,sc,false ) )
    {
        cout<<"Player "<<turn<<" is checked";
        castle[turn-1][0]++;
    }
    else
    {
        cout<<setw( 25 )<<' ';
        savegame();
    }
}
bool vermove( int sr,int sc,int er,int ec )
{
    return ( ( er-sr )&&( ec==sc ) );
}
bool hormove( int sr,int sc,int er,int ec )
{
    return ( ( ec-sc )&&( er==sr ) );
}
bool diagonalmove( int sr,int sc,int er,int ec )
{
    return ( abs( ec-sc )==abs( er-sr ) );
}
bool is_empty( char a )
{
    return a==' ';
}
bool is_black_piece( char a )
{
    return a>='A'&&a<='Z';
}
bool is_white_piece( char a )
{
    return a>='a'&&a<='z';
}
//Check  if the the piece passed is of the person
//whose turn is passed
bool piece_identifier( int bari,int x,int y )
{
    if( bari==1 )
        return is_black_piece( chess[y][x] );
    else return is_white_piece( chess[y][x] );
}
