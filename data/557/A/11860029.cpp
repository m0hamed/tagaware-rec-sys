//Language: GNU C++


#include <iostream>
using namespace std;

int n,a,b,c,d,e,f,g,h,i;

int main()
{
    cin>>n>>a>>b>>c>>d>>e>>f;
    g=min(n-(c+e),b);
    h=min(d,n-g-e);
    i=n-g-h;
    cout<<g<<" "<<h<<" "<<i;
    return 0;
}