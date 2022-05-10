import numpy as np
import matplotlib.pyplot as plt
from scipy.interpolate import interp1d



n=1e8
#print(x.shape)
def statistic(x,n):
    print('samples',x[x>0].shape,end=' ')
    x_average=np.sum(x)/n
    x_std=np.sqrt((np.sum(x**2)/n-x_average**2)/n)/x_average
    return x_average,x_std


gamma=np.fromfile('gamma.data',dtype=np.float64)
gamma=gamma.reshape(-1,20)
center,center_std=statistic(gamma[:,0],n)
print(center,center_std)
para=10/center
for i in range(19):
    value,error=statistic(gamma[:,i+1],n)
    print('%f usv/h %.2f'%(value*para*1e-6*60,error))






    

   


