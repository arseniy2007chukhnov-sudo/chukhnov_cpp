# Часть кода Python, в которой считаются точки теоретической O(N)
import pandas as pd
import matplotlib.pyplot as plt
# Для контекста создание Датафрейма:

df = pd.read_csv("algorithm_performance.csv")

# Собственно расчёт точек по теоретической O(N) (Используя среднее значение)

# Находим коэффициент, рассчитывая среднее значение (Сумма всех получившихся делений значений времени на N, делённая на количество точек)
scale_factor_n = (df['Time (miliseconds)'] / df['N']).mean()

# Создаём новый столбец в датафрейме для теоретического графика O(N)
df['O(n) Reference'] = scale_factor_n * df['N']

print(df)