#include<bits/stdc++.h>
#define ll long
using namespace std;
void swap(ll *a,ll *b) {
    ll temp;
    temp = *a;
    *a = *b;
    *b = temp;
}
pthread_mutex_t plock;

void solve() {
    pthread_mutex_init(&plock, NULL);

    ll p[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    ll sum = 0;
    ll n;
    cout << " -------Shortest Job First Scheduling ( Non-Preemtitive )-------\n";
    cout << "\nEnter the No. of processes in Queue :";
    cin >> n;
    ll at[n];
    ll bt[n];
    for (ll i = 0; i < n; i++) {

        cout << "\nFor P " << i + 1 << "\n";
        pthread_mutex_lock(&plock);
        AA:
        cout << "Arrival time:";
        cin >> at[i];
        if (at[i] == 0) {
            cout << "\n Arrival time should not be zero!!!! Re-enter the correct arrival time \n";
            goto AA;
        }
        bt[i] = at[i] * 2;
        cout << "Burst Time:" << bt[i] << "\n";
        cout << "----------------------------------------";
        pthread_mutex_unlock(&plock);
    }


    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < n; j++) {
            if (at[i] < at[j]) {
                swap(&p[j], &p[i]);
                swap(&at[j], &at[i]);
                swap(&bt[j], &bt[i]);
            }
        }
    }


    ll btime = 0;
    ll k = 1;
    ll min;
    for (ll j = 0; j < n; j++) {
        btime = btime + bt[j];
        min = bt[k];
        for (ll i = k; i < n; i++) {
            if (btime >= at[i] && bt[i] > min) {
                swap(&p[k], &p[i]);
                swap(&at[k], &at[i]);
                swap(&bt[k], &bt[i]);
            }
        }
        k++;
    }
    ll wt[10], tt[10];
    wt[0] = 0;
    float wavg = 0, tavg = 0, tsum = 0, wsum = 0;
    for (ll i = 1; i < n; i++) {
        wt[i] = 0;
        for (ll j = 0; j < i; j++)
            wt[i] += bt[j];
        wsum += wt[i];
    }
    ll ta = 0;
    wavg = (wsum / n);
    for (ll i = 0; i < n; i++) {
        ta = ta + bt[i];
        tt[i] = ta - at[i];
        tsum = tsum + tt[i];
    }

    tavg = (tsum / n);

    cout << "\n RESULT:-";
    cout << "\nProcess\t Burst\t Arrival\t Waiting\t Turn-around";
    for (ll i = 0; i < n; i++) {
        cout << "\n p" << p[i] << "\t " << bt[i] << "\t " << at[i] << "\t\t " << wt[i] << "\t\t\t" << tt[i];
    }

    cout << "\n\nAVERAGE WAITING TIME : " << wavg;
    cout << "\nAVERAGE TURN AROUND TIME : " << tavg << "\n";

}
int main() {
    solve();
    return 0;
}
