#pragma once

//////////////////////////////////
//  1 slot == 10 microseconds   //
//////////////////////////////////

const int TIME_BLOCK = 1000000;	// slots [ (10 sec * 1e+6) = 10000000 microseconds ]
const int CWo = 4;				// slots
const int CWmax = 1024;			// slots
const int TIME_INC = 1;		    // slots

const int DIFS_ORIGINAL = 2;	// 20 microseconds (us)
const int SIFS_ORIGINAL = 1;	// 10 microseconds (us)

const int LAMDA_A = 300; // frames/sec
const int LAMDA_C = 600; // frames/sec

const int DATA_FRAME_SIZE = 200; // slots [ (1500 bytes * 8 / 6 Mbps) = 2000 microseconds ]

const int RTS = 4;			// slots [ (30 bytes * 8 / 6 Mbps) = 40 microseconds ]
const int CTS = 4;			// slots [ (30 bytes * 8 / 6 Mbps) = 40 microseconds ]
const int ACK_ORIGINAL = 4; // slots [ (30 bytes * 8 / 6 Mbps) = 40 microseconds ]
