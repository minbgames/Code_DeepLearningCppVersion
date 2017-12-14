#include <iostream>
#include <cmath>

#define COUNT_SIZE 20001
#define DATA_COUNT 5
#define WEIGHT_COUNT 4

using namespace std;

float x_train[DATA_COUNT][WEIGHT_COUNT]={{73, 80, 75, 1},
                                         {93, 88, 93, 1},
                                         {89, 91, 90, 1},
                                         {96, 98, 100, 1},
                                         {73, 66, 70, 1}};

float y_train[DATA_COUNT][1]={{152},
                              {185},
                              {180},
                              {196},
                              {142}};

float W[WEIGHT_COUNT][1];
float cost=0;
float learning_rate = 0.00008;

float Cost_Make(void);
void Gradient_Descent(void);
void result_make(void);

int main(void){

    srand((unsigned int)time(NULL));

    for (int i = 0; i < WEIGHT_COUNT; ++i) {
        W[i][0]= (float)rand() / RAND_MAX;
    }

    for (int step = 0; step < COUNT_SIZE; step++)
    {
        Gradient_Descent();
        cost = Cost_Make();

        if(step % 20 == 0){
            cout << "[ cost = " << cost
                 << " ,W1 = " << W[0][0]
                 << " ,W2 = " << W[1][0]
                 << " ,W3 = " << W[2][0]
                 << " ,b = " << W[3][0]
                 << " ] " << endl;
        }
    }
    result_make();
}

float Cost_Make(void)
{
    float cost_ = 0;
    float hypothesis[DATA_COUNT];
    for (int i = 0; i < DATA_COUNT; i++) {
        hypothesis[i]=0;
        for (int j = 0; j < WEIGHT_COUNT; j++) {
            hypothesis[i] += x_train[i][j]*W[j][0];
        }
//        cout <<"hypothesis[i]: "<< hypothesis[i] <<endl;
//        cout <<"hypothesis[i]-y: "<< hypothesis[i]-y_train[i][0] << endl;
//        cout <<"hypothesis[i]-y square: "<< (float)pow(hypothesis[i]-y_train[i][0],2) << endl;
        cost_+=(float)pow(hypothesis[i]-y_train[i][0],2);
//        out << cost_ <<endl;
    }
    cost_= cost_ / (2*DATA_COUNT);
    return cost_;
}

void Gradient_Descent(void)
{
    float W_sum_[WEIGHT_COUNT]={0,0,0,0};
    float hypothesis[5];
    for (int i = 0; i < DATA_COUNT; i++) {
        hypothesis[i]=0;

        for (int j = 0; j < WEIGHT_COUNT; j++) {
            hypothesis[i] += x_train[i][j]*W[j][0];
        }
        for (int k = 0; k < WEIGHT_COUNT; k++) {
            W_sum_[k] += (hypothesis[i]-y_train[i][0])*x_train[i][k];
//            cout << "i : " << i << " k : "<< k << " : "<< W_sum_[k] << endl;
        }
    }

    for (int k = 0; k < WEIGHT_COUNT; k++) {
        W[k][0] -= learning_rate / DATA_COUNT * (W_sum_[k]);
    }
}

void result_make(void){
    float result_value[DATA_COUNT];
    for (int i = 0; i < DATA_COUNT; ++i) {
        result_value[i]=0;
        for (int j = 0; j < WEIGHT_COUNT; ++j) {
            result_value[i]+=x_train[i][j]*W[j][0];
        }
        cout << "y_value : " << y_train[i][0] << " result_value : " << result_value[i] <<endl;
    }
}