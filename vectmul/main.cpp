#include <iostream>
using namespace std;
#include <chrono>
struct vect2
{
  double x,y;
  vect2( double _x, double _y ) :x(_x),y(_y){}
  vect2  operator*( double f ) const
  {
    return vect2( x*f, y*f );
  }
};
int main()
{
  chrono::system_clock::time_point time_a;
  chrono::system_clock::time_point time_b;
  double f;
 
  vect2 p(1.2,2.3);
 
  time_a= chrono::system_clock::now(); 
  for ( int i=0 ; i < 10000 ; i++ )
  {
    p.x=p.x*2;p.y=p.y*2;  p.x=p.x*2;p.y=p.y*2;  p.x=p.x*2;p.y=p.y*2;  p.x=p.x*2;p.y=p.y*2;  p.x=p.x*2;p.y=p.y*2;
    p.x=p.x*2;p.y=p.y*2;  p.x=p.x*2;p.y=p.y*2;  p.x=p.x*2;p.y=p.y*2;  p.x=p.x*2;p.y=p.y*2;  p.x=p.x*2;p.y=p.y*2;
    p.x=p.x*2;p.y=p.y*2;  p.x=p.x*2;p.y=p.y*2;  p.x=p.x*2;p.y=p.y*2;  p.x=p.x*2;p.y=p.y*2;  p.x=p.x*2;p.y=p.y*2;
    p.x=p.x*2;p.y=p.y*2;  p.x=p.x*2;p.y=p.y*2;  p.x=p.x*2;p.y=p.y*2;  p.x=p.x*2;p.y=p.y*2;  p.x=p.x*2;p.y=p.y*2;
    p.x=p.x*2;p.y=p.y*2;  p.x=p.x*2;p.y=p.y*2;  p.x=p.x*2;p.y=p.y*2;  p.x=p.x*2;p.y=p.y*2;  p.x=p.x*2;p.y=p.y*2;
    p.x=p.x*2;p.y=p.y*2;  p.x=p.x*2;p.y=p.y*2;  p.x=p.x*2;p.y=p.y*2;  p.x=p.x*2;p.y=p.y*2;  p.x=p.x*2;p.y=p.y*2;
    p.x=p.x*2;p.y=p.y*2;  p.x=p.x*2;p.y=p.y*2;  p.x=p.x*2;p.y=p.y*2;  p.x=p.x*2;p.y=p.y*2;  p.x=p.x*2;p.y=p.y*2;
    p.x=p.x*2;p.y=p.y*2;  p.x=p.x*2;p.y=p.y*2;  p.x=p.x*2;p.y=p.y*2;  p.x=p.x*2;p.y=p.y*2;  p.x=p.x*2;p.y=p.y*2;
    p.x=p.x*2;p.y=p.y*2;  p.x=p.x*2;p.y=p.y*2;  p.x=p.x*2;p.y=p.y*2;  p.x=p.x*2;p.y=p.y*2;  p.x=p.x*2;p.y=p.y*2;
    p.x=p.x*2;p.y=p.y*2;  p.x=p.x*2;p.y=p.y*2;  p.x=p.x*2;p.y=p.y*2;  p.x=p.x*2;p.y=p.y*2;  p.x=p.x*2;p.y=p.y*2;
  }
  time_b= chrono::system_clock::now(); 
  f= chrono::duration_cast<chrono::microseconds>(time_b-time_a).count();
  if ( p.x || p.y ) cout << "a) " << f << " msec" << endl;

  time_a= chrono::system_clock::now(); 
  for ( int i=0 ; i < 10000 ; i++ )
  {
    p=p*2;  p=p*2;  p=p*2;  p=p*2;  p=p*2;
    p=p*2;  p=p*2;  p=p*2;  p=p*2;  p=p*2;
    p=p*2;  p=p*2;  p=p*2;  p=p*2;  p=p*2;
    p=p*2;  p=p*2;  p=p*2;  p=p*2;  p=p*2;
    p=p*2;  p=p*2;  p=p*2;  p=p*2;  p=p*2;
    p=p*2;  p=p*2;  p=p*2;  p=p*2;  p=p*2;
    p=p*2;  p=p*2;  p=p*2;  p=p*2;  p=p*2;
    p=p*2;  p=p*2;  p=p*2;  p=p*2;  p=p*2;
    p=p*2;  p=p*2;  p=p*2;  p=p*2;  p=p*2;
    p=p*2;  p=p*2;  p=p*2;  p=p*2;  p=p*2;
  }
  time_b= chrono::system_clock::now(); 
  f= chrono::duration_cast<chrono::microseconds>(time_b-time_a).count();
  if ( p.x || p.y ) cout << "b) " << f << " msec"  << endl;
}
