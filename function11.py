# ----------
#   README
# ----------
# Create on 2025-12-17
# Version 2
# 
# Python实现版本，依赖python3.x，numpy，matplotlib
# 
# f(x) = f(1-x)
# f(x) = 2f(x/10)
# f(x)的定义域和值域均为[0,1]
# 有:
# f(x)/2 = f(1-x)/2
# f(x/10) = f((1-x)/10)
# f(x/10) = f(0.1-x/10)，同理f(1-x/10) = f(x/10+0.9)
# 递归求证f(x)是分形，f(x)在[a,b]与[a,a+(b-a)/10],[b-(b-a)/10,b]自相似，其中初始a=0，b=1

import numpy as np
import matplotlib.pyplot as plt

LIMIT = 15
fct11_x = [0.5]
fct11_y = [0.5]
def dfs(x, y, step):
    if step > LIMIT:
        return
    fct11_x.append(x)
    fct11_y.append(y)
    dfs(x/10, y/2, step+1)      
    dfs(1-x/10, 1-y/2, step+1)  

dfs(0.5, 0.5, 1) # 递归求解f(x) 参数：dfs（当前自变量，当前因变量，当前递归深度）

# 此处换成任意 t∈[0.1, 0.9]，求解dfs(t, 0.5, 1)都不会影响结果
# 如：
# dfs(0.3, 0.5, 1)
# dfs(0.85, 0.5, 1)

plt.title('Function 11')
plt.xlabel('x')
plt.ylabel('y')
plt.xlim((-0.5,1.5))        # x轴默认显示范围
plt.ylim((0,1))             # y轴默认显示范围
fct11_x = sorted(fct11_x)   # f(x)在[0,1]单调递增，排序不影响点对匹配
fct11_y = sorted(fct11_y)   # f(x)在[0,1]单调递增，排序不影响点对匹配
plt.plot(fct11_x, fct11_y, c='blue', linestyle='-', marker='')  # 绘图 参数：plot（x轴采样点，y轴采样点，函数颜色，线样式，点样式）
plt.legend(['F11'])
plt.show()                  # 显示函数窗口
