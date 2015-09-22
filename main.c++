#include <iostream>
#include <utility>
#include <queue>
using namespace std;

// Pair of (display, number of presses)
typedef pair<int, unsigned int> ButtonResult;

ButtonResult press_blue(int n, unsigned int p){
    return make_pair(n-1, p+1);
}

ButtonResult press_red(int n, unsigned int p){
    return ButtonResult(n*2, p+1);
}

unsigned int getMinPresses(int n, int m){
    if(n > m){
        return n-m;
    }
    
    unsigned int min_presses = -1;

    // Initialize the intermediate results FIFO with a blue and a red press
    queue<ButtonResult> iresults;
    ButtonResult blue = press_blue(n, 0);
    ButtonResult red = press_red(n, 0);
    iresults.push(blue);
    iresults.push(red);

    // Loop through the queue of solutions
    while (iresults.size() > 0){
        // Get the oldest element and immediately remove it
        ButtonResult res = iresults.front();
        iresults.pop();

        int new_n = res.first;
        unsigned int presses = res.second;
        // Don't consider this result if the amount of presses already exceeds
        // our minimum
        if (presses > min_presses){
            continue;
        }

        // If our current display number is higher than n
        // we can reach m by blue presses only
        else if (new_n >= m){
            unsigned int extra_presses = new_n - m;
            min_presses = min(min_presses, presses+extra_presses);
            continue;
        }
       
        // In all other cases, add two iresults to our 
        // FIFO 
        else{
            // Only add blue press if display is larger than 0
            if (new_n > 0){
                iresults.push(press_blue(res.first, res.second));
            }

            iresults.push(press_red(res.first, res.second));
        }
    }
    return min_presses;    
}

int main(){
    int n, m;
    while(cin >> n, cin >> m){
        std::cout << getMinPresses(n, m) << endl;  
    }
    return 0;
}
