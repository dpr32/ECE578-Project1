#pragma once

#define TIME_BLOCK    50000;

const int CWo = 4;				// slots
const int CWmax = 1024;			// slots
const double TIME_INC = 0.1;	// slots

const double DIFS_DURRATION = 1;	// 20 microseconds (us)
const double SIFS_DURRATION = 0.5;	// 10 microseconds (us)

const int LAMDA_A = 50; // frames/sec
const int LAMDA_C = 50; // frames/sec

const double DATA_FRAME_SIZE = 12.5; // slots [ (1500 bytes / 6 Mbps) = 250 microseconds ]

const double ACK = 0.25; // slots [ (30 bytes / 6 Mbps) = 5 microseconds ]
const double RTS = 0.25; // slots [ (30 bytes / 6 Mbps) = 5 microseconds ]
const double CTS = 0.25; // slots [ (30 bytes / 6 Mbps) = 5 microseconds ]