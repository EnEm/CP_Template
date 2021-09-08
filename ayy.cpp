#include<bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

int gpt = 0;
static vector<double> dp[729][62][62][7];

//All time in seconds
class Problem
{
    private:
        int expectedDuration;
        int standardDeviation;

        double normalCDF(double x)
        {
            return 0.5 * erfc( (-x + expectedDuration) / (standardDeviation * sqrt((double)2) ) );
        }

    public:
        Problem(int mean, int delta)
        {
            expectedDuration = mean;
            standardDeviation = delta;
        }
        Problem(int mean)
        {
            expectedDuration = mean;
            standardDeviation = mean / 2;
        }

        double remainingProbability(int time)
        {
            return 1 - normalCDF((double)time);
        }
};

class Lockout
{
    private:
        int duration;
        int numProblems;
        vector<Problem> problems;

        int getEvaluationBracket(int time)
        {
            return ((int) (ceil(sqrt(time)/2) + 1e-5));
        }
        
        int getEvaluationTime(int bracket)
        {
            return (bracket*bracket)*4;
        }

        int getProblemState(int state, int problem)
        {
            int tmp = 1;
            for(int i=0; i<problem; i++)
                tmp *= 3;
            return (state / tmp) % 3;
        }

        int setProblemState(int state, int participant, int problem)
        {
            int tmp = 1;
            for(int i=0; i<problem; i++)
                tmp *= 3;
                
            if((state / tmp) % 3 == 0)
                state += tmp * (participant + 1);

            return state;
        }

        int reverseState(int state)
        {
            int tmp = 1;
            for(int i=0; i<numProblems; i++)
            {
                if((state / tmp) % 3 == 1)
                    state += tmp;
                else if((state / tmp) % 3 == 2)
                    state -= tmp;
                tmp *= 3;
            }

            return state;
        }

        int getWinScore()
        {
            int sm = 0;
            for(int i=0; i<numProblems; i++)
                sm += ((i+1)*100 + (1<<i));
            return (sm>>1) + 1;
        }

        vector<double> winProbabilityHelper(int state, int timeElapsed, int opponentTimeOnProblem, int opponentProblem)
        {
            int timeBracket = getEvaluationBracket(timeElapsed);
            int opponentBracket = getEvaluationBracket(opponentTimeOnProblem);

            if(!dp[state][timeBracket][opponentBracket][opponentProblem+1].empty())
                return dp[state][timeBracket][opponentBracket][opponentProblem+1];

            int tmp = state, scores[2] = {};
            for(int i=0; i<numProblems; i++)
            {
                scores[tmp%3 - 1] += (i+1)*100 + (1<<i);
                tmp /= 3;
            }

            if(scores[0] >= getWinScore())
                return dp[state][timeBracket][opponentBracket][opponentProblem+1] = vector<double>(numProblems, 1);
                
            if(scores[1] >= getWinScore())
                return dp[state][timeBracket][opponentBracket][opponentProblem+1] = vector<double>(numProblems, 0);

            if(timeElapsed > duration && scores[0] > scores[1])
                return dp[state][timeBracket][opponentBracket][opponentProblem+1] = vector<double>(numProblems, 1);
                
            if(timeElapsed > duration && scores[0] < scores[1])
                return dp[state][timeBracket][opponentBracket][opponentProblem+1] = vector<double>(numProblems, 0);

            vector<vector<double>> winProbabilityMatrix(numProblems, vector<double>(numProblems, 0));
            for(int i=0; i<numProblems; i++)
            {
                if(getProblemState(state, i) != 0) continue;
                for(int j=0; j<numProblems; j++)
                {
                    if(getProblemState(state, j) != 0)
                    {
                        winProbabilityMatrix[i][j] = 1;
                        continue;
                    }

                    double jprv = 1, iprv = 1;
                    for(int k = timeBracket + 1; getEvaluationTime(k) <= duration; k++)
                    {

                        double inxt = problems[i].remainingProbability(getEvaluationTime(k) - getEvaluationTime(timeBracket)) / problems[i].remainingProbability(0),
                            jnxt = problems[j].remainingProbability(getEvaluationTime(k) - getEvaluationTime(timeBracket)) / problems[j].remainingProbability(0);
                        if(opponentProblem == j || opponentProblem == -1)
                            double jnxt = problems[j].remainingProbability(getEvaluationTime(k) - getEvaluationTime(timeBracket) + getEvaluationTime(opponentBracket)) / problems[j].remainingProbability(getEvaluationTime(opponentBracket));

                        vector<double> tmp = winProbabilityHelper(reverseState(setProblemState(state, 1, j)),
                        getEvaluationTime(k), getEvaluationTime(k) - getEvaluationTime(timeBracket), i);
                        double mx = 0;
                        for(auto it : tmp) mx = max(mx, it);

                        winProbabilityMatrix[i][j] += (1 - mx) * (jprv - jnxt) * inxt;
                        if(i == j) winProbabilityMatrix[i][j] += (1 - mx) * (jprv - jnxt) * (iprv - inxt) / 2;

                        tmp = winProbabilityHelper(setProblemState(state, 0, i),
                        getEvaluationTime(k), getEvaluationTime(k) - getEvaluationTime(timeBracket) + getEvaluationTime(opponentBracket), j);
                        mx = 0;
                        for(auto it : tmp) mx = max(mx, it);

                        winProbabilityMatrix[i][j] += mx * (iprv - inxt) * jnxt;
                        if(i == j) winProbabilityMatrix[i][j] += mx * (iprv - inxt) * (jprv - jnxt) / 2;

                        if(i != j)
                        {
                            tmp = winProbabilityHelper(setProblemState(setProblemState(state, 0, i), 1, j),
                            getEvaluationTime(k), 0, 0);
                            mx = 0;
                            for(auto it : tmp) mx = max(mx, it);

                            winProbabilityMatrix[i][j] += mx * (iprv - inxt) * (jprv - jnxt);
                        }

                        iprv = inxt; jprv = jnxt;
                    }
                    
                    if(scores[0] > scores[1]) winProbabilityMatrix[i][j] += iprv * jprv;

                    winProbabilityMatrix[i][j] = max((double)0, min((double)1, winProbabilityMatrix[i][j]));
                }
            }

            vector<double> ans;
            for(int i=0; i<numProblems; i++)
            {
                double mn = 1;
                for(auto it : winProbabilityMatrix[i]) mn = min(mn, it);
                ans.push_back(mn);
            }
gpt++;
if(gpt%1000 == 0)
{
cout<<gpt<<endl;
// for(int i=0; i<numProblems; i++) cout<<getProblemState(state, i);
// cout<<' '<<scores[0]<<' '<<scores[1]<<' '<<timeBracket<<' '<<opponentBracket<<' '<<opponentProblem<<endl;
// for(int i=0; i<numProblems; i++)
// {
//     for(int j=0; j<numProblems; j++)
//     {
//         cout<<fixed<<setprecision(4)<<winProbabilityMatrix[i][j]<<' ';
//     }
//     cout<<'\n';
// }
}
            return dp[state][timeBracket][opponentBracket][opponentProblem+1] = ans;
        }

    public:
        Lockout(vector<pair<int, int>> vec, int time = 3600)
        {
            numProblems = vec.size();
            duration = time;
            for(int i = 0; i < numProblems; i++)
            {
                problems.push_back(Problem(vec[i].first, vec[i].second));
            }
        }

        vector<double> winProbability(vector<pair<int, pair<bool, int>>> events)
        {
            sort(events.begin(), events.end());

            int state = 0;
            int timeElapsed = 0;
            int lastOpponentProblemTime = 0;

            for(auto event : events)
            {
                timeElapsed = event.first;

                int participant = event.second.first;
                if(participant == 1)
                    lastOpponentProblemTime = event.first;

                int problem =  event.second.second;

                if(problem == -1)
                {
                    continue;
                }

                state = setProblemState(state, participant, problem);
            }

            return winProbabilityHelper(state, timeElapsed, timeElapsed - lastOpponentProblemTime, -1);
        }
};

int main()
{
    ifstream fin;
    fin.open("kekw.txt");

    string line;

    getline(fin, line);
    stringstream ss(line);
    int n, t;
    ss>>n>>t;

    vector<pair<int, int>> v(n);
    for(int i=0; i<n; i++)
    {
        getline(fin, line);
        stringstream ss(line);
        ss>>v[i].first>>v[i].second;
    }
    getline(fin, line);
    getline(fin, line);
    getline(fin, line);

    Lockout l = Lockout(v, t);

    vector<pair<int, pair<bool, int>>> events;
    int starthour = -1, startminute = -1;
    while(getline(fin, line))
    {
        string time, event;
        stringstream ss(line);

        getline(ss, time, ' ');
        getline(ss, event, ' ');

        int hour = stoi(time.substr(0, 2));
        int minute = stoi(time.substr(3, 2));

        if(event.empty())
        {
            if(starthour == -1 && startminute == -1)
            {
                starthour = hour;
                startminute = minute;
            }
            else
            {
                events.push_back({(hour-starthour)*3600 + (minute-startminute)*60, {((event[0] == '+')?false:true), -1}});
            }
        }
        else
        {
            events.push_back({(hour-starthour)*3600 + (minute-startminute)*60, {((event[0] == '+')?false:true), event[1]-'A'}});
        }
    }

    vector<double> ans = l.winProbability(events);
    for(int i=0; i<n; i++)
    {
        cout<<fixed<<setprecision(4)<<((char)('A'+i))<<" : "<<(ans[i]*100)<<" %\n";
    }

    return 0;
}