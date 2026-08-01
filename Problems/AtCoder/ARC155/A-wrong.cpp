#include <bits/stdc++.h>
using namespace std;

typedef long long ll; typedef unsigned long long ull;
const int inf = 1e9; const ll llnf = 4e18;

template< class Tp > void chkmax( Tp &x , Tp y ) { x = max( x , y ); }
template< class Tp > void chkmin( Tp &x , Tp y ) { x = min( x , y ); }

void solve( ) {
	int n; ll k; cin >> n >> k;
	vector< char > a( n + 1 ); for( int i = 1; i <= n; i ++ ) cin >> a[i];

	if( k >= n ) {
		for( int j = 1; j <= n; j ++ ) {
			if((k - j + 1 + 2 * n) / (2 * n) % 2) reverse(a.begin() + 1, a.end());
			int i = ( k - j + 1 + 2 * n ) % ( 2 * n ); if( i == 0 ) i = 2 * n, reverse(a.begin() + 1, a.end());
			if( i <= n && a[n + 1 - i] != a[j] ) return cout << "No" << "\n" , void( );
			else if( i > n && a[i - n] != a[j] ) return cout << "No" << "\n" , void( );
		}
		cout << "Yes" << "\n";
	} else {
		vector< char > b( k + 1 ); for( int i = 1; i <= k; i ++ ) b[i] = a[n + 1 - i];

		vector< char > c = a; for( int i = 1; i <= k; i ++ ) c.emplace_back( b[i] );
		vector< char > d = b; for( int i = 1; i <= n; i ++ ) d.emplace_back( a[i] );

		for( int i = 1; i <= n + k; i ++ ) if( c[i] != c[n + k + 1 - i] ) return cout << "No" << "\n" , void( );
		for( int i = 1; i <= n + k; i ++ ) if( d[i] != d[n + k + 1 - i] ) return cout << "No" << "\n" , void( );
		cout << "Yes" << "\n";
	}
}

int main( ) {
	ios::sync_with_stdio( 0 ), cin.tie( 0 ), cout.tie( 0 );
	int T; cin >> T; while( T -- ) solve( ); return 0;
}