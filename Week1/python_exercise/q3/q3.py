from typing import Callable
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
from scipy.optimize import curve_fit

def func(t, v, k):
    """ computes the function S(t) with constants v and k """
    
    # TODO: return the given function S(t)
    
    return v*(t-(1-np.exp(-k*t))/k)

    # END TODO


def find_constants(df: pd.DataFrame, func: Callable):
    """ returns the constants v and k """

    v = 0
    k = 0

    # TODO: fit a curve using SciPy to estimate v and k
    popt, pcov = curve_fit(func,df.t,df.S)
    v,k = popt
    # END TODO

    return v, k


if __name__ == "__main__":
    df = pd.read_csv("data.csv")
    v, k = find_constants(df, func)
    v = v.round(4)
    k = k.round(4)
    print(v, k)

    # TODO: plot a histogram and save to fit_curve.png
    plt.plot(df.t,df.S,'b*')
    x = np.linspace(0.016,0.370,num=100)
    y = func(x,v,k)
    plt.plot(x,y,color="red")
    plt.legend(["data",f"fit: v={v},k={k}"])
    
    plt.savefig("fit_curve.png")
    plt.show()
    # END TODO
