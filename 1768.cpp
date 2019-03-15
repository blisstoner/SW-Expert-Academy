#define N 4
#define S strike
#define B ball

typedef struct {
  int strike;
  int ball;
} Result;

// API
extern Result query(int guess[]);

inline Result getScore(int* guess, int* ball){
  Result ret;
  ret.strike = 0;
	ret.ball = 0;
	for(int i = 0; i < 4; i++){ // guess[i]에 대해
    if(guess[i] == ball[i]) ret.strike++;
    for(int j = 0; j < 4; j++){
      if(i==j) continue;
      if(guess[i] == ball[j]) ret.ball++;
    }
  }
  return ret;
}
int valid_ball[5040][4]; // 4자리가 모두 달라 가능한 생각하는 수들의 집합
  
void doUserImplementation(int guess[]) {
  static bool first = true;
  guess[0] = 1; guess[1] = 2; guess[2] = 9; guess[3] = 7; // my phone number ㅎㅅㅎ
  if(first){
    first = false;
    int len = 0;
    for(int i = 0; i < 10; i++){
      for(int j = 0; j < 10; j++){
        if(i==j) continue;
        for(int k = 0; k < 10; k++){
          if(i==k or j==k) continue;
          for(int l = 0; l < 10; l++){
            if(i==l or j==l or k==l) continue;
            valid_ball[len][0]=i,valid_ball[len][1]=j,valid_ball[len][2]=k,valid_ball[len][3]=l;
            len++;
          }
        }
      }
    }
  }

  Result ret = query(guess);  
  int cand[5040][4]; // 정답으로 가능한 후보군을 계속 가져갈 것이다.
  int len = 0; // len은 후보군의 갯수
  for(int i = 0; i < 5040; i++){
    Result score = getScore(guess, valid_ball[i]); // 정답이 digit일 수 있는가 확인하고 싶은 것이다.
//    cout << score.S << ' ' << score.B << '\n';
    if(score.S != ret.S or score.B != ret.B) continue;
    for(int j = 0; j < 4; j++) cand[len][j] = valid_ball[i][j];
    len++;
  }
  static int rrand2 = 234;
  while(len > 1){
//    cout << len << ' ';
    int bestguess[4];
    double bestdevi = 1e100; // 표준편차가 가장 작은 guess(=0S0B, 0S1B, 0S2B, ... 등등의 후보군의 수가 최대한 균등한 guess)를 찾을 것이다.
    int rrand = 0;
    for(int T = 0; T < len+1000; T++){ // valid_ball[i]로 guess해봄. 근데 5040개를 다 하니까 시간초과가 나서 1000개 정도만 하자.
      if(T < len) rrand = T;
      else rrand = rrand2;
      rrand2 = (10007*rrand+2333)%5040;
      int cnt[5][5]={}; // cnt[i][j] : strike가 i개, ball이 j개인 갯수
      for(int j = 0; j < len; j++){
        Result score = getScore(valid_ball[rrand], cand[j]);
        cnt[score.S][score.B]++;
      }
      double mean = 0;
      double devi = 0;
      for(int i = 0; i <= 4; i++){
        for(int j = 0; j <= 4-i; j++){
          mean += cnt[i][j];
        }
      }
      for(int i = 0; i <= 4; i++){
        for(int j = 0; j <= 4-i; j++){
          devi += (cnt[i][j]-mean)*(cnt[i][j]-mean);
        }
      }
      if(devi < bestdevi){
        for(int i = 0; i < 4; i++) bestguess[i] = valid_ball[rrand][i];
        bestdevi = devi;
      }
    }
    // valid_ball[bestguess]가 최선의 선택임
    for(int i = 0; i < 4; i++) guess[i] = bestguess[i];
    Result ret = query(guess); // 이 결과를 바탕으로 cand와 len을 갱신하자
    int beforelen = len;
    len = 0;
    for(int i = 0; i < beforelen; i++){
      Result score = getScore(guess, cand[i]);
      if(score.S != ret.S or score.B != ret.B) continue;
      for(int j = 0; j < 4; j++) cand[len][j] = cand[i][j];
      len++;       
    }
  }
  for(int i = 0; i < 4; i++) guess[i] = cand[0][i];
}
