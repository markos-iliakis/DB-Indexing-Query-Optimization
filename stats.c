#define N 50000000

for (int k = 0; k < table_num; k++) {
    int col, row;

    int l[col]; //lowest value
    int u[col]; //largest value
    int f[col]; //total num of values
    int d[col]; // num of unique valuess

    for (int i = 0; i < col; i++) {
        int temp_l = 0;
        int temp_u = 0;
        int temp_f = 0;

        for (int j = 0; j < row; j++) {
            temp_f++;

            if (temp_l > tables[table_num][row][col]) {
                temp_l = tables[table_num][row][col];
            }

            if (temp_u < tables[table_num][row][col]) {
                temp_u = tables[table_num][row][col];
            }
        }

        bool* find_d;

        int bool_lim = u[i] - l[i] + 1;
        if (bool_lim > N)
            find_d = malloc(N*sizeof(bool));
        else
            find_d = malloc(bool_lim*sizeof(bool));

        for (int m = 0; m < bool_lim; m++)
            find_d[m] = false;

        for (int j = 0; j < row; j++) {
            
        }
    }
}
