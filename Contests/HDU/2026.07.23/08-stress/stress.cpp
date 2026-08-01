#include <bits/stdc++.h>
using namespace std;

mt19937 rng((unsigned)chrono::steady_clock::now().time_since_epoch().count());

const int MAXN = 12;

vector<int> G[MAXN];

int dfs(int u,int fa){
    int ret=1;
    for(int v:G[u]){
        if(v==fa) continue;
        ret=max(ret,dfs(v,u)+1);
    }
    return ret;
}

vector<int> calc_d(int n,const vector<pair<int,int>>& edges){
    for(int i=1;i<=n;i++) G[i].clear();

    for(auto e:edges){
        G[e.first].push_back(e.second);
        G[e.second].push_back(e.first);
    }

    vector<int> d(n+1);

    for(int i=1;i<=n;i++)
        d[i]=dfs(i,0);

    return d;
}

vector<pair<int,int>> gen_tree(int n){
    vector<pair<int,int>> edges;

    for(int i=2;i<=n;i++){
        int fa=uniform_int_distribution<int>(1,i-1)(rng);
        edges.push_back({fa,i});
    }

    return edges;
}

bool check_answer(
    int n,
    const vector<int>& target,
    const vector<pair<int,int>>& ans){

    if((int)ans.size()!=n-1)
        return false;

    vector<int> fa(n+1);

    function<int(int)> find=[&](int x){
        return fa[x]==x?x:fa[x]=find(fa[x]);
    };

    for(int i=1;i<=n;i++)
        fa[i]=i;

    for(auto e:ans){

        int u=e.first;
        int v=e.second;

        if(u<1||u>n) return false;
        if(v<1||v>n) return false;

        int fu=find(u);
        int fv=find(v);

        if(fu==fv)
            return false;

        fa[fu]=fv;
    }

    int rt=find(1);

    for(int i=2;i<=n;i++)
        if(find(i)!=rt)
            return false;

    auto real=calc_d(n,ans);

    for(int i=1;i<=n;i++)
        if(real[i]!=target[i])
            return false;

    return true;
}

void print_case(
    int n,
    const vector<int>& d){

    cout<<"Hack Found!\n\n";

    cout<<"1\n";
    cout<<n<<"\n";

    for(int i=1;i<=n;i++)
        cout<<d[i]<<" ";

    cout<<"\n";
}

int main(){

    while(true){

        int n=uniform_int_distribution<int>(2,9)(rng);

        auto tree=gen_tree(n);

        auto d=calc_d(n,tree);

        ofstream fout("input.txt");

        fout<<1<<"\n";
        fout<<n<<"\n";

        for(int i=1;i<=n;i++)
            fout<<d[i]<<" ";

        fout<<"\n";

        fout.close();
		#ifdef _WIN32
        int ret = system("std.exe < input.txt > output.txt");
#else
        int ret = system("./std < input.txt > output.txt");
#endif

        if(ret != 0){
            cout << "Fail to execute std program.\n";
            return 0;
        }

        ifstream fin("output.txt");

        string s;
        fin >> s;

        if(!fin){
            cout << "Output format error.\n";
            print_case(n,d);
            return 0;
        }

        if(s=="No"){

            cout<<"Your program outputs No!\n";
            print_case(n,d);

            cout<<"\nOriginal tree:\n";
            for(auto e:tree)
                cout<<e.first<<" "<<e.second<<"\n";

            return 0;
        }

        if(s!="Yes"){

            cout<<"First token is neither Yes nor No.\n";
            return 0;
        }

        vector<pair<int,int>> ans;

        for(int i=1;i<=n-1;i++){

            int u,v;

            if(!(fin>>u>>v)){
                cout<<"Too few edges.\n";
                print_case(n,d);
                return 0;
            }

            ans.push_back({u,v});
        }

        if(!check_answer(n,d,ans)){

            cout<<"Wrong Answer!\n";

            print_case(n,d);

            cout<<"\nYour edges:\n";

            for(auto e:ans)
                cout<<e.first<<" "<<e.second<<"\n";

            cout<<"\nOriginal tree:\n";

            for(auto e:tree)
                cout<<e.first<<" "<<e.second<<"\n";

            return 0;
        }

        static int cnt=0;

        ++cnt;

        if(cnt%1000==0){

            cout<<"Passed "<<cnt<<" cases\r";
            cout.flush();

        }

    }

    return 0;
}