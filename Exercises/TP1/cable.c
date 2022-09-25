// Virtual cable program to test serial port.
// Creates a pair of virtual Tx / Rx serial ports using "socat".
//
// Author: Manuel Ricardo [mricardo@fe.up.pt]
// Modified by: Eduardo Nuno Almeida [enalmeida@fe.up.pt]

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <termios.h>
#include <unistd.h>

// Baudrate settings are defined in <asm/termbits.h>, which is
// included by <termios.h>
#define BAUDRATE B38400
#define _POSIX_SOURCE 1 // POSIX compliant source
#define FALSE 0
#define TRUE 1

#define BUF_SIZE 2048

typedef enum
{
    CableModeOn,
    CableModeOff,
    CableModeNoise,
} CableMode;

// Returns: serial port file descriptor (fd).
int openSerialPort(const char *serialPort, struct termios *oldtio, struct termios *newtio)
{
    int fd = open(serialPort, O_RDWR | O_NOCTTY);

    if (fd < 0)
        return -1;

    // Save current port settings
    if (tcgetattr(fd, oldtio) == -1)
        return -1;

    memset(newtio, 0, sizeof(*newtio));
    newtio->c_cflag = BAUDRATE | CS8 | CLOCAL | CREAD;
    newtio->c_iflag = IGNPAR;
    newtio->c_oflag = 0;
    newtio->c_lflag = 0;
    newtio->c_cc[VTIME] = 1; // Inter-character timer unused
    newtio->c_cc[VMIN] = 0;  // Read without blocking
    tcflush(fd, TCIOFLUSH);

    if (tcsetattr(fd, TCSANOW, newtio) == -1)
        return -1;

    return fd;
}

// Add noise to a buffer, by flipping the byte in the "errorIndex" position.
void addNoiseToBuffer(unsigned char *buf, size_t errorIndex)
{
    buf[errorIndex] ^= 0xFF;
}

int main(int argc, char *argv[])
{
    printf("\n");

    system("socat -dd PTY,link=/dev/ttyS10,mode=777 PTY,link=/dev/emulatorTx,mode=777 &");
    sleep(1);
    printf("\n");

    system("socat -dd PTY,link=/dev/ttyS11,mode=777 PTY,link=/dev/emulatorRx,mode=777 &");
    sleep(1);

    printf("\n\n"
           "Transmitter must open /dev/ttyS10\n"
           "Receiver must open /dev/ttyS11\n"
           "\n"
           "The cable program is sensible to the following interactive commands:\n"
           "--- on           : connect the cable and data is exchanged (default state)\n"
           "--- off          : disconnect the cable disabling data to be exchanged\n"
           "--- noise        : add fixed noise to the cable\n"
           "--- end          : terminate the program\n"
           "\n");

    // Configure serial ports
    struct termios oldtioTx;
    struct termios newtioTx;

    int fdTx = openSerialPort("/dev/emulatorTx", &oldtioTx, &newtioTx);

    if (fdTx < 0)
    {
        perror("Opening Tx emulator serial port");
        exit(-1);
    }

    struct termios oldtioRx;
    struct termios newtioRx;

    int fdRx = openSerialPort("/dev/emulatorRx", &oldtioRx, &newtioRx);

    if (fdRx < 0)
    {
        perror("Opening Rx emulator serial port");
        exit(-1);
    }

    // Configure stdin to receive commands to this program
    int oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    unsigned char tx2rx[BUF_SIZE] = {0};
    unsigned char rx2tx[BUF_SIZE] = {0};
    char rxStdin[BUF_SIZE] = {0};

    CableMode cableMode = CableModeOn;
    volatile int STOP = FALSE;

    printf("Cable ready\n");

    while (STOP == FALSE)
    {
        // Read from Tx
        int bytesFromTx = read(fdTx, tx2rx, BUF_SIZE);

        if (bytesFromTx > 0)
        {
            if (cableMode == CableModeOff)
            {
                printf("bytesFromTx=%d > bytesToRx=CONNECTION OFF\n", bytesFromTx);
            }
            else
            {
                if (cableMode == CableModeNoise)
                {
                    addNoiseToBuffer(tx2rx, 0);
                }

                int bytesToRx = write(fdRx, tx2rx, bytesFromTx);
                printf("bytesFromTx=%d > bytesToRx=%d\n", bytesFromTx, bytesToRx);
            }
        }

        // Read from Rx
        int bytesFromRx = read(fdRx, rx2tx, BUF_SIZE);

        if (bytesFromRx > 0)
        {
            if (cableMode == CableModeOff)
            {
                printf("bytesToTx=CONNECTION OFF < bytesFromRx=%d\n", bytesFromRx);
            }
            else
            {
                if (cableMode == CableModeNoise)
                {
                    addNoiseToBuffer(rx2tx, 0);
                }

                int bytesToTx = write(fdTx, rx2tx, bytesFromRx);
                printf("bytesToTx=%d < bytesFromRx=%d\n", bytesToTx, bytesFromRx);
            }
        }

        // Read commands from STDIN to control the cable mode
        int fromStdin = read(STDIN_FILENO, rxStdin, BUF_SIZE);
        if (fromStdin > 0)
        {
            rxStdin[fromStdin - 1] = '\0';

            if (strcmp(rxStdin, "off") == 0 || strcmp(rxStdin, "0") == 0)
            {
                printf("CONNECTION OFF\n");
                cableMode = CableModeOff;
            }
            else if (strcmp(rxStdin, "on") == 0 || strcmp(rxStdin, "1") == 0)
            {
                printf("CONNECTION ON\n");
                cableMode = CableModeOn;
            }
            else if (strcmp(rxStdin, "noise") == 0 || strcmp(rxStdin, "2") == 0)
            {
                printf("CONNECTION NOISE\n");
                cableMode = CableModeNoise;
            }
            else if (strcmp(rxStdin, "end") == 0)
            {
                printf("END OF THE PROGRAM\n");
                STOP = TRUE;
            }
        }
    }

    // Restore the old port settings
    if (tcsetattr(fdRx, TCSANOW, &oldtioRx) == -1)
    {
        perror("tcsetattr");
        exit(-1);
    }

    if (tcsetattr(fdTx, TCSANOW, &oldtioTx) == -1)
    {
        perror("tcsetattr");
        exit(-1);
    }

    close(fdTx);
    close(fdRx);

    system("killall socat");

    return 0;
}
