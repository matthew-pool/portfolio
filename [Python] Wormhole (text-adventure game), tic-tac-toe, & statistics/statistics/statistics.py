# This module will be used to prepare a pandas dataframe and calculate descriptive statistics
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import numpy as np
import random

temperatures = [91,93,93,91,82,91,93,82,93,93,91,93,91,90]

# prepare a dataframe for temperatures.
temperatures_df = pd.DataFrame(temperatures, columns=['temperature'])

# print temperatures dataframe
print(temperatures_df)

# mean
mean = temperatures_df['temperature'].mean()
print("Mean=", round(mean,2))

# median
median = temperatures_df['temperature'].median()
print("Median=", round(median,2))

# variance
variance = temperatures_df['temperature'].var()
print("Variance=", round(variance,2))

# standard deviation
stdeviation = temperatures_df['temperature'].std()
print("Standard Deviation=", round(stdeviation,2))

# descriptive statistics
statistics = temperatures_df['temperature'].describe()
print("")
print ("Describe method")
print (statistics)

# line chart
# plt.plot(temperatures_df['temperature']) # plot
plt.hist(temperatures_df['temperature'])

# setting a title for the plot, x-axis and y-axis
# plt.title('Line graph of temperature data', fontsize=20)
plt.title('Histogram of temperature data', fontsize=20)
plt.xlabel('day')
plt.ylabel('temperature')

# show the plot
plt.show()

# The temperature data created for Zion will be unique to you.
mean = random.randint(temperatures_df['temperature'].min(),temperatures_df['temperature'].max())
std_deviation = random.randint(round(temperatures_df['temperature'].std(),0),round(2*temperatures_df['temperature'].std(),0))
zion_temperatures = np.random.normal(mean, std_deviation, 25)
zion_temperatures = pd.DataFrame(zion_temperatures, columns=['temperature'])

# side-by-side boxplots require the two dataframes to be concatenated and require a variable identifying the data
temperatures_df['id'] = 'my_data'
zion_temperatures['id'] = 'zion_data'
both_temp_df = pd.concat((temperatures_df, zion_temperatures))

# sets a title for the plot, x-axis, and y-axis
plt.title('Boxplot for comparison', fontsize=20)

# prepares the boxplot
sns.boxplot(x="id",y="temperature",data=both_temp_df)

# shows the plot
plt.show()
