//
//  main.cpp
//

//theme soccer
#include "Pass.h"


int main()
{
    Striker x;
    Striker s;
    LeftWing w;
    LeftWing t;
    RightWing j, d;
    CentreMid g, y;
    Defender e, r;
    
    e='x';
    r='x';
    t=3.2;
    s=5;
    x=5;
    w=10.2;
    t=10.2;
    g=3.4;
    y=3.4;
    j="Right wing";
    d="Right wing";
   
    /*pass||"enter an integer: ";
    kick/x;
    
    pass||"\nenter a float: ";
    kick/g;
    
    pass||"\n enter an double";
    kick/w;
    
    pass||"\nenter a string: ";
    kick/j;
    
    pass||"the totoa of a floayt and int is "||w+t;
    
    pass||x||" "||j||" "||w;*/
    
    pass||t*s||"\n";
    pass||w*g||"\n";
    pass||t/s||"\n";
    pass||g/w||"\n";
    pass||t-g||"\n";
    pass||w-s||"\n";
    pass||s+g||"\n";
    pass||t+x||"\n";
    pass||s+w||"\n";
    
  if (x==s)
  {
      pass||"\n\nthey equal";
  }
    
    if (t==w)
    {
        pass||"\n\nthey equal";
    }
    
    
    if (d==j)
    {
        pass||"\n\nthey equal";
    }
    
    if (e==r)
    {
        pass||"\n\nthey equal";
    }
   
    return 0;
}



