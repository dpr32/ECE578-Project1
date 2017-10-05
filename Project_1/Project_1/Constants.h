#pragma once


const int CWo = 4;				// slots
const int CWmax = 1024;			// slots
const int TIME_BLOCK = 500000;


const int LAMDA_A = 50; // frames/sec
const int LAMDA_C = 50; // frames/sec

const int DATA_FRAME_SIZE = 100; // slots [ (1500 bytes * 8 / 6 Mbps) = 2000 microseconds ]

const int RTS = 2;			// slots [ (30 bytes * 8 / 6 Mbps) = 40 microseconds ]
const int CTS = 2;			// slots [ (30 bytes * 8 / 6 Mbps) = 40 microseconds ]
const int ACK_ORIGINAL = 2; // slots [ (30 bytes * 8 / 6 Mbps) = 40 microseconds ]
