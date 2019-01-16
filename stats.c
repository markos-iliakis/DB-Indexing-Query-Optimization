for (int k = 0; k < table_num; k++) {
    int col, row;

    int l[col]; //lowest value
    int u[col]; //largest value
    int f[col]; //total num of values
    int d[col]; // num of unique valuess

    for (int i = 0; i < col; i++) {
        bool* find_d;
        int temp_l = 0;
        int temp_u = 0;
        int temp_f = 0;

        //malloc find_d

        for (int j = 0; j < row; j++) {
            temp_f++;

            if (temp_l > tables[table_num][row][col]) {
                temp_l = tables[table_num][row][col];
            }

            if (temp_u < tables[table_num][row][col]) {
                temp_u = tables[table_num][row][col];
            }
        }
    }
}
