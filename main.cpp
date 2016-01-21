#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

void algo1(vector<int>& firstLine, vector<int>& keyLine, vector<int>& ballLine, int lockerSize){
    //brute force
    //get the variable out from the first line
    //int lockerSize = firstLine[0];
    int keySize = firstLine[1];
    int ballSize = firstLine[2];

    //cout << "inside algo1";

    sort(keyLine.begin(), keyLine.begin()+keySize);
    sort(ballLine.begin(), ballLine.begin()+ballSize);
    //need to open the ones that has a key with a balls in. We can merge that
    //then calculate the distance between the balls relative to the keys
    vector<int> ballLocker(lockerSize+1), keys(lockerSize+1);
    /*
    int* ballLocker;
    int* keys;
    ballLocker = new int [lockerSize];
    keys = new int [lockerSize];
    */
    for(int i = 0; i < lockerSize+1; i++){
        ballLocker[i] = 0;
        keys[i] = 0;
    }
    for(int i = 0; i < keySize; i++){
        keys[keyLine[i]] = 1;
    }
    for(int i = 0; i < ballSize; i++){
        ballLocker[ballLine[i]] = 1;
    }
/*    cout << "Balls in the locker: ";
    for(int i = 0; i < lockerSize+1; i++){
        cout << ballLocker[i] << " ";
    }
    cout << "\n";

    cout << "Keys: ";
    for(int i = 0; i < lockerSize+1; i++){
        cout << keys[i] << " ";
    }
    cout << "\n";
*/    //algorithm start
    vector<int> openedLocker;
    int run = 0, sum = 0;

    while(run < ballSize){
        cout << "***** Algorithm run **** \n";
        cout << "BallSize:" << ballSize << "\n";
        cout << "Balls in the locker: ";
        for(int i = 0; i < lockerSize+1; i++){
            cout << ballLocker[i] << " ";
        }
        cout << "\n";

        cout << "Keys: ";
        for(int i = 0; i < lockerSize+1; i++){
            cout << keys[i] << " ";
        }
        cout << "\n";
        for(int i = 0; i < lockerSize+1; i++){
            if(ballLocker[i] == 1){
                if((ballLocker[i] - keys[i]) == 0){
                    //add location of the key that used into opened Locker
                    openedLocker.push_back(i);
                    //update the available key
                    keys[i+1] = 1;
                    keys[i-1] = 1;
                    //update the ball that are opened
                    ballLocker[i] = 2;
                    sum++;
                }else if((ballLocker[i] - keys[i]) == 1){
                    int tempForward = 0, j;
                    int tempBackward = 0, k;
                    int keyFound1 = 0;
                    int keyFound2 = 0;
                    //find the nearest key forward from the current ball (i)
                    for(j = i; j < lockerSize+1; j++){
                        if(keys[j] == 1){
                            tempForward = abs(i - j);
                            keyFound1 = 1;
                            break;
                        }
                    }
                    //find the closest key backward from the current ball (i)
                    for(k = i; k > 0; k--){
                        cout << "i: " << i << " ";
                        cout << "k: " << k << " ";
                        if(keys[k] == 1){
                            cout << "key: " << keys[k];
                            tempBackward = i - k;
                            keyFound2 = 1;
                            break;
                        }
                    }
                    cout << "\n" ;
                    //compare which distance is shortest, if tempforward is shorter then use that
                    cout << tempBackward << ":" << tempForward << "\n";
                    if((tempForward < tempBackward) && (keyFound1 == 1 || keyFound2 == 1)){
                        for(int n = i; n > tempForward; n++){
                            //update keys and balls that are opened
                            keys[n] = 1;
                            ballLocker[n] = 2;
                            openedLocker.push_back(n);
                            sum++;
                        }
                    }else if((tempForward > tempBackward) && (keyFound2 == 1 || keyFound1 == 1)){
                        for(int n = i; n > tempBackward; n--){
                            //update keys and balls that are opened
                            keys[n] = 1;
                            ballLocker[n] = 2;
                            openedLocker.push_back(n);
                            sum++;
                        }
                    }

                }
            }
        }
        /*
        //time to quit if there are no balls left (balls are represent as 1)
        for(int i = 0; i < lockerSize; i++){
            if(ballLocker[i] == 1){
                run = 0;
            }else{
                run = 1;
            }
        }
        */
        run++;
    }
    cout << "result: " << sum << "\n";
    cout << "Balls in the locker: ";
    for(int i = 0; i < lockerSize+1; i++){
        cout << ballLocker[i] << " ";
    }
    cout << "\n";

    cout << "Keys: ";
    for(int i = 0; i < lockerSize+1; i++){
        cout << keys[i] << " ";
    }
    cout << "\n";
/*
    int locker[400] = { };
    cout << "\n" << "balls (1): ";
    for(int i = 0; i < ballSize; i++){
        cout << ballLine[i] << " ";
        locker[ballLine[i]] = 1;
    }
    cout << "keys (2): ";
    for(int i = 0; i < keySize; i++){
        cout << keyLine[i] << ", ";
        locker[keyLine[i]] = 2;
    }

    cout << "\n";
    //locker
    for(int i = 1; i <= lockerSize; i++){
        cout << locker[i] << " ";
    }
    cout << "\n";
*/
    /*
    vector<int> maxKeys, minKeys;
    int maxD = 0;
    int shortestD = 0;

    for(int i = 0; i < keySize; i++){
        int temp = 0;
        for(int j = 0; j < ballSize; j++){
            temp += abs(ballLine[j] - keyLine[i]);
        }
        if(temp > maxD){
            maxKeys.push_back(keyLine[i]);
        }else{
            minKeys.push_back(keyLine[i]);
        }
        */
        /*
        int sum = 0;
        cout << "test: ";
        for(int n = 0; n < ballSize; n++){
            sum += test[n];
            cout << test[n] << " ";
        }
        result.push_back(sum);
        cout << "= " << sum << "\n";
        //cout << "key: " << temp;
        test.clear();
        */
    //}

    /*
    for(int i = 0; i < keySize; i++){
        cout << keyLine[i] << " ";
    }
    cout << "\n";
    for(int i = 0; i < ballSize; i++){
        cout << ballLine[i] << " ";
    }
    */
}
void algo2(){
    //dynamic programming
}
int main()
{
    //run algorithms with testing file
      string line;
      ifstream myfile ("dp_set1.txt");
      int lockerSize;
      if(myfile.is_open()){
          cout << "Run all algorithms with dp.txt file" << "\n";
          int counter = 1;
          while(getline(myfile, line)){
              size_t found = line.find(':');
              //cout << found << "\n";
              if(found!=string::npos){
                  vector<int> firstLine, secondLine, thirdLine;
                  //cout << "found : (skip)" << "\n";
                  while(counter < 4){
                      getline(myfile, line);
                      stringstream ss(line);
                      string value;
                      int intValue;
                      if(counter == 1){
                        while(getline(ss, value, ' ')){
                            intValue = atoi(value.c_str());
                            firstLine.push_back(intValue);
                        }
                      }
                      if(counter == 2){
                        while(getline(ss, value, ' ')){
                            intValue = atoi(value.c_str());
                            secondLine.push_back(intValue);
                        }
                      }
                      if(counter == 3){
                        while(getline(ss, value, ' ')){
                            intValue = atoi(value.c_str());
                            thirdLine.push_back(intValue);
                        }
                      }
                      counter++;
                  }
                  //run algo1 for the first test
                  lockerSize = firstLine[0];
                  algo1(firstLine, secondLine, thirdLine, lockerSize);
              }else{
                /*stringstream ss(line);
                string value;
                //cout << line << "\n";
                //int intValue;
                vector<int> firstLine, secondLine, thirdLine;
                //first value is number of lockers
                //2nd value is keys
                //3rd value is balls
                while(getline(ss, value, ' ')){
                   firstLine.push_back(value);
                }*/
              }
              //call algorithms

              counter = 1;
          }
          myfile.close();
      }else{
          cout << "can't open the testing.txt file (required testing.txt file to be in the same location in order to run) \n";
      }
      /*
      vector<int>::const_iterator ci;
      for(ci = firstLine.begin(); ci!=firstLine.end(); ci++){
          cout << *ci << " ";
      }
      cout << "first line \n";
      vector<int>::const_iterator ci2;
      for(ci2 = secondLine.begin(); ci2!=secondLine.end(); ci2++){
          cout << *ci2 << " ";
      }
      cout << "second line \n";
      vector<int>::const_iterator ci3;
      for(ci3 = thirdLine.begin(); ci3!=thirdLine.end(); ci3++){
          cout << *ci3 << " ";
      }
      cout << "third line \n";
      */
    return 0;
}
