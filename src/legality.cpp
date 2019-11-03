#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include "inter.h"
const int dim=8;
extern char chess[dim][dim];

int castle[2][3];
//////////////////////////////////////////////////////////////////////////
/**********************/
/*   AHMED ASIF       */
/*	  11-4029         */
/*	  CHESS           */
/*  FINAL PROJECT ITC */
/**********************/
bool withinbound( int sr,int sc,int er,int ec )
{
    return ( sr>=0&&sr<dim&&sc>=0&&sc<dim&&er>=0&&er<dim&&ec>=0&&ec<dim );
}

bool endpoint( int er,int ec,int turn )
{
    if ( turn-1 )
    {
        return is_black_piece( chess[er][ec] )||is_empty( chess[er][ec] );
    }
    else
        return is_white_piece( chess[er][ec] )||is_empty( chess[er][ec] );
}

bool legal_move_piece( int sr,int sc,int er, int ec,bool type )
{
    switch( chess[sr][sc] )
    {
    case 'Q':
    case 'q':
        return legal_queen( sr,sc,er,ec );
        break;
    case 'K':
    case 'k':
        return legal_king( sr,sc,er,ec,type );
        break;
    case 'N':
    case 'n':
        return legal_knight( sr,sc,er,ec );
        break;
    case 'R':
    case 'r':
        return legal_rook( sr,sc,er,ec,type );
        break;
    case 'B':
    case 'b':
        return legal_bishop( sr,sc,er,ec );
        break;
    case 'P':
    case 'p':
        return legal_pawn( sr,sc,er,ec );
        break;
    default :
        return false;
    }
}
//////////////////////////////////////////////////////////////////////////
bool legal_queen( int sr,int sc,int er,int ec )
{
    return ( ( hormove( sr,sc,er,ec )||
               vermove( sr,sc,er,ec )||
               diagonalmove( sr,sc,er,ec ) )
             &&clearpath( sr,sc,er,ec ) );
}
//////////////////////////////////////////////////////////////////////////
bool legal_king( int sr,int sc,int er,int ec ,bool type)
{
    if( ( ( abs( sr-er )<=1 )&&( abs( sc-ec )<=1 ) )
            ||
            ((hormove(sr,sc,er,ec))&&(rook_castle(sr,sc,er,ec)&&type)))
    {
        if(type)
            castle[(sr!=0)][0]++;
        return true;
    }
    return false;
}
//////////////////////////////////////////////////////////////////////////
bool legal_bishop( int sr,int sc,int er,int ec )
{
    return diagonalmove( sr,sc,er,ec )&&
           clearpath( sr,sc,er,ec );
}//////////////////////////////////////////////////////////////////////////
bool legal_rook( int sr,int sc,int er,int ec,bool type )
{
    if (( hormove( sr,sc,er,ec )||
            vermove( sr,sc,er,ec ) )&&
            clearpath( sr,sc,er,ec ))
    {
        if(type)
            castle[sr!=0][(sc!=0)]++;
        return true;
    }
    return false;
}
//////////////////////////////////////////////////////////////////////////
bool legal_knight( int sr,int sc,int er,int ec )
{
    return ( ( abs( sr-er )==2&&abs( sc-ec )==1 )||
             ( abs( sc-ec )==2&&abs( sr-er )==1 ) );
}
//////////////////////////////////////////////////////////////////////////
bool legal_pawn( int sr,int sc,int er,int ec )
{
    int num=( pawnnotmoved( sr,sc )? 2 : 1 );

    return(
              clearpath( sr,sc,er,ec )&&
              (
                  ( ( is_black_piece( chess[sr][sc] ) )
                    &&
                    ( ( ( vermove( sr,sc,er,ec ) )&&( er>sr )&&( er-sr<=num )&&
                        ( is_empty( chess[er][ec] ) ) )
                      ||
                      ( ( er-sr==1 )&&( diagonalmove( sr,sc,er,ec ) )&&
                        ( is_white_piece( chess[er][ec] ) ) ) ) )
                  ||
                  ( ( is_white_piece( chess[sr][sc] ) )
                    &&
                    ( ( vermove( sr,sc,er,ec ) )&&( sr>er )&&( sr-er<=num )&&
                      ( is_empty( chess[er][ec] ) ) )
                    ||
                    ( ( sr-er==1 )&&( diagonalmove( sr,sc,er,ec ) )&&
                      ( is_black_piece( chess[er][ec] ) ) ) ) ) );
}
bool pawnnotmoved( int sr,int sc )
{
    return ( ( sr==1&&is_black_piece(chess[sr][sc]) )||
             ( sr==6&&is_white_piece(chess[sr][sc]) )? true :false );
}

//////////////////////////////////////////////////////////////////////////
/**************/
/* WATCH OUT  */
/**************/
bool clearpath( int sr,int sc,int er,int ec )
{
    int dx=movejudge( sc,ec );
    int dy = movejudge( sr,er );

    int change=( sc==ec ? abs( er-sr ) : abs( sc-ec ) )-2;
    for ( int row=sr+dy ,col=sc+dx  ;  change>=0; row=row+dy , col=col+dx )
    {
        if( !is_empty( chess[row][col] ) )
            return false;
        change--;
    }
    return true;
}
int movejudge( int start,int endp )
{
    if( endp>start )
        return 1;
    else if( start>endp )
        return -1;
    else return 0;
}
//////////////////////////////////////////////////////////////////////////


bool rook_castle(int sr,int sc,int er,int ec)
{
    int rx=(ec>sc?dim-1:0);

    int endrook=( ec>sc ? ec-1 : ec+1 );

    if(abs(ec-sc)==2&&
            (castle[sr!=0][0]==0) &&
            (castle[sr!=0][(rx!=0)+1]==0)
            &&clearpath(sr,sc,sr,rx)
            &&castling_assistant(sr,sc,rx)
      )
    {
        castle[sr!=0][(rx!=0)+1]++;
        storage(sr,rx,sr,endrook);
        refreshpiece(sr,rx,sr,endrook);
        return true;
    }

    return false;
}
bool castling_assistant(int sr,int sc,int ec )
{
    int diff=movejudge(sc,ec);
    for(; sc != ec ; sc += diff )
    {
        if(destinationmove(sr,sc,turn%2+1))
            return false;
    }
    return true;
}

