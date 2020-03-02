import pandas as pd

df = pd.read_csv('res_gas.csv')
co= []
lpg = []
ch4 = []
for i in df['ratio']:
    if i > 1.7:
        co.append(0)
        lpg.append(0)
        ch4.append(0)
    if i > 1.1 and i <= 1.7:
        co.append(200)
        lpg.append(400)
        ch4.append(500)
    if i > 0.85 and i <= 1.1:
        co.append(500)
        lpg.append(700)
        ch4.append(1000)
    if i > 0.8 and i <= 0.85:
        co.append(800)
        lpg.append(1000)
        ch4.append(2500)
    if i > 0.6 and i <= 0.8:
        co.append(1000)
        lpg.append(2800)
        ch4.append(3500)
    if i > 0.5 and i <= 0.6:
        co.append(2000)
        lpg.append(4000)
        ch4.append(5500)
    if i > 0.38 and i <= 0.5:
        co.append(3000)
        lpg.append(5000)
        ch4.append(7000)
    if i > 0.26 and i <= 0.38:
        co.append(5000)
        lpg.append(7000)
        ch4.append(10000)
    if i > 0.0 and i <= 0.26:
        co.append(10000)
        lpg.append(12000)
        ch4.append(15000)

df['co'] = co
df['lpg'] = lpg
df['ch4'] = ch4

df.to_csv('result_gas.csv')
