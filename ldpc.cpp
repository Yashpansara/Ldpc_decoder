#include <bits/stdc++.h>
using namespace std;

float randomFloat()
{
    return (float)(rand()) / (float)(RAND_MAX);
}

int randomInt(int a, int b)
{
    if (a > b)
        return randomInt(b, a);
    if (a == b)
        return a;
    return a + (rand() % (b - a));
}

float randomFloat(int a, int b)
{
    if (a > b)
        return randomFloat(b, a);
    if (a == b)
        return a;

    return (float)randomInt(a, b) + randomFloat();
}

vector<int> random(int hc, float p)
{
    vector<int> temp(hc, 0);
    for (int i = 0; i < hc; i++)
    {
        double num = randomFloat(0, 1);
        // cout << num << endl;
        if (num < p)
        {
            temp[i] = -1;
        }
    }
    return temp;
}

int check(vector<int> *H, int hr, float prob, vector<int> &no_of_erase)
{

    int hc = H[0].size();
    vector<int> checknode[hr + 1], varnode[hc + 1];
    vector<pair<int, int>> varlist[hc + 1];
    for (int i = 0; i < hr; i++)
    {
        for (int j = 0; j < hc; j++)
        {
            if (H[i][j] == 1)
            {
                checknode[i + 1].push_back(j + 1);
            }
        }
    }

    // for(int i=1; i<hr+1; i++)
    // {
    //     cout<<i<<" : ";
    //     for(int j=0; j<checknode[i].size(); j++)
    //     {
    //         cout<<checknode[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }

    for (int i = 0; i < hc; i++)
    {
        for (int j = 0; j < hr; j++)
        {
            if (H[j][i] == 1)
            {
                varnode[i + 1].push_back(j + 1);
                varlist[i + 1].push_back({j + 1, -1});
            }
        }
    }

    // for(int i=1; i<hc+1; i++)
    // {
    //     cout<<i<<" : ";
    //     for(int j=0; j<varnode[i].size(); j++)
    //     {
    //         cout<<varnode[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }

    // for(int i=1; i<hc+1; i++)
    // {
    //     cout<<i<<" : ";
    //     for(int j=0; j<varlist[i].size(); j++)
    //     {
    //         cout<<varlist[i][j].first<<" "<<varlist[i][j].second<<"    ";
    //     }
    //     cout<<endl;
    // }

    vector<int> received(hc + 1), temp;
    temp = random(hc, prob);
    int prev = 0;
    for (int i = 1; i < hc + 1; i++)
    {
        received[i] = temp[i - 1];
        if (received[i] == -1)
        {
            prev++;
        }
    }

    if (no_of_erase.size() == 0)
        no_of_erase.push_back(prev);
    else
        no_of_erase[0] += prev;

    int iter = 1;
    int current = 0;
    do
    {
        if (iter != 1)
            prev = current;

        for (int i = 1; i <= hc; i++)
        {

            if (received[i] == 0 || received[i] == 1)
            {
                continue;
            }
            // cout<<i<<" : ";
            for (int j = 0; j < varlist[i].size(); j++)
            {
                // cout<<"{ "<<varlist[i][j].first<<": ";
                vector<int> temp;
                for (int k = 0; k < checknode[varlist[i][j].first].size(); k++)
                {
                    if (checknode[varlist[i][j].first][k] != i)
                    {
                        temp.push_back(received[checknode[varlist[i][j].first][k]]);
                    }
                }
                int ans = 0;
                int flag = 0;
                for (auto p : temp)
                {
                    if (p == -1)
                    {
                        flag = 1;
                        break;
                    }
                    ans = (ans + p) % 2;
                }

                if (flag == 1)
                {
                    continue;
                }
                varlist[i][j].second = ans;

                // for(auto p:temp)
                // {
                //     cout<<p<<" ";
                // }
                // cout<<"}    ";
            }
            // cout << endl;
        }

        current = 0;
        for (int i = 1; i <= hc; i++)
        {

            for (int j = 0; j < varlist[i].size(); j++)
            {
                if (varlist[i][j].second != -1)
                {
                    received[i] = varlist[i][j].second;
                    break;
                }
            }

            if (received[i] == -1)
            {
                current++;
            }
        }

        if (no_of_erase.size() < iter)
            no_of_erase.push_back(current);
        else
            no_of_erase[iter] += current;

        iter++;

    } while (prev != current && iter <= 100);

    // for(int i=1; i<=hc; i++)
    // {
    //     cout<<received[i]<<" ";
    // }
    // cout<<endl;

    int check_return = 1;
    for (int i = 1; i <= hc; i++)
    {
        if (received[i] == -1)
        {
            // for(auto jhks:temp)cout<<jhks<<" ";
            // cout<<endl;
            return 0;
        }
    }

    return check_return;
}

int main(int argc, char const *argv[])
{
    int hr, hc;
    cin >> hr >> hc;
    srand(time(0));
    vector<int> H[hr], checknode[hr + 1], varnode[hc + 1];
    vector<pair<int, int>> varlist[hc + 1];
    int input;
    for (int i = 0; i < hr; i++)
    {
        for (int j = 0; j < hc; j++)
        {
            cin >> input;
            H[i].push_back(input);
        }
    }

    int ans = 0;
    vector<int> no_of_erase;
    vector<vector<float>> graph(5, vector<float>(51, 0));
    for (float p = 0; p <= 1; p += 0.01)
    {
        ans = 0;
        no_of_erase.clear();
        for (int ind = 1; ind <= 1000; ind++)
        {
            ans = ans + check(H, hr, p, no_of_erase);
        }

        cout << "Probability of successful decoding when p=" << p << " : " << ans / (float)1000 << endl;
        if (p >= 0.29 && p <= 0.301)
        {
            for (int iter = 0; iter < no_of_erase.size(); iter++)
            {
                graph[0][iter] = no_of_erase[iter] / 1000.0;
                // cout<<iter<<" "<<no_of_erase[iter]/1000.0<<endl;
            }
        }
        if (p >= 0.39 && p <= 0.401)
        {
            for (int iter = 0; iter < no_of_erase.size(); iter++)
            {
                graph[1][iter] = no_of_erase[iter] / 1000.0;
                // cout<<iter<<" "<<no_of_erase[iter]/1000.0<<endl;
            }
        }
        if (p >= 0.49 && p <= 0.501)
        {
            for (int iter = 0; iter < no_of_erase.size(); iter++)
            {
                graph[2][iter] = no_of_erase[iter] / 1000.0;
                // cout<<iter<<" "<<no_of_erase[iter]/1000.0<<endl;
            }
        }
        if (p >= 0.509 && p <= 0.5101)
        {
            for (int iter = 0; iter < no_of_erase.size(); iter++)

            {
                graph[3][iter] = no_of_erase[iter] / 1000.0;
                // cout<<iter<<" "<<no_of_erase[iter]/1000.0<<endl;
            }
        }

        if (p >= 0.519 && p <= 0.5201)
        {
            for (int iter = 0; iter < no_of_erase.size(); iter++)
            {
                graph[4][iter] = no_of_erase[iter] / 1000.0;
                // cout<<iter<<" "<<no_of_erase[iter]/1000.0<<endl;
            }
        }
    }

    for (auto it : graph)
    {
        for (auto i : it)
        {
            cout << i << " ";
        }
        cout << endl;
    }

    // cout<<check(H,hr,1);

    return 0;
}
