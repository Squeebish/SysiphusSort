/*
* Sysiphus Sort: an homage to the ancient myth of Sysiphus
* This code is a bubble sort, excpet every swap the number has a chance to fall back down
* Written by Jake Spaulding 2024 for the cs50 create task
* takes 4 args or can be run without any to use a defualt template:
* 1: the type of array (user, rev, rand, rand_inc)
* 2: an int to define the size of the array
* 3: an int to define the maximum probability of the fall
* 4: the type of probability growth (lin, log, const)
*/

#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <unistd.h>
#include <cstring>
#include <algorithm>
#include <math.h>

using namespace std;
// max size of array
#define MAX_SIZE 9999
// the wait speeds
#define MAX_SPEED 50000
#define STD_SPEED 220000

// num array
int nums[MAX_SIZE];
// gonna store if it's falling
bool falling;
// store the order of magnitude for the max number
int mag;
// max prob %
int max_prob;
// defines which equation to use
int prob_eq;

// the sort function, returns true when done, false if there is a fall
bool sort(int size);
// brings the pos index to 0
void fall(int size, int pos);
// prints the array and hightlights the position added
void printify(int size, int pos, string left, string right);
// animation played when the number reaches top
void end_anim(int size, int pos);
// random array generation function
void random_array_gen(int size);
// make an array that is just inverted from swapped
void rev_array(int size);
// makes a truly random array
void rand_inc(int size);
// let the user populate the array
void user(int size);
// will handle calling the propper probability function
bool prob(int size, int pos);

int main(int argc, char **argv)
{
    // the usage description
    string use = "Usage:\nThe first argument is array type (rand, rev, rand_inc)\nThe second argument is array size\nThe thrid argument is maximum probability for the fall (in %)\nThe fourth argument is the kind of probability growth(lin, log, const)\nor no arguments to use defualt values\n";
    // seed rng
    srand(time(NULL));
    int size;

    // default, if no params are entered
    if (argc == 1)
    {
        size = 20;
        max_prob = 15;
        rev_array(size);
        prob_eq = 3;
    }

    // handle user inputs
    else if (argc == 5)
    {
        size = atoi(argv[2]);
        // make the size of the array
        if (size < 2 || size > MAX_SIZE)
        {
            cout << "Invalid size: must be an itger from 2 - " << MAX_SIZE <<"\n\n" << use;
        }

        // make the max prob
        max_prob = atoi(argv[3]);
        if (max_prob > 100 || size < 0)
        {
            cout << "invalid probability input: size must be a positive integer from 0 - 100\n\n" << use;
            return 4;
        }

        // populate arrays
        if(!strcmp(argv[1], "rand_inc"))
        {
            rand_inc(size);
        }
        else if (!strcmp(argv[1], "rand"))
        {
            random_array_gen(size);
        }
        else if (!strcmp(argv[1], "rev"))
        {
            rev_array(size);
        }
        else if (!strcmp(argv[1], "user"))
        {
            user(size);
        }
        else
        {
            cout << "invalid array type: possible inputs\nrand: random\nrev: reverse\nrand_inc: inclusive random\nuser: user input\n\n" << use;
            return 2;
        }

        // define the type of growth
        if (!strcmp(argv[4], "lin"))
        {
            prob_eq = 1;
        }
        else if (!strcmp(argv[4], "log"))
        {
            prob_eq = 3;
        }
        else if (!strcmp(argv[4], "const"))
        {
            prob_eq = 4;
        }
        else
        {
            cout << "Invalid probability function\nLinier: lin\nLogistic: log\nConstant: const\n" << use;
            return 4;
        }
    }
    else
    {
        cout << "invalid arguments:\n" << use;
        return 1;
    }
    // get the order of magnitude
    mag = floor(log10(*max_element(nums, nums + size)));
    // bubble sort it
    while(!sort(size));
    printify(size, 0 ,"", "");
    return 0;
}

// sorting tasks
bool sort(int size)
{
    // outer loop for sorting each number
    while(true)
    {
        int pos = 0;

        // find first unsorted number
        while ((nums[pos] < nums[pos + 1] && pos < size - 1) || pos == size - 1)
        {
            if (pos == size - 1)
            {
                return 1;
            }
            pos++;
        }

        printify(size, pos, " |", "| ");
        // compare each number until it's less
        while((nums[pos] > nums[pos + 1] && pos  < size - 1))
        {
            // swap the numbers
            swap(nums[pos], nums[pos + 1]);

            pos++;

            printify(size, pos, " |", "| ");
            usleep(STD_SPEED);

            // check for fall condition
            if (prob(size, pos))
            {
                fall(size, pos);
                return 0;
            }
            // plays the end animation
            if (pos == size -1 || (nums[pos] <= nums[pos + 1]))
            {
                end_anim(size, pos);
            }
        }
    }
    return 1;
}

void fall(int size, int pos)
{
    // store the speed
    int speed = STD_SPEED;
    usleep(120000);

    // little shake animation (removed)
    for (int i = 0; i < 4; i++)
    {
        printify (size, pos, "|", "|  ");
        usleep(80000);
        printify(size, pos, " |", "| ");
        usleep(80000);
    }
    printify(size, pos, " |", "| ");
    usleep(150000);

    falling = 1;
    for (int i = pos; i > 0; i--)
    {
        // accelerate the fall
        if (speed > MAX_SPEED)
        {
            speed -= 25000;
        }
        swap(nums[i], nums[i - 1]);

        // make it flow :)
        usleep(speed / 3);
        printify(size, i - 1, "  |", "|");
        usleep(speed / 3);
        printify(size, i - 1, " |", "| ");
        usleep(speed / 3);
        printify(size, i - 1, "|", "|  ");
    }
    falling = 0;
    printify(size, 0, " |", "| ");
    usleep(300000);
}

// animation tasks
void printify(int size, int pos, string left, string right)
{
    // clear the screen
    cout << string(100,'\n');
    // display text for the fall
    if(falling)
    {
        cout << "ONE MUST IMAGINE SYSIPHUS HAPPY\n\n";
    }
    //make it look normal if pos != 0
    if (pos != 0)
    {
        cout << "  ";
    }
    for (int k = 0; k < size; k++)
    {
        // end line after 20 chars
        if (k >= 20 && k % 20 == 0 && k != pos)
        {
            cout << "\n  ";
        }
        else if (k >= 20 && k % 20 == 0 && k == pos)
        {
            cout << "\n";
        }

        // make the main number special
        if (k == pos)
        {
            cout << left << nums[k] << right;
        }
        // make the spacing right for the main number
        else if (k == pos - 1)
        {
            cout << nums[k];
        }
        else
        {
            cout << nums[k] << "  ";
        }
        // makes it even for numbers of different Orders of magnitude
        cout << string((mag - floor(log10(nums[k]))), ' ');
    }
    // flush the io stream
    cout << flush;
}

void end_anim(int size, int pos)
{
    printify(size, pos, " |", "| ");
    usleep(100000);

    printify(size, pos, " \\", "/ ");
    usleep(120000);

    printify(size, pos, "- ", " -");
    usleep(140000);

    printify(size, pos, "_ ", " _");
    usleep(250000);
}

// array gens
void random_array_gen(int size)
{
    // fill array
    for (int i = 1; i <= size; i++)
    {
        nums[i - 1] = i;
    }
    // randomize by swapping with random places
    for (int i = 0; i < size; i++)
    {
        swap(nums[i],nums[rand() % (size - 1)]);
    }
}

void rev_array(int size)
{
    for (int i = 0; i < size; i++)
    {
        nums[i] = size - i;
    }
}

void rand_inc(int size)
{
    for (int i = 0; i < size; i++)
    {
        nums[i] = rand() % MAX_SIZE;
    }
}

void user(int size)
{
    for (int i = 1; i <= size; i++)
    {
        cout << "\nEnter number " << i << ": " << flush;
        cin >> nums[i - 1];
        if (cin.fail())
        {
            cout << "invalid input\n";
            user(size);
        }
    }
}

// prob functions
bool prob(int size, int pos)
{
    switch(prob_eq)
    {
        // linear growth
        case 1:
            return(rand() % 100 < round(pos * 1. / size * max_prob));

        // logistic growth
        case 3:
            return(rand() % 100 < round(max_prob / (1 + exp(-10. / size * (pos - size / 2)))));

        // constant
        case 4:
            return(rand() % 100 < max_prob);
    }
    return 0;
}