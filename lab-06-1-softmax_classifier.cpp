
#include <iostream>
#include <cmath>

#define COUNT_SIZE 1000001
#define DATA_COUNT 8
#define WEIGHT_COUNT 5
#define OBJECT_COUNT 3

using namespace std;

float x_train[DATA_COUNT][WEIGHT_COUNT]={{1, 2, 1, 1, 1},
                                         {2, 1, 3, 2, 1},
                                         {3, 1, 3, 4, 1},
                                         {4, 1, 5, 5, 1},
                                         {1, 7, 5, 5, 1},
                                         {1, 2, 5, 6, 1},
                                         {1, 6, 6, 6, 1},
                                         {1, 7, 7, 7, 1}};

float y_train[DATA_COUNT][OBJECT_COUNT]={{0, 0, 1},
                                         {0, 0, 1},
                                         {0, 0, 1},
                                         {0, 1, 0},
                                         {0, 1, 0},
                                         {0, 1, 0},
                                         {1, 0, 0},
                                         {1, 0, 0}};

float W[OBJECT_COUNT][WEIGHT_COUNT];
float cost=0;
float learning_rate = 0.01;

float Cost_Make(void);
float Hypothesis_Make(int _DataIndex, int _ObjectIndex);
float Cross_Make(float _softmax,int _DataIndex, int _ObjectIndex);

void Gradient_Descent(void);
void result_make(void);

int Weight_Value_Confirm=1;
int Cost_Variable_Value_Confirm=0;
int Gradient_Variable_Value_Confirm=0;

int main(void){

    srand((unsigned int)time(NULL));


    for (int j = 0; j < OBJECT_COUNT; ++j) {
        for (int k = 0; k < WEIGHT_COUNT; ++k) {
            W[j][k]= (float)rand() / RAND_MAX;
        }
    }

    cost = Cost_Make();

    for (int step = 0; step < COUNT_SIZE; step++)
    {
        Gradient_Descent();
        cost = Cost_Make();
        if(step % 20 == 0) cout << "[ step : " << step <<" | cost = " << cost << " ] " << endl;
    }

    if(Weight_Value_Confirm){
        cout << endl;
        cout << "-----------------------------Weight Check--------------------------" <<endl<<endl;
        cout << " [ final_cost = " << cost << " ] " << endl <<endl;
        for (int j = 0; j < OBJECT_COUNT; ++j) {
            for (int k = 0; k < WEIGHT_COUNT; ++k) {
                cout << "  W[" <<j<<"]["<<k<< "] = " << W[j][k];
            }
            cout << endl << endl;
        }
    }
    result_make();

//    -8.8809166 -1.48664141 10.02068901 -4.00904417 -7.6252656
//    2.12684965 0.18414932  -3.57795453  4.99769211 -4.12105989
//    7.01780748 2.20236111  -8.49456406  2.15526128  9.14280415

}

float Hypothesis_Make(int _DataIndex, int _ObjectIndex)
{
    float hypothesis_ =0;
    for (int k = 0; k < WEIGHT_COUNT; k++) {
        hypothesis_ += x_train[_DataIndex][k] * W[_ObjectIndex][k];
    }
    return hypothesis_;
}

float Cross_Make(float _softmax, int _DataIndex, int _ObjectIndex)
{
    return -y_train[_DataIndex][_ObjectIndex]*log(_softmax);
}

float Cost_Make(void)
{
    float cost_ = 0;
    float hypothesis[OBJECT_COUNT];
    float softmax[OBJECT_COUNT];
    float index_cost[DATA_COUNT];
    float softmax_sum;
    for (int i = 0; i < DATA_COUNT; i++) {
        index_cost[i]=0;
        softmax_sum=0;
        for (int j = 0; j < OBJECT_COUNT; j++) {
            hypothesis[j]=Hypothesis_Make(i,j);
            softmax_sum+=exp(hypothesis[j]);
        }
        for (int j = 0; j < OBJECT_COUNT; j++) {
            softmax[j]=exp(hypothesis[j])/softmax_sum;
            index_cost[i]+=Cross_Make(softmax[j],i,j);
        }
        cost_+=index_cost[i];
    }
    cost_= cost_ / DATA_COUNT;
    return cost_;
}


void Gradient_Descent(void)
{
    float hypothesis[OBJECT_COUNT];
    float softmax[OBJECT_COUNT];
    float index_cost[DATA_COUNT];
    float softmax_sum;
    float W_sum_[OBJECT_COUNT][WEIGHT_COUNT];
    float Mean_W_sum_[OBJECT_COUNT][WEIGHT_COUNT];

    for (int j = 0; j < OBJECT_COUNT; j++) {
        for (int k = 0; k < WEIGHT_COUNT; k++) {
            W_sum_[j][k]=0;
        }
    }
    for (int i = 0; i < DATA_COUNT; i++) {
        index_cost[i] = 0;
        softmax_sum=0;
        for (int j = 0; j < OBJECT_COUNT; j++) {
            hypothesis[j] = Hypothesis_Make(i, j);
            softmax_sum += exp(hypothesis[j]);
        }
        for (int j = 0; j < OBJECT_COUNT; j++) {
            softmax[j] = exp(hypothesis[j]) / softmax_sum;
            for (int k = 0; k < WEIGHT_COUNT; k++) {
                W_sum_[j][k] += (softmax[j]-y_train[i][j])*x_train[i][k];
            }
        }
    }

    for (int j = 0; j < OBJECT_COUNT; j++) {
        for (int k = 0; k < WEIGHT_COUNT; k++) {
            Mean_W_sum_[j][k] = W_sum_[j][k] / DATA_COUNT;
        }
    }

    for (int j = 0; j < OBJECT_COUNT; j++) {
        for (int k = 0; k < WEIGHT_COUNT; k++) {
            W[j][k] -= learning_rate * (Mean_W_sum_[j][k]);
        }
    }
}

void result_make(void){
    float result_value[DATA_COUNT];
    float hypothesis[OBJECT_COUNT];
    float softmax[OBJECT_COUNT];
    float softmax_sum;
    cout<< "-----------------------------Result Check---------------------------" <<endl << endl;
    for (int i = 0; i < DATA_COUNT; ++i) {
        cout<< "data_index = " << i;
        softmax_sum=0;
        for (int j = 0; j < OBJECT_COUNT; j++) {
            hypothesis[j]=Hypothesis_Make(i,j);
            softmax_sum+=exp(hypothesis[j]);
            cout << " h : " << hypothesis[j] << " exp(h) : " << exp(hypothesis[j]) << " ";
        }
        cout << " [ ";
        for (int j = 0; j < OBJECT_COUNT; j++) {
            softmax[j]=exp(hypothesis[j])/softmax_sum;
            cout << softmax[j] <<" ";
        }
        cout <<"]"<< endl;
    }

}