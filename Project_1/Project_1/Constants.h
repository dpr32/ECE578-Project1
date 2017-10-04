#pragma once



const int TIME_BLOCK = 500000;
const int CWo = 4;				// slots
const int CWmax = 1024;			// slots
const int	 TIME_INC = 1;	// slots

const int DIFS_ORIGINAL = 2;	// 20 microseconds (us)
const int SIFS_ORIGINAL = 1;	// 10 microseconds (us)

const int LAMDA_A = 50; // frames/sec
const int LAMDA_C = 50; // frames/sec

const int DATA_FRAME_SIZE = 100; // slots [ (1500 bytes / 6 Mbps) = 250 microseconds ]

const int ACK_ORIGINAL = 2; // slots [ (30 bytes / 6 Mbps) = 5 microseconds ]
const int RTS = 2; // slots [ (30 bytes / 6 Mbps) = 5 microseconds ]
const int	 CTS = 2; // slots [ (30 bytes / 6 Mbps) = 5 microseconds ]