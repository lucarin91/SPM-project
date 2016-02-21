import json
import sse, tc

TEST_PATH = '../Test/good/'
SEQ = 'busy_test_sequential_2000x30_(0,1000,4500,10000,45000).json'
PAR_S = 'busy_test_N_2000x30_2_(0, 1000, 4500, 10000, 45000)_no234.json'
PAR_M = 'busy_test_mic_multy_N_2000x30.json'

if __name__ == '__main__':

    with open(TEST_PATH + PAR_S) as data_file:
        par_s = json.load(data_file)

    with open(TEST_PATH + PAR_M) as data_file:
        par_m = json.load(data_file)

    with open(TEST_PATH + SEQ) as data_file:
        seq = json.load(data_file)

    sse.plot(seq, par_m)
    sse.plot(seq, par_s)

    tc.plot(par_m)
    tc.plot(par_s).show()
