#include <stdio.h>
#include <stdlib.h>
 
#define M 3    
#define N 3        // 输入的矩阵规模
#if (M>N)      // 取M、N中的较大数
    #define MN M
#else
    #define MN N
#endif
 
double **dmatrix(int, int, int, int);
double *dvector(int, int);
void svdcmp(double **, int, int, double *, double **);

void print_r(double **a, int m, int n) {
    int i, j;
    for (i = 1; i <= m; i++) {
        for (j = 1; j <= n; j++) {
            printf("%le ", a[i][j]);
        }
        printf("\n");
    }
}
 
int main()
{
    /*
     * 使用 ** 来声明，然后用dmatrix来申请空间
     * 这样在函数引用矩阵时，就不用声明矩阵大小了
     */
    double **a;
    double *w;
    double **u,**v;
    int i,j,k;
    double t;
    double t1[MN],t2[MN];
 
    /* 矩阵均以M,N中的最大值来申请空间，避免越界 */
    a = dmatrix(1, MN, 1, MN);
    u = dmatrix(1, MN, 1, MN);
    w = dvector(1, MN);
    v = dmatrix(1, MN, 1, MN);
#if 0
    a[1][1] = 3.0;
    a[1][2] = 2.0;
    a[1][3] = 1.0;
    a[2][1] = 1.0;
    a[2][2] = 3.0;
    a[2][3] = 2.0;
    a[3][1] = 1.0;
    a[3][2] = 2.0;
    a[3][3] = 3.0;
 
 
    /* 备选验证数据 */
    // a[1][1] = 1.0;
    // a[1][2] = 2.0;
    // a[1][3] = 3.0;
    // a[2][1] = 4.0;
    // a[2][2] = 5.0;
    // a[2][3] = 6.0;
    // a[3][1] = 7.0;
    // a[3][2] = 8.0;
    // a[3][3] = 9.0;
#else
    // 83.000000  52.000000  66.000000  
    // 52.000000  56.000000  44.000000  
    // 66.000000  44.000000  68.000000   
    // 14.387495
    a[1][1] = 83.0;
    a[1][2] = 52.0;
    a[1][3] = 66.0;
    a[2][1] = 52.0;
    a[2][2] = 56.0;
    a[2][3] = 44.0;
    a[3][1] = 66.0;
    a[3][2] = 44.0;
    a[3][3] = 68.0;
#endif
 
    printf("=== a ===\n");
    print_r(a, M, N);
 
    /* 
     * 执行svdcmp后，结果U会存储在传入的矩阵a中，
     * 所以先复制矩阵a存入u中，然后在svdcmp中传入u，
     * 这样输出就保存在u中，矩阵a也不会变了
     */
    for (i = 1; i <= M; i++) {
        for (j = 1; j <= N; j++)
            u[i][j] = a[i][j];
    }
 
    // svdcmp(u, M, N, w, v);
    /* 
     * 这边理应传入的是上面的参数
     * 但当 M>N时，结果不正确，U最右边的几列会全为0
     * 应该是Householder那边计算的问题，因为Householder外循环参数为N？
     *
     * 使用下面这个参数，经过验证可以得到正确的结果...
     *
     * 矩阵初始化时，元素默认赋值0，那就是说，0元素不影响Housesholder计算？后续的迭代也不影响？
     * 比如 2X2矩阵A[1,2; 2,3] 计算结果是2x2矩阵U
     * 那把矩阵改成3X3矩阵A[1,2,0; 2,3,0; 0,0,0]，即多出来的元素用0填充
     * 然后经householder计算和迭代计算后，结果U虽然是3X3矩阵，但我们还是只取2X2矩阵，两者结果是一样的？
     *
     * 用Matlab验证了下，还真的是一样的... 0元素不影响计算结果
     * 改成3x3矩阵后，U的第三列是有值的，但可以忽略掉，取前面的2x2矩阵，这样结果是一致的。
     */
    svdcmp(u, MN, MN, w, v);
 
 
    /* Sort the singular values in descending order */
    for (i = 1; i <= N; i++) {
        for (j = i+1; j <= N; j++) {
            if (w[i] < w[j]) { /* 对特异值排序 */
                t = w[i];
                w[i] = w[j];
                w[j] = t;
                /* 同时也要把矩阵U,V的列位置交换 */
                /* 矩阵U */
                for (k = 1; k <= M; k++) {
                    t1[k] = u[k][i];
                }
                for (k = 1; k <= M; k++) {
                    u[k][i] = u[k][j];
                }
                for (k = 1; k <= M; k++) {
                    u[k][j] = t1[k];
                }
 
                /* 矩阵V */
                for (k = 1; k <= N; k++) {
                    t2[k] = v[k][i];
                }
                for (k = 1; k <= N; k++) {
                    v[k][i] = v[k][j];
                }
                for (k = 1; k <= N; k++) {
                    v[k][j] = t2[k];
                }
            }
        }
    }
 
    /* U为MxM矩阵 */
    printf("=== U ===\n");
    print_r(u, M, M);
 
    /* 奇异值有M个，存为W矩阵，后面会用到 */
    double **W;
    W = dmatrix(1, MN, 1, MN);
    printf("=== W ===\n");
    for (i = 1; i<= M; i++) {
        for (j =1; j <= N; j++) {
            if (i==j) {
                W[i][j] = w[i];
            } else {
                W[i][j] = 0.0;
            }
        }
    }
    print_r(W, M, N);
 
    /* V为NxN矩阵 */
    printf("=== V ===\n");
    print_r(v, N, N);
 
    /* 验证结果，即计算U*W*V’看是否等于a */
    printf("=== U*W*V' ===\n");
    double **temp;
    double sum;
    temp = dmatrix(1, MN, 1, MN);
    /* 先算 U*W */
    for(i = 1; i <= M; i++){
        for(j = 1; j <= M; j++){
            sum = 0;
            for(k = 1; k <= N; k++){
                sum += u[i][k] * W[k][j];
            }
            temp[i][j] = sum;
        }
    }
    /* 再算 temp*V */
    /* 先对v进行矩阵转置，存为V */
    double ** V;
    V = dmatrix(1, MN, 1, MN);
    for(i = 1; i <= N; i++) {
        for(j = 1; j <= N; j++) {
            V[i][j] = v[j][i];
        }
    }
    for(i = 1; i <= M; i++){
        for(j = 1; j <= N; j++){
            sum = 0;
            for(k = 1; k <= N; k++){
                sum += temp[i][k] * V[k][j];
            }
            printf("%le ", sum);
        }
        printf("\n");
    }
 
 
 
    for (i = 1; i <= N; i++) {
        printf("Sigular value %d = %le\n",i,w[i]);
        printf("        vector   = %le %le %le\n",u[1][i],u[2][i],u[3][i]);
    }
 
 
    system("pause");
    return 0;
}
