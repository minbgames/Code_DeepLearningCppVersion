
#include <iostream>
#include <cmath>

#define COUNT_SIZE 100001
#define DATA_COUNT 6
#define WEIGHT_COUNT 3

using namespace std;

float x_train[DATA_COUNT][WEIGHT_COUNT]={{1, 2, 1},
                                         {2, 3, 1},
                                         {3, 1, 1},
                                         {4, 3, 1},
                                         {5, 3, 1},
                                         {6, 2, 1}};

float y_train[DATA_COUNT][1]={{0},
                              {0},
                              {0},
                              {1},
                              {1},
                              {1}};

float W[WEIGHT_COUNT][1];
float cost=0;
float learning_rate = 0.01;

float Cost_Make(void);
float Hypothesis_Make(int _DataIndex);
float Sigmoid_Make(float _hypothesis);
float Sigmoid_Diff_Make(float _hypothesis);
float Cost_Diff_Make(float _sigmoid, int _DataIndex);
void Gradient_Descent(void);
void result_make(void);

int Weight_Value_Confirm=1;
int Cost_Variable_Value_Confirm=0;
int Gradient_Variable_Value_Confirm=0;

int main(void){

    srand((unsigned int)time(NULL));

    for (int i = 0; i < WEIGHT_COUNT; ++i) {
        W[i][0]= (float)rand() / RAND_MAX;
    }

    cost = Cost_Make();

    for (int step = 0; step < COUNT_SIZE; step++)
    {
        Gradient_Descent();
        cost = Cost_Make();

        if(Weight_Value_Confirm){
            cout << "[ cost = " << cost
                 << " ,W1 = " << W[0][0]
                 << " ,W2 = " << W[1][0]
                 << " ,b = " << W[2][0]
                 << " ] " << endl;
        }
    }
    result_make();
    //W1= 1.47028577 W2=0.3138389  W3(b):-5.54892206
}

float Hypothesis_Make(int _DataIndex)
{
    float hypothesis_ =0;
    for (int j = 0; j < WEIGHT_COUNT; j++) {
        hypothesis_ += x_train[_DataIndex][j] * W[j][0];
    }
    return hypothesis_;
}

float Sigmoid_Make(float _hypothesis)
{
    float sigmoid_=0;
    sigmoid_=1/(1+exp(-_hypothesis));
    return sigmoid_;
}

float Cost_Make(void)
{
    float cost_ = 0;
    float hypothesis[DATA_COUNT];
    float sigmoid[DATA_COUNT];
    for (int i = 0; i < DATA_COUNT; i++) {
        hypothesis[i]=0, sigmoid[i]=0;

        hypothesis[i]=Hypothesis_Make(i);
        sigmoid[i]=Sigmoid_Make(hypothesis[i]);

        if(Cost_Variable_Value_Confirm) {
            cout << "data_" << i << " : H=" << hypothesis[i] << " S=" << sigmoid[i] << " y=" << y_train[i][0] << endl;
            cout << "cost_" << i << "=" << y_train[i][0] * log(sigmoid[i]) + (1 - y_train[i][0]) * log(1 - sigmoid[i]) << endl;
        }
        cost_+=y_train[i][0]*log(sigmoid[i])+(1-y_train[i][0])*log(1-sigmoid[i]);
    }
    cost_= -cost_ / DATA_COUNT;
    if(Cost_Variable_Value_Confirm) {
        cout << "---------total_cost_make=" << cost_ << "------------" << endl;
    }
    return cost_;
}

float Cost_Diff_Make(float _sigmoid, int _DataIndex)
{
    return (_sigmoid-y_train[_DataIndex][0])/((_sigmoid-1)*_sigmoid);
}

float Sigmoid_Diff_Make(float _hypothesis)
{
    return exp(_hypothesis)/(float)(pow((exp(_hypothesis)+1),2));
}

void Gradient_Descent(void)
{
    float W_sum_[WEIGHT_COUNT];
    float hypothesis[DATA_COUNT];
    float sigmoid[DATA_COUNT];
    float Mean_W_sum_[WEIGHT_COUNT];

    for (int i = 0; i < WEIGHT_COUNT; i++) {
        W_sum_[i]=0;
    }
    for (int i = 0; i < DATA_COUNT; i++) {
        hypothesis[i]=Hypothesis_Make(i);
        sigmoid[i]=Sigmoid_Make(hypothesis[i]);

        if(Gradient_Variable_Value_Confirm) {
            cout << "data_" << i << " : H=" << hypothesis[i] << " S=" << sigmoid[i] << " y=" << y_train[i][0] << endl;
            cout << "cost_" << i << "=" << y_train[i][0] * log(sigmoid[i]) + (1 - y_train[i][0]) * log(1 - sigmoid[i]) << endl;
        }
        for (int k = 0; k < WEIGHT_COUNT; k++) {
            W_sum_[k] += Cost_Diff_Make(sigmoid[i], i) * Sigmoid_Diff_Make(hypothesis[i]) * x_train[i][k];
            if (Gradient_Variable_Value_Confirm) {
                cout << "Cost_Diff=" << Cost_Diff_Make(sigmoid[i], i)
                     << " Hypo_Diff=" << Sigmoid_Diff_Make(hypothesis[i])
                     << " x_train=" << x_train[i][k]
                     << " W_sum[" << k << "]="
                     << Cost_Diff_Make(sigmoid[i], i) * Sigmoid_Diff_Make(hypothesis[i]) * x_train[i][k] << endl;
                cout << "Total_W_sum_[" << k << "]=" << W_sum_[k] << endl;
            }
        }
    }
    for (int k = 0; k < WEIGHT_COUNT; k++) {
        Mean_W_sum_[k]=-W_sum_[k]/ DATA_COUNT;
        if(Gradient_Variable_Value_Confirm) {
            cout << " Mean_k = " << k << " : " << Mean_W_sum_[k] << endl;
        }
    }

    for (int k = 0; k < WEIGHT_COUNT; k++) {
        W[k][0] -= learning_rate * (Mean_W_sum_[k]);
    }
}

void result_make(void){
    float result_value[DATA_COUNT];
    for (int i = 0; i < DATA_COUNT; ++i) {
        result_value[i]=Sigmoid_Make(Hypothesis_Make(i));
        cout << "y_value : " << y_train[i][0] << " result_value : " << result_value[i] <<endl;
    }
}