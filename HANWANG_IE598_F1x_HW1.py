#Our first machine learning model
#Garreta and Moncecchi pp 10-20
#uses Iris database and SGD classifier
import sklearn
print( 'The scikit learn version is {}.'.format(sklearn.__version__))
# The scikit learn version is 0.21.3.

import pandas as pd
from sklearn import datasets

iris = datasets.load_iris()
X_iris, y_iris = iris.data, iris.target
# gain the size of data and target
print( X_iris.shape, y_iris.shape)
# (150, 4) (150,)
# print the 1st
print( X_iris[0], y_iris[0])
# [5.1 3.5 1.4 0.2] 0
'-----------------------------------------------------------------'
# sklearn.cross_validation has been revised to sklearn.model_selection in this version
from sklearn.model_selection import train_test_split
from sklearn import preprocessing
# Get dataset with only the first two attributes
#  for the data part, we need all of the data and the first two attributes
X, y = X_iris[:, :2], y_iris
# Split the dataset into a training and a testing set
# Test set will be the 25% taken randomly,and the random seed is 33 to ensure each time pick the same position
X_train, X_test, y_train, y_test = train_test_split(X, y,test_size=0.25, random_state=33)
# thus the train set size is expect to be 75% of 150  -> 112
print( X_train.shape, y_train.shape)
# (112, 2) (112,)
# Standardize the features
scaler = preprocessing.StandardScaler().fit(X_train)
X_train = scaler.transform(X_train)
X_test = scaler.transform(X_test)
'-----------------------------------------------------------------'
import matplotlib.pyplot as plt
colors = ['red', 'greenyellow', 'blue']
#it doesnt like "xrange" changed to "range"
# explore the relationship between two attribute, in this case, the sepal length and width
# y_train -> put different sorts of flowers into different colors
# we can also use data of petal to plot a new pic
for i in range(len(colors)):
    xs = X_train[:, 0][y_train == i]
    ys = X_train[:, 1][y_train == i]
    plt.scatter(xs, ys, c=colors[i])
plt.legend(iris.target_names)
plt.xlabel('Sepal length')
plt.ylabel('Sepal width')
plt.show()
'-----------------------------------------------------------------'
#found a typo here... incorrect from book followed by corrected code
#from sklearn.linear_modelsklearn._model import SGDClassifier
# SGD: Stochastic Gradient Descent
# collection of gradient descent -> SVM,logistic regression
from sklearn.linear_model import SGDClassifier
# initiate the model first
clf = SGDClassifier()
# then fit
clf.fit(X_train, y_train)
print( clf.coef_)
# [[-30.24297039  13.53386274]
#  [ -2.36655455 -18.84384354]
#  [  6.75851833  -1.55927105]]
#[-18.82275713  -3.73355601  -8.55775805]
'-----------------------------------------------------------------'
import numpy as np
x_min, x_max = X_train[:, 0].min() - .5, X_train[:, 0].max() + .5
y_min, y_max = X_train[:, 1].min() - .5, X_train[:, 1].max() + .5
Xs = np.arange(x_min, x_max, 0.5)
fig, axes = plt.subplots(1, 3)
fig.set_size_inches(10, 6)
for i in [0, 1, 2]:
    axes[i].set_aspect('equal')
    axes[i].set_title('Class '+ str(i) + ' versus the rest')
    axes[i].set_xlabel('Sepal length')
    axes[i].set_ylabel('Sepal width')
    axes[i].set_xlim(x_min, x_max)
    axes[i].set_ylim(y_min, y_max)
    # select certain curve to plot them into one pic
    plt.sca(axes[i])
    # figure out the division line and the name of get_cmap can ignore the pattern name
    plt.scatter(X_train[:, 0], X_train[:, 1], c=y_train, cmap=plt.cm.prism)
    # get_cmap('plasma')
    # draw the line
    ys = (-clf.intercept_[i] - Xs * clf.coef_[i, 0]) / clf.coef_[i, 1]
    # hold default to be True
    plt.plot(Xs, ys)
plt.show()
# Perform classification on samples in X.
print( clf.predict(scaler.transform([[4.7, 3.1]])) )
#[0]
# Evaluates the decision function for the samples in X.
print( clf.decision_function(scaler.transform([[4.7, 3.1]])) )
#[[ 20.41175136  -2.34494756 -17.20186077]]
'-----------------------------------------------------------------'
# model evaluation
from sklearn import metrics
# create a new object to copy the train set for prediction = clf.predict(X_train)
y_train_pred = clf.predict(X_train)
print( metrics.accuracy_score(y_train, y_train_pred) )
# 0.8035714285714286
# now it is the time for test set
y_pred = clf.predict(X_test)
# Accuracy classification score.
print( metrics.accuracy_score(y_test, y_pred) )
# 0.7368421052631579
# Build a text report showing the main classification metrics
print( metrics.classification_report(y_test, y_pred, target_names=iris.target_names) )
# precision    recall  f1-score   support
#
#       setosa       1.00      1.00      1.00         8
#   versicolor       0.53      0.73      0.62        11
#    virginica       0.80      0.63      0.71        19
#
#     accuracy                           0.74        38
#    macro avg       0.78      0.79      0.77        38
# weighted avg       0.76      0.74      0.74        38

# Compute confusion matrix to evaluate the accuracy of a classification
print( metrics.confusion_matrix(y_test, y_pred) )
# [[ 8  0  0]
#  [ 0  8  3]
#  [ 0  7 12]]

# df = pd.read_csv('C:/Users/wangh/Desktop/MSFE/machine_learning/HW1/iris.data',header = None)
# print(df.tail())
# since the iris data has been installed into the dataset of sklearn, we have no need to import it again.

print("My name is Han Wang")
print("My NetID is: 'hanw8'")
print("I hereby certify that I have read the University policy on Academic Integrity and that I am not in violation.")