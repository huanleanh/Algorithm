#include <bits/stdc++.h>
#include <vector>
// #include <iostream>
using namespace std;

int best = 0;
vector <pair <int, int> > ans;

void dequy(
    int cur_row, int cur_col, int a[10][10], int be, int row, 
    int column, vector <pair <int, int> > tmp_ans)
{
    // nếu giá trị ô hiện tại = 0 (đã bị loại bỏ) thì khỏi đệ quy thêm.
    int b[10][10];  // tạo mảng mới
    int check = 0;
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            b[i][j] = a[i][j];
            check += b[i][j];
        }
    }
    if(check ==0) return;
    int edge = cur_col;
    if (a[row][column] == 0) {
        if(be> best){
            // cout<<"- "<<be<<" "<<best<<endl;
            best = be;
            //ans = tmp_ans;
        }
        return;
    }

    int right=0, index[100] = {0}, ir = 0;
    pair<int, int> arr[100];
    arr[ir].first = row;
    arr[ir].second = column;
    index[row*10+column]++; //đánh dấu đã duyệt

    //in mảng mới để check
    // cout<<endl<<"New table"<<endl;
    // for(int i = cur_row-1; i>=0; i--){
    //      cout<< i << " -- ";
    //     for(int j =0; j<edge; j++){
    //         if ( i == row && j == column) cout<<"*";
    //         else
    //             b[i][j] == 0 ? cout<<" ":cout<<b[i][j];
    //     }
    //     cout<<endl;
    // }

    //cout<<right<<" ";

    while (ir<=right){ // duyệt các ô liên kề để tìm mảng cùng màu
        // trên
            if(arr[ir].first+1 < cur_row 
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
            b[arr[ir].first][arr[ir].second] = 0;
            ir++;
    }   // duyệt hết queue
    right++;
    
    if(right>=2)  be += right*right*5;    //tính điểm be hiện tại = right*right*5;
    
    // khử những ô đã được tính điểm
    for(int i = cur_row-1; i>=0; i--){ // khử từng cột
        for(int j = 0; j<edge; j++){ // nếu ô phía trên có màu (chưa bị khử),
        // ko bị out khỏi map thì, ô hiện tại đã bị khử:
            if(i+1<cur_row && b[i+1][j] >0 && b[i][j]==0){
                for(int k = i; k<cur_row; k++){
                    b[k][j] = b[k+1][j];
                }
            }
        }
    }
    
    //in mảng mới để check
    if(right == 13){

        cout<<endl<<"New table"<<endl;
        for(int i = cur_row-1; i>=0; i--){
            cout<< i << " -- ";
            for(int j =0; j<edge; j++){
                if (i == row && j == column) cout<<"*"; else
                a[i][j] == 0 ? cout<<" ":cout<<a[i][j];
            }
            cout<<endl;
        }

    }
    // kiểm tra xem có cột nào bị trống hay không?
    for(int j = 0; j< edge; j++){
        bool empty = true;
        for(int i = 0; i <cur_row; i++){
            if(b[i][j]>0){
                empty = false;
                break;
            }
        }
        if (empty){
            for(int k = j+1; k <= edge; k++){
                for (int i = 0; i<cur_row; i++){
                    b[i][k-1] = b[i][k];
                }
                
            }
            edge--;
            j--;
        }
    }

    //in mảng mới để check
 //   cout<<endl<<"New table"<<endl;
    // for(int i = cur_row-1; i>=0; i--){
    //      cout<< i << " -- ";
    //     for(int j =0; j<edge; j++){
    //         b[i][j] == 0 ? cout<<" ":cout<<b[i][j];
    //     }
    //     cout<<endl;
    // }

    //đệ quy trên mảng mới
    for(int i = edge-1; i>=0; i--){
        for(int j= 0; j<edge; j++){
            dequy(cur_row, edge, b, be, i, j, tmp_ans);
        }
    }
}

int main(){

    int a[10][10] = {0};

    cout<<"start\n";
    int edge = 4;

    // for(int i = edge-1; i >= 0 ; --i){
    //     cout<<"line "<<i<<endl;
    //     for (int j = 0; j < edge; j++){
    //         cin>>a[i][j];
    //     }
    // }


    a[3][0] = 1; a[3][1] = 2; a[3][2] = 3; a[3][3] = 4;
    a[2][0] = 1; a[2][1] = 2; a[2][2] = 3; a[2][3] = 1;
    a[1][0] = 3; a[1][1] = 2; a[1][2] = 3; a[1][3] = 1;
    a[0][0] = 4; a[0][1] = 2; a[0][2] = 3; a[0][3] = 4;
    
    
    vector<pair<int, int> > tmp_ans;
    int be = 0;
    // for(int i = edge-1; i >= 0;i--){
    //     for(int j = 0; j <edge; j++){
    //         dequy(edge, edge, a, be, i, j,tmp_ans);
    //         cout<<best<<endl;
    //     }
    // }

     dequy(edge, edge, a, be, 3, 0,tmp_ans);

    cout <<"best : "<< best<<endl;
}

/*input
1 2 3 4
1 2 3 1
3 2 3 1
4 2 3 4
*/
// 4*4*5+5*5*5+4*4*5+3*3*5
// 16+25+16+9
// 32+34  = 66 * 5