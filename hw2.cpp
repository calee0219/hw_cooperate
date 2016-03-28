#include<cstdio>
#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#include<algorithm>

using namespace std;

void accept(int *u, int *ii, int *t);
void items(int *u1, int *u2);
void users(int *i1, int *i2, int *t1, int *t2);
void ratio(int *i, int *ithreshold);
void findtime_item(int *i, int *count);
int binarySearch (int *u, int *ii, int *t);
int binarySearchToUser(int *u);
int binarySearchToItem(int *u);
int binarySearchforRatio(int *i);
int userNumber[2421060];

class User{
public:
  int UserId;
  int ItemId;
  int Result;
  int Unix_timestamp;
};

User *data;
User *data1;
User *data2;
int size = 0;
int size_ratio = 0;
int onaji[30000];
int findTime[70000000];
FILE *fin, *fout, *fin_database;

int binarySearch(int *u, int *ii, int *t){
  int low = 0, high = size - 1;
  int mid;
  int check1 = 0, check2 = 0;
  while(low <= high){
    mid = (low + high) / 2;
    if(data[mid].UserId == *u){
      check1 = 1;
      break;
    }
    else if(data[mid].UserId > *u){
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
int binarySearchToUser(int *u){
  int low = 0, high = size - 1;
  int mid;
  while(low <= high){
    mid = (low + high) / 2;
    if(data[mid].UserId == *u){
      return mid;
    }
    else if(data[mid].UserId > *u){
      high = mid - 1;
    }
    else if(data[mid].UserId < *u){
      low = mid + 1;
    }
  }
  return 0;
}

int binarySearchToItem(int *u){
  int low = 0, high = size - 1;
  int mid;
  while(low <= high){
    mid = (low + high) / 2;
    if(data1[mid].ItemId == *u){
      return mid;
    }
    else if(data1[mid].ItemId > *u){
      high = mid - 1;
    }
    else if(data1[mid].ItemId < *u){
      low = mid + 1;
    }
  }
  return 0;
}

int binarySearchforRatio(int *i){
  int low = 0, high = size_ratio - 1;
  int mid;
  while(low <= high){
    mid = (low + high) / 2;
    if(data2[mid].ItemId == *i){
      return mid;
    }
    else if(data2[mid].ItemId > *i){
      high = mid - 1;
    }
    else if(data2[mid].ItemId < *i){
      low = mid + 1;
    }
  }
  return 0;
}

bool cmp(User a, User b){
  if(a.UserId < b.UserId)
    return true;
  else if(a.UserId > b.UserId)
    return false;
  else if(a.ItemId < b.ItemId)
    return true;
  else if(a.ItemId > b.ItemId)
    return false;
  else if(a.Unix_timestamp < b.Unix_timestamp)
    return true;
  else
    return false;
}

bool cmp1(User a, User b){
  if(a.ItemId < b.ItemId)
    return true;
  else if(a.ItemId > b.ItemId)
    return false;
  else if(a.Unix_timestamp < b.Unix_timestamp)
    return true;
  else
    return false;
}

bool cmp2(User a, User b){
  if(a.ItemId < b.ItemId)
    return true;
  else if(a.ItemId > b.ItemId)
    return false;
  else if(a.UserId < b.UserId)
    return true;
  else if(a.UserId > b.UserId)
    return false;
  else if(a.Unix_timestamp < b.Unix_timestamp)
    return true;
  else
    return false;
}

int main(){
  fin_database = fopen("/tmp2/KDDCUP2012/track1/rec_log_train.txt", "rb");
  fin = stdin;
  fout = stdout;
  int n;
  char cmd[10];
  fscanf(fin, "%d", &n);
  int userId, itemId, Unix_timestamp;
  int user1, user2;
  int uu, ii, rr, tt;
  int item1, item2;
  int time1, time2;
  int i, threshold;
  memset(onaji, -1, sizeof(onaji));
  data = new User[73209300];
  data1 = new User[73209300];
  data2 = new User[73209300];
  while(fscanf(fin_database, "%d%d%d%d", &uu, &ii, &rr, &tt) == 4){
    data[size].UserId = uu;
    data1[size].UserId = uu;
    data2[size].UserId = uu;
    data[size].ItemId = ii;
    data1[size].ItemId = ii;
    data2[size].ItemId = ii;
    data[size].Result = rr;
    data1[size].Result = rr;
    data2[size].Result = rr;
    data[size].Unix_timestamp = tt;
    data1[size].Unix_timestamp = tt;
    data2[size].Unix_timestamp = tt;
    size++;
  }
  sort(data, data + size, cmp);
  sort(data1, data1 + size, cmp1);
  sort(data2, data2 + size, cmp2);
  int _w = 1;
  for(int w = 1; w < size; w++){
    if(data2[w].Result == data2[w - 1].Result && data2[w].ItemId == data2[w - 1].ItemId && data2[w].Unix_timestamp ==
       data2[w - 1].Unix_timestamp && data2[w].UserId == data2[w - 1].UserId){
    }
    else{
      data2[_w].Result = data2[w].Result;
      data2[_w].ItemId = data2[w].ItemId;
      data2[_w].Unix_timestamp = data2[w].Unix_timestamp;
      data2[_w].UserId = data2[w].UserId;
      _w++;
    }
  }
  memset(userNumber, 0, sizeof(userNumber));
  size_ratio = _w;
  for(int w = 0; w < size_ratio; w++){
      userNumber[data2[w].UserId]++;
  }
  while(n--){
    fscanf(fin, "%s", cmd);
    if(cmd[0] == 'a'){
      fscanf(fin, "%d%d%d", &userId, &itemId, &Unix_timestamp);
      accept(&userId, &itemId, &Unix_timestamp);
    }
    else if(cmd[0] == 'i'){
      fscanf(fin, "%d%d", &user1, &user2);
      items(&user1, &user2);
    }
    else if(cmd[0] == 'u'){
      fscanf(fin, "%d%d%d%d", &item1, &item2, &time1, &time2);
      users(&item1, &item2, &time1, &time2);
    }
    else if(cmd[0] == 'r'){
      fscanf(fin, "%d%d", &i, &threshold);
      ratio(&i, &threshold);
    }
    else if(cmd[0] == 'f'){
      int count = 0;
      char c;
      fscanf(fin, "%d", &i);
      fscanf(fin, "%d", &findTime[count]);
      count++;
      while(fscanf(fin, "%c", &c) == 1 && c == ' '){
        fscanf(fin, "%d", &findTime[count]);
        count++;
      }
      findtime_item(&i, &count);
    }
  }
  fclose(fin);
  fclose(fout);
  fclose(fin_database);
  delete [] data;
  delete [] data1;
  delete [] data2;
  return 0;
}
void accept(int *u, int *ii, int *t){
  int mid = binarySearch(u, ii, t);
  if(!mid){
    fprintf(fout, "%d\n", mid);
  }
  else{
    fprintf(fout, "%d\n", data[mid].Result);
  }
}
void items(int *u1, int *u2){
  char s[] = "EMPTY";
  int mid1 = binarySearchToUser(u1);
  int mid2 = binarySearchToUser(u2);
  if(mid1 == 0 || mid2 == 0) fprintf(fout, "%s\n", s);
  else{
    while(data[mid1].UserId == *u1) mid1--;
    while(data[mid2].UserId == *u2) mid2--;
    int piv1 = mid1 + 1;
    int piv2 = mid2 + 1;
    int i = 0;
    while((data[piv1].UserId == *u1) && (data[piv2].UserId == *u2)){
      if(data[piv1].ItemId == data[piv2].ItemId){
        onaji[i++] = piv1;
        piv1++;
        piv2++;
      }
      else if(data[piv1].ItemId > data[piv2].ItemId){
        piv2++;
      }
      else
        piv1++;
    }
    if(i == 0){
      fprintf(fout, "%s\n", s);
    }
    else{
      fprintf(fout, "%d\n", data[onaji[0]].ItemId);
      int end = i;
      for(int j = 1; j < end; j++){
        if(data[onaji[j]].ItemId != data[onaji[j - 1]].ItemId){
          fprintf(fout, "%d\n", data[onaji[j]].ItemId);
        }
      }
    }
  }
}

int users_1[70000000];
int users_2[70000000];
int users_3[70000000];

void users(int *i1, int *i2, int *t1, int *t2){
  int mid1 = binarySearchToItem(i1);
  int mid2 = binarySearchToItem(i2);
  char s[] = "EMPTY";
  if(mid1 == 0 || mid2 == 0){
    fprintf(fout, "%s\n", s);
  }
  else{
    while(data1[mid1].ItemId == *i1) mid1--;
    while(data1[mid2].ItemId == *i2) mid2--;
    int piv1 = mid1 + 1;
    int piv2 = mid2 + 1;
    int i = 0;
    int j = 0;
    while(data1[piv1].ItemId == *i1){
      if(data1[piv1].Unix_timestamp >= *t1 && data1[piv1].Unix_timestamp <= *t2){
        users_1[i] = data1[piv1].UserId;
        i++;
        piv1++;
      }
      else{
        piv1++;
      }
    }
    while(data1[piv2].ItemId == *i2){
      if(data1[piv2].Unix_timestamp >= *t1 && data1[piv2].Unix_timestamp <= *t2){
        users_2[j] = data1[piv2].UserId;
        j++;
        piv2++;
      }
      else{
        piv2++;
      }
    }
    if(i == 0 || j == 0)
      fprintf(fout, "%s\n", s);
    else{
      sort(&users_1[0], &users_1[i]);
      sort(&users_2[0], &users_2[j]);
      int k1 = 0;
      int k2 = 0;
      int k3 = 0;
      while(k1 < i && k2 < j){
        if(users_1[k1] == users_2[k2]){
          users_3[k3] = users_1[k1];
          k3++;
          k1++;
          k2++;
        }
        else if(users_1[k1] < users_2[k2]){
          k1++;
        }
        else
          k2++;
      }
      if(k3 == 0){
        fprintf(fout, "%s\n", s);
      }
      else{
        fprintf(fout, "%d\n", users_3[0]);
        for(int k = 1; k < k3; k++)
          if(users_3[k] != users_3[k - 1])
            fprintf(fout, "%d\n", users_3[k]);
      }
    }
  }
}

void ratio(int *i, int *threshold){
  char s[] = "EMPTY";
  int mid = binarySearchforRatio(i);
  int numerator = 0;
  int denominator = 0;
  if(!mid){
	  for (int i = 100000; i < 2421060; ++i)
	  {
		  if(userNumber[i] > *threshold)
			  denominator++;
	  }
	  fprintf(fout, "%d/%d\n", numerator, denominator);
  }
  else{
    while(data2[mid].ItemId == *i) mid--;
    int piv = mid + 1;
    while(data2[piv].ItemId == *i){
      if(userNumber[data2[piv].UserId] > *threshold && data2[piv].Result == 1){
        numerator++;
        piv++;
        while(data2[piv].UserId == data2[piv-1].UserId) piv++;
      }
      else
          piv++;
    }
    for (int i = 100000; i < 2421060; ++i)
    {
        if(userNumber[i] > *threshold)
            denominator++;
    }
    fprintf(fout, "%d/%d\n", numerator, denominator);
  }
}
int time1[70000000];
void findtime_item(int *i, int *count){
  char s[] = "EMPTY";
  int n = 0;
  int mid = binarySearchToItem(i);
  if(!mid) fprintf(fout, "%s\n", s);
  else{
    while(data1[mid].ItemId == *i) mid--;
    int piv = mid + 1;
    while(data1[piv].ItemId == *i){
      int check = 0;
      for(int i = 0; i < *count; i++)
        if(data1[piv].UserId == findTime[i])
          check = 1;
      if(check){
        time1[n] = data1[piv].Unix_timestamp;
        n++;
      }
      piv++;
    }
    int k = 0;
    if(n == 0) fprintf(fout, "%s\n", s);
    else{
	    fprintf(fout, "%d\n", time1[k]);
      k++;
      while(k < n){
	      if(time1[k] != time1[k - 1]){
		      fprintf(fout, "%d\n", time1[k]);
		      k++;
	      }
	      else k++;
      }
    }
  }
}
