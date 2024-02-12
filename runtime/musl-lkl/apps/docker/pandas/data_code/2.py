import pandas as pd
import matplotlib.pyplot as plt
from sklearn.preprocessing import StandardScaler
import seaborn as sns
sns.set(style="darkgrid")

# %% [code] {"execution":{"iopub.status.busy":"2022-08-05T10:32:09.578267Z","iopub.execute_input":"2022-08-05T10:32:09.579026Z","iopub.status.idle":"2022-08-05T10:32:09.597492Z","shell.execute_reply.started":"2022-08-05T10:32:09.578987Z","shell.execute_reply":"2022-08-05T10:32:09.595845Z"}}
all_data = pd.read_csv('full_data.csv')

# %% [code] {"execution":{"iopub.status.busy":"2022-08-05T10:32:09.635497Z","iopub.execute_input":"2022-08-05T10:32:09.635923Z","iopub.status.idle":"2022-08-05T10:32:09.667878Z","shell.execute_reply.started":"2022-08-05T10:32:09.635889Z","shell.execute_reply":"2022-08-05T10:32:09.666109Z"}}
all_data

# %% [code] {"execution":{"iopub.status.busy":"2022-08-05T10:32:09.679432Z","iopub.execute_input":"2022-08-05T10:32:09.67982Z","iopub.status.idle":"2022-08-05T10:32:09.689418Z","shell.execute_reply.started":"2022-08-05T10:32:09.679789Z","shell.execute_reply":"2022-08-05T10:32:09.688443Z"}}
target = 'stroke'
X = all_data.loc[:,all_data.columns!=target]
y = all_data.loc[:,all_data.columns==target]

# %% [code] {"execution":{"iopub.status.busy":"2022-08-05T10:32:09.715444Z","iopub.execute_input":"2022-08-05T10:32:09.715847Z","iopub.status.idle":"2022-08-05T10:32:09.734963Z","shell.execute_reply.started":"2022-08-05T10:32:09.715815Z","shell.execute_reply":"2022-08-05T10:32:09.734017Z"}}
columns = ['gender', 'age', 'hypertension', 'heart_disease', 'ever_married',
       'work_type', 'Residence_type', 'avg_glucose_level', 'bmi',
       'smoking_status']
X = pd.get_dummies(X[columns])

# %% [code] {"execution":{"iopub.status.busy":"2022-08-05T10:32:09.798414Z","iopub.execute_input":"2022-08-05T10:32:09.799681Z","iopub.status.idle":"2022-08-05T10:32:09.929878Z","shell.execute_reply.started":"2022-08-05T10:32:09.799628Z","shell.execute_reply":"2022-08-05T10:32:09.928589Z"}}
ax = sns.countplot(x=target,data=all_data)
print(all_data[target].value_counts())

# %% [markdown]
# **There is an oversampling in the dataset. There is a big difference between those who do not have a stroke and those who do.**

# %% [code] {"execution":{"iopub.status.busy":"2022-08-05T10:32:09.935051Z","iopub.execute_input":"2022-08-05T10:32:09.935617Z","iopub.status.idle":"2022-08-05T10:32:09.943594Z","shell.execute_reply.started":"2022-08-05T10:32:09.935582Z","shell.execute_reply":"2022-08-05T10:32:09.9424Z"}}
percentage_no_stroke = 100*(4733/float(all_data.shape[0]))
percentage_no_stroke

# %% [code] {"execution":{"iopub.status.busy":"2022-08-05T10:32:09.945575Z","iopub.execute_input":"2022-08-05T10:32:09.946499Z","iopub.status.idle":"2022-08-05T10:32:09.956892Z","shell.execute_reply.started":"2022-08-05T10:32:09.946447Z","shell.execute_reply":"2022-08-05T10:32:09.955697Z"}}
percentage_yes_stroke = 100*(248/float(all_data.shape[0]))
percentage_yes_stroke

# %% [code] {"execution":{"iopub.status.busy":"2022-08-05T10:32:09.985587Z","iopub.execute_input":"2022-08-05T10:32:09.986799Z","iopub.status.idle":"2022-08-05T10:32:10.021465Z","shell.execute_reply.started":"2022-08-05T10:32:09.986757Z","shell.execute_reply":"2022-08-05T10:32:10.019458Z"}}
import seaborn as sns
from sklearn.datasets import make_classification
from imblearn.over_sampling import SMOTE

oversample = SMOTE()
X, y = oversample.fit_resample(X, y)

# %% [code] {"execution":{"iopub.status.busy":"2022-08-05T10:32:10.051889Z","iopub.execute_input":"2022-08-05T10:32:10.052871Z","iopub.status.idle":"2022-08-05T10:32:10.212069Z","shell.execute_reply.started":"2022-08-05T10:32:10.052796Z","shell.execute_reply":"2022-08-05T10:32:10.210195Z"}}
ax = sns.countplot(x=target,data=y)
print(y[target].value_counts())

# %% [markdown]
# # Now we have a balanced dataset

# %% [code] {"execution":{"iopub.status.busy":"2022-08-05T10:32:10.215059Z","iopub.execute_input":"2022-08-05T10:32:10.215874Z","iopub.status.idle":"2022-08-05T10:32:10.227957Z","shell.execute_reply.started":"2022-08-05T10:32:10.215824Z","shell.execute_reply":"2022-08-05T10:32:10.226897Z"}}
from sklearn.model_selection import train_test_split

X_train, X_test, Y_train, Y_test = train_test_split(X,y, test_size=0.20, shuffle=True)

print(X_train)

# %% [markdown]
# # MODEL BUILDING

# %% [markdown]
# **RANDOM FOREST**

# %% [code] {"execution":{"iopub.status.busy":"2022-08-05T10:32:10.229595Z","iopub.execute_input":"2022-08-05T10:32:10.230234Z","iopub.status.idle":"2022-08-05T10:32:10.237452Z","shell.execute_reply.started":"2022-08-05T10:32:10.230199Z","shell.execute_reply":"2022-08-05T10:32:10.235315Z"}}
from sklearn.ensemble import RandomForestClassifier

def rf(X_train, Y_train, n_estimators=250):
 rndforest = RandomForestClassifier(n_estimators=n_estimators, n_jobs=-1)
 rndforest.fit(X_train, Y_train)
 return rndforest

# %% [code] {"execution":{"iopub.status.busy":"2022-08-05T10:32:10.242488Z","iopub.execute_input":"2022-08-05T10:32:10.243666Z","iopub.status.idle":"2022-08-05T10:32:11.572958Z","shell.execute_reply.started":"2022-08-05T10:32:10.243594Z","shell.execute_reply":"2022-08-05T10:32:11.571947Z"}}
random_forest_en = rf(X_train,Y_train.values.ravel(), n_estimators=250)

# %% [code] {"execution":{"iopub.status.busy":"2022-08-05T10:32:11.574736Z","iopub.execute_input":"2022-08-05T10:32:11.575102Z","iopub.status.idle":"2022-08-05T10:32:12.096268Z","shell.execute_reply.started":"2022-08-05T10:32:11.575072Z","shell.execute_reply":"2022-08-05T10:32:12.094955Z"}}
print("TRAINING ACCURACY:", random_forest_en.score(X_train, Y_train))
print("VALIDATION ACCURACY", random_forest_en.score(X_test, Y_test))
