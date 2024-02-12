import pandas as pd
import numpy as np
from sklearn.preprocessing import StandardScaler

print("hello world\n");

all_data = pd.read_csv('full_data.csv')

target = 'stroke'
X = all_data.loc[:,all_data.columns!=target]
y = all_data.loc[:,all_data.columns==target]

columns = ['gender', 'age', 'hypertension', 'heart_disease', 'ever_married',
       'work_type', 'Residence_type', 'avg_glucose_level', 'bmi',
       'smoking_status']
X = pd.get_dummies(X[columns])

print(all_data[target].value_counts())

# **There is an oversampling in the dataset. There is a big difference between those who do not have a stroke and those who do.**

percentage_no_stroke = 100*(4733/float(all_data.shape[0]))
percentage_no_stroke

percentage_yes_stroke = 100*(248/float(all_data.shape[0]))
percentage_yes_stroke

from sklearn.datasets import make_classification
from imblearn.over_sampling import SMOTE

oversample = SMOTE()
X, y = oversample.fit_resample(X, y)

print(y[target].value_counts())

# # Now we have a balanced dataset

from sklearn.model_selection import train_test_split

X_train, X_test, Y_train, Y_test = train_test_split(X,y, test_size=0.20, shuffle=True)

print(X_train)


# # MODEL BUILDING

# **RANDOM FOREST**

from sklearn.ensemble import RandomForestClassifier

def rf(X_train, Y_train, n_estimators=250):
 rndforest = RandomForestClassifier(n_estimators=n_estimators, n_jobs=1)
 rndforest.fit(X_train, Y_train)
 return rndforest

random_forest_en = rf(X_train,Y_train.values.ravel(), n_estimators=250)

print("TRAINING ACCURACY:", random_forest_en.score(X_train, Y_train))
print("VALIDATION ACCURACY", random_forest_en.score(X_test, Y_test))