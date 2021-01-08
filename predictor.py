from bs4 import *
import requests
import time
import datetime
import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize  import curve_fit

def ratings(user):

    r = requests.get( 'https://codeforces.com/api/user.rating?handle=' + user )

    PARTITIONS = 1

    time_ratings = []

    for x in range(0,PARTITIONS+1):
        time_ratings.append(( (r.json()['result'][0]['ratingUpdateTimeSeconds'] * (PARTITIONS-x) + r.json()['result'][1]['ratingUpdateTimeSeconds'] * x) / PARTITIONS, (1450 * (PARTITIONS-x) + r.json()['result'][0]['newRating'] * x) / PARTITIONS ))

    for i in range(1,len(r.json()['result'])-1):
        for x in range(1,PARTITIONS+1):
            time_ratings.append(( (r.json()['result'][i]['ratingUpdateTimeSeconds'] * (PARTITIONS-x) + r.json()['result'][i+1]['ratingUpdateTimeSeconds'] * x) / PARTITIONS, (r.json()['result'][i]['oldRating'] * (PARTITIONS-x) + r.json()['result'][i]['newRating'] * x) / PARTITIONS ))
    
    t = time.time()

    for x in range(1,PARTITIONS+1):
        time_ratings.append(( (r.json()['result'][len(r.json()['result'])-1]['ratingUpdateTimeSeconds'] * (PARTITIONS-x) + t * x) / PARTITIONS, float(r.json()['result'][len(r.json()['result'])-1]['newRating']) ))


    return time_ratings

def func1(x, a, b, c):
    return (1e2*a) * np.log(x - (1e6*b)) + (1e3*c)
    
def func1_inverse(y, a, b, c):
    return np.exp( (y - (1e3*c)) / (1e2*a) ) + (1e6*b)

def func2(x, a, b, c):
    return -np.exp(-(x - (1e9*b)) / (1e7*a)) + (1e3*c)

def func2_inverse(y, a, b, c):
    if y>=(1e3*c): return 0
    return -np.log( -(y - (1e3*c)) ) * (1e7*a) + (1e9*b)

if __name__ == "__main__":

    s = input()
    v = ratings(s)
    print(v)
    
    x0 = []
    y0 = []
    for t in v:
        x0.append(t[0])
        y0.append(t[1])

    strt = x0[0] - 60*60*24*30
    # strt = 0

    for i in range(len(v)-1,-1,-1):
        x0[i] -= strt
    
    x = np.array(x0)
    y = np.array(y0)

    YEARS = 2

    xnew = np.linspace(x0[0], x0[len(x0)-1] + 60*60*24*256*YEARS, 1000)

    popt1, pcov1 = curve_fit(func1, x, y)

    print('Expected by logarithmic')

    print('Values')
    print(popt1)
    print('Covariance')
    print(pcov1)

    print('Pupil at ', datetime.datetime.utcfromtimestamp(func1_inverse(1200, *popt1) + strt).strftime('%Y-%m-%d %H:%M:%S') )
    print('Specialist at ', datetime.datetime.utcfromtimestamp(func1_inverse(1400, *popt1) + strt).strftime('%Y-%m-%d %H:%M:%S') )
    print('Expert at ', datetime.datetime.utcfromtimestamp(func1_inverse(1600, *popt1) + strt).strftime('%Y-%m-%d %H:%M:%S') )
    print('Candidate Master at ', datetime.datetime.utcfromtimestamp(func1_inverse(1900, *popt1) + strt).strftime('%Y-%m-%d %H:%M:%S') )
    print('Master at ', datetime.datetime.utcfromtimestamp(func1_inverse(2100, *popt1) + strt).strftime('%Y-%m-%d %H:%M:%S') )
    print('International Master at ', datetime.datetime.utcfromtimestamp(func1_inverse(2300, *popt1) + strt).strftime('%Y-%m-%d %H:%M:%S') )
    print('GrandMaster at ', datetime.datetime.utcfromtimestamp(func1_inverse(2400, *popt1) + strt).strftime('%Y-%m-%d %H:%M:%S') )
    print('International Grandmaster at ', datetime.datetime.utcfromtimestamp(func1_inverse(2600, *popt1)+ strt).strftime('%Y-%m-%d %H:%M:%S') )
    print('Legendary Grandmaster at ', datetime.datetime.utcfromtimestamp(func1_inverse(3000, *popt1) + strt).strftime('%Y-%m-%d %H:%M:%S') )
    print('GR1 at ', datetime.datetime.utcfromtimestamp(func1_inverse(3800, *popt1) + strt).strftime('%Y-%m-%d %H:%M:%S') )
    
    popt2, pcov2 = curve_fit(func2, x, y)

    print('Expected by exopnentianal')

    print('Values')
    print(popt2)
    print('Covariance')
    print(pcov2)

    print('Pupil at ', datetime.datetime.utcfromtimestamp(func2_inverse(1200, *popt2) + strt).strftime('%Y-%m-%d %H:%M:%S') )
    print('Specialist at ', datetime.datetime.utcfromtimestamp(func2_inverse(1400, *popt2) + strt).strftime('%Y-%m-%d %H:%M:%S') )
    print('Expert at ', datetime.datetime.utcfromtimestamp(func2_inverse(1600, *popt2) + strt).strftime('%Y-%m-%d %H:%M:%S') )
    print('Candidate Master at ', datetime.datetime.utcfromtimestamp(func2_inverse(1900, *popt2) + strt).strftime('%Y-%m-%d %H:%M:%S') )
    print('Master at ', datetime.datetime.utcfromtimestamp(func2_inverse(2100, *popt2) + strt).strftime('%Y-%m-%d %H:%M:%S') )
    print('International Master at ', datetime.datetime.utcfromtimestamp(func2_inverse(2300, *popt2) + strt).strftime('%Y-%m-%d %H:%M:%S') )
    print('GrandMaster at ', datetime.datetime.utcfromtimestamp(func2_inverse(2400, *popt2) + strt).strftime('%Y-%m-%d %H:%M:%S') )
    print('International Grandmaster at ', datetime.datetime.utcfromtimestamp(func2_inverse(2600, *popt2)+ strt).strftime('%Y-%m-%d %H:%M:%S') )
    print('Legendary Grandmaster at ', datetime.datetime.utcfromtimestamp(func2_inverse(3000, *popt2) + strt).strftime('%Y-%m-%d %H:%M:%S') )
    print('GR1 at ', datetime.datetime.utcfromtimestamp(func2_inverse(3800, *popt2) + strt).strftime('%Y-%m-%d %H:%M:%S') )

    plt.plot(x, y, 'o', xnew, func1(xnew, *popt1), '--', func2(xnew, *popt2), '--',)
    plt.legend(['Data', 'Expected by logarithmic', 'Expected by exopnentianal'])
    plt.show()