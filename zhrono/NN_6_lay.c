#include "nn.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void print(int m, int n, const float *x){
    int i, j;
    for (i = 0; i < m; i++){
        for (j = 0; j < n; j++){
            printf("%.4f ", x[i * n + j]);
        }
    printf("\n");
    }
}

void fc(int m, int n, const float *x, const float *A, const float *b, float *y){
    int i, j;
    for (i = 0; i < m; i++){
        y[i] = b[i];
        for (j = 0; j < n; j++){
            y[i] = y[i] + A[i * n + j] * x[j];
        }
    }

}

void relu(int n, const float * x, float * y) {
    for (int i = 0; i < n;i++){
        if(x[i] > 0){
            y[i] = x[i];
        }else{
            y[i] = 0;
        }
    }
}

void softmax(int n, const float * x, float * y) {
    float xmax = x[0];
    for (int i = 0; i < n;i++){
        if(xmax<x[i]){
            xmax = x[i];
        }
    }
    float expsum = 0;
    for (int i = 0; i < n;i++){
        expsum = expsum + expf(x[i] - xmax);
    }
    for (int i = 0; i < n;i++){
        y[i] = expf(x[i]-xmax)/expsum;
    }
}

int inference3(const float * A, const float * b,
 const float * x,float *y) {
    int m = 10;
    int n = 784;
    fc(m, n, x, A, b, y);
    relu(m, y, y);
    softmax(m, y, y);
    float ymax = y[0]; 
    int p = 0;    
    int i;
    for (i = 0; i < m; i++){
        if (y[i] > ymax){
            ymax = y[i];
            p = i;
        }
    }
return p;
}

int inference6(const float *A1,const float *A2,const float *A3, const float *b1,  const float *b2, const float *b3, const float *x,float * y){
    float * y1 = malloc(sizeof(float) * 50);
    float * y2 = malloc(sizeof(float) * 100);
    fc(50, 784, x, A1, b1, y1);
    relu(50, y1, y1);
    fc(100, 50, y1, A2, b2, y2);
    relu(100, y2, y2);
    fc(10, 100, y2, A3, b3, y);
    softmax(10, y, y);
    float ymax = y[0]; //yの要素の最大のもの
    int y_index = 0;    //yの要素が最大の時の添字
    int i;
    for (i = 0; i < 10; i++){
        if (y[i] > ymax){
            ymax = y[i];
            y_index = i;
        }
    }
    free(y1);
    free(y2);
    return y_index;
}

void softmaxwithloss_bwd(int n, const float * y, unsigned char t, float * dEdx){
     float a[10] = {0};
    for (int i = 0; i < n; i++){
        if (i == t){
            a[i] = 1;
        }
    }
    for(int i = 0;i<n;i++){
        dEdx[i]= y[i] - a[i];
    }
}

void relu_bwd(int n, const float * x, const float * dEdy, float * dEdx){
    for (int i = 0; i < n; i++){
        if (x[i] > 0){
            dEdx[i] = dEdy[i];
        }
        else{
            dEdx[i] = 0;
        }
    }
}
void fc_bwd(int m, int n, const float *x, const float *dEdy, const float *A, float *dEdA, float *dEdb, float *dEdx){
   for (int i = 0; i < m; i++){
       for (int j = 0; j < n; j++){
           dEdA[i * n + j] = dEdy[i] * x[j];
       }
   }
   for (int i = 0; i < m; i++){
       dEdb[i] = dEdy[i];
   }
   for (int i = 0; i < n; i++){
       dEdx[i] = 0;
       for (int j = 0; j < m; j++){
           dEdx[i] += A[j * m + i] * dEdy[j];
       }
   }
}


void copy(int m, int n, const float *x, float *y){
    for (int i=0; i < m; i++){
        for (int j=0; j < n; j++){
            y[i*n+j] = x[i*n+j];
        }
    }
}

void backward3(const float * A, const float * b, const float * x, unsigned char t,
float * y, float * dEdA, float * dEdb) {
     int m = 10;
    int n = 784;
    float before_fc[784];
    float before_relu[10];
    float y1[10];
    float y0[784];
        //順伝播
    copy(1, n, x, before_fc);
    fc(m, n, x, A, b, y);
    copy(1, m, y, before_relu);
    relu(m, y, y);
    softmax(m, y, y);
    //逆伝播
    softmaxwithloss_bwd(m, y, t, y1);
    relu_bwd(m, before_relu, y1, y1);
    fc_bwd(m, n, before_fc, y1, A, dEdA, dEdb, y0);
}

void backward6(const float *A1,const float *A2,const float *A3,
 const float *b1,  const float *b2, const float *b3, const float *x, unsigned char t, float *y,
    float *dEdA1,float *dEdA2,float *dEdA3, float *dEdb1,float *dEdb2,float *dEdb3){
    float  * before_fc1 = malloc(sizeof(float) * 784);
    float  * before_fc2 = malloc(sizeof(float) * 50);
    float  * before_fc3 = malloc(sizeof(float) * 100);
    float  * before_relu1 = malloc(sizeof(float) * 50);
    float  * before_relu2 = malloc(sizeof(float) * 100);
    float * y0 = malloc(sizeof(float) * 784);
    float * y1 = malloc(sizeof(float) * 50);
    float * y2 = malloc(sizeof(float) * 100);
    float *y3 = malloc(sizeof(float) * 10);
    copy(1,784,x,before_fc1);
    fc(50, 784, x, A1, b1, before_relu1);
    relu(50, before_relu1, before_fc2);
    fc(100, 50, before_fc2, A2, b2, before_relu2);
    relu(100, before_relu2, before_fc3);
    fc(10, 100, before_fc3, A3, b3, y);
    softmax(10, y, y);

    softmaxwithloss_bwd(10, y, t, y3);
    fc_bwd(10, 100, before_fc3, y3, A3, dEdA3, dEdb3, y2);
    relu_bwd(100, before_relu2, y2, y2);
    fc_bwd(100, 50, before_fc2, y2, A2, dEdA2, dEdb2, y1);
    relu_bwd(50, before_relu1, y1, y1);
    fc_bwd(50, 784, before_fc1, y1, A1, dEdA1, dEdb1, y0);
    free(y0);
    free(y1);
    free(y2);
    free(y3);
    free(before_fc1);
    free(before_fc2);
    free(before_fc3);
    free(before_relu1);
    free(before_relu2);
}

void shuffle(int n, int *x){
    for (int i = 0; i < n; i++){
        int j = (int)(rand()*(  n+1.0)/(1.0+RAND_MAX));
        int tmp_xi = x[i];
        x[i] = x[j];
        x[j] = tmp_xi;
    }
}

void add(int n, const float * x,float * o) {
      for (int i = 0; i < n;i++){
          o[i] = o[i] + x[i];
      }
}

void scale(int n, float x, float *o) {
    for (int i = 0; i < n;i++){
          o[i] = o[i] * x;
      }
}

void init(int n, float x, float *o) {
    for (int i = 0; i < n;i++){
          o[i] =  x;
      }
}

void rand_init(int n, float *o){
    int i;
    for (i = 0; i < n; i++){
        o[i] = ((float)rand() / ((float)RAND_MAX + 1)) * 2 - 1 ;
    }
}

float cross_entropy_error(const float * y, int t){
    return -1*log(y[t] + 1e-7);
}


void save(const char *filename, int m, int n, const float *A, const float *b) {
    int i;
    FILE *fp;
    fp = fopen(filename, "w");
    for (i = 0; i < m * n; i++){
        fprintf(fp, "%.4f ", A[i]);
        if(i % n == n - 1){
            fprintf(fp, "\n");
        }
    }
    fprintf(fp, "\n");
    for (i = 0; i < m; i++){
        fprintf(fp, "%.4f\n", b[i]);
    }
    fclose(fp);
}

void NN_6layers(int train_count,int test_count,float * train_x,unsigned char * train_y,float * test_x, unsigned char * test_y, char *argv[]);

int main(int argc,char *argv[]){
    float * train_x = NULL;
    unsigned char * train_y = NULL;
    int train_count = -1;
    float * test_x = NULL;
    unsigned char * test_y = NULL;
    int test_count = -1;
    int width = -1;
    int height = -1;
    load_mnist(&train_x, &train_y, &train_count,
    &test_x, &test_y, &test_count,
    &width, &height);
// これ以降，３層 NN の係数 A_784x10 および b_784x10 と，
// 訓練データ train_x + 784*i (i=0,...,train_count-1), train_y[0]～train_y[train_count-1],
// テストデータ test_x + 784*i (i=0,...,test_count-1), test_y[0]～test_y[test_count-1],
// を使用することができる．
    srand(time(NULL));
    NN_6layers(train_count,test_count,train_x,train_y,test_x,test_y,argv);
    
    return 0;
}

void NN_6layers(int train_count,int test_count,float * train_x,unsigned char * train_y,
float * test_x, unsigned char * test_y, char *argv[]){
    /* エポック数、バッチサイズ、学習率の宣言等*/
    int epo = 10;
    int batch_length = 100;
    float learning_rate = 0.05; 
    
    /*勾配をそれぞれ宣言 */
    float *dEdwA1 = malloc(sizeof(float)*784*50);
    float *dEdwA2 = malloc(sizeof(float)*50*100);
    float *dEdwA3 = malloc(sizeof(float)*100*10);
    float *dEdwb1 = malloc(sizeof(float)*50);
    float *dEdwb2 = malloc(sizeof(float)*100);
    float *dEdwb3 = malloc(sizeof(float)*10);
    /*勾配の平均をそれぞれ宣言 */
    float *Av_dEdwA1 = malloc(sizeof(float)*784*50);
    float *Av_dEdwA2 = malloc(sizeof(float)*50*100);
    float *Av_dEdwA3 = malloc(sizeof(float)*100*10);
    float *Av_dEdwb1 = malloc(sizeof(float)*50);
    float *Av_dEdwb2 = malloc(sizeof(float)*100);
    float *Av_dEdwb3 = malloc(sizeof(float)*10);

        /* 重みwAとwbをそれぞれ宣言*/
    float *wA1 = malloc(sizeof(float)*784*50);
    float *wA2 = malloc(sizeof(float)*50*100);
    float *wA3 = malloc(sizeof(float)*100*10);
    float *wb1 = malloc(sizeof(float)*50);
    float *wb2 = malloc(sizeof(float)*100);
    float *wb3 = malloc(sizeof(float)*10);
    float *y = malloc(sizeof(float)*10);

    int *index = malloc(sizeof(int)*train_count);
    for(int i = 0;i<train_count;i++){
        index[i] = i;
    }

    //初期化
    rand_init(784*50,wA1);
    rand_init(50*100,wA2);
    rand_init(100*10,wA3);
    init(50,0,wb1);
    init(100,0,wb2);
    init(10,0,wb3);

    /*エポックをepo回実行する */
    for(int i=0;i<epo;i++){
        shuffle(train_count,index);
        printf("||||||||||||||||||||||epoch:%d||||||||||||||||||||||\n",i+1);
        /*ミニバッチ学習を規定回数行う */
        
        for(int j = 0;j<train_count/batch_length;j++){
            init(784*50,0,Av_dEdwA1);
            init(50*100,0,Av_dEdwA2);
            init(100*10,0,Av_dEdwA3);
            init(50,0,Av_dEdwb1);
            init(100,0,Av_dEdwb2);
            init(10,0,Av_dEdwb3);

            /*勾配を求める */
            for(int k=0;k<batch_length;k++){
                backward6(wA1,wA2,wA3,wb1,wb2,wb3,train_x+784*index[j*batch_length+k],train_y[index[j*batch_length+k]],y, dEdwA1, dEdwA2, dEdwA3, dEdwb1, dEdwb2, dEdwb3);
                add(784*50,dEdwA1,Av_dEdwA1);
                add(50*100,dEdwA2,Av_dEdwA2);
                add(100*10,dEdwA3,Av_dEdwA3);
                add(50,dEdwb1,Av_dEdwb1);
                add(100,dEdwb2,Av_dEdwb2);
                add(10,dEdwb3,Av_dEdwb3);
            }
            /*ミニバッチで割って、それぞれの平均を算出 */
            scale(784*50,-learning_rate/(float)batch_length,Av_dEdwA1);
            scale(50*100,-learning_rate/(float)batch_length,Av_dEdwA2);
            scale(100*10,-learning_rate/(float)batch_length,Av_dEdwA3);
            scale(50,-learning_rate/(float)batch_length,Av_dEdwb1);
            scale(100,-learning_rate/(float)batch_length,Av_dEdwb2);
            scale(10,-learning_rate/(float)batch_length,Av_dEdwb3);
            
            /*重みを変更*/
            add(784*50,Av_dEdwA1,wA1);
            add(50*100,Av_dEdwA2,wA2);
            add(100*10,Av_dEdwA3,wA3);
            add(50,Av_dEdwb1,wb1);
            add(100,Av_dEdwb2,wb2);
            add(10,Av_dEdwb3,wb3);
            printf("%.2f%% \r",(float)j * 100/(train_count/batch_length));
        }
        //訓練データでの推論を行う
        int  count = 0;
        float loss_count = 0;
        for(int q =0;q<train_count;q++){
            if(inference6(wA1,wA2,wA3,wb1,wb2,wb3,train_x+q*784,y) == train_y[q]){
                count++;
            }
            loss_count = loss_count + cross_entropy_error(y,train_y[q]);
        }
        /*テストデータでの推論を行う */
        int  t_count = 0;
        float t_loss_count = 0;
        for(int m =0;m<test_count;m++){
            if(inference6(wA1,wA2,wA3,wb1,wb2,wb3,test_x+m*784,y) == test_y[m]){
                t_count++;
            }
            t_loss_count = t_loss_count + cross_entropy_error(y,test_y[m]);
        }

        float right = 0.0;
        float t_right = 0.0;
        right = (float)count*100/(float)train_count;
        t_right = (float)t_count*100/(float)test_count;
        
        printf("train_Ac: %f%%\n",right);
        printf("loss: %f%%\n",loss_count/train_count);
        printf("test_Ac: %f%%\n",t_right);
        printf("loss: %f%%\n",t_loss_count/test_count);
    }

    /*パラメーターの保存 */
    save(argv[1],50,784,wA1,wb1);
    save(argv[2],100,50,wA2,wb2);
    save(argv[3],10,100,wA3,wb3);
}