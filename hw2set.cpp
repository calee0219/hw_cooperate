#include <bits/stdc++.h>
using namespace std;

class ui_User{
public:
    int UserId;
    int ItemId;
    int Result;
    int Unix_timestamp;

    ui_User(){}
    ui_User(int u,int i,int r,int t) {UserId = u; ItemId = i; Result = r; Unix_timestamp = t;}
    ui_User(int u,int i,int t) {UserId = u; ItemId = i; Result = 1; Unix_timestamp = t;}
    bool operator< (const ui_User&) const;
};

set<ui_User> ui_data;
//set<User> iutdata;
FILE *fin, *fout, *fin_database;

void accept(ui_User&);
void items(int *u1, int *u2);
set<ui_User>::iterator ui_binarySearch(const ui_User &user);

int main()
{
    fin_database = fopen("rec_log_train.txt", "rb");
    fin = fopen("testaccept.in", "rb");
    fout = fopen("data.out", "wb");
    int n;
    char cmd[10];
    fscanf(fin, "%d", &n);
    int userId, itemId, Unix_timestamp;
    int user1, user2;
    int uu, ii, rr, tt;
    while(fscanf(fin_database, "%d%d%d%d", &uu, &ii, &rr, &tt) == 4)
    {
        //data.insert(tmp);
        ui_User tmp(uu,ii,rr,tt);
        ui_data.insert(tmp);
    }

    while(n--)
    {
        fscanf(fin, "%s", cmd);
        switch(cmd[0]) {
            // accept
            case 'a':
                ui_User user;
                fscanf(fin, "%d%d%d", &user.UserId, &user.ItemId, &user.Unix_timestamp);
                accept(user);
                break;
                // items
/*
                   case 'i':
                   break;
            // users
            case 'u':
            break;
            // ratio
            case 'r':
            break;
            // findtime_item
            case 'f':
            break;
*/
        }
    }
    fclose(fin);
    fclose(fout);
    fclose(fin_database);
    return 0;
}

bool ui_User::operator<(const ui_User &u) const
{
    if(ui_User::UserId < u.UserId) return true;
    else if(ui_User::UserId > u.UserId) return false;
    else if(ui_User::ItemId < u.ItemId) return true;
    else if(ui_User::ItemId > u.ItemId) return false;
    else if(ui_User::Unix_timestamp < u.Unix_timestamp) return true;
    else return false;
}

void accept(ui_User &user)
{
    if(ui_data.find(user) != ui_data.end())
        fprintf(fout, "%d\n", ui_data.find(user)->Result);
    else
        fprintf(fout, "0\n");
    return;
}

set<ui_User>::iterator ui_binarySearch(const ui_User &user)
{
    int low = 0, high = ui_data.size() - 1;
    int mid;
    int check1 = 0, check2 = 0;
    while(low <= high){
        mid = (low + high) / 2;
        if((ui_data.begin()+mid)->UserId == user.UserId){
            check1 = 1;
            break;
        }
        else if(ui_data[mid].UserId > user.UserId){
            high = mid - 1;
        }
        else if(data[mid].UserId < *u){
            low = mid + 1;
        }
    }
    if(!check1) return 0;
    while(data[mid].UserId == *u){
        mid--;
    }
    low = mid + 1;
    mid++;
    while(data[mid].UserId == *u){
        mid++;
    }
    high = mid - 1;
    while(low <= high){
        mid = (low + high)/2;
        if(data[mid].ItemId == *ii){
            check2 = 1;
            break;
        }
        else if(data[mid].ItemId > *ii){
            high = mid - 1;
        }
        else if(data[mid].ItemId < *ii){
            low = mid + 1;
        }
    }
    if(!check2) return 0;
    while(data[mid].ItemId == *ii){
        mid--;
    }
    low = mid + 1;
    mid++;
    while(data[mid].ItemId == *ii){
        mid++;
    }
    high = mid - 1;
    while(low <= high){
        mid = (low + high)/2;
        if(data[mid].Unix_timestamp == *t){
            return mid;
        }
        else if(data[mid].Unix_timestamp > *t){
            high = mid - 1;
        }
        else if(data[mid].Unix_timestamp < *t){
            low = mid + 1;
        }
    }
    return 0;
}

//int binarySearchToUser(int *u)
//{
    //int low = 0, high = size - 1;
    //int mid;
    //while(low <= high){
        //mid = (low + high) / 2;
        //if(data[mid].UserId == *u){
            //return mid;
        //}
        //else if(data[mid].UserId > *u){
            //high = mid - 1;
        //}
        //else if(data[mid].UserId < *u){
            //low = mid + 1;
        //}
    //}
    //return 0;
//}
