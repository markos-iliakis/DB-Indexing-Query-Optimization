#include "help_functions.h"

int main(void){

    srand(time(NULL));

    // make the random arrays
    int **r_array = makeRandArray(XDIMEN, YDIMEN);
    int **s_array = makeRandArray(XDIMEN, YDIMEN);

    // make the id/hashed-value arrays MHPWS PREPEI NA BALOUME KAI TO ROWID MESA STO TUPLE
    relation *r_relation, *s_relation;
    r_relation = malloc(sizeof(relation));
    s_relation = malloc(sizeof(relation));
    r_relation->tuples = makeHashIdArray(r_array, XDIMEN);
    s_relation->tuples = makeHashIdArray(s_array, XDIMEN);

    //print arrays
    printArrayTuple(r_array, r_relation->tuples, XDIMEN, YDIMEN);

    //find different values for r_tuple and create hist
    histogram *r_hist = NULL;

    for (int i = 0; i < XDIMEN; i++) {
        histogram *temp = searchHistogram(r_hist, r_relation->tuples[i].key);
        if (temp == NULL)
            addHistogram(&r_hist, r_relation->tuples[i].key);
        else
            addFreq(temp);
    }

    printHistogram(r_hist);

    printf("Length is %d\n", histogramSize(r_hist));
    int hist_length = histogramSize(r_hist);
    histogram *psum = malloc(hist_length * sizeof(histogram));

    createPsum(psum, r_hist, hist_length);

    for (int i = 0; i < hist_length; i++) {
        printf("Value : %3d Frequency : %3d\n", psum[i].value, psum[i].freq);
    }


    //edw thelei array R' pou tha ftiaxtei me to sum tou histogram
    relation *r_ord = malloc(sizeof(relation));
    createReorderedarray(r_ord, r_hist, psum, r_relation);
    destroyHistogram(r_hist);


    return 0;
}
