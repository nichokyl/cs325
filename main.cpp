#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

void algorithm1(vector<int>& firstLine, vector<int>& keyLine, vector<int>& ballLine){
    int lockerSize = firstLine[0];
    int keySize = firstLine[1];
    int ballSize = firstLine[2];
    vector<int> ballLocker(lockerSize+1), keys(lockerSize+1);
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
/*    cout << "New Test Set:" << "\n";
    cout << "BallSize:" << ballSize << "\n";
    cout << "KeySize:" << keySize << "\n";

    cout << "Balls in the locker: ";
    for(int i = 1; i <= lockerSize; i++){
        cout << ballLocker[i] << " ";
    }
    cout << "\n";
    cout << "Keys array:          ";
    for(int i = 1; i <= lockerSize; i++){
        cout << keys[i] << " ";
    }
    cout << "\n";
*/
    //ALGORITHM START
    int result = 0;
    for(int i = 1; i <= lockerSize; i++){
        //if has a ball
        if(ballLocker[i] == 1){
            //if ball has a key in a same location
            if(ballLocker[i] - keys[i] == 0){
                keys[i+1] = 1;
                //keys[i-1] = 1;
                ballLocker[i] = 2;
                result++;
            }else if((ballLocker[i] - keys[i]) == 1){ //if keys are somewhere else
                int keyInFrontLoc = 0;
                int keyInFront = 0;
                int keyInBack = 0;
                int keyInBackLoc = 0;
                //find the nearest key forward from the current ball (i)
                for(int j = i; j <= lockerSize; j++){
                    if(keys[j] == 1){
                        keyInFront = 1;
                        keyInFrontLoc = j;
                        break;
                    }
                }
                //find the closest key backward from the current ball (i)
                for(int k = i; k > 0; k--){
                    if(keys[k] == 1){
                        keyInBack = 1;
                        keyInBackLoc = k;
                        break;
                    }
                }
                //find the balls in between the keys
                if(keyInBack == 1 && keyInFront == 1){
                    int calcForward = 1;
                    int calcBackward = 1;
                    int loopCount = 0, loopCount1 = 0;
                    //calculate the total distant of the balls to the initial key
                    for(int l = keyInBackLoc; l <= keyInFrontLoc; l++){
                        if(ballLocker[l] == 1){
                            calcForward += l - calcForward;
                        }
                        loopCount++;
                    }
                    for(int l = keyInFrontLoc; l >= keyInBackLoc; l--){
                        if(ballLocker[l] == 1){
                            calcBackward += (keyInFrontLoc - l) - calcBackward;
                        }
                        loopCount1++;
                    }
                    //weird counting problem I have to add one to make it correct
                    calcBackward++;
                    int ballFound = 0, distKeyToBall = 0, distBallToKey, sum = 0, sumLeft = 0, sumRight = 0;
                    //check the last option where using both keys is optimal
                    for(int l = keyInBackLoc; l <= keyInFrontLoc; l++){
                        if(ballLocker[l] == 1){
                            ballFound = l;
                            distKeyToBall = ballFound - keyInBackLoc;
                            distBallToKey = keyInFrontLoc - ballFound;
                            if(distBallToKey > distKeyToBall){
                                sumLeft = distKeyToBall + 1;
                            }else if(distBallToKey < distKeyToBall){
                                sumRight = distBallToKey + 1;
                                break;
                            }else if(distKeyToBall == distBallToKey){
                                sumLeft = distKeyToBall + 1;
                            }
                        }
                    }
                    sum = sumLeft + sumRight;
                    //cout << "Total for balls forward from the first key: "<< calcForward << "," << loopCount << "\n";
                    //cout << "Total for balls backward from the last key: "<< calcBackward << "," << loopCount1 << "\n";
                    //cout << "Total for balls from both end : " << sum << "," << "\n";
                    //update the balls and keys
                    for(int n = keyInBackLoc; n <= keyInFrontLoc; n++){
                        if(ballLocker[n] == 1){
                            ballLocker[n] = 2;
                        }
                    }
                    keys[keyInFrontLoc+1] = 1;
                    result += min(sum, min(calcForward, calcBackward));
                }else if(keyInBack == 1 && keyInFront == 0){
                    int temp = 0;
                    for(int n = keyInBackLoc; n <= lockerSize; n++){
                        if(ballLocker[n] == 1){
                            temp = n - keyInBackLoc + 1;
                            ballLocker[n] = 2;
                        }
                        //update the keys
                        keys[n+1] = 1;
                        keys[n-1] = 1;
                    }
                    result += temp;
                }else if(keyInBack == 0 && keyInFront == 1){
                    result += keyInFrontLoc - i + 1;
                    for(int n = i; n <= keyInFrontLoc; n++){
                        if(ballLocker[n] == 1){
                            ballLocker[n] = 2;
                        }
                        keys[n+1] = 1;
                        keys[n-1] = 1;
                    }

                }
            }
        }
    }
    ofstream myFile ("Results.txt", ios::out | ios::app);
    if(myFile.is_open()){
        myFile << result << ", ";
    }else{
        cout << "cant open the file";
    }
    myFile.close();
}
void algo1(vector<int>& firstLine, vector<int>& keyLine, vector<int>& ballLine, int lockerSize){
    //brute force
    //get the variable out from the first line
    //int lockerSize = firstLine[0];
    int keySize = firstLine[1];
    int ballSize = firstLine[2];
    //need to open the ones that has a key with a balls in. We can merge that
    //then calculate the distance between the balls relative to the keys
    vector<int> ballLocker(lockerSize+1), keys(lockerSize+1), originalKeys(lockerSize+1);
    for(int i = 0; i < lockerSize+1; i++){
        ballLocker[i] = 0;
        keys[i] = 0;
    }
    for(int i = 0; i < keySize; i++){
        keys[keyLine[i]] = 1;
        originalKeys[keyLine[i]] = 1;
    }
    for(int i = 0; i < ballSize; i++){
        ballLocker[ballLine[i]] = 1;
    }
    cout << "New Test Set:" << "\n";
    cout << "BallSize:" << ballSize << "\n";
    cout << "KeySize:" << keySize << "\n";

    cout << "Balls in the locker: ";
    for(int i = 0; i < lockerSize+1; i++){
        cout << ballLocker[i] << " ";
    }
    cout << "\n";
    cout << "Keys array:          ";
    for(int i = 0; i < lockerSize+1; i++){
        cout << keys[i] << " ";
    }
    cout << "\n";
    vector<int> ballLockerOrg;
    ballLockerOrg = ballLocker;
    //algorithm start
    vector<int> usedKeys;
    int run = 0, sum = 0;
    cout << "***** Algorithm begins**** \n";
    while(run < ballSize){
        for(int i = 0; i < lockerSize+1; i++){
            if(ballLocker[i] == 1){
                if((ballLocker[i] - keys[i]) == 0){
                    //add location of the key that used into opened Locker
                    bool found = false;
                    for(int l = 0; l < usedKeys.size(); l++){
                        if(i == usedKeys[l]){
                            found = true;
                        }
                    }
/*                  for(int i = 0; i < usedKeys.size();i++){
                        cout << usedKeys[i] << " ";
                    }
                    cout << "\n";
*/                    //update the available keys
                    keys[i+1] = 1;
                    keys[i-1] = 1;
                    //update the ball that are opened
                    ballLocker[i] = 2;
                    if(found == false){
                        sum++;
                        usedKeys.push_back(i);
                    }
                     //cout << "TEMP//sum: " << //sum << "\n";
                    //cout << "Keys opened at location i with the key at location i \n";
/*                    for(int i = 0; i < lockerSize+1; i++){
                        cout << keys[i] << " ";
                    }
                    cout << "\n";
*/                }else if((ballLocker[i] - keys[i]) == 1){
                    int distForward = 0, j;
                    int distBackward = 0, k;
                    int keyInfront = 0;
                    int keyInBack = 0;
                    int lastBallBetweenKeysLoc = 0;
                    //int firstBallFound = i;
                    int keyInBackLoc = 0;
                    int keyInFrontLoc = 0;
                    //find the nearest key forward from the current ball (i)
                    for(j = i; j < lockerSize+1; j++){
                        //cout << "j:" << j ;
                        if(ballLocker[j] == 1){
                            lastBallBetweenKeysLoc = j;
                        }
                        if(keys[j] == 1){
                            //cout << "keyFound1: " << keys[j] << "\n";
                            distForward = abs(i - j) + 1;
                            keyInfront = 1;
                            keyInFrontLoc = j;
                            break;
                        }
                    }

                    if(keyInfront == 0){
                        lastBallBetweenKeysLoc = 0;
                    }else{
                        cout << "another ball found between the keys: " << lastBallBetweenKeysLoc << "\n";
                    }
                    //find the closest key backward from the current ball (i)
                    for(k = i; k > 0; k--){
                        if(keys[k] == 1){
                            //cout << "keyFound2: " << keys[k] << "\n";
                            distBackward = (i - k) + 1;
                            keyInBack = 1;
                            keyInBackLoc = k;
                            break;
                        }
                    }
                    if(lastBallBetweenKeysLoc != 0){
                        int temp = 0;
                        if(distForward < lastBallBetweenKeysLoc){
                            distBackward = distForward + 10;
                        }

                    }
                    //compare which distance is shortest, use the one is shortest
//                    cout << "* backward : forward " << distBackward << ":" << distForward << "\n";
                    if(keyInfront == 1 && keyInBack == 0){
                        for(int n = i; n < i + distForward; n++){
                            //update keys and balls that are opened
                            keys[n] = 1;
                            //keys[i+1] = 1;
                            ballLocker[n] = 2;
                            usedKeys.push_back(n);
/*                            for(int i = 0; i < usedKeys.size();i++){
                                cout << usedKeys[i] << " ";
                            }
                            cout << "\n";
*/                          sum++;
                        }
                        //update the keys
                        keys[i+1] = 1;
                        //keys[i-1] = 1;
/*                        cout << "Keys opened in the case of key1 = 1 key2 = 0 \n";
                        for(int i = 0; i < lockerSize+1; i++){
                            cout << keys[i] << " ";
                        }
                        cout << "\n";
*/                       //cout << "temp //sum: " << //sum  << "\n";
                    }else if(keyInBack == 1 && keyInfront == 0){
                        for(int n = i; n > i - distBackward; n--){
                            //cout << "n: " << n;
                            //update keys and balls that are opened
                            keys[n] = 1;
                            //keys[i-1] = 1;
                            ballLocker[n] = 2;
                            usedKeys.push_back(n);
/*                            for(int i = 0; i < usedKeys.size();i++){
                                cout << usedKeys[i] << " ";
                            }
                            cout << "\n";
*/                          sum++;
                        }
                        //update the keys
                        keys[i+1] = 1;
                        //keys[i-1] = 1;
/*                        cout << "Keys opened in the case of key2 = 1 key1 = 0 : \n";
                        for(int i = 0; i < lockerSize+1; i++){
                            cout << keys[i] << " ";
                        }
                        cout << "\n";
*/                        //cout << "temp //sum: " << //sum  << "\n";
                    }else if(keyInfront == 1 && keyInBack == 1){
                        //cout << "both key is found" << "\n";
                        if(distForward < distBackward){ //if the key forward is smaller then use that
                             //cout << "distance forward < distance backward" << "\n";
                            for(int n = i; n < i + distForward; n++){
                                //update keys and balls that are opened
                                keys[n] = 1;
                                //keys[i+1] = 1;
                                ballLocker[n] = 2;
                                usedKeys.push_back(n);
/*                                for(int i = 0; i < usedKeys.size();i++){
                                    cout << usedKeys[i] << " ";
                                }
                                cout << "\n";
*/                              sum++;
                            }
                            //update the balls
                            //ballLocker[i] = 2;
                            //update the keys
                            keys[i+1] = 1;
                            //keys[i-1] = 1;
/*                            cout << "Keys opened in the case of distForward < distBackward\n";
                            for(int i = 0; i < lockerSize+1; i++){
                                cout << keys[i] << " ";
                            }
                            cout << "\n";
*/                            //cout << "temp //sum: " << //sum  << "\n";
                        }else if(distForward > distBackward){ //if the backward key is smaller then use that
                            //cout << "distance forward > distance backward" << "\n";
                            for(int n = i; n > i - distBackward; n--){
                                //cout << "n:" << n;
                                //update keys and balls that are opened
                                keys[n] = 1;
                                //keys[i-1] = 1;
                                ballLocker[n] = 2;
                                usedKeys.push_back(n);
/*                                for(int i = 0; i < lockerSize;i++){
                                    cout << usedKeys[i] << " ";
                                }
                                cout << "\n";
*/                              sum++;
                            }
                            //update the balls
                            //ballLocker[i] = 2;
                            //update the keys
                            keys[i+1] = 1;
                            //keys[i-1] = 1;
/*                            cout << "Keys opened in the case of distForward > distBackward \n";
                            for(int i = 0; i < lockerSize+1; i++){
                                cout << keys[i] << " ";
                            }
                            cout << "\n";
*/                            //cout << "temp //sum: " << //sum  << "\n";
                        }else{
//                            cout << "equal distance to the key" << "\n";
                            //we have to decide which on to use since both keys have the same distance to the ball.
                            //we have to look at the next ball
                            for(int n = i; n < i + distForward; n++){
                                //update keys and balls that are opened
                                keys[n] = 1;
                                //keys[i+1] = 1;
                                ballLocker[n] = 2;
                                usedKeys.push_back(n);
/*                                for(int i = 0; i < usedKeys.size();i++){
                                    cout << usedKeys[i] << " ";
                                }
                                cout << "\n";
 */                             sum++;
                            }
                            //update the balls
                            //ballLocker[i] = 2;
                            //update the keys
                            //keys[i+1] = 1;
                            //keys[i-1] = 1;
/*                            cout << "Keys opened after the first run on equal case: \n";
                            for(int i = 0; i < lockerSize+1; i++){
                                cout << keys[i] << " ";
                            }
                            cout << "\n";
*/                            //cout << "temp //sum: " << //sum  << "\n";
                        }
                    }

                }
            }
        }
        run++;
    }
/*    for(int i = 0; i < ballLocker.size(); i++){
        if(ballLocker[i] == 2){
            sum++;
        }
    }
*/
    cout << "**Result: " << sum << "\n";
    cout << "Balls changed after the run: ";
    for(int i = 0; i < lockerSize+1; i++){
        cout << ballLocker[i] << " ";
    }
    cout << "\n";
    cout << "Keys used and updated:       ";
    for(int i = 0; i < lockerSize+1; i++){
        cout << keys[i] << " ";
    }
    cout << "\n";
    cout << "Ball orig and updated:       ";
    for(int i = 0; i < lockerSize+1; i++){
        cout << ballLockerOrg[i] << " ";
    }
    cout << "\n";
    cout << "Keys orig and updated:       ";
    for(int i = 0; i < lockerSize+1; i++){
        cout << originalKeys[i] << " ";
    }
    cout << "\n";
    cout << "Number of keys used: " << usedKeys.size() << "\n";
    cout << "**** algorithm end **** \n";

}
void algo2(){
    //dynamic programming
}
int main()
{
    //run algorithms with testing file
      string line;
      //ifstream myfile ("dp_set1.txt");
      //ifstream myfile ("dp_set2.txt");
      ifstream myfile ("dp_set3.txt");
      int lockerSize = 0;
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
                  int keySize = firstLine[1];
                  int ballSize = firstLine[2];
                  sort(secondLine.begin(), secondLine.begin()+keySize);
                  sort(thirdLine.begin(), thirdLine.begin()+ballSize);
                  //algo1(firstLine, secondLine, thirdLine, lockerSize);
                  algorithm1(firstLine, secondLine, thirdLine);
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
          cout << "can't open the testing.txt file (required testing .txt file to be in the same location in order to run) \n";
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
