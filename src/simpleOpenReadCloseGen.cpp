//
// Created by arezaii on 10/30/20.
//




{
    S0();
    for (int c1 = 0; c1 < m_numSubgrids; c1 += 1) {
        S1(c1);
        if (c1 + 1 == m_numSubgrids)
        S2(m_numSubgrids - 1);
        for (int c3 = 0; c3 < nz; c3 += 1)
            for (int c4 = 0; c4 < ny; c4 += 1) {
                S3(c1, c3, c4);
                for (int c5 = 0; c5 <= nx; c5 += 1)
                S4(c1, c3, c4, c5);
            }
    }
    S5();
}
