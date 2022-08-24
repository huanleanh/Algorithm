#include <bits/stdc++.h>
#include <vector>
#include <iostream>
using namespace std;

int best = 0;
vector <pair <int, int> > ans;

void dequy(
    int edge, int a[10][10], int be, int row, 
    int column, vector <pair <int, int> > tmp_ans)
{
    // nếu giá trị ô hiện tại = 0 (đã bị loại bỏ) thì khỏi đệ quy thêm.
    if (a[row][column] == 0) {
        if(be> best){
            best = be;
            ans = tmp_ans;
        }
        return;
    }

    int right=0, index[100] = {0}, ir = 0;
    pair<int, int> arr[100];
    arr[ir].first = row;
    arr[ir].second = column;
    index[row*10+column]++; //đánh dấu đã duyệt

    while (ir<=right){ // duyệt các ô liên kề để tìm mảng cùng màu
        // trên
            if(arr[ir].first+1 < edge 
            && a[arr[ir].first+1][arr[ir].second] == a[arr[ir].first][arr[ir].second] 
            && index[(arr[ir].first+1)*10+arr[ir].second] == 0){
                index[(arr[ir].first+1)*10+arr[ir].second]++; //đánh dấu đã duyệt
                right++;
                arr[right].first = arr[ir].first+1;
                arr[right].second = arr[ir].second;
            }
        // dưới
            if(arr[ir].first-1>=0 
            && a[arr[ir].first-1][arr[ir].second]==a[arr[ir].first][arr[ir].second] 
            && index[(arr[ir].first-1)*10+arr[ir].second] == 0){
                index[(arr[ir].first-1)*10+arr[ir].second]++; //đánh dấu đã duyệt
                right++;
                arr[right].first = arr[ir].first-1;
                arr[right].second = arr[ir].second;
            }
        // trái
            if(arr[ir].second-1>=0 
            && a[arr[ir].first][arr[ir].second-1]==a[arr[ir].first][arr[ir].second] 
            && index[arr[ir].first*10+arr[ir].second-1] == 0){
                index[arr[ir].first*10+arr[ir].second-1]++; //đánh dấu đã duyệt
                right++;
                arr[right].first = arr[ir].first;
                arr[right].second = arr[ir].second-1;
            }
        // phải
            if(arr[ir].second+1<edge 
            && a[arr[ir].first][arr[ir].second+1]==a[arr[ir].first][arr[ir].second] 
            && index[arr[ir].first*10+arr[ir].second+1] == 0){
                index[arr[ir].first*10+arr[ir].second+1]++; //đánh dấu đã duyệt
                right++;
                arr[right].first = arr[ir].first;
                arr[right].second = arr[ir].second-1;
            }
        // đánh dấu giá trị tại ô hiện tại = 0 để lát khử những ô này ra khỏi mảng
            a[arr[ir].first][arr[ir].second] = 0;
    }   // duyệt hết queue
    if(right>1)  be += right*right*5;    //tính điểm be hiện tại = right*right*5;
    int b[10][10];  // tạo mảng mới
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            b[i][j] = a[i][j];
        }
    }
    // khử những ô đã được tính điểm
    for(int i = edge-1; i>=0; i--){ // khử từng cột
        for(int j = 0; j<edge; j++){ // nếu ô phía trên có màu (chưa bị khử),
        // ko bị out khỏi map thì, ô hiện tại đã bị khử:
            if(i+1<edge && b[i+1][j] >0 && b[i][j]==0){
                for(int k = i; k<edge-1; k++){
                    b[k][j] = b[k+1][j];
                }
            }
        }
    }
    // kiểm tra xem có cột nào bị trống hay không?
    for(int j = 0; j< edge; j++){
        bool empty = false;
        for(int i = 0; i <edge; i++){
            if(b[i][j]>0){
                empty =true;
                break;
            }
        }
        if (empty){
            for(int k = j+1; k < edge; k++){
                for (int i = 0; i<edge; i++){
                    b[i][k-1] = b[i][k];
                }
                j--;
            }
        }
    }
    //in mảng mới để check
    cout<<endl<<"New table"<<endl;
    for(int i = edge-1; i>=0; i--){
        for(int j =0; j<edge; j++){
            a[i][j] == 0 ? cout<<" ":cout<<a[i][j];
        }
        cout<<endl;
    }
    //đệ quy trên mảng mới
    for(int i = edge-1; i>=0; i--){
        for(int j= 0; j<edge; j++){
            dequy(edge, b, be, i, j, tmp_ans);
        }
    }
}

int main(){

    int a[10][10] = {0};

    cout<<"start\n";
    int edge = 4;

    for(int i = edge-1; i >= 0 ; --i){
        cout<<"line "<<i<<endl;
        for (int j = 0; j < edge; j++){
            cin>>a[i][j];
        }
    }
    vector<pair<int, int> > tmp_ans;
    int be = 0;
    for(int i = edge-1; i >= 0;i--){
        for(int j = 0; j <edge; j++){
            dequy(edge, a, be, i, j,tmp_ans);
        }
    }
}