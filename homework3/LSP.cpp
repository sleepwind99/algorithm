#include <iostream>
#include <limits.h>
#include <queue>
#include <thread>
#include <tuple>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::get;
using std::make_tuple;
using std::thread;
using std::tuple;
using std::vector;

typedef tuple<int, int> pair;
vector<thread> work;
vector<pair> *edge;
tuple<int, int, int> cumuldist;
int numTrd = 8;
int numVtx;

void insertEdge(int v0, int v1, int w) { edge[v0].push_back(make_tuple(v1, w)); }

void progressBar(int cur) {
    float progress = (float)cur / numVtx;
    int pos = 70 * progress;
    cout << "[";
    for (int i = 0; i < 70; ++i) {
        if (i < pos)
            cout << "=";
        else if (i == pos)
            cout << ">";
        else
            cout << " ";
    }
    cout << std::fixed;
    cout.precision(2);
    cout << "] " << progress * 100.0f << " %\r";
    cout.flush();
}

void Dijktra(int trdId, tuple<int, int, int> &longDist) {
    for (int src = trdId; src < numVtx; src += numTrd) {
        std::priority_queue<pair, vector<pair>, std::greater<pair>> prt_queue;
        vector<int> shortDist(numVtx, INT_MAX);
        prt_queue.push(make_tuple(0, src));
        shortDist[src] = 0;

        while (!prt_queue.empty()) {
            int v0 = get<1>(prt_queue.top());
            prt_queue.pop();
            vector<pair>::iterator i;
            for (i = edge[v0].begin(); i != edge[v0].end(); i++) {
                int v1 = get<0>(*i);
                int weight = get<1>(*i);
                if (shortDist[v1] > shortDist[v0] + weight) {
                    shortDist[v1] = shortDist[v0] + weight;
                    prt_queue.push(make_tuple(shortDist[v1], v1));
                }
            }
        }

        for (int i = 0; i < numVtx; i++)
            if (i != src && shortDist[i] != INT_MAX && shortDist[i] > get<2>(longDist))
                longDist = make_tuple(src, i, shortDist[i]);

        if (trdId == 0 && src % 100 == 0)
            progressBar(src);
    }
}

void DijktraT() {
    vector<thread> work;
    vector<tuple<int, int, int>> longdists;
    longdists.resize(numTrd);
    work.resize(numTrd);
    for (int i = 0; i < numTrd; i++) {
        longdists[i] = make_tuple(0, 0, -1);
        work[i] = thread(Dijktra, i, std::ref(longdists[i]));
    }
    for (int i = 0; i < numTrd; i++)
        work[i].join();

    cumuldist = longdists[0];
    for (int i = 0; i < numTrd; i++)
        if (get<2>(cumuldist) < get<2>(longdists[i]))
            cumuldist = longdists[i];

    cout << "[=====================================================================>] 100.00 %"
         << endl;
    cout << get<0>(cumuldist) << " " << get<1>(cumuldist) << " " << get<2>(cumuldist) << endl;
}

void SPFA(int trdId, tuple<int, int, int> &longDist) {
    for (int src = trdId; src < numVtx; src += numTrd) {
        std::deque<int> dec;
        vector<int> shortDist(numVtx, INT_MAX);
        bool isQueue[numVtx];

        dec.push_back(src);
        shortDist[src] = 0;
        isQueue[src] = true;
        while (!dec.empty()) {
            int v0 = dec.front();
            dec.pop_front();
            isQueue[v0] = false;
            for (auto i : edge[v0]) {
                if (shortDist[get<0>(i)] > shortDist[v0] + get<1>(i)) {
                    shortDist[get<0>(i)] = shortDist[v0] + get<1>(i);
                    if (!isQueue[get<0>(i)]) {
                        dec.push_back(get<0>(i));
                        isQueue[get<0>(i)] = true;
                        if (shortDist[dec.back()] < shortDist[dec.front()]) {
                            dec.push_back(dec.back());
                            dec.pop_back();
                        }
                    }
                    if (shortDist[get<0>(i)] > get<2>(longDist))
                        longDist = make_tuple(src, get<0>(i), shortDist[get<0>(i)]);
                }
            }
        }

        if (trdId == 0 && src % 100 == 0)
            progressBar(src);
    }
}

void SPFAT() {
    vector<thread> work;
    vector<tuple<int, int, int>> longdists;
    longdists.resize(numTrd);
    work.resize(numTrd);
    for (int i = 0; i < numTrd; i++) {
        longdists[i] = make_tuple(0, 0, -1);
        work[i] = thread(SPFA, i, std::ref(longdists[i]));
    }
    for (int i = 0; i < numTrd; i++)
        work[i].join();

    cumuldist = longdists[0];
    for (int i = 0; i < numTrd; i++)
        if (get<2>(cumuldist) < get<2>(longdists[i]))
            cumuldist = longdists[i];

    cout << "[=====================================================================>] 100.00 %"
         << endl;
    cout << get<0>(cumuldist) << " " << get<1>(cumuldist) << " " << get<2>(cumuldist) << endl;
}

void getInput() {
    edge = new vector<pair>[numVtx];
    while (true) {
        int src, dest, weight;
        cin >> src >> dest >> weight;
        if (cin.eof())
            break;
        insertEdge(src, dest, weight);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cout << "One argument is required." << endl;
        return 0;
    }
    numVtx = atoi(argv[1]);
    getInput();
    SPFAT();
    return 0;
}