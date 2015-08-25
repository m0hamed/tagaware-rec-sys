//Language: GNU C++


//In the Name of God

#include<iostream>
#include<vector>
#include<algorithm>
#define ll long long

using namespace std;

const ll M=1e9+7;
ll n,x,y,h,w,f[200200],P[200200],a[2020],ret;
vector<pair<ll,ll> > v;

ll p(ll b,ll k)
{
  if(k==0)
    return 1;
  ret=p(b,k/2);
  if(k%2)
    {
      return (((ret*ret)%M)*b)%M;
    }
  return (ret*ret)%M;
}

ll c(ll i,ll j)
{
  return (((f[i]*P[j])%M)*P[i-j])%M;
}

int main()
{
  for(f[0]=1,n=1;n<=200010;f[n]=(f[n-1]*n)%M,n++);
  for(n=0;n<=200010;P[n]=p(f[n],M-2),n++);
  cin>>h>>w>>n;
  for(int i=0;i<n;i++)
    {
      cin>>x>>y;
      v.push_back(make_pair(x,y));
    }
  v.push_back(make_pair(h,w));
  sort(v.begin(),v.end());
  for(int i=0;i<=n;i++)
    {
      x=v[i].first;
      y=v[i].second;
      a[i]=c(x+y-2,x-1);
      for(int j=0;j<i;j++)
	if(v[j].first<=x && v[j].second<=y)
	  {
	    a[i]-=(a[j]*c(x-v[j].first+y-v[j].second,x-v[j].first));
	    a[i]=((a[i]%M)+M)%M;
	  }
    }
  cout<<a[n]<<endl;
  return 0;
}