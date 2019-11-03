#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include "inter.h"
const int dim=8;
char chess[dim][dim];
int hmax=5;
int vmax=3;
using namespace std;
//////////////////////////////////////////////////////////////////////////
/**********************/
/*   AHMED ASIF       */
/*	  11-4029         */
/*	  CHESS           */
/*  FINAL PROJECT ITC */
/**********************/
void v_line( int x, int y, int length )
{
    for( int i=0; i<length; i++ )
    {
        setXY( x,y+i );
        cout<<"|";
    }
}

void h_line( int x, int y, int length )
{
    setXY( x,y );
    for( int i=0; i<length; i++ )
    {
        cout<<"-";
    }
}

void print_box( int x, int y )
{
    v_line( x,y,vmax );
    v_line( x+hmax,y,vmax );
    h_line( x,y,hmax );
    h_line( x,y+vmax,hmax+1 );
}
void print_board_2()
{
    int i=0;
    int j=0;
    color( 15 );
    do
    {
        print_box( i*hmax+3,j*vmax+2 );

    }
    while(nestedfor(i,j,dim));
    colorcontrol();
}
//////////////////////////////////////////////////////////////////////////
void printinboard( char a,int x,int y ,int r,int c)
{
    if( (is_black_piece( a ) ||is_empty(a))&&(y*7+x)%2==0&&x>=0&&y>=0)
        color( 12 );
    else if((is_black_piece(a)||is_empty(a))&&(y*7+x)%2==1&&x>=0&&y>=0)
        color(252);
    else if(is_white_piece(a)&&(y*7+x)%2==0&&x>=0&&y>=0)
        color(9 );
    else if(is_white_piece(a)&&x>=0&&y>=0)
        color(249);
    setXY( c,r );
    cout<<a;
    color(15);
}
void displaychars()
{
    int r=0;
    int c=0;
    do
    {
        printinboard( chess[r][c],c,r ,r*vmax+3,c*hmax+5);
    }
    while(nestedfor(r,c,dim));
}
void refreshpiece( int sr,int sc,int er,int ec )
{
    printinboard( chess[sr][sc],sc,sr ,sr*vmax+3,sc*hmax+5);
    printinboard( chess[er][ec],ec,er ,er*vmax+3,ec*hmax+5);
}

void sideline()
{
    for( int i=0 ; i<dim ; i++ )
    {
        printinboard ( char( i +'a'), i,-1,0,i*hmax+5 );
    }
    for( int i=0; i<dim; i++ )
    {
        printinboard( char( i+int( '1' ) ),-1,i ,i*vmax+3,0);
    }
}
void caseup( char &a )
{
    int d=( 'a' )-( 'A' );
    if( a>='a'&&a<='z' )
        a-=d;
}
void casedown( char &a )
{
    int d=int( 'a' )-int( 'A' );
    if( a>='A'&&a<='a' )
        a+=d;
}
//////////////////////////////////////////////////////////////////////////
void color( int k )
{
    SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), k );
}
void setXY( int x, int y )
{
    COORD coord= {x, y};
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), coord );
}
void resizescreen( int x,int y )
{
    SMALL_RECT rect= {0,0,x,y};
    SetConsoleWindowInfo( GetStdHandle( STD_OUTPUT_HANDLE ),TRUE,&rect );
}
//////////////////////////////////////////////////////////////////////////
void colordaboard(int srow,int scol)
{
    for(int i=0; i<2; i++)
    {
        for(int j=0; j<4; j++)
        {
            printinboard(' ',scol,srow,srow*vmax+3+i,scol*hmax+4+j);
        }
    }
}
void colorcontrol()
{
    for(int i=0; i<8; i++)
    {
        for(int j=0; j<8; j++)
        {
            colordaboard(i,j);
        }
    }
}
