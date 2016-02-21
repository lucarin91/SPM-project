from sys import argv
import json
import sse
import tc

TEST_PATH = '../Test/good/'
SEQ = 'busy_test_sequential_N_2000x30.json'
PAR_S = 'busy_test_N_2000x30_2_(0, 1000, 4500, 10000, 45000)_with65-70.json'
PAR_M = 'busy_test_mic_multy_N_2000x30.json'

if __name__ == '__main__':

    with open(TEST_PATH + PAR_S) as data_file:
        par_s = json.load(data_file)

    with open(TEST_PATH + PAR_M) as data_file:
        par_m = json.load(data_file)

    with open(TEST_PATH + SEQ) as data_file:
        seq = json.load(data_file)

    if len(argv) == 1 or argv[1] == 'sse':
        p = sse.plot(seq, par_m)
        p = sse.plot(seq, par_s)

    if len(argv) == 1 or argv[1] == 'tc':
        p = tc.plot(par_m, ylimit=[0.25, 0.47])
        p = tc.plot(par_s, ylimit=[0.4, 0.8])

    if len(argv) == 1 or argv[1] == 'vs':
        p = sse.plot([seq[3], seq[3]],
                     [par_m[3], par_s[3]],
                     ['single queue', 'multiple queue'])
    p.show()
