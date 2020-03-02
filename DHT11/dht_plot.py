import matplotlib.pyplot as plt
import seaborn as sns
import pandas as pd
df = pd.read_csv('results.csv')
n = len(df['humidity'])
points = list(range(1,n+1))
plt.plot(points,df['humidity'],label = 'Humidity (%)')
plt.plot(points,df['temperature'],label = 'Temperature (Celsius)')
# plt.plot(points,df['ch4'],label = 'CH4')
plt.xlabel('Time (Seconds)')
plt.ylabel('Magnitude')
plt.legend()
# sns.set_style("darkgrid")
# sns.lineplot(x = points, y = 'ch4', data = df)
# sns.lineplot(x = points, y = 'co', data = df)
# sns.lineplot(x = points, y = 'lpg', data = df)
plt.show()
