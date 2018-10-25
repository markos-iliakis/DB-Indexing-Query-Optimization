#include "help_functions.h"

int main(void){

    srand(time(NULL));

    // make the random arrays
    int **r_array = makeRandArray(XDIMEN, YDIMEN);
    int **s_array = makeRandArray(XDIMEN, YDIMEN);

    // make the id/hashed-value arrays
    tuple *r_tuple = makeHashIdArray(r_array, XDIMEN);
    tuple *s_tuple = makeHashIdArray(s_array, XDIMEN);

    //print arrays
    printArrayTuple(r_array, r_tuple, XDIMEN, YDIMEN);

    //find different values for r_tuple and create hist
    histogram *r_hist = NULL;

    for (int i = 0; i < XDIMEN; i++) {
        histogram *temp = searchHistogram(r_hist, r_tuple[i].key);
        if (temp == NULL)
            addHistogram(&r_hist, r_tuple[i].key);
        else
            addFreq(temp);
    }

    printHistogram(r_hist);

    destroyHistogram(r_hist);
}
