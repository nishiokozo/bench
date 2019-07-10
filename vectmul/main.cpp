#include <iostream>
using namespace std;
#include <chrono>
struct vect2
{
  double x,y;
  vect2( double _x, double _y ) { x=_x;y=_y;}
  vect2  operator*( vect2 a ) 
  {
    vect2 v( x*a.x, y*a.y );
    return v;
  }
};
int main()
{
  chrono::system_clock::time_point time_a;
  chrono::system_clock::time_point time_b;
  double f;
 
  vect2 p(1.2,2.3);
  vect2 q(4.5,6.7);

  time_a= chrono::system_clock::now(); 
  for ( int i=0 ; i < 20000 ; i++ )
  {
  
    p.x=p.x*q.x;p.y=p.y*q.y;  p.x=p.x*q.x;p.y=p.y*q.y;  p.x=p.x*q.x;p.y=p.y*q.y;  p.x=p.x*q.x;p.y=p.y*q.y;  p.x=p.x*q.x;p.y=p.y*q.y;
    p.x=p.x*q.x;p.y=p.y*q.y;  p.x=p.x*q.x;p.y=p.y*q.y;  p.x=p.x*q.x;p.y=p.y*q.y;  p.x=p.x*q.x;p.y=p.y*q.y;  p.x=p.x*q.x;p.y=p.y*q.y;
    p.x=p.x*q.x;p.y=p.y*q.y;  p.x=p.x*q.x;p.y=p.y*q.y;  p.x=p.x*q.x;p.y=p.y*q.y;  p.x=p.x*q.x;p.y=p.y*q.y;  p.x=p.x*q.x;p.y=p.y*q.y;
    p.x=p.x*q.x;p.y=p.y*q.y;  p.x=p.x*q.x;p.y=p.y*q.y;  p.x=p.x*q.x;p.y=p.y*q.y;  p.x=p.x*q.x;p.y=p.y*q.y;  p.x=p.x*q.x;p.y=p.y*q.y;
    p.x=p.x*q.x;p.y=p.y*q.y;  p.x=p.x*q.x;p.y=p.y*q.y;  p.x=p.x*q.x;p.y=p.y*q.y;  p.x=p.x*q.x;p.y=p.y*q.y;  p.x=p.x*q.x;p.y=p.y*q.y;
    p.x=p.x*q.x;p.y=p.y*q.y;  p.x=p.x*q.x;p.y=p.y*q.y;  p.x=p.x*q.x;p.y=p.y*q.y;  p.x=p.x*q.x;p.y=p.y*q.y;  p.x=p.x*q.x;p.y=p.y*q.y;
    p.x=p.x*q.x;p.y=p.y*q.y;  p.x=p.x*q.x;p.y=p.y*q.y;  p.x=p.x*q.x;p.y=p.y*q.y;  p.x=p.x*q.x;p.y=p.y*q.y;  p.x=p.x*q.x;p.y=p.y*q.y;
    p.x=p.x*q.x;p.y=p.y*q.y;  p.x=p.x*q.x;p.y=p.y*q.y;  p.x=p.x*q.x;p.y=p.y*q.y;  p.x=p.x*q.x;p.y=p.y*q.y;  p.x=p.x*q.x;p.y=p.y*q.y;
    p.x=p.x*q.x;p.y=p.y*q.y;  p.x=p.x*q.x;p.y=p.y*q.y;  p.x=p.x*q.x;p.y=p.y*q.y;  p.x=p.x*q.x;p.y=p.y*q.y;  p.x=p.x*q.x;p.y=p.y*q.y;
    p.x=p.x*q.x;p.y=p.y*q.y;  p.x=p.x*q.x;p.y=p.y*q.y;  p.x=p.x*q.x;p.y=p.y*q.y;  p.x=p.x*q.x;p.y=p.y*q.y;  p.x=p.x*q.x;p.y=p.y*q.y;
  }
  time_b= chrono::system_clock::now(); 
  f= chrono::duration_cast<chrono::microseconds>(time_b-time_a).count();
  if ( p.x || p.y ) cout << "a) " << f << " usec" << endl;

  time_a= chrono::system_clock::now(); 
  for ( int i=0 ; i < 20000 ; i++ )
  {
    p=p*q;  p=p*q;  p=p*q;  p=p*q;  p=p*q;
    p=p*q;  p=p*q;  p=p*q;  p=p*q;  p=p*q;
    p=p*q;  p=p*q;  p=p*q;  p=p*q;  p=p*q;
    p=p*q;  p=p*q;  p=p*q;  p=p*q;  p=p*q;
    p=p*q;  p=p*q;  p=p*q;  p=p*q;  p=p*q;
    p=p*q;  p=p*q;  p=p*q;  p=p*q;  p=p*q;
    p=p*q;  p=p*q;  p=p*q;  p=p*q;  p=p*q;
    p=p*q;  p=p*q;  p=p*q;  p=p*q;  p=p*q;
    p=p*q;  p=p*q;  p=p*q;  p=p*q;  p=p*q;
    p=p*q;  p=p*q;  p=p*q;  p=p*q;  p=p*q;
  }
  time_b= chrono::system_clock::now(); 
  f= chrono::duration_cast<chrono::microseconds>(time_b-time_a).count();
  if ( p.x || p.y ) cout << "b) " << f << " usec"  << endl;

}